
#ifndef CYQUEUE_H
#define CYQUEUE_H

#define QUEUESIZE  13
typedef unsigned char ElemType;

typedef struct 
{
	ElemType data[QUEUESIZE];  //�������Ԫ��
	int front,rear;   //��ͷ�Ͷ�β
}SqQueue;


class CyQueue
{
public:
	CyQueue();
	void ClearQueue();
	int EnQueue(ElemType x);  //���
	int DeQueue(ElemType &x);   //����
	int GetHead(ElemType &x);   //��ȡͷԪ��
	int IsEmpty();    //�ж�Ϊ��
	int IsFull();  //�ж϶���

public:
	SqQueue qu;

};


#endif