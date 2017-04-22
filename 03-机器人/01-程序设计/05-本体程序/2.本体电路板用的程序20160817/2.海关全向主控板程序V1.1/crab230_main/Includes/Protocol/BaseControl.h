/**
  ******************************************************************************
	*�ļ���BaseControl.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������������豸��Э��Ļ����ͷ�ļ�
	*��ע��
	*
  ******************************************************************************  
	*/ 
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _BASE_CONTROL_H
#define _BASE_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "DataChain.h"
#include "SerialPort.h"

/* ���Ͷ��� --------------------------------------------------------------------*/
//�����嶨�� ��������ת��
typedef union{
        uint16_t DATA_U16;
				int16_t DATA_16;
        unsigned char DATA_8[2];
// 				char DATA_8[2];
}ctrData;
/* �궨��-----------------------------------------------------------------------*/ 
#define COMMAMD_LEN 6
#define	PORT_AMOUNT	6


class BaseControl
{
public:
	BaseControl(SerialPort *);
	virtual ~BaseControl();
	
	void setAddr(uint8_t a){addr=a;}
	void sendCommand();		//����ͺ���
	static uint8_t * getReciveData(uint8_t num){return  reciveBuf[num];}
	static bool reciveData(SerialPort *temPort);		//���ݽ��պ���

	uint8_t getNumCounter(){return numCounter;}		 //��ȡ��������ֵ
	void resetNumCounter();												 //���跢�ͼ�����
	void setErrorFlag(uint8_t);										 //���ô�����
	void setErrorFlag_1(uint8_t);									 //���ô�����
	void resetErrorFlag(){errorFlag=0;}		 				 //��λ������
	uint8_t getErrorFlag(){return errorFlag;}		   //��ȡ������

protected:
	SerialPort *port;			//���ں�

	uint8_t frameHeader;	//֡ͷ
	uint8_t addr;					//��ַ
	uint8_t command;			//������
	ctrData *data;				//���ݵĴ��湲����
	uint8_t numCounter;		//���ͼ�����
	uint8_t errorFlag;    //������
private:
	static uint8_t reciveBuf[PORT_AMOUNT][COMMAMD_LEN]; 	//���ݵĽ������� 
	static RingChain* reciveChin[PORT_AMOUNT];						//�������ݵ���ת����
	inline uint8_t subChecksum();//����У���

	
};

#endif /* _BASE_CONTROL_H */


