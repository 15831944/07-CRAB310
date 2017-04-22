/**
  ******************************************************************************
	*�ļ���DataChain.h
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������ṹ���ͷ�ļ�
	*��ע��
	*
  ******************************************************************************  
	*/ 
#ifndef __DATA_CHAIN_H
#define __DATA_CHAIN_H

#include <stm32f4xx.h>
#include <stdlib.h>		
// #include "MySysDefine.h"

#define DATATYPE uint8_t


class ChainNode
{
	friend class RingChain;
	
private:
	ChainNode(DATATYPE value=0,ChainNode* previous=NULL,ChainNode* next=NULL)
	{
		this->data=value;
		this->m_next=next;
		this->m_previous=previous;
	}
	~ChainNode()
	{

	}
private:
	DATATYPE data;
	ChainNode *m_next;
	ChainNode *m_previous;
};



// //˫��ѭ������Ľṹ��
// typedef struct CHAIN
// {
// 	DATATYPE data;
// 	struct CHAIN *last;
// 	struct CHAIN *next;	
// } chain;


class RingChain
{
	public:
		RingChain(int);
		~RingChain();
		DATATYPE getData();
		void next();
		void previous();
		int getLen();
		void setData(DATATYPE);
	private:
		int length;
// 		ChainNode *Chains;
		ChainNode *current;
};
// //����֪�ڵ�����һ���ڵ�
// void insertAfter(DATATYPE,chain *p);


// //����֪�ڵ�ǰ����һ���ڵ�
// void insertBefore(DATATYPE,chain *p);


// //ɾ����̽ڵ㣬��p�ĺ�һ���ڵ�
// bool deleteAfter(chain *head,chain *p);


// //ɾ��ǰһ���ڵ㣬��p��ǰһ���ڵ�
// bool deleteBefore(chain *head,chain *p);


// //ɾ���ڵ㱾��
// bool deletSelf(chain *head,chain *p);


// //����һ��˫��ѭ������
// chain * creatChain(uint16_t len);	 


// //ɾ��һ��˫��ѭ������
// void deleteChain(chain *head);

#endif
