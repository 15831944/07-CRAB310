/**
  ******************************************************************************
	*�ļ���OpticalBobbin.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-28
	*��Ҫ�������������豸�Ŀ���Э�����ʵ��
	*��ע��
  ******************************************************************************  
  */ 


/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "OpticalBobbin.h"

/* ���Ͷ��� --------------------------------------------------------------------*/
/* �궨��-----------------------------------------------------------------------*/ 

OpticalBobbin::OpticalBobbin(SerialPort * p):BaseControl(p)
{
	addr=0X0A;
	command=0X00;

	wireLength=0;		//�߳���ָ�������е��߳�
	speed=0;				//�Զ������̵ķ����ٶ�
	leftSpeed=0;		//�ҵ���ٶ�
	rightSpeed=0;		//�ҵ���ٶ�
	workStatus=0;		//�����̵Ŀ���״̬
}
//OtherDeviceControl����������
OpticalBobbin::~OpticalBobbin()
{
	
}

void OpticalBobbin::sendOpticalBobbinCommand()
{
	command&=0X00;
	command|=workStatus;
// 	data->DATA_16=0X00;
	data->DATA_8[0]=rightSpeed;
	data->DATA_8[1]=leftSpeed;
	sendCommand();
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}



