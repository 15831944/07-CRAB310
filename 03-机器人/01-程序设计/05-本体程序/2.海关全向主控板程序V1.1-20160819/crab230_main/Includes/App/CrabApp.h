 /* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _CRAB_APP_H
#define _CRAB_APP_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "MotorControl.h" 
#include "TerminalControl.h" 
#include "Timer.h"
#include "LEDLighter.h" 
#include "CamControl.h"
#include "VideoControl.h"
#include "Key.h"
#include "Mpu6050Control.h"
#ifdef __cplusplus  
extern "C"
{
#endif
	#include "STM32_Adc.h"
	#include "STM32F4_GpioInit.h"
 	#include "STM32F4_PwmOut.h" 
#ifdef __cplusplus
}
#endif
/* ���Ͷ��� --------------------------------------------------------------------*/
//ö��ģʽID
/* �궨��-----------------------------------------------------------------------*/ 
//����ֵ��
#define ABS(X)			((X)>0?(X):(-(X)))
//���߾���ֵ˭��˭С��
#define MAX(X,Y)		((ABS(X))>(ABS(Y))?(ABS(X)):(ABS(Y)))
#define MIN(X,Y)		((ABS(X))<(ABS(Y))?(ABS(X)):(ABS(Y)))
//֡����
#define TERMINAL_FRAME_LEN 10
//ȫ����������
#define WHEEL_NUM 4
//�ٶȵ�λ����
#define SPEED_KK 4
//�ٶȵ�λ����
#define SPEED_MAX 8000
//�Զ�ģʽ���� 
#define MODE_AUTO_FINISH  	0x02 
#define MODE_AUTO 					0x01
#define MODE_MANUAL  				0x00

#define AUTO_RUN_SPEED 			1000
#define AUTO_TURN_SPEED 		100
//����״̬
#define INFRA_ON   		0x00
#define INFRA_OFF			0x01
#define KEYINDEX_MAX 	10
//4�������ַ�Ķ���
#define LEFTUP_DDR  		0
#define LEFTDOWN_DDR		1
#define RIGHTUP_DDR			2
#define RIGHTDOWN_DDR		3
//Ĭ�ϵ���̨Ĭ��PWM
#define DEFAULT_PWM 		100
//���������źų�ʱʱ��
#define TICKET_MAX  		2000
//ҡ����������
#define MOVE_MID				0X80  //128
#define MOVE_MID1				0X66  //112
#define MOVE_MID2				0X98  //144
#define MOVE_DEADAREA 	25
//�������ú� 
#define		WIRE_LESS_PORT_NUM			2
#define		WHEEL_PORT_NUM					3
#define		CAM_PORT_NUM						4
#define		VIDEO_PORT_NUM					5 
#define		MPU6050_PORT_NUM				6 

#define		WIRE_LESS_PORT_BAUD		9600
#define		WHEEL_PORT_BAUD				38400
#define		CAM_PORT_BAUD					9600
#define		VIDEO_PORT_BAUD				9600 
#define		MPU6050_PORT_BAUD			115200 
//������ʾ���
#define POW_LED_TICK1  60
#define POW_LED_TICK2  30

class CrabApp
{
public:
	CrabApp();
	~CrabApp();
	void openUserInterrupt();
	void runOnTime2();								//�����ڶ�ʱ��TIM2�еĺ���
	void runOnTime3();								//�����ڶ�ʱ��TIM3�еĺ���
	void runOnTime4();								//�����ڶ�ʱ��TIM4�еĺ��� 
private:
	int16_t *wheelspeed;
	uint8_t *fBTerminalData;
	Timer *t1;												//��ʱ��1
	Timer *t2;												//��ʱ��2
	Timer *t3;												//��ʱ��3

	LEDLighter *led_1; 
	LEDLighter *led_2;
  LEDLighter *led_3;

	SerialPort *wireLessPort;				//���ն�����ͨ�ŵĴ���
	SerialPort *wheelPort;					//��4�������ֵĴ���
	SerialPort *camPort;						//���г����ͨ�ŵĴ���
	SerialPort *videoPort;					//��4�����л���ͨ�ŵĴ���
	SerialPort *mpu6050Port;					//��4�����л���ͨ�ŵĴ���

	TerminalControl *Terminal;								//�ն�ͨ�ŵ�Э�������
	Mpu6050Control *mpu6050;
	Key *infra;
  
	MotorControl *frontLeftMotor;							//���ϵ��
	MotorControl *rearLeftMotor;							//���µ��
	MotorControl *frontRightMotor;						//���ϵ��
	MotorControl *rearRightMotor;							//���µ�� 
	
	ctrData *fBEctQuantity_1;									//�����ĵ�Դ����1�ݴ�
	ctrData *fBEctQuantity_2;									//�����ĵ�Դ����2�ݴ�
	
  uint8_t workmode;
	uint8_t workmodesta;
	uint8_t autotime;
	bool rockeysta;
	bool turnstartflag;
	uint8_t infrasta;
	int16_t robotangle;
	uint8_t camlenscommand;
  uint8_t zoomstatus;
	CamControl *driverCam;
	uint8_t videochannel;
	VideoControl *videocont;
 
	float leftbatvoltage;				//���ص���
	float rightbatvoltage;				//�ҵ�ص���
 
 	int16_t pantitlepwm; 
	
	bool recflag;
private:
	
  	void resetvaule();
  	void disposeTerminalData();
  	void updateSendTerminalData();								//����Ҫ���͵��ն˵�����
		void sendDriverMotorData();
		void sendCamData();
		void sendVideoChangeData();
  	void updateSendDriverData();									//����Ҫ���͵������豸������
		void lightcontrol(uint8_t* recdata);
		int16_t wheelspeedcal(int16_t speeddata,int16_t speedKK);
		int16_t setwheelspeed(int16_t *wheelsp,int16_t *speedref,int16_t speedK);
		void mecanumwheelcontrol(uint8_t* recdata);
		void cradlecontrol(uint8_t* recdata);
		void fpvchannelconf(uint8_t channel);
		void fpvchannelchange(uint8_t* recdata); 
		void radiochannelchange(uint8_t* recdata);
		void camlencontrol(uint8_t* recdata); 
		void videochanelcontrol(uint8_t* recdata);
		uint8_t workmodedetect(uint8_t* recdata);
		void autoruncontrol();
		uint8_t autoturncontrol();
		void infrascan();
		float subEctQuantity(float* leftbat,float* rightbat);
		void powerledshow(float batvaule);
};
#endif 









