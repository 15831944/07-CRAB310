/***********************************************************************************************
*�ļ���		��	STM32_SysTick.h
*����		��	SysTick��ʼ����us��ms��ʱ��������
*����		��	����
*��������	��	����
*�޸�����	��	20160104
*�޸��� 		��	�Ϻ�
*�޸�ԭ��	��	������룬���ע��
*�汾 		��	2.0
*��ʷ�汾	��	����
***********************************************************************************************/

#ifndef __STM32_SYSTICK_H
	#define __STM32_SYSTICK_H
	#ifdef __cplusplus
		extern "C" {
	#endif
			
	#include "stm32f10x.h"

	void SysTick_Init(void); 				//	SysTick��ʼ��
	void SysTick_DelayUs(uint32_t nus);		//	us��ʱ
	void SysTick_DelayMs(uint32_t nms);		//	ms��ʱ

	#ifdef __cplusplus
		}
	#endif
#endif

