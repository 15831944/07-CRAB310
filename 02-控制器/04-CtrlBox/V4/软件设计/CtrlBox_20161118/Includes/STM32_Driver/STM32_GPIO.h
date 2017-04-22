/***********************************************************************************************
*�ļ���		��	STM32_GPIO.h
*����		  ��	GPIO��ʼ����������
*����		  ��	Ҷ��˳
*��������	��	����
*�޸�����	��	20160104
*�޸��� 		��	�Ϻ�
*�޸�ԭ��	��	������룬���ע��
*�汾 		��	2.0
*��ʷ�汾	��	����
***********************************************************************************************/

#ifndef __STM32_GPIO_H
	#define __STM32_GPIO_H	
	
	#ifdef __cplusplus
		extern "C" {
	#endif
		 
	#include "stm32f10x.h"
			
	void STM32_GpioOneInit(uint16_t, GPIOSpeed_TypeDef, GPIOMode_TypeDef, GPIO_TypeDef*);
		 
	#ifdef __cplusplus
		}
	#endif
#endif





