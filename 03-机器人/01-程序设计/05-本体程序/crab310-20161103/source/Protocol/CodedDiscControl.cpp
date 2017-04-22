/**
  ******************************************************************************
	*�ļ���CodedDiscControl.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������Э�����ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 


/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "CodedDiscControl.h"

/* ���Ͷ��� --------------------------------------------------------------------*/
/* �궨��-----------------------------------------------------------------------*/

//���͵���������
static uint8_t getCodeDiscComm[6]={0xaa, 0xbb, 0x01, 0xcc, 0xcc, 0xcc};

//���캯��
CodedDiscControl::CodedDiscControl(SerialPort * p)
{
	port=p;
	cylinder=new CodeDiscData();
	angle=new CodeDiscData();
	ADCangle=0;
}

//��������
CodedDiscControl::~CodedDiscControl()
{
	delete cylinder;
	delete angle;
}
/**
  * ��  �ܣ������������ֵΪ0
  * ��  ������
  * ����ֵ����
  * 
  */
void CodedDiscControl::resetNumCounter()
{
	numCounter=0;
}
/**
  * ��  �ܣ����ô�����
  * ��  ���������
  * ����ֵ����
  * 
  */
void CodedDiscControl::setErrorFlag(uint8_t value)
{
	if(value==0&&errorFlag>0x00&&errorFlag<0x08)
		return;
	errorFlag=value;
}
/**
  * ��  �ܣ����ô����� ������������һЩ��������
  * ��  ���������
  * ����ֵ����
  * 
  */
void CodedDiscControl::setErrorFlag_1(uint8_t value)
{
	if(errorFlag<0x08)
		errorFlag=value;
}
/**
  * ��  �ܣ����Ͳ�ѯ���̽Ƕ�����
  * ��  ������
  * ����ֵ����
  * 
  */
void CodedDiscControl::sendCodeDiscCommand()				//���Ͳ�ѯ���̽Ƕ�����
{
	port->write(getCodeDiscComm,6);
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}

/**
  * ��  �ܣ�������������
  * ��  ������
  * ����ֵ�����ճɹ�֡�ı�־
	*					true:�ɹ����յ�һ֡
  * 				false:��ǰ֡û������
  */
bool CodedDiscControl::reciveData()
{
	//֡ͷ aa bb 01
	bool readFlag=false;
	static bool headFlag=false;
	static uint8_t head[3]={0,0,0};
	static uint8_t index=0;
	while (port->readAllow()&&(readFlag==false))
	{
		if(headFlag)//֡ͷ���յ�
		{
			if(index==0)
			{
				cylinder->DATA_8[1]=0;
				cylinder->DATA_8[0]=port->getChar();
			}
			else if(index==1)
				angle->DATA_8[1]=port->getChar();
			else if(index==2)
				angle->DATA_8[0]=port->getChar();
			
			index++;
			if(index>2)
			{
				readFlag=true;
				index=0;
				headFlag=false;
			}
		}
		else//֡ͷû�յ�
		{
			head[2]=head[1];
			head[1]=head[0];
			head[0]=port->getChar();
			if(head[0]==0x01&&head[1]==0xbb&&head[2]==0xaa)
			{
				headFlag=true;
			}
		}
	}
	return readFlag;
}
uint16_t CodedDiscControl::getADCAngle()
{
	ADCangle=getADCValue()&0x0fff;
	return ADCangle;
}

void CodedDiscControl::initADC()
{
	Adc1DmaInit();
	ADC_SoftwareStartConv(ADC1);
}









