/**
  ******************************************************************************
	*�ļ���main.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������������
	*��ע��
	*
  ******************************************************************************  
	*/ 
	
/* �궨��-----------------------------------------------------------------------*/ 	

#include "Process.h"

#define CLI()     __set_PRIMASK(1) 							//	�ر����ж�
#define SEI()     __set_PRIMASK(0) 							//	�����ж�

#define	__LEDSYS_PORT	GPIOA								//	ϵͳָʾ�ƶ˿�
#define	__LEDSYS_PIN	GPIO_Pin_11							//	ϵͳָʾ�����ź�
//ȫ�ֱ���
Process *process;
IoOut *ledSys;

int main(void)
{ 
	CLI();
	NVIC_PriorityGroupConfig(STM32_NVIC_PriorityGroup);		//	�ж����ȼ�����
	SysTick_Init();											//	SysTick��ʼ��
	SysTick_DelayMs(20);								
	ledSys = new IoOut(__LEDSYS_PORT,__LEDSYS_PIN);
	ledSys->setOn();
	process = new Process();
	process->openPeriph();

	SEI();
	
	while(1)
	{  	
//		SysTick_DelayMs(1000);
//		ledSys->reverseState();
	}
}

/**/
extern "C" {
	void TIM2_IRQHandler(void)
	{ 
		if (Timer::getITStatus(TIM2)!= RESET) 
		{
			Timer::clearITPendingBit(TIM2);
			Timer::stop(TIM2);
				process->runOnTime2();
			Timer::start(TIM2);
		}
	}
	void TIM3_IRQHandler(void)
	{ 
		if (Timer::getITStatus(TIM3)!= RESET) 
		{
			Timer::clearITPendingBit(TIM3);
			Timer::stop(TIM3);
				process->runOnTime3();
			Timer::start(TIM3);
		}
	}
	void TIM4_IRQHandler(void)
	{ 
		if (Timer::getITStatus(TIM4)!= RESET) 
		{
			Timer::clearITPendingBit(TIM4);
			Timer::stop(TIM4);
				process->runOnTime4();
			Timer::start(TIM4);
		}
	}

	/**
	  * @����˵����  	���жϺ�������NMI�쳣
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			��NMI���ֹ���ʱ,�쳣ָʾ��ledSys�ر�
	  */
	void NMI_Handler(void)
	{
		ledSys->setOff();
	}

	/**
	  * @����˵����  	���жϺ�������Ӳ�����쳣
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			��Ӳ�����ֹ���ʱ,�쳣ָʾ��ledSys��200�����Ƶ����˸
	  */
	void HardFault_Handler(void)
	{
		/* ������Ӳ�������쳣ʱ������ѭ�� */
	  while (1)
	  {
			SysTick_DelayMs(100);
			ledSys->reverseState();
	  }
	}

	/**
	  * @����˵����  	���жϺ��������ڴ�����쳣
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			���ڴ������ֹ���ʱ,�쳣ָʾ��ledSys��500�����Ƶ����˸
	  */
	void MemManage_Handler(void)
	{
	  /* �������ڴ�����쳣ʱ������ѭ�� */
		ledSys->setOff();
	  while (1)
	  {
			SysTick_DelayMs(500);	
			ledSys->reverseState();
	  }
	}

	/**
	  * @����˵����  	���жϺ����������߹����쳣
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			�����߳��ֹ���ʱ,�쳣ָʾ��ledSys��1���Ƶ����˸
	  */
	void BusFault_Handler(void)
	{
	  /* �����������쳣ʱ������ѭ�� */
	  while (1)
	  {
			SysTick_DelayMs(1000);	
			ledSys->reverseState();
	  }
	}

	/**
	  * @����˵����  	���жϺ�������ʹ�ù����쳣
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			��ʹ�ó��ֹ���ʱ,�쳣ָʾ��ledSys��2���Ƶ����˸
	  */
	void UsageFault_Handler(void)
	{
	  /* ������ʹ�ô����쳣ʱ������ѭ�� */
	  while (1)
	  {
			SysTick_DelayMs(2000);	
			ledSys->reverseState();
	  }
	}

	/**
	  * @����˵����  	���жϺ�������SVCcall�����쳣
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			��SVCcall���ֹ���ʱ,�쳣ָʾ��ledSysϨ��
	  */
	void SVC_Handler(void)
	{
		ledSys->setOff();
	}

	/**
	  * @����˵����  	���жϺ���������Լ��ӹ����쳣
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			�����Լ��ӳ��ֹ���ʱ,�쳣ָʾ��ledSysϨ��
	  */
	void DebugMon_Handler(void)
	{
		ledSys->setOff();
	}

	/**
	  * @����˵����  	���жϺ�������PendSVC�쳣
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			��PendSVC���ֹ���ʱ,�쳣ָʾ��ledSysϨ��
	  */
	void PendSV_Handler(void)
	{
		ledSys->setOff();
	}

	/**
	  * @����˵����  	���жϺ�������ϵͳ1msʱ��
	  * @������			��
	  * @����ֵ�� 		��
	  *	@��ע�� 			���жϲ���CLI()Ӱ�죬����ϵͳ���ж϶���û��Ӱ��
	  */
	void SysTick_Handler(void)
	{
		  
	}

}



