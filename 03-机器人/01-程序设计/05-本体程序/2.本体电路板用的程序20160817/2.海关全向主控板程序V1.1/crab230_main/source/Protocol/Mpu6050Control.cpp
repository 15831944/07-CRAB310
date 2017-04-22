/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "Mpu6050Control.h"

/* ���Ͷ��� --------------------------------------------------------------------*/

/* �궨��-----------------------------------------------------------------------*/ 
//����֡���Ⱥ�
#define SEND_BUF_LEN 						10
#define RECIVE_BUF_LEN 					32 
 

//���캯��
Mpu6050Control::Mpu6050Control(SerialPort * p1)
{
	port=p1;  
	reciveChin=new RingChain(RECIVE_BUF_LEN); 
	reciveBuf=new uint8_t[RECIVE_BUF_LEN]; 
	for(int i=0;i<RECIVE_BUF_LEN;i++)
	{
		reciveBuf[i]=0;
	}	
	imudata = new imu_data;
}


//��������
Mpu6050Control::~Mpu6050Control()
{
	delete reciveChin;
	delete [] sendBuf;
	delete [] reciveBuf;
	delete imudata;
}
 

/**
  * ��  �ܣ����տ����ն˵�����
  * ��  �����������ݵĴ���
  * ����ֵ��
			true:�ɹ�����һ֡
			false:û�н��յ�һ֡����
  */
//88 AF 1C 00 1D FF 63 10 11 00 00 00 00 00 00 00 00 00 00 00 00 FF E4 FF 05 06 F1 FF 00 FF FF CF 
bool Mpu6050Control::imureciveData(SerialPort *port)
{
	uint8_t checkSum=0;
	bool readFlag=false;
  //���մ�������
	while (port->readAllow()&&(readFlag==false))
	{
		reciveChin->setData(port->getChar());
		reciveChin->next();
		if(reciveChin->getData()==0x88)//���֡ͷ	
		{	
			checkSum+=0x88;
			reciveChin->next();
			if(reciveChin->getData()==0xAF)//���֡ͷ	
			{
				for(int i=0;i<(RECIVE_BUF_LEN-3);i++)
				{
					 checkSum+=reciveChin->getData();
					 reciveChin->next();
				}
				reciveChin->next();
				if(checkSum==reciveChin->getData())//У�����ȷ
				{
					//�����ݴ�������
					for(int i=0;i<RECIVE_BUF_LEN;i++)
					{
						 reciveChin->next();
						 reciveBuf[i]=reciveChin->getData();
					}
					readFlag=true;
				}
				reciveChin->next(); 
			}
		  else
			{
				 reciveChin->previous();//�����ϸ��ڵ�	
			}			
		 	checkSum=0;
		}	
	}
	return 	readFlag;
}
 

/**
  * ��  �ܣ�������յ�������
  * ��  �����������ݵĴ���
  * ����ֵ��
			true:�ɹ�����һ֡
			false:û�н��յ�һ֡����
  */
bool Mpu6050Control::dealrecData()
{
	uint8_t i=0;
	float acc[3],angular[3],angle[3],tempature;
	bool tempFlag = false;  
	
	tempFlag = imureciveData(port);
	if(tempFlag==true)
	{  
// 		switch(reciveBuf[1])
// 		{
// 			 case 0x51: //��ʶ������Ǽ��ٶȰ�
// 					acc[0] 			= ((short)(reciveBuf[3]<<8 | reciveBuf[2]))/32768.0*16;      //X����ٶ�
// 					acc[1] 			= ((short)(reciveBuf[5]<<8 | reciveBuf[4]))/32768.0*16;      //Y����ٶ�
// 					acc[2] 			= ((short)(reciveBuf[7]<<8 | reciveBuf[6]))/32768.0*16;      //Z����ٶ�
// 					tempature   = ((short)(reciveBuf[9]<<8 | reciveBuf[8]))/340.0+36.25;      //�¶�
// 					break;
// 			 case 0x52: //��ʶ������ǽ��ٶȰ�
// 					angular[0] 	= ((short)(reciveBuf[3]<<8| reciveBuf[2]))/32768.0*2000;      //X����ٶ�
// 					angular[1] 	= ((short)(reciveBuf[5]<<8| reciveBuf[4]))/32768.0*2000;      //Y����ٶ�
// 					angular[2] 	= ((short)(reciveBuf[7]<<8| reciveBuf[6]))/32768.0*2000;      //Z����ٶ�
// 					tempature   = ((short)(reciveBuf[9]<<8| reciveBuf[8]))/340.0+36.25;      	//�¶�
// 					break;
// 			 case 0x53: //��ʶ������ǽǶȰ�
// 					angle[0] 		= ((short)(reciveBuf[3]<<8| reciveBuf[2]))/32768.0*180;   		//X���ת�ǣ�x �ᣩ
// 					angle[1] 		= ((short)(reciveBuf[5]<<8| reciveBuf[4]))/32768.0*180;   		//Y�ḩ���ǣ�y �ᣩ
// 					angle[2] 		= ((short)(reciveBuf[7]<<8| reciveBuf[6]))/32768.0*180;   		//Z��ƫ���ǣ�z �ᣩ
// 					tempature   = ((short)(reciveBuf[9]<<8| reciveBuf[8]))/340.0+36.25;   		//�¶� 
// 					break;
// 			 default:  break;
// 		} 
//֡ͷ��0x88,0xAF;���ȣ�LEN��
		i = 3;
    imudata->accl[0] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->accl[1] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->accl[2] = (reciveBuf[i++]<<8) + reciveBuf[i++];

    imudata->gyro[0] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->gyro[1] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->gyro[2] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    
    imudata->mag[0] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->mag[1] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->mag[2] = (reciveBuf[i++]<<8) + reciveBuf[i++];
    
    imudata->roll 	= (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->pitch 	= (reciveBuf[i++]<<8) + reciveBuf[i++];
    imudata->yaw 		= (reciveBuf[i++]<<8) + reciveBuf[i++];
    
    imudata->presure =  (reciveBuf[i++]<<0)+ (reciveBuf[i++]<<8)+ (reciveBuf[i++]<<16)+(reciveBuf[i++]<<24);
// 		GPIO_WriteBit(GPIOE, GPIO_Pin_13, (BitAction)(1 - GPIO_ReadOutputDataBit(GPIOE, GPIO_Pin_13)));
	}
	angleX = (int16_t)imudata->yaw; 
	return tempFlag;
}

 