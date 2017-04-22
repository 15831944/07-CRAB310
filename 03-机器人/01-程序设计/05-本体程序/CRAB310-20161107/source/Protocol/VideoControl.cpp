/* ͷ�ļ����� ------------------------------------------------------------------*/
#include "VideoControl.h"


/* ���Ͷ��� --------------------------------------------------------------------*/
/* �궨��-----------------------------------------------------------------------*/
  
//���캯��
VideoControl::VideoControl(SerialPort * p)
{
	port=p; 
}

//��������
VideoControl::~VideoControl()
{
	delete port;
} 
 /**
  * ��  �ܣ����ͱ佹ָ��
  * ��  ����STOP 0x00;TELE 0x01;WIDE 0x02
  * ����ֵ����
  * 
  */
void VideoControl::sendVideoCommand(uint8_t data1)				 
{
	uint8_t buf[2] = {0};
	uint8_t i=0;

	buf[i++] = 0x00; 
	buf[i++] = data1;   
	
	port->write(buf,i); 
}

 /**
  * ��  �ܣ����ͻ����л�ָ��
  * ��  ����0x81,��һ���棻0x82,�ڶ����棻0x9b�����»���ָ
  * ����ֵ����
  * 
  */
void VideoControl::sendVideoChannel(uint8_t cmd)				 
{
	sendVideoCommand(cmd); 
} 







