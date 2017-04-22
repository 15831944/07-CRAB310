/**
  ******************************************************************************
	*�ļ���Process.h
	*���ߣ��Ϻ�
	*�汾��2.0
	*���ڣ�
	*��Ҫ��
	*��ע��
	*
  ******************************************************************************  
	*/ 
	
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _PROCESS_H
	#define _PROCESS_H

	/* ͷ�ļ����� ------------------------------------------------------------------*/
	#include "DataTypeConvertion.h"
	#include "stm32f10x.h"
	#include "Protocol.h"
	#include "SerialPort.h"
	#include "Timer.h"
	#include "IoOut.h"
	#include "Key.h"
	#include "STM32_SysTick.h"
	#include "STM32_ADC.h" 
	#include "stdint.h"
	
	
/* ���Ŷ���--------------------------------------------------------------------*/
#define	USE_PERIPH
#ifdef	USE_PERIPH
	#define	TESTLED_PORT			GPIOA
	#define	TESTLED_PIN				GPIO_Pin_8
	#define	POWER_LED1R_PORT		GPIOA
	#define	POWER_LED1R_PIN			GPIO_Pin_15
	#define	POWER_LED1B_PORT		GPIOB
	#define	POWER_LED1B_PIN			GPIO_Pin_3
	#define	POWER_LED2R_PORT		GPIOB
	#define	POWER_LED2R_PIN			GPIO_Pin_4
	#define	POWER_LED2B_PORT		GPIOB
	#define	POWER_LED2B_PIN			GPIO_Pin_5
	#define	POWER_LED3R_PORT		GPIOB
	#define	POWER_LED3R_PIN			GPIO_Pin_6
	#define	POWER_LED3B_PORT		GPIOB
	#define	POWER_LED3B_PIN			GPIO_Pin_7
	#define	POWER_LED4R_PORT		GPIOB
	#define	POWER_LED4R_PIN			GPIO_Pin_8
	#define	POWER_LED4B_PORT		GPIOB
	#define	POWER_LED4B_PIN			GPIO_Pin_9
	#define	POWER_CTR_PORT			GPIOB
	#define	POWER_CTR_PIN			GPIO_Pin_1
	#define	DIG_SET_PORT			GPIOB
	#define	DIG_SET_PIN				GPIO_Pin_12
	#define	VEDIO_CH1_PORT			GPIOB
	#define	VEDIO_CH1_PIN			GPIO_Pin_13
	#define	VEDIO_CH2_PORT			GPIOB
	#define	VEDIO_CH2_PIN			GPIO_Pin_14
	#define	VEDIO_CH3_PORT			GPIOB
	#define	VEDIO_CH3_PIN			GPIO_Pin_15
	#define	BT_SET_PORT				GPIOA
	#define	BT_SET_PIN				GPIO_Pin_12
	#define	VBT_CTR_PORT			GPIOB
	#define	VBT_CTR_PIN				GPIO_Pin_2
	

	/* AD˳����--------------------------------------------------------------------*/
	#define NUM_ctrLeftX			3										//	�˶�����
	#define NUM_ctrLeftY			2										//	�˶�����
	#define NUM_ctrRightX			6										//	ԭ����ת
	#define	NUM_ctrRightY			5										//	��̨����
	#define NUM_KEY_LEFT			1										//	��ఴ����
	#define	NUM_KEY_RIGHT			7										//	�Ҳఴ����
	#define	NUM_KEY_POWER			0										//	��Դ�ػ�����
	#define	NUM_POWER				4										//	��Դ��ѹ
	#define	PADTEST					8										//	���pad����
	
	#define	LEFT1	0
	#define	LEFT2	1
	#define	LEFT3	2
	#define	LEFT4	3
	#define	RIGHT1	0
	#define	RIGHT2	1
	#define	RIGHT3	2
	#define	RIGHT4	3

#endif
	
	#define	TIM2_DELAY_TIME		10
	#define	TIM3_DELAY_TIME		50
	#define	TIM4_DELAY_TIME		50
	#define LEFT_AD_KEY_NUM		4
	#define RIGHT_AD_KEY_NUM	4
	/* ������� --------------------------------------------------------------------*/
	class Process
	{
		public:
						Process();
						~Process();
			void 		runOnTime2(void);							//	�����ڶ�ʱ��TIM2�еĺ���
			void 		runOnTime3(void);							//	�����ڶ�ʱ��TIM3�еĺ���
			void 		runOnTime4(void);							//	�����ڶ�ʱ��TIM4�еĺ���
			void 		openPeriph(void);							//	��������		
		
		private:
			uint8_t		ctrBatVal;									//	�����ذ��ÿ�������ص��������͸�pad
			uint8_t		ctrData1, ctrStatus1, ctrStatus2;			//	�����ذ��ÿ������ݣ����͸�pad
			uint8_t		ctrBotData1, ctrBotData2;					//	�����ذ��ÿ������ݣ����͸�����
			uint8_t		ctrLeftX, ctrLeftY, ctrRightX, ctrRightY;	//	�����ذ���ҡ������,���͸�����			
			uint8_t		ctrChannel;									//	�ӱ��������ݣ����¿�����ͨ���󷵻ظ�pad

			bool		padOffState;								//	��pad������ݣ�pad�ػ�״̬
			uint8_t		padChannel;									//	��pad������ݣ�ͨ����
			
			uint8_t		botLeftBatVal, botRightBatVal;				//	�ӱ��������ݣ������ص���
			uint8_t		botAngle;									//	�ӱ��������ݣ�����Ƕ�
			uint8_t		botMode;									//	�ӱ��������ݣ�����ģʽ
			uint8_t		botIR;										//	�ӱ��������ݣ��������
			uint8_t		botChannel;									//	�ӱ��������ݣ�����ͨ����
		
			SerialPort 	*com1st,*com2nd;
			Protocol 	*protocol;
			Timer		*t2,*t3,*t4;								//	��ʱ��2,��ʱ��3,��ʱ��4			
			IoOut 		*testLed;									//	����ָʾ��			
			IoOut		*powerLed1R, *powerLed1B;					//	��Դָʾ��1
			IoOut		*powerLed2R, *powerLed2B;					//	��Դָʾ��2
			IoOut		*powerLed3R, *powerLed3B;					//	��Դָʾ��3
			IoOut		*powerLed4R, *powerLed4B;					//	��Դָʾ��4
			IoOut		*powerCtr;									//	��Դ����	
			IoOut		*vbtCtr;									//	��Ƶ�ɼ�����������Դ����
			IoOut		*digSet;									//	������������
			IoOut		*vedioCh1, *vedioCh2, *vedioCh3;			//	ͼ����������
			IoOut		*BtSet;										//	������������
			IoOut		*spareIo1, *spareIo2;						//	Ԥ������		
			// Key			*keys[NUM_KEY];							//	����			
			
	
			bool		ctrFlag_Auto;								//	�Զ�ģʽ
			bool		ctrFlag_InterruptAuto;						//	�Զ�ģʽ�����
			bool		ctrFlag_WorkAuto;							//	�Զ�ģʽ��ɱ�־
			bool		ctrFlag_PowerOn;							//	�ϵ�׼����
			bool		ctrFlag_PowerLedOff;						//	��Դָʾ�����
			bool		ctrFlag_PadInsert;							//	Pad�����־
			bool		leftAdKey[LEFT_AD_KEY_NUM];					//	���AD������ֵ
			bool		rightAdKey[RIGHT_AD_KEY_NUM];				//	�Ҳ�AD������ֵ
			uint8_t		count_PowerOff;								//	�ػ�����ʱ					
			uint8_t		com1st_DataToSend[COMN1_SEND_DATA_LENGTH];	//	com1st��Ҫ���͵�����
			uint8_t		com2nd_DataToSend[COMN2_SEND_DATA_LENGTH];	//	com2nd��Ҫ���͵�����			

			void	    initAllData(void);							//	ȫ�����ݳ�ʼ����������־λ
			void		initIo(void);								//	��ʼ��IO
			void	    initADs(void);								//	��ʼ��ADͨ��
			void	    initUsarts(void);							//	��ʼ������
			void	    initTimers(void);							//	��ʼ����ʱ��		
			
			void	    getKeyValue(void);							//	��ȡ����ֵ
			void		getAdKeyValue(void);						//	��ȡAD����ֵ
			void		getBatValue(void);							//	��ȡ��ѹֵ
			void		getJoyStickValue(void);						//	��ȡҡ������	
			
			void		dealPadData(void);							//	������������
			void		dealBotData(void);							//	����������
			void		setCtrData(void);							//	���ÿ�������
			void		setPowerLed(void);							//	���õ�Դָʾ��
			void		setPowerState(bool);						//	���õ�Դ״̬
			
			void		setChannel(uint8_t);						//	����ͨ��
			void		setVedioCh(uint8_t);						//	����ͼ��ͨ��
			void		setDataCh(uint8_t);							//	��������ͨ��			

			void		setCom1Data(void);							//	����Com1��Ҫ���͵�����
			void		setCom2Data(void);							//	����Com2��Ҫ���͵�����
			
			void		enable_SWD_disable_Jtag(void);				//	ʹ��SWD���ر�JTAG
			void		testWithUsart(void);						//	ͨ�����ڲ�������
	};
	
#endif 
/*--------------------------------- End of Process.h -----------------------------*/
