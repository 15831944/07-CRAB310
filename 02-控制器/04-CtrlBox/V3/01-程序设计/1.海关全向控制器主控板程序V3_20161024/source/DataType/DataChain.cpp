/**
  ******************************************************************************
	*�ļ���DataChain.cpp
	*���ߣ�Ҷ��˳
	*�汾��2.0
	*���ڣ�2013-06-17
	*��Ҫ������ṹ���ʵ��
	*��ע��
	*
  ******************************************************************************  
	*/ 

#include "DataChain.h"

//���캯��
RingChain::RingChain(int len)
{
	if(len<1)
	{
		currentNode=NULL;
		return;
	}
	length=len;
	currentNode=new ChainNode(0,NULL,NULL);
	currentNode->m_next=currentNode;
	currentNode->m_previous=currentNode;
	for(int i=0;i<len-1;i++)
	{
		currentNode->m_next=new ChainNode(0,currentNode,currentNode->m_next);
		currentNode->m_next->m_next->m_previous=currentNode->m_next;
	}
}

//��������
RingChain::~RingChain()
{
	ChainNode *q,*p=currentNode->m_next;	
	while(p!=currentNode)
	{
		q=p->m_next;
		delete (p);
		p=q;
	}
	delete (currentNode);
}


/**
  * ��  �ܣ���ȡ��ǰ�ڵ������
  * ��  ������
  * ����ֵ����ǰ�ڵ������ֵ
  * 
  */
DATATYPE RingChain::getData()
{
	return currentNode->data;
}

/**
  * ��  �ܣ�����ǰ�ڵ�ָ��ָ���¸��ڵ�
  * ��  ������
  * ����ֵ����
  * 
  */
void RingChain::next()
{
	currentNode=currentNode->m_next;
}

/**
  * ��  �ܣ�����ǰ�ڵ�ָ��ָ���ϸ��ڵ�
  * ��  ������
  * ����ֵ����
  * 
  */
void RingChain::previous()
{
	currentNode=currentNode->m_previous;
}

/**
  * ��  �ܣ���ȡ����ĳ���
  * ��  ������
  * ����ֵ������ĳ���
  * 
  */
int RingChain::getLen()
{
	return length;
}

/**
  * ��  �ܣ����õ�ǰ�ڵ������
  * ��  �������趨��ֵ
  * ����ֵ����
  * 
  */
void RingChain::setData(DATATYPE value)
{
	currentNode->data=value;
}

