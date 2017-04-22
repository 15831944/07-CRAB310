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

//���Ź�ֻ��λһ��
// #define RESET_ONE



#ifdef __cplusplus  
       extern "C" {  
#endif  
	#include "stm32f4xx.h"  
	#include "system_stm32f4xx.h"

	#include "STM32F4_PriorityControl.h"
	#include <stdlib.h>
	#include <rt_heap.h>  //_init_alloc
	#include "CrabApp.h"
	#include "WatchDag.h"
	#include "STM32F4_SysTick.h"
	#include "LEDLighter.h" 
#ifdef __cplusplus  

//  #define HEAP_SIZE   (0x3000)              //���ڴ�صĳ���3000*4=16K STM32��RAM�ܴ�С��32K
//  int32_t  heap_zone[HEAP_SIZE] = {0};       //���ڴ�����ȫ��ʼ��Ϊ0
        }  
#endif 	
#define CLI()     __set_PRIMASK(1) //�ر����ж�
#define SEI()     __set_PRIMASK(0) //�����ж�
				
CrabApp *myApp;
// WatchDag *myDag;
				
int main(void)
{ 
	//_init_alloc((int32_t)heap_zone, (int32_t)&heap_zone[HEAP_SIZE-1]); //��ʼ���ѵ���ֹ��ַ��������16K�Ŀռ�
	CLI();//�ر����ж�
	setSystemPriorityGroup();		//ϵͳ�ж����ȼ���������
	SysTick_DelayMs(5000);				//��ʱ2�룬�ȴ��豸���� 
	SysTick_DelayMs(5000);				//��ʱ2�룬�ȴ��豸���� 
// 	STM32_GpioInit();						//GPIO��ʼ��
// 	LIGHT_OFF;									//ǰ�������ƹر�
// 	POW_ON;											//��Դ����
	myApp=new CrabApp(); 				//��ʼ���û�Ӧ����
	SEI();											//�����ж�

 	myApp->openUserInterrupt();	//���û��ж�
// #ifdef RESET_ONE	
// 	if(WatchDag::getStatus()!=RESET)
// 	{
// 		WatchDag::clearFlag();
// 	}
// 	else
// 	{
// 		WatchDag::init();
// 	}	
// #else	
	//myApp->GPSPort->writeLine("Watch dog has run!\r\n");//���Կ��Ź�
// 	WatchDag::init();
// #endif
	while(1)
	{  
	}
}

