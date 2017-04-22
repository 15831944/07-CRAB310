/***********************************************************************************************
*�ļ���		��	STM32_SysTick.c
*����		��	SysTick��ʼ��(��ѯ��ʱ)
*����		��	����
*��������	��	����
*�޸�����	��	20160104
*�޸��� 		��	�Ϻ�
*�޸�ԭ��	��	������룬���ע��
*�汾 		��	2.0
*��ʷ�汾	��	����
*����1		��	SysTick_Init					//	SysTick ��ʼ����ֻ���ⲿ����1��
*����2		��	SysTick_DelayUs					//	SysTick us��ʱ <=798915
*����3		��	SysTick_DelayXms				//	SysTick ms��ʱ <=1864��ֻ��SysTick_DelayMs����
*����4		��	SysTick_DelayMs					//	SysTick ms��ʱ <=2^32-1
***********************************************************************************************/

#include "STM32_SysTick.h"

static uint8_t  fac_us=0;						//	us��ʱ������			   
static uint16_t fac_ms=0;						//	ms��ʱ������
static void SysTick_DelayXms(uint16_t xms);		//	ms��ʱ������ֻ��SysTick_DelayMs����

/**
*	@����˵����	SysTick��ʼ��
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 			
*/
void SysTick_Init(void)   
{ 
	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//	SYSTICK��ʱ�ӹ̶�ΪAHBʱ�ӵ�1/8
	fac_us=SystemCoreClock/8000000;				//	ÿ��us��Ҫ��systickʱ����  
	fac_ms=(uint16_t)fac_us*1000;				//	ÿ��ms��Ҫ��systickʱ����   
} 

/**
*	@����˵����	us��ʱ
*	@������		nus��Ҫ��ʱ��us������Ҫ����798915(���ֵ��2^24/fac_us@fac_us=21)
*	@����ֵ�� 	��
*	@��ע�� 		��		
*/
void SysTick_DelayUs(uint32_t nus)
{		
	uint32_t temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//	ʱ�����	  		 
	SysTick->VAL=0x00;        					//	��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//	��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//	�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//	�رռ�����
	SysTick->VAL =0X00;      					//	��ռ�����	 
}

/**
*	@����˵����	ms��ʱ��ֻ��SysTick_DelayMs����
*	@������		xms��Ҫ��ʱ��ms������Ҫ����1864��ֻ��SysTick_DelayMs����
*	@����ֵ�� 	��
*	@��ע��		�� 			
*/
static	void SysTick_DelayXms(uint16_t xms)
{	 		  	  
	uint32_t temp;

	SysTick->LOAD=(uint32_t)xms*fac_ms;			//	ʱ�����(LOADΪ24bit)
	SysTick->VAL =0x00;							//	��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//	��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//	�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//	�رռ�����
	SysTick->VAL =0X00;       					//	��ռ�����	  	    
} 

/**
*	@����˵����	ms��ʱ��ֻ��SysTick_DelayMs����
*	@������		nms��Ҫ��ʱ��ms������Ҫ����2^32-1
*	@����ֵ�� 	��
*	@��ע�� 		��		
*/
#define	DELAY_SCALE	1000						//	DELAY_SCALE���ܳ���1864
void SysTick_DelayMs(uint32_t nms)
{	
	uint32_t repeat=nms/DELAY_SCALE;															
	uint16_t remain=nms%DELAY_SCALE;
    
	while(repeat)
	{
		SysTick_DelayXms(DELAY_SCALE);
		repeat--;
	}

    if (remain)
    {
        SysTick_DelayXms(remain);
    }       
}

