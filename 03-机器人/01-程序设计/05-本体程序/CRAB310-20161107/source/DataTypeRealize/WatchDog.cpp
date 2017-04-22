/**
  ******************************************************************************
	*�ļ���WatchDag.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ���������Ź����ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 
	
#include "WatchDag.h"
WatchDag::WatchDag()
{
// 	/*ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����*/
// 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
// 	/*����IWDGʱ��ΪLSI��32��Ƶ����IWDG������ʱ��=32KHz(LSI)/32=1kHz*/
// 	IWDG_SetPrescaler(IWDG_Prescaler_32);
// 	IWDG_SetReload(1000);								//����IWDG����ֵΪ349
// 	IWDG_ReloadCounter();								//����IWDG����ֵ
// 	IWDG_Enable();											//����IWDG
}
WatchDag::~WatchDag()
{

}

void WatchDag::init()
{
	/*ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����*/
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	/*����IWDGʱ��ΪLSI��32��Ƶ����IWDG������ʱ��=32KHz(LSI)/32=1kHz*/
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	IWDG_SetReload(2000);								//����IWDG����ֵΪ2��
	IWDG_ReloadCounter();								//����IWDG����ֵ
	IWDG_Enable();											//����IWDG
}
void WatchDag::feedDog()							//��������IWDG
{
	IWDG_ReloadCounter();								//����IWDG����ֵ
}
bool WatchDag::getStatus()
{
	return RCC_GetFlagStatus(RCC_FLAG_IWDGRST);
}














































