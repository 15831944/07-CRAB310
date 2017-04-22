/**
  ******************************************************************************
	*�ļ���GpsImuControl.c
	*���ߣ�Ҷ��˳
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-27
	*��Ҫ��GPS��IMU�豸�Ŀ���Э�����ʵ��
	*��ע��
  ******************************************************************************  
  */ 


/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "GpsImuControl.h"

/* ���Ͷ��� --------------------------------------------------------------------*/
/* �궨��-----------------------------------------------------------------------*/ 
#define POWER_LED_CTR 0X07

#define GREEN 		0X01
#define RED 			0X02
#define NO_COLOR 	0X03


GpsImuControl::GpsImuControl(SerialPort * p):BaseControl(p)
{
	powerLEDColor=GREEN;
}
//OtherDeviceControl����������
GpsImuControl::~GpsImuControl()
{
	
}

/**
  * ��  �ܣ����õ�Դ�Ƶ���ɫ
  * ��  ����
	*		color ���Ƶ���ɫ����
  * ����ֵ����
  * 
  */
void GpsImuControl::setPowerLEDColor(uint8_t color)
{
	powerLEDColor=color;
}

/**
  * ��  �ܣ����ݵ�ѹֵ���õ�Դָʾ�Ƶ���ɫ
  * ��  ����
	*		voltage ����ѹֵ���� 
  * ����ֵ����
  * 
  */
// bool GpsImuControl::setPowerLEDColorFromVoltage(uint8_t voltage)
// {
// 	static uint8_t index=0;
// 	
// 	if(voltage>NORMAL_VOLTAGE)//���̵�
// 	{
// 		setPowerLEDColor(GREEN);
// 		index=0;
// 	}
// 	else if(voltage>WARNING_VOLTAGE)//�̵ƺͺ�ƽ�����
// 	{
// 		if(powerLEDColor==GREEN)
// 			setPowerLEDColor(RED);
// 		else
// 			setPowerLEDColor(GREEN);
// 		index=0;
// 	}
// 	else if(voltage>DANGER_VOLTAGE)//�����
// 	{
// 		setPowerLEDColor(RED);
// 		index=0;
// 	}
// 	else //�����
// 	{
// 		if(powerLEDColor==NO_COLOR)
// 			setPowerLEDColor(RED);
// 		else
// 			setPowerLEDColor(NO_COLOR);
// 		index++;
// 	}
// 	if(index>20)
// 	{
// 		index=0;
// 		return true;
// 	}
// 	else 
// 		return false;
// }
           void GpsImuControl::setPowerLEDColorFromVoltage(uint8_t voltage)
{
	if(voltage>130)//�̵�ȫ�� 130 127 124 121 118 
	{
		setPowerLEDColor(5);
	}
	else if(voltage>127)
	{
		setPowerLEDColor(4);
	}
	else if(voltage>124)
	{
		setPowerLEDColor(3);
	}
	else if(voltage>121)
	{
		setPowerLEDColor(2);
	}
	else if(voltage>118)
	{
		setPowerLEDColor(1);
	}
	else
	{
		setPowerLEDColor(0);
	}
}

void GpsImuControl::sendsetLEDColorCommand()
{
	uint8_t Command[6]={0xA4, 0x01, 0x17, 0x00, 0x00, 0x00};
	Command[4]=powerLEDColor;
	Command[5]=0xBC+Command[4];
	port->write(Command,6);
}






