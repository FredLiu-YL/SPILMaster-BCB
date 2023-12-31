//=================================================================================
/*++
iVision Error Code
//=================================================================================

created:	2013/10/28

Author: Sean, Hank 

Revision History:

--*/
//=================================================================================

#pragma once

enum E_iVision_ERRORS
{
	E_OK1						= 0,
	E_FAILED						= 1,
	E_NULL						= 2,
	E_TRUE						= 3,
	E_FALSE						= 4,

	//IIMAGE
	E_IIMAGE_NULL					= 10    +1,
	E_IIMAGE_GETSUBIMAGE_FAILED		= 10		+2,
	E_IIMAGE_RESIZE_FAILED			= 10		+3,
	E_IIMAGE_SAVE_FAILED			= 10    +4,
	E_IIMAGE_MEM_ERROR				= 10		+5,
	E_IIMAGE_READIMAGE_FAILD		= 10    +6,
	E_IIMAGE_SVAEIMAGE_FAILD		= 10    +7,

	//iMtach
	E_IMATCH_IMAGE_NULL			= 20		+1,
	E_IMTACH_CREATENCCMODEL_FAILED	= 20		+2,
	E_IMATCH_INITIALMODEL_FAILED	= 20		+3,
	E_IMATCH_PROCESS_FAILED		= 20		+4,
	E_IMATCH_MODEL_MISMATCH		= 20		+5,
	E_IMATCH_MEM_ERROR				= 20		+6,
	E_IMATCH_VALUE_OUTOFRANGE		= 20		+7,
	E_IMATCH_KEYPRO_FAILD			= 20		+8,
	E_IMATCH_NON_TRAINING			= 20		+9,

	//iFind
	E_IFIND_IMAGE_NULL				= 30 	+1,
	E_IFIND_IMAGE_TYPE_ERR			= 30 	+2,
	E_IFIND_INITIALMODEL_FAILED		= 30		+3,
	E_IFIND_MEM_ERROR				= 30		+4,
	E_IFIND_PROCESS_FAILED			= 30		+5,
	E_IFIND_KEYPRO_FAILD			= 30		+6,
};