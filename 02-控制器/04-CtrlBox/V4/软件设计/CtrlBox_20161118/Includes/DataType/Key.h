/**
******************************************************************************
*�ļ���Key.h
*�汾��2.0
*���ڣ�2013-06-17
*��Ҫ���������ͷ�ļ�
*��ע��
******************************************************************************  
*/ 
#ifndef _Key_H
	#define _Key_H
	
	#include "stdlib.h"
	#include "stdint.h"
	#include "STM32_GPIO.h"

	#define	KEY_MAX_TIMER	1						//����״̬������һ�㲻��Ҫ�޸�
	#define KEY_PRESS_DOWN	0X00					//����״̬������Ϊ0
	#define KEY_PRESS_UP	0X01					//����״̬��̧��Ϊ1
		
	class Key
	{
		public:
			Key(GPIO_TypeDef *port=GPIOA, uint16_t Pin=GPIO_Pin_0, bool bLevel=false);
			~Key();
			uint8_t			FinalState;				//	��������״̬
			void			getValue(void);			//	��ȡ����ֵ
			
		private:
			void 			initKey(void);			//	������ʼ��
			GPIO_TypeDef 	*KeyPort;				//	�˿�
			uint16_t		KeyPin;					//	����
			bool			KeyLevel;				    //	������ƽ
			uint8_t			TrickCount;				//	����ʱ��
	};

#endif



