/**
  ******************************************************************************
	*�ļ���PowerControl.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ����Դ����Э���ʵ��
	*��ע���ػ�����Ϳ���������ʱû�õ�
	*
  ******************************************************************************  
	*/ 


/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "PowerControl.h"
#include "STM32F4_GpioInit.h"
/* ���Ͷ��� --------------------------------------------------------------------*/
/* �궨��-----------------------------------------------------------------------*/ 
#define SW_ST_ON	   	1
#define SW_ST_OFF	   	0 
#define NOTSURE_MCU   2
#define SWCTRL_MAX_TIMER   100        //�������Ƚ�ֵ
#define TURNOFF_BUT GPIO_ReadInputDataBit(__GPIO_IN1_PORT, __GPIO_IN1_PIN)

//PowerControl�๹�캯��
PowerControl::PowerControl(SerialPort * p):BaseControl(p)
{
	addr=0X03;
	command|=0X30;
	powerDown=false;
	powerReadState=false;
}

//PowerControl����������
PowerControl::~PowerControl()
{
	
}
//a4 00 01 00 00 a5
/**
  * ��  �ܣ����͹ػ������Դ���ư壬����OK
  * ��  ������
  * ����ֵ����
  * 
  */
void PowerControl::sendPowerOffCommand()								//���͹ػ�����
{
	command&=0xf0;
	command|=0X01;
	data->DATA_16=0x2222;
	sendCommand();	//��������������ϣ���������
}

/**
  * ��  �ܣ����Ϳ��������Դ���ư壬����OK
  * ��  ������
  * ����ֵ����
  * 
  */
void PowerControl::sendPowerOnCommand()							//���Ϳ�������
{
	command&=0xf0;
	command|=0X01;
	data->DATA_16=0x1111;
	sendCommand();	//��������������ϣ���������
}

/**
  * ��  �ܣ����Ϳ��ػ������Դ���ư壬����OK
  * ��  ������
  * ����ֵ����
  * 
  */
void PowerControl::sendPowerOnOffCommand()						//���Ϳ��ػ�����
{
	if(powerDown)
	{
// 		sendPowerOffCommand();								//���͹ػ�����
		POW_OFF;
	}
	else
	{
// 		sendPowerOnCommand();									//���Ϳ�������
		POW_ON;		
	}
}
/**
  * ��  �ܣ����͵�ص�����ȡָ���Դ���ư�
  * ��  ������ر��
	* ����ֵ��0x00:���1
	*					0x01:���2
	*					0x02:���3
	*					0x03:���4
  * ����ֵ����
  */
void PowerControl::sendGetEctQuantityCommand(int8_t batteryNum)					//���͵�����ȡ����
{
	command&=0xf0;
	command|=0X02;
	data->DATA_16=0x0000;
	data->DATA_8[0]=batteryNum;
// 	data->DATA_8[1]=(batteryNum<<6);
	sendCommand();	//��������������ϣ���������
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}
/**
  * ��  �ܣ������¶Ȼ�ȡָ���Դ���ư�
  * ��  ����������
	* ����ֵ��0x00:���1
	*					0x01:���2
	*					0x02:���3
  * ����ֵ����
  */
void PowerControl::sendGetTemperatureCommand(uint8_t motorNum)					//�����¶ȶ�ȡ����
{
	command&=0xf0;
	command|=0X03;
	data->DATA_16=0x0000;
	data->DATA_8[0]=motorNum;
	data->DATA_8[1]=0;
	sendCommand();	//��������������ϣ���������
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}

/**
  * ��  �ܣ������¶Ȼ�ȡָ���Դ���ư�
  * ��  ����������
	* ����ֵ��0x00:���1
	*					0x01:���2
	*					0x02:���3
  * ����ֵ����
  */
void PowerControl::sendGetTempCommand(int8_t moterNum)									//�����¶ȶ�ȡ����
{
	command&=0xf0;
	command|=0X03;
	data->DATA_16=0x0000;
	data->DATA_8[1]=(moterNum<<6);
	sendCommand();	//��������������ϣ���������
}

/**
  * ��  �ܣ�����Դ�����Ƿ���
  * ��  ������
  * ����ֵ��
	*  	true: ����
  * 	false:û����
  */
bool PowerControl::checkPowerKey()								//���ػ�����
{
	static unsigned char SwTimerTick = 0;
	static unsigned char SwPreState= NOTSURE_MCU;		//��ʾǰһʱ�̰���״̬,Ĭ�������û�а������� 2
	unsigned char SwReadState=0;											//����һ���м�������𵽴��ε�����

	SwReadState = TURNOFF_BUT; 											//��ȡ��λPA������ 0 or 1
	if(SwPreState != SwReadState)
	{
		if(SwTimerTick>SWCTRL_MAX_TIMER)
		{
			SwPreState = SwReadState;
			if(SwPreState == SW_ST_OFF)
			{   
        powerReadState = true;
				//LED1_ON;
			}
			else
			{  
        powerReadState = false;    
				//LED1_OFF;
			}
		}
		else
		{
			SwTimerTick++;
    }	
	}
	else
	{
    SwTimerTick=0;
  }
	return powerReadState;
}




