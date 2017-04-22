/**
  ******************************************************************************
	*�ļ���OtherDeviceControl.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������һЩ�豸�Ŀ���Э�����ʵ��
	*��ע��
  ******************************************************************************  
  */ 


/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "OtherDeviceControl.h"

/* ���Ͷ��� --------------------------------------------------------------------*/
/* �궨��-----------------------------------------------------------------------*/ 

//OtherDeviceControl�๹�캯��
OtherDeviceControl::OtherDeviceControl(SerialPort * p):BaseControl(p)
{
	addr=0X09;
	command|=0X31;
	floodLightFlag=false;
	headLightFlag=false;
	powerPilotLampFlag=false;
	laserSightFlag=false;
}

//OtherDeviceControl����������
OtherDeviceControl::~OtherDeviceControl()
{
	
}

/**
  * ��  �ܣ�����������������
  * ��  ������
  * ����ֵ����
  * 
  */
void OtherDeviceControl::sendWeaponControlCommand()
{
	uint8_t weaponCommand[6]={0XA4,0X09,0X32,0XB5,0XF5,0X89};
	port->write(weaponCommand,6);
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}

/**
  * ��  �ܣ�����������������
  * ��  ������
  * ����ֵ����
  * 
  */
void OtherDeviceControl::sendGunControlCommand()
{
	uint8_t weaponCommand[6]={0XA4,0X09,0X32,0XA5,0XE5,0X69};
	port->write(weaponCommand,6);
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}

/**
  * ��  �ܣ����������豸��������
  * ��  ������
  * ����ֵ����
  * 
  */
void OtherDeviceControl::sendOtherDeviceCommand()							//���������豸��������
{
	data->DATA_16=0x0000;
	if(powerPilotLampFlag)
		data->DATA_8[1]|=0x01;
	else
		data->DATA_8[1]&=0xfe;
	
	if(laserSightFlag)
		data->DATA_8[1]|=0x20;
	else
		data->DATA_8[1]&=0xdf;
	
	if(floodLightFlag)
		data->DATA_8[1]|=0x40;
	else
		data->DATA_8[1]&=0xbf;
	
	if(headLightFlag)
		data->DATA_8[1]|=0x80;
	else
		data->DATA_8[1]&=0x7f;
	
	data->DATA_8[0]|=videoZoom;
	data->DATA_8[0]|=(uint8_t)(videoSelectFlag<<5);
	sendCommand();	//��������������ϣ���������
	numCounter++;
	if(numCounter>20)
	{
		numCounter=20;
	}
}


/**
  * ��  �ܣ������ķ���ͼ��ѡ��
  * ��  ������������
	* ����ֵ��0x00:��̨ͼ����ʾ
	*					0x01:��ץͼ����ʾ
	*					0x02:ǰ��ͼ����ʾ
	*					0x03:����ͼ����ʾ
	*					0x04:�ķ���ͼ����ʾ
  * ����ֵ����
  */
void OtherDeviceControl::setVideoSelect(uint8_t value)
{
	if(value<5)
		videoSelectFlag=value;
}
/**
  * ��  �ܣ�������̨ͼ��佹����
  * ��  �����佹����
  * ����ֵ����
  */
void OtherDeviceControl::setVideoZoom(uint8_t value)
{
	if(value<32)
		videoZoom=value;
}

/**
  * ��  �ܣ����������Ƶ�����״̬
  * ��  ������������
	* ����ֵ��false:������Ϩ��
	*					true :�����Ƶ���
  * ����ֵ����
  */
void OtherDeviceControl::setFloodLight(bool value)
{
	floodLightFlag=value;
}

/**
  * ��  �ܣ�������̨�����Ƶ�����״̬
  * ��  ������������
	* ����ֵ��false:��̨������Ϩ��
	*					true :��̨�����Ƶ���
  * ����ֵ����
  */
void OtherDeviceControl::setheadLight(bool value)
{
	headLightFlag=value;
}

/**
  * ��  �ܣ����ü�����׼�����״̬
  * ��  ������������
	* ����ֵ��false:������׼��Ϩ��
	*					true :������׼�Ƶ���
  * ����ֵ����
  */
void OtherDeviceControl::setLaserSight(bool value)
{
	laserSightFlag=value;
}
/**
  * ��  �ܣ����õ�Դָʾ�Ƶ���ɫ
  * ��  ������������
	* ����ֵ��false:��Դָʾ�Ƶ���ɫ���
	*					true :��Դָʾ�Ƶ���ɫ����
  * ����ֵ����
  */
void OtherDeviceControl::setPowerPilotLamp(bool value)
{
	powerPilotLampFlag=value;
}

