//---------------------------------------------------------------------------

#ifndef VworksCCDH
#define VworksCCDH

// 這裡定義TCHAR
#include <windows.h>

// 這裡定義AnsiString...
#include <vcl.h>
#include <stdio.h>

#include "VwGigE.API.h"
#pragma link "VwGigE.v7.lib"

class VworksCCD
{
private:	// User declarations
   // init ViewWorks CCD
   UINT		           m_imagebuffernumber;
   VWSDK::VWGIGE_HANDLE    m_pvwGigE;
   //VWSDK::HCAMERA	   m_pCamera;
   VWSDK::OBJECT_INFO*     m_pobjectInfo;
   VWSDK::IMAGE_INFO*      pImageInfo;
   BITMAPINFO*		   m_pBmpInfo1;    				  //Bitmap object : 1
   BYTE*		   m_pUnpackedImage;
   UINT                    m_curFPS;
   HDC			   m_hdc1;
   //UINT                    m_Width,m_Height;
   UINT                    m_nFrame;

   // 2023 8 21 - chc info
   VWSDK::CAMERA_INFO_STRUCT     m_stInfo;

protected:
   int GetCustomCommand(VWSDK::HCAMERA hCamera, char* cpFeatureName, UINT* unValue, VWSDK::GET_CUSTOM_COMMAND eCmdType);
   void GetDeviceInfo(int nIndex, AnsiString *strVenderName, AnsiString *strModelName, AnsiString *strDeviceVersion, AnsiString *strDeviceID);
   void MakeUnPackedBuffer();
   void __fastcall SetupVieworksView();
   void __fastcall InitVworks();
   //void __fastcall DisplayVCCD(int cnt);
   //static void DrawImage( VWSDK::OBJECT_INFO* pObjectInfo, VWSDK::IMAGE_INFO* pImageInfo);
   //void DrawImage( VWSDK::OBJECT_INFO* pObjectInfo, VWSDK::IMAGE_INFO* pImageInfo);

public:		// User declarations
   __fastcall VworksCCD();
   __fastcall VworksCCD::~VworksCCD();

   bool boolVworksCCD;
   bool boolVWLive;
   UINT                    m_Width,m_Height;
   void __fastcall CCDLive();
   void __fastcall CCDGrab();
   void __fastcall DisplayVCCD(int cnt);
   __fastcall SetTriggerMode(bool mode);
   int TriggerFrameNo;
   bool                    boolInTrigger;
   // 2023 8 10 - chc Gain Set
   __fastcall VworksCCD::SetTriggerGain(double fgain);
   // 2023 8 11 - chc Close
   __fastcall VworksCCD::CloseCCD();

   __fastcall VworksCCD::SetTriggerTargerBrightness(int targetbrightness);
   __fastcall VworksCCD::SetTriggerExposureAuto(bool mode);
   __fastcall VworksCCD::ClearActive();
   VWSDK::HCAMERA	   m_pCamera;
   __fastcall VworksCCD::Grab();

};

//---------------------------------------------------------------------------
#endif
