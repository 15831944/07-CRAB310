/**
  ******************************************************************************
	*�ļ���SerialPort.cpp
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2014-01-02
	*��Ҫ���������ʵ��
	*
  ******************************************************************************  
	*/
#include "SerialPort.h"	

#define PORT_1 1
#define PORT_2 2
#define PORT_3 3
#define PORT_4 4
#define PORT_5 5

//���ݲ�ͬ��CPU�ͺ�������
#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
#define ISSERIALPORT(PORT) (((PORT) == 1) || \
                                     ((PORT) == 2) || \
                                     ((PORT) == 3) || \
                                     ((PORT) == 4) || \
                                     ((PORT) == 5))
#endif

#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)
#define ISSERIALPORT(PORT) (((PORT) == 1) || \
                                     ((PORT) == 2) || \
                                     ((PORT) == 3))
#endif

#if defined(STM32F10X_LD)\
		||defined(STM32F10X_LD_VL)
#define ISSERIALPORT(PORT) (((PORT) == 1) || \
                                     ((PORT) == 2))
#endif

//���ڴ������ź�ʱ�ӵȵ����ú�

// #define USARTREMAP_1 //���忪������1��ӳ��

#ifndef USARTREMAP_1 //����1û����ӳ��

	#define USARTPORT_1 			GPIOA									//����1���ڶ˿�
	#define USARTPIN_IN_1 		GPIO_Pin_10						//����1��������
	#define USARTPIN_OUT_1 	  GPIO_Pin_9						//����1�������
	#define USARTRCCPERIPH_1 	RCC_APB2Periph_GPIOA	//����1�������ŵ�ʱ������

#else 							//����1������ӳ��

	#define USARTPORT_1 			GPIOB									//����1���ڶ˿�
	#define USARTPIN_IN_1 		GPIO_Pin_7						//����1��������
	#define USARTPIN_OUT_1 		GPIO_Pin_6						//����1�������
	#define USARTRCCPERIPH_1	RCC_APB2Periph_GPIOB	//����1�������ŵ�ʱ������
	
#endif

// #define USARTREMAP_2 //���忪������2��ӳ��

#ifndef USARTREMAP_2 //����2û����ӳ�� USART2_REMAP = 0

	#define USARTPORT_2 			GPIOA									//����2���ڶ˿�
	#define USARTPIN_IN_2 		GPIO_Pin_3						//����2��������
	#define USARTPIN_OUT_2	  GPIO_Pin_2						//����2�������
	#define USARTRCCPERIPH_2 	RCC_APB2Periph_GPIOA	//����2�������ŵ�ʱ������

#else 							//����2������ӳ�� USART2_REMAP = 1

	#define USARTPORT_2 			GPIOD									//����2���ڶ˿�
	#define USARTPIN_IN_2 		GPIO_Pin_6						//����2��������
	#define USARTPIN_OUT_2 		GPIO_Pin_5						//����2�������
	#define USARTRCCPERIPH_2	RCC_APB2Periph_GPIOD	//����2�������ŵ�ʱ������
	
#endif

//��100��144���ŷ�װ��STM32F10Xϵ�е�Ƭ���ϴ���3��������ӳ��

#define USARTREMAP_3_OFF 					//û�п�������3��ӳ��
// #define USARTREMAP_3_TO_PORTC	//������ӳ�䵽PORTC��
// #define USARTREMAP_3_TO_PORTD	//������ӳ�䵽PORTD��

#if !defined(USARTREMAP_3_OFF)&&!defined(USARTREMAP_3_TO_PORTC)&&!defined(USARTREMAP_3_TO_PORTD)
#error ����3û��ָ��ӳ������
#endif


#ifdef USARTREMAP_3_OFF //����3û����ӳ�� 

	#define USARTPORT_3 			GPIOB									//����3���ڶ˿�
	#define USARTPIN_IN_3 		GPIO_Pin_11						//����3��������
	#define USARTPIN_OUT_3	  GPIO_Pin_10						//����3�������
	#define USARTRCCPERIPH_3 	RCC_APB2Periph_GPIOB	//����3�������ŵ�ʱ������
#endif
							//����3������ӳ��
#ifdef USARTREMAP_3_TO_PORTC	//������ӳ�䵽PORTC��
	#define USARTPORT_3 			GPIOC									//����3���ڶ˿�
	#define USARTPIN_IN_3 		GPIO_Pin_11						//����3��������
	#define USARTPIN_OUT_3	  GPIO_Pin_10						//����3�������
	#define USARTRCCPERIPH_3 	RCC_APB2Periph_GPIOC	//����3�������ŵ�ʱ������
#endif

#ifdef USARTREMAP_3_TO_PORTD	//������ӳ�䵽PORTD��	
	#define USARTPORT_3 			GPIOD									//����3���ڶ˿�
	#define USARTPIN_IN_3 		GPIO_Pin_9						//����3��������
	#define USARTPIN_OUT_3	  GPIO_Pin_8						//����3�������
	#define USARTRCCPERIPH_3 	RCC_APB2Periph_GPIOD	//����3�������ŵ�ʱ������
#endif

//����4��5û����ӳ��
	#define USARTPORT_4 			GPIOC									//����4���ڶ˿�
	#define USARTPIN_IN_4 		GPIO_Pin_11						//����4��������
	#define USARTPIN_OUT_4	  GPIO_Pin_10						//����4�������
	#define USARTRCCPERIPH_4 	RCC_APB2Periph_GPIOC	//����4�������ŵ�ʱ������

	#define USARTPORT_5_IN 				GPIOD									//����5�����������ڶ˿�
	#define USARTPORT_5_OUT 			GPIOC									//����5����������ڶ˿�
	#define USARTPIN_IN_5 				GPIO_Pin_2						//����5��������
	#define USARTPIN_OUT_5	  		GPIO_Pin_12						//����5�������
	#define USARTRCCPERIPH_5_IN 	RCC_APB2Periph_GPIOD	//����5�����������ŵ�ʱ������
	#define USARTRCCPERIPH_5_OUT 	RCC_APB2Periph_GPIOC	//����5����������ŵ�ʱ������

#define USART_CR1_TXEIE_gm 	(uint16_t)(1<<7)

USART_data_t USART_data_1;
USART_data_t USART_data_2;
USART_data_t USART_data_3;
USART_data_t USART_data_4;
USART_data_t USART_data_5;
USART_data_t USART_data_6;

/**
  * ��  �ܣ�USART_data_t���캯��
  * ��  �������ڵļĴ���
  * ����ֵ����
  */
USART_data_t::USART_data_t()
{
	useRS485Flag=false;
	ctrTxPort=NULL;
	ctrTxPin=0;
	usart=NULL;
	buffer.RX_Tail = 0;
	buffer.RX_Head = 0;
	buffer.TX_Tail = 0;
	buffer.TX_Head = 0;
}

/**
  * ��  �ܣ��жϴ��ڷ��ͻ������Ƿ��пռ�
  * ��  ������
  * ����ֵ��
	* true: �������пռ䣬����д
	* false: ������û�пռ䣬������д
  */
bool USART_data_t::txBuffer_GetFreeStatus()
{
	/* Make copies to make sure that volatile access is specified. */
	uint8_t tempHead = (buffer.TX_Head + 1) & TX_BUFFER_MASK;
	uint8_t tempTail = buffer.TX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}

/**
  * ��  �ܣ��жϴ��ڻ����������Ƿ������
  * ��  ������
  * ����ֵ��
	* true: û�з�����
	* false: �������
  */
bool USART_data_t::txBuffer_SendAll()
{
	uint8_t tempHead =  buffer.TX_Head;
	uint8_t tempTail =  buffer.TX_Tail;
	return (tempHead != tempTail);
}

/**
  * ��  �ܣ��򴮿ڻ�����дһ���ֽ�
  * ��  ����
	* data  :��д�������
  * ����ֵ��
	* true: �ɹ�д��
	* false: д��ʧ��
  */
uint8_t USART_data_t::txBuffer_PutByte(uint8_t data)
{
// 	uint16_t tempCR1;
	uint8_t tempTX_Head;
	bool TXBuffer_FreeSpace;
	USART_Buffer_t * TXbufPtr;
	TXbufPtr = &buffer;
	TXBuffer_FreeSpace = txBuffer_GetFreeStatus();
	if(TXBuffer_FreeSpace)//���ڻ�����δ��
	{
	  	tempTX_Head = TXbufPtr->TX_Head;
	  	TXbufPtr->TX[tempTX_Head]= data;
		/* Advance buffer head. */
		TXbufPtr->TX_Head = (tempTX_Head + 1) & TX_BUFFER_MASK;
		/* Enable DRE interrupt.���ж� */
		USART_ITConfig(usart, USART_IT_TXE, ENABLE); //	ʹ�ܷ����ж�
	}
	return TXBuffer_FreeSpace;
}

/**
  * ��  �ܣ��жϽ��ջ������Ƿ�������
  * ��  ������
  * ����ֵ��
	* true: 	������
	* false: 	������
  */
bool USART_data_t::rxBuffer_GetAvailableStatus()
{
	/* Make copies to make sure that volatile access is specified. */
	uint8_t tempHead = buffer.RX_Head;
	uint8_t tempTail = buffer.RX_Tail;

	/* There are data left in the buffer unless Head and Tail are equal. */
	return (tempHead != tempTail);
}

/**
  * ��  �ܣ��Ӵ��ڽ��ջ�������ȡһ���ֽ�
  * ��  ������
  * ����ֵ����ȡ���ֽ�
  */
uint8_t USART_data_t::rxBuffer_GetByte()
{
	USART_Buffer_t * bufPtr;
	uint8_t ans;

	bufPtr = &buffer;
	ans = (bufPtr->RX[bufPtr->RX_Tail]);

	/* Advance buffer tail. */
	bufPtr->RX_Tail = (bufPtr->RX_Tail + 1) & RX_BUFFER_MASK;
	return ans;
}

/**
  * ��  �ܣ��Ӵ���DR�Ĵ����н���һ������д����ջ�����
  * ��  ������
  * ����ֵ��
	* true:  ���ջ�����δ��
	* false: ���ջ�������
  */
bool USART_data_t::rxComplete()
{
	USART_Buffer_t * bufPtr;
	uint8_t ans;
	uint8_t tempRX_Head;
	uint8_t tempRX_Tail;
	uint8_t data;

	bufPtr = &buffer;
	/* Advance buffer head. */
	tempRX_Head = (bufPtr->RX_Head + 1) & RX_BUFFER_MASK;

	/* Check for overflow. */
	tempRX_Tail = bufPtr->RX_Tail;
	data = usart->DR;

	if (tempRX_Head == tempRX_Tail) {
	  	ans = 0;
	}else{
		ans = 1;
		buffer.RX[buffer.RX_Head] = data;
		buffer.RX_Head = tempRX_Head;
	}
	return ans;
}

/**
  * ��  �ܣ��򴮿����ݼĴ�����д��һ������
  * ��  ������
  * ����ֵ����
  */
void USART_data_t::dataRegEmpty()
{
	USART_Buffer_t * bufPtr;
	uint8_t tempTX_Tail;
	uint16_t tempCR1;
	uint8_t data;
	bufPtr = &buffer;


	/* Check if all data is transmitted. */
	tempTX_Tail = buffer.TX_Tail;
	if (bufPtr->TX_Head == tempTX_Tail){
	    /* Disable DRE interrupts. */
		tempCR1 = usart->CR1;
		tempCR1 = (tempCR1 & ~USART_CR1_TXEIE_gm) ;
		usart->CR1 = tempCR1;

	}else{
		/* Start transmitting. */
		enableTX();
		data = bufPtr->TX[buffer.TX_Tail];
		usart->DR = data;
		/* Advance buffer tail. */
		bufPtr->TX_Tail = (bufPtr->TX_Tail + 1) & TX_BUFFER_MASK;
	}
}

/**
  * ��  �ܣ�����485����
  * ��  ������
  * ����ֵ����
  */
void USART_data_t::enableTX(void)
{
	if(!useRS485Flag)
		return;
	else//ʹ�ܷ���
		GPIO_SetBits(ctrTxPort, ctrTxPin);
}

/**
  * ��  �ܣ���ֹ485����
  * ��  ������
  * ����ֵ����
  */
void USART_data_t::disabledTX(void)
{
	if(!useRS485Flag)
		return;
	else//ʧ�ܷ���
		GPIO_ResetBits(ctrTxPort, ctrTxPin);
}

/**
  * ��  �ܣ�SerialPort��Ĺ��캯��
  * ��  ����
	* s_port�����ں�
	* s_baudrate��������
  * ����ֵ����
  */
SerialPort::SerialPort(int s_port,int s_baudrate)
{
	assert_param(ISSERIALPORT(s_port));						//���Դ����Ƿ�Ϸ� 1 2 3 4 5
	assert_param(IS_USART_BAUDRATE(s_baudrate));	//���Բ������Ƿ�Ϸ�
	port=s_port; 
	baudrate=s_baudrate;
	initUsart();//���ڳ�ʼ��
}

/**
  * ��  �ܣ�SerialPort�����������
  * ��  ����
  * ����ֵ����
  */
SerialPort::~SerialPort()
{
	close();	//stop ֹͣ����
	COM=NULL;
}

/**
  * ��  �ܣ��������ú���
  * ��  ����
	* USART_x���������üĴ���
	* Baudrate��������
	*	USART_Mode������ģʽ �緢�ͽ��յ�
  * ����ֵ����
  */
void SerialPort::usartConfig(USART_TypeDef *USART_x, uint32_t Baudrate,uint16_t USART_Mode)
{
	USART_InitTypeDef USART_InitStructure;

	//���ṹ������Ϊȱʡ״̬
  USART_StructInit(&USART_InitStructure);
	USART_InitStructure.USART_BaudRate = Baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode;

	/* Configure USART1 */
	USART_Init(USART_x, &USART_InitStructure);
}

/**
  * ��  �ܣ�����GPIO����
  * ��  ����
	* usartPort�����ں�
  * ����ֵ����
  */
void SerialPort::usartGpioInit()
{
	int temPort=port;
	close();//ʧ�ܴ���
	switch(temPort)
	{
#if defined(STM32F10X_LD)\
		||defined(STM32F10X_LD_VL)\
		||defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
		case 1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_AFIO, ENABLE);//ʹ�ܴ���ʱ��
#ifndef USARTREMAP_1	
			GPIO_PinRemapConfig(GPIO_Remap_USART1, DISABLE);	//��ֹ���ڹܽ���ӳ��
#else
			GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);		//���ڹܽ���ӳ��
#endif
			STM32_GpioOneInit(USARTPIN_IN_1, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_1);	//��������
			STM32_GpioOneInit(USARTPIN_OUT_1,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_1);				//���츴�����
			break;
		case 2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2|RCC_APB2Periph_AFIO, ENABLE);//ʹ�ܴ���ʱ��
#ifndef USARTREMAP_2	
			GPIO_PinRemapConfig(GPIO_Remap_USART2, DISABLE);	//��ֹ���ڹܽ���ӳ��
#else
			GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);		//���ڹܽ���ӳ��
#endif
			STM32_GpioOneInit(USARTPIN_IN_2, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_2);	//��������
			STM32_GpioOneInit(USARTPIN_OUT_2,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_2);				//���츴�����
			break;
#endif
#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)		
		case 3:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3|RCC_APB2Periph_AFIO, ENABLE);//ʹ�ܴ���ʱ��
#ifdef USARTREMAP_3_OFF	
			GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, DISABLE);	//��ֹ����3�Ĳ�����ӳ��
			GPIO_PinRemapConfig(GPIO_FullRemap_USART3, DISABLE);		//��ֹ����3����ȫ��ӳ��
#endif
		
#ifdef USARTREMAP_3_TOPORTC
			GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);	//��������3�Ĳ�����ӳ��
#endif
		
#ifdef USARTREMAP_3_TOPORTD
			GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);			//��������3����ȫ��ӳ��
#endif
		
			STM32_GpioOneInit(USARTPIN_IN_3, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_3);	//��������
			STM32_GpioOneInit(USARTPIN_OUT_3,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_3);				//���츴�����
			break;
#endif

#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)		
		case 4:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4|RCC_APB2Periph_AFIO, ENABLE);//ʹ�ܴ���ʱ��
			STM32_GpioOneInit(USARTPIN_IN_4, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_4);	//��������
			STM32_GpioOneInit(USARTPIN_OUT_4,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_4);				//���츴�����
			break;
		case 5:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5|RCC_APB2Periph_AFIO, ENABLE);//ʹ�ܴ���ʱ��
			STM32_GpioOneInit(USARTPIN_IN_5, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING,USARTPORT_5_IN);	//��������
			STM32_GpioOneInit(USARTPIN_OUT_5,GPIO_Speed_50MHz, GPIO_Mode_AF_PP,USARTPORT_5_OUT);				//���츴�����
			break;
#endif
	}
}
/**
  * ��  �ܣ����ô��ڵ����ȼ�
  * ��  ����
	* Preemption����ռ���ȼ�
	* Sub				����Ӧ���ȼ�
  * ����ֵ����
  */
void SerialPort::setPriority(uint8_t Preemption,uint8_t Sub)
{
	uint8_t temPreemptionPriority = Preemption;
	uint8_t temSubPriority = Sub;
	setIRQPriority(USART_IRQn,temPreemptionPriority,temSubPriority);
}

/**
  * ��  �ܣ����ڵĳ�ʼ��
  * ��  ����
  * ����ֵ����
  */
void SerialPort::initUsart()
{
	switch(port)
	{
#if defined(STM32F10X_LD)\
		||defined(STM32F10X_LD_VL)\
		||defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
		case PORT_1:
			COM=&USART_data_1;
			COM->usart=USART1;
			USART_IRQn=USART1_IRQn;
			break;
		case PORT_2:
			COM=&USART_data_2;
			COM->usart=USART2;
			USART_IRQn=USART2_IRQn;
			break;
#endif

#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)		
		case PORT_3:
			COM=&USART_data_3;
			COM->usart=USART3;
			USART_IRQn=USART3_IRQn;
			break;
#endif
		
#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)		
		case PORT_4:
			COM=&USART_data_4;
			COM->usart=UART4;
			USART_IRQn=UART4_IRQn;
			break;
		case PORT_5:
			COM=&USART_data_5;
			COM->usart=UART5;
			USART_IRQn=UART5_IRQn;
			break;
#endif
		default: //���ںŲ����Ϲ淶
// 			while(1);
			break;
	}
		usartGpioInit();
		setIRQPriority(USART_IRQn,0X00,0X00);//�������ȼ� ,Ĭ�ϵ���������ȼ�
		usartConfig(COM->usart, baudrate, USART_Mode_Tx|USART_Mode_Rx);//���ô���
		USART_ITConfig(COM->usart, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
// 		USART_ITConfig(COM->usart, USART_IT_TC, ENABLE);	//ʹ�ܷ�������ж�
}

/**
  * ��  �ܣ�����485ͨ�ŷ�ʽ�ķ��Ϳ�������
  * ��  ����
	*	port_ctrTx�������������ڵĶ˿ں�
	* pin_ctrTx �������������ڵ����ź�
  * ����ֵ����
  */
void SerialPort::setRS485CtrTx(GPIO_TypeDef* port_ctrTx,uint16_t pin_ctrTx)			//����485�������źͶ˿ڵ�
{
	COM->useRS485Flag=true;			//���ô���������485����
	COM->ctrTxPort=port_ctrTx;
	COM->ctrTxPin=pin_ctrTx;
	STM32_GpioOneInit(COM->ctrTxPin, GPIO_Speed_50MHz,GPIO_Mode_Out_PP,COM->ctrTxPort);
}

/**
  * ��  �ܣ���ȡ���ڵĶ˿ں�
  * ��  ������
  * ����ֵ���˿ں�
  */
int SerialPort::getPort()
{
	return port;
}

/**
  * ��  �ܣ��ж����ڽ��ջ������Ƿ�������
  * ��  ������
  * ����ֵ��
	*			true:������
  * 		false:������
  */
bool SerialPort::readAllow()
{
		return COM->rxBuffer_GetAvailableStatus();
}

/**
  * ��  �ܣ��Ӵ��ڻ������ж�ȡһ���ֽ�
  * ��  ������
  * ����ֵ����ȡ��ֵ
  */
uint8_t SerialPort::getChar(void)
{
	return COM->rxBuffer_GetByte();
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
	return COM->txBuffer_PutByte(data);
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
void SerialPort::open()						  //�򿪴���
{
	if(COM->usart==NULL)
		return;
	USART_Cmd(COM->usart, ENABLE);
}

/**
  * ��  �ܣ��رմ���
  * ��  ������
  * ����ֵ����
  */
void SerialPort::close()							//�رմ���
{
	if(COM->usart==NULL)
		return;
	USART_Cmd(COM->usart, DISABLE);
}




//	�����Ǵ����жϺ�����ʵ��
/**************************************ע������********************************************

*����3��4��5ֻ֧��һЩ�ض��ĵ�Ƭ�����ͣ������ú���ƶ������жϺ���������
*���⣬�����ļ����ʹ��MDK�Զ����ɵģ������е�����Target Options->c/c++->Define
*���������д��Ӧ��CPU���ͺ���������жϽ���ȥ�����
*���ڷ�����ɵ��жϲ���Ҫ�򿪣����ж��ڶ໺�淢��ʱ���б�Ҫʹ��
*USART_IT_TXE��־������Ӳ���Զ�����ģ�������USART_ClearITPendingBit(USART3,USART_IT_TXE)����
********************************************************************************************/

extern "C" {
	
/**************************** USART1 IRQHandler ********************************/
#if defined(STM32F10X_LD)\
		||defined(STM32F10X_LD_VL)\
		||defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
	
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    //	��USART_DR��һ���ֽ�
		USART_data_1.rxComplete();
  }  
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)	
  { 
		//	ͨ��дUSART_DR�Զ����USART_IT_TXE��־λ 
    //	дһ���ֽڵ�USART_DR
		USART_data_1.dataRegEmpty();
  }                          
}

/**************************** USART2 IRQHandler ********************************/
void USART2_IRQHandler(void)
{
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    //	��USART_DR��һ���ֽ�
		USART_data_2.rxComplete();  
  }  
  if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
  {   
		//	ͨ��дUSART_DR�Զ����USART_IT_TXE��־λ 
    //	дһ���ֽڵ�USART_DR
		USART_data_2.dataRegEmpty(); 
  }
}
#endif

#if defined(STM32F10X_MD)\
		||defined(STM32F10X_MD_VL)\
		||defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)
/**************************** USART3 IRQHandler ********************************/
void USART3_IRQHandler(void)
{
  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    //	��USART_DR��һ���ֽ�
		USART_data_3.rxComplete();  
  }  
  if(USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
  { 
		//	ͨ��дUSART_DR�Զ����USART_IT_TXE��־λ 
    //	дһ���ֽڵ�USART_DR
		USART_data_3.dataRegEmpty();   
  }
}
#endif


#if defined(STM32F10X_HD)\
		||defined(STM32F10X_HD_VL)\
		||defined(STM32F10X_XL)\
		||defined(STM32F10X_CL)

/**************************** USART4 IRQHandler ********************************************/
void UART4_IRQHandler(void)
{	
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
    //	��USART_DR��һ���ֽ�
		USART_data_4.rxComplete();		
  }  
  if(USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
  {
		//	ͨ��дUSART_DR�Զ����USART_IT_TXE��־λ 
    //	дһ���ֽڵ�USART_DR
 		USART_data_4.dataRegEmpty();
  }
}


/**************************** USART5 IRQHandler ********************************/
void UART5_IRQHandler(void)
{
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
  {
  	USART_ClearITPendingBit(UART5, USART_IT_RXNE);
    //	��USART_DR��һ���ֽ�
		USART_data_5.rxComplete();  
  }  
  if(USART_GetITStatus(UART5, USART_IT_TXE) != RESET)
  {  
		//	ͨ��дUSART_DR�Զ����USART_IT_TXE��־λ 
    //	дһ���ֽڵ�USART_DR
		USART_data_5.dataRegEmpty();   
  }
}
#endif
}

