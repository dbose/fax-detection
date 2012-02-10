

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Thu Mar 01 00:36:09 2007
 */
/* Compiler settings for .\FaxDetection.idl:
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

#ifndef __FaxDetectionidl_h__
#define __FaxDetectionidl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DFaxDetection_FWD_DEFINED__
#define ___DFaxDetection_FWD_DEFINED__
typedef interface _DFaxDetection _DFaxDetection;
#endif 	/* ___DFaxDetection_FWD_DEFINED__ */


#ifndef ___DFaxDetectionEvents_FWD_DEFINED__
#define ___DFaxDetectionEvents_FWD_DEFINED__
typedef interface _DFaxDetectionEvents _DFaxDetectionEvents;
#endif 	/* ___DFaxDetectionEvents_FWD_DEFINED__ */


#ifndef __FaxDetection_FWD_DEFINED__
#define __FaxDetection_FWD_DEFINED__

#ifdef __cplusplus
typedef class FaxDetection FaxDetection;
#else
typedef struct FaxDetection FaxDetection;
#endif /* __cplusplus */

#endif 	/* __FaxDetection_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __FaxDetectionLib_LIBRARY_DEFINED__
#define __FaxDetectionLib_LIBRARY_DEFINED__

/* library FaxDetectionLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_FaxDetectionLib;

#ifndef ___DFaxDetection_DISPINTERFACE_DEFINED__
#define ___DFaxDetection_DISPINTERFACE_DEFINED__

/* dispinterface _DFaxDetection */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DFaxDetection;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("456C0DDE-7D41-4792-ABA4-3A0C805D1A71")
    _DFaxDetection : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DFaxDetectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DFaxDetection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DFaxDetection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DFaxDetection * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DFaxDetection * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DFaxDetection * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DFaxDetection * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DFaxDetection * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DFaxDetectionVtbl;

    interface _DFaxDetection
    {
        CONST_VTBL struct _DFaxDetectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DFaxDetection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DFaxDetection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DFaxDetection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DFaxDetection_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DFaxDetection_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DFaxDetection_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DFaxDetection_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DFaxDetection_DISPINTERFACE_DEFINED__ */


#ifndef ___DFaxDetectionEvents_DISPINTERFACE_DEFINED__
#define ___DFaxDetectionEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DFaxDetectionEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DFaxDetectionEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("DCCBC9D2-3B58-4AD6-8B0A-0809FDD91202")
    _DFaxDetectionEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DFaxDetectionEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DFaxDetectionEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DFaxDetectionEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DFaxDetectionEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DFaxDetectionEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DFaxDetectionEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DFaxDetectionEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DFaxDetectionEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DFaxDetectionEventsVtbl;

    interface _DFaxDetectionEvents
    {
        CONST_VTBL struct _DFaxDetectionEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DFaxDetectionEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DFaxDetectionEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DFaxDetectionEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DFaxDetectionEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DFaxDetectionEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DFaxDetectionEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DFaxDetectionEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DFaxDetectionEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_FaxDetection;

#ifdef __cplusplus

class DECLSPEC_UUID("0F6EE488-6DA4-43D3-AAF0-D75DE93AB0C5")
FaxDetection;
#endif
#endif /* __FaxDetectionLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


