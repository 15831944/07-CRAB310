 
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _CAM_CONTROL_H
#define _CAM_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "BaseControl.h"     //Э��Ļ���
 
#define CAM_STOP  0x00
#define CAM_TELE  0x01
#define CAM_WIDE  0x02
#define CAM_OFF   0x00
#define CAM_ON    0x01

class CamControl  
{
public:
	CamControl(SerialPort * p);
	virtual ~CamControl();
	uint16_t crc16(uint8_t *buf, uint16_t len);
	void sendCamCommand(uint8_t *);
	void sendZoomCommand(uint8_t cmd);
	void sendOnePushAutoFocus(uint8_t cmd);
private:
	SerialPort *port; 
};
#endif   


