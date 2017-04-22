/**
  ******************************************************************************
	*�ļ���STM32F4_IRQ_INIT.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ����ʱ���жϺ�����ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 
//��ʱ������

#include "STM32F4_IRQ_INIT.H"
// #include "LEDLighter.h"

// static LEDLighter *led = new LEDLighter(GPIOC,GPIO_Pin_0);//Ĭ�ϵ���

extern "C" {
//1ms ����һ��
/******************************  TIM2_IRQHandler *************************************/
void TIM2_IRQHandler(void)
{ 
// 	static int index=0;
	if (Timer::getITStatus(TIM2)!= RESET) 
	{
		Timer::clearITPendingBit(TIM2);
		Timer::stop(TIM2);	
		myApp->runOnTime2();
		Timer::start(TIM2);
	}
}

//10ms����һ��
/******************************  TIM3_IRQHandler *************************************/
void TIM3_IRQHandler(void)
{
	if (Timer::getITStatus(TIM3)!= RESET)
	{ 
		Timer::clearITPendingBit(TIM3);
		Timer::stop(TIM3);
		myApp->runOnTime3();
		Timer::start(TIM3);
	}
 
}

//100ms����һ��
/******************************  TIM4_IRQHandler *************************************/

void TIM4_IRQHandler(void)
{
	if (Timer::getITStatus(TIM4)!= RESET)
	{
		Timer::clearITPendingBit(TIM4);
		Timer::stop(TIM4);
		myApp->runOnTime4();
// 		WatchDag::feedDog();	//ι�� ÿ100MSι��һ�� ��ʱֵΪ2000����
		Timer::start(TIM4);
	}	
}

}

