/******************************************************************************
 *	
 *	(C) Copyright WDI 2012
 *	
 ******************************************************************************
 *
 *	FILE:		atf_lib_exp.h
 *
 *	PROJECT:	AFT Sensors
 *
 *	SUBPROJECT:	.
 *
 *	Description: Functions exported from the ATF DLL library
 *	
 ******************************************************************************
 *	
 *	Change Activity
 *	Defect  Date       Developer        Description
 *	Number  DD/MM/YYYY Name
 *	======= ========== ================ =======================================
 *          19/04/2012 Chris O.         Initial version 
 *                                      
 *****************************************************************************/

#pragma once

// 2016 7 4 - chc
#include "atf_def.h"

#include <stdio.h>

// 2016 7 4 - chc
//#ifdef __cplusplus

	extern "C" {

// 2016 7 4 - chc
//#endif

// 2016 7 5 - chc
//#define DllExport __declspec(dllexport)
//#define DllExport __declspec(dllimport) __stdcall
#define DllExport  __declspec(dllimport)

// ---------- ATF error info functions

// returns text name of most recent error
DllExport const char* ATF_GetErrorInfo(int iErr);

// ---------- ATF serial port functions

// 2016 7 4 - chc 再加上__stdcall於ATF_前面

// establishing connection. Return 0 if OK, or something else in case of error
DllExport int __stdcall ATF_OpenConnection(char *port, int speed);
DllExport void __stdcall ATF_CloseConnection(void);

// to select which of the multiple com objects are used. New index is assigned
// with every ATF_OpenConnection and invalidated with ATF_CloseConnection.
// Index is a thread local. There is no need to use those functions if a thread is
// dedicated to communicate with a single com object. If thread is talking through 
// multiple com objects (multiple sensors) then ATF_SetComIdx needs to be done
// every time ccom object changes
DllExport int __stdcall ATF_GetComIdx();
DllExport int __stdcall ATF_SetComIdx(int idx);

// serial Com port baudrate
DllExport int __stdcall ATF_ChangeCommBaudrate(DWORD dwBaudRate);
DllExport int __stdcall ATF_GetCommBaudrate(DWORD *dwBaudrate);
DllExport BOOL __stdcall ATF_isSerialConnection(void);

// read current sensor baudrate setting
DllExport int __stdcall ATF_ReadBaud(int *pBR);
// writes new baudrate setting (need to follow up with change of port setting if communication is to continue) 
DllExport int __stdcall ATF_WriteBaud(int br);

// ---------- ATF ping and recovery functions

// attempts to recover in case of communication loss
// verify what is running. Returns:
// 0 - no communnication could be established
// 1 - application found
// 2 - bootloader found, it was restarted back to application
DllExport int __stdcall ATF_RecoverSensor(void);
// check if "A" is returned which indicate that software is working
DllExport int __stdcall ATF_PingAck(void);
// resets sensor
DllExport int __stdcall ATF_Reset(void);

// ---------- ATF low level communication functions

// direct access to read and write
DllExport int __stdcall ATF_ReadArray(void *to, int bid, int pid, EppDataType tag, int num, int offset);
DllExport int __stdcall ATF_ReadArray2(void **to, int bid, int pid, EppDataType tag, int num, int offset);
DllExport int __stdcall ATF_WriteArray(void *from, int bid, int pid, EppDataType tag, int num, int offset);

// ---------- ATF part identification functions

// returns text corresponding to sensor id
DllExport const char* __stdcall ATF_PartInfo(void);

DllExport int __stdcall ATF_ReadSerialNumber(unsigned int *SensorSN);
DllExport int __stdcall ATF_ReadFirmwareVer(int *ver);

// ---------- ATF one time initialization functions

// raed magnification assigned to particular objective
DllExport int __stdcall ATF_ReadMagnification(int obj, short *pMag);
// assigns magnification to the objective. 
// This will cause to reinitialize all the parameters associated with objective
DllExport int __stdcall ATF_WriteMagnification(int obj, short uMag);

// ---------- ATF objective configuration functions

// assign current z position to be best in focus
DllExport int __stdcall ATF_Make0(void);

// save all parameters into the eprom memory
DllExport int __stdcall ATF_SaveAll(void);
// read and set current objective number
DllExport int __stdcall ATF_ReadObjNum(int *pObj);
DllExport int __stdcall ATF_WriteObjNum(int iObj);

// read/write peak offset
DllExport int __stdcall ATF_ReadPeakOffset (int obj, enum PeakOffsetWhich pow, int* peakArray);
DllExport int __stdcall ATF_WritePeakOffset(int obj, enum PeakOffsetWhich pow, int* peakArray);

// read acceleration in mm/ss
DllExport int __stdcall ATF_ReadAccel(int obj, float *pAccel);
DllExport int __stdcall ATF_WriteAccel(int obj, float fAccel);
// read speed in mm/s
DllExport int __stdcall ATF_ReadSpeed(int obj, float *pSpeed);
DllExport int __stdcall ATF_WriteSpeed(int obj, float fSpeed);
// read proportional gain factor
DllExport int __stdcall ATF_ReadP(int obj, float *pP);
DllExport int __stdcall ATF_WriteP(int obj, float fP);

// reads/writes row delay parameter for specified objective and specified window
DllExport int __stdcall ATF_ReadWindowRowDelay  (int obj, WindowEnm which, short* prd);
DllExport int __stdcall ATF_WriteWindowRowDelay (int obj, WindowEnm which, short rd);

// read number of steps correponding to 1 mm of motion
DllExport int __stdcall ATF_ReadStepPerMmConversion(unsigned short *puStepMm);
// write number of steps correponding to 1 mm of motion
DllExport int __stdcall ATF_WriteStepPerMmConversion(unsigned short uStepMm);

// read number of microsteps assigned per each stepper motor step
DllExport int __stdcall ATF_ReadMicrostep(unsigned short *puUstep);
// change number os microsteps 
DllExport int __stdcall ATF_WriteMicrostep(unsigned short uUstep);

// read number of micrometers corresponding to unit on sensor output
DllExport int __stdcall ATF_ReadSlopeUmPerOut(int obj, float *pfumout);
DllExport int __stdcall ATF_WriteSlopeUmPerOut(int obj, float fumout);

// DUV jump dist
DllExport int __stdcall ATF_WriteDuvJump(int obj, short sUStep);
DllExport int __stdcall ATF_ReadDuvJump(int obj, short *pUStep);

// write number of units as reported by sensor position defining infocus range
DllExport int __stdcall ATF_WriteInfocusRange(int obj, int iRange);
DllExport int __stdcall ATF_ReadInfocusRange(int obj, int *pRange);

// prevent sensor from changing current window mode to the different one
DllExport int __stdcall ATF_DisableAutoWindowTransit(void) ;
// alows automatic window selection. TYpically: near mode (7 segments) at focus and far mode if distance is
// greater then linear range
DllExport int __stdcall ATF_EnableAutoWindowTransit(void);

// read number of imager pixels assigned to represent linear range
DllExport int __stdcall ATF_ReadLinearRange(int obj, int *pLinearRange);
DllExport int __stdcall ATF_WriteLinearRange(int obj, int iLinearRange);

// read and write surface
DllExport int __stdcall ATF_ReadSurface(short *piSurf);
DllExport int __stdcall ATF_WriteSurface(short iSurf);

// ---------- ATF auto focus tracking setup functions

// sets upper and lower limits (in abs position units) for motion executed during AF cycle.
// if adaptive_lim!=0 then upper and lower limits are adjusted up or down around 0 position if number
// of samples in a row falls within InFocusRange
DllExport int __stdcall ATF_WriteMotionLimits(int upper_limit, int lower_limit, int adaptive_lim);

// sets mode in which laser is going to be turned off once focus is reached. 
// Next AF command is going to enable laser
DllExport int __stdcall ATF_EnableAutoOff(void);
DllExport int __stdcall ATF_DisableAutoOff(void);

// set far mode
DllExport int __stdcall ATF_ForceFarMode(void);
// set near mode
DllExport int __stdcall ATF_ForceNearMode(void);
// set center of the imager
DllExport int __stdcall ATF_CenterFarWindow(void);
DllExport int __stdcall ATF_ClearFarWindowCentering(void);

// ---------- ATF commands and tracking functions

// executes motion of move microsteps
DllExport int __stdcall ATF_MoveZ(int move);
// executes motion of move micrometers
DllExport int __stdcall ATF_MoveZum(int iMoveUm);
// reads most recent motion distance
DllExport int __stdcall ATF_ReadLastMoveZ(int *pzMove);
// executes stop motor motion
DllExport int __stdcall ATF_StopZMotor(void);
// executes motion of move microsteps followed by clear abs position
DllExport int __stdcall ATF_MoveZ_ClearAbs(int move);

// reads position in microstepps updated by the sensor with every z motion
DllExport int __stdcall ATF_ReadAbsZPos(int *absZ);
DllExport int __stdcall ATF_WriteAbsZPos(int absZ);

// stops AF tracking
DllExport int __stdcall ATF_AfStop(void);
// starts AF tracking
DllExport int __stdcall ATF_AFTrack(void);
// start AF tracking first, once at focus continue on AOI tracking
DllExport int __stdcall ATF_AFAoiTrack(void);
// start Video tracking
DllExport int __stdcall ATF_AFVideoTrack(void);
// execute focus and disables, if DUV jump is defined will be taken
DllExport int __stdcall ATF_AfDuvJump(void);
// start AOI tracking
DllExport int __stdcall ATF_AFAoiOnlyTrack(void);

DllExport int __stdcall ATF_DPAF();

// ---------- ATF status and results functions

// reads sensor position, typically in range +/- 512
DllExport int __stdcall ATF_ReadPosition(float *pfpos);

// read position packed into single short along with some extra flags
DllExport int __stdcall ATF_ReadPositionPacked(RsData *prs);

// reads hardware status of HwStatusFlagsEnm type (see description above)
DllExport int __stdcall ATF_ReadHwStat(int *HwStat);

// read status flags of StatusFlagsEnm type (see description above)
DllExport int __stdcall ATF_ReadStatus(short *pstatus);

// reads scanline.
// mode: one of the ...WINIDOW defined above
// h_scanline: points to a buffer of MAX_SCANLINE_LENGTH where horizontal scanline is to be copied to
// v_scanline: points to a buffer of MAX_SCANLINE_LENGTH where vertical scanline is to be copied to
// h_len: number of elements of h_scanline
// v_len: returns number of elements of v_scanline
// width: returns width of the v_scanline peak as detected by sensor
DllExport int __stdcall ATF_ReadScanline(unsigned short *mode,
							   unsigned short *h_scanline, unsigned short *v_scanline, 
							   unsigned short *h_len, unsigned short *v_len, 
							   unsigned short *width);

// read individual dot.line segment position
DllExport int __stdcall ATF_Read7DotPosition(short *p7dots, int iLinearRange);

// read value reported on analog output
DllExport int __stdcall ATF_ReadAnalogOut(short *pAnalog);

// get sensor error code
DllExport int __stdcall ATF_ReadErrorCode(enum AtfCodesEnm *pcode);

// ---------- ATF laser control functions

// turns laser ON
DllExport int __stdcall ATF_EnableLaser(void);
// turns laser OFF
DllExport int __stdcall ATF_DisableLaser(void);
// enable automated laser power control
DllExport int __stdcall ATF_LaserTrackOn(void);
// enable manual laser power control
DllExport int __stdcall ATF_LaserTrackOff(void);
// read current laser power. Value from 0-1023.
// ATF5
// dotIdx:	0-2 - write laser power to current window
//          4 - far mode laser power (3,5 unused) 
//          6-8 - near mode left window laser power
//          9-11 - near mode center window laser power (10 is central dot)
//          12-14 - near mode right window laser power 
// ATF6
// dotIdx:	0 - write laser power to current window (1,2 - unused)
//          4 - far mode laser power (3,5 unused) 
//			7-13 - near mode 7 dot laser power (typically they are the same, 10 is central dot)
//          6,14 - unused
DllExport int __stdcall ATF_ReadLaserPower(unsigned short *plaser, int iByteNumToRead, int dotIdx);
// set current laser power
DllExport int __stdcall ATF_WriteLaserPower(unsigned short laser, int iByteNumToRead, int dotIdx);


// equivalent to enabling sync signal on input DIO
DllExport int __stdcall ATF_EnableSync(void);
// equivalent to disabling sync signal on input DIO
DllExport int __stdcall ATF_DisableSync(void);

// ---------- ATF LED control functions

// there are up to 3 led (0,1,2)
DllExport int __stdcall ATF_ReadLedCurrent(int channel, unsigned short *pCurrent);
DllExport int __stdcall ATF_WriteLedCurrent(int channel, unsigned short uCurrent);
DllExport int __stdcall ATF_ReadLedPwm(int channel, unsigned short *pPWM);
DllExport int __stdcall ATF_WriteLedPwm(int channel, unsigned short uPWM);
DllExport int __stdcall ATF_ReadLedPwmStartupVal(int iChannel, unsigned short *puPWM);
DllExport int __stdcall ATF_WriteLedPwmStartupVal(int iChannel, unsigned short uPWM);

// ---------- ATF MFC related functions

DllExport int __stdcall ATF_ReadMfcConfig(int *mfc_config);
// read 5 bytes used to configure motor.
DllExport int __stdcall ATF_ReadMfcMotorParm(unsigned char *motor_parm);
DllExport int __stdcall ATF_WriteMfcMotorParm(unsigned char *motor_parm);

// ---------- ATF CM functions
DllExport BOOL __stdcall ATF_IsCmAvailable();
DllExport int __stdcall ATF_ReadCmGlassThickness (int* piThicknessUstep);
DllExport int __stdcall ATF_WriteCmGlassThickness (int iThicknessUstep);
DllExport int __stdcall ATF_ReadCmRetarder (float *pfRetardation_percent, int iSurface);
DllExport int __stdcall ATF_WriteCmRetarder (float fRetardation_percent, int iSurface);
DllExport int __stdcall ATF_ReadCmRetarderAutoDetectConfigOptions (BOOL *pbDoAutoDetectOnMake0, BOOL *pbDoWaitAutoDetectToAf);
DllExport int __stdcall ATF_WriteCmRetarderAutoDetectConfigOptions(BOOL bDoAutoDetectOnMake0,  BOOL  bDoWaitAutoDetectToAf);
DllExport CmAutoDetectEnum __stdcall ATF_ReadCmRetarderAutoDetectStatus();
DllExport int __stdcall ATF_ScheduleCmRetarderAutoDetectForAF();
DllExport int __stdcall ATF_StartCmRetarderAutoDetect();
DllExport int __stdcall ATF_StopCmRetarderAutoDetect();

// ---------- ATF logger functions

DllExport BOOL __stdcall ATF_openLogFile(const char *pLogFilePath, const char *pMode);
DllExport BOOL __stdcall ATF_closeLogFile(void);
DllExport void __stdcall ATF_setLogLevel(int iLogLevel);

// 2016 7 5 - chc add __stdcall will cause error!
DllExport FILE *ATF_getLogFileHandle(void);

DllExport void __stdcall ATF_saveToLog(char *pLogMsg, int iLogLevel);
DllExport void __stdcall ATF_saveToLog2( int iLogLevel, char *pFormat, ...);


// ---------- ATF LLC related functions

DllExport BOOL __stdcall ATF_initializeLlc(char *pOffsetFileDir, int *piErrCode);
DllExport int __stdcall ATF_sendLlc(char *toSend, char *toRecv);
DllExport BOOL __stdcall ATF_getLlcStatus(int *piErrCode, const char **ppErrMsg, int *piStatReg, int *piMtrFailureReg);
DllExport BOOL __stdcall ATF_recoverLlc(int *piErrCode);
DllExport BOOL __stdcall ATF_recoverLlcSensorConnection(int *piErrCode);
DllExport BOOL __stdcall ATF_recoverLlcHdwr(int *piErrCode);
DllExport BOOL __stdcall ATF_resetLlcController(int *piErrCode);
DllExport BOOL __stdcall ATF_homeLlc(BOOL bWaitForEnd, int *piErrCode);
DllExport BOOL __stdcall ATF_isLlcInHomePos(int *piErrCode);
DllExport void __stdcall ATF_setObjectiveNum(int iObjNum);
DllExport int __stdcall ATF_getObjectiveNum(void);
DllExport int __stdcall ATF_getLlcForcerSerNum(void);
DllExport BOOL __stdcall ATF_saveLlcObjectivePositionOffset(int iObjectiveNumber, int iOffset);
DllExport BOOL __stdcall ATF_getLlcObjectivePositionOffset(int iObjectiveNumber, int *piPositionOffset);
DllExport BOOL __stdcall ATF_moveLlcToObjective(int iObjectiveNumber, BOOL bWaitForEnd, int *piErrCode);
DllExport BOOL __stdcall ATF_moveLlcToObjective2(int iObjectiveNumber, BOOL bWaitForEnd, int *piErrCode);
DllExport BOOL __stdcall ATF_moveLlcToPosition(int iPosition, BOOL bWaitForEnd, int *piErrCode);
DllExport BOOL __stdcall ATF_moveLLcRelativeDistance(int iDistance, BOOL bWaitForEnd, int *piErrCode);
DllExport BOOL __stdcall ATF_isLlcInTargetPosition(int *piErrCode);
DllExport BOOL __stdcall ATF_enableLlcMotor(int *piErrCode);
DllExport BOOL __stdcall ATF_disableLlcMotor(int *piErrCode);
DllExport BOOL __stdcall ATF_stopLlcMotion(int *piErrCode);
DllExport BOOL __stdcall ATF_setLlcSpeed(int iLlcSpeed, int *piErrCode);
DllExport BOOL __stdcall ATF_getLlcSpeed(int *piLlcSpeed, int *piErrCode);
DllExport BOOL __stdcall ATF_setLlcAcceleration(int iLlcAcceleration, int *piErrCode);
DllExport BOOL __stdcall ATF_getLlcAcceleration(int *piLlcAcceleration, int *piErrCode);
DllExport BOOL __stdcall ATF_setLlcDeceleration(int iLlcDeceleration, int *piErrCode);
DllExport BOOL __stdcall ATF_getLlcDeceleration(int *piLlcDeceleration, int *piErrCode);
DllExport BOOL __stdcall ATF_setLlcSmoothFactor(int iLlcSmoothFactor, int *piErrCode);
DllExport BOOL __stdcall ATF_getLlcSmoothFactor(int *piLlcSmoothFactor, int *piErrCode);
DllExport BOOL __stdcall ATF_getLlcVelocity(float *pfLlcVelocity, int *piErrCode);
DllExport BOOL __stdcall ATF_getLlcPosition(float *pfLlcPosition, int *piErrCode);
DllExport BOOL __stdcall ATF_getLlcMotorCurrent(float *pfLlcMotorCurrent, int *piErrCode);
DllExport int __stdcall ATF_CommToLlc(char* to_send, char* to_read);

// ---------- ATF homing Z functions
DllExport int __stdcall ATF_ReadHomingZ_Parameters(int *pHomingZ_Parameters);
DllExport int __stdcall ATF_WriteHomingZ_Parameters(int *pHomingZ_Parameters);
DllExport int __stdcall ATF_RunHomingZ(int *pHomingZ_Parameters);

// 2016 7 6 - chc
//DllExport int __stdcall ATF_IsInHomePosition(BOOL *pbInHome);
DllExport int __stdcall ATF_IsInHomePosition(bool *pbInHome);

// ---------- ATF jogging Z functions
DllExport int __stdcall ATF_StartJoggingZ(int iSpeed);

DllExport int __stdcall ATF_ReadStrobePulseTime(int iLed, int *pStrobeTime);
DllExport int __stdcall ATF_WriteStrobePulseTime(int iLed, int iStrobeTime);
DllExport int __stdcall ATF_ReadStrobeIntervalTime(int *pStrobeIntervalUs);
DllExport int __stdcall ATF_WriteStrobeIntervalTime(int iStrobeIntervalUs);
DllExport int __stdcall ATF_Strobe(int iLed, int iNum, int iMaxError);
DllExport int __stdcall ATF_StrobeCount(int *pNumStb, int *pNumStbRequested, bool *pbStrobeActive);
DllExport int __stdcall ATF_ReadConfigExt (int iObj, int *pcfg);
DllExport int __stdcall ATF_SetConfigExt (int iObj, int mask, int cfg);
DllExport int __stdcall ATF_ReadMoveObjNum (int *pObj, int *pMoveObj);
DllExport int __stdcall ATF_WriteMoveObjNum(int iObj, int iMoveObj);
DllExport int __stdcall ATF_ReadAbsZPosStage (enum StageSelectorEnum ess, int* pAbsZ, int *pMoveObj) ;
DllExport int __stdcall ATF_ReadAoiFollowUp (int iObj, int *pObjFollowUp);
DllExport int __stdcall ATF_WriteAoiFollowUp (int iObj, int iObjFollowUp);

//sensor measurement
DllExport int __stdcall ATF_EnableMeasurement(bool bEnable);
DllExport int __stdcall ATF_WriteMeasInterval(unsigned short iMeasIntervalUS=800);
DllExport int __stdcall ATF_ReadMeasInterval(unsigned short* iMeasInterval);
DllExport int __stdcall ATF_ReadMeasurementStatus(short *piStatus, short *piDataPoints);
DllExport int __stdcall ATF_ReadMeasurementBuffer(double *pData, short *piDatalen);
DllExport int __stdcall ATF_ReadCurrentDataPoint(double *pdData);
DllExport int __stdcall ATF_ReadMeasTimeArray(double* pTimeStampArray);

// 2016 7 4 - chc
//#ifdef __cplusplus

	}

// 2016 7 4 - chc
//#endif