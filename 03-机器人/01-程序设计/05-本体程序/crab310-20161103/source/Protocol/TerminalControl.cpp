/**
  ******************************************************************************
	*�ļ���TerminalControl.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ��Xbot���ն˽�����Э����ʵ��
	*��ע�����ݳ��Ⱥͳ�ʱ�����ú���ƣ���ʱ����������200���ڣ�̫����ܻᵼ�»�����ʧȥ�źź��ܼܺ�ʱ��ֹͣ
  ******************************************************************************  
	*/ 


/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "TerminalControl.h"

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 
//����֡���Ⱥ�
#define SEND_BUF_LEN 						12
#define RECIVE_BUF_LEN 					12

//֡ͷ����
#define FRAME_HEADER 						0XA4
//֡ͷ����
#define ROBO_ADDR 						  0X00

//��ʱ����
#define WIRELESS_TIME_TICK_MAX	5000
#define WIRE_TIME_TICK_MAX			5000

//���캯��
TerminalControl::TerminalControl(SerialPort * p1)
{
	terminalWireLessPort=p1; 
	serialWorkMode=NOSIGNAL_WORK_MODE;
	reciveChin=new RingChain(RECIVE_BUF_LEN);
	sendBuf=new uint8_t[SEND_BUF_LEN];
	reciveBuf=new uint8_t[RECIVE_BUF_LEN];
	for(int i=0;i<SEND_BUF_LEN;i++)
	{
		sendBuf[i]=0;
	}
	for(int i=0;i<RECIVE_BUF_LEN;i++)
	{
		reciveBuf[i]=0;
	}	
}


//��������
TerminalControl::~TerminalControl()
{
	delete reciveChin;
	delete [] sendBuf;
	delete [] reciveBuf;
}

/**
  * ��  �ܣ��������ݵ������ն�
  * ��  ������
  * ����ֵ����
	* ��  ע: ��������߲����޷��͹��ܵĹ���ͨ�������Ӧ�ùرշ��ͣ��������
  */
void TerminalControl::sendcommand()
{
// 	if(serialWorkMode==WIRE_WORK_MODE)
// 		terminalWirePort->write(sendBuf,SEND_BUF_LEN);
// 	else// if(serialWorkMode==WIRELESS_WORK_MODE)
		terminalWireLessPort->write(sendBuf,SEND_BUF_LEN);
}

/**
  * ��  �ܣ����տ����ն˵�����
  * ��  �����������ݵĴ���
  * ����ֵ��
			true:�ɹ�����һ֡
			false:û�н��յ�һ֡����
  */
bool TerminalControl::reciveData(SerialPort *port)
{
	uint8_t checkSum=0;
	bool readFlag=false;
  //���մ�������
	while (port->readAllow()&&(readFlag==false))
	{
		reciveChin->setData(port->getChar());
		reciveChin->next();
		if(reciveChin->getData()==FRAME_HEADER)//���֡ͷ	
		{	
			checkSum+=FRAME_HEADER;
			reciveChin->next();
			if((reciveChin->getData())==ROBO_ADDR)// 
			{
				for(int i=0;i<RECIVE_BUF_LEN-2;i++)
				{
				   checkSum+=reciveChin->getData();
				   reciveChin->next();
				}
				if(checkSum==reciveChin->getData())//У�����ȷ
				{
					//�����ݴ�������
					for(int i=0;i<RECIVE_BUF_LEN;i++)
					{
					   reciveChin->next();
					   reciveBuf[i]=reciveChin->getData();
					}
					readFlag=true;
				}
				reciveChin->next();
			}
			else
			{
				 reciveChin->previous();//�����ϸ��ڵ�	
			}			
		 	checkSum=0;
		}	
	}
	return 	readFlag;
}

/**
  * ��  �ܣ����տ����ն˵����ݲ��Զ��ж������߻�������
  * ��  ������
  * ����ֵ��
			true:�ɹ�����һ֡
			false:û�н��յ�һ֡����
  */
bool TerminalControl::reciveData()
{
	bool tempFlag = false;
	static uint16_t wirelessTimeTick = 0;
	//�������ߵ�����

	//���տ����������
	tempFlag = reciveData(terminalWireLessPort);
	if(tempFlag == true)								// ���������յ�
	{
		wirelessTimeTick = 0;
		serialWorkMode =  WIRELESS_WORK_MODE;
	}
	else if (wirelessTimeTick<WIRELESS_TIME_TICK_MAX)	//����Ч����֡��ʱ��ֱ������WIRELESS_TIME_TICK_MAX��
	{
		wirelessTimeTick++;
	}
	else												//���WIRELESS_TIME_TICK_MAX������������ź�
	{
		serialWorkMode = NOSIGNAL_WORK_MODE;
	}
	return tempFlag;
}

/**
  * ��  �ܣ����·��͵�����
  * ��  �������µ�����
  * ����ֵ����
  */
void TerminalControl::updateSendBuf(uint8_t * temBuf)
{
	uint8_t checksum=0;
	for(int i=0;i<SEND_BUF_LEN-1;i++)
	{
		sendBuf[i]=temBuf[i];
		checksum +=temBuf[i];
	}
	sendBuf[SEND_BUF_LEN-1] = checksum;
}









