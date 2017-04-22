/**
  ******************************************************************************
	*�ļ���SerialPort.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ���������ʵ��
	*��ע�������ǰ��װ��
	*
  ******************************************************************************  
	*/
	
#include "SerialPort.h"


//���캯��
SerialPort::SerialPort(int s_port,int s_baudrate)
{
	port=s_port;
	baudrate=s_baudrate;
	if(port==1)
	{
		COM=&USART_data_1;
		STM32_InitUsart1(baudrate);
	}

	else if(port==2)
	{
		COM=&USART_data_2;
		STM32_InitUsart2(baudrate);
	}
		
	else if(port==3)
	{
		COM=&USART_data_3;
		STM32_InitUsart3(baudrate);
	}
		
	else if(port==4)
	{
		COM=&USART_data_4;
		STM32_InitUsart4(baudrate);
	}
		
	else if(port==5)
	{
		COM=&USART_data_5;
		STM32_InitUsart5(baudrate);
	}
		
	else if(port==6)
	{
		COM=&USART_data_6;
		STM32_InitUsart6(baudrate);
	}
}

//��������
SerialPort::~SerialPort()
{
	COM=NULL;
}
int SerialPort::getPort()
{
	return port;
}


/**
  * ��  �ܣ��ж����ڻ������Ƿ�������
  * ��  ������
  * ����ֵ��
	*			true:������
  * 		false:������
  */
bool SerialPort::readAllow()
{
	return USART_RXBufferData_Available(COM);
}

/**
  * ��  �ܣ��Ӵ��ڻ������ж�ȡһ���ֽ�
  * ��  ������
  * ����ֵ����ȡ��ֵ
  */
uint8_t SerialPort::getChar(void)
{
	return USART_RXBuffer_GetByte(COM);
}

/**
  * ��  �ܣ�дһ�����ݵ����ڷ��ͻ�����
  * ��  ������д������
  * ����ֵ��
	*			true:д��ɹ�
	*			false:д��ʧ��
  */
bool SerialPort::putChar(uint8_t data)
{
	return USART_TXBuffer_PutByte(COM,data);
}

/**
  * ��  �ܣ�дһ�����ݵ����ڻ�����
  * ��  ����
	*			data�������ָ��
	*			maxSize����д�ĳ���
  * ����ֵ����
  */
void SerialPort::write(uint8_t * data, uint8_t maxSize )
{
	int i;
	for(i=0;i<maxSize;i++)
		while(!putChar(data[i]));
}

/**
  * ��  �ܣ�дһ���ַ��������ڻ�����
  * ��  ����
	*			data���ַ���ָ��
  * ����ֵ����
  */
void SerialPort::writeLine(const char* data)
{
	while(*data)
	{
		while(!putChar(*data));
		data++;
	}
}

/**
  * ��  �ܣ��򿪴���
  * ��  ������
  * ����ֵ����
  */
void SerialPort::open(void)
{
	if(port==1)
	{
		USART_Cmd(USART1, ENABLE);
	}
		
	else if(port==2)
	{
		USART_Cmd(USART2, ENABLE);
	}
		
	else if(port==3)
	{
		USART_Cmd(USART3, ENABLE);
	}
		
	else if(port==4)
	{
		USART_Cmd(UART4, ENABLE);
	}
		
	else if(port==5)
	{
		USART_Cmd(UART5, ENABLE);
	}
		
	else if(port==6)
	{
		USART_Cmd(USART6, ENABLE);
	}
}

/**
  * ��  �ܣ��رմ���
  * ��  ������
  * ����ֵ����
  */
void SerialPort::close(void)
{
	if(port==1)
	{
		USART_Cmd(USART1, DISABLE);
	}
		
	else if(port==2)
	{
		USART_Cmd(USART2, DISABLE);;
	}
		
	else if(port==3)
	{
		USART_Cmd(USART3, DISABLE);;
	}
		
	else if(port==4)
	{
		USART_Cmd(UART4, DISABLE);;
	}
		
	else if(port==5)
	{
		USART_Cmd(UART5, DISABLE);;
	}
		
	else if(port==6)
	{
		USART_Cmd(USART6, DISABLE);;
	}
}

