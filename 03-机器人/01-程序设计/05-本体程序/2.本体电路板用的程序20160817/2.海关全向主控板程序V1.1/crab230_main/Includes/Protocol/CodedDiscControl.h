/**
  ******************************************************************************
	*�ļ���CodedDiscControl.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������Э����ͷ�ļ�
	*��ע��
	*
  ******************************************************************************  
	*/ 
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _CODED_DISC_CONTROL_H
#define _CODED_DISC_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
// #include "BaseControl.h"     //Э��Ļ���
#include "SerialPort.h"
#ifdef __cplusplus  
extern "C"
{
#endif
#include "STM32_Adc.h"
#ifdef __cplusplus  
}
#endif
/* ���Ͷ��� --------------------------------------------------------------------*/
typedef union{
        uint16_t DATA_U16;
				int16_t DATA_16;
        unsigned char DATA_8[2];
}CodeDiscData;

/* �궨��-----------------------------------------------------------------------*/ 

class CodedDiscControl
{
public:
	CodedDiscControl(SerialPort * p);
	virtual ~CodedDiscControl();

	void sendCodeDiscCommand();							//�����ٶ����� �����������ţ���������ͣ�
	bool reciveData();

	CodeDiscData * getCylinder(){return  cylinder;}
	CodeDiscData * getAngle(){return  angle;}


	void resetNumCounter();												 //���跢�ͼ�����
	void setErrorFlag(uint8_t);										 //���ô�����
	void setErrorFlag_1(uint8_t);									 //���ô�����

	void resetErrorFlag(){errorFlag=0;}		 				 //��λ������
	uint8_t getNumCounter(){return numCounter;}		 //��ȡ��������ֵ
	uint8_t getErrorFlag(){return errorFlag;}		   //��ȡ������
	uint16_t getADCAngle();
	void initADC();
private:
	SerialPort *port;
	CodeDiscData *cylinder;
	CodeDiscData *angle;
	uint8_t numCounter;		//���ͼ�����
	uint8_t errorFlag;    //������
	uint16_t ADCangle;
};
#endif  /*_CODED_DISC_CONTROL_H */


