/**
  ******************************************************************************
	*�ļ���MotorControl.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ�����Э�����ͷ�ļ�
	*��ע��
	*
  ******************************************************************************  
	*/ 
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "BaseControl.h"     //Э��Ļ���

/* ���Ͷ��� --------------------------------------------------------------------*/
typedef uint8_t(*setSpeedFun)(int16_t);
/* �궨��-----------------------------------------------------------------------*/ 
//U0ָ��͵��ٽ�ʱ��
#define UO_TIME_MAX				500


class MotorControl : public BaseControl
{
public:
	MotorControl(SerialPort * p);
	virtual ~MotorControl();

	void updateUspeedTime();										//����Uָ��ʱ��
	void sendSpeedCommand();										//�����ٶ����� ���Ը��ݳ�ʱ�����Զ��ж�V �� u

	void sendSpeedCommand(int8_t);							//�����ٶ����� �����������ţ���������ͣ�
	void sendCurrentCommand(int8_t);						//���͵������� �����������ţ���������ͣ�
	void sendAngleCommand(int8_t);							//���ͽǶ����� �����������ţ���������ͣ�

	void setSpeedFromSubAngle(int64_t,int64_t,int64_t);			//���ݽǶȲ������ٶ�
	void setSpeedFromSubAngle_1(int64_t,int64_t,int64_t);			//���ݽǶȲ������ٶ�
	void setSpeed(int16_t);
	void setSpeed_1(int16_t);
	void setPWMSpeed(int16_t value){feedPWMSpeed=value;}

	void setAngle(int16_t value)								{feedAngle=value;}
	void setZeroAngle(int16_t value)						{feedZeroAngle=value;}
	void setAngleMaxSpeed(int16_t value)				{feedAngleMaxSpeed=value;}

	void setMaxSpeed(int16_t value)							{feedMaxSpeed=value;}
	void setCodedDiscLineNum(int16_t value)			{feedCodedDiscLineNum=value;}
	void setReductionRatio(int16_t value)				{feedReductionRatio=value;}
	void setAcceleration(int16_t value)					{feedAcceleration=value;}
	void setDeceleration(int16_t value)					{feedDeceleration=value;}
	void setCurrent(int16_t value)							{feedCurrent=value;}
	void setContinuousCurrent(int16_t value)		{feedContinuousCurrent=value;}
	void setPeakCurrent(int16_t value)					{feedPeakCurrent=value;}
	void setReferSpeedMax(int16_t value)				{referSpeedMax=value;}
	void setReferSpeedMin(int16_t value)				{referSpeedMin=value;}
	void resetUspeedTime(){uspeedTime=UO_TIME_MAX;}
	int16_t getSpeed(){return feedSpeed;}
	int16_t getPWMSpeed(){return feedPWMSpeed;}
	int16_t getPWMSpeedTime(){return uspeedTime;}
	void setReferMaxSpeed(bool direction)
	{
		if(direction)
			feedSpeed=referSpeedMin;
		else
			feedSpeed=-referSpeedMin;
	}
	
	
// 						{feedSpeed=(direction?referSpeedMax:(-referSpeedMax));}
	void setReferMinSpeed(bool direction)						{feedSpeed=(direction?referSpeedMin:(-referSpeedMin));}
	
	void resetSpeed(){feedSpeed=0;}
  void setSpeedFromSubAngle(setSpeedFun,int64_t,int64_t,int64_t);	//���ݽǶȲ������ٶ�
protected:
	int16_t uspeedTime;								//uָ��������ʱ�����
	int16_t feedAngle;								//��Ҫ���õĽǶ��ݴ�
	int16_t feedZeroAngle;						//��Ҫ���õ���λ�Ƕ��ݴ�
	int16_t feedAngleMaxSpeed;				//��Ҫ���õĽǶ��ݴ�
	int16_t feedSpeed;								//��Ҫ���õ��ٶ��ݴ�
	int16_t feedPWMSpeed;							//��Ҫ����PWMռ�ձȲ���
	int16_t feedMaxSpeed;							//��Ҫ���õ�����ٶ��ݴ�
	int16_t feedCodedDiscLineNum;			//��Ҫ�������������ݴ�
	int16_t feedReductionRatio;				//��Ҫ���ü��ٱ��ݴ�
	int16_t feedAcceleration;			  	//��Ҫ���ü��ٶ��ݴ�
	int16_t feedDeceleration;			 	 	//��Ҫ���ü��ٶ��ݴ�
	int16_t feedCurrent;			  			//��Ҫ���õ����ݴ�
	int16_t feedContinuousCurrent;		//��Ҫ���õ�������ֵ�ݴ�
	int16_t feedPeakCurrent;					//��Ҫ���õ�����ֵ�ݴ�	

	int16_t referSpeedMax;						//��Ҫ���õĲο�����ٶ�
	int16_t referSpeedMin;						//��Ҫ���õĲο���С�ٶ�
};
#endif  /*_MOTOR_CONTROL_H */


