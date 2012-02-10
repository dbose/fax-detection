

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Sat Mar 10 02:55:17 2007
 */
/* Compiler settings for .\AMSFaxDetection.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __AMSFaxDetectionidl_h__
#define __AMSFaxDetectionidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DAMSFaxDetection_FWD_DEFINED__
#define ___DAMSFaxDetection_FWD_DEFINED__
typedef interface _DAMSFaxDetection _DAMSFaxDetection;
#endif 	/* ___DAMSFaxDetection_FWD_DEFINED__ */


#ifndef ___DAMSFaxDetectionEvents_FWD_DEFINED__
#define ___DAMSFaxDetectionEvents_FWD_DEFINED__
typedef interface _DAMSFaxDetectionEvents _DAMSFaxDetectionEvents;
#endif 	/* ___DAMSFaxDetectionEvents_FWD_DEFINED__ */


#ifndef __AMSFaxDetection_FWD_DEFINED__
#define __AMSFaxDetection_FWD_DEFINED__

#ifdef __cplusplus
typedef class AMSFaxDetection AMSFaxDetection;
#else
typedef struct AMSFaxDetection AMSFaxDetection;
#endif /* __cplusplus */

#endif 	/* __AMSFaxDetection_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __AMSFaxDetectionLib_LIBRARY_DEFINED__
#define __AMSFaxDetectionLib_LIBRARY_DEFINED__

/* library AMSFaxDetectionLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_AMSFaxDetectionLib;

#ifndef ___DAMSFaxDetection_DISPINTERFACE_DEFINED__
#define ___DAMSFaxDetection_DISPINTERFACE_DEFINED__

/* dispinterface _DAMSFaxDetection */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DAMSFaxDetection;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("456C0DDE-7D41-4792-ABA4-3A0C805D1A71")
    _DAMSFaxDetection : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DAMSFaxDetectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DAMSFaxDetection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DAMSFaxDetection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DAMSFaxDetection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DAMSFaxDetection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DAMSFaxDetection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DAMSFaxDetection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DAMSFaxDetection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DAMSFaxDetectionVtbl;

    interface _DAMSFaxDetection
    {
        CONST_VTBL struct _DAMSFaxDetectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DAMSFaxDetection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DAMSFaxDetection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DAMSFaxDetection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DAMSFaxDetection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DAMSFaxDetection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DAMSFaxDetection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DAMSFaxDetection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DAMSFaxDetection_DISPINTERFACE_DEFINED__ */


#ifndef ___DAMSFaxDetectionEvents_DISPINTERFACE_DEFINED__
#define ___DAMSFaxDetectionEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DAMSFaxDetectionEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DAMSFaxDetectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DCCBC9D2-3B58-4AD6-8B0A-0809FDD91202")
    _DAMSFaxDetectionEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DAMSFaxDetectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DAMSFaxDetectionEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DAMSFaxDetectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DAMSFaxDetectionEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DAMSFaxDetectionEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DAMSFaxDetectionEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DAMSFaxDetectionEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DAMSFaxDetectionEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DAMSFaxDetectionEventsVtbl;

    interface _DAMSFaxDetectionEvents
    {
        CONST_VTBL struct _DAMSFaxDetectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DAMSFaxDetectionEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DAMSFaxDetectionEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DAMSFaxDetectionEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DAMSFaxDetectionEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DAMSFaxDetectionEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DAMSFaxDetectionEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DAMSFaxDetectionEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DAMSFaxDetectionEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AMSFaxDetection;

#ifdef __cplusplus

class DECLSPEC_UUID("0F6EE488-6DA4-43D3-AAF0-D75DE93AB0C5")
AMSFaxDetection;
#endif
#endif /* __AMSFaxDetectionLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


