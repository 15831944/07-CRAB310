/**
  ******************************************************************************
	*�ļ���LEDLighter.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ��LED�����ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 
	
#include "LEDLighter.h"
LEDLighter::LEDLighter(GPIO_TypeDef *port,unsigned int Pin)
{
	lighterPort=port;
	lighterPin=Pin;
	if(port==GPIOA)
		portNumber=0;
	else if(port==GPIOB)
		portNumber=1;
	else if(port==GPIOC)
		portNumber=2;
	else if(port==GPIOD)
		portNumber=3;
	else if(port==GPIOE)
		portNumber=4;
	else if(port==GPIOF)
		portNumber=5;
	else if(port==GPIOG)
		portNumber=6;
	else if(port==GPIOH)
		portNumber=7;
	else if(port==GPIOI)
		portNumber=8;
	initLighter();
}

LEDLighter::~LEDLighter()
{
// 	delete lighterPort;
}

/**
  * ��  �ܣ���ʼ���ƵĶ˿�
  * ��  ������
  * ����ֵ����
  */
void LEDLighter::initLighter()
{
	RCC_AHB1PeriphClockCmd(((uint32_t)(0x01<<portNumber)), ENABLE);
	STM32_GpioOneInit(lighterPin,GPIO_Speed_2MHz,GPIO_Mode_OUT,GPIO_OType_PP,GPIO_PuPd_UP,lighterPort);	
}

/**
  * ��  �ܣ���ת�ȵ�����״̬
  * ��  ������
  * ����ֵ����
  */
void LEDLighter::reverseLight()	//��ת�Ƶ�״̬
{
	 GPIO_WriteBit(lighterPort, lighterPin, (BitAction)(1 - GPIO_ReadOutputDataBit(lighterPort, lighterPin)));
}

/**
  * ��  �ܣ����õȵ�����
  * ��  ����
	*			true:����
	*			false:Ϩ��
  * ����ֵ����
  */
void LEDLighter::setLightStatus(bool light)
{
	if(light)
		GPIO_ResetBits(lighterPort, lighterPin);
	else
		GPIO_SetBits(lighterPort, lighterPin);
}
