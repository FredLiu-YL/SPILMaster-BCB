//---------------------------------------------------------------------------


#pragma hdrstop

#include "VworksCCD.h"
#include "MainFrm.h"

// 使用mkdir
#include <dir.h>

unsigned char *svptr;
extern VworksCCD *VieworksCCD;

//---------------------------------------------------------------------------
__fastcall VworksCCD::VworksCCD()
{

   // 2023 8 13 - chc set NULL
   m_pobjectInfo = NULL;
   pImageInfo = NULL;
   m_pBmpInfo1 = NULL;
   m_pUnpackedImage = NULL;

   m_curFPS = 0;
   TriggerFrameNo = 0;
   boolVworksCCD = false;
   boolInTrigger = false;
   boolVWLive = false;
   InitVworks();
}
//---------------------------------------------------------------------------
// 1600*1600
//Image capture event
//static void VworksCCD::DrawImage( VWSDK::OBJECT_INFO* pObjectInfo, VWSDK::IMAGE_INFO* pImageInfo )
//void VworksCCD::DrawImage( VWSDK::OBJECT_INFO* pObjectInfo, VWSDK::IMAGE_INFO* pImageInfo )
//static void DrawImage( VWSDK::OBJECT_INFO* pObjectInfo, VWSDK::IMAGE_INFO* pImageInfo )
bool VWActive = false;
void DrawImage( VWSDK::OBJECT_INFO* pObjectInfo, VWSDK::IMAGE_INFO* pImageInfo )
{
static int cnt = 0;
AnsiString msg;
unsigned char *dptr,*sptr;
int sindex,dindex;
static bfirst = true;

   MainForm->pnlDisplayCount->Caption = "0";

// Re-Entrant
int sum = 0;
static int incnt = 0;
static bool active = false;
   if(VWActive == true) {
      incnt++;
      MainForm->pnlInCnt->Caption = IntToStr(incnt);
      MainForm->WriteSystemLog("Re-Entrant: DrawImage()");
      return;
   }
   VWActive = true;

   MainForm->pnlDisplayCount->Caption = "1";
   MainForm->pnlCCDCount->Color = clNavy;

   // 2023 8 18 - chc 先關掉
   //=> 會太慢
   //VWSDK::CameraAbort(VieworksCCD->m_pCamera);
   //VieworksCCD->boolVWLive = false;

   // 2023 8 9 - chc 不log
   //MainForm->pnlCCDRun->Caption = "1:" + IntToStr(VieworksCCD->m_Width) + "," + IntToStr(VieworksCCD->m_Height);
   //MainForm->WriteSystemLog(MainForm->pnlCCDRun->Caption);

   if(MainForm->rgCCDSource->ItemIndex == 0) {
      goto end;
   }

   if(VieworksCCD->boolInTrigger == true) {
      VieworksCCD->TriggerFrameNo++;
      MainForm->pnlTriggerCaptureNo->Caption = IntToStr(VieworksCCD->TriggerFrameNo);
      MainForm->pnlTriggerCaptureNo->Refresh();
   }

   MainForm->pnlDisplayCount->Caption = "2";

   cnt++;
   MainForm->pnlCCDCount->Caption = IntToStr(cnt);
   MainForm->pnlCCDCount->Refresh();
   //msg.sprintf("%ld", pObjectInfo->pUserPointer);
   //MainForm->pnlVieworksMessage->Caption = msg;

   MainForm->pnlDisplayCount->Caption = "3";

   if(bfirst == true) {
      bfirst = false;

// 有設定W/H會無法取像, DMK也會無法顯示??? 三個都沒有會有Out of Resource!! Error
// => 可能用自己的TImage
//      MainForm->imVieworks->Picture->Bitmap->PixelFormat = pf24bit;

      MainForm->imVieworks->Picture->Bitmap->Width = VieworksCCD->m_Width;
      MainForm->imVieworks->Picture->Bitmap->Height = VieworksCCD->m_Height;
      // eVsion
      MainForm->EImageAry.SetSize(VieworksCCD->m_Width,VieworksCCD->m_Height);
      //MainForm->usb_ImageAry[2].SetSize(VieworksCCD->m_Width,VieworksCCD->m_Height);

      // 2023 8 2 - chc ROI
      MainForm->EImageAryROI.Attach(&MainForm->EImageAry);

      MainForm->pnlDisplayCount->Caption = "4";

   }

   MainForm->pnlDisplayCount->Caption = "5";

   sptr = (unsigned char *)pImageInfo->pImage;
   svptr = (unsigned char *)pImageInfo->pImage;
   MainForm->pnlW->Caption = IntToStr(pImageInfo->width);
   MainForm->pnlH->Caption = IntToStr(pImageInfo->height);

   MainForm->pnlDisplayCount->Caption = "6";

   /*
   sindex = 0;
   for(int row=0; row<m_Height ; row++) {
      // bitmap
      if(MainForm->rgImageType->ItemIndex == 0) {
         dptr = (Byte *) MainForm->imVieworks->Picture->Bitmap->ScanLine[row];        //讀取第 row 列
         //dindex = 0;
         //for(int col=0; col<m_Width; col++) {
         //   dptr[dindex++] = sptr[sindex++];                                       // 藍色分量
         //   dptr[dindex++] = sptr[sindex++];                                       // 綠色分量
         //   dptr[dindex++] = sptr[sindex++];                                       // 紅色分量
         //   //sindex += 3;
         //}
         // 由sptr到dptr
         memcpy(dptr, sptr,m_Width*3);
      }
      // eVision
      else if(MainForm->rgImageType->ItemIndex == 1 || MainForm->rgImageType->ItemIndex == 2) {
         dptr = (unsigned char *)MainForm->EImageAry.GetImagePtr(0,row);
         memcpy(dptr, sptr,m_Width*3);
      }
      // pattern
      else if(MainForm->rgImageType->ItemIndex == 3) {
         dptr = (unsigned char *)MainForm->EImageAry.GetImagePtr(0,row);
         for(int i=0 ; i<m_Width*3 ; i++) {
            if((cnt % 10) < 5)
               dptr[i] = 0x99;
            else
               dptr[i] = 0x55;
         }
      }
      sum += sptr[10];
      sptr += m_Width*3;

      //MainForm->pnlCCDRun->Caption = "2a:" + IntToStr(m_Width) + "," + IntToStr(m_Height) + "," + IntToStr(row+1);
      //MainForm->WriteSystemLog(MainForm->pnlCCDRun->Caption);

   }

   MainForm->pnlCCDRun->Caption = "3:" + IntToStr(m_Width) + "," + IntToStr(m_Height);
   MainForm->WriteSystemLog(MainForm->pnlCCDRun->Caption);

   if(MainForm->rgImageType->ItemIndex == 1) {
      //MainForm->EImageAry.Draw(MainForm->imVieworks->Canvas->Handle);
      MainForm->EImageAryROI.SetPlacement(0,0,m_Width,m_Height);
      MainForm->EImageAryROI.Draw(MainForm->imVieworks->Canvas->Handle);
   }
   // file
   else if(MainForm->rgImageType->ItemIndex == 2 || MainForm->rgImageType->ItemIndex == 3) {
      MainForm->EImageAry.Save("D:\\Test.bmp",E_FILE_FORMAT_COLOR_BMP);
      MainForm->imVieworks->Picture->LoadFromFile("D:\\Test.bmp");
   }
   MainForm->imVieworks->Refresh();
   MainForm->pnlSum->Caption = IntToStr(sum);
   */
   MainForm->pnlDisplayCount->Caption = "7";
   MainForm->pnlCCDCount->Color = clTeal;
   VieworksCCD->DisplayVCCD(cnt);
   MainForm->pnlCCDCount->Color = clBlack;

end:
   VWActive = false;

   // 2023 8 18 - chc 再打開
   //=> 會太慢
   //VWSDK::CameraGrab(VieworksCCD->m_pCamera);
   //VieworksCCD->boolVWLive = true;

}
//---------------------------------------------------------------------------
// 2023 6 5 - chc init ViewWorks CCD
void __fastcall VworksCCD::InitVworks()
{
int ccdindex = 1;

   SetupVieworksView();
   ccdindex = MainForm->edCCDIndex->Text.ToInt();
   MainForm->WriteSystemLog("Setup CCD: ViewWorks...");
   m_pobjectInfo = new VWSDK::OBJECT_INFO;

   //VwCamera*	m_pCamera;
   VWSDK::RESULT result = VWSDK::RESULT_ERROR;
   m_imagebuffernumber = 2;

   if(VWSDK::RESULT_SUCCESS != VWSDK::OpenVwGigE( &m_pvwGigE )) {
      //Application->MessageBox("Open failed!", MB_OK);
   }
   else {
      //Application->MessageBox("VworkCCD Open Succ.", MB_OK);
   }

   // 2023 8 21 - chc info
   VWSDK::VwDiscoveryCameraInfo( m_pvwGigE, ccdindex, &m_stInfo );

   //VWSDK::VwUserLogging(m_pvwGigE, "Sample Code", __VWFILE__, __VWFUNCTION__, __VWLINE__,
   //		"You can see this message in a tool called SpiderLogger.exe");

   //FUNCTION_IMPORTEXPORT RESULT VwOpenCameraByIndex(VWGIGE_HANDLE hVwGigE, UINT nCameraIndex, HCAMERA* phCamera, UINT nNumBuffer, UINT nWidth, UINT nHeight,
   //		UINT nPacketSize, void* pUserPointer, ImageCallbackFn* pImageCallbackFn, DisconnectCallbackFn* pDisconnectCallbackFn = NULL);

   //result = VWSDK::VwOpenCameraByIndex( m_pvwGigE, ccdindex, &m_pCamera, m_imagebuffernumber, 0, 0, 0, m_pobjectInfo, DrawImage, NULL);
   // 2023 8 21 - chc 改用Name
   //result = VWSDK::VwOpenCameraByIndex( m_pvwGigE, ccdindex, &m_pCamera, m_imagebuffernumber, 0, 0, 0, m_pobjectInfo, DrawImage);
   //result = VWSDK::VwOpenCameraByName( m_pvwGigE, "VQ-5MG2-C24H", &m_pCamera, m_imagebuffernumber, 0, 0, 0, m_pobjectInfo, DrawImage);
   MainForm->WriteSystemLog("Name: " + AnsiString(m_stInfo.name));
   result = VWSDK::VwOpenCameraByName( m_pvwGigE, m_stInfo.name, &m_pCamera, m_imagebuffernumber, 0, 0, 0, m_pobjectInfo, DrawImage);

   //Application->MessageBox((AnsiString("VworkCCD Open= ") + IntToStr(result)).c_str() , MB_OK);

   if(result != VWSDK::RESULT_SUCCESS) {
      MainForm->WriteSystemLog("Setup CCD: ViewWorks fail: " + IntToStr(result));
      switch(result) {
         default:
	    Application->MessageBox("ERROR : Default error code returned", MB_OK);
	    break;
	 case VWSDK::RESULT_ERROR_DEVCREATEDATASTREAM:
	    Application->MessageBox("ERROR : RESULT_ERROR_DEVCREATESTREAM was returned", MB_OK);
	    break;
	 case VWSDK::RESULT_ERROR_NO_CAMERAS:
	    Application->MessageBox("ERROR : RESULT_ERROR_NO_CAMERAS was returned", MB_OK);
	    Application->MessageBox("CHECK : NIC properties", MB_OK);
	    break;
	 case VWSDK::RESULT_ERROR_VWCAMERA_CAMERAINDEX_OVER:
	    Application->MessageBox("ERROR : RESULT_ERROR_VWCAMERA_CAMERAINDEX_OVER was returned", MB_OK);
	    Application->MessageBox("CHECK : Zero-based camera index", MB_OK);
	    break;
	 case VWSDK::RESULT_ERROR_DATASTREAM_MTU:
	    Application->MessageBox("ERROR : RESULT_ERROR_STREAM_MTU was returned", MB_OK);
	    Application->MessageBox("CHECK : Check NIC MTU", MB_OK);
	    break;
	 case VWSDK::RESULT_ERROR_INSUFFICIENT_RESOURCES:
	    Application->MessageBox("ERROR : RESULT_ERROR_BUFFER_TOO_SMALL was returned", MB_OK);
	    Application->MessageBox("CHECK : Check system resources", MB_OK);
	    break;
	 case VWSDK::RESULT_ERROR_MEMORY_ALLOCATION:
	    Application->MessageBox("ERROR : RESULT_ERROR_MEMORY_ALLOCATION was returned", MB_OK);
	    Application->MessageBox("CHECK : Check system resources", MB_OK);
	    break;
      }
      return;
   }

   //---------------------------------------------------------------------------
   m_pobjectInfo->pUserPointer = this;
   m_pobjectInfo->pVwCamera = m_pCamera;

   //Get image width,height
   UINT nWidth = 0;
   UINT nHeight = 0;
   VWSDK::PIXEL_FORMAT pixelFormat = VWSDK::PIXEL_FORMAT_BGR8;

   GetCustomCommand(m_pCamera, "Width", &nWidth, VWSDK::GET_CUSTOM_COMMAND_VALUE);
   GetCustomCommand(m_pCamera, "Height", &nHeight, VWSDK::GET_CUSTOM_COMMAND_VALUE);
   MainForm->pnlWidth->Caption = IntToStr(nWidth);
   MainForm->pnlHeight->Caption = IntToStr(nHeight);

   // 2023 8 2 - chc Set Width/Height/OffsetX/Offset(712*424)
   VWSDK::RESULT ret1 = VWSDK::CameraSetCustomCommand(m_pCamera, "Width", "1600");
   VWSDK::RESULT ret2 = VWSDK::CameraSetCustomCommand(m_pCamera, "Height", "1600");
   VWSDK::RESULT ret3 = VWSDK::CameraSetCustomCommand(m_pCamera, "OffsetX", "424");
   VWSDK::RESULT ret4 = VWSDK::CameraSetCustomCommand(m_pCamera, "OffsetY", "224");

   // 2023 8 10 - chc Gain Set
   AnsiString str;
   str.sprintf("%.2f",MainForm->ed45Gain->Text.ToDouble());
   VWSDK::RESULT ret5 = VWSDK::CameraSetCustomCommand(m_pCamera, "Gain", str.c_str());

   // 2023 8 15 - chc Set TargetBrightness,ExposureAuto
   str.sprintf("%d",MainForm->ed45TargetBrightness->Text.ToInt());
   VWSDK::RESULT ret6 = VWSDK::CameraSetCustomCommand(m_pCamera, "TargetBrightness", str.c_str());
   if(MainForm->cb45ExposureAuto->Checked == false)
      VWSDK::RESULT ret7 = VWSDK::CameraSetCustomCommand(m_pCamera, "TargetBrightness", "Off");
   else
      VWSDK::RESULT ret7 = VWSDK::CameraSetCustomCommand(m_pCamera, "TargetBrightness", "Continuous");

   // 直接設為"RGB8"
   VWSDK::RESULT ret = VWSDK::CameraSetCustomCommand(m_pCamera, "PixelFormat", "BGR8");
   //VWSDK::RESULT ret = VWSDK::CameraSetCustomCommand(m_pCamera, "PixelFormat", "BayerRG8");
   switch(ret) {
      case VWSDK::RESULT_SUCCESS:
      	 break;
      case VWSDK::RESULT_ERROR_INVALID_PARAMETER:
	 Application->MessageBox("Invalid pixelformat.", MB_OK);
	 break;
      default:
	 Application->MessageBox("Can't change the pixelformat.", MB_OK);
	 break;
   }

   // Update Pixel Size
   UINT nPixelSize = 0;
   GetCustomCommand(m_pCamera, "PixelSize", &nPixelSize,  VWSDK::GET_CUSTOM_COMMAND_VALUE);
   MainForm->pnlPixelSize->Caption = "Bpp" + IntToStr(nPixelSize);

   AnsiString  strVendorName, strModelName, strVersion, strID;
   GetDeviceInfo( ccdindex, &strVendorName, &strModelName, &strVersion, &strID );
   MainForm->pnlVendor->Caption = strVendorName;
   MainForm->pnlModel->Caption = strModelName;
   MainForm->pnlVersion->Caption = strVersion;
   MainForm->pnlID->Caption = strID;

   //Application->MessageBox("InitVworks: info", MB_OK);

   //---------------------------------------------------------------------------

   boolVworksCCD = true;
   MainForm->WriteSystemLog("Setup CCD: ViewWorks ok: " + IntToStr(result));

}

//---------------------------------------------------------------------------
// 2023 8 1 - chc Vieworks Image
// 1024*1200 - 764*896
// Offset: 712*424
void __fastcall VworksCCD::SetupVieworksView()
{

   MainForm->pnlVieworks->Left = 103;
   MainForm->pnlVieworks->Top = 11;
   MainForm->pnlVieworks->Width = 1102;
   MainForm->pnlVieworks->Height = 910;

   MainForm->imVieworks->Left = 8;
   MainForm->imVieworks->Top = 8;
   MainForm->imVieworks->Width = 896;
   MainForm->imVieworks->Height = 896;

}
//---------------------------------------------------------------------------
// 2023 8 1 - chc Vieworks CCD
//CString Left( int nCount ) const;                   //左第1個開始取前nCount個字符
//CString Mid( int nFirst ) const;                    //左?第 nFirst+1 字符開始,取后面所有的字符
//CString Mid( int nFirst, int nCount ) const;        //左?第 nFirst+1 字符開始,取后面  nCount 個字符
//CString Right( int nCount ) const;                  //右第1個開始取右向左前 nCount 個字符
int VworksCCD::GetCustomCommand(VWSDK::HCAMERA hCamera, char* cpFeatureName, UINT* unValue, VWSDK::GET_CUSTOM_COMMAND eCmdType)
{
VWSDK::RESULT eRet = VWSDK::RESULT_ERROR;
int len;

   char chResult[100] = { 0, };
   size_t szResult = sizeof(chResult);

   eRet = CameraGetCustomCommand(hCamera, cpFeatureName, chResult, &szResult, eCmdType);
   if(eRet == VWSDK::RESULT_SUCCESS){
      if(0 == strcmp(cpFeatureName, "PixelSize") && VWSDK::GET_CUSTOM_COMMAND_VALUE == eCmdType){
	 // Bpp8 Bpp10 Bpp12 ...
	 AnsiString strTmp(chResult);
         // 4到最後
         // 1234567890
         len = strTmp.Length();
	 *unValue = strTmp.SubString(4,len-3).ToInt();
      }
      else
      	 *unValue = atoi(chResult);
   }

   return eRet;
}
//---------------------------------------------------------------------------
// 2023 8 1 - chc Vieworks CCD
void VworksCCD::GetDeviceInfo(int nIndex, AnsiString *strVenderName, AnsiString *strModelName, AnsiString *strDeviceVersion, AnsiString *strDeviceID)
{

   if(NULL == m_pCamera) {
      MainForm->WriteSystemLog("GetDeviceInfo: Fail");
      return;
   }

   const int STR_SIZE =	256;

   char szVendorName[STR_SIZE];
   size_t cbVendor = sizeof( szVendorName );

   char szModelName[ STR_SIZE ];
   size_t cbModel = sizeof( szModelName );

   char szVersion[ STR_SIZE ];
   size_t cbVersion = sizeof ( szVersion );

   char szID[ STR_SIZE ];
   size_t cbID = sizeof ( szID );


   if(VWSDK::CameraGetDeviceVendorName( m_pCamera, nIndex, szVendorName, &cbVendor ) == VWSDK::RESULT_SUCCESS ) {
      *strVenderName = szVendorName;
   }

   if(VWSDK::CameraGetDeviceModelName( m_pCamera, nIndex, szModelName, &cbModel ) == VWSDK::RESULT_SUCCESS ) {
      *strModelName = szModelName;
   }

   if(VWSDK::CameraGetDeviceVersion( m_pCamera, nIndex, szVersion, &cbVersion ) == VWSDK::RESULT_SUCCESS ) {
      *strDeviceVersion = szVersion;
   }

   if(VWSDK::CameraGetDeviceID( m_pCamera, nIndex, szID, &cbID ) == VWSDK::RESULT_SUCCESS ) {
      *strDeviceID = szID;
   }

   // 2023 8 21 - chc Info
   *strModelName = m_stInfo.model;
   *strDeviceID = m_stInfo.name;
   *strVenderName = m_stInfo.vendor;

}
//---------------------------------------------------------------------------
// 2023 8 1 - chc Vieworks CCD
void __fastcall VworksCCD::CCDLive()
{

   if(NULL == m_pCamera) {
      MainForm->WriteSystemLog("btnLiveClick: Fail");
      return;
   }

   BOOL bGrabbing = FALSE;
   VWSDK::CameraGetGrabCondition( m_pCamera, bGrabbing);
   if(bGrabbing) {
      Application->MessageBox("Now living... Please 'Grab' first.", MB_OK );
      return;
   }

   // 2023 8 20 - chc Log
   MainForm->WriteSystemLog("啟動Vieworks CCD live mode: CCDLive-1");

   // 2023 8 20 - chc 放到最後
   //boolVWLive = true;

   UINT nWidth = 0;
   UINT nHeight = 0;
   UINT nInputWidth = 0;
   UINT nInputHeight = 0;
   GetCustomCommand(m_pCamera, "Width", &nWidth, VWSDK::GET_CUSTOM_COMMAND_VALUE);
   GetCustomCommand(m_pCamera, "Height", &nHeight, VWSDK::GET_CUSTOM_COMMAND_VALUE);
   nInputWidth = nWidth;
   nInputHeight = nHeight;
   MainForm->pnlWidth->Caption = IntToStr(nWidth);
   MainForm->pnlHeight->Caption = IntToStr(nHeight);
   m_Width = nWidth;
   m_Height = nHeight;

   // 2023 8 20 - chc Log
   MainForm->WriteSystemLog("啟動Vieworks CCD live mode: CCDLive-2");

   {
      // CameraSetReadoutMode
      char chValue[10] = { 0, };
      // This property values may be different for each GigE camera.
      // READOUT_NORMAL			= 0
      // READOUT_AOI				= 1
      // READOUT_BINNING			= 2
      // READOUT_HORIZONTALSTART	= 3
      // READOUT_HORIZONTALEND	= 4
      // READOUT_VERTICALSTART	= 5
      // READOUT_VERTICALEND		= 6
      // READOUT_BINNINGFATOR		= 7
      //sprintf(chValue, "%d", 1);                                                // READOUT_AOI = 1
      //VWSDK::RESULT ret = VWSDK::CameraSetCustomCommand(m_pCamera, "ReadoutMode", chValue);
      AnsiString str;
      str.sprintf("%d",1);
      VWSDK::RESULT ret = VWSDK::CameraSetCustomCommand(m_pCamera, "ReadoutMode", str.c_str());
   }

   // 2023 8 20 - chc Log
   MainForm->WriteSystemLog("啟動Vieworks CCD live mode: CCDLive-3");

   {
      // CameraSetHorizontalStart/End
      VWSDK::CameraSetCustomCommand(m_pCamera, "HorizontalStart", "0");
      char chValue[100] = { 0, };
      //sprintf(chValue, "%d", nInputWidth - 1);
      //VWSDK::CameraSetCustomCommand(m_pCamera, "HorizontalEnd", chValue);
      AnsiString str;
      str.sprintf("%d",nInputWidth - 1);
      VWSDK::CameraSetCustomCommand(m_pCamera, "HorizontalEnd", str.c_str());

      // CameraSetVerticalStart/End
      VWSDK::CameraSetCustomCommand(m_pCamera, "VerticalStart", "0");
      ZeroMemory(chValue, sizeof(chValue));

      //sprintf(chValue, "%d", nInputHeight - 1);
      //VWSDK::CameraSetCustomCommand(m_pCamera, "VerticalEnd", chValue);
      str.sprintf("%d",nInputHeight - 1);
      VWSDK::CameraSetCustomCommand(m_pCamera, "VerticalEnd", str.c_str());
   }

   // 2023 8 20 - chc Log
   MainForm->WriteSystemLog("啟動Vieworks CCD live mode: CCDLive-4");

   VWSDK::PIXEL_FORMAT pixelFormat = VWSDK::PIXEL_FORMAT_BGR8;
   //VWSDK::PIXEL_FORMAT pixelFormat = VWSDK::PIXEL_FORMAT_BAYRG8;

   VWSDK::CameraGetPixelFormat( m_pCamera, &pixelFormat);
   if(nInputWidth != nWidth || nInputHeight != nHeight) {
      if(VWSDK::RESULT_SUCCESS != VWSDK::CameraChangeBufferFormat( m_pCamera, m_imagebuffernumber, nInputWidth, nInputHeight, pixelFormat)) {
	 Application->MessageBox("Can't change the camera buffer.", MB_OK);
	 return;
      }
      // 取得總長度W*H*3
      MakeUnPackedBuffer();
   }

   // 2023 8 20 - chc Log
   MainForm->WriteSystemLog("啟動Vieworks CCD live mode: CCDLive-5");

   if(VWSDK::CameraGrab( m_pCamera ) == VWSDK::RESULT_SUCCESS) {

   }
   else {
      return;
   }

   // 2023 8 20 - chc 放到最後
   boolVWLive = true;

}
//---------------------------------------------------------------------------
// 2023 8 1 - chc Vieworks CCD
void __fastcall VworksCCD::CCDGrab()
{

   if(NULL == m_pCamera) {
      MainForm->WriteSystemLog("btnGrabClick: Fail");
      return;
   }

   VWSDK::CameraAbort(m_pCamera);
   boolVWLive = false;

}
//---------------------------------------------------------------------------
void VworksCCD::MakeUnPackedBuffer()
{

   if(NULL == m_pCamera) {
      MainForm->WriteSystemLog("MakeUnPackedBuffer: Fail");
      // ERROR
      return;
   }

   if(m_pUnpackedImage) {
      delete [] m_pUnpackedImage;
      m_pUnpackedImage = NULL;
   }

   //Get image width,height
   UINT nWidth = 0;
   UINT nHeight = 0;
   GetCustomCommand(m_pCamera, "Width", &nWidth, VWSDK::GET_CUSTOM_COMMAND_VALUE);
   GetCustomCommand(m_pCamera, "Height", &nHeight, VWSDK::GET_CUSTOM_COMMAND_VALUE);

   VWSDK::PIXEL_FORMAT pixelFormat = VWSDK::PIXEL_FORMAT_BGR8;
   VWSDK::CameraGetPixelFormat( m_pCamera, &pixelFormat);

   if(pixelFormat == VWSDK::PIXEL_FORMAT_BGR8)
      m_pUnpackedImage = new BYTE[nWidth*nHeight*3];
   else
      m_pUnpackedImage = new BYTE[nWidth*nHeight*3];

}
//---------------------------------------------------------------------------
// Vieworks ccd
void __fastcall VworksCCD::DisplayVCCD(int cnt)
{
int sindex;
unsigned char *dptr;
int sum = 0;
int w,h;
AnsiString fname,path;

   // 2023 8 20 - chc true: 由MainForm 的timer來做
   MainForm->boolInVieworksDisplay = true;

   MainForm->pnlDisplayCount->Caption = "8";
   sindex = 0;
   w = MainForm->EImageAry.GetWidth();
   h = MainForm->EImageAry.GetHeight();
   if(w != m_Width) {
      MainForm->WriteSystemLog("Width(Err): " + IntToStr(m_Width) + "," + IntToStr(w));
   }
   if(h != m_Height) {
      MainForm->WriteSystemLog("Height(Err): " + IntToStr(m_Height) + "," + IntToStr(h));
   }

   MainForm->pnlDisplayCount->Caption = "9";

   for(int row=0; row<m_Height ; row++) {
      // bitmap
      if(MainForm->rgImageType->ItemIndex == 0) {
         dptr = (Byte *) MainForm->imVieworks->Picture->Bitmap->ScanLine[row];        //讀取第 row 列
         //dindex = 0;
         //for(int col=0; col<m_Width; col++) {
         //   dptr[dindex++] = svptr[sindex++];                                       // 藍色分量
         //   dptr[dindex++] = svptr[sindex++];                                       // 綠色分量
         //   dptr[dindex++] = svptr[sindex++];                                       // 紅色分量
         //   //sindex += 3;
         //}
         // 由svptr到dptr
         memcpy(dptr, svptr,m_Width*3);
      }
      // eVision
      else if(MainForm->rgImageType->ItemIndex == 1 || MainForm->rgImageType->ItemIndex == 2) {
         //if(MainForm->rgImageType->ItemIndex == 1)
         //   dptr = (unsigned char *)MainForm->usb_ImageAry[2].GetImagePtr(0,row);
         //else
            dptr = (unsigned char *)MainForm->EImageAry.GetImagePtr(0,row);
         memcpy(dptr, svptr,m_Width*3);
      }
      // pattern
      else if(MainForm->rgImageType->ItemIndex == 3) {
         dptr = (unsigned char *)MainForm->EImageAry.GetImagePtr(0,row);
         for(int i=0 ; i<m_Width*3 ; i++) {
            if((cnt % 10) < 5)
               dptr[i] = 0x99;
            else
               dptr[i] = 0x55;
         }
      }
      sum += svptr[10];
      svptr += m_Width*3;

   }

   // 2023 8 20 - chc true: 由MainForm 的timer來做
   MainForm->boolInVieworksDisplay = false;

   MainForm->pnlDisplayCount->Caption = "10";

   // 2023 8 9 - chc 不log
   //MainForm->pnlCCDRun->Caption = "3:" + IntToStr(m_Width) + "," + IntToStr(m_Height);
   //MainForm->WriteSystemLog(MainForm->pnlCCDRun->Caption);

   if(MainForm->rgImageType->ItemIndex == 1) {

      // 先做Save & Load 再做Draw, 直接Draw不會顯示出來!
      if(MainForm->cbLoadFirst->Checked == true) {
         MainForm->EImageAry.Save("D:\\Test.bmp",E_FILE_FORMAT_COLOR_BMP);
         MainForm->EImageAry.Load("D:\\test.bmp");
      }

      // 2023 8 20 - chc true: 由MainForm 的timer來做
      if(MainForm->cbTimerDisplay->Checked == false)

         MainForm->EImageAry.Draw(MainForm->imVieworks->Canvas->Handle);
      //MainForm->usb_ImageAry[2].Draw(MainForm->imVieworks->Canvas->Handle);
      //MainForm->EImageAryROI.SetPlacement(0,0,m_Width,m_Height);
      //MainForm->EImageAryROI.Draw(MainForm->imVieworks->Canvas->Handle);
      //MainForm->PutVieworksImage();
      if(VieworksCCD->boolInTrigger == true) {
         path = MainForm->SystemConfig.ImagePath;
         if(!DirectoryExists(path))
            mkdir(path.c_str());
         fname.sprintf("%s\\%03d.bmp",path.c_str(),VieworksCCD->TriggerFrameNo);
         MainForm->EImageAry.Save(fname.c_str(),E_FILE_FORMAT_COLOR_BMP);
      }
   }
   // file
   else if(MainForm->rgImageType->ItemIndex == 2 || MainForm->rgImageType->ItemIndex == 3) {
      if(VieworksCCD->boolInTrigger == true) {

         // 2023 8 17 - chc ImagePath
         //path = "D:\\Vieworks";
         path = MainForm->SystemConfig.ImagePath;

         if(!DirectoryExists(path))
            mkdir(path.c_str());
         fname.sprintf("%s\\%03d.bmp",path.c_str(),VieworksCCD->TriggerFrameNo);
         MainForm->EImageAry.Save(fname.c_str(),E_FILE_FORMAT_COLOR_BMP);
         if(MainForm->rgPictureBitmap->ItemIndex == 0)
            MainForm->imVieworks->Picture->LoadFromFile(fname);
         else
            MainForm->imVieworks->Picture->Bitmap->LoadFromFile(fname);
      }
      else {

         // 2023 8 110 - chc FullImage?
         if(MainForm->cb45FullImage->Checked == false) {
            int w,h,ox,oy;
            w = MainForm->imVieworks->Width;
            h = MainForm->imVieworks->Height;
            //MainForm->imVieworks->Picture->Bitmap->Width = w;
            //MainForm->imVieworks->Picture->Bitmap->Height = h;
            ox = (m_Width - w) / 2;
            oy = (m_Height - h) / 2;
            MainForm->EImageAryROI.SetPlacement(ox,oy,w,h);
            //MainForm->EImageAry.Save("D:\\Test.bmp",E_FILE_FORMAT_COLOR_BMP);
            MainForm->EImageAryROI.Save("D:\\Test.bmp",E_FILE_FORMAT_COLOR_BMP);
         }
         else {
            //MainForm->imVieworks->Picture->Bitmap->Width = VieworksCCD->m_Width;
            //MainForm->imVieworks->Picture->Bitmap->Height = VieworksCCD->m_Height;

            MainForm->pnlDisplayCount->Caption = "11";
            MainForm->EImageAry.Save("D:\\Test.bmp",E_FILE_FORMAT_COLOR_BMP);
            MainForm->pnlDisplayCount->Caption = "12";
         }
         MainForm->pnlDisplayCount->Caption = "13";
         try {
            if(MainForm->rgPictureBitmap->ItemIndex == 0)
               MainForm->imVieworks->Picture->LoadFromFile("D:\\Test.bmp");
            else
               MainForm->imVieworks->Picture->Bitmap->LoadFromFile("D:\\Test.bmp");
         }
         catch(Exception &e) {
            MainForm->WriteSystemLog("Error(DisplayVCCD): " + e.Message);
         }
         MainForm->pnlDisplayCount->Caption = "14";
      }
   }
   MainForm->pnlDisplayCount->Caption = "15";
   MainForm->imVieworks->Refresh();
   MainForm->pnlSum->Caption = IntToStr(sum);
   MainForm->pnlDisplayCount->Caption = "16";

}
//---------------------------------------------------------------------------
// 2023 8 13 - chc set NULL
//  m_pobjectInfo = NULL;                       *
//  pImageInfo = NULL;
//  m_pBmpInfo1 = NULL;                         *
//  m_pUnpackedImage = NULL;                    *
__fastcall VworksCCD::~VworksCCD()
{

   MainForm->WriteSystemLog("Vieworks CCD Reset: ~");

   //Delete bitmap object
   if(m_pBmpInfo1) {
      delete m_pBmpInfo1;
      m_pBmpInfo1 = NULL;
   }

   MainForm->WriteSystemLog("Vieworks CCD Reset: ~m_pBmpInfo1");

   // 2023 8 13 - chc 不需要
   /*
   if(m_pvwGigE) {
      VWSDK::CloseVwGigE( m_pvwGigE );
      m_pvwGigE = NULL;
   }

   MainForm->WriteSystemLog("Vieworks CCD Reset: ~m_pvwGigE");
   */

   if(m_pUnpackedImage) {
      delete [] m_pUnpackedImage;
      m_pUnpackedImage = NULL;
   }

   MainForm->WriteSystemLog("Vieworks CCD Reset: ~m_pUnpackedImage");

   if(m_pobjectInfo) {
      delete m_pobjectInfo;
      m_pobjectInfo = NULL;
   }

   MainForm->WriteSystemLog("Vieworks CCD Reset: ~m_pobjectInfo");

}
//---------------------------------------------------------------------------
//CCD
//  AcquisitionMode: Continuous
//  ReadoutMode: 1
//  HorizontalStart: 0
//  HorizontalEbd: 1023
//  VerticalStart: 0
//  VerticalEbd: 1199
//
//  TriggerMode: On / Off
//  TriggerSource: Line0
//  TriggerActivation: LevelHigh

//Motion(TRG CH0)
//  Trigger Parameter
//    Compare Source: Command Counter
//    Compare Enable: =(Counting Up)
//    Trigger Source: CMP 0
//    Trigger Pulse Width: 10
//    Trigger Config: Pulse+Not Inverse
//    Compare Type: Linear
//  Compare Setting
//    Linear Compare 0: LCMP0
//    StartPoint: 100
//    RepeatTimes: 100
//    Interval: 14
__fastcall VworksCCD::SetTriggerMode(bool mode)
{

   if(mode == true) {
      VWSDK::CameraSetCustomCommand(m_pCamera, "TriggerMode", "On");
      VWSDK::CameraSetCustomCommand(m_pCamera, "TriggerSource", "Line0");
      VWSDK::CameraSetCustomCommand(m_pCamera, "TriggerActivation", "LevelHigh");
      TriggerFrameNo = 0;
      boolInTrigger = true;
   }
   else {
      boolInTrigger = false;
      VWSDK::CameraSetCustomCommand(m_pCamera, "TriggerMode", "Off");
   }
}
//---------------------------------------------------------------------------
// 2023 8 10 - chc Gain Set
__fastcall VworksCCD::SetTriggerGain(double fgain)
{
AnsiString str;

   str.sprintf("%.2f",fgain);
   VWSDK::RESULT ret4 = VWSDK::CameraSetCustomCommand(m_pCamera, "Gain", str.c_str());
}
//---------------------------------------------------------------------------
// 2023 8 11 - chc Close
__fastcall VworksCCD::CloseCCD()
{

   VWSDK::CloseVwGigE(m_pvwGigE);
}
//---------------------------------------------------------------------------
__fastcall VworksCCD::SetTriggerTargerBrightness(int targetbrightness)
{
AnsiString str;

   str.sprintf("%d",targetbrightness);
   VWSDK::RESULT ret4 = VWSDK::CameraSetCustomCommand(m_pCamera, "TargetBrightness", str.c_str());
}
//---------------------------------------------------------------------------
__fastcall VworksCCD::SetTriggerExposureAuto(bool mode)
{
AnsiString str;

   if(mode == false)
      VWSDK::RESULT ret7 = VWSDK::CameraSetCustomCommand(m_pCamera, "TargetBrightness", "Off");
   else
      VWSDK::RESULT ret7 = VWSDK::CameraSetCustomCommand(m_pCamera, "TargetBrightness", "Continuous");
}
//---------------------------------------------------------------------------
__fastcall VworksCCD::ClearActive()
{

   VWActive = false;
}
//---------------------------------------------------------------------------
__fastcall VworksCCD::Grab()
{

   VWSDK::CameraGrab(VieworksCCD->m_pCamera);
   boolVWLive = true;
}
//---------------------------------------------------------------------------


#pragma package(smart_init)
