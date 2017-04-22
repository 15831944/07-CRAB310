/**
  ******************************************************************************
	*�ļ���BaseControl.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������������豸��Э��Ļ����ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 
	
	
/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "BaseControl.h"

/* ���Ͷ��� --------------------------------------------------------------------*/
/* �궨��-----------------------------------------------------------------------*/ 

//��������
uint8_t BaseControl::reciveBuf[PORT_AMOUNT][COMMAMD_LEN] ={0x00}; //�����ڴ浽ջ

//��������
RingChain* BaseControl::reciveChin[]={new RingChain(COMMAMD_LEN),new RingChain(COMMAMD_LEN),\
																			new RingChain(COMMAMD_LEN),new RingChain(COMMAMD_LEN),\
																			new RingChain(COMMAMD_LEN),new RingChain(COMMAMD_LEN)};
//���캯��
BaseControl::BaseControl(SerialPort *temPort)
{
	port=temPort;
	data=new ctrData();
	frameHeader=0XA4;
	addr=0X00;
	command=0X00;
	data->DATA_8[0]=0X00;
	data->DATA_8[1]=0X00;
	numCounter=0;
	errorFlag=0;
}

//��������
BaseControl::~BaseControl()
{
	for(int i=0;i<PORT_AMOUNT;i++)
		delete reciveChin[i];
	delete data;
}

/**
  * ��  �ܣ���������
  * ��  ������
  * ����ֵ����
  * 
  */
void BaseControl::sendCommand()
{
	while(!port->putChar(frameHeader));
	while(!port->putChar(addr));
	while(!port->putChar(command));
	while(!port->putChar(data->DATA_8[1]));//�ȷ���λ
	while(!port->putChar(data->DATA_8[0]));//�󷢵�λ
	while(!port->putChar(subChecksum()));
}
/**
  * ��  �ܣ������������ֵΪ0
  * ��  ������
  * ����ֵ����
  * 
  */
void BaseControl::resetNumCounter()
{
	numCounter=0;
}
/**
  * ��  �ܣ����ô�����
  * ��  ���������
  * ����ֵ����
  * 
  */
void BaseControl::setErrorFlag(uint8_t value)
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
void BaseControl::setErrorFlag_1(uint8_t value)
{
	if(errorFlag<0x08)
		errorFlag=value;
}
/**
  * ��  �ܣ����պ���
  * ��  �������յĴ��ں�
  * ����ֵ����
  * 
  */
bool BaseControl::reciveData(SerialPort *temPort)
{
	uint8_t checkSum=0;
	bool readFlag=false;
	uint8_t arrayNum=temPort->getPort()-1;
	while (temPort->readAllow()&&(readFlag==false))
	{
		BaseControl::reciveChin[arrayNum]->setData(temPort->getChar());
		BaseControl::reciveChin[arrayNum]->next();
		if(reciveChin[arrayNum]->getData()==0XA4)//���֡ͷ	
		{	
			checkSum+=0XA4;
			reciveChin[arrayNum]->next();
			
			checkSum+=reciveChin[arrayNum]->getData();//��ַ
			reciveChin[arrayNum]->next();
			
			if((reciveChin[arrayNum]->getData()&0X40)==0x40)//����λ��ȷ
			{
				for(int i=0;i<COMMAMD_LEN-3;i++)
				{
				   checkSum+=reciveChin[arrayNum]->getData();
				   reciveChin[arrayNum]->next();
				}
				if(checkSum==reciveChin[arrayNum]->getData())//У�����ȷ
				{
					//�����ݴ�������
					for(int i=0;i<COMMAMD_LEN;i++)
					{
					   reciveChin[arrayNum]->next();
					   reciveBuf[arrayNum][i]=reciveChin[arrayNum]->getData();
					}
					readFlag=true;
				}
				reciveChin[arrayNum]->next();
			}
			else
			{
				reciveChin[arrayNum]->previous();//�����ϸ��ڵ�	
				reciveChin[arrayNum]->previous();//�����ϸ��ڵ�	
			}			
		 	checkSum=0;
		}
	}
	return 	readFlag;
}

/**
  * ��  �ܣ�����У���
  * ��  ������
  * ����ֵ����
  * 
  */
uint8_t BaseControl::subChecksum()
{
	uint8_t checksum=0;
	checksum+=frameHeader;
	checksum+=addr;
	checksum+=command;
	checksum+=data->DATA_8[1];
	checksum+=data->DATA_8[0];
	return checksum;
}






