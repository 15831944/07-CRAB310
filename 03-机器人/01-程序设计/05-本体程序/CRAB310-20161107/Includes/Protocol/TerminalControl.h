/**
  ******************************************************************************
	*�ļ���TerminalControl.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ��Xbot���ն˽������ͷ�ļ�
	*��ע��
	*
  ******************************************************************************  
  */ 
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _TERMINAL_CONTROL_H
#define _TERMINAL_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "SerialPort.h"
#include "DataChain.h"

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 
//���ڹ���ģʽ��
#define WIRE_WORK_MODE			0x01
#define WIRELESS_WORK_MODE	0x02
#define NOSIGNAL_WORK_MODE	0x00


class TerminalControl
{
public:
	TerminalControl(SerialPort *);
	virtual ~TerminalControl();
	void updateSendBuf(uint8_t * temBuf);
	void sendcommand();
	bool reciveData();
	uint8_t* getReciveData(){return reciveBuf;}
	int getSerialWorkMode(){return serialWorkMode;}
private:
	int serialWorkMode;
	SerialPort *terminalWireLessPort;		//���ߴ��ں�
	SerialPort *terminalWirePort;				//���ߴ��ں�
	RingChain *reciveChin;
	uint8_t *sendBuf; 
	uint8_t *reciveBuf;
	bool reciveData(SerialPort *);			//�������ݣ������ڻ����������ݶ�ȡ��reciveBuf

};

#endif /* _TERMINAL_CONTROL_H */


