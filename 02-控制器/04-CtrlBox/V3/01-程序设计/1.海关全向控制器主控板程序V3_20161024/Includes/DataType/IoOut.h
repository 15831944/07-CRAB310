/**
******************************************************************************
*�ļ���Key.cpp
*���ߣ��Ϻ�
*�汾��1.0
*���ڣ�2015-03-09
*��Ҫ��Key���ͷ�ļ�
*��ע��
******************************************************************************  
*/ 
#ifndef _IO_OUT_H
	#define _IO_OUT_H

	#include  "STM32_GPIO.h"

	class IoOut
	{
		public:
			IoOut(GPIO_TypeDef *port=GPIOA, uint16_t pin=GPIO_Pin_0, bool bLevel=false);
			~IoOut();

			void 			setOn();		
			void 			setOff();	
			void 			reverseState();	//��תIo��״̬
			
		private:
			void 			initIo();
			GPIO_TypeDef 	*ioOutPort; 
			uint16_t 		ioOutPin;	
			uint8_t 		ioOutLevel;						
	};

#endif



