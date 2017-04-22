/********************************************************************
	created:	2011/08/05
	created:	5:8:2011   9:31
	filename: 	.\libDXCap\datastru.h

*********************************************************************/

#ifndef __LIBDXCAP_DATASTRU__20110805__
#define __LIBDXCAP_DATASTRU__20110805__

typedef void* device_handle;
typedef void* image_handle;

// ����״̬
enum {state_stopped, state_paused, state_running};

// ȥ����ģʽ
enum {di_none, di_weave, di_blend, di_bob};

// ����ģʽ
enum {dn_none, dn_b};

// ��Ƶ��ɫ�ռ�
enum {cs_rgb24, cs_rgb32, cs_yuy2};

// �豸����ҳ
enum {attr_video, attr_audio, attr_encode};

// �豸��Ϣ
#define MAX_DEVICE_NAME		128
typedef struct _device_tag
{
	unsigned	idx;							// ��������ö�ٹ����е����
	TCHAR		deviceName[MAX_DEVICE_NAME];	// ������������
} DEVICE_TAG, *PDEVICE_TAG;

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