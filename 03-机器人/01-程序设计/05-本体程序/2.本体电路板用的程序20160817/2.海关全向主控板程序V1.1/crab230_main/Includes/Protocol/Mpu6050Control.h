 
/* �����ֹ�ݹ�����Ŀ��ƺ�----------------------------------------------------*/
#ifndef _MPU6050_CONTROL_H
#define _MPU6050_CONTROL_H

/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "SerialPort.h"
#include "DataChain.h"
 
typedef struct 
{
    int16_t accl[3];
    int16_t gyro[3];
    int16_t mag[3];
    int16_t yaw;
    int16_t pitch;
    int16_t roll;
    int32_t presure;
}imu_data;


class Mpu6050Control  
{
public:
	Mpu6050Control(SerialPort * p);
	virtual ~Mpu6050Control();  
	uint8_t* getReciveData(){return reciveBuf;}
	int16_t  getRoatAngle(){return angleX;}
	bool imureciveData(SerialPort *port);
	bool dealrecData();
private:
	SerialPort *port;  
	RingChain *reciveChin;
	uint8_t *sendBuf; 
	uint8_t *reciveBuf;
  int16_t angleX;
	imu_data *imudata;
};
#endif   
