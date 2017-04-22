/**
  ******************************************************************************
	*�ļ���MotorControl.c
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ�����Э�����ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 



/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "MotorControl.h"

/* ���Ͷ��� --------------------------------------------------------------------*/
/* �궨��-----------------------------------------------------------------------*/ 

//����ֵ��
#define ABS(X)			((X)>0?(X):(-(X)))

//���е�ָ��λ�õĽǶ���Χ����2�ȣ�
#define ANGLE_ALLOWANCE 	50 

//�����ٽ�λ

#define ANGLE_SLOW_START	700
#define ANGLE_SLOW_GO			450
#define ANGLE_SLOW_DOWN		200



//���캯��
MotorControl::MotorControl(SerialPort * p):BaseControl(p)
{
	feedSpeed=0;								//��Ҫ���õ��ٶ��ݴ�	
	referSpeedMax=0;						//��Ҫ���õĲο�����ٶ�
	referSpeedMin=0;						//��Ҫ���õĲο���С�ٶ�	
	feedPWMSpeed=0;
	feedAngle=0;								//��Ҫ���õĽǶ��ݴ�
	feedZeroAngle=0;						//��Ҫ���õ���λ�Ƕ��ݴ�
	feedAngleMaxSpeed=0;				//��Ҫ���õĽǶ��ݴ�

	feedMaxSpeed=0;							//��Ҫ���õ�����ٶ��ݴ�
	feedCodedDiscLineNum=0;			//��Ҫ�������������ݴ�
	feedReductionRatio=0;				//��Ҫ���ü��ٱ��ݴ�
	feedAcceleration=0;			  	//��Ҫ���ü��ٶ��ݴ�
	feedDeceleration=0;			 	 	//��Ҫ���ü��ٶ��ݴ�
	feedCurrent=0;			  			//��Ҫ���õ����ݴ�
	feedContinuousCurrent=0;		//��Ҫ���õ�������ֵ�ݴ�
	feedPeakCurrent=0;					//��Ҫ���õ�����ֵ�ݴ�
	
	feedSpeed=0;								//��Ҫ���õ��ٶ��ݴ�	
	referSpeedMax=0;						//��Ҫ���õĲο�����ٶ�
	referSpeedMin=0;						//��Ҫ���õĲο���С�ٶ�
	uspeedTime=0;								//uָ��������ʱ�����
	resetUspeedTime();
}

//��������
MotorControl::~MotorControl()
{
// 	char* sss="���Э���������ɹ���\r\n";
// 	port->writeLine(sss);
}

/**
  * ��  �ܣ������ٶȿ���ָ����������
  * ��  ����CommandType ����ı�ţ��ȿ��Ƶ�����
	* ����ֵ��0x01:�����ٶȣ����ش������ؽǶ�ֵ
	*					0x02:�����ٶȣ�����OK
	*					0x03:���������ٶȣ�����OK
	*					0x04:��������ٶ� ����OK
	*					0x05:������������ ����OK
	*					0x06:�����ܼ��ٱ� ����OK
	*					0x07:���ü��ٶ� ����OK
	*					0x08:���ü��ٶ� ����OK
	*					0x09:��ȡ�ٶ� �����ٶ�
	*					0x0a:��ȡ�¶� �����¶�
	*					0x0b:�������� ����OK
	*					0x0c:ʹ���˶� ���ؽǶ�
  * ����ֵ��
  * 
  */
void MotorControl::sendSpeedCommand(int8_t CommandType)		//�����ٶ����� �����������ţ���������ͣ�
{
	if(CommandType<0x01||CommandType>0x0c) 									//��������Χ
		return;
	uint8_t tem=(uint8_t)CommandType;
	command&=0x00;
	command|=tem;
	switch(tem)
	{
		case 0x01:																					//�����ٶȣ����ش������ؽǶ�ֵ
		case 0x02:																					//�����ٶȣ�����OK
			data->DATA_16=feedSpeed;
			break;
		case 0x03:																					//���������ٶ�(PWM����)������OK
			data->DATA_16=feedPWMSpeed;
			break;
		case 0x04:																					//��������ٶ� ����OK
			data->DATA_16=feedMaxSpeed;
			break;
		case 0x05:																					//������������ ����OK
			data->DATA_16=feedCodedDiscLineNum;
			break;
		case 0x06:																					//�����ܼ��ٱ� ����OK
			data->DATA_16=feedReductionRatio;	
			break;
		case 0x07:																					//���ü��ٶ� ����OK
			data->DATA_16=feedAcceleration;
			break;
		case 0x08:																					//���ü��ٶ� ����OK
			data->DATA_16=feedDeceleration;
			break;
		case 0x09:																					//��ȡ�ٶ� �����ٶ�
		case 0x0a:																					//��ȡ�¶� �����¶�
		case 0x0b:																					//�������� ����OK
		case 0x0c:																					//ʹ���˶� ���ؽǶ�
			data->DATA_16=0x0000;
			break;
		default:
			break;
	}
	sendCommand();	//��������������ϣ���������
	numCounter++;
	if(numCounter>21)
	{
		numCounter=21;
	}
}


/**
  * ��  �ܣ����͵�������ָ����������
  * ��  ����CommandType ����ı�ţ��ȿ��Ƶ�����
	* ����ֵ��0x01:���õ���������OK
	*					0x02:������㿪��������OK
	*					0x03:�������㣬����OK
	*					0x04:�������У׼����������OK
	*					0x05:�������У׼������OK
	*					0x06:�������У׼����������OK
	*					0x07:�������У׼������OK
	*					0x08:����У׼�洢������OK
	*					0x09:���ó�������������OK
	*					0x0a:���÷�ֵ����������0K
	*					0x0b:��ȡ���������ص���
  * ����ֵ����
  * 
  */
void MotorControl::sendCurrentCommand(int8_t CommandType)	//���͵������� �����������ţ���������ͣ�
{
	if(CommandType<0x01||CommandType>0x0b) //��������Χ
		return;
	uint8_t tem=(uint8_t)CommandType;
	command&=0x00;
	command|=0x10;												//�������λ��Ϊ��������
	command|=tem;
	switch(tem)
	{
		case 0x01:																					//���õ���������OK
			data->DATA_16=feedCurrent;
			break;
		case 0x02:																					//������㿪��������OK
		case 0x03:																					//�������㣬����OK
		case 0x04:																					//�������У׼����������OK
		case 0x05:																					//�������У׼������OK
		case 0x06:																					//�������У׼����������OK
		case 0x07:																					//�������У׼������OK
		case 0x08:																					//����У׼�洢������OK
			data->DATA_16=0x0000;
			break;			
		case 0x09:																					//���ó�������������OK
			data->DATA_16=feedContinuousCurrent;
			break;
		case 0x0a:																					//���÷�ֵ����������0K
			data->DATA_16=feedPeakCurrent;
			break;
		case 0x0b:																					//��ȡ���������ص���
			data->DATA_16=0x0000;
			break;
		default:
			break;
	}
	sendCommand();	//��������������ϣ���������
}


/**
  * ��  �ܣ����ͽǶȿ���ָ����������
  * ��  ����CommandType ����ı�ţ��ȿ��Ƶ�����
	* ����ֵ��0x01:���е���Ӧ�ĽǶȣ�����0K
	*					0x02:������λʧЧ������0K
	*					0x03:���������λ������0K
	*					0x04:������С��λ������0K
	*					0x05:���õ�ǰ�ĽǶ�ֵΪ�ο�ֵ������0K �ϰ汾0x06
	*					0x06:���浱ǰ�Ƕȣ�����0K	 �ϰ汾0x07
	*					0x07:��ȡ�Ƕȣ����ؽǶ� �ϰ汾0x08
	*					0x08:����λ���˶�������ٶȣ�����0K  �ϰ汾0x09
  * ����ֵ��
  * 
  */
void MotorControl::sendAngleCommand(int8_t CommandType)		//���ͽǶ����� �����������ţ���������ͣ�
{
	if(CommandType<0x01||CommandType>0x09) //��������Χ //�˴��°�Э����Ҫ�޸ĳ�0x08****************
		return;
	uint8_t tem=(uint8_t)CommandType;
	command&=0x00;
	command|=0x20;												//�������λ��Ϊ�Ƕȷ���
	command|=tem;
	if(tem==0x01)
	{
		data->DATA_16=feedAngle;
	}
	else if(tem==0x06)
	{
		data->DATA_16=feedZeroAngle;
	}
	else if(tem==0x09)									//�˴��°�Э����Ҫ�޸ĳ�0x08**********************************
	{
		data->DATA_16=feedAngleMaxSpeed;
	}
	else
	{
		data->DATA_16=0x0000;
	}
	sendCommand();	//��������������ϣ���������
}

/**
  * ��  �ܣ������ٶ�
  * ��  �����ٶȵĲο�ֵ
  * ����ֵ����
  * 
  */
void MotorControl::setSpeed(int16_t value)
{
	int16_t temValue=value;
	if(temValue>0&&temValue<200)
	{
		temValue=200;
	}
	else if(temValue<0&&temValue>-200)
	{
		temValue=-200;
	}
	feedSpeed=temValue;
}

void MotorControl::setSpeed_1(int16_t value)
{
	int16_t temValue=value;
	feedSpeed=temValue;
}
/**
  * ��  �ܣ����ݽǶȲ��ʱ��������ٶ�
  * ��  ����
					subA:			�ǶȲ�
					sunT:			ʱ���
					sunMAXT:	ʱ�������ֵ
  * ����ֵ����
  * 
  */
void MotorControl::setSpeedFromSubAngle(int64_t subA,int64_t sunT,int64_t sunMaxT)
{
	if(ABS(subA)>ANGLE_ALLOWANCE)//����� ��0.5 ��
	{
		
		if(ABS(subA)>ANGLE_SLOW_START) 
			setSpeed((int16_t)(((int64_t)referSpeedMax)*sunT/sunMaxT));	  //һ���ٶ� ����ٶ� 
		else if(ABS(subA)>ANGLE_SLOW_GO) 
			setSpeed((int16_t)(((int64_t)referSpeedMin)*18*sunT/sunMaxT));//�����ٶ� ����ٶȵ�9/10
		else if(ABS(subA)>ANGLE_SLOW_DOWN) 
			setSpeed((int16_t)(((int64_t)referSpeedMin)*15*sunT/sunMaxT));	//�����ٶ� ����ٶȵ�3/4
		else															 
			setSpeed((int16_t)(((int64_t)referSpeedMin)*5*sunT/sunMaxT));		//�ļ��ٶ� ����ٶȵ�1/2
	}
	else																													//�Ƕȵ���λ�� ���ٶ�0
	{
		resetSpeed();
	}
}
/**
  * ��  �ܣ����ݽǶȲ��ʱ��������ٶ� �ú���û������
  * ��  ����
					subA:			�ǶȲ�
					sunT:			ʱ���
					sunMAXT:	ʱ�������ֵ
  * ����ֵ����
  * 
  */
void MotorControl::setSpeedFromSubAngle_1(int64_t subA,int64_t sunT,int64_t sunMaxT)
{
	if(ABS(subA)>5)//����� ��0.5 ��
	{
			setSpeed_1((int16_t)(((int64_t)referSpeedMax)*sunT/sunMaxT));	  //һ���ٶ� ����ٶ� 
	}
	else																													//�Ƕȵ���λ�� ���ٶ�0
	{
		resetSpeed();
	}
}
/**
  * ��  �ܣ��ص���ʽʵ�� ���ݽǶȲ������ٶ�
  * ��  ����
	*				fun��			�ص�����ָ��
	*				subA:			�ǶȲ�
	*				sunT:			ʱ���
	*				sunMAXT:	ʱ�������ֵ
  * ����ֵ����
  * 
  */
void MotorControl::setSpeedFromSubAngle(setSpeedFun fun,int64_t subA,int64_t sunT,int64_t sunMaxT)	//���ݽǶȲ������ٶ�
{
	if(ABS(subA)>ANGLE_ALLOWANCE)//����� ��0.5 ��
	{
// 		setSpeed((int16_t)(((int)referSpeedMin)*5*sunT/sunMaxT));		//�ļ��ٶ� ����ٶȵ�1/2
		if(ABS(subA)>ANGLE_SLOW_START)//�ǶȲ�10������
			fun((int16_t)(((int64_t)referSpeedMax)*sunT/sunMaxT));
		else if(ABS(subA)>ANGLE_SLOW_GO)//4.5-10
			fun((int16_t)(((int64_t)referSpeedMin)*18*sunT/sunMaxT));
		else if(ABS(subA)>ANGLE_SLOW_DOWN)//2.0-4.5
			fun((int16_t)(((int64_t)referSpeedMin)*15*sunT/sunMaxT));
		else
			fun((int16_t)(((int64_t)referSpeedMin)*5*sunT/sunMaxT));
	}
	else								//�ٶ���0
	{
		resetSpeed();
	}
}

/**
  * ��  �ܣ�����Uָ��ʱ�䣬�����Զ�ʵ�ֵ�����ͷ�
  * ��  ������
  * ����ֵ����
  * 
  */
void MotorControl::updateUspeedTime()										//����Uָ��ʱ��
{
	
	if(feedSpeed==0)
		uspeedTime++;
	else
	{
		feedPWMSpeed=0;
		uspeedTime=0;
	}
	if(uspeedTime>3500)                                //����Uָ�����ʱ��3500-UO_TIME_MAX=3��
	{
		uspeedTime=UO_TIME_MAX;
		feedPWMSpeed=0;
	}
}

/**
  * ��  �ܣ������ٶ����� ���Ը��ݳ�ʱ�����Զ��ж�V �� u
  * ��  ������
  * ����ֵ����
  * 
  */
void MotorControl::sendSpeedCommand()
{
	if(uspeedTime<UO_TIME_MAX)
		sendSpeedCommand(0x01);
	else
		sendSpeedCommand(0x03);
}





