/**
  ******************************************************************************
	*�ļ���Protocol.h
	*���ߣ��Ϻ�
	*�汾��1.0
	*���ڣ�2015-05-28
	*��Ҫ������İ塢�󰴼��塢�Ұ�����ͨ��
	*��ע��
	*
  ******************************************************************************  
  */ 
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _PROTOCOL_H
	#define _PROTOCOL_H

	/* ͷ�ļ����� ------------------------------------------------------------------*/
	#include "SerialPort.h"
	#include "DataChain.h"
	#include "IoOut.h"
	
	
	#define COM_BOT_ID 					0x00
	#define COM_CTR_ID 					0x01
	#define COM_PAD_ID 					0x02
	
	#define	COMN1_485_PIN				GPIO_Pin_8
	#define	COMN1_485_PORT				GPIOA
	
	#define COMN1_SEND_LENGTH 			12
	#define COMN1_SEND_DATA_LENGTH 		COMN1_SEND_LENGTH-3
	#define COMN1_SEND_HEAD 			0xA6
	#define COMN1_RECEIVE_LENGTH 		12
	#define COMN1_RECEIVE_HEAD 			0xA7


	#define	COMN2_485_PIN				GPIO_Pin_8
	#define	COMN2_485_PORT				GPIOA
	
	#define COMN2_SEND_LENGTH 			12
	#define COMN2_SEND_DATA_LENGTH 		COMN2_SEND_LENGTH-3
	#define COMN2_SEND_HEAD 			0xA4
	#define COMN2_RECEIVE_LENGTH 		12
	#define COMN2_RECEIVE_HEAD 			0xA5

	class Protocol
	{
		public:
			Protocol(SerialPort *comNum);							//	���캯��
			Protocol(SerialPort *comNum1,SerialPort *comNum2);		//	���캯��
			~Protocol();											//	��������
			
			void		com1st_Init();								//	com1st��ʼ��
			void 		com1st_UpdateSendBuf(uint8_t* );			//	com1st�������� 
			void 		com1st_Send();								//	com1st��������
			bool 		com1st_Receive();							//	com1st��������
			uint8_t* 	com1st_GetData();							//	��ȡcom1st���յ�������
			
			void		com2nd_Init();								//	com2nd_��ʼ��
			void 		com2nd_UpdateSendBuf(uint8_t* );			//	com2nd_�������� 
			void 		com2nd_Send();								//	com2nd_��������
			bool 		com2nd_Receive();							//	com2nd_��������
			uint8_t* 	com2nd_GetData();							//	��ȡcom2nd_���յ�������
		
			SerialPort 	*com1st;									//	com1st�˿�
			SerialPort 	*com2nd;									//	com2nd_�˿�
		private:
			
			uint8_t		*com1st_SendBuf;							//	com1st��������
			uint8_t		*com1st_ReceiveBuf;							//	com1st��������
			RingChain 	*com1st_ReceiveChain;						//	com1st������������					
			
			uint8_t		*com2nd_SendBuf;							//	com2nd_��������
			uint8_t		*com2nd_ReceiveBuf;							//	com2nd_��������
			RingChain 	*com2nd_ReceiveChain;						//	com2nd_������������		
	};

#endif

