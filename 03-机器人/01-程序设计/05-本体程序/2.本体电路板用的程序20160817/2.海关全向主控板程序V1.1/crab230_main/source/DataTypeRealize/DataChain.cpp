/**
  ******************************************************************************
	*�ļ���DataChain.c
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
		current=NULL;
		return;
	}
	length=len;
	
//��һ�ַ��䷽ʽ ��������
// 	Chains =new ChainNode[length]; //�ڶ��Ϸ����ڴ���ܻ�ʧ��?
// 	for(int i=0;i<length;i++)
// 	{
// 		if(i==length-1)
// 		{
// 			Chains[i].m_next=Chains;
// 		}
// 		else
// 		{
// 			Chains[i].m_next=&Chains[i+1];
// 		}
// 		if(i==0)
// 		{
// 			Chains[0].m_previous=&Chains[length-1];
// 		}
// 		else
// 		{
// 			Chains[i+1].m_previous=&Chains[i];
// 		}
// 	}
// 	current=Chains;
//�ڶ����ڴ����뷽ʽ �������м����
	current=new ChainNode(0,NULL,NULL);
	
//Ϊ��ֹ�����ڴ�ʧ�ܿ���������ķ�ʽ 
// 	do
// 	{
// 		current=new ChainNode(0,NULL,NULL);
// 	}
// 	while(current==NULL);


	current->m_next=current;
	current->m_previous=current;

	for(int i=0;i<len-1;i++)
	{
		//ͬ�� ������do while ��ֹ�ڴ�����ʧ��
		current->m_next=new ChainNode(0,current,current->m_next);
		current->m_next->m_next->m_previous=current->m_next;
	}
	
//�����ַ��䷽ʽ �����м���� ��C���ݱ������
// 	int i=0;
// 	chain *head;
// 	chain *trail;
// 	length=len;
// 	if(len<1)
// 		return ;
// 	else
// 	{
// 		chain *tem=(chain *)malloc(sizeof(chain));
// 		
// 		head=tem;
// 		trail=tem;
// 		tem->data=0;	
// 		tem->next=head;
// 		tem->last=head;
		
// 		for(i=0;i<len-1;i++)
// 		{
// 			tem=(chain *)malloc(sizeof(chain));	  //�ڶ�������ռ�  
// 			tem->data=0;
// 			tem->next=head;
// 			tem->last=trail;
// 			head->last=tem;
// 			trail->next=tem;
// 			trail=tem;	
// 		}
// 		current=head;
// 	}
}

//��������
RingChain::~RingChain()
{
// 	delete [] Chains;
	ChainNode *q,*p=current->m_next;	
	while(p!=current)
	{
		q=p->m_next;
		delete (p);
		p=q;
	}
	delete (current);
// 	current=NULL;
}


/**
  * ��  �ܣ���ȡ��ǰ�ڵ������
  * ��  ������
  * ����ֵ����ǰ�ڵ������ֵ
  * 
  */
DATATYPE RingChain::getData()
{
	return current->data;
}

/**
  * ��  �ܣ�����ǰ�ڵ�ָ��ָ���¸��ڵ�
  * ��  ������
  * ����ֵ����
  * 
  */
void RingChain::next()
{
	current=current->m_next;
}

/**
  * ��  �ܣ�����ǰ�ڵ�ָ��ָ���ϸ��ڵ�
  * ��  ������
  * ����ֵ����
  * 
  */
void RingChain::previous()
{
	current=current->m_previous;
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
	current->data=value;
}



// //����֪�ڵ�����һ���ڵ�
// //������data�� ����Ľڵ���ֵ��p����֪�Ľڵ� 
// void insertAfter(DATATYPE data,chain *p)
// {
// 	chain *tem;
// 	if(p)
// 	{
// 		 tem=(chain *)malloc(sizeof(chain));
// 		 tem->data=data;
// 		 tem->next=p->next;
// 		 (p->next)->last=tem;
// 		 tem->last=p;
// 		 p->next=tem;	
// 	}	
// }

// //����֪�ڵ�ǰ����һ���ڵ�
// //������data�� ����Ľڵ���ֵ��p����֪�Ľڵ� 
// void insertBefore(DATATYPE data,chain *p)
// {
// //	insert_after(data,p->last);
// 	chain *tem;
// 	if(p)
// 	{
// 		 tem=(chain *)malloc(sizeof(chain));
// 		 tem->data=data;
// 		 tem->next=p;
// 		 tem->last=p->last;
// 		 (p->last)->next=tem;		 
// 		 p->last=tem;		
// 	}
// }

// //ɾ����̽ڵ㣬��p�ĺ�һ���ڵ�
// //����ֵ��1��ɾ���ɹ���0��ɾ��ʧ��
// bool deleteAfter(chain *head,chain *p)
// {
// 	chain *tem;
// 	if(p->next!=head)
// 	{
// 		tem=p->next;
// 		p->next=tem->next;
// 		(tem->next)->last=p;
// 		free(tem);
// 		return true;
// 	}
// 	else
// 		return false;
// }

// //ɾ��ǰһ���ڵ㣬��p��ǰһ���ڵ�
// //����ֵ��1��ɾ���ɹ���0��ɾ��ʧ��
// bool deleteBefore(chain *head,chain *p)
// {
// 	chain *tem;
// 	if(p->next!=head)
// 	{
// 		tem=p->last;
// 		p->last=tem->last;
// 		(tem->last)->next=p;
// 		free(tem);
// 		return true;
// 	}
// 	else
// 		return false;
// }

// //ɾ���ڵ㱾��
// //����ֵ��1��ɾ���ɹ���0��ɾ��ʧ��
// bool deletSelf(chain *head,chain *p)
// {
// 	chain *q;
// 	q=head;
// 	if(!p)
// 		return false;
// 	else
// 	{
// 		while(q->next!=p&&q->next!=head)
// 			q=q->next;	
// 		q->next=p->next;
// 		(p->next)->last=q;
// 		free(p);
// 		return true;
// 	}
// }

// //����һ��˫��ѭ������ ��β�����뷨����һ�ַ�����ͷ�����뷨��
// //len:����Ľڵ���
// //����ֵ������������ָ��
// chain * creatChain(uint16_t len)
// {
// 	uint16_t i=0;
// 	chain *head;
// 	chain *trail;
// 	if(len<1)
// 		return NULL;
// 	else
// 	{
// 		chain *tem=(chain *)malloc(sizeof(chain));
// 		
// 		head=tem;
// 		trail=tem;
// 		tem->data=0;	
// 		tem->next=head;
// 		tem->last=head;
// 		
// 		for(i=0;i<len-1;i++)
// 		{
// 			tem=(chain *)malloc(sizeof(chain));	  //�ڶ�������ռ�  
// 			tem->data=0;
// 			tem->next=head;
// 			tem->last=trail;
// 			head->last=tem;
// 			trail->next=tem;
// 			trail=tem;	
// 		}
// 		return 	head;
// 	}	 
// }

// //ɾ��(����)һ��˫��ѭ������
// //����ֵ��1��ɾ���ɹ���0��ɾ��ʧ��
// void deleteChain(chain *head)
// {
// 	chain *q,*p=head->next;	
//    	while(p!=head)
// 	{
// 		q=p->next;
// 		free(p);
// 		p=q;
// 	}
// 	free(head);
// 	head=NULL;
// }


/******************************** �������ģʽ����********************************/
//bool receiveData(USART_data_t* p_usart_data, uint8_t* pRXD_DATA)
//{
//	static uint8_t flag=0;
//		
//	static chain *readData;	  // =creat_chain(XBOT_RXD_DATA_LEN);
//	
//	uint8_t CheckSum=0;
//
//	bool RxdFlag=false;
//
//	uint8_t Index=0;
//	
// 	if(flag==0)
//	{
//	   readData=creatChain(RXD_LEN);
//	   flag=1;
//	}
//
//	while (USART_RXBufferData_Available(p_usart_data))
//	{
//		readData->data = USART_RXBuffer_GetByte(p_usart_data);
//
//		readData = readData->next;//���������¸��ڵ�
//
//		if(readData->data==RXD_START)//���֡ͷ
//		{			
//			readData=readData->next;
//			CheckSum+=RXD_LEN;
//			if(readData->data==RXD_ID_1||readData->data==RXD_ID_2||readData->data==RXD_ID_3||readData->data==RXD_ID_4)//���������
//			{
//				//��������ȷ
//				for(Index=0;Index<RXD_LEN-2;Index++)
//				{
//				   CheckSum+= readData->data;
//				   readData=readData->next;
//				}
//				if(CheckSum==readData->data)//У�����ȷ
//				{
//					//�����ݴ�������
//					for(Index=0;Index<RXD_LEN;Index++)
//					{
//					   readData = readData->next;
//					   pRXD_DATA[Index]=readData->data;
//					}
//					RxdFlag=true;	
//				}
//				readData=readData->next; 	
//			}
//			else
//			{
//				readData=readData->last;//�����ϸ��ڵ�	
//			}			
//		 	CheckSum=0;
//		}
//	}
//	return 	RxdFlag;
//}
