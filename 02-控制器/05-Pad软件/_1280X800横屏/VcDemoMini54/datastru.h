/********************************************************************
	created:	2011/08/05

*********************************************************************/

#ifndef __LIBDXCAP_DATASTRU__20110805__
#define __LIBDXCAP_DATASTRU__20110805__

typedef void* device_handle;
typedef void* image_handle;

// ����״̬
enum {state_stopped, state_paused, state_running};

// ��Ƶ��ɫ�ռ�
enum {cs_rgb24, cs_rgb32, cs_yuy2};

// �豸��Ϣ
#define MAX_DEVICE_NAME		128
typedef struct _device_tag
{
	unsigned	idx;							// ��������ö�ٹ����е����
	TCHAR		deviceName[MAX_DEVICE_NAME];	// ������������
} DEVICE_TAG, *PDEVICE_TAG;

typedef struct _videocaps
{
	int width;
	int height;
}VIDEOCAPS, *PVIDEOCAPS;

//----��Ƶ�����������----------------------
#define X264CODEC_FILTER TEXT("x264 Codec\0")
#define XVIDCODEC_FILTER TEXT("xvid Codec\0")
#define AAC_FILTER       TEXT("aac Codec\0")
enum {codec_sys,codec_x264,codec_xvid};
enum {acodec_sys,acodec_aac};
enum {codec_CBR=0, codec_VBR=1};
typedef struct{
	int fps;    //֡��
	int keyframeinterval;  //�ؼ�֡�����������ڵ���֡��
	int rcMode;   //���ʿ���:codec_CBR(�㶨����)/codec_VBR(ƽ������)��
	int Quality; //codec_xvid: 1 ~ 31 (1Ϊ��С���ȣ�ѹ���������)
	int Bitrate; //���ʣ���λ��kbps��Ĭ��ֵ256��x264��Ϊ0ʱ���������ڲ��Լ�����

	int Maxrbps;  //VBR��Ч��Ĭ��ֵ4000000,λ�ʷ�Χ:56bps ~ 10Mbps; ��λKbps
	int Peekbps;  //VBR��Ч��Ĭ��ֵ10000000bps,λ�ʷ�Χ:56bps ~ 10Mbps; ��λKbps
}VidCodecPara;
//-------------------------------------------

enum {drate_color};
typedef struct{
	int nBrightness; // ���ȣ�ȡֵ(-255��255)
	int nContrast;  //�Աȶȣ�ȡֵ(-100��100)
}DRateColorPara;

enum SwsAlogrithm
{
	SWS_SA_FAST_BILINEAR	= 0,
	SWS_SA_BILINEAR			,
	SWS_SA_BICUBIC			,
	SWS_SA_X				,
	SWS_SA_POINT			,
	SWS_SA_AREA				,
	SWS_SA_BICUBLIN			,
	SWS_SA_GAUSS			,
	SWS_SA_SINC				,
	SWS_SA_LANCZOS			,
	SWS_SA_SPLINE			,
};

// ¼��֪ͨ
EXTERN_C const IID IID_ISaveNotify;
/*
// {BAE74021-AFEC-4336-8497-658ED4432F65}
DEFINE_GUID(IID_ISaveNotify, 
			0xbae74021, 0xafec, 0x4336, 0x84, 0x97, 0x65, 0x8e, 0xd4, 0x43, 0x2f, 0x65);
			// */
class ISaveNotify : public IUnknown// ¼����¼�֪ͨ
{
public:
	virtual HRESULT foo() = 0;
};

// isp�ӿ�
//EXTERN_C const IID IID_IispTask;
/*
/// {BC7DE54C-F483-4768-9CBA-3228D81600CD}
DEFINE_GUID(IID_IispTask, 
			0xbc7de54c, 0xf483, 0x4768, 0x9c, 0xba, 0x32, 0x28, 0xd8, 0x16, 0x0, 0xcd);
			// */

//class IispTask : public IUnknown // ��Ƶ����ӿ�
//{
//public:
//	virtual HRESULT QueryAccept(/*AM_MEDIA_TYPE**/void* mt) = 0;

//	virtual HRESULT BeginIsp() = 0;
//	virtual HRESULT IspTask(/*IMediaSample**/void* pMS) = 0;
//	virtual HRESULT EndIsp() = 0;
//};
EXTERN_C const IID IID_IispTask;
class IispTask : public IUnknown
{
public:
    virtual /* [local][id] */ HRESULT STDMETHODCALLTYPE QueryAccept( 
        void *mt) = 0;
    
    virtual /* [id] */ HRESULT STDMETHODCALLTYPE BeginIsp( void) = 0;
    
    virtual /* [local][id] */ HRESULT STDMETHODCALLTYPE IspTask( 
        void *pMS) = 0;
    
    virtual /* [id] */ HRESULT STDMETHODCALLTYPE EndIsp( void) = 0;
    
};



#endif // __LIBDXCAP_DATASTRU__20110805__