/***********************************************************************************************
*�ļ���		��	STM32_Priority.c
*����		��	NVIC���顢�����ж����ȼ�
*����		��	����
*��������	��	����
*�޸�����	��	20160104
*�޸��� 		��	�Ϻ�
*�޸�ԭ��	��	������룬���ע��
*�汾 		��	2.0
*��ʷ�汾	��	����
*����1		��	setSystemPriorityGroup				//	NVIC����
*����2		��	setIRQPriority						//	�����ж����ȼ�
***********************************************************************************************/

#include "STM32_Priority.h"

/**
*	@����˵����  NVIC����
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
void	setSystemPriorityGroup(void)
{
	NVIC_PriorityGroupConfig(STM32_NVIC_PriorityGroup);
}

/**
*	@����˵����  �����ж����ȼ�
*	@������		NVIC_IRQChannel���жϺ�
				NVIC_IRQChannelPreemptionPriority����ռ���ȼ�
				NVIC_IRQChannelSubPriority����Ӧ���ȼ�
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
void	setIRQPriority(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,uint8_t NVIC_IRQChannelSubPriority)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel 	= NVIC_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


