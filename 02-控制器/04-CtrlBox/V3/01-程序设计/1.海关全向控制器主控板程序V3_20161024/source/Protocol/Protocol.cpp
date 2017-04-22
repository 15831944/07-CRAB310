
/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "Protocol.h"

/* �궨��-----------------------------------------------------------------------*/ 



//	���캯��
Protocol::Protocol(SerialPort *comNum)
{
	com1st=comNum;
	com1st_Init();
}

//	���캯��
Protocol::Protocol(SerialPort *comNum1,SerialPort *comNum2)
{
	com1st=comNum1;
	com2nd=comNum2;
	
	com1st_Init();
	com2nd_Init();
}

//	��������
Protocol::~Protocol()					
{
	delete com1st_ReceiveChain;
	delete []com1st_SendBuf;
	delete []com1st_ReceiveBuf;
	
	delete com2nd_ReceiveChain;
	delete []com2nd_SendBuf;
	delete []com2nd_ReceiveBuf;
}

//	com1st��ʼ��
void Protocol::com1st_Init()				
{
	com1st_ReceiveChain	=	new RingChain(COMN1_RECEIVE_LENGTH);
	com1st_ReceiveBuf	=	new	uint8_t[COMN1_RECEIVE_LENGTH];
	com1st_SendBuf		=	new	uint8_t[COMN1_SEND_LENGTH];

	for(uint8_t i=0; i<COMN1_RECEIVE_LENGTH; i++)
	{
		com1st_ReceiveBuf[i] = 0;
	}
	
	for(uint8_t i=0; i<COMN1_SEND_LENGTH; i++)
	{
		com1st_SendBuf[i] = 0;
	}
}

//	com1st�������� 
void Protocol::com1st_UpdateSendBuf(uint8_t* tempData)		
{
	com1st_SendBuf[0]=COMN1_SEND_HEAD;
	com1st_SendBuf[1]=COM_PAD_ID;
	
	for(uint8_t i=0; i<COMN1_SEND_DATA_LENGTH; i++)
	{
		com1st_SendBuf[i+2] = tempData[i];
	}
	
	com1st_SendBuf[COMN1_SEND_LENGTH-1] = 0;
	for(uint8_t i=0; i< COMN1_SEND_LENGTH-1; i++)
	{
		com1st_SendBuf[COMN1_SEND_LENGTH-1] += com1st_SendBuf[i];
	}
}

//	com1st��������
void Protocol::com1st_Send()				
{
	com1st->write(com1st_SendBuf,COMN1_SEND_LENGTH);
}

//	com1st��������
bool Protocol::com1st_Receive()			
{
	uint8_t checkSum=0;
	bool readFlag=false;
	
	while (com1st->readAllow()&&(readFlag==false))
	{
		com1st_ReceiveChain->setData(com1st->getChar());
		com1st_ReceiveChain->next();
		if(com1st_ReceiveChain->getData()==COMN1_RECEIVE_HEAD)		//	���֡ͷ
		{
			checkSum+=COMN1_RECEIVE_HEAD;
			com1st_ReceiveChain->next();
			if(com1st_ReceiveChain->getData()==COM_CTR_ID)			//	���ID
			{
				
				for(uint8_t i=0;i<COMN1_RECEIVE_LENGTH-2;i++)
				{
				   checkSum+=com1st_ReceiveChain->getData();
				   com1st_ReceiveChain->next();
				}
				if(checkSum==com1st_ReceiveChain->getData())		//	���У���
				{
					for(int i=0;i<COMN1_RECEIVE_LENGTH;i++)			//	��������
					{
					   com1st_ReceiveChain->next();
					   com1st_ReceiveBuf[i]=com1st_ReceiveChain->getData();
					}
					readFlag=true;
				}
				com1st_ReceiveChain->next();
			}
			else
			{
				 com1st_ReceiveChain->previous();					//	������һ�ڵ�
			}			
		 	checkSum=0;
		}	
	}
	return 	readFlag;
}

//	��ȡcom1st���յ�������
uint8_t* Protocol::com1st_GetData()		
{
	return	com1st_ReceiveBuf;
}

//	com2nd_��ʼ��
void Protocol::com2nd_Init()				
{
	com2nd_ReceiveChain	=	new RingChain(COMN2_RECEIVE_LENGTH);
	com2nd_ReceiveBuf		=	new	uint8_t[COMN2_RECEIVE_LENGTH];
	com2nd_SendBuf		=	new	uint8_t[COMN2_SEND_LENGTH];

	for(uint8_t i=0; i<COMN2_RECEIVE_LENGTH; i++)
	{
		com2nd_ReceiveBuf[i] = 0;
	}
	
	for(uint8_t i=0; i<COMN2_SEND_LENGTH; i++)
	{
		com2nd_SendBuf[i] = 0;
	}
}

//	com2nd_�������� 
void Protocol::com2nd_UpdateSendBuf(uint8_t* tempData)		
{
	com2nd_SendBuf[0]=COMN2_SEND_HEAD;
	com2nd_SendBuf[1]=COM_BOT_ID;
	
	for(uint8_t i=0; i<COMN2_SEND_DATA_LENGTH; i++)
	{
		com2nd_SendBuf[i+2] = tempData[i];
	}
	
	com2nd_SendBuf[COMN2_SEND_LENGTH-1] = 0;
	for(uint8_t i=0; i<COMN2_SEND_LENGTH-1; i++)
	{
		com2nd_SendBuf[COMN2_SEND_LENGTH-1] += com2nd_SendBuf[i];
	}
}

//	com2nd_��������
void Protocol::com2nd_Send()				
{
	com2nd->write(com2nd_SendBuf,COMN2_SEND_LENGTH);
}

//	com2nd_��������
bool Protocol::com2nd_Receive()			
{
	uint8_t checkSum=0;
	bool readFlag=false;
	
	while (com2nd->readAllow()&&(readFlag==false))
	{
		com2nd_ReceiveChain->setData(com2nd->getChar());
		com2nd_ReceiveChain->next();
		if(com2nd_ReceiveChain->getData()==COMN2_RECEIVE_HEAD)		//	���֡ͷ
		{
			checkSum+=COMN2_RECEIVE_HEAD;
			com2nd_ReceiveChain->next();
			if(com2nd_ReceiveChain->getData()==COM_CTR_ID)	//	���ID
			{
				
				for(uint8_t i=0;i<COMN2_RECEIVE_LENGTH-2;i++)
				{
				   checkSum+=com2nd_ReceiveChain->getData();
				   com2nd_ReceiveChain->next();
				}
				if(checkSum==com2nd_ReceiveChain->getData())		//	���У���
				{
					for(int i=0;i<COMN2_RECEIVE_LENGTH;i++)		//	��������
					{
					   com2nd_ReceiveChain->next();
					   com2nd_ReceiveBuf[i]=com2nd_ReceiveChain->getData();
					}
					readFlag=true;
				}
				com2nd_ReceiveChain->next();
			}
			else
			{
				 com2nd_ReceiveChain->previous();					//	������һ�ڵ�
			}			
		 	checkSum=0;
		}	
	}
	return 	readFlag;
}

//	��ȡcom2nd_���յ�������
uint8_t* Protocol::com2nd_GetData()		
{
	return	com2nd_ReceiveBuf;
}
