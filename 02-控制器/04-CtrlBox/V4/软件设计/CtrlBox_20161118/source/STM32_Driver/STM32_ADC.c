/***********************************************************************************************
*�ļ���		��	STM32_ADC.c
*����		��	ADC1��ʼ������ֵ�˲�
*����		��	����
*��������	��	����
*�޸�����	��	20160104
*�޸��� 		��	�Ϻ�
*�޸�ԭ��	��	������룬���ע��
*�汾 		��	2.0
*��ʷ�汾	��	����
*����1		��	ADC1_DMA_Init					//	ADC1 ��ʼ��(DMA����)��ֻ���ⲿ����1��
*����2		��	ADC1_GPIO_Config				//	��̬������ADC1 GPIO��ʼ��������Ӳ���ʵ��޸�
*����3		��	ADC1_Config						//	��̬������ADC1 ���ã�����Ӳ���ʵ��޸�
*����4		��	ADC1_DMA_Config					//	��̬������ADC1 DMA��ʼ���������޸�
*����5		��	ADC_MeanFilter					//	��̬������ADC1 ��ֵ�˲��������޸�
*����6		��	DMA1_Channel1_IRQHandler		//	DMA1 Channel1�жϺ����������޸�
***********************************************************************************************/

#include "STM32_ADC.h" 

#define ADC1_DR_Address	((uint32_t)0x4001244C)	//	ADC1���ݼĴ�����ַ


uint16_t AD_Filter[ADC_CHANNEL_N];   			//	AD�˲����ͨ���������
uint16_t AD_Cache[ADC_CACHEL_M][ADC_CHANNEL_N];	//	ȫ��AD��ͨ���������ֵ

// ����4���������ڱ��ļ��ڵ���
static  void 	ADC1_GPIO_Config(void);			//	ADC1 GPIO����   
static  void 	ADC1_Config(void);				//	ADC1 ����
static  void 	ADC1_DMA_Config(void);			//	ADC1 DMA����
static	void 	ADC_MeanFilter(void);			//	ADC  ��ֵ�˲�

/**
*	@����˵����	ADC1��ʼ��(DMA����)
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
void 	ADC1_DMA_Init(void)
{
	ADC1_GPIO_Config(); 						//	GPIO����
	ADC1_DMA_Config();  						//	ADC1-DMA����
	ADC1_Config();  							//	ADC1����
	ADC_Cmd(ADC1, ENABLE); 						//	ʹ��ADC1(ʹ�ܺ󣬿���ת������Ҫ�����������)
	ADC_SoftwareStartConvCmd(ADC1, ENABLE); 				//	ADC�����������  
}

/**
*	@����˵����	ADC1 GPIO����(ģ������)������Ӳ���ʵ��޸�
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
static	void	ADC1_GPIO_Config(void)
{
	STM32_GpioOneInit(GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);	//	����AD_PowKeyͨ��
	STM32_GpioOneInit(GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);	//	����AD_Powͨ��
	
	STM32_GpioOneInit(GPIO_Pin_1,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOB);	//	����AD1ͨ��
	STM32_GpioOneInit(GPIO_Pin_0,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOB);	//	����AD2ͨ��
	STM32_GpioOneInit(GPIO_Pin_5,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);	//	����AD3ͨ��
	STM32_GpioOneInit(GPIO_Pin_4,GPIO_Speed_50MHz,GPIO_Mode_AIN,GPIOA);	//	����AD4ͨ��

}

/**
*	@����˵����	ADC1����DMA���޸�ͨ��ʱ������Ҫ�޸Ĵ˺���
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
static	void	ADC1_DMA_Config(void)   
{   
    DMA_InitTypeDef DMA_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
     
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);      //	���� DMA ʱ��
    DMA_DeInit(DMA1_Channel1);
		
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; 
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&AD_Cache;   
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;   

    //	������ã�ʹ����1�������AD_Cache[0]������2�������AD_Cache[1]    
    DMA_InitStructure.DMA_BufferSize = ADC_CHANNEL_N*ADC_CACHEL_M;   
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;   
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;   
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;   
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;   
    //	ѭ��ģʽ������Bufferд�����Զ��ص���ʼ��ַ��ʼ����    
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;   
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;   
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;   
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);   
    
	//	DMA �ж�����
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE); //	ʹ��DMA��������ж�   
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);          //	ʹ��DMA�ж� 
	
	//	������ɺ�����DMAͨ��    
    DMA_Cmd(DMA1_Channel1, ENABLE);
} 

/**
*	@����˵����	ADC1����(ʱ�Ӳ��ܳ���14MHz)������Ӳ���ʵ��޸�
*				�޸�ͨ��ʱ����Ҫ��Ӳ��޸�ADC_RegularChannelConfig����
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
static	void	ADC1_Config(void)   
{   
    ADC_InitTypeDef ADC_InitStructure;   
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);						//	ADCCLK = PCLK2/4 = 9MHz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//	���� ADC1 ʱ��
	
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; 		//	ת��ģʽΪ����ģʽ 
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;   			//	ʹ�ö�ͨ��ʱ��Ҫ����
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;  	//	����ת������    
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//	û���ⲿ���� 
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//	�����Ҷ��� 
    ADC_InitStructure.ADC_NbrOfChannel = ADC_CHANNEL_N;     //	ͨ����    
    ADC_Init(ADC1, &ADC_InitStructure);   					//	д��Ĵ���
       
    ADC_TempSensorVrefintCmd(DISABLE);    					//	ʹ��Ƭ���¶ȴ�����ʱ���迪��   
     
	//	���������ADC1��ͨ��(ADC_Channel_0~ADC_Channel_17)��ת��˳��(1~16)������ʱ��  
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 4, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 5, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 6, ADC_SampleTime_55Cycles5);

   
    ADC_DMACmd(ADC1, ENABLE);								//	����ADC��DMA֧��(Ҫʵ��DMA�����赥������DMAͨ���Ȳ���)    
	ADC_Cmd(ADC1, ENABLE);      							//	ʹ��ADC1   
	
    ADC_ResetCalibration(ADC1);								//	ADC�Զ�У׼����������ִ��һ�Σ���֤���� 
    while(ADC_GetResetCalibrationStatus(ADC1));    
    ADC_StartCalibration(ADC1);    
    while(ADC_GetCalibrationStatus(ADC1)){};  				//	ADC�Զ�У׼����   
	
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); 				//	ADC�����������    
}  

/**
*	@����˵����	ADC��ֵ�˲����޸�ͨ��ʱ������Ҫ�޸Ĵ˺���
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
static	void	ADC_MeanFilter(void)
{
	int32_t sum = 0;
	uint8_t channelNum,cacheNum;
	for(channelNum=0; channelNum<ADC_CHANNEL_N; channelNum++)
	{
		for ( cacheNum=0;cacheNum<ADC_CACHEL_M;cacheNum++)
		{
			sum += AD_Cache[cacheNum][channelNum];
		}
		AD_Filter[channelNum]=sum/ADC_CACHEL_M;
		sum=0;
	} 
}

/**
*	@����˵����	DMA1ͨ��1�жϴ���������ֵ�˲����޸�ͨ��ʱ������Ҫ�޸Ĵ˺���
*	@������		��
*	@����ֵ�� 	��
*	@��ע�� 		��
*/
void	DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA1_IT_TC1) != RESET)
	{ 
		ADC_MeanFilter(); 
		DMA_ClearITPendingBit(DMA1_IT_TC1); //���ȫ���жϱ�־    
    }
}

 








