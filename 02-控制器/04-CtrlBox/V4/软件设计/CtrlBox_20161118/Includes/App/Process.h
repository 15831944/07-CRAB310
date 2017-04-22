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
//<���Ŷ˿ڶ���>
	#define	TESTLED_PORT			  GPIOA
	#define	TESTLED_PIN				GPIO_Pin_6
	//<�Ŵ���С�����٣����� ���Ŷ���>
	#define KEY1_PORT           GPIOA
	#define KEY1_PIN            GPIO_Pin_10
	#define KEY2_PORT           GPIOA
	#define KEY2_PIN            GPIO_Pin_9
	#define KEY3_PORT           GPIOB
	#define KEY3_PIN            GPIO_Pin_15
	#define KEY4_PORT           GPIOA
	#define KEY4_PIN            GPIO_Pin_8
	//</�Ŵ���С�����٣����� ���Ŷ���>
	//<���ƣ��۲�ƣ��Զ�ģʽ�������л� ���Ŷ���>
	#define KEY5_PORT           GPIOB
	#define KEY5_PIN            GPIO_Pin_5
	#define KEY6_PORT           GPIOB
	#define KEY6_PIN            GPIO_Pin_4
	#define KEY7_PORT           GPIOB
	#define KEY7_PIN            GPIO_Pin_3
	#define KEY8_PORT           GPIOA
	#define KEY8_PIN            GPIO_Pin_15
	//</���ƣ��۲�ƣ��Զ�ģʽ�������л� ���Ŷ���>
	//<��Դָʾ�� ���Ŷ���>
	#define POWLED1_PORT           GPIOB
	#define POWLED1_PIN            GPIO_Pin_14
	#define POWLED2_PORT           GPIOB
	#define POWLED2_PIN            GPIO_Pin_13
	#define POWLED3_PORT           GPIOB
	#define POWLED3_PIN            GPIO_Pin_12
	#define POWLED4_PORT           GPIOB
	#define POWLED4_PIN            GPIO_Pin_2	
	//</��Դָʾ�� ���Ŷ���>
	//<���� ���Ŷ���>
	#define PADDET_PORT           GPIOA
	#define PADDET_PIN            GPIO_Pin_12
	#define CTRLBTPOW_PORT           GPIOA
	#define CTRLBTPOW_PIN            GPIO_Pin_11
	#define CTRLVIDEOPOW_PORT           GPIOB
	#define CTRLVIDEOPOW_PIN            GPIO_Pin_6
	#define CTRLPOW_PORT           GPIOB
	#define CTRLPOW_PIN            GPIO_Pin_7
	
	//</���� ���Ŷ���>
	
	
	/*
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
	
	*/
	
//</���Ŷ˿ڶ���>
	
//<AD ��ض���>
	/* AD˳����--------------------------------------------------------------------*/
	#define	NUM_KEY_POWER			0										//	��Դ�ػ�����
	#define	NUM_POWER			   	1										//	��Դ��ѹ
	
	#define NUM_ctrLeftX			3										//  ȫ�������˶�����
	#define NUM_ctrLeftY			2										//	ȫ��ǰ���˶�����
	
	#define	NUM_ctrRightY			5										//	��̨����
	#define NUM_ctrRightX			4										//	ԭ��������ת




	
	#define	LEFT1	0
	#define	LEFT2	1
	#define	LEFT3	2
	#define	LEFT4	3
	#define	RIGHT1	0
	#define	RIGHT2	1
	#define	RIGHT3	2
	#define	RIGHT4	3
	//</AD ��ض���>

#endif
	
	#define	TIM2_DELAY_TIME		10
	#define	TIM3_DELAY_TIME		50
	#define	TIM4_DELAY_TIME		50
	
	#define LEFT_KEY_NUM		4
	#define RIGHT_KEY_NUM	4
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
		
			SerialPort 	*comToPad,*comToRobot;             //
			Protocol 	*protocol;
			Timer		*t2,*t3,*t4;								//	��ʱ��2,��ʱ��3,��ʱ��4			
			IoOut 		*testLed;									//	����ָʾ��		
/*		
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
		*/
			// Key			*keys[NUM_KEY];							//	����	
			//<8������ʵ������>
			Key     *zoomInKey,*zoomOutKey;
			Key     *speedUpKey,*speedDownKey;
			Key     *vehicleLedKey,*observeLedKey;
			Key     *autoModeKey,*pictureSwitchKey;
			//<Pad���ʵ������>
			Key     *padDetector;
			//3����Դ����IO
			IoOut   *blueToothPowCtrl;
			IoOut   *videoCardPowCtrl;
			IoOut   *systemPowCtrl;
			//4����Դָʾ��IO
			IoOut   *powerLed1,*powerLed2,*powerLed3,*powerLed4;
			
	
			bool		ctrFlag_Auto;								//	�Զ�ģʽ
			bool		ctrFlag_InterruptAuto;						//	�Զ�ģʽ�����
			bool		ctrFlag_WorkAuto;							//	�Զ�ģʽ��ɱ�־
			bool		ctrFlag_PowerOn;							//	�ϵ�׼����
			bool		ctrFlag_PowerLedOff;						//	��Դָʾ�����
			bool		ctrFlag_PadInsert;							//	Pad�����־
			/*
			bool		leftAdKey[LEFT_AD_KEY_NUM];					//	���AD������ֵ
			bool		rightAdKey[RIGHT_AD_KEY_NUM];				//	�Ҳ�AD������ֵ
			*/
			uint8_t		count_PowerOff;								//	�ػ�����ʱ					
			uint8_t		com1st_DataToSend[COMN1_SEND_DATA_LENGTH];	//	com1st��Ҫ���͵�����
			uint8_t		com2nd_DataToSend[COMN2_SEND_DATA_LENGTH];	//	com2nd��Ҫ���͵�����		
			

			void	    initAllData(void);							//	ȫ�����ݳ�ʼ����������־λ
			void			initGPIO(void);							  	//	��ʼ��IO
			void	    initADs(void);								//	��ʼ��ADͨ��
			void	    initUsarts(void);							//	��ʼ������
			void	    initTimers(void);							//	��ʼ����ʱ��		
			
			void	  getKeyValue(void);							//	��ȡ����ֵ
// 			void		getAdKeyValue(void);						//	��ȡAD����ֵ
			void		getBatValue(void);							//	��ȡ��ѹֵ
			void		getJoyStickValue(void);						//	��ȡҡ������	
			
			void    detectPad();                    //���Pad
			void    detectPowerSwitch();            //����Դ����
			
			void		dealPadData(void);							//	������������
			void		dealBotData(void);							//	����������
			void		dealKeyValue(void);							//	��������������
			void		setPowerLed(void);							//	���õ�Դָʾ��
			void		setPowerState(bool);						//	���õ�Դ״̬
			
// 			void		setChannel(uint8_t);						//	����ͨ��
// 			void		setVedioCh(uint8_t);						//	����ͼ��ͨ��
// 			void		setDataCh(uint8_t);							//	��������ͨ��			

			void		setComToPadData(void);						  	//	����Com1��Ҫ���͵�����
			void		setComToRobotData(void);							//	����Com2��Ҫ���͵�����
			
			void		enable_SWD_disable_Jtag(void);				//	ʹ��SWD���ر�JTAG
			void		testWithUsart(void);						//	ͨ�����ڲ�������
	};
	
#endif 
/*--------------------------------- End of Process.h -----------------------------*/
