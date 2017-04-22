/**
  ******************************************************************************
	*�ļ���LEDLighter.h
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ��LED�����ͷ�ļ�
	*��ע��
	*
  ******************************************************************************  
	*/ 
#ifndef _LEDLIGHTER_H
#define _LEDLIGHTER_H

#ifdef __cplusplus  
extern "C"
{
#endif
	#include <stdlib.h>			 
// 	#include "STM32F4_LedDisp.h"
	#include <stm32f4xx_gpio.h>
	#include "STM32F4_GpioInit.h"	
#ifdef __cplusplus
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LEDLighter
{
public:
	LEDLighter(GPIO_TypeDef *port,unsigned int Pin);
	~LEDLighter();
// 	void setPort(GPIO_TypeDef *port);
// 	void setPin(unsigned int Pin);
// 	void initLighter();
	void setLightOn(){setLightStatus(true);}		//����
	void setLightOff(){setLightStatus(false);}	//�ص�
	void reverseLight();	//��ת�Ƶ�״̬
	void setLightStatus(bool light);
private:
	void initLighter();
	GPIO_TypeDef *lighterPort;
	unsigned int lighterPin;
	int portNumber;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}  
#endif
#endif



