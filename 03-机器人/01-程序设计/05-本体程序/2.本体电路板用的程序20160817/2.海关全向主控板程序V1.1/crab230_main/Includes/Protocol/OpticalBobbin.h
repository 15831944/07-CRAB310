/**
  ******************************************************************************
	*�ļ���OpticalBobbin.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-27
	*��Ҫ��GPS��IMU�豸�Ŀ���Э�����ͷ�ļ�
	*��ע��
  ******************************************************************************  
  */ 

/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _OPTICAL_BOBBIN_H  
#define _OPTICAL_BOBBIN_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "BaseControl.h"     //Э��Ļ���

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 

class OpticalBobbin : public BaseControl
{
public:
	OpticalBobbin(SerialPort * p);
	virtual ~OpticalBobbin();
	void setWorkStatus(uint8_t status){workStatus=status;}
	void setLeftSpeed(uint8_t speed){leftSpeed=speed;}
	void setRightSpeed(uint8_t speed){rightSpeed=speed;}
	void setWireLength(uint8_t length){wireLength=length;}
	uint8_t getWireLength(){return wireLength;}
	
	void sendOpticalBobbinCommand();

private:
	uint8_t workStatus;		//�����̵Ŀ���״̬
	uint8_t wireLength;		//�߳���ָ�������е��߳�
	uint8_t speed;				//�Զ������̵ķ����ٶ�
	uint8_t leftSpeed;		//�ҵ���ٶ�
	uint8_t rightSpeed;		//�ҵ���ٶ�
};
#endif  /*_OPTICAL_BOBBIN_H */


