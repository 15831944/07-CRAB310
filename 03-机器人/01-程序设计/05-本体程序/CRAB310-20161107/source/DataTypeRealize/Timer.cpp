/**
  ******************************************************************************
	*�ļ���Timer.c
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ����ʱ�����ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 
	
#include "Timer.h"
//��ʱ��ϵ�� ��ϵ����ϵͳʱ���й� ��ϵͳʱ������� �޸ĸú꣬ͬʱ�޸ĳ�Ա����setTimeOut����֤�ܹ��� TIME_COEFFICIENT ����
#define TIME_COEFFICIENT 84000


//���캯��
Timer::Timer(TIM_TypeDef *TIMX)//Ĭ�϶�ʱʱ��1ms ��ռ����Ӧ���ȼ���Ϊ���
{
	TimX=TIMX;
	if(TimX==TIM2)
	{
		Tim_IRQn=TIM2_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);///////////���//////////////
	}

	else if(TimX==TIM3)
	{
		Tim_IRQn=TIM3_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);///////////���//////////////
	}
	else if(TimX==TIM4)
	{
		Tim_IRQn=TIM4_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);///////////���//////////////
	}
	else if(TimX==TIM5)
	{
		Tim_IRQn=TIM5_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);///////////���//////////////
	}
	else if(TimX==TIM7)
	{
		Tim_IRQn=TIM7_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);///////////���//////////////
	}
// 	else if(TimX==TIM12)
// 	{
// 		Tim_IRQn=TIM12_IRQn;
// 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);///////////���//////////////
// 	}
// 	else if(TimX==TIM13)
// 	{
// 		Tim_IRQn=TIM13_IRQn;
// 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);///////////���//////////////
// 	}
// 	else if(TimX==TIM14)
// 	{
// 		Tim_IRQn=TIM14_IRQn;
// 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);///////////���//////////////
// 	}
// 	
	setPriority(0X00,0X00);
	RepetitionCounter=0x00;
	setTimeOut(1);

// 	PreemptionPriority=0X00;
// 	SubPriority=0X00;
	stop();

}

//��������
Timer::~Timer()
{
	stop();
	delete TimX;
}

/**
  * ��  �ܣ����ö�ʱ�������ȼ�
  * ��  ����
	*			Preemption����ռ���ȼ�
	*			Sub				����Ӧ���ȼ�
  * ����ֵ����
  */
void Timer::setPriority(uint8_t Preemption,uint8_t Sub)
{
	PreemptionPriority = Preemption;
	SubPriority = Sub;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = Tim_IRQn;////////////////////////////////
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
}


//��ʱʱ�����
//((1+TIM_Prescaler )/84M)*(1+TIM_Period )=((1+8399)/84M)*(1+9999)=1�� */
//
/**
  * ��  �ܣ����ö�ʱ�������Ӧʱ��
  * ��  �������趨��ʱ��
  * ����ֵ����
  */
void Timer::setTimeOut(int interval_ms)
{
	if(interval_ms<1)
		return;
	if(interval_ms>0&&interval_ms<5)//1-5 ms
	{
		Prescaler=399;
	}	
	else if(interval_ms>4&&interval_ms<10)//5-10 ms
	{
		Prescaler=799;
	}			
	else if(interval_ms>9&&interval_ms<50)//10-50ms
	{
		Prescaler=1499;
	}		
	else if(interval_ms>49&&interval_ms<100)//50-100ms
	{
		Prescaler=2399;
	}			
	else if(interval_ms>99&&interval_ms<500)//100-500ms
	{
		Prescaler=4199;
	}			
	else if(interval_ms>499&&interval_ms<3000)//500-1000ms
	{
		Prescaler=8399;
	}
	else if(interval_ms>2999&&interval_ms<5000)//1-5s
	{
		Prescaler=16799;
	}	
	else //>5s
	{
		Prescaler=41999;
	}	
	Period=(TIME_COEFFICIENT*interval_ms)/(1+Prescaler)-1;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = Period;
	TIM_TimeBaseStructure.TIM_Prescaler = Prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = RepetitionCounter;
 	TIM_TimeBaseInit(TimX, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TimX, TIM_FLAG_Update);
	TIM_ITConfig(TimX, TIM_IT_Update, ENABLE);		
}

/**
  * ��  �ܣ��򿪶�ʱ��
  * ��  ������
  * ����ֵ����
  */
void Timer::start()
{
	TIM_Cmd(TimX, ENABLE);
}

/**
  * ��  �ܣ�ֹͣ��ʱ��
  * ��  ������
  * ����ֵ����
  */
void Timer::stop()
{
	TIM_Cmd(TimX, DISABLE);
}

/**
  * ��  �ܣ��򿪶�ʱ��
  * ��  ������ʱ���ļĴ���
  * ����ֵ����
  */
void Timer::start(TIM_TypeDef* Tx)
{
	TIM_Cmd(Tx, ENABLE);
}

/**
  * ��  �ܣ�ֹͣ��ʱ��
  * ��  ������ʱ���ļĴ���
  * ����ֵ����
  */
void Timer::stop(TIM_TypeDef* Tx)
{
	TIM_Cmd(Tx, DISABLE);
}

/**
  * ��  �ܣ���ȡ��ʱ���Ĺ���״̬
  * ��  ������ʱ���ļĴ���
  * ����ֵ����
  */
ITStatus Timer::getITStatus(TIM_TypeDef* Tx)
{
	return TIM_GetITStatus(Tx, TIM_IT_Update);
}

/**
  * ��  �ܣ���ն�ʱ����״̬
  * ��  ������ʱ���ļĴ���
  * ����ֵ����
  */
void Timer::clearITPendingBit(TIM_TypeDef* Tx)
{
	TIM_ClearITPendingBit(Tx , TIM_FLAG_Update);
}

