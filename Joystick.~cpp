//---------------------------------------------------------------------------

#pragma hdrstop

#include "Joystick.h"
#include "MainFrm.h"

// 2020 2 13 - chc AI速度
#include "pci_8154.h"

#define STRICT
#define DIRECTINPUT_VERSION 0x0800
//#include <windows.h>
#include <commctrl.h>
#include <basetsd.h>
#include <dinput.h>
#pragma link "dinput8.lib"
#pragma link "dxguid.lib"

// 2020 2 17 - chc Joystick停止時還要檢查其它軸
void __fastcall StopAllAxis();

//-----------------------------------------------------------------------------
// Function-prototypes
//-----------------------------------------------------------------------------
INT_PTR CALLBACK MainDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam );
BOOL CALLBACK    EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext );
BOOL CALLBACK    EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance, VOID* pContext );
HRESULT InitDirectInput( HWND hDlg );
void    FreeDirectInput();
//HRESULT UpdateInputState( HWND hDlg );
HRESULT UpdateInputState( );

//-----------------------------------------------------------------------------
// Defines, constants, and global variables
//-----------------------------------------------------------------------------
#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

LPDIRECTINPUT8       g_pDI              = NULL;
LPDIRECTINPUTDEVICE8 g_pJoystick        = NULL;

//---------------------------------------------------------------------------
void __fastcall InitJoystick(HWND Handle)
{

   BoolJoystick = false;
   MainForm->boolJoystick = false;
   JoystickType = JOYSTICK_GENERAL;

   //if(FAILED(InitDirectInput(Handle))) {
   if(InitDirectInput(Handle) == S_FALSE) {
      //Application->MessageBox("Error Initializing DirectInput","DirectInput", MB_ICONERROR | MB_OK);
      MainForm->pnlJoystickStatus->Color = clSilver;

      // 2023 7 24 - chc Log
      MainForm->WriteSystemLog("InitJoystick Fail!");

   }
   else {

      // 2023 7 24 - chc Log
      MainForm->WriteSystemLog("InitJoystick Succ.");

      // Set a timer to go off 30 times a second. At every timer message
      // the input device will be read
      //MainForm->tmJoystick->Enabled = true;
      BoolJoystick = true;
      MainForm->pnlJoystickStatus->Color = clLime;
      MainForm->boolJoystick = true;
   }
}
//---------------------------------------------------------------------------
// JoyStick
//-----------------------------------------------------------------------------
// Name: InitDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
HRESULT InitDirectInput( HWND hDlg )
{
HRESULT hr;
static bool inputcreated=false,devices=false;

   // Register with the DirectInput subsystem and get a pointer
   // to a IDirectInput interface we can use.
   // Create a DInput object
   // => 已Create
   if(inputcreated == false) {
      if(FAILED(hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION,
                                       IID_IDirectInput8, (VOID**)&g_pDI, NULL)))
         return S_FALSE;
   }

   // Look for a simple joystick we can use for this sample program.
   // 已Create
   if(devices == false) {
      if(FAILED(hr = g_pDI->EnumDevices( DI8DEVCLASS_GAMECTRL,
                                      EnumJoysticksCallback,
                                      NULL, DIEDFL_ATTACHEDONLY)))
      return S_FALSE;
   }

   // Make sure we got a joystick
   if(NULL == g_pJoystick ) {
      //Application->MessageBox("Joystick not found. The sample will now exit.","DirectInput Sample",MB_ICONERROR | MB_OK);
      //return S_OK;
      return S_FALSE;
   }

   // Set the data format to "simple joystick" - a predefined data format
   //
   // A data format specifies which controls on a device we are interested in,
   // and how they should be reported. This tells DInput that we will be
   // passing a DIJOYSTATE2 structure to IDirectInputDevice::GetDeviceState().
   if(FAILED(hr = g_pJoystick->SetDataFormat( &c_dfDIJoystick2)))
      //return hr;
      return S_FALSE;

   // Set the cooperative level to let DInput know how this device should
   // interact with the system and with other DInput applications.
   if(FAILED(hr = g_pJoystick->SetCooperativeLevel( hDlg, DISCL_EXCLUSIVE |
                                                           DISCL_FOREGROUND)))
      //return hr;
      return S_FALSE;

   // Enumerate the joystick objects. The callback function enabled user
   // interface elements for objects that are found, and sets the min/max
   // values property for discovered axes.
   if(FAILED(hr = g_pJoystick->EnumObjects( EnumObjectsCallback,
                                           (VOID*)hDlg, DIDFT_ALL)))
      //return hr;
      return S_FALSE;

   return S_OK;
}
//---------------------------------------------------------------------------
// Free Joystick
void __fastcall FreeJoystick()
{

   //if(BoolJoystick == true) {
   if(MainForm->boolJoystick == true) {
      FreeDirectInput();
      MainForm->tmJoystick->Enabled = false;
   }
}
//---------------------------------------------------------------------------
// 2020 2 12 - chc 不用Handle
//void __fastcall UpdateJoystick(HWND Handle)
void __fastcall UpdateJoystick()
{
static bool active = false;

   if(active == true)
      return;
   active = true;

   g_pJoystick->Acquire();
   //UpdateInputState(Handle);

   UpdateInputState();

   active = false;
}
//---------------------------------------------------------------------------
// Name: UpdateInputState()
// Desc: Get the input device's state and display it.
//-----------------------------------------------------------------------------
// Scroll Bar Commands
//  #define SB_LINEUP           0
//  #define SB_LINELEFT         0
//  #define SB_LINEDOWN         1
//  #define SB_LINERIGHT        1
//  #define SB_PAGEUP           2
//  #define SB_PAGELEFT         2
//  #define SB_PAGEDOWN         3
//  #define SB_PAGERIGHT        3
//  #define SB_THUMBPOSITION    4
//  #define SB_THUMBTRACK       5
//  #define SB_TOP              6
//  #define SB_LEFT             6
//  #define SB_BOTTOM           7
//  #define SB_RIGHT            7
//  #define SB_ENDSCROLL        8
//
//winuser.h
//#define WM_INITDIALOG                   0x0110
//#define WM_COMMAND                      0x0111
//#define WM_SYSCOMMAND                   0x0112
//#define WM_TIMER                        0x0113
//#define WM_HSCROLL                      0x0114
//#define WM_VSCROLL                      0x0115
//#define WM_INITMENU                     0x0116
//#define WM_INITMENUPOPUP                0x0117
//#define WM_MENUSELECT                   0x011F
//#define WM_MENUCHAR                     0x0120
//#define WM_ENTERIDLE                    0x0121
//#define WM_CTLCOLORMSGBOX               0x0132
//#define WM_CTLCOLOREDIT                 0x0133
//#define WM_CTLCOLORLISTBOX              0x0134
//#define WM_CTLCOLORBTN                  0x0135
//#define WM_CTLCOLORDLG                  0x0136
//#define WM_CTLCOLORSCROLLBAR            0x0137
//#define WM_CTLCOLORSTATIC               0x0138
//
//#define WM_MOUSEFIRST                   0x0200
//#define WM_MOUSEMOVE                    0x0200
//#define WM_LBUTTONDOWN                  0x0201
//#define WM_LBUTTONUP                    0x0202
//#define WM_LBUTTONDBLCLK                0x0203
//#define WM_RBUTTONDOWN                  0x0204
//#define WM_RBUTTONUP                    0x0205
//#define WM_RBUTTONDBLCLK                0x0206
//#define WM_MBUTTONDOWN                  0x0207
//#define WM_MBUTTONUP                    0x0208
//#define WM_MBUTTONDBLCLK                0x0209
// 及其它
//
// 單螢幕: 在主畫面運作
// 雙螢幕: 在人員螢幕運作
//
// General Joysitck
//                   左                  右
//   前一張     XAxis(lX=-1000)          1
//   後一張     XAxis(lX=+1000)          4
//   前一頁     YAxis(lY=-1000)          2
//   後一頁     YAxis(lY=+1000)          3
//   首頁            5                   6
//   末頁            7                   8
//
// XBox Joysitck
//                   左                  右
//   前一張     XAxis(lX=-1000)          X(02)-3
//   後一張     XAxis(lX=+1000)          B(01)-2
//   前一頁     YAxis(lY=-1000)          Y(03)-4
//   後一頁     YAxis(lY=+1000)          A(00)-1
//   首頁          LB(04)-5             RB(05)-6
//   末頁         Back(06)-7           Start(07)-8
//
//HRESULT UpdateInputState( HWND hDlg )
HRESULT UpdateInputState( )
{
HRESULT     hr;
TCHAR       strText[128];                                                       // Device state text
DIJOYSTATE2 js;                                                                 // DInput joystick state
TCHAR*      str;
TPanel      *panel;
bool        pressed = false;
static bool released = false;
//TDBCtrlGrid *firstdbctrlgrid,*seconddbctrlgrid;

// 2020 2 12 - chc 記錄是否作動
static bool booljostickmovex = false;
static bool booljostickmovey = false;
static bool booljostickmovez = false;
static bool bool9 = false;

// 2020 2 13 - chc AISpeed
static int xspeedvalue = 0;
static int yspeedvalue = 0;
static int zspeedvalue = 0;

   if(NULL == g_pJoystick)
      return S_OK;

   // 2020 1 5 - chc home前不可以使用
   //if(MainForm->boolHomeDone == false) {
   //   return S_OK;
   //}

   // Poll the device to read the current state
   hr = g_pJoystick->Poll();
   if(FAILED(hr)) {
      // 記錄為Joystick Alarm
      MainForm->pnlJoystickStatus->Color = clRed;
      MainForm->sbSystemMessage->Panels->Items[6]->Text = "Joystick Disconnect!";
      // DInput is telling us that the input stream has been
      // interrupted. We aren't tracking any state between polls, so
      // we don't have any special reset that needs to be done. We
      // just re-acquire and try again.
      hr = g_pJoystick->Acquire();

      // 不再Wait, 會造成開機後初次執行系統會無法使用Joysitck, 且離開時會有Error Message
      //while(hr == DIERR_INPUTLOST)
      //    hr = g_pJoystick->Acquire();

      // hr may be DIERR_OTHERAPPHASPRIO or other errors.  This
      // may occur when the app is minimized or in the process of
      // switching, so just try again later
      return S_OK;
   }

   // Get the input's device state
   if(FAILED( hr = g_pJoystick->GetDeviceState( sizeof(DIJOYSTATE2), &js)))
      return hr; // The device should have been acquired during the Poll()

   // 記錄為Joystick Alarm
   MainForm->pnlJoystickStatus->Color = clLime;

   MainForm->pnlJX->Caption = IntToStr(js.lX);
   MainForm->pnlJY->Caption = IntToStr(js.lY);
   MainForm->pnlJZ->Caption = IntToStr(js.lZ);

   // 2020 2 12 - chc 顯示Joystick XYZ Value
   MainForm->pnlJoystickX->Caption = IntToStr(js.lX);
   MainForm->pnlJoystickY->Caption = IntToStr(js.lY);
   MainForm->pnlJoystickZ->Caption = IntToStr(js.lZ);

   // 2020 2 14 - chc 要更新
   MainForm->JoystickStart = MainForm->edJoystickStart->Text.ToInt();
   MainForm->JoystickStop = MainForm->edJoystickStop->Text.ToInt();

   //firstdbctrlgrid = MainForm->dbcgLCDDefect;
   //seconddbctrlgrid = MainForm->dbcgLCDMatDefect;

   //
   // BcB 6.0
   //---------------------------------------------------------------------------
   // X-Axes (-)
   //---------------------------------------------------------------------------
   if((MainForm->cbAISpeed->Checked == false && js.lX <= 0-MainForm->JoystickStart) ||
      (MainForm->cbAISpeed->Checked == true && js.lX <= 0-MainForm->edAISpeedStart->Text.ToInt())) {

      // 2020 2 17 - chc 反向?
      if(MainForm->pnlJoystickActive->Color == clLime && booljostickmovex == true && MainForm->MoveDirection == 1)
         goto xstop;

      MainForm->sbSystemMessage->Panels->Items[6]->Text = "X: Left";
      pressed = true;
      if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovey == false && booljostickmovez == false)) {
         booljostickmovex = true;
         MainForm->cbTableDirection->Checked = true;
         MainForm->WriteSystemLog("X: Left");

         // 2020 2 14 - chc 設定最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            xspeedvalue = MainForm->pnlJoystickX->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(X_AXIS, (F64)10000, 1);
               MainForm->WriteSystemLog("AISpeed: X-設最大速10000. " + IntToStr(xspeedvalue));
            }
            else {
               _8154_set_max_override_speed(X_AXIS, (F64)500000, 1);
               MainForm->WriteSystemLog("AISpeed: X-設最大速500000. " + IntToStr(xspeedvalue));
            }
         }

         MainForm->DoBackwardX();
      }

      // 2020 2 14 - chc AISpeed
      else {
         if(MainForm->cbAISpeed->Checked == true && booljostickmovex == true && abs(xspeedvalue-js.lX) > MainForm->edAISpeedChange->Text.ToInt()) {
            double ratio,unit;
            int value,base,maxvel;
            base = MainForm->edAISpeedStart->Text.ToInt();
            value = MainForm->pnlJoystickX->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               unit = 10000 / (1000 - base);
            else
               unit = 500000 / (1000 - base);
            maxvel = (abs(value) - base) * unit;
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               ratio = (double)(maxvel * 100) / 10000;
            else
               ratio = (double)(maxvel * 100) / 500000;
            _8154_speed_override(X_AXIS, ratio, 0.1);
            MainForm->WriteSystemLog(">Joystick: X-, AI變速度= " + FloatToStr(maxvel) + "," + IntToStr(value) + "," + FloatToStr(ratio));
            xspeedvalue = value;
         }
      }

   }
   //---------------------------------------------------------------------------
   // X-Axes (+)
   //---------------------------------------------------------------------------
   else if((MainForm->cbAISpeed->Checked == false && js.lX >= MainForm->JoystickStart) ||
           (MainForm->cbAISpeed->Checked == true && js.lX >= MainForm->edAISpeedStart->Text.ToInt())) {

      // 2020 2 17 - chc 反向?
      if(MainForm->pnlJoystickActive->Color == clLime && booljostickmovex == true && MainForm->MoveDirection == 2)
         goto xstop;

      MainForm->sbSystemMessage->Panels->Items[6]->Text = "X: Right";
      pressed = true;

      // 2012 2 13 - chc 也要看x
      //if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovey == false && booljostickmovez == false)) {
      if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovey == false && booljostickmovez == false)) {

         MainForm->WriteSystemLog("X: Right");
         booljostickmovex = true;
         MainForm->cbTableDirection->Checked = true;

         // 2020 2 13 - chc 設定最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            xspeedvalue = MainForm->pnlJoystickX->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(X_AXIS, (F64)10000, 1);
               MainForm->WriteSystemLog("AISpeed: X+設最大速10000. " + IntToStr(xspeedvalue));
            }
            else {
               _8154_set_max_override_speed(X_AXIS, (F64)500000, 1);
               MainForm->WriteSystemLog("AISpeed: X+設最大速500000. " + IntToStr(xspeedvalue));
            }
         }

         MainForm->DoMoveX();
      }

      // 2020 2 13 - chc AISpeed
      else {
         if(MainForm->cbAISpeed->Checked == true && booljostickmovex == true && abs(xspeedvalue-js.lX) > MainForm->edAISpeedChange->Text.ToInt()) {
            double ratio,unit;
            int value,base,maxvel;
            base = MainForm->edAISpeedStart->Text.ToInt();
            value = MainForm->pnlJoystickX->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               unit = 10000 / (1000 - base);
            else
               unit = 500000 / (1000 - base);
            maxvel = (abs(value) - base) * unit;
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               ratio = (double)(maxvel * 100) / 10000;
            else
               ratio = (double)(maxvel * 100) / 500000;
            _8154_speed_override(X_AXIS, ratio, 0.1);
            MainForm->WriteSystemLog(">Joystick: X+, AI變速度= " + FloatToStr(maxvel) + "," + IntToStr(value) + "," + FloatToStr(ratio));
            xspeedvalue = value;
         }
      }

   }
   // 2020 2 13 - chc AI Speed: edAISpeedStart
   //else if(abs(js.lX) <= MainForm->JoystickStop) {
   else if((MainForm->cbAISpeed->Checked == false && abs(js.lX) <= MainForm->JoystickStop) ||
           (MainForm->cbAISpeed->Checked == true && abs(js.lX) < MainForm->edAISpeedStart->Text.ToInt())) {
xstop:
      // 2020 2 12 - chc 取消
      if(booljostickmovex == true) {
         booljostickmovex = false;
         if(MainForm->cbContinueMove->Checked == true) {
            MainForm->boolJogMove = false;

            // 2020 2 17 - chc 不會立即停下! 要下stop
            StopAllAxis();

         }

         // 2020 2 16 - chc 記錄目前做連續移動中: 軸與移動方向(1/2: 正/反, 0-沒有移動)
         MainForm->MoveDirection = 0;

         // 2020 2 13 - chc 取消最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(X_AXIS, (F64)10000, 0);
               MainForm->WriteSystemLog("AISpeed: X設最大速10000.結束");
            }
            else {
               _8154_set_max_override_speed(X_AXIS, (F64)500000, 0);
               MainForm->WriteSystemLog("AISpeed: X設最大速500000.結束");
            }
         }

      }

   }
   //---------------------------------------------------------------------------
   // Y-Axes (-)
   //---------------------------------------------------------------------------
   if((MainForm->cbAISpeed->Checked == false && js.lY <= 0-MainForm->JoystickStart) ||
      (MainForm->cbAISpeed->Checked == true && js.lY <= 0-MainForm->edAISpeedStart->Text.ToInt())) {

      // 2020 2 17 - chc 反向?
      if(MainForm->pnlJoystickActive->Color == clLime && booljostickmovey == true && MainForm->MoveDirection == 2) {
         MainForm->WriteSystemLog("-Y反向: Stop");
         goto ystop;
      }

      MainForm->sbSystemMessage->Panels->Items[6]->Text = "Y: Front";
      pressed = true;

      // 2012 2 13 - chc 也要看y
      //if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovez == false)) {
      if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovey == false && booljostickmovez == false)) {

         MainForm->WriteSystemLog("Y: Front");
         booljostickmovey = true;
         MainForm->cbTableDirection->Checked = true;

         // 2020 2 14 - chc 設定最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            yspeedvalue = MainForm->pnlJoystickY->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(Y_AXIS, (F64)10000, 1);
               MainForm->WriteSystemLog("AISpeed: Y-設最大速10000. " + IntToStr(yspeedvalue));
            }
            else {
               _8154_set_max_override_speed(Y_AXIS, (F64)500000, 1);
               MainForm->WriteSystemLog("AISpeed: Y-設最大速500000. " + IntToStr(yspeedvalue));
            }
         }

         MainForm->DoMoveY();

      }

      // 2020 2 14 - chc AISpeed
      else {
         if(MainForm->cbAISpeed->Checked == true && booljostickmovey == true && abs(yspeedvalue-js.lY) > MainForm->edAISpeedChange->Text.ToInt()) {
            double ratio,unit;
            int value,base,maxvel;
            base = MainForm->edAISpeedStart->Text.ToInt();
            value = MainForm->pnlJoystickY->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               unit = 10000 / (1000 - base);
            else
               unit = 500000 / (1000 - base);
            maxvel = (abs(value) - base) * unit;
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               ratio = (double)(maxvel * 100) / 10000;
            else
               ratio = (double)(maxvel * 100) / 500000;
            _8154_speed_override(Y_AXIS, ratio, 0.1);
            MainForm->WriteSystemLog(">Joystick: Y-, AI變速度= " + FloatToStr(maxvel) + "," + IntToStr(value) + "," + FloatToStr(ratio));
            yspeedvalue = value;
         }
      }

   }
   //---------------------------------------------------------------------------
   // Y-Axes (+)
   //---------------------------------------------------------------------------
   else if((MainForm->cbAISpeed->Checked == false && js.lY >= MainForm->JoystickStart) ||
           (MainForm->cbAISpeed->Checked == true && js.lY >= MainForm->edAISpeedStart->Text.ToInt())) {

      // 2020 2 17 - chc 反向?
      if(MainForm->pnlJoystickActive->Color == clLime && booljostickmovey == true && MainForm->MoveDirection == 1) {
         MainForm->WriteSystemLog("+Y反向: Stop");
         goto ystop;
      }

      MainForm->sbSystemMessage->Panels->Items[6]->Text = "Y: Rear";
      pressed = true;

      // 2012 2 13 - chc 也要看y
      //if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovez == false)) {
      if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovey == false && booljostickmovez == false)) {

         MainForm->WriteSystemLog("Y: Rear");
         booljostickmovey = true;
         MainForm->cbTableDirection->Checked = true;

         // 2020 2 14 - chc 設定最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            yspeedvalue = MainForm->pnlJoystickY->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(Y_AXIS, (F64)10000, 1);
               MainForm->WriteSystemLog("AISpeed: Y+設最大速10000. " + IntToStr(yspeedvalue));
            }
            else {
               _8154_set_max_override_speed(Y_AXIS, (F64)500000, 1);
               MainForm->WriteSystemLog("AISpeed: Y+設最大速500000. " + IntToStr(yspeedvalue));
            }
         }

         MainForm->DoBackwardY();
      }

      // 2020 2 13 - chc AISpeed
      else {
         if(MainForm->cbAISpeed->Checked == true && booljostickmovey == true && abs(yspeedvalue-js.lY) > MainForm->edAISpeedChange->Text.ToInt()) {
            double ratio,unit;
            int value,base,maxvel;
            base = MainForm->edAISpeedStart->Text.ToInt();
            value = MainForm->pnlJoystickY->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               unit = 10000 / (1000 - base);
            else
               unit = 500000 / (1000 - base);
            maxvel = (abs(value) - base) * unit;
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               ratio = (double)(maxvel * 100) / 10000;
            else
               ratio = (double)(maxvel * 100) / 500000;
            _8154_speed_override(Y_AXIS, ratio, 0.1);
            MainForm->WriteSystemLog(">Joystick: Y+, AI變速度= " + FloatToStr(maxvel) + "," + IntToStr(value) + "," + FloatToStr(ratio));
            yspeedvalue = value;
         }
      }

   }
   // 2020 2 14a - chc 取消
   //else if(abs(js.lY) <= MainForm->JoystickStop) {
   else if((MainForm->cbAISpeed->Checked == false && abs(js.lY) <= MainForm->JoystickStop) ||
           (MainForm->cbAISpeed->Checked == true && abs(js.lY) < MainForm->edAISpeedStart->Text.ToInt())) {

ystop:
      // 2020 2 12 - chc 取消
      if(booljostickmovey == true) {
         booljostickmovey = false;
         if(MainForm->cbContinueMove->Checked == true) {
            MainForm->boolJogMove = false;

            // 2020 2 17 - chc 不會立即停下! 要下stop
            StopAllAxis();

         }

         // 2020 2 16 - chc 記錄目前做連續移動中: 軸與移動方向(1/2: 正/反, 0-沒有移動)
         MainForm->MoveDirection = 0;

         // 2020 2 14 - chc 取消最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(Y_AXIS, (F64)10000, 0);
               MainForm->WriteSystemLog("AISpeed: Y設最大速10000.結束");
            }
            else {
               _8154_set_max_override_speed(Y_AXIS, (F64)500000, 0);
               MainForm->WriteSystemLog("AISpeed: Y設最大速500000.結束");
            }
         }

      }

   }
   //---------------------------------------------------------------------------
   // Z-Axes (-)
   //---------------------------------------------------------------------------
   if((MainForm->cbAISpeed->Checked == false && js.lZ <= 0-MainForm->JoystickStart) ||
      (MainForm->cbAISpeed->Checked == true && js.lZ <= 0-MainForm->edAISpeedStart->Text.ToInt())) {

      // 2020 2 17 - chc 反向?
      if(MainForm->pnlJoystickActive->Color == clLime && booljostickmovez == true && MainForm->MoveDirection == 1)
         goto zstop;

      MainForm->sbSystemMessage->Panels->Items[6]->Text = "Z: Up";
      pressed = true;
      // 往上
      // 2012 2 13 - chc 也要看z
      //if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovey == false)) {
      if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovey == false && booljostickmovez == false)) {

         MainForm->WriteSystemLog("Z: Up");
         booljostickmovez = true;
         MainForm->cbTableDirection->Checked = true;

         // 2020 2 14 - chc 設定最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            zspeedvalue = MainForm->pnlJoystickZ->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(Z_AXIS, (F64)100, 1);
               MainForm->WriteSystemLog("AISpeed: Z-設最大速100. " + IntToStr(zspeedvalue));
            }
            else {
               _8154_set_max_override_speed(Z_AXIS, (F64)5000, 1);
               MainForm->WriteSystemLog("AISpeed: Z-設最大速5000. " + IntToStr(zspeedvalue));
            }
         }

         MainForm->DoBackwardZ();
      }

      // 2020 2 14 - chc AISpeed
      else {
         if(MainForm->cbAISpeed->Checked == true && booljostickmovez == true && abs(zspeedvalue-js.lZ) > MainForm->edAISpeedChange->Text.ToInt()) {
            double ratio,unit;
            int value,base,maxvel;
            base = MainForm->edAISpeedStart->Text.ToInt();
            value = MainForm->pnlJoystickZ->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               unit = 100.0 / (1000.0 - base);
            else
               unit = 5000.0 / (1000.0 - base);
            maxvel = (abs(value) - base) * unit;
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               ratio = (double)(maxvel * 100.0) / 100.0;
            else
               ratio = (double)(maxvel * 100.0) / 5000.0;
            _8154_speed_override(Z_AXIS, ratio, 0.1);
            MainForm->WriteSystemLog(">Joystick: Z-, AI變速度= " + FloatToStr(maxvel) + "," + IntToStr(value) + "," + FloatToStr(ratio));
            zspeedvalue = value;
         }
      }

   }
   //---------------------------------------------------------------------------
   // Z-Axes (+)
   //---------------------------------------------------------------------------
   else if((MainForm->cbAISpeed->Checked == false && js.lZ >= MainForm->JoystickStart) ||
           (MainForm->cbAISpeed->Checked == true && js.lZ >= MainForm->edAISpeedStart->Text.ToInt())) {

      // 2020 2 17 - chc 反向?
      if(MainForm->pnlJoystickActive->Color == clLime && booljostickmovez == true && MainForm->MoveDirection == 2)
         goto zstop;

      MainForm->sbSystemMessage->Panels->Items[6]->Text = "Z: Down";
      pressed = true;
      // 往下
      // 2012 2 13 - chc 也要看z
      //if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovey == false)) {
      if(MainForm->pnlJoystickActive->Color == clLime && (booljostickmovex == false && booljostickmovey == false && booljostickmovez == false)) {

         MainForm->WriteSystemLog("Z: Down");
         booljostickmovez = true;
         MainForm->cbTableDirection->Checked = true;

         // 2020 2 14 - chc 設定最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            zspeedvalue = MainForm->pnlJoystickZ->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(Z_AXIS, (F64)100, 1);
               MainForm->WriteSystemLog("AISpeed: Z+設最大速100. " + IntToStr(zspeedvalue));
            }
            else {
               _8154_set_max_override_speed(Z_AXIS, (F64)5000, 1);
               MainForm->WriteSystemLog("AISpeed: Z+設最大速5000. " + IntToStr(zspeedvalue));
            }
         }

         MainForm->DoMoveZ();
      }

      // 2020 2 14 - chc AISpeed
      else {
         if(MainForm->cbAISpeed->Checked == true && booljostickmovez == true && abs(zspeedvalue-js.lY) > MainForm->edAISpeedChange->Text.ToInt()) {
            double ratio,unit;
            int value,base,maxvel;
            base = MainForm->edAISpeedStart->Text.ToInt();
            value = MainForm->pnlJoystickZ->Caption.ToInt();
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               unit = 100.0 / (1000.0 - base);
            else
               unit = 5000.0 / (1000.0 - base);
            maxvel = (abs(value) - base) * unit;
            if(MainForm->rgJoystickSpeed->ItemIndex == 0)
               ratio = (double)(maxvel * 100.0) / 100.0;
            else
               ratio = (double)(maxvel * 100.0) / 5000.0;
            _8154_speed_override(Z_AXIS, ratio, 0.1);
            MainForm->WriteSystemLog(">Joystick: Z+, AI變速度= " + FloatToStr(maxvel) + "," + IntToStr(value) + "," + FloatToStr(ratio));
            zspeedvalue = value;
         }
      }

   }
   // 2020 2 14a - chc 取消
   //else if(abs(js.lZ) <= MainForm->JoystickStop) {
   else if((MainForm->cbAISpeed->Checked == false && abs(js.lZ) <= MainForm->JoystickStop) ||
           (MainForm->cbAISpeed->Checked == true && abs(js.lZ) < MainForm->edAISpeedStart->Text.ToInt())) {

zstop:
      // 取消
      if(booljostickmovez== true) {
         booljostickmovez= false;
         if(MainForm->cbContinueMove->Checked == true) {
            MainForm->boolJogMove = false;

            // 2020 2 17 - chc 不會立即停下! 要下stop
            StopAllAxis();

         }

         // 2020 2 14 - chc 取消最大速: 50mm
         if(MainForm->cbAISpeed->Checked == true) {
            if(MainForm->rgJoystickSpeed->ItemIndex == 0) {
               _8154_set_max_override_speed(Z_AXIS, (F64)100, 0);
               MainForm->WriteSystemLog("AISpeed: Z設最大速100.結束");
            }
            else {
               _8154_set_max_override_speed(Z_AXIS, (F64)5000, 0);
               MainForm->WriteSystemLog("AISpeed: Z設最大速5000.結束");
            }
         }

      }
   }
   //---------------------------------------------------------------------------

   // Fill up text with which buttons are pressed
   str = strText;
   for(int i=0 ; i<12 ; i++) {                                                  // 可到128個Buttoms
      if(js.rgbButtons[i] & 0x80 ) {
         //panel = (TPanel*)(MainForm->FindComponent("pnlButton" + IntToStr(i+1)));
         //panel->Color = clLime;
         MainForm->sbSystemMessage->Panels->Items[6]->Text = "Button: " + IntToStr(i+1);

         // 2020 1 12 - chc Joystick 顯示 : pnlJoystick1
         if(i < 10) {
            panel = (TPanel*)(MainForm->FindComponent("pnlJoystick" + IntToStr(i+1)));
         }
         else if(i == 10) {
            panel = (TPanel*)(MainForm->FindComponent("pnlJoystickLeft"));
            MainForm->rgJoystickSpeed->ItemIndex = 0;
            MainForm->pnlSpeed->Caption = "Low";
         }
         else if(i == 11) {
            panel = (TPanel*)(MainForm->FindComponent("pnlJoystickRight"));
            MainForm->rgJoystickSpeed->ItemIndex = 1;
            MainForm->pnlSpeed->Caption = "High";
         }
         panel->Color = clLime;

         // 使用搖桿
         // 2021 12 18 - chc 指定7/8/9/10何者為Enable/Disable: JoystickEnabledKey, JoystickEnabledMode
         //if((i+1) == 9) {
         int keysel = i+1;
         if((keysel == MainForm->JoystickEnabledKey && MainForm->JoystickEnabledMode == 0) ||
            (keysel >= 7 && keysel <= 10            && MainForm->JoystickEnabledMode == 1)) {

            if(bool9 == false) {
               if(MainForm->pnlJoystickActive->Color == clSilver) 
                  MainForm->SetJoystickActive(true);
               else
                  MainForm->SetJoystickActive(false);
               bool9 = true;
            }
         }

         if(released == true) {
            // XBox
            if(JoystickType == JOYSTICK_XBOX) {
               // Second: 左, 右, 上頁, 下頁, 首頁, 末頁
               /*
               if((i+1) == 3)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_LINELEFT,0);
               else if((i+1) == 2)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_LINERIGHT,0);
               else if((i+1) == 4)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_PAGELEFT,0);
               else if((i+1) == 1)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_PAGERIGHT,0);
               else if((i+1) == 6)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_LEFT,0);
               else if((i+1) == 8)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_RIGHT,0);
               // First: 首頁, 末頁
               else if((i+1) == 5)
                  SendMessage(firstdbctrlgrid->Handle,WM_HSCROLL,SB_LEFT,0);
               else if((i+1) == 7)
                  SendMessage(firstdbctrlgrid->Handle,WM_HSCROLL,SB_RIGHT,0);
               */
            }
            else {

               // Second: 左, 右, 上頁, 下頁, 首頁, 末頁
               /*
               if((i+1) == 1)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_LINELEFT,0);
               else if((i+1) == 4)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_LINERIGHT,0);
               else if((i+1) == 2)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_PAGELEFT,0);
               else if((i+1) == 3)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_PAGERIGHT,0);
               else if((i+1) == 6)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_LEFT,0);
               else if((i+1) == 8)
                  SendMessage(seconddbctrlgrid->Handle,WM_HSCROLL,SB_RIGHT,0);
               // First: 首頁, 末頁
               else if((i+1) == 5)
                  SendMessage(firstdbctrlgrid->Handle,WM_HSCROLL,SB_LEFT,0);
               else if((i+1) == 7)
                  SendMessage(firstdbctrlgrid->Handle,WM_HSCROLL,SB_RIGHT,0);
               */
            }
         }
         pressed = true;
      }
      else {
         //panel = (TPanel*)(MainForm->FindComponent("pnlButton" + IntToStr(i+1)));
         //i/f(panel->Color != clSilver)
         //   panel->Color = clSilver;
         //MainForm->sbSystemMessage->Panels->Items[6]->Text = "";

         // 2020 1 12 - chc Joystick 顯示 : pnlJoystick1
         if(i < 10) {
            panel = (TPanel*)(MainForm->FindComponent("pnlJoystick" + IntToStr(i+1)));
         }
         else if(i == 10) {
            panel = (TPanel*)(MainForm->FindComponent("pnlJoystickLeft"));
         }
         else if(i == 11) {
            panel = (TPanel*)(MainForm->FindComponent("pnlJoystickRight"));
         }
         panel->Color = clSilver;
         // 使用搖桿
         if((i+1) == 9)
            bool9 = false;
      }
   }
   //
   if(pressed == false) {
      MainForm->sbSystemMessage->Panels->Items[6]->Text = "";
      released = true;
   }
   else
      released = false;

   return S_OK;
}
//-----------------------------------------------------------------------------
// Name: FreeDirectInput()
// Desc: Initialize the DirectInput variables.
//-----------------------------------------------------------------------------
void FreeDirectInput()
{

   // Unacquire the device one last time just in case
   // the app tried to exit while the device is still acquired.
   if( g_pJoystick )
      g_pJoystick->Unacquire();

   // Release any DirectInput objects.
   SAFE_RELEASE( g_pJoystick );
   SAFE_RELEASE( g_pDI );
}
//-----------------------------------------------------------------------------
// Name: EnumJoysticksCallback()
// Desc: Called once for each enumerated joystick. If we find one, create a
//       device interface on it so we can play with it.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumJoysticksCallback( const DIDEVICEINSTANCE* pdidInstance,
                                     VOID* pContext )
{
HRESULT hr;

   // Obtain an interface to the enumerated joystick.
   hr = g_pDI->CreateDevice( pdidInstance->guidInstance, &g_pJoystick, NULL );

   // If it failed, then we can't use this joystick. (Maybe the user unplugged
   // it while we were in the middle of enumerating it.)
   if(FAILED(hr))
      return DIENUM_CONTINUE;

   // Stop enumeration. Note: we're just taking the first joystick we get. You
   // could store all the enumerated joysticks and let the user pick.
   return DIENUM_STOP;
}
//-----------------------------------------------------------------------------
// Name: EnumObjectsCallback()
// Desc: Callback function for enumerating objects (axes, buttons, POVs) on a
//       joystick. This function enables user interface elements for objects
//       that are found to exist, and scales axes min/max values.
//-----------------------------------------------------------------------------
BOOL CALLBACK EnumObjectsCallback( const DIDEVICEOBJECTINSTANCE* pdidoi,
                                   VOID* pContext )
{
HWND hDlg = (HWND)pContext;

   static int nSliderCount = 0;  // Number of returned slider controls
   static int nPOVCount = 0;     // Number of returned POV controls

   // For axes that are returned, set the DIPROP_RANGE property for the
   // enumerated axis in order to scale min/max values.
   if(pdidoi->dwType & DIDFT_AXIS) {
      DIPROPRANGE diprg;
      diprg.diph.dwSize       = sizeof(DIPROPRANGE);
      diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
      diprg.diph.dwHow        = DIPH_BYID;
      diprg.diph.dwObj        = pdidoi->dwType; // Specify the enumerated axis
      diprg.lMin              = -1000;
      diprg.lMax              = +1000;

      // Set the range for the axis
      if(FAILED( g_pJoystick->SetProperty( DIPROP_RANGE, &diprg.diph)))
         return DIENUM_STOP;
   }

   return DIENUM_CONTINUE;
}
//-----------------------------------------------------------------------------


