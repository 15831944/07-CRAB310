/**
  ******************************************************************************
	*�ļ���PowerControl.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ����Դ����Э���ͷ�ļ�
	*��ע��
	*
  ******************************************************************************  
	*/ 

/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _POWER_CONTROL_H
#define _POWER_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "BaseControl.h"     //Э��Ļ���

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 

class PowerControl : public BaseControl
{
public:
	PowerControl(SerialPort * p);
	virtual ~PowerControl();
	void sendPowerOnOffCommand();						//���Ϳ��ػ�����
	void sendGetEctQuantityCommand(int8_t);					//���͵�����ȡ����
	void sendGetTemperatureCommand(uint8_t);					//���͵�����ȡ����PowerControl
	void sendGetTempCommand(int8_t);								//�����¶ȶ�ȡ����
	bool checkPowerKey();														//���ػ�����
	void shutDown(){powerDown=true;}
// 	bool getPowerReadState(){return powerReadState;}
private:
	bool powerReadState;														//�ػ�״̬
	bool powerDown;
	void sendPowerOffCommand();							//���͹ػ�����
	void sendPowerOnCommand();							//���Ϳ�������
};
#endif  /*_POWER_CONTROL_H */


