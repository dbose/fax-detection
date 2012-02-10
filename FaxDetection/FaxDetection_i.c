

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_FaxDetectionLib,0x9521D099,0x9240,0x4F30,0x85,0x48,0xB5,0x89,0x67,0x41,0xB7,0xAD);


MIDL_DEFINE_GUID(IID, DIID__DFaxDetection,0x456C0DDE,0x7D41,0x4792,0xAB,0xA4,0x3A,0x0C,0x80,0x5D,0x1A,0x71);


MIDL_DEFINE_GUID(IID, DIID__DFaxDetectionEvents,0xDCCBC9D2,0x3B58,0x4AD6,0x8B,0x0A,0x08,0x09,0xFD,0xD9,0x12,0x02);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDetection,0x0F6EE488,0x6DA4,0x43D3,0xAA,0xF0,0xD7,0x5D,0xE9,0x3A,0xB0,0xC5);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



