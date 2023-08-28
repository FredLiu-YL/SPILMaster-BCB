//=================================================================================
/*++
iVision Error handling and Version 
//=================================================================================

created:	2013/10/28

Author: Sean, Hank 

Revision History:

--*/
//=================================================================================

#pragma once

#ifdef IVISION_EXPORTS
#define IVISION_API  __declspec(dllexport)
#else
#define IVISION_API  __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// Version
IVISION_API	char* iGetiImageVersion();
IVISION_API	char* iGetiImageVersionDate();
IVISION_API	char* iGetiMatchVersion();
IVISION_API	char* iGetiMatchVersionDate();
IVISION_API	char* iGetiFindVersion();
IVISION_API	char* iGetiFindVersionDate();

// Error messages
IVISION_API	char*				iGetErrorText		(enum E_iVision_ERRORS eError);

IVISION_API  E_iVision_ERRORS		iGetKeySerial		(int *Serial);
#ifdef __cplusplus
}
#endif
