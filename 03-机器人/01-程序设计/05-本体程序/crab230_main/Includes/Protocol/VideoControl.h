 
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _VIDEO_CONTROL_H
#define _VIDEO_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "BaseControl.h"     //Э��Ļ���
 
 
#define VIDEO_1  0x81
#define VIDEO_2  0x82
#define VIDEO_12 0x9b

class VideoControl  
{
public:
	VideoControl(SerialPort * p);
	virtual ~VideoControl(); 
	void sendVideoCommand(uint8_t );
	void sendVideoChannel(uint8_t );	
 
private:
	SerialPort *port; 
};
#endif   
