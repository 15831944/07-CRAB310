
/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "Process.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include <stdlib.h>
#ifdef __cplusplus
 }
#endif
 
/* ���ʵ��--------------------------------------------------------------------*/
 
/**
  * @brief  TIM2��ʱ���жϺ���
  * @param  None
  * @retval None
  */
void Process::runOnTime2(void)
{
	getJoyStickValue();													//	��ȡҡ������
	getBatValue();														//	��ȡ��ص�ѹ
	getAdKeyValue();													//	��ȡAD����ֵ
	
	if(protocol->com2nd_Receive())										//	���մ�������
	{
		dealBotData();													//	��������		
	}
}

/**
  * @brief  TIM3��ʱ���жϺ���,���µ���ֵ���Դ��ѹ
  * @param  None
  * @retval None
  */
void Process::runOnTime3(void)
{	
	setCtrData();														//	���ÿ�������
	setPowerLed();														//	���õ�����ʾ
	
	setCom1Data();	
	
	protocol->com1st_UpdateSendBuf(com1st_DataToSend);	
	if(protocol->com1st_Receive())										//	���յ�pad����֮���ٷ���
	{
//		testLed->reverseState();
		dealPadData();													//	��������	
	}
	if(ctrFlag_PadInsert)												//	����pad�ŷ�����
	{
		protocol->com1st_Send();										//	��������	
	}
}

/**
  * @brief  TIM4��ʱ���жϺ�����TIM4��������δʹ��
  * @param  None
  * @retval None
  */
void Process::runOnTime4(void)
{
//	if (ctrChannel==botChannel)
//	{
//		setCom2Data();
//		protocol->com2nd_UpdateSendBuf(com2nd_DataToSend);
//		protocol->com2nd_Send();											//	com2nd��������
//	}		
//	else//	if (ctrChannel!=botChannel)	//	���ÿ�����ͨ��
//	{
//		setChannel(botChannel);
//		setChannel(botChannel);
//		ctrChannel=botChannel;
//	}
//	testWithUsart();													//	���Դ��룬�鿴AD��ֵ
	setCom2Data();
	protocol->com2nd_UpdateSendBuf(com2nd_DataToSend);
	protocol->com2nd_Send();											//	com2nd��������
	ctrChannel=botChannel;
}


/**
  * @brief  ��ȡ��������
  * @param  None
  * @retval None	
  */
#define	POWER_OFF_COUNT_DOWN			100							//	�ػ���ʱ,5s�Ժ��Զ��ػ�
#define	POWER_OFF_HARD_WARE_COUNT_DOWN	80							//	ǿ�ƹػ���ʱ
void Process::setCtrData()
{
	static 	bool	preLeftAdKey[LEFT_AD_KEY_NUM]		={false,false,false,false};
	static 	bool	preRightAdKey[RIGHT_AD_KEY_NUM]		={false,false,false,false};
	static 	bool	finalRightAdKey[RIGHT_AD_KEY_NUM]	={false,false,false,false};	
	static 	uint8_t finalVedioSwitch=0x01;							//	��Ƶ�л�
	static 	uint8_t finalSpeed=0x01;									//	�ٶȵ���
//	static 	uint16_t	trigAutoCount=0;								//	�����Զ�ģʽ��ʱ
	static	uint8_t	powerOffHardWareCountDown=0;					//
	static	uint8_t	padOffDelayCount=0;								//	pad�ػ���ʱ
	static	uint8_t	padInsertCount=0;								//	pad�����ʱ
	
	//	����Զ��/����
	ctrBotData1&=~0x03;												//	����bit1~0							
	if(leftAdKey[LEFT1])											//	Զ��
	{
		ctrBotData1|=0x01;
	}
	else if (leftAdKey[LEFT2])										//	����
	{
		ctrBotData1|=0x01<<1;
	}

	//	�����ٶȵ�λ	
	if (preLeftAdKey[LEFT3]!=leftAdKey[LEFT3])						//	��3����-�ٶ�+��ÿ��1���ٶ�+1
	{
		preLeftAdKey[LEFT3]=leftAdKey[LEFT3];
		if (leftAdKey[LEFT3]==false&&finalSpeed<0x03)				//	�ٶ����3			
			finalSpeed++;
	}
	if (preLeftAdKey[LEFT4]!=leftAdKey[LEFT4])						//	��4����-�ٶ�-��ÿ��1���ٶ�-1
	{
		preLeftAdKey[LEFT4]=leftAdKey[LEFT4];
		if (leftAdKey[LEFT4]==false&&finalSpeed>0x00)				//	�ٶ���С0			
			finalSpeed--;
	}
	
//	finalSpeed=2;
	
	ctrBotData1	&=~(0x03<<4);										//	����bit5~4
	ctrBotData1	|=finalSpeed<<4;									//	���ñ�������
	ctrStatus2	&=~(0x03<<6);										//	����bit7~6
	ctrStatus2	|=finalSpeed<<6;									//	����pad����
	
	//	�����Զ�ģʽ	�����������ϡ�
//	if (0X7A>=ctrLeftX||ctrLeftX>=0X85||0X7A>=ctrLeftY||ctrLeftY>=0X85)		//	����˶�ҡ�˶������˳��Զ�ģʽ
//	{
//		ctrFlag_Auto=false;
//	}
//	if (botMode==0x02)												//	�Զ�ģʽ��ɺ���˳��Զ�ģʽ
//	{
//		ctrFlag_Auto=false;										
//	}
//	if (rightAdKey[RIGHT1])											//	��1������������1s�����Զ�ģʽ
//	{	
//		trigAutoCount++;
//		if(trigAutoCount>=(1000/TIM3_DELAY_TIME))
//		{
//			ctrFlag_Auto=true;
//			trigAutoCount=0;
//		}
//	}
//	else
//	{
//		trigAutoCount=0;
//	}
	
	if (rightAdKey[RIGHT1])											//	��1������������1s�����Զ�ģʽ
	{	
		ctrFlag_Auto=true;
	}
	else
	{
		ctrFlag_Auto=false;
	}
	ctrBotData2&=~(0x03<<4);
	if (ctrFlag_Auto)
		ctrBotData2|=0x01<<4;
		
	//	���û����л�	
	if (preRightAdKey[RIGHT2]!=rightAdKey[RIGHT2])					//	��2����-��Ƶ�л�
	{
		preRightAdKey[RIGHT2]=rightAdKey[RIGHT2];
		if (rightAdKey[RIGHT2]==false)
			finalVedioSwitch++;
	}
	if(finalVedioSwitch>3)
		finalVedioSwitch=1;
	
	ctrBotData1&=~(0x03<<2);										//	����bit3~2
	ctrBotData1|=finalVedioSwitch<<2;
	ctrStatus2&=~(0x03<<4);											//	����bit5~4
	ctrStatus2|=finalVedioSwitch<<4;
	
	//	�����г���
	
	if (preRightAdKey[RIGHT3]!=rightAdKey[RIGHT3])					//	��3����-�г���
	{
		preRightAdKey[RIGHT3]=rightAdKey[RIGHT3];
		if (rightAdKey[RIGHT3]==false)
		{
			finalRightAdKey[RIGHT3]=!finalRightAdKey[RIGHT3];
			if (finalRightAdKey[RIGHT3])
			{
				ctrBotData1&=~(0x01<<7);										//	����bit7
				ctrBotData1|=0x01<<7;
			}
			else
			{
				ctrBotData1&=~(0x01<<7);										//	����bit7
			}
		}
	}
	
	//	���ù۲��
	
	if (preRightAdKey[RIGHT4]!=rightAdKey[RIGHT4])					//	��4����-�۲��
	{
		preRightAdKey[RIGHT4]=rightAdKey[RIGHT4];
		if (rightAdKey[RIGHT4]==false)
		{
			finalRightAdKey[RIGHT4]=!finalRightAdKey[RIGHT4];
			if (finalRightAdKey[RIGHT4])
			{
				ctrBotData1&=~(0x01<<6);										//	����bit6
				ctrBotData1|=0x01<<6;
			}
			else
			{
				ctrBotData1&=~(0x01<<6);										//	����bit6
			}
		}
	}
	
	//	����״̬��pad
	ctrStatus1=0x00;
	ctrStatus1|=botMode<<6;
	ctrStatus1|=botIR<<4;
	ctrStatus1|=ctrChannel;
	//	���ñ���ͨ��
	ctrBotData2&=0xF0;							//	����bit3~0	
	ctrBotData2|=padChannel;
	
	//	���pad�Ƿ����
	if (AD_Filter[PADTEST]<=0X200&&!ctrFlag_PadInsert)	//�����AD��⵽�ӵ�
	{
		padInsertCount++;
		if(padInsertCount>=20)
		{
			ctrFlag_PadInsert=true;
			padInsertCount=0;
		}
	}
	else if (AD_Filter[PADTEST]>=0X200)
	{
		padInsertCount=0;
		ctrFlag_PadInsert=false;
	}
//	if(ctrFlag_PadInsert)
//		vbtCtr->setOn();
//	else
//		vbtCtr->setOff();
	vbtCtr->setOn();
	//	���ùػ�
	if (AD_Filter[NUM_KEY_POWER]<=0X200)
		ctrFlag_PowerOn=1;
	if(AD_Filter[NUM_KEY_POWER]>=0X240&&ctrFlag_PowerOn==1)
	{
		ctrData1&=~(0x03<<6);
		ctrData1|=0x01<<6;
		if(powerOffHardWareCountDown<POWER_OFF_HARD_WARE_COUNT_DOWN)
			powerOffHardWareCountDown++;
		else
		{
			ctrFlag_PowerLedOff=true;
			setPowerState(false);	//�ػ�
		}
		
	}
	if(padOffState)
	{
		padOffDelayCount++;
		if(padOffDelayCount>=POWER_OFF_COUNT_DOWN)
		{
			ctrFlag_PowerLedOff=true;
			setPowerState(false);	//�ػ�
		}
	}
}

/**
  * @brief  ����Pad����
  * @param  None
  * @retval None
  */
void Process::dealPadData(void)
{
	uint8_t	*dataFromPad;
	uint8_t	tempPadOffState=0;
	
	dataFromPad 	= protocol->com1st_GetData();
	tempPadOffState	= dataFromPad[3]&0x03;			//	bit 1~0;
	padChannel		= dataFromPad[4]&0x0F;			//	bit 3~0;
	
	if(tempPadOffState!=0x00)
		padOffState=true;
}

/**
  * @brief  ����������
  * @param  None
  * @retval None
  */
void Process::dealBotData(void)
{
	uint8_t	*dataFromBot;
	dataFromBot		= protocol->com2nd_GetData();
	botLeftBatVal	= dataFromBot[3];			//	bit 7~0;
	botRightBatVal	= dataFromBot[4];			//	bit 7~0;
	botAngle		= dataFromBot[5];
	botMode			= (dataFromBot[6]&(0x03<<6))>>6;
	botIR			= (dataFromBot[6]&(0x03<<4))>>4;
	botChannel		= dataFromBot[6]&0x0F;
}
/**
  * @brief  ����com1st��Ҫ���͵�����
  * @param  None
  * @retval None
  */
void Process::setCom1Data(void)
{
	com1st_DataToSend[0] = 0x80;
	com1st_DataToSend[1] = ctrData1;
	com1st_DataToSend[2] = ctrBatVal;
	com1st_DataToSend[3] = botLeftBatVal;
	com1st_DataToSend[4] = botRightBatVal;
	com1st_DataToSend[5] = botAngle;
	com1st_DataToSend[6] = ctrStatus1;
	com1st_DataToSend[7] = ctrStatus2;
	com1st_DataToSend[8] = 0x00;
}

/**
  * @brief  ����com2nd��Ҫ���͵�����
  * @param  None
  * @retval None
  */
void Process::setCom2Data(void)
{
	com2nd_DataToSend[0] = 0x80;
	com2nd_DataToSend[1] = ctrLeftX;
	com2nd_DataToSend[2] = ctrLeftY;
	com2nd_DataToSend[3] = ctrRightX;
	com2nd_DataToSend[4] = ctrRightY;
//	com2nd_DataToSend[1] = 0x80;
//	com2nd_DataToSend[2] = 0;
//	com2nd_DataToSend[3] = 0x80;
//	com2nd_DataToSend[4] = 0x80;
	com2nd_DataToSend[5] = ctrBotData1;
	com2nd_DataToSend[6] = ctrBotData2;
	com2nd_DataToSend[7] = 0x00;
	com2nd_DataToSend[8] = 0x00;
}

/**
  * @brief  ��ȡҡ�����ݣ�����ҡ�˱����ǹ�Թ�������˴���Ҫ����������
  * @param  None
  * @retval None
  */
#define MIN_JOY_VALUE		0x20
#define	MIN_MIDDLE_VALUE	0x7A
#define	MAX_MIDDLE_VALUE	0x85
#define MAX_JOY_VALUE		0xE0
void Process::getJoyStickValue()
{	
	uint16_t tempLX, tempLY, tempRX, tempRY;
	
	tempLX	= AD_Filter[NUM_ctrLeftX]>>4;
	tempLY	= AD_Filter[NUM_ctrLeftY]>>4;
	tempRX	= AD_Filter[NUM_ctrRightX]>>4;
	tempRY	= AD_Filter[NUM_ctrRightY]>>4;
	
	if (tempLX<=MIN_JOY_VALUE)
	{
		tempLX=0;
	}
	else if(tempLX<=MIN_MIDDLE_VALUE)
	{
		tempLX 	= (tempLX-MIN_JOY_VALUE)*0x080/(MIN_MIDDLE_VALUE-MIN_JOY_VALUE);
	}
	else if (tempLX<=MAX_MIDDLE_VALUE)
	{
		tempLX=0x80;
	}
	else if(tempLX<=MAX_JOY_VALUE)
	{
		tempLX	= (tempLX-MAX_MIDDLE_VALUE)*0x080/(MAX_JOY_VALUE-MAX_MIDDLE_VALUE)+0x80;
	}
	else
	{
		tempLX = 0xFF;
	}
	
	
	
	if (tempLY<=MIN_JOY_VALUE)
	{
		tempLY=0;
	}
	else if(tempLY<=MIN_MIDDLE_VALUE)
	{
		tempLY 	= (tempLY-MIN_JOY_VALUE)*0x080/(MIN_MIDDLE_VALUE-MIN_JOY_VALUE);
	}
	else if (tempLY<=MAX_MIDDLE_VALUE)
	{
		tempLY=0x80;
	}
	else if(tempLY<=MAX_JOY_VALUE)
	{
		tempLY	= (tempLY-MAX_MIDDLE_VALUE)*0x080/(MAX_JOY_VALUE-MAX_MIDDLE_VALUE)+0x80;
	}
	else
	{
		tempLY = 0xFF;
	}
	
	if (tempRX<=MIN_JOY_VALUE)
	{
		tempRX=0;
	}
	else if(tempRX<=MIN_MIDDLE_VALUE)
	{
		tempRX 	= (tempRX-MIN_JOY_VALUE)*0x080/(MIN_MIDDLE_VALUE-MIN_JOY_VALUE);
	}
	else if (tempRX<=MAX_MIDDLE_VALUE)
	{
		tempRX=0x80;
	}
	else if(tempRX<=MAX_JOY_VALUE)
	{
		tempRX	= (tempRX-MAX_MIDDLE_VALUE)*0x080/(MAX_JOY_VALUE-MAX_MIDDLE_VALUE)+0x80;
	}
	else
	{
		tempRX = 0xFF;
	}
	
	if (tempRY<=MIN_JOY_VALUE)
	{
		tempRY=0;
	}
	else if(tempRY<=MIN_MIDDLE_VALUE)
	{
		tempRY 	= (tempRY-MIN_JOY_VALUE)*0x080/(MIN_MIDDLE_VALUE-MIN_JOY_VALUE);
	}
	else if (tempRY<=MAX_MIDDLE_VALUE)
	{
		tempRY=0x80;
	}
	else if(tempRY<=MAX_JOY_VALUE)
	{
		tempRY	= (tempRY-MAX_MIDDLE_VALUE)*0x080/(MAX_JOY_VALUE-MAX_MIDDLE_VALUE)+0x80;
	}
	else
	{
		tempRY = 0xFF;
	}
	
	ctrLeftX	= uint8_t(tempLX);
	ctrLeftY	= 255-uint8_t(tempLY);
	ctrRightX	= uint8_t(tempRX);
	ctrRightY	= uint8_t(tempRY);
	
	ctrLeftY=255-ctrLeftY;
	ctrRightY=255-ctrRightY;
}


/**
  * @brief  ��ȡAD����ֵ,�Ѽ����������
  * @param  None
  * @retval None
  */
#define	AD_KEY_DEAD	3
#define	AD_KEY1_VALUE	0x80
#define	AD_KEY2_VALUE	0x55
#define	AD_KEY3_VALUE	0x40
#define	AD_KEY4_VALUE	0x33
#define	AD_KEY_COUNT	2
void Process::getAdKeyValue(void)
{
	uint8_t	leftAdKeyValue=0;
	uint8_t	rightAdKeyValue=0;
	static	bool tempLeftAdKeyValue[4] = {false,false,false,false};
	static	uint8_t countLeftAdKey[4] = {0,0,0,0};
	static	bool tempRightAdKeyValue[4] = {false,false,false,false};
	static	uint8_t countRightAdKey[4] = {0,0,0,0};
	
	leftAdKeyValue	= AD_Filter[NUM_KEY_LEFT]>>4;	
	if (leftAdKeyValue<=0x05)									//	���û�а�������,��������1K
	{
		for(uint8_t i=0 ; i<LEFT_AD_KEY_NUM ; i++ )				//	����ȫ����������
			tempLeftAdKeyValue[i]=false;
	}
	else if (leftAdKeyValue>(AD_KEY1_VALUE-AD_KEY_DEAD)&&leftAdKeyValue<(AD_KEY1_VALUE+AD_KEY_DEAD))			//	������1��������������120R
	{
		for(uint8_t i=0 ; i<LEFT_AD_KEY_NUM ; i++ )				//	����ȫ����������
		{tempLeftAdKeyValue[i]=false;}		
		tempLeftAdKeyValue[LEFT1]=true;
	}
	else if (leftAdKeyValue>(AD_KEY2_VALUE-AD_KEY_DEAD)&&leftAdKeyValue<(AD_KEY2_VALUE+AD_KEY_DEAD))			//	������2��������������330R
	{
		for(uint8_t i=0 ; i<LEFT_AD_KEY_NUM ; i++ )				//	����ȫ����������
		{tempLeftAdKeyValue[i]=false;}		
		tempLeftAdKeyValue[LEFT3]=true;
	}
	
	else if (leftAdKeyValue>(AD_KEY3_VALUE-AD_KEY_DEAD)&&leftAdKeyValue<(AD_KEY3_VALUE+AD_KEY_DEAD))			//	������3��������������1K
	{
		for(uint8_t i=0 ; i<LEFT_AD_KEY_NUM ; i++ )				//	����ȫ����������
		{tempLeftAdKeyValue[i]=false;}		
		tempLeftAdKeyValue[LEFT2]=true;
	}
	else if (leftAdKeyValue>(AD_KEY4_VALUE-AD_KEY_DEAD)&&leftAdKeyValue<(AD_KEY4_VALUE+AD_KEY_DEAD))			//	������4��������������2K
	{
		for(uint8_t i=0 ; i<LEFT_AD_KEY_NUM ; i++ )				//	����ȫ����������
		{tempLeftAdKeyValue[i]=false;}		
		tempLeftAdKeyValue[LEFT4]=true;
	}

	for(uint8_t i=0; i<4; i++)
	{
		if(leftAdKey[i]!=tempLeftAdKeyValue[i])
		{
			countLeftAdKey[i]++;
			if(countLeftAdKey[i]>AD_KEY_COUNT)
			{
				leftAdKey[i]=tempLeftAdKeyValue[i];
				countLeftAdKey[i]=0;
			}
		}
		else
		{
			countLeftAdKey[i]=0;
		}
	}
	
	rightAdKeyValue	= AD_Filter[NUM_KEY_RIGHT]>>4;
	if (rightAdKeyValue<=0x05)									//	�Ҳ�û�а�������,��������1K
	{
		for(uint8_t i=0 ; i<RIGHT_AD_KEY_NUM ; i++ )
			tempRightAdKeyValue[i]=false;
	}
	else if (rightAdKeyValue>(AD_KEY1_VALUE-AD_KEY_DEAD)&&rightAdKeyValue<(AD_KEY1_VALUE+AD_KEY_DEAD))		//	������1��������������120R
	{
		for(uint8_t i=0 ; i<RIGHT_AD_KEY_NUM ; i++ )			//	����ȫ����������
			{tempRightAdKeyValue[i]=false;}		
		tempRightAdKeyValue[RIGHT1]=true;
	}
	else if (rightAdKeyValue>(AD_KEY2_VALUE-AD_KEY_DEAD)&&rightAdKeyValue<(AD_KEY2_VALUE+AD_KEY_DEAD))		//	������2��������������330R
	{
		for(uint8_t i=0 ; i<RIGHT_AD_KEY_NUM ; i++ )			//	����ȫ����������
			{tempRightAdKeyValue[i]=false;}		
		tempRightAdKeyValue[RIGHT3]=true;
	}
	else if (rightAdKeyValue>(AD_KEY3_VALUE-AD_KEY_DEAD)&&rightAdKeyValue<(AD_KEY3_VALUE+AD_KEY_DEAD))		//	������3��������������1K
	{
		for(uint8_t i=0 ; i<RIGHT_AD_KEY_NUM ; i++ )			//	����ȫ����������
			{tempRightAdKeyValue[i]=false;}		
		tempRightAdKeyValue[RIGHT2]=true;
	}
	else if (rightAdKeyValue>(AD_KEY4_VALUE-AD_KEY_DEAD)&&rightAdKeyValue<(AD_KEY4_VALUE+AD_KEY_DEAD))		//	������4��������������2K
	{
		for(uint8_t i=0 ; i<RIGHT_AD_KEY_NUM ; i++ )			//	����ȫ����������
			{tempRightAdKeyValue[i]=false;}		
		tempRightAdKeyValue[RIGHT4]=true;
	}	
	
	for(uint8_t i=0; i<4; i++)
	{
		if(rightAdKey[i]!=tempRightAdKeyValue[i])
		{
			countRightAdKey[i]++;
			if(countRightAdKey[i]>AD_KEY_COUNT)
			{
				rightAdKey[i]=tempRightAdKeyValue[i];
				countRightAdKey[i]=0;
			}
		}
		else
		{
			countRightAdKey[i]=0;
		}
	}
	if(rightAdKey[0]||rightAdKey[1]||rightAdKey[2]||rightAdKey[3]||leftAdKey[0]||leftAdKey[1]||leftAdKey[2]||leftAdKey[3])
		testLed->setOn();
	else
		testLed->setOff();
}
	
void Process::getKeyValue()
{
//	for(uint8_t index=0; index<NUM_KEY; index++) 				// ��ȡ���а�����Ϣ
//			keys[index]->getValue();							// ��ȡ������Ϣ
}

/**
  * @brief  ʹ��SWD���ر�JTAG
  * @param  None
  * @retval None
  */
void Process::enable_SWD_disable_Jtag()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//	ʹ��AFIOʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//	�ر�JTAG��������ΪGPIO��
}



 Process::Process()
{
	enable_SWD_disable_Jtag();											//	�ر�JTAG��SWD	
	initIo();															//	��ʼ��ָʾ��
	initADs();															//	��ʼ��ADͨ��
	initUsarts();														//	��ʼ������
	initTimers();														//	��ʼ����ʱ��	
	initAllData();														//	��ʼ����������
	testLed->setOn();													//	
	SysTick_DelayMs(3000);												//	���µ�Դ����3000ms���ٿ�����������Ҫ��ʼ��2s����
	setPowerState(true);												//	����ϵͳ��Դ
//	setDataCh(1);														//	ÿ���ϵ��������һ������
	testLed->setOff();													//	ָʾ�ƹر�-ϵͳ�ϵ����
	setPowerLed();
}
	 
/**
  * @brief  �����û�����
  * @param  None
  * @retval None
  */
void Process::openPeriph()
{
	SysTick_DelayMs(10);												//	��ʱ 10ms
	com1st->open();    													//	����ͨ�Ŷ˿�1
	com2nd->open();														//	����ͨ�Ŷ˿�2
	t2->start();														//	������ʱ��2
	t3->start();														//	������ʱ��3
	t4->start();														//	������ʱ��4
}

/**
  * @brief  ��ʼ��IO
  * @param  None
  * @retval None
  */
void Process::initIo()
{	
	testLed		= new IoOut(TESTLED_PORT,TESTLED_PIN);					//	ָʾ�ƣ��͵�ƽ����
	
	powerLed1R	= new IoOut(POWER_LED1R_PORT,POWER_LED1R_PIN,true);		//	ָʾ�ƣ�1����ߵ�ƽ��0����͵�ƽ
	powerLed1B	= new IoOut(POWER_LED1B_PORT,POWER_LED1B_PIN,true);		//	ָʾ�ƣ�1����ߵ�ƽ��0����͵�ƽ
	powerLed2R	= new IoOut(POWER_LED2R_PORT,POWER_LED2R_PIN,true);		//	ָʾ�ƣ�1����ߵ�ƽ��0����͵�ƽ
	powerLed2B	= new IoOut(POWER_LED2B_PORT,POWER_LED2B_PIN,true);		//	ָʾ�ƣ�1����ߵ�ƽ��0����͵�ƽ
	powerLed3R	= new IoOut(POWER_LED3R_PORT,POWER_LED3R_PIN,true);		//	ָʾ�ƣ�1����ߵ�ƽ��0����͵�ƽ
	powerLed3B	= new IoOut(POWER_LED3B_PORT,POWER_LED3B_PIN,true);		//	ָʾ�ƣ�1����ߵ�ƽ��0����͵�ƽ
	powerLed4R	= new IoOut(POWER_LED4R_PORT,POWER_LED4R_PIN,true);		//	ָʾ�ƣ�1����ߵ�ƽ��0����͵�ƽ
	powerLed4B	= new IoOut(POWER_LED4B_PORT,POWER_LED4B_PIN,true);		//	ָʾ�ƣ�1����ߵ�ƽ��0����͵�ƽ
	
	powerCtr 	= new IoOut(POWER_CTR_PORT,POWER_CTR_PIN,true);			//	��Դ�������ţ��ߵ�ƽ����
	
	digSet		= new IoOut(DIG_SET_PORT,DIG_SET_PIN,true);				//	�����������ţ��ߵ�ƽ����
	
	vedioCh1	= new IoOut(VEDIO_CH1_PORT,VEDIO_CH1_PIN,true);			//	ͼ������ͨ��1���ߵ�ƽ��Ч
	vedioCh2	= new IoOut(VEDIO_CH2_PORT,VEDIO_CH2_PIN,true);			//	ͼ������ͨ��2���ߵ�ƽ��Ч
	vedioCh3	= new IoOut(VEDIO_CH3_PORT,VEDIO_CH3_PIN,true);			//	ͼ������ͨ��3���ߵ�ƽ��Ч
	vbtCtr		= new IoOut(VBT_CTR_PORT,VBT_CTR_PIN,true);				//	����/ͼ����Դ����
	
	BtSet		= new IoOut(BT_SET_PORT,BT_SET_PIN,true);				//	usb�������ţ�Ĭ�ϲ��ô˹���
}

/**
  * @brief  ��ʼ��AD
  * @param  None
  * @retval None
  */
void Process::initADs()
{
	ADC1_DMA_Init();
}

/**
  * @brief  ��ʼ����ʱ��
  * @param  None
  * @retval None
  */
void Process::initTimers()
{
	t2=new Timer (TIM2);
	t2->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM2_SubPriority);
	t2->setTimeOut(TIM2_DELAY_TIME);		// �޸ĺ궨���Ըı���ʱ

	t3=new Timer (TIM3);
	t3->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM3_SubPriority);
	t3->setTimeOut(TIM3_DELAY_TIME);		// �޸ĺ궨���Ըı���ʱ
	
	t4=new Timer (TIM4);
	t4->setPriority(STM32_NVIC_TIM2_PrePriority,STM32_NVIC_TIM4_SubPriority);
	t4->setTimeOut(TIM4_DELAY_TIME);		// �޸ĺ궨���Ըı���ʱ
}

/**
  * @brief  ��ʼ��usart
  * @param  None
  * @retval None
  */
void Process::initUsarts()
{
	com1st = new SerialPort(1,9600);	
	com2nd = new SerialPort(3,9600);	
	protocol = new Protocol(com1st,com2nd);
}

/**
  * @brief  ��ʼ��ȫ������
  * @param  None
  * @retval None
  */	
void Process::initAllData()
{
	for(uint8_t i=0; i<COMN1_SEND_LENGTH;i++)
	{
		com1st_DataToSend[i]=0;
	}	
	
	for(uint8_t i=0; i<COMN2_SEND_LENGTH;i++)
	{
		com2nd_DataToSend[i]=0;
	}
	
	//	����Ĭ������
	botLeftBatVal=0;	//	���ص���0
	botRightBatVal=0;	//	�ҵ�ص���0
	botAngle=0;			//	����Ƕ�0
	botIR=0;			//	����������ź�
	botMode=0;			//	�����ֶ�ģʽ
	
	//	padĬ������
	padOffState=false;	//	pad������
	padChannel=0x00;	//	padͨ��0
	
	//	������Ĭ������
	ctrBatVal=0;		//	��ص���0	
	ctrLeftX=128;		//	��ҡ��X����λ��
	ctrLeftY=128;		//	��ҡ��Y����λ��
	ctrRightX=128;		//	��ҡ��X����λ��
	ctrRightY=128;		//	��ҡ��Y����λ��
	
	//	������Ĭ��״̬
	ctrData1=0x00;
	ctrStatus1=0x10;
	ctrStatus2=0x50;
	ctrBotData1=0x12;
	ctrBotData2=0x00;	
	ctrFlag_PowerOn=0x00;	
	ctrFlag_PowerLedOff=0x00;
	ctrFlag_Auto=false;
	ctrFlag_InterruptAuto=false;
	ctrFlag_WorkAuto=false;
	ctrFlag_PadInsert=false;
	
	//	����ͨ��
	padChannel=0x01;
	ctrChannel=0x01;
	botChannel=0x01;
	
	setCom1Data();													//	������Ҫ���͵�����
	setCom2Data();													//	������Ҫ���͵�����
	protocol->com1st_UpdateSendBuf(com1st_DataToSend);				//	������Ҫ���͵�����
	protocol->com2nd_UpdateSendBuf(com2nd_DataToSend);				//	������Ҫ���͵�����
}

/**
  * @brief  ���õ�Դָʾ��
  * @param  None
  * @retval None
  */
void Process::setPowerLed()
{
	static uint8_t showCount=0;
	float  tempValue=ctrBatVal;
	if(ctrFlag_PowerLedOff==0x00)
	{
		showCount++;
		if(showCount>=50)												//	ÿ��50�θ���һ����ʾ�������������
		{
			showCount=0;
			if(tempValue<(102/2))
			{
				powerLed1R->setOn();	
				powerLed1B->setOff();
				powerLed2R->setOn();	
				powerLed2B->setOff();
				powerLed3R->setOn();	
				powerLed3B->setOff();
				powerLed4R->setOn();	
				powerLed4B->setOff();
			}
			else if(tempValue<(108/2))
			{	
				powerLed1R->setOn();	
				powerLed1B->setOff();
				powerLed2R->setOn();	
				powerLed2B->setOff();
				powerLed3R->setOn();	
				powerLed3B->setOff();
				powerLed4R->setOff();	
				powerLed4B->setOn();
			}
			else if(tempValue<(114/2))
			{
				powerLed1R->setOn();	
				powerLed1B->setOff();
				powerLed2R->setOn();	
				powerLed2B->setOff();
				powerLed3R->setOff();	
				powerLed3B->setOn();
				powerLed4R->setOff();	
				powerLed4B->setOn();
			}
			else if(tempValue<=(120/2))
			{
				powerLed1R->setOn();	
				powerLed1B->setOff();
				powerLed2R->setOff();	
				powerLed2B->setOn();
				powerLed3R->setOff();	
				powerLed3B->setOn();
				powerLed4R->setOff();	
				powerLed4B->setOn();
			}
			else 	//	tempValue>120/2
			{
				powerLed1R->setOff();	
				powerLed1B->setOn();
				powerLed2R->setOff();	
				powerLed2B->setOn();
				powerLed3R->setOff();	
				powerLed3B->setOn();
				powerLed4R->setOff();	
				powerLed4B->setOn();
			}			
		}
	}
	else
	{
		powerLed1R->setOff();	
		powerLed1B->setOff();
		powerLed2R->setOff();	
		powerLed2B->setOff();
		powerLed3R->setOff();	
		powerLed3B->setOff();
		powerLed4R->setOff();	
		powerLed4B->setOff();
	}
}

/**
  * @brief  �����������ص�ѹ,1unit=0.2V
  * @param  None
  * @retval None
  */
#define	R_UP	10	//	��ѹ����10k
#define	R_DOWN	1	//	��ѹ����1k
void Process::getBatValue()
{	
	float tempValue=0;
	
	tempValue = AD_Filter[NUM_POWER];
	
	tempValue = tempValue*33*(R_DOWN+R_UP)/(R_DOWN*4096)/2;
	ctrBatVal = (uint8_t)(tempValue);
}


/**
  * @brief  ���õ�Դ״̬
  * @param  
			*true	�򿪿�������Դ
			*false	�رտ�������Դ
  * @retval None	
  */
void Process::setPowerState(bool state)
{
	if(state)
		powerCtr->setOn();
	else
		powerCtr->setOff();
}

/**
  * @brief  ����ͼ��ͨ��
  * @param  
			*ch		ͼ��ͨ��
  * @retval None	
  */
void Process::setVedioCh(uint8_t ch)
{
	switch (ch)
	{
		case 0:
			vedioCh1->setOff();
			vedioCh2->setOff();
			vedioCh3->setOff();
			break;
		case 1:
			vedioCh1->setOn();
			vedioCh2->setOff();
			vedioCh3->setOff();
			break;
		case 2:
			vedioCh1->setOff();
			vedioCh2->setOn();
			vedioCh3->setOff();
			break;
		case 3:
			vedioCh1->setOn();
			vedioCh2->setOn();
			vedioCh3->setOff();
			break;
		case 4:
			vedioCh1->setOff();
			vedioCh2->setOff();
			vedioCh3->setOn();
			break;
		case 5:
			vedioCh1->setOn();
			vedioCh2->setOff();
			vedioCh3->setOn();
			break;
		case 6:
			vedioCh1->setOff();
			vedioCh2->setOn();
			vedioCh3->setOn();
			break;
		case 7:
			vedioCh1->setOn();
			vedioCh2->setOn();
			vedioCh3->setOn();
			break;
		default :
			vedioCh1->setOff();
			vedioCh2->setOff();
			vedioCh3->setOff();
			break;
	}
}

/**
  * @brief  ��������ͨ��,ͨ���Ŵ�1��ʼ��Ч
  * @param  
			*ch		����ͨ��
  * @retval None	
  */
void Process::setDataCh(uint8_t ch)
{	
	uint8_t DTSet[17];						//	�������ݳ���17
	char baudRate=0x03;						//	��������&���ڲ�����
	
	if(ch<1)
		ch=1;
	
	DTSet[0]=0xAA;							//	���ܸ���
	DTSet[1]=0xFA;							//	���ܸ���	
	DTSet[2]=0x03;							//	���ܸ���
	DTSet[3]=ch;							//	�ŵ�,�ŵ���1��ʼ��0��Ч
	DTSet[4]=0x14;							//	����Ƶ�Σ����ܸ��ģ�01��ʾ433MHz
	DTSet[5]=baudRate;						//	���ߴ������ʣ�03��ʾ9600
	DTSet[6]=0x07;							//	���书�ʣ����������
	DTSet[7]=baudRate;						//	���ڲ����ʣ�03��ʾ9600
	DTSet[8]=0x02;							//	��������λ
	DTSet[9]=0x01;							//	����ֹͣλ
	DTSet[10]=0x01;							//	����У��λ
	DTSet[11]=0x00;							//	NET ID	
	DTSet[12]=0x00;							//	NET ID	
	DTSet[13]=0x00;							//	NET ID	
	DTSet[14]=0x00;							//	NET ID	
	DTSet[15]=0x00;							//	NODE ID	
	DTSet[16]=0xac;							//	NODE ID	

//	delete	com2nd;
//	com2nd = new SerialPort(3,9600);	
	digSet->setOn();						//	������������ģʽ
	SysTick_DelayMs(5);						//	�˴���ʱ��С3ms��С��3ms����ʧ��
	protocol->com2nd->write(DTSet,17);		//	��������
	SysTick_DelayMs(5);						//	�˴���ʱ��С3ms��С��3ms����ʧ��
	digSet->setOff();						//	�ر���������ģʽ
	
//	delete	com2nd;
//	com2nd = new SerialPort(3,19200);
}

/**
  * @brief  ��������/ͼ��ͨ��
  * @param  
			*ch		����/ͼ��ͨ��
  * @retval None	
  */
void Process::setChannel(uint8_t ch)
{
	switch(ch)
	{
		case 0:
			setDataCh(1);						//	���������ŵ�
			setVedioCh(0);						//	����ͼ��ͨ��
			break;
		case 1:
			setDataCh(2);						//	���������ŵ�
			setVedioCh(1);						//	����ͼ��ͨ��
			break;
		case 2:
			setDataCh(3);						//	���������ŵ�
			setVedioCh(2);						//	����ͼ��ͨ��
			break;
		case 3:
			setDataCh(4);						//	���������ŵ�
			setVedioCh(3);						//	����ͼ��ͨ��
			break;
		case 4:
			setDataCh(5);						//	���������ŵ�
			setVedioCh(4);						//	����ͼ��ͨ��
			break;
		case 5:
			setDataCh(6);						//	���������ŵ�
			setVedioCh(5);						//	����ͼ��ͨ��
			break;
		case 6:
			setDataCh(7);						//	���������ŵ�
			setVedioCh(6);						//	����ͼ��ͨ��
			break;
		case 7:
			setDataCh(8);						//	���������ŵ�
			setVedioCh(7);						//	����ͼ��ͨ��
			break;
		default :
			break;
	}
}

/**
  * @brief  ���Դ��룬�������
  * @param  None
  * @retval None
  */
void Process::testWithUsart(void)
{
	uint8_t aa;
	aa=AD_Filter[1]>>4;													//	���Դ���	
	protocol->com2nd->putChar(aa);										//	���Դ���	
//	testLed->reverseState();
}

/*--------------------------------- End of Process.cpp -----------------------------*/
