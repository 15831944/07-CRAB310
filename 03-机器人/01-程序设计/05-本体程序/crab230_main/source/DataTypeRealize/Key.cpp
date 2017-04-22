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
Key::Key(GPIO_TypeDef *port,unsigned int Pin)
{
	keyPort=port;
	keyPin=Pin;
	if(port==GPIOA)
	{ 	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
	}
	else if(port==GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  
	}
	else if(port==GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  
	}
	else if(port==GPIOD)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
	}
	else if(port==GPIOE)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);  
	}
	else if(port==GPIOF)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);  
	}
	else if(port==GPIOG)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);  
	}
	initKey();
}

/**
  * ��  �ܣ����������������
  * ��  ������
  * ����ֵ����
  */
Key::~Key()
{
	keyPort=NULL;
}

/**
  * ��  �ܣ���ʼ���ƵĶ˿�
  * ��  ������
  * ����ֵ����
  */
void Key::initKey()
{
	STM32_GpioOneInit(keyPin,GPIO_Speed_50MHz,GPIO_Mode_IN,GPIO_OType_PP,GPIO_PuPd_NOPULL,keyPort);    
}

/**
  * ��  �ܣ����ذ���ֵ
  * ��  ������
  * ����ֵ��
	* true:��������
	* false:����û�а��£����ߵ�����
  */
bool Key::getValue()
{
	return !GPIO_ReadInputDataBit(keyPort,keyPin);
}

