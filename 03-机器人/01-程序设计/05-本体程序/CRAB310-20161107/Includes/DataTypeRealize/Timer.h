/**
**********************************************************************************************************************
*
*
*
*
*
**********************************************************************************************************************
*/
#ifndef _TIMER_H
#define _TIMER_H

#ifdef __cplusplus  
extern "C"
{
#endif
	#include <stdlib.h>			 
	#include "STM32F4_PriorityControl.h"
#ifdef __cplusplus
}
#endif
#include "stm32f4xx.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Timer
{
public:
	Timer(TIM_TypeDef *);
	~Timer();
	void setTimeOut(int);					//��ʱʱ�䳤�� ��λMS
	void start();
	void stop();
	static void start(TIM_TypeDef*);
	static void stop(TIM_TypeDef*);
	static ITStatus getITStatus(TIM_TypeDef*);
	static void clearITPendingBit(TIM_TypeDef*);
	void setPriority(uint8_t,uint8_t);

private:
	int Tim_IRQn;
	uint8_t RepetitionCounter; 	//�ظ�����
	uint32_t Period;						//����
	uint16_t Prescaler;				 	//Ԥ����
	TIM_TypeDef* TimX;       		//��ʱ���Ĵ���
	uint8_t PreemptionPriority; //��ռ���ȼ�
	uint8_t SubPriority;        //��Ӧ���ȼ�

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif



