/**
  ******************************************************************************
	*�ļ���GpsImuControl.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-27
	*��Ҫ��GPS��IMU�豸�Ŀ���Э�����ͷ�ļ�
	*��ע��
  ******************************************************************************  
  */ 

/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _GPS_IMU_CONTROL_H
#define _GPS_IMU_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "BaseControl.h"     //Э��Ļ���

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 
//�õ�ع���ʱ���2�� �õ�ع��������
// #define SUB_VOLTAGE 10

#ifdef SUB_VOLTAGE 
	//����������ѹ>24�� ʵ����26��
	#define  NORMAL_VOLTAGE				(130-SUB_VOLTAGE)
	//�����ѹ>23�� ʵ����25��
	#define  WARNING_VOLTAGE			(125-SUB_VOLTAGE)
	//Σ�յ�ѹ>22�� ʵ����24��
	#define  DANGER_VOLTAGE				(120-SUB_VOLTAGE)
	//ʧ�ܵ�ѹ>21�� ʵ����23��
	#define  DISABILITY_VOLTAGE		(115-SUB_VOLTAGE)
#else
	#define  NORMAL_VOLTAGE				130
	#define  WARNING_VOLTAGE			125
	#define  DANGER_VOLTAGE				120
	#define  DISABILITY_VOLTAGE		115
#endif


class GpsImuControl : public BaseControl
{
public:
	GpsImuControl(SerialPort * p);
	virtual ~GpsImuControl();
	void sendsetLEDColorCommand();
	void setPowerLEDColor(uint8_t);
	void setPowerLEDColorFromVoltage(uint8_t);
	
private:
	uint8_t powerLEDColor;
	
};
#endif  /*_GPS_IMU_CONTROL_H */


