/**
******************************************************************************
*�ļ���IoOut.cpp
*���ߣ��Ϻ�
*�汾��1.0
*���ڣ�2015-03-09
*��Ҫ��IoOut���ʵ��
*��ע��
******************************************************************************  
*/ 
	
#include "IoOut.h"
  
/**
*	@����˵����  IoOut���캯��
*	@������		port	=	[GPIOA(Ĭ��),GPIOB,GPIOC,GPIOD,GPIOB,GPIOE,GPIOF,GPIOG]
*				Pin		=	[GPIO_Pin_0(Ĭ��)~GPIO_Pin_15]
*				bLevel	=	[false(Ĭ��)��true]
*	@����ֵ�� 	��
*	@��ע�� 			
*/
IoOut::IoOut(GPIO_TypeDef *port, uint16_t pin, bool bLevel)
{
	ioOutPort=port;
	ioOutPin=pin;
	ioOutLevel = bLevel;
	
	initIo();
}


IoOut::~IoOut()
{
// 	delete ioOutPort;
}

/**
*	@����˵����  ��ʼ����IO
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		PD0��PD1ֻ������2MHzģʽ��
*/
void IoOut::initIo()
{
	//	PD0��PD1ֻ������2MHzģʽ��
	if(ioOutPort==GPIOD&&(ioOutPin==GPIO_Pin_0||ioOutPin==GPIO_Pin_1))
		STM32_GpioOneInit(ioOutPin,GPIO_Speed_50MHz,GPIO_Mode_Out_PP,ioOutPort);	//�������
	else
		STM32_GpioOneInit(ioOutPin,GPIO_Speed_10MHz,GPIO_Mode_Out_PP,ioOutPort);	//�������
	
	setOff();
}

/**
*	@����˵����  ��תIo��״̬
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
void IoOut::reverseState()	
{
	 GPIO_WriteBit(ioOutPort, ioOutPin, (BitAction)(1 - GPIO_ReadOutputDataBit(ioOutPort, ioOutPin)));
}

/**
*	@����˵����  ����IO
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		ioOutLevelΪtrueʱ�ߵ�ƽ��Ч����֮�͵�ƽ��Ч
*/
void IoOut::setOn()
{
	if(ioOutLevel)
		GPIO_SetBits(ioOutPort, ioOutPin);
	else
		GPIO_ResetBits(ioOutPort, ioOutPin);
}	

/**
*	@����˵����  �ر�IO
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		ioOutLevelΪtrueʱ�͵�ƽ��Ч����֮�ߵ�ƽ��Ч
*/
void IoOut::setOff()
{
	if(ioOutLevel)
		GPIO_ResetBits(ioOutPort, ioOutPin);
	else
		GPIO_SetBits(ioOutPort, ioOutPin);
}	

