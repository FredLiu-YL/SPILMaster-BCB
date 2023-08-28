//=================================================================================
/*++
iVision iObject class
C++ code for the iObject class.
//=================================================================================

created:	2014/03/27

Author: Sean, Hank 

Revision History:

--*/
//=================================================================================

#pragma once 

#ifdef IOBJECT_EXPORTS
#define IOBJECT_API  __declspec(dllexport)
#else
#define IOBJECT_API  __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
// 外層介面 定義
	IOBJECT_API int __cdecl add();

#ifdef __cplusplus
}
#endif