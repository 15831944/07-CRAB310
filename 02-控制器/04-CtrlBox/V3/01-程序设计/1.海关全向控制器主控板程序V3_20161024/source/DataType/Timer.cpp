/**
  ******************************************************************************
	*�ļ���Timer.c
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ����ʱ�����ʵ��
  ******************************************************************************  
	*/ 
#include "Timer.h"

//�ж�TIM�ж��Ƿ���ڵĺ�
#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
#define ENABLE_TIM4
#endif

#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
#define ENABLE_TIM5
#define ENABLE_TIM6
#endif

#if defined(STM32F10X_LD_VL)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
#define ENABLE_TIM7
#endif

#if defined(STM32F10X_HD_VL)
#define ENABLE_TIM12
#define ENABLE_TIM13
#define ENABLE_TIM14
#endif

//��ʱ��ϵ�� ��ϵ����ϵͳʱ���й� ��ϵͳʱ������� �޸ĸú꣬ͬʱ�޸ĳ�Ա����setTimeOut����֤�ܹ��� TIME_COEFFICIENT ����
#define TIME_COEFFICIENT 72000

/**
  * ��  �ܣ���ʱ����Ĺ��캯��
  * ��  ����
	* 	TIMX����ʱ���Ŀ��ƼĴ���
  * ����ֵ����
  */
Timer::Timer(TIM_TypeDef *TIMX,int timeNum)//Ĭ�϶�ʱʱ��1ms ��ռ����Ӧ���ȼ���Ϊ���
{
	TimX=TIMX;
	if(TimX==TIM2)
	{
		Tim_IRQn=TIM2_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}

	else if(TimX==TIM3)
	{
		Tim_IRQn=TIM3_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if(TimX==TIM4)
	{
#ifdef ENABLE_TIM4
		Tim_IRQn=TIM4_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM5)
	{
#ifdef ENABLE_TIM5
		Tim_IRQn=TIM5_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM6)
	{
#ifdef ENABLE_TIM6
		Tim_IRQn=TIM6_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM7)
	{
#ifdef ENABLE_TIM7
		Tim_IRQn=TIM7_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
#else
		return;
#endif
	}

	else if(TimX==TIM12)
	{
#ifdef ENABLE_TIM12
		Tim_IRQn=TIM12_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM13)
	{
#ifdef ENABLE_TIM13
		Tim_IRQn=TIM13_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, ENABLE);
#else
		return;
#endif
	}
	else if(TimX==TIM14)
	{
#ifdef ENABLE_TIM14
		Tim_IRQn=TIM14_IRQn;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
#else
		return;
#endif
	}
	else
		return;

	setTimeOut(timeNum);
	setPriority(0X00,0X00);//����Ĭ�����ȼ�Ϊ���
	stop();
}

/**
  * ��  �ܣ���ʱ�������������
  * ��  ������
  * ����ֵ����
  */
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
	uint8_t temPreemptionPriority = Preemption;
	uint8_t temSubPriority = Sub;
	setIRQPriority(Tim_IRQn,temPreemptionPriority,temSubPriority);
}

/**
  * ��  �ܣ����ö�ʱ�������Ӧʱ��
  * ��  �������趨��ʱ��
  * ����ֵ����
	* ��  ע����ʱʱ�����((1+TIM_Prescaler )/74M)*(1+TIM_Period )=((1+7299)/72M)*(1+9999)=1�� 
  */
void Timer::setTimeOut(int interval_ms)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	uint8_t RepetitionCounter=0x00; 	//�ظ�����
	uint32_t Period=0x00;						//����
	uint16_t Prescaler=0x00;				 	//Ԥ����
	if(interval_ms<1)
		return;
	if(interval_ms>0&&interval_ms<5)//1-5 ms
	{
		Prescaler=224;
	}	
	else if(interval_ms>4&&interval_ms<10)//5-10 ms
	{
		Prescaler=449;
	}			
	else if(interval_ms>9&&interval_ms<50)//10-50ms
	{
		Prescaler=899;
	}		
	else if(interval_ms>49&&interval_ms<100)//50-100ms
	{
		Prescaler=1799;
	}			
	else if(interval_ms>99&&interval_ms<500)//100-500ms
	{
		Prescaler=3599;
	}			
	else if(interval_ms>499&&interval_ms<3000)//500-1000ms
	{
		Prescaler=7199;
	}
	else if(interval_ms>2999&&interval_ms<5000)//1-5s
	{
		Prescaler=14399;
	}	
	else //>5s
	{
		Prescaler=35999;
	}	
	
	Period=(TIME_COEFFICIENT*interval_ms)/(1+Prescaler)-1;

	TIM_TimeBaseStructure.TIM_Period =(uint16_t)Period;
	TIM_TimeBaseStructure.TIM_Prescaler =(uint16_t)Prescaler;
	TIM_TimeBaseStructure.TIM_ClockDivision =(uint16_t)TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =(uint16_t)TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter =(uint8_t)RepetitionCounter;

	TIM_TimeBaseInit(TimX, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TimX, TIM_FLAG_Update);						//�����ʱ���жϱ�־
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
	TIM_TypeDef *temTX=Tx;
	TIM_Cmd(temTX, ENABLE);
}

/**
  * ��  �ܣ�ֹͣ��ʱ��
  * ��  ������ʱ���ļĴ���
  * ����ֵ����
  */
void Timer::stop(TIM_TypeDef* Tx)
{
	TIM_TypeDef *temTX=Tx;
	TIM_Cmd(temTX, DISABLE);
}

/**
  * ��  �ܣ���ȡ��ʱ���Ĺ���״̬
  * ��  ������ʱ���ļĴ���
  * ����ֵ����
  */
ITStatus Timer::getITStatus(TIM_TypeDef* Tx)
{
	TIM_TypeDef* temTx=Tx;
	return TIM_GetITStatus(temTx, TIM_IT_Update);
}

/**
  * ��  �ܣ�����жϱ�־λ
  * ��  ������ʱ���ļĴ���
  * ����ֵ����
  */
void Timer::clearITPendingBit(TIM_TypeDef* Tx)
{
	TIM_TypeDef* temTx=Tx;
	TIM_ClearITPendingBit(temTx , TIM_FLAG_Update);
}

