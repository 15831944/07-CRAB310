/***********************************************************************************************
*�ļ���		��	DataTypeConvertion.h
*����		��	��������ת��
*����		��	�Ϻ�
*��������	��	2016.1.17
*�޸�����	��	2016.1.17
*�޸��� 		��	�Ϻ�
*�޸�ԭ��	��	������룬���ע��
*�汾 		��	1.0
*��ʷ�汾	��	��
***********************************************************************************************/

#ifndef	_DATATYPECONVERTION_H
#define	_DATATYPECONVERTION_H
#ifdef __cplusplus
	 extern "C" {
	#endif
		 
	#include	"stdint.h"

	typedef union
			{	uint16_t u16_data;
				uint8_t  u8_data[2];
			}	Char2Uint;	// uint8_tתuint16_t
		
	#ifdef __cplusplus
	 }
	#endif
#endif
/*--------------------------------- End of DataTypeConvertion.h -----------------------------*/
