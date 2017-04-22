/**
  ******************************************************************************
	*�ļ���OtherDeviceControl.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������һЩ�豸�Ŀ���Э�����ͷ�ļ�
	*��ע��
  ******************************************************************************  
  */ 

/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _OTHER_DEVICE_CONTROL_H
#define _OTHER_DEVICE_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "BaseControl.h"     //Э��Ļ���

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 
// #define RED 	false
// #define GREEN true

class OtherDeviceControl : public BaseControl
{
public:
	OtherDeviceControl(SerialPort * p);
	virtual ~OtherDeviceControl();
	void sendOtherDeviceCommand();							//���������豸��������
	void sendWeaponControlCommand();						//����������������
	void sendGunControlCommand();						//����������������

	void laserSightOn()			{setLaserSight(true);}
	void laserSightOff()		{setLaserSight(false);}
	void floodLightOn()			{setFloodLight(true);}
	void floodLightOff()		{setFloodLight(false);}
	void headLightOn()			{setheadLight(true);}
	void headLightOff()			{setheadLight(false);}
	void allLightOn()				{setFloodLight(true);setheadLight(true);}
	void allLightOff()			{setFloodLight(false);setheadLight(false);}
	void PowLedTrunRed()		{setPowerPilotLamp(false);}
	void PowLedTrunGreen()	{setPowerPilotLamp(true);}
	void setVideoSelect(uint8_t);
	void setVideoZoom(uint8_t);
private:
	bool floodLightFlag;
	bool headLightFlag;
	bool powerPilotLampFlag;
	bool laserSightFlag;
	uint8_t videoSelectFlag;
	uint8_t videoZoom;
	void setFloodLight(bool);
	void setheadLight(bool);
	void setPowerPilotLamp(bool);
	void setLaserSight(bool);
	
};
#endif  /*_OTHER_DEVICE_CONTROL_H */


