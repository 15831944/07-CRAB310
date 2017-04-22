/**
  ******************************************************************************
	*�ļ���Key.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ���������ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 
#include "Key.h"

/**
  * ��  �ܣ�������Ĺ��캯��
  * ��  ����
	* 	port�������������ڵ�GPIO�˿�
	*		Pin : �������ź�
  * ����ֵ����
  */
Key::Key(GPIO_TypeDef *port,uint16_t Pin, bool bLevel)
{
	TrickCount	= 0;
	KeyPort		= port;
	KeyPin		= Pin;
	KeyLevel	= bLevel;
	FinalState	= KEY_PRESS_UP;
	
	initKey();
}

/**
  * ��  �ܣ����������������
  * ��  ������
  * ����ֵ����
  */
Key::~Key()
{
	KeyPort=NULL;
}

/**
  * ��  �ܣ���ʼ���ƵĶ˿�
  * ��  ������
  * ����ֵ����
  */
void Key::initKey()
{
	STM32_GpioOneInit(KeyPin,GPIO_Speed_2MHz,GPIO_Mode_IPU,KeyPort);	//��������GPIO_Mode_IPU
}

/**
  * ��  �ܣ����ذ���ֵ
  * ��  ������
  * ����ֵ����
  */
void Key::getValue()
{
	uint8_t TempState;//��ʱ�������洢��ǰ������IO��ƽ
	if(KeyLevel)
		TempState = !GPIO_ReadInputDataBit(KeyPort,KeyPin);
	else
		TempState = GPIO_ReadInputDataBit(KeyPort,KeyPin);
	
	if(FinalState!=TempState)//IO��ƽ�仯
	{
		TrickCount++;//TimerTick�Լ�
		if(TrickCount>KEY_MAX_TIMER)//�����涨ʱ���ƽ��Ȼ��һ��
		{
			FinalState=TempState;//����IO��ƽ
			TrickCount=0;//��ʱ��������Ϊ0
		}
	}
	else//IO��ƽ���仯
	{
		TrickCount=0;
	}
}

