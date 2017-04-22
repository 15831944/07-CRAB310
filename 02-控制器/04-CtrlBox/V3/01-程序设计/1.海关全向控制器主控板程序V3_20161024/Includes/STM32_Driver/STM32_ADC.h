/***********************************************************************************************
*�ļ���		��	STM32_ADC.h
*����		��	ADC1��ʼ��(DMA����)
*����		��	����
*��������	��	����
*�޸�����	��	20160104
*�޸��� 		��	�Ϻ�
*�޸�ԭ��	��	������룬���ע��
*�汾 		��	2.0
*��ʷ�汾	��	����
***********************************************************************************************/

#ifndef __STM32_ADC_H
	#define __STM32_ADC_H	
	
	#ifdef __cplusplus
	 extern "C" {
	#endif
	
			 
	#include "stm32f10x_adc.h"
	#include "stm32f10x_dma.h"
	#include "STM32_GPIO.h"
	
	#define ADC_CHANNEL_N	9	   					//	ͨ������ʹ�ö��ͨ��ʱ��Ҫ�޸Ĵ˶���
	#define ADC_CACHEL_M	10 						//	ÿ��ͨ�������������ھ�ֵ�˲�
	
	extern	uint16_t AD_Filter[];	//	ADC1-DMA��ʼ���󣬴������ֱ����
	void	ADC1_DMA_Init(void);	//	ADC1-DMA��ʼ������ʼ��֮�󼴿�ʼת��

	#ifdef __cplusplus
	 }
	#endif

#endif 
