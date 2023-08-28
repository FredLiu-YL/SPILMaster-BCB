/******************************************************************************
 *	
 *	(C) Copyright WDI 2010
 *	
 ******************************************************************************
 *
 *	FILE:		atf_lib.cpp
 *
 *	PROJECT:	AFT Sensors
 *
 *	SUBPROJECT:	.
 *
 *	Description: ATF sensor communication library
 *	
 ******************************************************************************
 *	
 *	Change Activity
 *	Defect  Date       Developer        Description
 *	Number  DD/MM/YYYY Name
 *	======= ========== ================ =======================================
 *          21/09/2009 Andrew L.        Initial version 
 *          03/11/2010 Chris O.          
 *          15/11/2010 Chris O.         Added synchronization objects for
 *                                      multithreaded applications
 *                                      
 *****************************************************************************/

// This is the main DLL file.

#include "stdafx.h"
#include "stdio.h"
#include "epp.h"
#include "llc.h"
#include "atf_lib.h"

CLogger g_log;
CEppArr g_epp_arr;
CLlc g_llc(&g_log);

// logging macros
#define ENTERFUN(funname) atf_saveToLog2(CLogger::LogLow, "%s%s", funname, " - entered\n");
#define EXITFUN(funname) atf_saveToLog2(CLogger::LogLow, "%s%s", funname, " - exited\n");
#define LOGMSG(pLogMsg, LogLev) g_log.saveToLog(pLogMsg, LogLev);
#define LOGMSG2(LogLev, format, ...) atf_saveToLog2(LogLev, format, __VA_ARGS__);

static int gs_read_delay = 4;

#define RET_ON_ERROR(expression) {int iErr = ErrOK; if((iErr = expression) != ErrOK) return iErr;}
#define RET_ERROR(expression) {int iErr = ErrOK; return iErr = expression;}
#define RET_VAL_ON_ERROR(expression, err) {int iErr = ErrOK; if((iErr = expression) != ErrOK) return err;}

// -------------------------------------------------------------------------------------------
int atf_GetComIdx()
{
	return CEppArr::GetCurrentEppIndex();
}
int atf_SetComIdx(int idx)
{
	return CEppArr::SetCurrentEppIndex(idx); 
}
// -------------------------------------------------------------------------------------------

int atf_OpenConnection (char *port, int speed)
{ 
	return CEppArr::Open (port, speed > 0 ? speed : 9600);	// 9600 is default
}
void atf_CloseConnection()
{ 
	CEppArr::Close ();
}

const char* atf_GetErrorInfo(int iErr)
{
	int iErrLoc = iErr;

	if (iErr < ErrOK || iErr > Unknown)
	{
		iErr = Unknown;
	}
	return CEpp::errName ((EppErrorCodes)iErr);
}

int atf_RecoverSensor() 
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	return pEpp->RecoverSensor();
}

int atf_PingAck() 
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	return pEpp->PingAck(); 
}

int atf_Reset() 
{ 
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	return pEpp->Reset(); 
}

// -------------------------------------------------------------------------------------------
const char *atf_PartInfo()
{
	static char cInfoBuffer[256];
	int swver,fpgaver,sensorSN;
	cInfoBuffer[0] = 0;
	CEpp *pEpp = CEppArr::Epp();
	if (!pEpp) return NULL;

	RET_VAL_ON_ERROR(pEpp->ReadArray ((void*)&swver, 'U', 80, DtDwordEnm),0);	
	RET_VAL_ON_ERROR(pEpp->ReadArray ((void*)&fpgaver, 'U', 81, DtDwordEnm),0); 
	RET_VAL_ON_ERROR(pEpp->ReadArray((void*)&sensorSN, 'U', 82, DtDwordEnm, 1, 3),0);

	sprintf_s(cInfoBuffer, sizeof(cInfoBuffer), "SwVer=%08x; FwVer=%08x; SN=%06d;\n", swver, fpgaver, sensorSN);

	return cInfoBuffer;
}

int atf_ReadSerialNumber(unsigned int* SensorSN)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray((void*)SensorSN, 'U', 82, DtDwordEnm, 1, 3));
}

int atf_ReadFirmwareVer(int* ver)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray((void*)ver, 'U', 80, DtDwordEnm));
}

int atf_ReadStatus (short *pstatus)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pstatus, 'U', 20, DtWordEnm)); 
}

int atf_ReadHwStat (int *HwStat)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)HwStat, 'U', 45, DtDwordEnm)); 
}

int atf_ReadLinearRange (int obj, int *pLinearRange)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pLinearRange, 'U', 52, DtWordEnm, 1, obj)); 
}

int atf_WriteLinearRange (int obj, int iLinearRange)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&iLinearRange, 'U', 52, DtWordEnm, 1, obj)); 
}

int atf_Read7DotPosition (short *p7dots, int iLinearRange)
{
    int i7DotPos[7];
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)&i7DotPos, 't', 31, DtDwordEnm, 7, 16)); 
    for (int i=0; i<7; i++) *p7dots++ = (i7DotPos[i]*512/iLinearRange)>>10;
	return ErrOK;
}

int atf_ReadPosition (float &fpos)
{
	int pos = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)&pos, 't', 41, DtDwordEnm)); 
	fpos = pos/1024.0f;
	return ErrOK;
}

int atf_ReadSurface (short *piSurf)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)piSurf, 'U', 71, DtWordEnm, 1, 0));
}

int atf_WriteSurface (short iSurf)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	if (iSurf < 0) iSurf = 0;
	if (iSurf > 4) iSurf = 4;

	RET_ERROR(pEpp->WriteArray ((void*)&iSurf, 'U', 71, DtWordEnm, 1, 0));
}

// scanline header
#define ScanlineHeaderId    0xfead

#define FR_MaxNumEnm      6         // number of bits used by FR_....Enm
#define FR_HProjId        0
#define FR_VProjId        1         // this is measuring scanline
#define FR_AcquisitionId  2         // this contains elements below
#define FR_LHistProjId    3         // histograms are reported in stead of projections
#define FR_RHistProjId    4
#define FR_HwCogId        5         // cog hw position

// elements found in acquisition array
#define FR_AcqElem_LaserId				0   // elements found in acquisition array
#define FR_AcqElem_MaxHPeakIdxId		1   // where max V peak is found (in pixels from the beginning of scanline)
#define FR_AcqElem_MaxVPeakIdxId		2   // where max H peak is found (...)
#define FR_AcqElem_IntegrationTimeId	3
#define FR_AcqElem_4RowFloorId			4
#define FR_AcqElem_MapPeakDotId			5
#define FR_AcqElem_WidthHPeakId			6   // width for V peak (in pixels * 10)
#define FR_AcqElem_WidthVPeakId			7   // width for H peak (in pixels * 10)
#define FR_AcqElem_FrameId				8

// FR_AcqElem_FrameId bits are partition here
#define WINSWITCH_DOTWINDOW_VALID   0x000f    // where dotwindow window information is supposed to be found
#define WINSWITCH_WINDOW_VALID      0x00f0    // where window information is supposed to be found
#define SURFRACE_VALID              0x0100    // indicate surface validation  
#define IMAGE_VALID                 0x0200    // indicate image presence
#define WINSWITCH_VALID             0x1000    // this frame is deemed to be valid (0 is invalid)
#define WINSWITCH_SYNC              0x2000    // indicates that frame had been resulting from dynamic switching
#define WINSWITCH_CASERR            0x4000    // cas error reported
#define WINSWITCH_ISRERR            0x8000    // isr error reported

// layout of the scanline header
typedef struct _FpgaScanlineHeader 
{
	u_short   id;                       // identifier (ScanlineHeaderId)
	u_short   num;                      // table size (=FR_MaxNumEnm)
	u_short   beg [FR_MaxNumEnm];       // beggining index of where block is placed in data
	u_short   len [FR_MaxNumEnm];       // number of elements of data used up by block
	u_short   data[1];                  // block of data follows immediately here 
} FpgaScanlineHeader,*PFpgaScanlineHeader;

int atf_ReadScanline (u_short* mode, u_short* h_scanline, u_short* v_scanline , u_short* h_len, u_short* v_len, u_short* width)
{	
	u_short buf[MAX_SCANLINE_LENGTH];
	int h_len_max, v_len_max;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

    h_len_max = *h_len;
    if (h_len_max>1300) 
        h_len_max = 1300;
    v_len_max = *v_len;
    if (v_len_max>1300) 
        v_len_max = 1300;

	RET_ON_ERROR(pEpp->ReadArray ((void*)buf, 't', 91, DtWordEnm, 1300, 0));

	// validate first byte contain what we expect
	if (buf[0]!=ScanlineHeaderId)
	{
		return -1;
	}

	if(buf[2+FR_AcquisitionId] != 0)
	{
		return -2;
	}

	*mode = buf[2+2*FR_MaxNumEnm+FR_AcqElem_FrameId] & 0xf;

	*width = buf[2+2*FR_MaxNumEnm+FR_AcqElem_WidthHPeakId];  // v width

    // if hw cog is provided, then we us this one instead of horizontal line
    if (*h_len = buf[2+FR_MaxNumEnm+FR_HwCogId])
    {
        if (*h_len>h_len_max) 
            *h_len = h_len_max;
	    memcpy(h_scanline, &buf[2+2*FR_MaxNumEnm+ buf[2+FR_HwCogId]], *h_len * sizeof(u_short));
    }
    else
	{
	    *h_len = buf[2+FR_MaxNumEnm+FR_HProjId];
        if (*h_len>h_len_max) 
            *h_len = h_len_max;
        if (*h_len)memcpy(h_scanline, &buf[2+2*FR_MaxNumEnm+ buf[2+FR_HProjId]], *h_len * sizeof(u_short));
    }

    *v_len = buf[2+FR_MaxNumEnm+FR_VProjId];
    if (*v_len>v_len_max) 
        *v_len = v_len_max;
    if (*v_len)memcpy(v_scanline, &buf[2+2*FR_MaxNumEnm+ buf[2+FR_VProjId]], *v_len * sizeof(u_short));


	return ErrOK;
}

int atf_MoveZ (int move)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&move, 't', 100, DtDwordEnm)); 
}

int atf_MoveZum (int iMoveUm)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&iMoveUm, 'U', 99, DtDwordEnm)); 
}

int atf_MoveZ_ClearAbs (int move)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&move, 'U', 98, DtDwordEnm)); 
}

int atf_ReadLastMoveZ (int &zMove)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)&zMove, 't', 100, DtDwordEnm));
}

int atf_StopZMotor()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 16, DtNoDataEnm));
}

int atf_ReadAccel (int obj, float *pAccel)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int _Accel = 0;
	*pAccel = 0.0f;
	RET_ON_ERROR(pEpp->ReadArray ((void*)&_Accel, 'U', 107, DtDwordEnm, 1, obj));
	*pAccel = (float)(_Accel)/1000.0f;
	return ErrOK;
}

int atf_WriteAccel (int obj, float fAccel)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int _Accel = (int)(fAccel*1000);
	RET_ERROR(pEpp->WriteArray ((void*)&_Accel, 'U', 107, DtDwordEnm, 1, obj));
}

int atf_ReadSpeed (int obj, float* pSpeed)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int _Speed = 0;
	RET_ON_ERROR(pEpp->ReadArray ((void*)&_Speed, 'U', 108, DtDwordEnm, 1, obj));
	*pSpeed = (float)(_Speed)/1000.0f;
	return ErrOK;
}

int atf_WriteSpeed (int obj, float fSpeed)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int _Speed = (int)(fSpeed *1000.0f);
	RET_ERROR(pEpp->WriteArray ((void*)&_Speed, 'U', 108, DtDwordEnm, 1, obj));
}

int atf_EnableLaser ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 1, DtNoDataEnm)); 
}

int atf_DisableLaser ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 2, DtNoDataEnm)); 
}

int atf_EnableSync ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 17, DtNoDataEnm)); 
}

int atf_DisableSync ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 18, DtNoDataEnm)); 
}

int atf_SaveAll ()
{
	int iRet = 0;
	int iErr = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	iErr = pEpp->_ChangeCommTimeouts(CEpp::SaveToSensorTimeout);
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to change COM port timeouts. [ErrorNum=", iErr, "]\n");
	}

	iRet = pEpp->WriteArray (0, 'U', 5, DtNoDataEnm);

	iErr = pEpp->_ResetCommTimeouts();
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to reset COM port timeouts. [ErrorNum=", iErr, "]\n");
	}

	return iRet;
}

int atf_AfStop ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 7, DtNoDataEnm));
}

int atf_AFTrack ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 6, DtNoDataEnm)); 
}

int atf_AFAoiTrack ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 9, DtNoDataEnm));
}

int atf_DPAF()
{
    CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 11, DtNoDataEnm));
}

int atf_AFVideoTrack ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 206, DtNoDataEnm));
}

int atf_AfDuvJump ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 8, DtNoDataEnm));
}

int atf_AFAoiOnlyTrack ()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 'U', 10, DtNoDataEnm));
}

int atf_ReadBaud (int &br)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)&br, 'U', 25, DtDwordEnm)); 
}

int atf_WriteBaud (int br)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&br, 'U', 25, DtDwordEnm)); 
}

int atf_ReadPositionPacked (RsData *prs) 
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)prs, 'U', 41, DtWordEnm)); 
}

int atf_ReadObjNum (int *pObj)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pObj, 'U', 50, DtDwordEnm));
}

int atf_WriteObjNum(int obj)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&obj, 'U', 50, DtDwordEnm)); 
}

int atf_ReadPeakOffset (int obj,					/* objective index */ \
						PeakOffsetWhich pow,		/* peak offset, reading mode */\
						int* peakArray				/* pointer to returned data */) 
{
	int iOffset			= 0;
	int iNumOfElement	= 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	switch(pow)
	{
		case RPOW_VFar:
		{
			iOffset			= 13; iNumOfElement	= 1;
			break;
		}
		case RPOW_VNear1:
		{
			iOffset			= 12; iNumOfElement	= 1;
			break;
		}
		case RPOW_VNear7:
		{
			iOffset			= 16; iNumOfElement	= 7;
			break;
		}
		case RPOW_VAll:
		{
			iOffset			= 12; iNumOfElement	= 12;
			break;
		}
		case RPOW_VHAll:
		{
			iOffset			= 0; iNumOfElement	= 24;
			break;
		}
		default:
		{
			return ErrNotSupported;
		}
	}

	RET_ERROR( pEpp->ReadArray ((void*)peakArray, 'U', 51, DtDwordEnm, iNumOfElement, obj*24+iOffset) );
}

int atf_WritePeakOffset (int obj,					/* objective index */ \
						 PeakOffsetWhich pow,		/* peak offset, reading mode */\
						 int* peakArray				/* pointer to returned data */) 
{
	int iOffset			= 0;
	int iNumOfElement	= 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	switch(pow)
	{
		case RPOW_VFar:
		{
			iOffset			= 13; iNumOfElement	= 1;
			break;
		}
		case RPOW_VNear1:
		{
			iOffset			= 12; iNumOfElement	= 1;
			break;
		}
		case RPOW_VNear7:
		{
			iOffset			= 16; iNumOfElement	= 7;
			break;
		}
		case RPOW_VAll:
		{
			iOffset			= 12; iNumOfElement	= 12;
			break;
		}
		case RPOW_VHAll:
		{
			iOffset			= 0; iNumOfElement	= 24;
			break;
		}
		default:
		{
			return ErrNotSupported;
		}
	}

	RET_ERROR( pEpp->WriteArray ((void*)peakArray, 'U', 51, DtDwordEnm, iNumOfElement, obj*24+iOffset) );
}

int atf_ReadWindowRowDelay (int obj, WindowEnm which, short* prd)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)prd, 't', 72, DtWordEnm, 1, obj*4+which));
}

int atf_WriteWindowRowDelay (int obj, WindowEnm which, short rd)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&rd, 't', 72, DtWordEnm, 1, obj*4+which));
}

int atf_WriteStepPerMmConversion (u_short uStepMm)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&uStepMm, 'U', 100, DtWordEnm));
}

int atf_ReadStepPerMmConversion (u_short* puStepMm)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)puStepMm, 'U', 100, DtWordEnm));
}

int atf_WriteMicrostep (u_short uUstep)
{
	int iRet = 0;
	int iErr = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	iErr = pEpp->_ChangeCommTimeouts(CEpp::MicroStepTimeout);
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to change COM port timeouts. [ErrorNum=", iErr, "]\n");
	}

	iRet = pEpp->WriteArray ((void*)&uUstep, 'U', 101, DtWordEnm, 1, 0);

	iErr = pEpp->_ResetCommTimeouts();
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to reset COM port timeouts. [ErrorNum=", iErr, "]\n");
	}

	return iRet;
}

int atf_ReadMicrostep (u_short* puUstep)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)puUstep, 'U', 101, DtWordEnm, 1, 0));
}

int atf_LaserTrackOn()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 't', 6, DtNoDataEnm)); 
}

int atf_LaserTrackOff()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 't', 7, DtNoDataEnm)); 
}

int atf_ReadLaserPower(u_short *plaser, int iByteNumToRead, int dotIdx)
{ 
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int iByteNumToReadLoc = iByteNumToRead;

	if (iByteNumToReadLoc > 15) iByteNumToReadLoc = 15;

	RET_ERROR(pEpp->ReadArray ((void*)plaser, 'U', 30, DtWordEnm, iByteNumToReadLoc, dotIdx));
}

int atf_WriteLaserPower(u_short laser, int iByteNumToWrite, int dotIdx) 
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int iByteNumToWriteLoc = iByteNumToWrite;
	u_short _laser[3] = {laser, laser, laser};

	if (iByteNumToWriteLoc > 3) iByteNumToWriteLoc = 3;

	RET_ERROR(pEpp->WriteArray ((void*)&_laser, 'U', 30, DtWordEnm, iByteNumToWriteLoc, dotIdx));
}

int atf_WriteInfocusRange (int obj, int iRange) 
{ 
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&iRange, 'U', 53, DtWordEnm, 1, obj)); 
}

int atf_ReadInfocusRange (int obj, int* pRange) 
{ 
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pRange, 'U', 53, DtWordEnm, 1, obj));
}

int atf_WriteSlopeUmPerOut (int obj, float fumout) 
{ 
	int _Umout = (int)(fumout*1024);
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&_Umout, 'U', 55, DtDwordEnm, 1, obj)); 
}

int atf_ReadSlopeUmPerOut (int obj, float* pfumout)
{
	int _Umout;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)&_Umout, 'U', 55, DtDwordEnm, 1, obj));
	*pfumout = (float)_Umout /1024;
	return ErrOK; 
}

int atf_WriteP (int obj, float fP)
{ 
	int _P = (int)(fP*1024);
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&_P, 'U', 106, DtDwordEnm, 1, obj)); 
}

int atf_ReadP (int obj, float* pP)
{ 
	int _P;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)&_P, 'U', 106, DtDwordEnm, 1, obj));
	*pP = (float)_P /1024;
	return ErrOK; 
}

int atf_WriteMotionLimits (int upper_limit, int lower_limit, int adaptive_lim)
{
	int limit[3] = {upper_limit, lower_limit, adaptive_lim};
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray((void*)limit, 'U', 112, DtDwordEnm, 3, 0)); 
}

int atf_WriteAbsZPos (int absZ)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&absZ, 'U', 109, DtDwordEnm)); 
}

int atf_ReadAbsZPos (int* absZ)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)absZ, 'U', 109, DtDwordEnm)); 
}


int atf_ReadAllAvailableMagnification (short* pMag, int* pnum) 
{
	if (!pnum || *pnum>16 || *pnum==0) return ErrInvalid;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	memset (pMag,0,sizeof(short)*(*pnum));
	RET_ON_ERROR(pEpp->ReadArray ((void*)pMag, 'U', 78, DtWordEnm, *pnum, 0)); 
	for (int i=0; i<*pnum; i++) if (!pMag[i]) *pnum = i;
	return ErrOK;
}

const char *atf_DecodeMagnification (int mag) 
{
	static char mag_id[32];
	char *pdesc="";
	switch((mag>>8)&0xff) {
		case 'U' : pdesc = "DUV"; break;
		case 'u' : pdesc = "NUV"; break;
		case 'G' : pdesc = "Green"; break;
	}
	sprintf(mag_id, "%2dX%s", mag&0xff, pdesc);
	return mag_id;
}

int atf_ReadMagnification (int obj, short* pMag) 
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)pMag, 'U', 54, DtWordEnm, 1, obj)); 
	// *pMag &= 0xff;		// Need upper 8 bits, since they encode objective type
							// retired: (upper 8 bits may be set and confuse user)
	return ErrOK;
}

int atf_WriteMagnification (int obj, short uMag)
{
	int iRet = 0;
	int iErr = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	iErr = pEpp->_ChangeCommTimeouts(CEpp::MagnifChangeTimeout);
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to change COM port timeouts. [ErrorNum=", iErr, "]\n");
	}
	
	iRet = pEpp->WriteArray ((void*)&uMag, 'U', 54, DtWordEnm, 1, obj); 

	iErr = pEpp->_ResetCommTimeouts();
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to reset COM port timeouts. [ErrorNum=", iErr, "]\n");
	}

	return iRet;
}

int atf_Make0() 
{
	int iRet = 0;
	int iErr = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	iErr = pEpp->_ChangeCommTimeouts(CEpp::MakeZeroTimeout);
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to change COM port timeouts. [ErrorNum=", iErr, "]\n");
	}
	
	iRet = pEpp->WriteArray ((void*)0, 'U', 62, DtNoDataEnm);

	iErr = pEpp->_ResetCommTimeouts();
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to reset COM port timeouts. [ErrorNum=", iErr, "]\n");
	}

	Sleep (2000);
	return iRet;
}

int atf_DisableAutoWindowTransit (void)
{
	char noAutoTransit = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&noAutoTransit, 'U', 56, DtByteEnm)); 
}

int atf_EnableAutoWindowTransit (void)
{
	char doAutoTransit = 0x20;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&doAutoTransit, 'U', 56, DtByteEnm)); 
}

int atf_EnableAutoOff()
{
	char buf;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)&buf, 'U', 56, DtByteEnm, 1, 1));
	buf |= 0x04;
	RET_ERROR(pEpp->WriteArray ((void*)&buf, 'U', 56, DtByteEnm, 1, 1)); 
}

int atf_DisableAutoOff()
{
	char buf;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)&buf, 'U', 56, DtByteEnm, 1, 1));
	buf &= ~(0x04);
	RET_ERROR(pEpp->WriteArray ((void*)&buf, 'U', 56, DtByteEnm, 1, 1)); 
}

int atf_ForceFarMode () 
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 't', 11, DtNoDataEnm)); 
}

int atf_ForceNearMode () 
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (0, 't', 10, DtNoDataEnm)); 
}

int atf_CenterFarWindow ()
{
	u_short win[2];
	win[0] = 644;
	win[1] = 516;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray((void*)win , 't', 65, DtWordEnm, 2, 0));
}

int atf_ClearFarWindowCentering ()
{
	u_short win[2];
	win[0] = 0;
	win[1] = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray((void*)win , 't', 65, DtWordEnm, 2, 0));
}

int atf_WriteDuvJump (int obj, short sUStep)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&sUStep, 'U', 110, DtWordEnm, 1, obj)); 
}

int atf_ReadDuvJump (int obj, short* pUStep)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pUStep, 'U', 110, DtWordEnm, 1, obj)); 
}

int atf_ReadLedCurrent (int channel, u_short* pCurrent)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pCurrent, 't', 131, DtWordEnm, 1, channel)); 
}

int atf_WriteLedCurrent (int channel, u_short uCurrent)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&uCurrent, 't', 131, DtWordEnm, 1, channel)); 
}

int atf_ReadLedPwm (int channel, u_short* pPWM)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pPWM, 'U', 130, DtWordEnm, 1, channel)); 
}

int atf_WriteLedPwm (int channel, u_short uPWM)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&uPWM, 'U', 130, DtWordEnm, 1, channel)); 
}

int atf_ReadLedPwmStartupVal (int iChannel, u_short *puPWM)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)puPWM, 't', 132, DtWordEnm, 1, iChannel));
}

int atf_WriteLedPwmStartupVal (int iChannel, u_short uPWM)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&uPWM, 't', 132, DtWordEnm, 1, iChannel));
}

int atf_ReadMfcConfig (int* mfc_config)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)mfc_config, 'U', 48, DtDwordEnm));
}

int atf_ReadMfcMotorParm (u_char* motor_parm)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)motor_parm, 't', 171, DtByteEnm, 5, 0));
}

BOOL atf_IsCmAvailable()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int model = 0;
	RET_VAL_ON_ERROR(pEpp->ReadArray((void*)&model, 'U', 56, DtByteEnm, 1, 2),FALSE);
	return (model&0xff) == 1 ? TRUE : FALSE;
}
int atf_ReadCmGlassThickness (int* piThicknessUstep)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)piThicknessUstep, 'U', 155, DtDwordEnm));
}
int atf_WriteCmGlassThickness (int iThicknessUstep)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&iThicknessUstep, 'U', 155, DtDwordEnm));
}

int atf_ReadCmRetarder (float *pfrp, int iSurface)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int retardation_percentage = 0;
	RET_ON_ERROR(pEpp->ReadArray((void*)&retardation_percentage, 'U', 211, DtWordEnm, 1, iSurface));
	*pfrp = (float)((retardation_percentage*100)/1024);
	return ErrOK;
}
int atf_WriteCmRetarder (float fRetardation_percent, int iSurface)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int retardation_percentage = (int)(fRetardation_percent*1024/100);
	RET_ERROR(pEpp->WriteArray((void*)&retardation_percentage, 'U', 211, DtWordEnm, 1, iSurface));
}
CmRetarderEnum atf_ReadCmRetarderStatus ()
{
	CEpp *pEpp = CEppArr::Epp();
	if (!pEpp) return CmRetarderStatusUnavailable;
	CmRetarderEnum status = CmRetarderStatusUnavailable;
	RET_VAL_ON_ERROR(pEpp->ReadArray ((void*)&status, 't', 211, DtWordEnm),status);
	return status;
}

// CM AutoDetect
#define RETARDER_OPTION_AUTOCORRECT_AF     0x10   // keep correcting retardation angle during AF
#define RETARDER_OPTION_AUTODISCOVERY_WAIT 0x20   // wait for make0 or AF before doing retardation discovery
#define RETARDER_OPTION_MAKE0DISCOVERY     0x40   // discover retardation value during make0 phase        
int atf_ReadCmRetarderAutoDetectConfigOptions (bool &bDoAutoDetectOnMake0, bool &bDoWaitAutoDetectToAf)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int option = 0;
	bDoAutoDetectOnMake0 = bDoWaitAutoDetectToAf = false;
	RET_ON_ERROR(pEpp->ReadArray ((void*)&option, 'U', 212, DtWordEnm));
	bDoAutoDetectOnMake0  = (option&RETARDER_OPTION_MAKE0DISCOVERY)		? true : false;
	bDoWaitAutoDetectToAf = (option&RETARDER_OPTION_AUTODISCOVERY_WAIT) ? true : false;
	return ErrOK;
}
int atf_WriteCmRetarderAutoDetectConfigOptions(bool bDoAutoDetectOnMake0,  bool  bDoWaitAutoDetectToAf)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int option = 0;

	RET_ON_ERROR(pEpp->ReadArray ((void*)&option, 'U', 212, DtWordEnm));
	if (bDoAutoDetectOnMake0)	option |=  RETARDER_OPTION_MAKE0DISCOVERY;
	else						option &= ~RETARDER_OPTION_MAKE0DISCOVERY;
	if (bDoWaitAutoDetectToAf)	option |=  RETARDER_OPTION_AUTODISCOVERY_WAIT;
	else						option &= ~RETARDER_OPTION_AUTODISCOVERY_WAIT;
	RET_ERROR(pEpp->WriteArray ((void*)&option, 'U', 212, DtWordEnm));
}
int atf_ScheduleCmRetarderAutoDetectForAF()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int code = CmAutoDetectStatusPending;
	RET_ERROR(pEpp->WriteArray ((void*)&code, 'U', 213, DtWordEnm));
}
int atf_StartCmRetarderAutoDetect() 
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int code = CmAutoDetectStatusDone;
	RET_ERROR(pEpp->WriteArray ((void*)&code, 'U', 213, DtWordEnm));
}
int atf_StopCmRetarderAutoDetect()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	int code = CmAutoDetectStop;
	RET_ERROR(pEpp->WriteArray ((void*)&code, 'U', 213, DtWordEnm));
}
CmAutoDetectEnum atf_ReadCmRetarderAutoDetectStatus() 
{
	CEpp *pEpp = CEppArr::Epp();
	if (!pEpp) return CmAutoDetectStatusFailed;
	CmAutoDetectEnum eadStatus = CmAutoDetectStatusFailed;
	RET_VAL_ON_ERROR(pEpp->ReadArray ((void*)&eadStatus, 'U', 213, DtWordEnm),eadStatus);
	return eadStatus;
}

// >>> --------------- Strobing -------------------------------------------------
int atf_ReadStrobePulseTime(int iLed, int *pStrobeTime)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	if (iLed!=1 && iLed!=2) return AfStatusOutOfBound;
	*pStrobeTime = 0;
	RET_ERROR(pEpp->ReadArray ((void*)pStrobeTime, 'U', 236, DtWordEnm, 1, iLed-1));
}
int atf_WriteStrobePulseTime(int iLed, int iStrobeTime)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	if (iLed!=1 && iLed!=2) return AfStatusOutOfBound;
	RET_ERROR(pEpp->WriteArray ((void*)&iStrobeTime, 'U', 236, DtWordEnm, 1, iLed-1));
}
int atf_ReadStrobeIntervalTime(int *pStrobeIntervalUs)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	*pStrobeIntervalUs = 0;
	RET_ERROR(pEpp->ReadArray ((void*)pStrobeIntervalUs, 'U', 237, DtDwordEnm));
}
int atf_WriteStrobeIntervalTime(int iStrobeIntervalUs)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&iStrobeIntervalUs, 'U', 237, DtDwordEnm));
}
int atf_Strobe(int iLed, int iNum, int iMaxError)
{
	short int stbcmd[4];
	stbcmd[0] = iLed;	// only 1,2 or 3
	stbcmd[1] = iNum;	// -1, 0, or someting
	stbcmd[2] = iMaxError;	// 0 or < 512
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&stbcmd, 'U', 235, DtWordEnm,iMaxError ? 3 : (iNum ? 2 : 1),0));
}
int atf_XyStrobeStart(int iNum, int iDistance)
{
	short int stbcmd[4];
	stbcmd[0] = 1;	
	stbcmd[1] = iNum;		// >0
	stbcmd[2] = iDistance;	// <= 127
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&stbcmd, 'U', 238, DtWordEnm,3,0));
}
int atf_XyStrobeStop()
{
	short int stbcmd[4];
	stbcmd[0] = 0;	
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&stbcmd, 'U', 238, DtWordEnm,1,0));
}
int atf_XyStrobeFreeRun()
{
	short int stbcmd[4];
	stbcmd[0] = 2;	
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&stbcmd, 'U', 238, DtWordEnm,1,0));
}

int atf_StrobeCount(int *pNumStb, int *pNumStbRequested, bool *pbStrobeActive)
{
	short unsigned int stbcmd[4];
	int emflags = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)&stbcmd, 'U', 235, DtWordEnm,4));
	*pNumStb = stbcmd[3];
	*pNumStbRequested = stbcmd[1]==0xffff ? -1 : stbcmd[1];
	RET_ON_ERROR(pEpp->ReadArray ((void*)&emflags, 't', 21, DtDwordEnm,1,1));
	*pbStrobeActive = (emflags&1) ? true : false;
	return ErrOK;
}
// <<< --------------- Strobing -------------------------------------------------

// >>> --------------- Hybrid hardware support -------------------------------------------------
int atf_ReadConfigExt (int iObj, int *pcfg)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pcfg, 'U', 57, DtDwordEnm,1,iObj));
}
int atf_SetConfigExt (int iObj, int mask, int cfg)
{
	int cfg_curr = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)&cfg_curr, 'U', 57, DtDwordEnm,1,iObj));
	mask &= (CeePZ1_Activate|CeePZ2_Activate|CeeZAA_Move|CeePZ_Move);
	cfg_curr &= ~mask;
	cfg_curr |= (cfg&mask);
	RET_ERROR(pEpp->WriteArray ((void*)&cfg_curr, 'U', 57, DtDwordEnm,1,iObj));
}
int atf_ReadMoveObjNum (int *pObj, int *pMoveObj)
{
	short int buff[2];
	buff[0] = buff[1] = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ON_ERROR(pEpp->ReadArray ((void*)buff, 'U', 50, DtWordEnm, 2));
	*pObj = buff[0];
	*pMoveObj = buff[1];
	return ErrOK;
}
int atf_WriteMoveObjNum(int iObj, int iMoveObj)
{
	short int buff[2];
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	buff[0] = iObj;
	buff[1] = iMoveObj;
	RET_ERROR(pEpp->WriteArray ((void*)buff, 'U', 50, DtWordEnm, 2));
}
int atf_ReadAbsZPosStage (enum StageSelectorEnum sse, int* pAbsZ, int *pMoveObj)
{
	int idx = sse;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	if (idx!=1 && idx!=2) return AfStatusOutOfBound;
	*pAbsZ = 0;
	RET_ON_ERROR(pEpp->ReadArray ((void*)pAbsZ, 'U', 233, DtDwordEnm, 1, idx-1));
	*pMoveObj = 0;
	RET_ERROR(pEpp->ReadArray ((void*)pMoveObj, 'U', 234, DtWordEnm, 1, idx-1));
}
int atf_ReadAoiFollowUp (int iObj, int *pObjFollowUp)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	*pObjFollowUp = 0;
	RET_ERROR(pEpp->ReadArray ((void*)pObjFollowUp, 'U', 232, DtWordEnm, 1, iObj));
}
int atf_WriteAoiFollowUp (int iObj, int iObjFollowUp)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void*)&iObjFollowUp, 'U', 232, DtWordEnm, 1, iObj));
}
// <<< --------------- Hybrid hardware support -------------------------------------------------

int atf_WriteMfcMotorParm (u_char* motor_parm)
{
	int iRet = 0;
	int iErr = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	iErr = pEpp->_ChangeCommTimeouts(CEpp::MotorParamTimeout);
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to change COM port timeouts. [ErrorNum=", iErr, "]\n");
	}

	iRet = pEpp->WriteArray ((void*)motor_parm, 't', 171, DtByteEnm, 5, 0);

	iErr = pEpp->_ResetCommTimeouts();
	if (iErr != ErrOK)
	{
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to reset COM port timeouts. [ErrorNum=", iErr, "]\n");
	}

	return iRet;
}

int atf_ReadAnalogOut (short &analog)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)&analog, 'U', 40, DtWordEnm)); 
}

int atf_ReadErrorCode (AtfCodesEnm *pcode)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void*)pcode, 'U', 42, DtDwordEnm)); 
}

int atf_ReadArray  (void *to,   int bid, int pid, EppDataType tag, int num, int offset)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray (to,bid,pid,tag,num,offset)); 
}

int atf_WriteArray (void *from, int bid, int pid, EppDataType tag, int num, int offset)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray (from,bid,pid,tag,num,offset)); 
}


// logging functions
// open log file
// Arguments:	pLogFilePath = pointer to the string - the log file path
//				pMode = pointer to the string - type of access permitted (see C fopen function)
bool atf_openLogFile(const char *pLogFilePath, const char *pMode)
{
	bool bRet = false;

	// open log file
	bRet = g_log.openLogFile(pLogFilePath, pMode);
	// check for errors
	if (bRet == false)
	{
		// ensure on failure that log level is in OFF state
		g_log.setLogLevel(CLogger::LogOff);	// failure
	}

// if success, remember to set logging level

	return bRet;
}

// close handle to the log file
bool atf_closeLogFile(void)
{
	return g_log.closeLogFile();
}

// set logger logging level
// Arguments:	iLogLevel = logging level from 0 (logging off) to 3 (save all messages)
void atf_setLogLevel(int iLogLevel)
{
	CLogger::LogLevels iLL = CLogger::LogOff;

	// check logging level value
	if (iLogLevel < 0)
	{
		iLL = CLogger::LogOff;	// logging off
	}
	else if (iLogLevel > 3)
	{
		iLL = CLogger::LogAll;	// logging all
	}
	else
	{
		iLL = (CLogger::LogLevels) iLogLevel;
	}

	g_log.setLogLevel(iLL);
}

// get log file handle
FILE *atf_getLogFileHandle()
{
	return g_log.getLogFileHandle();
}

// save messages in the log file - caller is responsible for allocating buffer for the message
// Arguments:	pLogMsg = pointer to message to be saved
//				iLogLevel = logging level from 0 (logging off) to 3 (save all messages)
// e.g. atf_saveToLog("Info: new baudrate=9600;\n", 1)
void atf_saveToLog(char *pLogMsg, int iLogLevel)
{
	g_log.saveToLog(pLogMsg, (CLogger::LogLevels) iLogLevel);
}

// save messages in the log file with variable-length argument list - the function is allocating buffer for the message
// Arguments: iLogLevel = logging level from 0 (logging off) to 3 (save all messages)
//			  pFormat = message formatting string
//			  ... = arguments according to formatting string
// e.g. atf_saveToLog2(1, "%s%d%s", "Info: new baudrate=", 9600, " ;\n")
void atf_saveToLog2(int iLogLevel, char *pFormat, ...)
{
    va_list args;
    int iLen = 0;
    char *pLogMsg = NULL;

    va_start(args, pFormat);
    
    iLen = _vscprintf(pFormat, args) + 1;
	pLogMsg = (char*)malloc(iLen * sizeof(char));

	if (pLogMsg != NULL)
	{
		vsprintf(pLogMsg, pFormat, args );
		g_log.saveToLog(pLogMsg, (CLogger::LogLevels) iLogLevel);
		free (pLogMsg);
	}
}

// serial port baudrate
// change serial Com port baudrate
int atf_ChangeCommBaudrate(DWORD dwBaudRate)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	return pEpp->ChangeCommBaudrate(dwBaudRate);
}

// get serial Com port baudrate
int atf_GetCommBaudrate(DWORD *dwBaudrate)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	return pEpp->GetCommBaudrate(dwBaudrate);
}

// check serial connection. if "true" serial connection is enabled
bool atf_isSerialConnection()
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN_BOOL
	return pEpp->isSerialConnection();
}

// LLC related functions

/**************************************************************************************************
*
* Function	 :	atf_initializeLlc
*
* Description:	Initialize LLC class.
*				Call this function to initialize LLC before any other LLC function - this function 
*				MUST be called first.
*
* Input		 :	pOffsetFileDir - directory for objective position offsets file (if specified MUST
*								 already exist) or can be NULL
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK			 = LLC initialization successful
*				- LlcErrSensorCom    = serial communication failure
*				- LlcErrObjectiveNum = failed to get available number of LLC objectives 
*									   (initialization is still successfull with this error)
*				- LlcErrOffsetFile	 = failed to create objective position offset file  - make your
*									   application current directory writable otherwise you will
*									   not be able to specify objective position offsets 
*									   (initialization is still successfull with this error) 
*
* Return	 :	true = success; false = failure
*
* Notice	 :	After runnig this function the piErrCode has to be examinned. In case of 
*				"LlcErrObjectiveNum" error call "setObjectiveNum" function and set the objective
*				number manually depends on which LLC model you have. Set: 2 for LLC2, 4 for LLC4, 6
*				for LLC6 or 8 for LLC8. The serial communication has to be opened first before
*				calling any LLC functions.
*
**************************************************************************************************/
bool atf_initializeLlc(char *pOffsetFileDir, int *piErrCode)
{
	return g_llc.initializeLlc(pOffsetFileDir, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_setObjectiveNum
*
* Description:	Set a number of available objectives for the LLC.
*				Call this function to finish LLC initialization if automatic detection of available
*				objective number failed.
*
* Input		 :	iObjNum - number of objectives available in user LLC model. Set: 2 for LLC2, 4 for 
*						  LLC4, 6 for LLC6 or 8 for LLC8.
*
* Output	 :	void
*
* Return	 :	void
*
* Notice	 :	To ensure if there is any need to set objective number parameter, call
*				"getObjectiveNum" function after call to "initializeLlc". If "getObjectiveNum" 
*				returns zero than use this function as shown in Input section above.
*
**************************************************************************************************/
void atf_setObjectiveNum(int iObjNum)
{
	return g_llc.setObjectiveNum(iObjNum);
}

/**************************************************************************************************
*
* Function	 :	atf_getObjectiveNum
*
* Description:	Get a number of available objectives for the LLC.
*				Call this function to get a number of available objectives for the LLC.
*
* Input		 :	void
*
* Output	 :	void
*
* Return	 :	int - a number of available objectives for the LLC
*
* Notice	 :	Use this function after call to "initializeLlc" function. If it returns zero than
*				call "setObjectiveNum" function (as described in the function header).
*
**************************************************************************************************/
int atf_getObjectiveNum()
{
	return g_llc.getObjectiveNum();
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcForcerSerNum
*
* Description:	Get LLC forcer serial number.
*				Call this function to get unique LLC forcer serial number.
*
* Input		 :	void
*
* Output	 :	void
*
* Return	 :	int - forcer serial number
*
* Notice	 :	This number is unique for each LLC/MFC pair system.
*
**************************************************************************************************/
int atf_getLlcForcerSerNum()
{
	return g_llc.getLlcForcerSerNum();
}

/**************************************************************************************************
*
* Function	 :	atf_sendLlc
*
* Description:	Process LLC command.
*				Call this function when sending command to LLC. This function is also waiting for 
*				LLC response. Use this function when implementing specific task not covered by CLlc
*				class, otherwise use already ready to use library functions.
*
* Input		 :	pToSend - pointer to buffer containing LLC command
*
* Output	 :	pToRecv - pointer to buffer for LLC response
*
* Return	 :	int - LLC error code returned by this function
*				- LlcErrOK			= processing LLC command successful
*				- LlcErrCmndSyntax	= LLC command syntax error - command to long
*				- LlcErrSendFailure = failed to send LLC command - COM port problem
*				- LlcErrSensorCom	= failed to receive LLC response - timeout
*				- LlcErrRecvLen		= incorrect LLC response - response to long
*				- LlcErrRecvSyntax	= incorrect LLC response - missing termination character or 
*									  missing LLC command echo or mismatch betweeen sent command and
*									  its echo
*				- LlcErrWhistleEC	= LLC responded with error - see log file for error details and
*									  documentation for Whistle Error Code meaning
*
* Notice	 :	This function is a replacement for CommToLlc function available in earlier versions
*				of the ATF library. Use this function - if required - in new applications.
*
**************************************************************************************************/
int atf_sendLlc(char *toSend, char *toRecv)
{
	return g_llc.sendLlc(toSend, toRecv);
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcStatus
*
* Description:	Get LLC status.
*				Call this function to get current LLC serial communication and hardware status.
*
* Input		 :	void
*
* Output	 :	piErrCode - error code indicating current LLC status
*				- LlcErrOK		      = LLC is in good operational state
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = failed to communicate with sensor, call 
*									    "recoverLlcSensorConnection" for an attempt to reinstate
*										serial communication
*				- LlcErrStatus	      = failed to get status register or motor failure register 
*										value from the sensor, retry this function again, if failed
*										with the same error code again call "recoverLlcHdwr"
*				- LlcErrLimitSwitch   = one of the limit switches is on
*				- LlcErrMotorDisabled = LLC motor is disabled
*				- LlcErrPeakCurrExceeded = hardware failure - peak current exceeded - to recover
*										call "recoverLlc" or "recoverLlcHdwr" function
*				- LlcErrInhibit		  =	hardware failure - inhibit - to recover	call "recoverLlc"
*										or "recoverLlcHdwr" function
*				- LlcErrSpeedTracking =	hardware failure - speed tracking error - to recover call 
*										"recoverLlc" or "recoverLlcHdwr" function
*				- LlcErrPositionTracking = hardware failure - position tracking error - to recover
*										call "recoverLlc" or "recoverLlcHdwr" function
*				- LlcErrUnderVoltage  =	hardware failure - under voltage error - examine LLC power
*										lines, restart application, to recover "recoverLlc" or
*										"recoverLlcHdwr" function may be called
*				- LlcErrOverVoltage   =	hardware failure - over voltage error - examine LLC power
*										lines, restart application, to recover "recoverLlc" or
*										"recoverLlcHdwr" function may be called
*				- LlcErrShortCircuit  =	hardware failure - short circuit - examin LLC wiring,
*										restart application, to recover "recoverLlc" or
*										"recoverLlcHdwr" function may be called
*				- LlcErrOverheating   =	hardware failure - motor overheating - examine LLC hardware,
*										restart application, to recover "recoverLlc" or
*										"recoverLlcHdwr" function may be called
*				- LlcErrElectricalZero = hardware failure - electrical zero not found - examine LLC
*										hardware, restart application, to recover "recoverLlc" or
*										"recoverLlcHdwr" function may be called
*				- LlcErrSpeedLimit	  = hardware failure - speed limit exceeded, examine LLC 
*										parameters, restart application, to recover "recoverLlc" or
*										"recoverLlcHdwr" function may be called
*				- LlcErrMotorStuck	  = hardware failure - motor not moving - examine LLC hardware,
*										restart application, to recover "recoverLlc" or
*										"recoverLlcHdwr" function may be called
*				- LlcErrPositionlimit =	hardware failure - position limit exceeded - examine LLC
*										hardware and parameters, restart application, to recover 
*										"recoverLlc" or	"recoverLlcHdwr" function may be called
*				- LlcErrStartMotor	  = hardware failure - cannot start motor - examine LLC
*										hardware, restart application, to recover "recoverLlc" or
*										"recoverLlcHdwr" function may be called
*				- LlcErrStackOverflow =	firmware failure - stack overflow - restart LLC
*				- LlcErrCpuException  =	frimware failure - CPU exception- restart LLC
*				ppErrMsg - error message information (see top of this file for all error messages)
*				piStatReg - status register - received with "SR;" command (see relevant bit
*							description on the top of llc.h file)
*				piMtrFailureReg - motor failure register - received with "MF;" command (see
*								  relevant bit description on the top of llc.h file)
*
* Return	 :	true = success; false = failure
*
* Notice	 :	In case of error - especially hardware failures - examine error message returned
*				with this function to undertake proper way to fix the problem. It may be beneficial
*				to examine additionally status register and motor failure register if needed.
*
**************************************************************************************************/
bool atf_getLlcStatus(int *piErrCode, const char **ppErrMsg, int *piStatReg, int *piMtrFailureReg)
{
	return g_llc.getLlcStatus(piErrCode, ppErrMsg, piStatReg, piMtrFailureReg);
}

/**************************************************************************************************
*
* Function	 :	atf_recoverLlc
*
* Description:	Recover LLC - serial communication to the sensor/LLC and LLC hardware.
*				Call this function to recover from serial communication failure to the sensor as 
*				well as from LLC hardware failure.
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = LLC recovery succeded
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrStatus		  = failed to get status register
*				- LlcErrRecoveryFailed = LLC attempted recovery failed on status register
*				- error codes returned by "recoverLlcSensorConnection" function
*				- error codes returned by "recoverLlcHdwr" function
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function is a wrapper for "recoverLlcSensorConnection" and "recoverLlcHdwr"
*				functions combined into one. An additional call is made to evaluate status register
*				to ensure LLC good health state.
*
**************************************************************************************************/
bool atf_recoverLlc(int *piErrCode)
{
	return g_llc.recoverLlc(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_recoverLlcSensorConnection
*
* Description:	Restore communication with the sensor / LLC.
*				Call this function to test or to restore serial communication with the sensor / LLC.
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = LLC serial communication recovery succeded
*				- LlcErrSensorCom	  = serial communication not working at all
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function is restoring communication with the sensor / LLC if at least the 
*				communication with the bootloader, Whistle or MFC is detected. The call to 
*				"getLlcStatus" function may be performed first before calling this function. The
*				function is also called from within "recoverLlc" function for serial communication 
*				and hardware recovery.
*
**************************************************************************************************/
bool atf_recoverLlcSensorConnection(int *piErrCode)
{
	return g_llc.recoverLlcSensorConnection(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_recoverLlcHdwr
*
* Description:	Recover from LLC hardware error.
*				Call this function to restore LLC hardware functionality in case of hardware error.
*				One of the recovery step is LLC homing what may take up to 10 seconds.
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = LLC hardware recovery succeded
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- error codes returned by "resetLlcController" function
*				- error codes returned by "homeLlc" function
*
* Return	 :	true = success; false = failure
*
* Notice	 :	Call to	"getLlcStatus" function may be performed first before calling this function
*				to ensure hardware failure. The function is also called from within "recoverLlc" 
*				function for serial communication and hardware recovery.
*
**************************************************************************************************/
bool atf_recoverLlcHdwr(int *piErrCode)
{
	return g_llc.recoverLlcHdwr(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_resetLlcController
*
* Description:	Reset LLC controller.
*				Call this function to reset LLC controller, i.e.: disable the motor, perform soft
*				reset and load all non-volatile variables from the flash memory to the RAM and 
*				reset all volatile variables to their default values.
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = LLC resetting controller succeded
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom    = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	The function is also called from within "recoverLlcHdwr" function as a part of
*				hardware recovery.
*
**************************************************************************************************/
bool atf_resetLlcController(int *piErrCode)
{
	return g_llc.resetLlcController(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_homeLlc
*
* Description:	Move LLC into home position.
*				Call this function to move LLC into home position. The function may exit 
*				immediatelly (bWaitForEnd = false) or wait until the home position is reached
*				(bWaitForEnd = true). When choosing first option call "isLlcInHomePos" function
*				periodically to check for the end of the homing procedure.
*
* Input		 :	bWaitForEnd - false = exit function immediatelly
*							  true  = exit function on the end of homing
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = homing LLC succeded
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom    = serial communication failure
*				- LlcErrTimeout		 = failed to reach home position before timeout
*				- error codes returned by "isLlcInHomePos" function
*
* Return	 :	true = success; false = failure
*
* Notice	 :	The function is also called from within "recoverLlcHdwr" function as a part of
*				hardware recovery. The homing procedure may take up to 10 seconds. It is worthy to
*				mention that this function is enabling the LLC motor internally.
*
**************************************************************************************************/
bool atf_homeLlc(bool bWaitForEnd, int *piErrCode)
{
	return g_llc.homeLlc(bWaitForEnd, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_isLlcInHomePos
*
* Description:	Check if LLC reached its home position.
*				Call this function to check if LLC reached its home position. The function should
*				be called periodically to determine homing status after calling "homeLlc" function
*				(assuming that "homeLlc" was called with "bWaitForEnd = false" argument, otherwise
*				there is no need to call this function).
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected (does not mean that it reached home 
*										position) 
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*				- LlcErrHoming		  = failed to reach home position - incorrect final status
*				- LlcErrStatus		  = failed to reach home position - incorrect motion status or 
*									    motor status
*
* Return	 :	true = success (in home postion); false = failure (not in home position yet)
*
* Notice	 :	The function is also called from within "homeLlc" function if "bWaitForEnd = true"
*				argument is specified. The homing procedure may take up to 10 seconds.
*
**************************************************************************************************/
bool atf_isLlcInHomePos(int *piErrCode)
{
	return g_llc.isLlcInHomePos(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_saveLlcObjectivePositionOffset
*
* Description:	Save objective position offset into LLC offset file.
*				Call this function to save objective position offset for each objective. The
*				default value of all offsets are zero. The value of the offset is taken into
*				account	when moving LLC into any requested objective position.
*
* Input		 :	iObjectiveNumber - objective number (0 to 1 for LLC2, 0 to 3 for LLC4,
*													(0 to 5 for LLC6, 0 to 7 for LLC8)
*				iPositionOffset	- objective position offset [in um] for requested objective
*								  (max/min value: +/- 1000 um)
*
* Output	 :	void
*
* Return	 :	true = success; false = failure
*
* Notice	 :	The function will fail if "initializeLlc" was not able to create the file.
*
**************************************************************************************************/
bool atf_saveLlcObjectivePositionOffset(int iObjectiveNumber, int iOffset)
{
	return g_llc.saveLlcObjectivePositionOffset(iObjectiveNumber, iOffset);	
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcObjectivePositionOffset
*
* Description:	Get objective position offset value from LLC offset file.
*				Call this function to get objective position offset for any objective. The
*				default value of all offsets are zero. The value of the offset is taken into
*				account	when moving LLC into any requested objective position.
*
* Input		 :	iObjectiveNumber - objective number (0 to 1 for LLC2, 0 to 3 for LLC4,
*													(0 to 5 for LLC6, 0 to 7 for LLC8)
*
* Output	 :	piPositionOffset - objective position offset [in um] for requested objective
*
* Return	 :	true = success; false = failure
*
* Notice	 :	The function will fail if "initializeLlc" was not able to create the file.
*
**************************************************************************************************/
bool atf_getLlcObjectivePositionOffset(int iObjectiveNumber, int *piPositionOffset)
{
	return g_llc.getLlcObjectivePositionOffset(iObjectiveNumber, piPositionOffset);
}

/**************************************************************************************************
*
* Function	 :	atf_moveLlcToObjective
*
* Description:	Move LLC to requested objective position.
*				Call this function to move LLC to requested objective position. The function may 
*				exit immediatelly (bWaitForEnd = false) or wait until the target objective position
*				is reached (bWaitForEnd = true). When choosing first option call 
*				"isLlcInTargetPosition" function periodically to check for the end of the moving
*				procedure.
*
* Input		 :	iObjectiveNumber - objective number (0 to 1 for LLC2, 0 to 3 for LLC4,
*													(0 to 5 for LLC6, 0 to 7 for LLC8)
*				bWaitForEnd - false = exit function immediatelly
*							  true  = exit function on the end of moving
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = moving LLC to objective position succeded
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrArgRange	  = objective number not in range
*				- LlcErrSensorCom     = serial communication failure 
*				- LlcErrStatus		  = LLC status shows error preventing the movement
*				- LlcErrTimeout		  = failed to reach target position before timeout
*				- error codes returned by "isLlcInTargetPosition" function
*
* Return	 :	true = success; false = failure
*
* Notice	 :	When using this function a value saved in the objective position offset file is
*				taken into account (offset default value is equal zero). The target objective 
*				position is	calculated using the following formula:
*				- for LLC2:		
*				  (ObjectiveNumber[=0 to 1] * ObjectivePositionPitch[=35000]) + ObjectivePositionOffset
*				- for LLC4/6/8:	
*				  (ObjectiveNumber[=0 to 7] * ObjectivePositionPitch[=38000]) + ObjectivePositionOffset 
*
**************************************************************************************************/
bool atf_moveLlcToObjective(int iObjectiveNumber, bool bWaitForEnd, int *piErrCode)
{
	return g_llc.moveLlcToObjective(iObjectiveNumber, bWaitForEnd, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_moveLlcToObjective2
*
* Description:	Move LLC to requested objective position.
*				Call this function to move LLC to requested objective position. The function may 
*				exit immediately (bWaitForEnd = false) or wait until the target objective position
*				is reached (bWaitForEnd = true). When choosing first option call 
*				"isLlcInTargetPosition" function periodically to check for the end of the moving
*				procedure.
*				In contrary to atf_moveLlcToObjective this function does not check for the LLC status before move
*
* Input		 :	iObjectiveNumber - objective number (0 to 1 for LLC2, 0 to 3 for LLC4,
*													(0 to 5 for LLC6, 0 to 7 for LLC8)
*				bWaitForEnd - false = exit function immediately
*							  true  = exit function on the end of moving
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = moving LLC to objective position succeeded
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrArgRange	  = objective number not in range
*				- LlcErrSensorCom     = serial communication failure 
*				- LlcErrStatus		  = LLC status shows error preventing the movement
*				- LlcErrTimeout		  = failed to reach target position before timeout
*				- error codes returned by "isLlcInTargetPosition" function
*
* Return	 :	true = success; false = failure
*
* Notice	 :	When using this function a value saved in the objective position offset file is
*				taken into account (offset default value is equal zero). The target objective 
*				position is	calculated using the following formula:
*				- for LLC2:		
*				  (ObjectiveNumber[=0 to 1] * ObjectivePositionPitch[=35000]) + ObjectivePositionOffset
*				- for LLC4/6/8:	
*				  (ObjectiveNumber[=0 to 7] * ObjectivePositionPitch[=38000]) + ObjectivePositionOffset 
*
**************************************************************************************************/
bool atf_moveLlcToObjective2(int iObjectiveNumber, bool bWaitForEnd, int *piErrCode)
{
	return g_llc.moveLlcToObjective2(iObjectiveNumber, bWaitForEnd, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_moveLlcToPosition
*
* Description:	Move LLC to requested target position.
*				Call this function to move LLC to requested target position. The function may 
*				exit immediatelly (bWaitForEnd = false) or wait until the requested target position
*				is reached (bWaitForEnd = true). When choosing first option call 
*				"isLlcInTargetPosition" function periodically to check for the end of the moving
*				procedure.
*
* Input		 :	iPosition - target position in um
*				bWaitForEnd - false = exit function immediatelly
*							  true  = exit function on the end of moving
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = moving LLC to requested target position succeded
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrArgRange	  = target position value not in range
*				- LlcErrSensorCom    = serial communication failure
*				- LlcErrStatus		  = LLC status shows error preventing the movement
*				- LlcErrTimeout		 = failed to reach target position before timeout
*				- error codes returned by "isLlcInTargetPosition" function
*
* Return	 :	true = success; false = failure
*
* Notice	 :	When using this function a value saved in the objective position offset file is
*				NOT taken into account. The target position has to be in the following range:
*				- for LLC2:
*				-MaxPositionOffset[=-1000] =< TargetPosition =< (MaxObjectiveNumber[=1] * ObjectivePositionPitch[=35000]) + MaxPositionOffset[=1000]
*				- for LLC4/6/8:	
*				-MaxPositionOffset[=-1000] =< TargetPosition =< (MaxObjectiveNumber[=3, 5 or 7] * ObjectivePositionPitch[=38000]) + MaxPositionOffset[=1000]
*
**************************************************************************************************/
bool atf_moveLlcToPosition(int iPosition, bool bWaitForEnd, int *piErrCode)
{
	return g_llc.moveLlcToPosition(iPosition, bWaitForEnd, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_moveLLcRelativeDistance
*
* Description:	Move LLC by requested distance in relation to its current position.
*				Call this function to move LLC by requested distance in relation to its current
*				position. The function may exit immediatelly (bWaitForEnd = false) or wait until
*				the requested target position is reached (bWaitForEnd = true). When choosing first
*				option call	"isLlcInTargetPosition" function periodically to check for the end
*				of the moving procedure.
*
* Input		 :	iDistance - distance to move in um
*				bWaitForEnd - false = exit function immediatelly
*							  true  = exit function on the end of moving
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = moving LLC to requested target position succeded
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrArgRange	  = distance to move value not in range
*				- LlcErrSensorCom    = serial communication failure
*				- LlcErrStatus		  = LLC status shows error preventing the movement
*				- LlcErrTimeout		 = failed to reach target position before timeout
*				- error codes returned by "isLlcInTargetPosition" function
*
* Return	 :	true = success; false = failure
*
* Notice	 :	When using this function a value saved in the objective position offset file is NOT
*				taken into account. The aim of this function is to allow small LLC movements in
*				relation to current position. The distance has to be in the following range:
*				- LLC2/4/6/8:
*				-MaxPositionOffset[=-1000] =< Distance =< MaxPositionOffset[=1000]
*
**************************************************************************************************/
bool atf_moveLLcRelativeDistance(int iDistance, bool bWaitForEnd, int *piErrCode)
{
	return g_llc.moveLLcRelativeDistance(iDistance, bWaitForEnd, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_isLlcInTargetPosition
*
* Description:	Check if LLC reached its requested target position.
*				Call this function to check if LLC reached its home position. The function should
*				be called periodically to determine movement status after calling 
*				"moveLlcToObjective", "moveLlcToPosition" or "moveLLcRelativeDistance" function
*				(assuming that these functions were called with "bWaitForEnd = false" argument, 
*				otherwise there is no need to call this function). The function returns if the 
*				target is reached within +/- MaxInPositionRange [=5um].
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected (does not mean that it reached target 
*										position) 
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*				- LlcErrTargetPos	  = failed to reach target position - incorrect final status
*
* Return	 :	true = success (in target postion); false = failure (not in target position yet)
*
* Notice	 :	The function is also called from within "moveLlcToObjective", "moveLlcToPosition"
*				and "moveLLcRelativeDistance" functions if "bWaitForEnd = true"	argument is
*				specified.
*
**************************************************************************************************/
bool atf_isLlcInTargetPosition(int *piErrCode)
{
	return g_llc.isLlcInTargetPosition(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_enableLlcMotor
*
* Description:	Enable LLC motor power.
*				Call this function to enable LLC motor. To make LLC operational the "homeLlc" 
*				function has to be called too.
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*				- LlcErrStatus		  = failed to enable LLC motor
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function is also called internally by "homeLlc" function.
*
**************************************************************************************************/
bool atf_enableLlcMotor(int *piErrCode)
{
	return g_llc.enableLlcMotor(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_disableLlcMotor
*
* Description:	Disable LLC motor power.
*				Call this function to disable LLC motor. This action invalidates LLC home position.
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*				- LlcErrStatus		  = failed to disable LLC motor
*
* Return	 :	true = success; false = failure
*
* Notice	 :	When enabling LLC motor again the home procedure has to be run again.
*
**************************************************************************************************/
bool atf_disableLlcMotor(int *piErrCode)
{
	return g_llc.disableLlcMotor(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_stopLlcMotion
*
* Description:	Stop LLC motion.
*				Call this function to stop LLC motion.
*
* Input		 :	void
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*				- LlcErrStatus		  = failed to stop LLC motion
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to stop motor motion in emergency cases.
*
**************************************************************************************************/
bool atf_stopLlcMotion(int *piErrCode)
{
	return g_llc.stopLlcMotion(piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_setLlcSpeed
*
* Description:	Set LLC motor speed.
*				Call this function to set LLC motor speed parameter. The speed range limits are as
*				follow:
*				- minimum speed = 1    mm/s
*				- maximum speed = 1000 mm/s
*
* Input		 :	iLlcSpeed - LLC motor speed value
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to modify factory set default speed value
*				(default speed = 900 mm/s).
*
**************************************************************************************************/
bool atf_setLlcSpeed(int iLlcSpeed, int *piErrCode)
{
	return g_llc.setLlcSpeed(iLlcSpeed, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcSpeed
*
* Description:	Get LLC motor speed.
*				Call this function to get LLC motor speed parameter. The speed range limits are as
*				follow:
*				- minimum speed = 1    mm/s
*				- maximum speed = 1000 mm/s
*
* Input		 :	void
*
* Output	 :	piLlcSpeed - LLC motor speed value
*				piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to get currently set LLC speed value parameter
*				(default speed = 900 mm/s).
*
**************************************************************************************************/
bool atf_getLlcSpeed(int *piLlcSpeed, int *piErrCode)
{
	return g_llc.getLlcSpeed(piLlcSpeed, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_setLlcAcceleration
*
* Description:	Set LLC motor acceleration.
*				Call this function to set LLC motor acceleration parameter. The acceleration range
*				limits are as follow:
*				- minimum acceleration = 100  mm/s/s
*				- maximum acceleration = 8500 mm/s/s
*
* Input		 :	iLlcAcceleration - LLC motor acceleration value
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to modify factory default set acceleration value
*				(default acceleration = 6500 mm/s/s).
*
**************************************************************************************************/
bool atf_setLlcAcceleration(int iLlcAcceleration, int *piErrCode)
{
	return g_llc.setLlcAcceleration(iLlcAcceleration, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcAcceleration
*
* Description:	Get LLC motor acceleration.
*				Call this function to get LLC motor acceleration parameter. The acceleration range
*				limits are as follow:
*				- minimum acceleration = 100  mm/s/s
*				- maximum acceleration = 8500 mm/s/s
*
* Input		 :	void
*
* Output	 :	piLlcAcceleration - LLC motor acceleration value
*				piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to get currently set LLC acceleration value parameter
*				(default acceleration = 6500 mm/s/s).
*
**************************************************************************************************/
bool atf_getLlcAcceleration(int *piLlcAcceleration, int *piErrCode)
{
	return g_llc.getLlcAcceleration(piLlcAcceleration, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_setLlcDeceleration
*
* Description:	Set LLC motor deceleration.
*				Call this function to set LLC motor deceleration parameter. The deceleration range
*				limits are as follow:
*				- minimum deceleration = 100  mm/s/s
*				- maximum deceleration = 8500 mm/s/s
*
* Input		 :	iLlcDeceleration - LLC motor deceleration value
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to modify factory default set deceleration value
*				(default deceleration = 7500 mm/s/s).
*
**************************************************************************************************/
bool atf_setLlcDeceleration(int iLlcDeceleration, int *piErrCode)
{
	return g_llc.setLlcDeceleration(iLlcDeceleration, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcDeceleration
*
* Description:	Get LLC motor deceleration.
*				Call this function to get LLC motor deceleration parameter. The deceleration range
*				limits are as follow:
*				- minimum deceleration = 100  mm/s/s
*				- maximum deceleration = 8500 mm/s/s
*
* Input		 :	void
*
* Output	 :	piLlcDeceleration - LLC motor deceleration value
*				piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to get currently set LLC deceleration value parameter
*				(default deceleration = 7500 mm/s/s).
*
**************************************************************************************************/
bool atf_getLlcDeceleration(int *piLlcDeceleration, int *piErrCode)
{
	return g_llc.getLlcDeceleration(piLlcDeceleration, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_setLlcSmoothFactor
*
* Description:	Set LLC motor smooth factor.
*				Call this function to set LLC motor smooth factor parameter. The smooth factor
*				range limits are as follow:
*				- minimum smooth factor = 0   ms
*				- maximum smooth factor = 100 ms
*				The price for smoothing is that the total time required for completing the motion 
*				increases.
*
* Input		 :	iLlcSmoothFactor - LLC motor smooth factor value
*
* Output	 :	piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*				- LlcErrStatus		  = the smooth factor can not be set - motor is enabled
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to modify factory set default smooth factor value
*				(default smooth factor = 10 ms). This parameter can be set only when LLC motor is
*				disabled.
*
**************************************************************************************************/
bool atf_setLlcSmoothFactor(int iLlcSmoothFactor, int *piErrCode)
{
	return g_llc.setLlcSmoothFactor(iLlcSmoothFactor, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcSmoothFactor
*
* Description:	Get LLC motor smooth factor.
*				Call this function to get LLC motor smooth factor parameter. The smooth factor
*				range limits are as follow:
*				- minimum smooth factor = 0   ms
*				- maximum smooth factor = 100 ms
*				The price for smoothing is that the total time required for completing the motion 
*				increases.
*
* Input		 :	void
*
* Output	 :	piLlcSmoothFactor - LLC motor smooth factor value
*				piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to get currently set LLC smooth factor value parameter
*				(default smooth factor = 10 ms).
*
**************************************************************************************************/
bool atf_getLlcSmoothFactor(int *piLlcSmoothFactor, int *piErrCode)
{
	return g_llc.getLlcSmoothFactor(piLlcSmoothFactor, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcVelocity
*
* Description:	Get LLC motor velocity.
*				Call this function to get LLC current motor velocity.
*
* Input		 :	void
*
* Output	 :	pfLlcVelocity - LLC motor speed value
*				piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to get current motion velocity while motor is moving.
*
**************************************************************************************************/
bool atf_getLlcVelocity(float *pfLlcVelocity, int *piErrCode)
{
	return g_llc.getLlcVelocity(pfLlcVelocity, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcPosition
*
* Description:	Get LLC motor position.
*				Call this function to get LLC current motor position.
*
* Input		 :	void
*
* Output	 :	pfLlcPosition - LLC motor current position value
*				piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to get current motor position while it is moving or it is
*				stationary.
*
**************************************************************************************************/
bool atf_getLlcPosition(float *pfLlcPosition, int *piErrCode)
{
	return g_llc.getLlcPosition(pfLlcPosition, piErrCode);
}

/**************************************************************************************************
*
* Function	 :	atf_getLlcMotorCurrent
*
* Description:	Get LLC motor current.
*				Call this function to get LLC motor active and reactive currents.
*
* Input		 :	void
*
* Output	 :	pfLlcMotorCurrent - LLC motor current position value
*				piErrCode - error code returned by this function
*				- LlcErrOK		      = no problem detected
*				- LlcErrNotInitialized = LLC is not initialized yet, call "initializeLlc" function
*										first
*				- LlcErrSensorCom     = serial communication failure
*
* Return	 :	true = success; false = failure
*
* Notice	 :	This function may be used to get motor current while it is moving or it is
*				stationary.
*
**************************************************************************************************/
bool atf_getLlcMotorCurrent(float *pfLlcMotorCurrent, int *piErrCode)
{
	return g_llc.getLlcMotorCurrent(pfLlcMotorCurrent, piErrCode);
}

// This LLC function is here for backward compatibility - should NOT be used for new applications
// use sendLlc in CLlc if such low level communication is required
int atf_CommToLlc (char* to_send, char* to_read)
{
	const char *pFunName = "CommToLlc";

	char read_buf[64];
	int send_num = (int)strlen(to_send);
	int rcv_num  = 0;
	int rty = 0;
	int error = -6;
	int iRet = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	ENTERFUN(pFunName);

	if (send_num >= 64)
	{
		error = -1;

		LOGMSG2(CLogger::LogAll, "%s%s%s%d%s", 
			    "Error: Failed to execute LLC command: \"", to_send, 
				"\" - command to long. [ErrorNum=", error, "]\n");

		goto exitfun;
	}

	for (int repeat = 2; repeat; repeat--)
	{
		LOGMSG2(CLogger::LogLow, "%s%s%s", "Info: Send command to LLC: \"", to_send, "\".\n");

		iRet = pEpp->WriteArray ((void*)to_send, 'f', 100, DtByteEnm, send_num, 0);

		if (iRet != ErrOK)
		{
			LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to send LLC command [ErrorNum=", iRet, "]\n");
			continue;
		}

		memset (read_buf, 0, 64);
		rcv_num = 0;

		// basic wait time for response
		Sleep(send_num * gs_read_delay + 4);

		// wait a little bit longer for RS command
		if (_stricmp(to_send, "RS;") == 0)
		{
			rty = 100;
		}
		else
		{
			rty = 50;
		}

		while (rty-- > 0)
		{
			iRet = pEpp->ReadArray((void*)(read_buf + rcv_num), 'f', 100, DtByteEnm, 62-rcv_num, 0);

			if (iRet != ErrOK)
			{
				LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to get LLC response. [ErrorNum=", iRet, "]\n");
				Sleep(3);
				continue;
			}

			rcv_num = (int)strlen(read_buf);

			if (rcv_num >= 61) 
			{
				// unexpected number of characters received
				LOGMSG2(CLogger::LogAll, "%s%d%s", 
						"Error: Failed to get LLC response - unexpected number of characters received [ResponseLen=",
						rcv_num, "].\n");
				LOGMSG2(CLogger::LogLow, "%s%32s %s%s",
						"Info: Failed LLC response: \"", read_buf,
						(rcv_num > 32) ? "..." : "", "\".\n");

				error = -4;
				goto one_more_time;
			}

			// the response is terminated with ";"
			if (rcv_num > send_num && read_buf[rcv_num-1] == ';') 
			{
				break; // last byte is terminator
			}

			Sleep(10);
		}

		if (rty < 0) 
		{
			LOGMSG2(CLogger::LogAll, "%s%d%s", 
					"Error: Failed to get LLC response - no termination character [ResponseLen=", 
					rcv_num, "].\n");
			LOGMSG2(CLogger::LogLow, "%s%s%s", 
					"Info: Failed LLC response: \"",
					(rcv_num > 0) ? read_buf : "", "\".\n");

			error = -1;	// can't get termination ;

			// cleanout partial command
			LOGMSG("Info: Send command to LLC: \";\".\n", CLogger::LogLow);

			iRet = pEpp->WriteArray ((void*)";", 'f', 100, DtByteEnm, 1, 0);

			if (iRet != ErrOK)
			{
				LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to send LLC cleanout command. [ErrorNum=", error, "]\n");
			}

			Sleep(10);
			iRet = pEpp->ReadArray((void*)(read_buf), 'f', 100, DtByteEnm, 62, 0);

			if (iRet != ErrOK)
			{
				LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to get response to LLC cleanout command. [ErrorNum=", iRet, "]\n");
			}

			goto one_more_time;
		}
		
		if (rcv_num <= send_num) 
		{
			LOGMSG("Error: Failed to receive LLC response - response to short.\n", CLogger::LogLow);
			LOGMSG2(CLogger::LogLow, "%s%s%s", 
					"Info: Failed LLC response: \"", 
					(rcv_num > 0) ? read_buf : "", "\".\n");

			error = -2;	// elmo always suppose to repeat what was send
			goto one_more_time;
		}

		// verify that leading echo characters are the same
		if (_strnicmp(read_buf, to_send, send_num) != 0)
		{
			LOGMSG("Error: Failed to receive LLC response - leading echo characters mismatch.\n", CLogger::LogLow);
			LOGMSG2(CLogger::LogLow, "%s%s%s",
					"Info: Failed LLC response: \"",
					(rcv_num > 0) ? read_buf : "", "\".\n");

			error = -3;	// some mismatch
			goto one_more_time;
		}

		// also verify that character before ; is not ?, in this case command was garbled
		if (read_buf[rcv_num - 2] == '?') 
		{			
			error = ((unsigned char)read_buf[rcv_num - 3]);	// error as detected by whistle

			LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: Failed to receive LLC response - garbled response.[WhistleError=", error, "]\n");
			LOGMSG2(CLogger::LogLow, "%s%s%s",
					"Info: Failed LLC response: \"",
					(rcv_num > 0) ? read_buf : "", "\".\n");

			switch(error) 
			{
			case 2 :		// those are error codes indicating syntax problem
			case 3 :
			case 5 :
			case 18 :
			case 19 :
			case 24 :
			case 42:
			goto one_more_time;
			default:
				goto exitfun;
			}
		}

		// all is OK
		error = ErrOK;
		break;

		// one more time
one_more_time:
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: LLC Error First, cleaning up. [ErrorNum=", error, "]\n");
	}

	if (error)	
	{
		*to_read = '\0';
		LOGMSG2(CLogger::LogAll, "%s%d%s", "Error: LLC Error Final. [ErrorNum=", error, "]\n");
	}
	else 
	{
		LOGMSG2(CLogger::LogLow, "%s%s%s", "Info: LLC response: \"", read_buf, "\".\n");
		strcpy (to_read, read_buf+send_num);
		to_read[strlen(to_read) - 1] = '\0';
	}

exitfun:
	EXITFUN(pFunName);
	return error;
}

// Homing Z

/**************************************************************************************************
*
* Function	 :	atf_ReadHomingZ_Parameters
*
* Description:	Get homing Z parameters.
*				Call this function to get homing Z parameters. The argument passed to the function
*				represents an array of eight integers. First four parameters contain Z distance to
*				move [in um] and next four parameters contain Z speed [in um/s] for four independent
*				motions.
*
* Input		 :	void
*
* Output	 :	pHomingZ_Parameters - the pointer to an array of eight integers
*
* Return	 :	0 = success; >0 = failure
*
* Notice	 :	Homing functionality allows to restore same Z position regardless of the starting Z. 
*				Homing is using limit switches as a reference. In order to provide increased 
*				accuracy up to 4 motions could be defined that allows to cross limit switch at 
*				constant speed.
*
**************************************************************************************************/
int atf_ReadHomingZ_Parameters(int *pHomingZ_Parameters)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->ReadArray ((void *)pHomingZ_Parameters, 'U', 76, DtDwordEnm, 8, 0));
}

/**************************************************************************************************
*
* Function	 :	atf_WriteHomingZ_Parameters
*
* Description:	Set homing Z parameters.
*				Call this function to set homing Z parameters. The argument passed to the function
*				represents an array of eight integers. First four parameters contain Z distance to
*				move [in um] and next four parameters contain Z speed [in um/s] for four independent
*				motions.
*
* Input		 :	pHomingZ_Parameters - the pointer to an array of eight integers
*
* Output	 :	void
*
* Return	 :	0 = success; >0 = failure
*
* Notice	 :	Homing functionality allows to restore same Z position regardless of the starting Z. 
*				Homing is using limit switches as a reference. In order to provide increased 
*				accuracy up to 4 motions could be defined that allows to cross limit switch at 
*				constant speed.
*
**************************************************************************************************/
int atf_WriteHomingZ_Parameters(int *pHomingZ_Parameters)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void *)pHomingZ_Parameters, 'U', 76, DtDwordEnm, 8, 0));
}

/**************************************************************************************************
*
* Function	 :	atf_RunHomingZ
*
* Description:	Run homing Z procedure.
*				Call this function to run homing Z procedure. The argument passed to the function
*				represents an array of eight integers. First four parameters contain Z distance to
*				move [in um] and next four parameters contain Z speed [in um/s] for four independent
*				motions. The argument can be also NULL, in such case the homing Z parameters are
*				taken from the sensor memory.
*
* Input		 :	pHomingZ_Parameters - the pointer to an array of eight integers or NULL
*
* Output	 :	void
*
* Return	 :	0 = success; >0 = failure
*
* Notice	 :	Homing functionality allows to restore same Z position regardless of the starting Z. 
*				Homing is using limit switches as a reference. In order to provide increased 
*				accuracy up to 4 motions could be defined that allows to cross limit switch at 
*				constant speed.
*
**************************************************************************************************/
int atf_RunHomingZ(int *pHomingZ_Parameters)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	if (pHomingZ_Parameters)
	{
		RET_ERROR(pEpp->WriteArray ((void *)pHomingZ_Parameters, 'U', 98, DtDwordEnm, 8, 0));
	}
	else
	{
		RET_ERROR(pEpp->WriteArray ((void *)0, 'U', 98, DtDwordEnm, 0, 0));
	}
}

/**************************************************************************************************
*
* Function	 :	atf_IsInHomePosition
*
* Description:	Test if homing Z procedure is finished.
*				Call this function to check if homing Z procedure is finished. 
*
* Input		 :	void
*
* Output	 :	pbInHome - true = in home; false = not in home;
*
* Return	 :	0 = success; >0 = failure
*
* Notice	 :	Homing functionality allows to restore same Z position regardless of the starting Z. 
*				Homing is using limit switches as a reference. In order to provide increased 
*				accuracy up to 4 motions could be defined that allows to cross limit switch at 
*				constant speed.
*
**************************************************************************************************/
int atf_IsInHomePosition(bool *pbInHome)
{
	int iFlags = 0;
	int iErr = 0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	iErr = pEpp->ReadArray ((void *)&iFlags, 't', 21, DtDwordEnm, 1, 0);

	if (iErr == ErrOK) 
	{
		*pbInHome = (iFlags & 0x8) ? false : true;    // bit 0x08 is homing false if homing is still being executed
	}

	return iErr;      // error of some sort 
}

// Jogging Z

/**************************************************************************************************
*
* Function	 :	atf_StartJoggingZ
*
* Description:	Start jogging Z procedure.
*				Call this function to initiate continuous Z movement with requested speed. To stop
*				the movement call atf_StopZMotor function. The sign of the speed value influences
*				direction of movement.
*
* Input		 :	void
*
* Output	 :	iSpeed - the Z movement motor speed [in um/s] 
*
* Return	 :	0 = success; >0 = failure
*
* Notice	 :	The typical speed values are in the range: +/-1000 - +/-10000 [um/s]
*
**************************************************************************************************/
int atf_StartJoggingZ(int iSpeed)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	RET_ERROR(pEpp->WriteArray ((void *)&iSpeed, 'U', 99, DtDwordEnm, 1, 1));
}



//sensor measurement 
/**************************************************************************************************
*
* Function	 :	aft_WriteMeasInterval
*
* Description:	Call this function to set measurement sampling interval.
*				
*
* Input		 :  iMeasIntervalUS-measurement sampling interval in micro seconds, the default and Min. value is 800 us;
*			 
*
* Return	 :	0 = success; >0 = failure
*
**************************************************************************************************/

int atf_WriteMeasInterval(unsigned short iMeasIntervalUS)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN 

	if(iMeasIntervalUS <800) iMeasIntervalUS =800;

	RET_ERROR(pEpp->WriteArray ((void *)&iMeasIntervalUS, 'U', 218, DtWordEnm, 1,0));
	
}

//sensor measurement 
/**************************************************************************************************
*
* Function	 :	atf_ReadMeasInterval
*
* Description:	Call this function to read measurement sampling interval.
*				
*
* Input		 :  iMeasIntervalUS-measurement sampling interval in micro seconds, the default and Min. value is 800 us;
*			 
*
* Return	 :	0 = success; >0 = failure
*
**************************************************************************************************/


int atf_ReadMeasInterval(unsigned short* iMeasIntervalUS)
{
	CEPPARR_DECLARE_CURRENT_OR_RETURN 

	RET_ERROR(pEpp->ReadArray ((void *)iMeasIntervalUS, 'U', 218, DtWordEnm, 1,0));

}

//sensor measurement 
/**************************************************************************************************
*
* Function	 :	atf_EnableMeasurement
*
* Description:	Start sensor measurement function.
*				Call this function to initiate or stop sensor measurement function
*
* Input		 :	bEnable- true to start the measurement function, false to top the function
*			 :  iMeasIntervalUS-measurement sampling interval in micro seconds, the default and Min. value is 800 us;
*
* Return	 :	0 = success; >0 = failure
*
**************************************************************************************************/

int atf_EnableMeasurement(bool bEnable)
{
	short iFlag=0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN 

    if(bEnable)
		iFlag =1;
	else
		iFlag=0;


	RET_ERROR(pEpp->WriteArray ((void *)&iFlag, 'U', 215, DtWordEnm, 1,0));

}


//sensor measurement 
/**************************************************************************************************
*
* Function	 :	atf_ReadMeasurementStatus
*
* Description:	Read measurement status.
*				Call this function to read sensor measurement status
*
* Output	 :	piStatus-0=disable; 1=enable; 3=enable and performing measurement. 
*				piDataPoints-how many data point already in the measurement data buffer, max=1000.
*
* Return	 :	0 = success; >0 = failure
*
**************************************************************************************************/
int atf_ReadMeasurementStatus(short *piStatus, short *piDataPoints)
{
	int ret=0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	ret=pEpp->ReadArray ((void *)piStatus, 'U',215 , DtWordEnm, 1, 0);
	if(ret!=0) return ret;
	
	RET_ERROR( pEpp->ReadArray ((void *)piDataPoints, 'U',215 , DtWordEnm, 1, 1));


}



//sensor measurement 
/**************************************************************************************************
*
* Function	 :	aft_ReadMeasurementBuffer
*
* Description:	Read measurement data buffer
*				Call this function to read sensor measurement data in the buffer.
*
* Output	 :	piData-the sensor abs position in micron, allocate piData with double[1000] to make sure enough space to store data. 
*				piDatalen-the number of data points of the measurement data, max=1000.
*
* Return	 :	0 = success; >0 = failure
*
* Note		 :  the buffer size for sensor menasurement data is 1000. the buffer will be wrapped around when it is full.
*				the data will be sorted in order when the measurement is stop. To read data in order,
*				stop the measurement then read the data.
**************************************************************************************************/
int atf_ReadMeasurementBuffer(double *pData, short *piDataLen)
{

	int ret=0;
	short data[1000];
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	ret=pEpp->ReadArray ((void *)piDataLen, 'U', 215 , DtWordEnm, 1, 1);

	if( (ret!=0) || (*piDataLen<=0 ) ) return ret; //error or no data to read	
	if (*piDataLen>1000) *piDataLen = 1000;

	ret=(pEpp->ReadArray ((void *)data, 'U',216 , DtWordEnm, *piDataLen, 0));
	
	if(ret==0)
	{
		for(int i=0; i<*piDataLen; i++)
			pData[i]=data[i]/8.0;
	}

	return ret;


}


//sensor measurement 
/**************************************************************************************************
*
* Function	 :	aft_ReadMeasurementBuffer
*
* Description:	
*				Call this function to read sensor current measurement data point.
*
* Output	 :	piData-the current sensor abs position in micron.
*
* Return	 :	0 = success; >0 = failure
*
**************************************************************************************************/
int atf_ReadCurrentDataPoint(double *pdData)
{

	int ret=0;
	short data;
	CEPPARR_DECLARE_CURRENT_OR_RETURN

	ret=(pEpp->ReadArray ((void *)&data, 'U',215 , DtWordEnm, 1, 2));

	if(ret!=0) *pdData =data/8.0; 

	return ret;



}

//sensor measurement 
/**************************************************************************************************
*
* Function	 :	atf_ReadMeasTimeArray
*
* Description:	Call this function to read sensor current measurement time stamp for the profile data
*				time start from the moment when measurement function is enable. max 6.4 seconds
*
* Output	 :	piTimeStampArray- the measurement data time stamp in ms
*
* Return	 :	0 = success; >0 = failure
*
**************************************************************************************************/
int atf_ReadMeasTimeArray(double* pTimeStampArray)
{
	int ret=0;
	unsigned short data[1000], len=0;
	CEPPARR_DECLARE_CURRENT_OR_RETURN
	ret=pEpp->ReadArray ((void *)&len, 'U', 215 , DtWordEnm, 1, 1);

	if( (ret!=0) || (len<=0 ) ) return ret; //error or no data to read	
	if (len>1000) len = 1000;

	ret=(pEpp->ReadArray ((void *)data, 'U',217 , DtWordEnm, len, 0));
	
	if(ret==0)
	{
		for(int i=0; i<len; i++)
			pTimeStampArray[i]=data[i]/10.0;
	}

	return ret;

}

/**************************************************************************************************
*
* Function	 :	atf_ReadCurrentTime
*
* Description:	Call this function to read sensor time in seconds from the most recent reset
*
* Output	 :	pTime - time since last reset
*				pReference - last reference time
*
* Return	 :	0 = success; >0 = failure
*
**************************************************************************************************/
int atf_ReadCurrentTime ( unsigned int *pTime, unsigned int *pReference )
{
	unsigned int tmp[2] = { 0 } ;
	CEPPARR_DECLARE_CURRENT_OR_RETURN ;
	int err = pEpp->ReadArray ( tmp, 't', 240, DtDwordEnm, 2 );
	if ( err == ErrOK )
	{
		*pTime = tmp[0];
		*pReference = tmp[1];
	}
	return err ;
}
