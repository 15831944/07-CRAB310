/**
  ******************************************************************************
	*�ļ���Timer.h
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ����ʱ�����ͷ�ļ�
	*��ע��
  ******************************************************************************  
	*/ 
#ifndef _TIMER_H
#define _TIMER_H

#include <stdlib.h>			 
#include "stm32f10x.h"
#include "STM32_Priority.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Timer
{
public:
	Timer(TIM_TypeDef *tim=TIM2,int timeNum=100);
	~Timer();
	
	void start();
	void stop();
	static void start(TIM_TypeDef*);
	static void stop(TIM_TypeDef*);
	static ITStatus getITStatus(TIM_TypeDef*);
	static void clearITPendingBit(TIM_TypeDef*);
	void setPriority(uint8_t,uint8_t);					//�������ȼ�
	void setTimeOut(int);								//��ʱʱ�䳤�� ��λMS

private:
	int Tim_IRQn;										//�жϺ�
	TIM_TypeDef* TimX;       							//��ʱ���Ĵ���
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif



