//---------------------------------------------------------------------------

#ifndef MainFrmH
#define MainFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "LMDButton.hpp"
#include "LMDCustomButton.hpp"
#include <Chart.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include "LMDBaseEdit.hpp"
#include "LMDButtonControl.hpp"
#include "LMDCheckBox.hpp"
#include "LMDComboBox.hpp"
#include "LMDControl.hpp"
#include "LMDCustomBevelPanel.hpp"
#include "LMDCustomButtonGroup.hpp"
#include "LMDCustomCheckBox.hpp"
#include "LMDCustomComboBox.hpp"
#include "LMDCustomControl.hpp"
#include "LMDCustomEdit.hpp"
#include "LMDCustomGroupBox.hpp"
#include "LMDCustomPanel.hpp"
#include "LMDCustomPanelFill.hpp"
#include "LMDCustomParentPanel.hpp"
#include "LMDCustomRadioGroup.hpp"
#include "LMDCustomSheetControl.hpp"
#include "LMDEdit.hpp"
#include "LMDGroupBox.hpp"
#include "LMDPageControl.hpp"
#include "LMDRadioGroup.hpp"
#include "LMDThemedComboBox.hpp"
#include <Graphics.hpp>
#include <Grids.hpp>
#include "YbCommDevice.h"

// pci-8154 f64
#include "type_def.h"
#include <ImgList.hpp>
#include <DB.hpp>
#include <DBTables.hpp>
#include "LMDCustomMaskEdit.hpp"
#include "LMDMaskEdit.hpp"

// 2016 4 16 - chc eVision
#include "EmcLegacy.h"
// 要使用ImgScaleRotate()功能
#include "EImage.h"
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>

// 2016 4 18 - chc 8158
#include "type_def.h"

// 2016 4 19 - chc APS - PCI-7856
#include "APS168.h"
#include "APS_Define.h"
#include "ErrorCodeDef.h"
#include "LMDBaseControl.hpp"
#include "LMDBaseGraphicControl.hpp"
#include "LMDBaseMeter.hpp"
#include "LMDCustomProgress.hpp"
#include "LMDGraphicControl.hpp"
#include "LMDProgress.hpp"

// fabs
#include <math.h>
#include "LMDCustomTrackBar.hpp"
#include "LMDTrackBar.hpp"
#include "LMDBaseLabel.hpp"
#include "LMDCustomLabel.hpp"
#include "LMDLabel.hpp"
#include "LMDSBar.hpp"
#include <Menus.hpp>
#include "ICImagingControl3_OCX.h"
#include <OleCtrls.hpp>
#include <ScktComp.hpp>
#include <jpeg.hpp>
#include "LMDBackPanel.hpp"
#include "LMDSimplePanel.hpp"

// 精度為0.1um
#define X_RESOLUTION    0.1
#define Y_RESOLUTION    0.1
#define Z_RESOLUTION    0.1
#define T_RESOLUTION    0.05
#define L_RESOLUTION    8.2                                                     // 257 - 2856
#define W_RESOLUTION    0.1

// 2021 12 9 - chc 錯了
//#define MM_TO_UM        10000.0
#define MM_TO_UM        1000.0

// 2016 8 30 - chc Define Axis Range(um)
// 2019 7 8 - chc 行程為545*677 => 600*600
//#define X_RANGE         2000000                                                 // 200mm
//#define Y_RANGE         2050000                                                 // 205mm
#define Z_RANGE         500000                                                  // 5mm
#define T_RANGE         3200000
#define X_RANGE         6000000                                                 // 200mm
#define Y_RANGE         6000000                                                 // 205mm

// 2016 7 23 - chc timeout from 5sec to 30sec
// 2022 5 18 - chc 增加到40sec
//#define MOTION_TIMEOUT                  30000
#define MOTION_TIMEOUT                  40000

// 2023 6 5 - chc init ViewWorks CCD
// 2023 8 6 - chc 另建module
//#include "VwGigE.API.h"
//#pragma link "VwGigE.v7.lib"


//---------------------------------------------------------------------------
class TMainForm : public TForm
{
__published:	// IDE-managed Components

        TStatusBar *sbSystemMessage;
        TTimer *tmSystem;
        TLMDPageControl *pcSystem;
        TLMDTabSheet *tsSystem;
        TLMDTabSheet *tsParameter;
        TLMDTabSheet *tsMotion;
        TLMDTabSheet *tsHelp;
        TLMDTabSheet *tsUser;
        TLMDGroupBox *gbAxisInformation;
        TLabel *Label60;
        TLabel *Label61;
        TLabel *Label72;
        TLabel *laXAxis;
        TLabel *laTAxis;
        TLabel *laZAxis;
        TLabel *laYAxis;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label25;
        TLMDEdit *edCommandX;
        TLMDEdit *edCounterX;
        TLMDEdit *edComparatorX;
        TLMDEdit *edCommandY;
        TLMDEdit *edCounterY;
        TLMDEdit *edComparatorY;
        TLMDEdit *edCommandZ;
        TLMDEdit *edCounterZ;
        TLMDEdit *edComparatorZ;
        TLMDEdit *edCommandT;
        TLMDEdit *edCounterT;
        TLMDEdit *edComparatorT;
        TPanel *pnlStatusX;
        TPanel *pnlStatusY;
        TPanel *pnlStatusZ;
        TPanel *pnlStatusT;
        TPanel *pnlMotionStatusX;
        TPanel *pnlMotionStatusY;
        TPanel *pnlMotionStatusZ;
        TPanel *pnlMotionStatusT;
        TPanel *pnlIOStatusX;
        TPanel *pnlIOStatusY;
        TPanel *pnlIOStatusZ;
        TPanel *pnlIOStatusT;
        TLMDGroupBox *LMDGroupBox19;
        TLabel *Label69;
        TLabel *Label70;
        TLabel *la8154Status;
        TPanel *pnl8154Status;
        TPanel *pnl7856Status;
        TPanel *pnlAIStatus;
        TLMDGroupBox *LMDGroupBox20;
        TComboBox *combAxis;
        TLMDButton *btnResetOneAxis;
        TLMDButton *btnResetAll;
        TLMDButton *btnMove;
        TLMDButton *btnBackward;
        TLMDButton *btnHomeOneAxis;
        TPanel *pnlHomeStatus;
        TPanel *Panel132;
        TButton *btnHome;
        TPanel *pnlAllHomeStatus;
        TLMDGroupBox *rgRelativeMove;
        TLabel *Label32;
        TLMDButton *btnMoveX;
        TLMDButton *btnBackwardX;
        TLMDButton *btnStopRelative;
        TLMDGroupBox *rgAbsoluteMove;
        TLMDButton *btnMoveAbsolute;
        TLMDButton *btnStopAbsolute;
        TLabel *Label2;
        TLMDButton *btnMoveY;
        TLMDButton *btnBackwardY;
        TLabel *Label4;
        TLMDButton *btnMoveZ;
        TLMDButton *btnBackwardZ;
        TLabel *Label5;
        TLMDButton *btnMoveT;
        TLMDButton *btnBackwardT;
        TLMDPageControl *pcMotion;
        TLMDTabSheet *tsMotionParameter;
        TLMDGroupBox *gbMotion;
        TLabel *Label137;
        TLabel *Label138;
        TLabel *Label139;
        TLabel *Label140;
        TLabel *Label141;
        TLabel *Label142;
        TLabel *Label143;
        TLabel *Label121;
        TLabel *Label49;
        TLabel *Label52;
        TLabel *Label54;
        TLabel *Label56;
        TLabel *Label58;
        TLabel *Label59;
        TLabel *Label62;
        TLabel *Label219;
        TLMDEdit *edStartVelX;
        TLMDEdit *edMaxVelX;
        TLMDEdit *edDistanceX;
        TLMDEdit *edTaccX;
        TLMDEdit *edTdecX;
        TLMDEdit *edPositionX;
        TLMDEdit *edHomeVelX;
        TLMDEdit *edReviewVelX;
        TLMDEdit *edReviewVelY;
        TLMDEdit *edHomeVelY;
        TLMDEdit *edPositionY;
        TLMDEdit *edTdecY;
        TLMDEdit *edTaccY;
        TLMDEdit *edDistanceY;
        TLMDEdit *edMaxVelY;
        TLMDEdit *edStartVelY;
        TLMDEdit *edReviewVelZ;
        TLMDEdit *edHomeVelZ;
        TLMDEdit *edPositionZ;
        TLMDEdit *edTdecZ;
        TLMDEdit *edTaccZ;
        TLMDEdit *edDistanceZ;
        TLMDEdit *edMaxVelZ;
        TLMDEdit *edStartVelZ;
        TLMDEdit *edReviewVelT;
        TLMDEdit *edHomeVelT;
        TLMDEdit *edPositionT;
        TLMDEdit *edTdecT;
        TLMDEdit *edTaccT;
        TLMDEdit *edDistanceT;
        TLMDEdit *edMaxVelT;
        TLMDEdit *edStartVelT;
        TLMDEdit *edUpLimitX;
        TLMDEdit *edUpLimitY;
        TLMDEdit *edUpLimitZ;
        TLMDEdit *edUpLimitT;
        TLMDCheckBox *cbOrgLogicX;
        TLMDCheckBox *cbOrgLogicY;
        TLMDCheckBox *cbOrgLogicZ;
        TLMDCheckBox *cbOrgLogicT;
        TLMDComboBox *combHomeModeX;
        TLMDComboBox *combHomeModeY;
        TLMDComboBox *combHomeModeZ;
        TLMDComboBox *combHomeModeT;
        TLMDEdit *edLowDistanceX;
        TLMDEdit *edLowDistanceY;
        TLMDEdit *edLowDistanceT;
        TLMDEdit *edLowDistanceZ;
        TLMDTabSheet *tsMotionStatus;
        TLabel *Label221;
        TLMDGroupBox *LMDGroupBox10;
        TLabel *Label107;
        TLabel *Label106;
        TLabel *Label105;
        TLabel *Label104;
        TLabel *Label103;
        TLabel *Label102;
        TLabel *Label101;
        TLabel *Label100;
        TLabel *Label99;
        TLabel *Label96;
        TLabel *Label95;
        TLabel *Label94;
        TLabel *Label85;
        TLabel *Label84;
        TLabel *Label6;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label22;
        TLabel *Label83;
        TPanel *pnlRDYX;
        TPanel *pnlALMX;
        TPanel *pnlPELX;
        TPanel *pnlNELX;
        TPanel *pnlORGX;
        TPanel *pnlDIRX;
        TPanel *pnlReserved1X;
        TPanel *pnlPCSX;
        TPanel *pnlERCX;
        TPanel *pnlEZX;
        TPanel *pnlReserved2X;
        TPanel *pnlLatchX;
        TPanel *pnlSDX;
        TPanel *pnlINPX;
        TPanel *pnlSVONX;
        TPanel *pnlRDYY;
        TPanel *pnlALMY;
        TPanel *pnlPELY;
        TPanel *pnlNELY;
        TPanel *pnlORGY;
        TPanel *pnlDIRY;
        TPanel *pnlReserved1Y;
        TPanel *pnlPCSY;
        TPanel *pnlERCY;
        TPanel *pnlEZY;
        TPanel *pnlReserved2Y;
        TPanel *pnlLatchY;
        TPanel *pnlSDY;
        TPanel *pnlINPY;
        TPanel *pnlSVONY;
        TPanel *pnlRDYZ;
        TPanel *pnlALMZ;
        TPanel *pnlPELZ;
        TPanel *pnlNELZ;
        TPanel *pnlORGZ;
        TPanel *pnlDIRZ;
        TPanel *pnlReserved1Z;
        TPanel *pnlPCSZ;
        TPanel *pnlERCZ;
        TPanel *pnlEZZ;
        TPanel *pnlReserved2Z;
        TPanel *pnlLatchZ;
        TPanel *pnlSDZ;
        TPanel *pnlINPZ;
        TPanel *pnlSVONZ;
        TPanel *pnlRDYT;
        TPanel *pnlALMT;
        TPanel *pnlPELT;
        TPanel *pnlNELT;
        TPanel *pnlORGT;
        TPanel *pnlDIRT;
        TPanel *pnlReserved1T;
        TPanel *pnlPCST;
        TPanel *pnlERCT;
        TPanel *pnlEZT;
        TPanel *pnlReserved2T;
        TPanel *pnlLatchT;
        TPanel *pnlSDT;
        TPanel *pnlINPT;
        TPanel *pnlSVONT;
        TLMDTabSheet *tsDI;
        TLabel *Label63;
        TLabel *Label97;
        TLabel *Label122;
        TLabel *Label196;
        TLabel *Label468;
        TPanel *pnlBit0;
        TPanel *pnlBit1;
        TPanel *pnlBit2;
        TPanel *pnlBit3;
        TLMDTabSheet *tsDO;
        TLabel *Label272;
        TGroupBox *GroupBox3;
        TLabel *Label290;
        TLabel *Label291;
        TLabel *Label292;
        TLMDButton *btnUserNew;
        TLMDButton *btnUserDelete;
        TLMDButton *btnUserRefresh;
        TStringGrid *sgUser;
        TLMDEdit *edUserName;
        TLMDEdit *edUserPassword;
        TPanel *Panel50;
        TImage *Image7;
        TMemo *mmHelp;
        TGroupBox *gbSystemCommand;
        TPanel *Panel65;
        TLMDButton *btnPassword;
        TGroupBox *gbSubstrate;
        TComboBox *cbOperator;
        TComboBox *cbType;
        TEdit *edLotNo;
        TPanel *Panel29;
        TPanel *pnlGrade;
        TPanel *pnlLotNoTilte;
        TPanel *pnlRecipe;
        TComboBox *cbRecipe;
        TPanel *Panel39;
        TEdit *edBoxNo;
        TLMDRadioGroup *rgLevel;
        TPanel *pnlRecipeLabel;
        TComboBox *combRecipe;
        TTimer *tmTMove;
        TPanel *Panel63;
        TButton *btnUpdateMotion;
        TPanel *Panel69;
        TButton *btnUpdateRecipe;
        TPanel *pnlRecipeMessage;
        TPanel *pnlError;
        TLabel *Label471;
        TPanel *Panel70;
        TLMDButton *btnManualOk;
        TImageList *ilBiSS;
        TTable *tblData;
        TTable *tblHD;
        TLabel *Label87;
        TPanel *pnlMotionZero;
        TLabel *laMotionZero;
        TPanel *Panel47;
        TPanel *pnlPassword;
        TPanel *Panel49;
        TLMDButton *btnLog;
        TLabel *Label111;
        TLabel *Label112;
        TLMDEdit *edLogName;
        TMaskEdit *medCurrentPassword;
        TPanel *pnlLeftWindow;
        TImage *imCCD;
        TShape *shLeftPosition;
        TShape *shRightPosition;
        TShape *shUpPosition;
        TShape *shDownPosition;
        TShape *shVertical;
        TShape *shHorizontalUp1;
        TShape *shHorizontalDown1;
        TShape *shRightDown;
        TShape *shDown;
        TShape *shLeftDown;
        TShape *shLeft;
        TShape *shLeftUp;
        TShape *shUp;
        TShape *shRightUp;
        TShape *shRight;
        TShape *shCenter;
        TShape *shMarkMatch;
        TLabel *Label1;
        TLabel *Label3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label198;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label15;
        TLabel *Label98;
        TLabel *Label144;
        TLabel *Label145;
        TLabel *Label472;
        TPanel *pnlBit4;
        TPanel *pnlBit5;
        TPanel *pnlBit6;
        TPanel *pnlBit7;
        TPanel *pnlBit8;
        TPanel *pnlBit9;
        TPanel *pnlBit10;
        TPanel *pnlBit11;
        TPanel *pnlBit12;
        TPanel *pnlBit13;
        TPanel *pnlBit14;
        TPanel *pnlBit15;
        TPanel *pnlSystemMessage;
        TLMDGroupBox *LMDGroupBox13;
        TLabel *Label203;
        TLabel *Label205;
        TLabel *Label209;
        TLabel *Label206;
        TLMDRadioGroup *rgRulerColor;
        TLMDCheckBox *cbRuler;
        TBitBtn *btnReviewLive;
        TBitBtn *btnReviewGrab;
        TBitBtn *btnReviewLoad;
        TBitBtn *btnReviewSave;
        TPanel *pnlCCDX;
        TPanel *pnlCCDY;
        TPanel *pnlCCDR;
        TPanel *pnlCCDG;
        TPanel *pnlCCDB;
        TPanel *pnlCCDStatus;
        TPanel *pnlCapturedNo;
        TLabel *Label336;
        TPanel *pnlCaptureTime;
        TLabel *Label333;
        TPanel *pnlCCDSize;
        TSavePictureDialog *spCCDImage;
        TOpenPictureDialog *opCCDImage;
        TPanel *pnlOperation;
        TLMDTabSheet *tsPosition;
        TLMDGroupBox *LMDGroupBox2;
        TLabel *Label18;
        TLabel *laY1;
        TLabel *Label28;
        TLMDEdit *edTiltX;
        TLMDEdit *edTiltY;
        TLMDButton *btnTiltPosition;
        TLMDButton *btnToTiltPosition;
        TLMDEdit *edTiltZ;
        TPanel *pnlToTiltPosition;
        TLabel *Label30;
        TLMDEdit *edTiltW;
        TTimer *tmMotionPolling;
        TPanel *pnlAxisError;
        TPanel *pnlDO;
        TPanel *pnlDI;
        TPanel *pnlDOValue;
        TTimer *tmBeep;
        TPanel *pnlDIOStatus;
        TLabel *Label50;
        TPanel *pnlDoorOpen;
        TPanel *pnlStageLock;
        TLabel *Label51;
        TPanel *pnlStageVacuum;
        TLabel *Label53;
        TPanel *pnlStageBar;
        TLabel *laOrangeLamp;
        TPanel *pnlDOMaintenanceLight;
        TLabel *laGreenLamp;
        TPanel *pnlDOCDA;
        TLabel *laDOCDA;
        TPanel *pnlDOEFEMFFU;
        TLabel *Label65;
        TPanel *pnlDOStageFFU;
        TLabel *Label66;
        TPanel *pnlStageVacuum1;
        TLabel *Label67;
        TPanel *pnlDOReserved8;
        TLabel *Label68;
        TPanel *pnlDOReserved9;
        TLabel *Label73;
        TPanel *pnlDOPolarizer;
        TLabel *Label74;
        TPanel *pnlDORedLamp;
        TLabel *Label75;
        TPanel *pnlDOYellowLamp;
        TLabel *Label76;
        TPanel *pnlDOGreenLamp;
        TLabel *Label77;
        TPanel *pnlDOBlueLamp;
        TLabel *Label79;
        TPanel *pnlDOBuzzer;
        TLabel *Label80;
        TLMDTabSheet *tsAI;
        TLabel *Label55;
        TLabel *Label57;
        TPanel *pnlAI1Value;
        TPanel *pnlAI2Value;
        TPanel *pnlAI1Low;
        TPanel *pnlAI1High;
        TPanel *pnlAI2Low;
        TPanel *pnlAI2High;
        TLMDProgress *pgAI1;
        TLMDProgress *pgAI2;
        TTimer *tm500ms;
        TLabel *Label86;
        TLabel *Label92;
        TLabel *Label93;
        TLMDGroupBox *LMDGroupBox3;
        TLabel *Label108;
        TLabel *laY2;
        TLabel *Label110;
        TLabel *Label113;
        TLMDEdit *edZeroX;
        TLMDEdit *edZeroY;
        TLMDButton *btnZeroPosition;
        TLMDButton *btnToZeroPosition;
        TLMDEdit *edZeroZ;
        TPanel *pnlToZeroPosition;
        TLMDEdit *edZeroW;
        TLMDTabSheet *tsCCD;
        TLMDGroupBox *LMDGroupBox4;
        TLabel *Label117;
        TLabel *laOrigin;
        TLabel *Label119;
        TLabel *Label120;
        TLMDEdit *edLoadX;
        TLMDEdit *edLoadY;
        TLMDButton *btnLoadPosition;
        TLMDButton *btnToLoadPosition;
        TLMDEdit *edLoadZ;
        TPanel *pnlToLoadPosition;
        TLMDEdit *edLoadW;
        TLabel *Label127;
        TLMDEdit *edMinVibrate;
        TLMDTabSheet *tsMove;
        TGroupBox *GroupBox15;
        TLabel *Label435;
        TLabel *Label229;
        TLabel *Label230;
        TLabel *Label16;
        TLabel *Label116;
        TEdit *edCCDPrecision1;
        TPanel *pnlYAltOffset;
        TLMDCheckBox *cbCCDYDirection;
        TPanel *pnlYMove;
        TPanel *pnlXAltOffset;
        TLMDCheckBox *cbCCDXDirection;
        TPanel *pnlXMove;
        TPanel *pnlTAltOffset;
        TPanel *pnlTMove;
        TLMDCheckBox *cbCCDTDirection;
        TEdit *edCCDPrecision2;
        TEdit *edCCDPrecision3;
        TEdit *edCCDPrecision4;
        TEdit *edCCDPrecision5;
        TShape *shHorizontalUp2;
        TShape *shHorizontalUp4;
        TShape *shHorizontalUp3;
        TShape *shHorizontalUp8;
        TShape *shHorizontalUp7;
        TShape *shHorizontalUp6;
        TShape *shHorizontalUp5;
        TShape *shHorizontalUp16;
        TShape *shHorizontalUp15;
        TShape *shHorizontalUp14;
        TShape *shHorizontalUp13;
        TShape *shHorizontalUp12;
        TShape *shHorizontalUp11;
        TShape *shHorizontalUp10;
        TShape *shHorizontalUp9;
        TShape *shHorizontalDown16;
        TShape *shHorizontalDown14;
        TShape *shHorizontalDown15;
        TShape *shHorizontalDown10;
        TShape *shHorizontalDown11;
        TShape *shHorizontalDown12;
        TShape *shHorizontalDown13;
        TShape *shHorizontalDown2;
        TShape *shHorizontalDown3;
        TShape *shHorizontalDown4;
        TShape *shHorizontalDown5;
        TShape *shHorizontalDown6;
        TShape *shHorizontalDown7;
        TShape *shHorizontalDown8;
        TShape *shHorizontalDown9;
        TShape *shCenter1;
        TShape *shCenter8;
        TShape *shCenter5;
        TShape *shCenter4;
        TShape *shCenter2;
        TShape *shCenter3;
        TShape *shCenter7;
        TShape *shCenter6;
        TPanel *pnlAlarmMessage;
        TShape *shVerticalLeft1;
        TShape *shVerticalLeft2;
        TShape *shVerticalLeft4;
        TShape *shVerticalLeft3;
        TShape *shVerticalLeft8;
        TShape *shVerticalLeft7;
        TShape *shVerticalLeft6;
        TShape *shVerticalLeft5;
        TShape *shVerticalLeft16;
        TShape *shVerticalLeft15;
        TShape *shVerticalLeft14;
        TShape *shVerticalLeft13;
        TShape *shVerticalLeft12;
        TShape *shVerticalLeft11;
        TShape *shVerticalLeft10;
        TShape *shVerticalLeft9;
        TShape *shVerticalRight1;
        TShape *shVerticalRight2;
        TShape *shVerticalRight3;
        TShape *shVerticalRight4;
        TShape *shVerticalRight5;
        TShape *shVerticalRight6;
        TShape *shVerticalRight7;
        TShape *shVerticalRight8;
        TShape *shVerticalRight9;
        TShape *shVerticalRight10;
        TShape *shVerticalRight11;
        TShape *shVerticalRight12;
        TShape *shVerticalRight13;
        TShape *shVerticalRight14;
        TShape *shVerticalRight15;
        TShape *shVerticalRight16;
        TLabel *Label129;
        TLMDEdit *edGridPixel;
        TLabel *laCCDPrecision1;
        TLabel *laCCDPrecision2;
        TLabel *laCCDPrecision3;
        TLabel *laCCDPrecision4;
        TLabel *laCCDPrecision5;
        TLMDButton *btnReset;
        TLMDGroupBox *LMDGroupBox11;
        TLabel *Label167;
        TLabel *Label168;
        TLabel *Label169;
        TLabel *Label170;
        TLMDEdit *edLastX;
        TLMDEdit *edLastY;
        TLMDButton *btnLastPosition;
        TLMDButton *btnToLastPosition;
        TLMDEdit *edLastZ;
        TPanel *pnlToLastPosition;
        TLMDEdit *edLastW;
        TEdit *edCCDPrecision6;
        TLabel *laCCDPrecision6;
        TLMDPageControl *pcOP;
        TLMDTabSheet *tsPosittionMove;
        TLMDTabSheet *tsArrayDieMove;
        TLMDGroupBox *gbArrayOperation;
        TLMDButton *btnArrayLeft;
        TLMDButton *btnArrayRight;
        TLMDButton *btnArrayUp;
        TLMDButton *btnArrayDown;
        TLMDGroupBox *gbDieOperation;
        TLMDButton *btnDieLeft;
        TLMDButton *btnDieRight;
        TLMDButton *btnDieUp;
        TLMDButton *btnDieDown;
        TLMDTabSheet *tsMatch;
        TLMDTabSheet *tsMark;
        TLMDRadioGroup *rgRulerType;
        TLMDGroupBox *LMDGroupBox5;
        TLabel *Label173;
        TLMDEdit *edPos1X;
        TLMDEdit *edPos1Y;
        TLMDButton *btnPos1Set;
        TLMDEdit *edPos1Z;
        TLMDEdit *edPos1T;
        TLMDGroupBox *LMDGroupBox6;
        TLabel *Label175;
        TLMDEdit *edPos2X;
        TLMDEdit *edPos2Y;
        TLMDButton *btnPos2Set;
        TLMDEdit *edPos2Z;
        TLMDEdit *edPos2T;
        TLMDGroupBox *LMDGroupBox16;
        TLabel *Label177;
        TLMDEdit *edPos3X;
        TLMDEdit *edPos3Y;
        TLMDButton *btnPos3Set;
        TLMDEdit *edPos3Z;
        TLMDEdit *edPos3T;
        TLMDGroupBox *LMDGroupBox17;
        TLabel *Label179;
        TLMDEdit *edPos4X;
        TLMDEdit *edPos4Y;
        TLMDButton *btnPos4Set;
        TLMDEdit *edPos4Z;
        TLMDEdit *edPos4T;
        TLMDGroupBox *LMDGroupBox18;
        TLabel *Label181;
        TLMDEdit *edPos5X;
        TLMDEdit *edPos5Y;
        TLMDButton *btnPos5Set;
        TLMDEdit *edPos5Z;
        TLMDEdit *edPos5T;
        TLMDButton *btnPositionSave;
        TPanel *pnlPositionGo;
        TLMDButton *btnPos1Go;
        TLMDButton *btnPos2Go;
        TLMDButton *btnPos3Go;
        TLMDButton *btnPos4Go;
        TLMDButton *btnPos5Go;
        TLMDTabSheet *tsHome;
        TLMDButton *btnUpdateSystemParameter;
        TPanel *pnlWidthValue;
        TPanel *Panel1;
        TButton *btnHome1;
        TPanel *pnlAllHomeStatus1;
        TPanel *pnlHome2;
        TPanel *pnlX;
        TPanel *pnlY;
        TPanel *pnlZ;
        TPanel *pnlT;
        TLabel *Label182;
        TPanel *pnlMoveTop;
        TPanel *pnlMoveBottom;
        TPanel *pnlMoveLeft;
        TPanel *pnlMoveRight;
        TShape *shLaserShutterOuter;
        TShape *shLaserShutterInner;
        TImage *Image1;
        TImage *Image2;
        TPanel *pnlZUnit;
        TLMDRadioGroup *rgRulerColor1;
        TGroupBox *GroupBox14;
        TLabel *Label231;
        TLabel *Label232;
        TLabel *Label234;
        TLabel *laFirst;
        TLabel *laSecond;
        TPanel *pnlTRemoteOffset;
        TPanel *pnlTRemoteDegree;
        TPanel *pnlRemoteLeft;
        TPanel *pnlRemoteRight;
        TLMDButton *btnRemoteRotate;
        TLMDCheckBox *cbRotateDirection;
        TLMDCheckBox *cbDirectMove;
        TPanel *pnlRemoteRotate;
        TPanel *pnlTSystemStartVel;
        TPanel *pnlTSystemMaxVel;
        TPanel *pnlTSystemDistance;
        TLMDCheckBox *cbAngularHorizontal;
        TLMDGroupBox *gbArray1Operation;
        TLMDButton *btnArray1Left;
        TLMDButton *btnArray1Right;
        TLMDButton *btnArray1Up;
        TLMDButton *btnArray1Down;
        TLMDGroupBox *gbArray2Operation;
        TLMDButton *btnArray2Left;
        TLMDButton *btnArray2Right;
        TLMDButton *btnArray2Up;
        TLMDButton *btnArray2Down;
        TOpenDialog *odPointMove;
        TPanel *pnlAssignResult;
        TTimer *tm400ms;
        TLMDButton *btnHome2;
        TLMDTabSheet *tsLens;
        TLMDGroupBox *LMDGroupBox27;
        TLabel *Label213;
        TLabel *Label214;
        TLabel *Label215;
        TLabel *Label216;
        TLMDEdit *edLens1X;
        TLMDButton *btnSetLens1Position;
        TLMDButton *btnToLens1Position;
        TPanel *pnlToLens1Position;
        TLMDEdit *edLens2X;
        TLMDEdit *edLens3X;
        TLMDEdit *edLens4X;
        TLMDEdit *edLens5X;
        TLMDEdit *edLens6X;
        TLMDEdit *edLens1Y;
        TLMDEdit *edLens2Y;
        TLMDEdit *edLens3Y;
        TLMDEdit *edLens4Y;
        TLMDEdit *edLens5Y;
        TLMDEdit *edLens6Y;
        TLMDEdit *edLens1Z;
        TLMDEdit *edLens2Z;
        TLMDEdit *edLens3Z;
        TLMDEdit *edLens4Z;
        TLMDEdit *edLens5Z;
        TLMDEdit *edLens6Z;
        TLMDEdit *edLens1T;
        TLMDEdit *edLens2T;
        TLMDEdit *edLens3T;
        TLMDEdit *edLens4T;
        TLMDEdit *edLens5T;
        TLMDEdit *edLens6T;
        TLMDButton *btnSetLens2Position;
        TLMDButton *btnToLens2Position;
        TPanel *pnlToLens2Position;
        TLMDButton *btnSetLens3Position;
        TLMDButton *btnToLens3Position;
        TPanel *pnlToLens3Position;
        TLMDButton *btnSetLens4Position;
        TLMDButton *btnToLens4Position;
        TPanel *pnlToLens4Position;
        TLMDButton *btnSetLens5Position;
        TLMDButton *btnToLens5Position;
        TPanel *pnlToLens5Position;
        TLMDButton *btnSetLens6Position;
        TLMDButton *btnToLens6Position;
        TPanel *pnlToLens6Position;
        TLMDButton *btnSaveLensPosition;
        TPanel *pnlSaveLensPosition;
        TLabel *Label243;
        TLMDEdit *edLens1ZLimit;
        TLMDEdit *edLens2ZLimit;
        TLMDEdit *edLens3ZLimit;
        TLMDEdit *edLens4ZLimit;
        TLMDEdit *edLens5ZLimit;
        TLMDEdit *edLens6ZLimit;
        TLMDButton *btnSetLens1ZLimit;
        TLMDButton *btnSetLens2ZLimit;
        TLMDButton *btnSetLens3ZLimit;
        TLMDButton *btnSetLens4ZLimit;
        TLMDButton *btnSetLens5ZLimit;
        TLMDButton *btnSetLens6ZLimit;
        TPanel *pnlLens1LED;
        TPanel *pnlLens2LED;
        TPanel *pnlLens3LED;
        TPanel *pnlLens4LED;
        TPanel *pnlLens5LED;
        TPanel *pnlLens6LED;
        TShape *shMeasure;
        TLMDCheckBox *cbMeasure;
        TLMDCheckBox *cbCrossHair;
        TLMDCheckBox *cbUnitMove;
        TPanel *pnlLaserCenterPosition1;
        TLMDButton *btnAbortWithin;
        TShape *Shape2;
        TTimer *tm250ms;
        TLabel *Label286;
        TPanel *pnlYShift;
        TPanel *pnlMessage;
        TPanel *pnlClip;
        TICImagingControl *ICImagingControl1;
        TTimer *tmISCCD;
        TPanel *pnlISCCDInfo;
        TShape *shCircle;
        TShape *shEllipse;
        TShape *shPoint1;
        TShape *shPoint2;
        TShape *shPoint3;
        TLMDButton *btnDeleteRecipe;
        TPanel *Panel10;
        TShape *shDirRightTop;
        TRadioGroup *rgBaslerShutter;
        TGroupBox *GroupBox35;
        TLabel *Label329;
        TLabel *Label330;
        TLabel *Label331;
        TTrackBar *tbBaslerGain;
        TPanel *pnlBaslerGain;
        TShape *shPointSet1;
        TPanel *pnlPointSet1;
        TPanel *pnlPositionLength;
        TLMDGroupBox *LMDGroupBox22;
        TPanel *pnlXFactor;
        TLMDEdit *edXStd;
        TLMDEdit *edXValue;
        TLabel *Label245;
        TLabel *Label246;
        TLabel *Label247;
        TLabel *Label248;
        TLMDEdit *edYValue;
        TLMDEdit *edYStd;
        TPanel *pnlYFactor;
        TLMDButton *btnCalibrationSave;
        TLMDButton *btnCalibrationDone;
        TShape *shPointSet2;
        TPanel *pnlPointSet2;
        TShape *shPointSet3;
        TPanel *pnlPointSet3;
        TShape *shPointSet4;
        TPanel *pnlPointSet4;
        TShape *shPointSet5;
        TPanel *pnlPointSet5;
        TShape *shCircleCenter1;
        TShape *shLineSet1;
        TPanel *pnlLineSet1;
        TShape *shLineSet2;
        TPanel *pnlLineSet2;
        TShape *shCirclePoint1;
        TPanel *pnlCircleCenter1;
        TPanel *pnlCirclePoint1;
        TGroupBox *GroupBox1;
        TLabel *Label241;
        TLabel *Label249;
        TLabel *Label257;
        TTrackBar *tbContrast;
        TPanel *pnlContrast;
        TShape *shCircleCenter2;
        TShape *shCirclePoint2;
        TPanel *pnlCircleCenter2;
        TPanel *pnlCirclePoint2;
        TLabel *Label132;
        TPanel *pnlLensPrecision;
        TPanel *pnlUnit;
        TMemo *mmMeasure;
        TPanel *pnlPoint1;
        TPanel *pnlPoint2;
        TPanel *pnlPoint3;
        TPanel *Panel44;
        TLMDRadioGroup *rgSpeed;
        TPanel *pnlCurrentSpeed;
        TPanel *pnlMove;
        TLabel *Label263;
        TLMDEdit *edTempCalibration;
        TLabel *Label264;
        TLMDEdit *edTempSurface;
        TLabel *Label265;
        TLMDEdit *edHeatFactor;
        TLabel *Label266;
        TShape *shCircleMark1;
        TShape *shCircleMark2;
        TListBox *lbGiga;
        TPanel *Panel4;
        TPopupMenu *pmMemo;
        TMenuItem *mnClear;
        TMenuItem *mnSaveFile;
        TLMDGroupBox *gbSpeedSetting;
        TLabel *Label270;
        TLabel *Label271;
        TLabel *Label273;
        TLabel *Label274;
        TLMDEdit *edSpeedGeneralLow;
        TLMDEdit *edSpeedGeneralMiddle;
        TLMDEdit *edSpeedGeneralHigh;
        TLMDButton *btnSpeedUpdate;
        TLabel *Label275;
        TLMDEdit *edSpeedTurboLow;
        TLMDEdit *edSpeedTurboMiddle;
        TLMDEdit *edSpeedTurboHigh;
        TLabel *Label276;
        TLMDEdit *edSpeedZLow;
        TLMDEdit *edSpeedZMiddle;
        TLMDEdit *edSpeedZHigh;
        TLMDGroupBox *LMDGroupBox31;
        TLabel *Label282;
        TLabel *Label283;
        TLabel *Label284;
        TLabel *Label285;
        TPanel *Panel55;
        TLMDButton *btnSaveLED2;
        TPanel *pnlLED2CH1;
        TPanel *pnlLampControl2;
        TCheckBox *cbLampControl2;
        TButton *btnLampControl2;
        TLMDTrackBar *tbLED2CH1;
        TLMDTrackBar *tbLED2CH2;
        TPanel *pnlLED2CH2;
        TLMDTrackBar *tbLED2CH3;
        TPanel *pnlLED2CH3;
        TLMDTrackBar *tbLED2CH4;
        TPanel *pnlLED2CH4;
        TPanel *Panel20;
        TPanel *Panel51;
        TPanel *Panel54;
        TYbCommDevice *ybLampControl2;
        TLMDTabSheet *tsOlympus;
        TLMDGroupBox *gbOlympus;
        TLabel *Label317;
        TEdit *edYuanliPort;
        TComboBox *comboOlympusVisionName;
        TPanel *Panel62;
        TPanel *pnlYuanliMessage;
        TLMDButton *btnYuanliConnect;
        TPanel *pnlOlympusStatus;
        TLMDGroupBox *rgCCDPosition;
        TLabel *Label294;
        TLabel *Label297;
        TLabel *Label298;
        TLabel *Label299;
        TLMDEdit *edCCDX;
        TLMDEdit *edCCDY;
        TLMDButton *btnCCDPosition;
        TLMDButton *btnToCCDPosition;
        TLMDEdit *edCCDZ;
        TPanel *pnlToCCDPosition;
        TLMDEdit *edCCDW;
        TPopupMenu *pmLensSwitch;
        TMenuItem *mnToLens;
        TMenuItem *mnToLens1;
        TMenuItem *mnToLens2;
        TMenuItem *mnToLens3;
        TMenuItem *mnToLens4;
        TMenuItem *mnToCCD;
        TLabel *Label302;
        TPanel *pnlOlympusLensPrecision;
        TLMDTabSheet *tsRun;
        TPanel *pnlAreaNoRun;
        TPanel *pnlDotNoRun;
        TPanel *pnlSystemRun;
        TPanel *Panel67;
        TPanel *pnlRunRecipe;
        TPanel *pnlRunAreaTNo;
        TPanel *pnlRunDotTNo;
        TBitBtn *btnStopMotion;
        TLabel *Label313;
        TLMDGroupBox *LMDGroupBox9;
        TLabel *Label130;
        TLabel *Label131;
        TLMDEdit *edJogFactor;
        TLMDEdit *edContinueFactor;
        TLabel *Label318;
        TLMDEdit *edRunLoop;
        TLMDButton *btnRunStop;
        TPanel *pnlRunDoneNo;
        TPanel *pnlElapsedTime;
        TPanel *pnlTableX;
        TLabel *Label134;
        TLabel *Label319;
        TPanel *pnlTableY;
        TLMDCheckBox *cbContinueMove;
        TLabel *Label41;
        TPanel *pnlISCCDStaus;
        TPanel *pnlISCCDCapture;
        TLabel *laAOI;
        TLMDEdit *edTiltT;
        TLabel *laLoad;
        TLMDEdit *edZeroT;
        TLabel *laOriginal;
        TLMDEdit *edLoadT;
        TLabel *Label325;
        TLMDEdit *edLastT;
        TLabel *Label326;
        TLMDEdit *edCCDT;
        TPanel *Panel72;
        TPanel *pnlRunDatabase;
        TLabel *Label293;
        TBitBtn *btnToOriginal;
        TBitBtn *btnToInput;
        TLMDTabSheet *tsOLS5000;
        TLMDButton *btnFindFocus;
        TPanel *pnlAutoFocus1;
        TCheckBox *cbCalibration;
        TLMDButton *btnVacuum;
        TLabel *Label328;
        TPanel *pnlOffsetXBase;
        TPanel *pnlOffsetYBase;
        TLabel *Label332;
        TLabel *Label334;
        TPanel *pnlRotate;
        TCheckBox *cbAutoFocus;
        TLabel *Label335;
        TLabel *Label337;
        TLabel *Label338;
        TPanel *pnlOffsetXArea;
        TPanel *pnlOffsetYArea;
        TLabel *Label339;
        TOpenDialog *opkmfFile;
        TCheckBox *cbkmfDirection;
        TPanel *pnlRecipeTypeRecipe;
        TLMDPageControl *pcRecipe;
        TLMDTabSheet *tsReadkfm;
        TLabel *Label347;
        TLabel *Label348;
        TLabel *Label349;
        TLabel *Label350;
        TLabel *Label352;
        TLMDRadioGroup *rgkmfUnit;
        TLMDGroupBox *LMDGroupBox32;
        TLabel *Label340;
        TLabel *Label341;
        TLMDEdit *edkmfX;
        TLMDEdit *edkmfY;
        TLMDButton *btnkmfPosition;
        TLMDButton *btnTokmfPosition;
        TPanel *pnlToTXTPosition;
        TPanel *Panel75;
        TEdit *edkmfPath;
        TPanel *pnlkmfFile;
        TEdit *edkmfFilename;
        TStringGrid *sgkmf;
        TLMDButton *btnReadkmf;
        TPanel *pnlReadkmf;
        TPanel *pnlkmfX;
        TPanel *pnlkmfY;
        TPanel *pnlkmfNo;
        TLMDButton *btnTokmf;
        TPanel *pnlTokmf;
        TPanel *pnlkmfTypeName;
        TPanel *pnlkmfTNo;
        TLMDButton *btnSetkmf;
        TLMDButton *btnSavekmfParameter;
        TLMDTabSheet *tsRecipeSetting;
        TLMDGroupBox *LMDGroupBox38;
        TLabel *Label314;
        TLabel *Label316;
        TStringGrid *sgArea;
        TStringGrid *sgDot;
        TGroupBox *GroupBox2;
        TLabel *Label17;
        TPanel *pnlScore;
        TLMDEdit *edMinScore;
        TLMDButton *btnAutoMatch;
        TPanel *pnlNCC;
        TCheckBox *cbStdPattern;
        TLMDButton *btnEraseMatchBox;
        TLMDRadioGroup *rgMatchSource;
        TLMDButton *btnSavePattern;
        TCheckBox *cbMoveToCenterMatched;
        TComboBox *comboPattern;
        TLMDButton *btnAssignPattern;
        TPanel *pnlAreaX;
        TPanel *pnlAreaY;
        TPanel *pnlDotX;
        TPanel *pnlDotY;
        TPanel *pnlDotZ;
        TPanel *pnlAreaZ;
        TPanel *pnlDotIntensity;
        TPanel *pnlDotRow;
        TPanel *pnlDotCol;
        TLMDTabSheet *LMDTabSheet5;
        TLMDGroupBox *LMDGroupBox12;
        TLabel *Label36;
        TLabel *Label38;
        TLabel *Label39;
        TLabel *Label40;
        TLabel *Label31;
        TLabel *Label35;
        TLMDEdit *edArrayWidthRecipe;
        TLMDEdit *edArrayHeightRecipe;
        TLMDEdit *edDieWidthRecipe;
        TLMDEdit *edDieHeightRecipe;
        TLMDEdit *edArray1WidthRecipe;
        TLMDEdit *edArray1HeightRecipe;
        TLMDEdit *edArray2WidthRecipe;
        TLMDEdit *edArray2HeightRecipe;
        TPanel *Panel2;
        TComboBox *combSizeRecipe;
        TLMDButton *btnDotSelect;
        TLMDButton *btnDotApply;
        TPanel *pnlDotSelect;
        TLMDCheckBox *cbSpeedUp;
        TLMDButton *btnDisplayResult;
        TLMDButton *btnMatchToCenter;
        TTimer *tmJoystick;
        TTimer *tmTrigger;
        TPanel *pnlJX;
        TPanel *pnlJY;
        TPanel *pnlJZ;
        TLabel *Label312;
        TLMDRadioGroup *rgkmfDirection;
        TLMDGroupBox *LMDGroupBox39;
        TLabel *Label354;
        TLMDEdit *edPos6X;
        TLMDEdit *edPos6Y;
        TLMDButton *btnPos6Set;
        TLMDEdit *edPos6Z;
        TLMDEdit *edPos6T;
        TLMDButton *btnPos6Go;
        TLMDGroupBox *LMDGroupBox40;
        TLabel *Label355;
        TLMDEdit *edPos7X;
        TLMDEdit *edPos7Y;
        TLMDButton *btnPos7Set;
        TLMDEdit *edPos7Z;
        TLMDEdit *edPos7T;
        TLMDButton *btnPos7Go;
        TLMDGroupBox *LMDGroupBox41;
        TLabel *Label356;
        TLMDEdit *edPos8X;
        TLMDEdit *edPos8Y;
        TLMDButton *btnPos8Set;
        TLMDEdit *edPos8Z;
        TLMDEdit *edPos8T;
        TLMDButton *btnPos8Go;
        TLMDGroupBox *LMDGroupBox42;
        TLabel *Label357;
        TLMDEdit *edPos9X;
        TLMDEdit *edPos9Y;
        TLMDButton *btnPos9Set;
        TLMDEdit *edPos9Z;
        TLMDEdit *edPos9T;
        TLMDButton *btnPos9Go;
        TLMDGroupBox *LMDGroupBox43;
        TLabel *Label358;
        TLMDEdit *edPos10X;
        TLMDEdit *edPos10Y;
        TLMDButton *btnPos10Set;
        TLMDEdit *edPos10Z;
        TLMDEdit *edPos10T;
        TLMDButton *btnPos10Go;
        TLMDGroupBox *gbRelativeBase;
        TLabel *Label359;
        TLMDEdit *edMoveBaseX;
        TLMDEdit *edMoveBaseY;
        TLMDButton *btnMoveBaseMove;
        TLabel *Label360;
        TPanel *pnlMoveBaseX;
        TPanel *pnlMoveBaseY;
        TLMDButton *btnMoveBaseSet;
        TLMDButton *btnMoveBaseGo;
        TPanel *pnlToMoveBasePosition;
        TLabel *Label361;
        TLabel *Label362;
        TLabel *Label363;
        TLMDTabSheet *tsJoystick;
        TLabel *Label365;
        TLabel *Label369;
        TLabel *Label370;
        TLabel *Label371;
        TLabel *Label372;
        TPanel *pnlJoystick1;
        TPanel *pnlJoystick2;
        TPanel *pnlJoystick3;
        TPanel *pnlJoystick4;
        TPanel *pnlJoystick5;
        TLabel *Label373;
        TLabel *Label374;
        TLabel *Label375;
        TLabel *Label376;
        TLabel *Label377;
        TPanel *pnlJoystick6;
        TPanel *pnlJoystick7;
        TPanel *pnlJoystick8;
        TPanel *pnlJoystick9;
        TPanel *pnlJoystick10;
        TLabel *Label378;
        TPanel *pnlJoystickX;
        TLabel *Label379;
        TPanel *pnlJoystickY;
        TLabel *Label380;
        TPanel *pnlJoystickZ;
        TLabel *Label381;
        TLabel *Label382;
        TPanel *pnlJoystickLeft;
        TPanel *pnlJoystickRight;
        TPanel *pnlMoveBaseMove;
        TLMDRadioGroup *rgJoystickSpeed;
        TTimer *tmX;
        TTimer *tmY;
        TTimer *tmZ;
        TLMDGroupBox *LMDGroupBox46;
        TLabel *Label383;
        TLabel *Label384;
        TLMDEdit *edJoystickStart;
        TLMDEdit *edJoystickStop;
        TLMDButton *btnJoystickSave;
        TLMDCheckBox *cbAISpeed;
        TLMDGroupBox *LMDGroupBox47;
        TLabel *Label385;
        TLMDEdit *edAISpeedStart;
        TLMDButton *btnJoystickSaveAI;
        TLabel *Label386;
        TLMDEdit *edAISpeedChange;
        TLMDTabSheet *tsSafe;
        TPanel *Panel76;
        TLMDButton *btnFrontOut;
        TLMDButton *btnFrontIn;
        TLMDButton *btnRearIn;
        TLMDButton *btnRearOut;
        TLMDButton *btnLeftOut;
        TLMDButton *btnLeftIn;
        TLMDButton *btnRightIn;
        TLMDButton *btnRightOut;
        TPanel *pnlSpeed;
        TPanel *pnlFrontOut;
        TPanel *pnlFrontIn;
        TPanel *pnlRearIn;
        TPanel *pnlRearOut;
        TPanel *pnlLeftOut;
        TPanel *pnlLeftIn;
        TPanel *pnlRightIn;
        TPanel *pnlRightOut;
        TLMDButton *btnSafeSave;
        TButton *btnSvon;
        TCheckBox *cbSafeCalibration;
        TPanel *Panel77;
        TShape *shHorizontal;
        TBitBtn *btnToCenter;
        TLMDButton *btnEFEMMaintenanceMode;
        TPanel *pnlEFEMMaintenanceMode;
        TYbCommDevice *ybRobot;
        TGroupBox *GroupBox4;
        TLabel *Label416;
        TLabel *Label417;
        TLabel *Label418;
        TLabel *Label419;
        TLabel *Label420;
        TLabel *Label424;
        TPanel *pnlRobotReady;
        TPanel *pnlAlignerReady;
        TPanel *pnlLoadPortReady;
        TPanel *pnlEFEMKey;
        TPanel *pnlEFEMLeftDoor;
        TPanel *pnlEFEMRightDoor;
        TPanel *pnlEFEMCassette;
        TPanel *pnlMoving;
        TYbCommDevice *ybAligner;
        TYbCommDevice *ybLoadPort;
        TLabel *Label483;
        TPanel *pnlSystemPower;
        TLabel *Label484;
        TPanel *pnlSystemCDA;
        TLabel *Label485;
        TPanel *pnlSystemVacuum;
        TTimer *tmLoadUnload;
        TPanel *Panel78;
        TLabel *Label441;
        TPanel *pnlEFEMReady;
        TTimer *tmSetupEFEM;
        TPanel *pnlRobotErrorCode1;
        TPanel *pnlLoadPortErrorCode1;
        TPanel *pnlAlignerErrorCode1;
        TShape *Shape1;
        TShape *Shape3;
        TPanel *pnlAlignerErrorMsg;
        TPanel *pnlLoadPortErrorMsg;
        TPanel *pnlRobotErrorMsg;
        TTimer *tmBuzzer;
        TLMDRadioGroup *rgMaintenanceMode;
        TLMDCheckBox *cbMaintenanceMode;
        TLMDButton *btnMaintenanceLight;
        TPanel *pnlMaintenanceLight;
        TTimer *tmAlignerStas;
        TTimer *tmLFup;
        TTimer *tmLFDown;
        TTimer *tmAlignerORG;
        TPanel *pnlPattern;
        TImage *imPattern;
        TLMDGroupBox *gbMatchData;
        TStringGrid *sgResult;
        TPanel *pnlMatchDataClose;
        TPanel *pnlMatchError;
        TLMDButton *btnReMatch;
        TLMDButton *btnExitMatch;
        TPanel *pnlMatchErrorMsg;
        TPanel *pnlToLast;
        TLabel *laLast;
        TPanel *Panel13;
        TLMDButton *btnToLastYes;
        TLMDButton *btnToLastNo;
        TBitBtn *btnSaveImage;
        TShape *shMotionStatus;
        TLabel *Label26;
        TPanel *pnlCardNo;
        TLabel *Label34;
        TLMDCheckBox *cbJoystick;
        TLMDRadioGroup *rgAllHomeMethod;
        TPanel *pnlVendorTitle;
        TComboBox *cbProduct;
        TPanel *Panel71;
        TComboBox *cbMode;
        TPanel *Panel36;
        TEdit *edGlassID;
        TPanel *Panel32;
        TComboBox *cbSpec;
        TLMDGroupBox *gbSetting;
        TLMDButton *btnAlarmOn;
        TLMDButton *btnAlarmOff;
        TLMDButton *btnServoOn;
        TLMDButton *btnServoOff;
        TLMDButton *btnDOOn;
        TLMDButton *btnDOOff;
        TLMDRadioGroup *rgCCDSelect;
        TLMDButton *btnSystemRun;
        TLMDTabSheet *tsRorzeEFEM;
        TPageControl *pcEFEMR;
        TTabSheet *tsAligner;
        TPanel *pnlRorzeAligner;
        TLabel *Label12;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label27;
        TLabel *Label29;
        TPanel *Panel5;
        TPanel *Panel8;
        TButton *btnAlignerINIT;
        TPanel *pnlAlignerSocketConnect;
        TMemo *mmAligner;
        TButton *btnRorzeAlignerORGN;
        TButton *btnAlignerALGN;
        TButton *btnAlignerCLMP;
        TButton *btnAlignerUCLM;
        TButton *btnAlignerSTAT;
        TButton *btnAlignerSend;
        TEdit *edAlignerCommand;
        TButton *btnAlignerRSTA;
        TButton *btnAlignerSTOP;
        TButton *btnAlignerzHome;
        TButton *btnAlignerSSIZ;
        TButton *btnAlignerDo;
        TPanel *pnlAlignerDo;
        TPanel *Panel11;
        TPanel *pnlAlignerSend;
        TRadioGroup *rgWaferSize;
        TRadioGroup *rgWaferDegree;
        TPanel *pnlAlignerReady1;
        TPanel *pnlAlignerADSensor;
        TButton *btnAlignerGTAD;
        TPanel *pnlAlignerORGN1;
        TPanel *pnlAlignerCancelCode;
        TButton *btnInput;
        TPanel *pnlInput;
        TTabSheet *tsRobot;
        TPanel *pnlRorzeRobot;
        TLabel *Label33;
        TLabel *Label37;
        TLabel *Label43;
        TPanel *Panel16;
        TPanel *Panel17;
        TPanel *pnlRobotSocketConnect;
        TMemo *mmRobot;
        TButton *btnRobotORGN;
        TButton *btnRobotSTAT;
        TButton *btnRobotSend;
        TEdit *edRobotCommand;
        TButton *btnRobotRSTA;
        TButton *btnRobotHOME;
        TButton *btnRorzeRobotGet;
        TPanel *pnlRorzeRobotGet;
        TPanel *Panel19;
        TCheckBox *cbRobotActive;
        TPanel *pnlRobotSend;
        TButton *btnRobotToHome;
        TPanel *pnlRobotToHomeStatus;
        TPanel *pnlRobotORGNStatus;
        TPanel *Panel22;
        TPanel *pnlRobotErrorMessage;
        TPanel *pnlRobotReceive;
        TPanel *pnlOperationResult;
        TRadioGroup *rgRobotArm;
        TRadioGroup *rgRobotStage;
        TButton *btnRobotStageHome;
        TRadioGroup *rgRobotOperation;
        TComboBox *combRobotSlot;
        TButton *btnRorzeRobotPut;
        TPanel *pnlRorzeRobotPut;
        TRadioGroup *rgRobotSpeed;
        TTabSheet *tsLoadPort1;
        TPanel *pnlLoadPort1;
        TLabel *Label44;
        TLabel *Label64;
        TLabel *Label78;
        TLabel *Label81;
        TLabel *Label88;
        TLabel *Label89;
        TLabel *Label135;
        TLabel *Label136;
        TPanel *Panel24;
        TPanel *Panel25;
        TButton *btnLoadPort1UNLD;
        TPanel *pnlLoadPort1SocketConnect;
        TMemo *mmLoadPort1;
        TButton *btnLoadPort1ORGN;
        TButton *btnLoadPort1LOAD;
        TButton *btnLoadPort1CLMP;
        TButton *btnLoadPort1UCLM;
        TButton *btnLoadPort1STAT;
        TButton *btnLoadPort1Send;
        TEdit *edLoadPort1Command;
        TButton *btnLoadPort1RSTA;
        TButton *btnLoadPort1MODE;
        TPanel *Panel27;
        TPanel *pnlLoadPort1Send;
        TRadioGroup *rgLoadPort1Mode;
        TPanel *pnlLoadPort1Ready;
        TPanel *pnlLoadPort1ORGN;
        TPanel *pnlLoadPort1CancelCode;
        TPanel *pnlLoadPort1Presence;
        TPanel *pnlLoadPort1Placement;
        TPanel *pnlLoadPort1Load;
        TPanel *pnlLoadPort1Manual;
        TPanel *pnlLoadPort1Dock;
        TCheckBox *cbLoadPort1E84;
        TPanel *pnlLoadPort1Unload;
        TPanel *pnlLoadPort1Alarm;
        TPanel *pnlLoadPort1Clamp;
        TButton *btnLoadPort1INIT;
        TButton *btnLoadPort1WMAP;
        TButton *btnLoadPort1GMAP;
        TPanel *pnlLoadPort1CLMP;
        TPanel *pnlLoadPort1UCLM;
        TPanel *pnlLoadPort1WMAP;
        TRadioGroup *rgLoadPort1WaferSize;
        TButton *btnLoadPort1GPIO;
        TTabSheet *tsLoadPort2;
        TPanel *pnlLoadPort2;
        TLabel *Label146;
        TLabel *Label147;
        TLabel *Label148;
        TLabel *Label149;
        TLabel *Label150;
        TLabel *Label151;
        TLabel *Label152;
        TLabel *Label155;
        TPanel *Panel30;
        TButton *btnLoadPort2UNLD;
        TPanel *pnlLoadPort2SocketConnect;
        TButton *btnLoadPort2ORGN;
        TButton *btnLoadPort2LOAD;
        TButton *btnLoadPort2CLMP;
        TButton *btnLoadPort2UCLM;
        TButton *btnLoadPort2STAT;
        TButton *btnLoadPort2Send;
        TEdit *edLoadPort2Command;
        TButton *btnLoadPort2RSTA;
        TPanel *pnlLoadPort2Send;
        TPanel *pnlLoadPort2Ready;
        TPanel *pnlLoadPort2ORGN;
        TButton *btnLoadPort2INIT;
        TButton *btnLoadPort2WMAP;
        TButton *btnLoadPort2GMAP;
        TPanel *Panel34;
        TMemo *mmLoadPort2;
        TButton *btnLoadPort2MODE;
        TPanel *Panel37;
        TRadioGroup *rgLoadPort2Mode;
        TPanel *pnlLoadPort2CancelCode;
        TPanel *pnlLoadPort2Load;
        TPanel *pnlLoadPort2Dock;
        TCheckBox *cbLoadPort2E84;
        TPanel *pnlLoadPort2Unload;
        TPanel *pnlLoadPort2Clamp;
        TRadioGroup *rgLoadPort2WaferSize;
        TPanel *pnlLoadPort2Presence;
        TPanel *pnlLoadPort2Manual;
        TPanel *pnlLoadPort2Alarm;
        TPanel *pnlLoadPort2Placement;
        TPanel *pnlLoadPort2CLMP;
        TPanel *pnlLoadPort2UCLM;
        TPanel *pnlLoadPort2WMAP;
        TButton *btnLoadPort2GPIO;
        TTabSheet *tsRFID;
        TPanel *pnlRFID;
        TButton *btnRFIDSend;
        TPanel *pnlRFID18;
        TPanel *pnlRFID112;
        TPanel *pnlRFID28;
        TPanel *pnlRFID212;
        TEdit *edRFIDCommand;
        TRadioGroup *rgRFIDLoadPort;
        TRadioGroup *rgRFIDWaferSize;
        TButton *btnRFIDRead;
        TButton *btnRFIDSerialNumber;
        TMemo *mmRFID;
        TPanel *pnlCSTCode;
        TPanel *pnlRFIDResult;
        TComboBox *combRFIDComport;
        TComboBox *combRFIDBaudrate;
        TButton *btnRFIDInit;
        TButton *btnRFIDTest;
        TEdit *edRFIDTest;
        TRadioGroup *rgRFIDTagType;
        TLMDTabSheet *tsSECSGEM;
        TLMDTabSheet *tsHirataEFEM;
        TLMDPageControl *pcEFEMH;
        TLMDTabSheet *tsCommand;
        TPanel *pnlRobot;
        TPanel *pnlRobotStatus;
        TComboBox *combRobotComport;
        TComboBox *combRobotBaudrate;
        TPanel *Panel94;
        TPanel *Panel95;
        TPanel *pnlRobotSN;
        TPanel *pnlRobotMessage;
        TPanel *Panel98;
        TLMDButton *btnRobotConnect;
        TEdit *edRobotCmd;
        TLMDButton *btnRobotCMD;
        TMemo *mmRobotMsg;
        TLMDButton *btnRobotOriginal;
        TPanel *pnlRobotOriginal;
        TLMDButton *btnRobotPos;
        TEdit *edRobotPos;
        TPanel *pnlRobotPos;
        TCheckBox *cbRobot;
        TLMDButton *btnRobotStas;
        TPanel *pnlRobotOperation;
        TPanel *pnlRobotErrorCode;
        TLMDButton *btnRobotVacuumOn;
        TLMDButton *btnRobotVacuumOff;
        TLMDButton *btnRobotWithWafer;
        TPanel *pnlRobotWithWafer;
        TLMDButton *btnRobotGetPosition;
        TPanel *pnlRobotXPosition;
        TLMDButton *btnRobotClearAlarm;
        TLMDButton *btnRobotEanble;
        TLMDButton *btnRobotDisable;
        TPanel *Panel81;
        TLMDRadioGroup *rgWaferLocation;
        TLMDButton *btnRobotGet;
        TPanel *pnlRobotGet;
        TLMDButton *btnRobotPut;
        TPanel *pnlRobotPut;
        TComboBox *combRobotTrayNo;
        TPanel *pnlLoadPort;
        TPanel *pnlLoadPortStatus;
        TComboBox *combLoadPortComport;
        TComboBox *combLoadPortBaudrate;
        TPanel *Panel89;
        TPanel *Panel90;
        TPanel *pnlLoadPortSN;
        TPanel *pnlLoadPortMessage;
        TPanel *Panel93;
        TLMDButton *btnLoadPortConnect;
        TMemo *mmLoadPortMsg;
        TLMDButton *btnLoadPortMap;
        TLMDButton *btnLoadPortLoad;
        TLMDButton *btnLoadPortUnLoad;
        TPanel *pnlLoadPortPresence;
        TPanel *Panel104;
        TPanel *Panel106;
        TPanel *pnlLoadPortPlacement;
        TPanel *pnlLoadPortStatus1;
        TPanel *Panel109;
        TPanel *Panel110;
        TPanel *pnlLoadPortStatus2;
        TPanel *pnlLoadPortKWF;
        TPanel *Panel113;
        TPanel *Panel114;
        TPanel *pnlLoadPortLoad;
        TPanel *pnlLoadPortUnLoad;
        TPanel *Panel117;
        TPanel *Panel118;
        TPanel *pnlLoadPortAlarm;
        TPanel *Panel120;
        TPanel *pnlLoadPortPower;
        TLMDButton *btnLoadPortCMD;
        TEdit *edLoadPortCmd;
        TPanel *pnlLoadPortOperation;
        TPanel *pnlLoadPortErrorCode;
        TLMDButton *btnLoadPortStas;
        TLMDButton *btnLoadPortLED;
        TPanel *pnlLoadPortInterLockCode;
        TLMDButton *btnLoadPortMapping;
        TLMDButton *btnLoadPortReset;
        TPanel *pnlLoadPortReset;
        TPanel *pnlAligner;
        TLabel *Label463;
        TLabel *Label474;
        TLabel *Label475;
        TPanel *pnlAlignerStatus;
        TComboBox *combAlignerComport;
        TComboBox *combAlignerBaudrate;
        TPanel *Panel101;
        TPanel *Panel102;
        TPanel *pnlAlignerSN;
        TPanel *pnlAlignerMessage;
        TPanel *Panel105;
        TLMDButton *btnAlignerConnect;
        TLMDRadioGroup *rgAlignerSet;
        TEdit *edAlignerDegree;
        TPanel *Panel86;
        TPanel *Panel88;
        TEdit *edAlignerSpeed;
        TPanel *Panel91;
        TEdit *edAlignerType;
        TLMDButton *btnAlignerSet;
        TLMDButton *btnAlignerGet;
        TMemo *mmAlignerMsg;
        TLMDButton *btnAlignerCMD;
        TEdit *edAlignerCmd;
        TLMDButton *btnAlignerORGN;
        TLMDButton *btnAlignerAlignment;
        TLMDButton *btnAlignerVacuumOff;
        TPanel *pnlAlignerOperation;
        TPanel *pnlAlignerErrorCode;
        TLMDButton *btnAlignerStas;
        TPanel *pnlAlignerWithWafer;
        TLMDButton *btnAlignerWithWafer;
        TPanel *pnlAlignerORGN;
        TPanel *pnlAlignerAlignment;
        TPanel *pnlAlignerVacuumOff;
        TLMDButton *btnAlignerReset;
        TPanel *pnlAlignerReset;
        TLMDButton *btnAlignerSave;
        TEdit *edAlignerDegreeOut;
        TLMDButton *btnRobotEnable;
        TLMDButton *btnLoadPortEnable;
        TLMDButton *btnAlignerEnable;
        TLMDTabSheet *tsRobotStatus;
        TLMDGroupBox *LMDGroupBox21;
        TLabel *Label392;
        TLabel *Label396;
        TLabel *Label397;
        TLabel *Label398;
        TLabel *Label399;
        TLabel *Label400;
        TLabel *Label401;
        TLabel *Label402;
        TLabel *Label403;
        TLabel *Label404;
        TLabel *Label405;
        TLabel *Label406;
        TLabel *Label407;
        TLabel *Label408;
        TLabel *Label409;
        TLabel *Label410;
        TLabel *Label19;
        TLabel *Label109;
        TLabel *Label118;
        TLabel *Label425;
        TLabel *Label426;
        TLabel *Label427;
        TLabel *Label428;
        TLabel *Label429;
        TLabel *Label430;
        TLabel *Label431;
        TLabel *Label432;
        TLabel *Label433;
        TLabel *Label434;
        TLabel *Label436;
        TLabel *Label437;
        TLabel *Label438;
        TLabel *Label442;
        TPanel *pnlRobotS10;
        TPanel *pnlRobotS11;
        TPanel *pnlRobotS12;
        TPanel *pnlRobotS13;
        TPanel *pnlRobotS14;
        TPanel *pnlRobotS15;
        TPanel *pnlRobotS16;
        TPanel *pnlRobotS17;
        TPanel *pnlRobotS20;
        TPanel *pnlRobotS21;
        TPanel *pnlRobotS22;
        TPanel *pnlRobotS23;
        TPanel *pnlRobotS24;
        TPanel *pnlRobotS25;
        TPanel *pnlRobotS26;
        TPanel *pnlRobotS27;
        TPanel *pnlRobotS30;
        TPanel *pnlRobotS31;
        TPanel *pnlRobotS32;
        TPanel *pnlRobotS33;
        TPanel *pnlRobotS34;
        TPanel *pnlRobotS35;
        TPanel *pnlRobotS36;
        TPanel *pnlRobotS37;
        TPanel *pnlRobotS40;
        TPanel *pnlRobotS41;
        TPanel *pnlRobotS42;
        TPanel *pnlRobotS43;
        TPanel *pnlRobotS44;
        TPanel *pnlRobotS45;
        TPanel *pnlRobotS46;
        TPanel *pnlRobotS47;
        TLMDGroupBox *LMDGroupBox44;
        TLabel *Label439;
        TLabel *Label440;
        TLabel *Label443;
        TLabel *Label476;
        TLabel *Label477;
        TLabel *Label478;
        TLabel *Label479;
        TLabel *Label480;
        TLabel *Label481;
        TPanel *pnlRobotE1;
        TPanel *pnlRobotE2;
        TPanel *pnlRobotAX;
        TPanel *pnlRobotAY;
        TPanel *pnlRobotAZ;
        TPanel *pnlRobotAW;
        TPanel *pnlRobotAR;
        TPanel *pnlRobotAC;
        TLMDTabSheet *tsLoadPortStatus;
        TLabel *Label491;
        TLMDPageControl *LMDPageControl1;
        TLMDTabSheet *LMDTabSheet1;
        TLMDGroupBox *LMDGroupBox36;
        TLabel *Label412;
        TLabel *Label413;
        TLabel *Label414;
        TLabel *Label444;
        TLabel *Label445;
        TLabel *Label446;
        TLabel *Label447;
        TLabel *Label448;
        TLabel *Label449;
        TLabel *Label450;
        TLabel *Label451;
        TLabel *Label452;
        TLabel *Label453;
        TLabel *Label454;
        TLabel *Label455;
        TLabel *Label456;
        TLabel *Label457;
        TLabel *Label458;
        TLabel *Label459;
        TLabel *Label460;
        TLabel *Label488;
        TPanel *pnlLoadPortS1;
        TPanel *pnlLoadPortS2;
        TPanel *pnlLoadPortS3;
        TPanel *pnlLoadPortS4;
        TPanel *pnlLoadPortS5;
        TPanel *pnlLoadPortS6;
        TPanel *pnlLoadPortS7;
        TPanel *pnlLoadPortS8;
        TPanel *pnlLoadPortS9;
        TPanel *pnlLoadPortS10;
        TPanel *pnlLoadPortS11;
        TPanel *pnlLoadPortS12;
        TPanel *pnlLoadPortS13;
        TPanel *pnlLoadPortS14;
        TPanel *pnlLoadPortS15;
        TPanel *pnlLoadPortS16;
        TPanel *pnlLoadPortS17;
        TPanel *pnlLoadPortS18;
        TPanel *pnlLoadPortS19;
        TPanel *pnlLoadPortS20;
        TLMDTabSheet *LMDTabSheet3;
        TLabel *Label496;
        TLMDTabSheet *tsAlignerStatus;
        TLabel *Label490;
        TLabel *Label492;
        TLabel *Label493;
        TLabel *Label494;
        TLabel *Label495;
        TLabel *Label499;
        TLMDGroupBox *LMDGroupBox45;
        TLabel *Label461;
        TLabel *Label462;
        TLabel *Label464;
        TLabel *Label465;
        TLabel *Label466;
        TLabel *Label467;
        TLabel *Label469;
        TLabel *Label470;
        TLabel *Label473;
        TLabel *Label482;
        TPanel *pnlAlignerS1;
        TPanel *pnlAlignerS2;
        TPanel *pnlAlignerS3;
        TPanel *pnlAlignerS4;
        TPanel *pnlAlignerS5;
        TPanel *pnlAlignerS6;
        TPanel *pnlAlignerS7;
        TPanel *pnlAlignerS8;
        TPanel *pnlAlignerS9;
        TPanel *pnlAlignerS10;
        TPanel *Panel79;
        TPanel *Panel80;
        TLMDTabSheet *tsErrorLog;
        TMemo *mmLog;
        TLMDButton *LMDButton2;
        TLMDTabSheet *tsHelp1;
        TMemo *mmSystemHelp;
        TLMDTabSheet *tsOperation;
        TLMDRadioGroup *rgWaferNo;
        TLMDButton *btnLoad;
        TLMDButton *btnLoadWafer;
        TLMDButton *btnUnloadWafer;
        TPanel *pnlLoadWafer;
        TPanel *pnlUnloadWafer;
        TPanel *pnlLoad;
        TPanel *pnlOperationMessage;
        TLMDButton *btnReStart;
        TPanel *pnlLoadPort1Title;
        TPanel *pnlLoadPort1Status;
        TLabel *Label156;
        TLabel *Label157;
        TLabel *Label158;
        TLabel *Label159;
        TLabel *Label160;
        TLabel *Label161;
        TLabel *Label162;
        TLabel *Label163;
        TLabel *Label164;
        TLabel *Label165;
        TLabel *Label166;
        TLabel *Label176;
        TLabel *Label178;
        TLabel *Label180;
        TLabel *Label183;
        TLabel *Label184;
        TLabel *Label187;
        TLabel *Label197;
        TLabel *Label217;
        TLabel *Label218;
        TLabel *Label220;
        TLabel *Label222;
        TLabel *Label223;
        TLabel *Label224;
        TLabel *Label228;
        TPanel *Panel40;
        TPanel *pnlLoadPort1Tray25;
        TPanel *pnlLoadPort1Tray24;
        TPanel *pnlLoadPort1Tray23;
        TPanel *pnlLoadPort1Tray22;
        TPanel *pnlLoadPort1Tray21;
        TPanel *pnlLoadPort1Tray20;
        TPanel *pnlLoadPort1Tray19;
        TPanel *pnlLoadPort1Tray18;
        TPanel *pnlLoadPort1Tray17;
        TPanel *pnlLoadPort1Tray16;
        TPanel *pnlLoadPort1Tray15;
        TPanel *pnlLoadPort1Tray14;
        TPanel *pnlLoadPort1Tray13;
        TPanel *pnlLoadPort1Tray12;
        TPanel *pnlLoadPort1Tray11;
        TPanel *pnlLoadPort1Tray10;
        TPanel *pnlLoadPort1Tray9;
        TPanel *pnlLoadPort1Tray8;
        TPanel *pnlLoadPort1Tray7;
        TPanel *pnlLoadPort1Tray6;
        TPanel *pnlLoadPort1Tray5;
        TPanel *pnlLoadPort1Tray4;
        TPanel *pnlLoadPort1Tray3;
        TPanel *pnlLoadPort1Tray2;
        TPanel *pnlLoadPort1Tray1;
        TPanel *pnlLoadPort1Tray1Select;
        TPanel *pnlLoadPort1Tray2Select;
        TPanel *pnlLoadPort1Tray3Select;
        TPanel *pnlLoadPort1Tray4Select;
        TPanel *pnlLoadPort1Tray5Select;
        TPanel *pnlLoadPort1Tray6Select;
        TPanel *pnlLoadPort1Tray7Select;
        TPanel *pnlLoadPort1Tray8Select;
        TPanel *pnlLoadPort1Tray9Select;
        TPanel *pnlLoadPort1Tray10Select;
        TPanel *pnlLoadPort1Tray11Select;
        TPanel *pnlLoadPort1Tray12Select;
        TPanel *pnlLoadPort1Tray13Select;
        TPanel *pnlLoadPort1Tray14Select;
        TPanel *pnlLoadPort1Tray15Select;
        TPanel *pnlLoadPort1Tray16Select;
        TPanel *pnlLoadPort1Tray17Select;
        TPanel *pnlLoadPort1Tray18Select;
        TPanel *pnlLoadPort1Tray19Select;
        TPanel *pnlLoadPort1Tray20Select;
        TPanel *pnlLoadPort1Tray21Select;
        TPanel *pnlLoadPort1Tray22Select;
        TPanel *pnlLoadPort1Tray23Select;
        TPanel *pnlLoadPort1Tray24Select;
        TPanel *pnlLoadPort1Tray25Select;
        TPanel *Panel41;
        TLMDButton *btnLoadPort1AllSelect;
        TPanel *pnlLoadPort2Title;
        TPanel *pnlLoadPort2Status;
        TLabel *Label233;
        TLabel *Label235;
        TLabel *Label236;
        TLabel *Label237;
        TLabel *Label238;
        TLabel *Label239;
        TLabel *Label240;
        TLabel *Label242;
        TLabel *Label244;
        TLabel *Label256;
        TLabel *Label260;
        TLabel *Label261;
        TLabel *Label269;
        TLabel *Label277;
        TLabel *Label278;
        TLabel *Label287;
        TLabel *Label288;
        TLabel *Label289;
        TLabel *Label295;
        TLabel *Label296;
        TLabel *Label300;
        TLabel *Label301;
        TLabel *Label387;
        TLabel *Label388;
        TLabel *Label390;
        TPanel *Panel42;
        TPanel *pnlLoadPort2Tray25;
        TPanel *pnlLoadPort2Tray24;
        TPanel *pnlLoadPort2Tray23;
        TPanel *pnlLoadPort2Tray22;
        TPanel *pnlLoadPort2Tray21;
        TPanel *pnlLoadPort2Tray20;
        TPanel *pnlLoadPort2Tray19;
        TPanel *pnlLoadPort2Tray18;
        TPanel *pnlLoadPort2Tray17;
        TPanel *pnlLoadPort2Tray16;
        TPanel *pnlLoadPort2Tray15;
        TPanel *pnlLoadPort2Tray14;
        TPanel *pnlLoadPort2Tray13;
        TPanel *pnlLoadPort2Tray12;
        TPanel *pnlLoadPort2Tray11;
        TPanel *pnlLoadPort2Tray10;
        TPanel *pnlLoadPort2Tray9;
        TPanel *pnlLoadPort2Tray8;
        TPanel *pnlLoadPort2Tray7;
        TPanel *pnlLoadPort2Tray6;
        TPanel *pnlLoadPort2Tray5;
        TPanel *pnlLoadPort2Tray4;
        TPanel *pnlLoadPort2Tray3;
        TPanel *pnlLoadPort2Tray2;
        TPanel *pnlLoadPort2Tray1;
        TPanel *pnlLoadPort2Tray1Select;
        TPanel *pnlLoadPort2Tray2Select;
        TPanel *pnlLoadPort2Tray3Select;
        TPanel *pnlLoadPort2Tray4Select;
        TPanel *pnlLoadPort2Tray5Select;
        TPanel *pnlLoadPort2Tray6Select;
        TPanel *pnlLoadPort2Tray7Select;
        TPanel *pnlLoadPort2Tray8Select;
        TPanel *pnlLoadPort2Tray9Select;
        TPanel *pnlLoadPort2Tray10Select;
        TPanel *pnlLoadPort2Tray11Select;
        TPanel *pnlLoadPort2Tray12Select;
        TPanel *pnlLoadPort2Tray13Select;
        TPanel *pnlLoadPort2Tray14Select;
        TPanel *pnlLoadPort2Tray15Select;
        TPanel *pnlLoadPort2Tray16Select;
        TPanel *pnlLoadPort2Tray17Select;
        TPanel *pnlLoadPort2Tray18Select;
        TPanel *pnlLoadPort2Tray19Select;
        TPanel *pnlLoadPort2Tray20Select;
        TPanel *pnlLoadPort2Tray21Select;
        TPanel *pnlLoadPort2Tray22Select;
        TPanel *pnlLoadPort2Tray23Select;
        TPanel *pnlLoadPort2Tray24Select;
        TPanel *pnlLoadPort2Tray25Select;
        TPanel *Panel43;
        TLMDButton *btnLoadPort2AllSelect;
        TClientSocket *csAlignerSocket;
        TClientSocket *csRobotSocket;
        TClientSocket *csLoadPort1Socket;
        TClientSocket *csLoadPort2Socket;
        TPopupMenu *pmAligner;
        TMenuItem *mnSaveAlignerToFile;
        TMenuItem *mnClearAlignerMessage;
        TMenuItem *MenuItem4;
        TPopupMenu *pmRobot;
        TMenuItem *mnSaveRobotToFile;
        TMenuItem *mnClearRobotMessage;
        TMenuItem *MenuItem7;
        TPopupMenu *pmLoadPort1;
        TMenuItem *mnSaveLoadProt1ToFile;
        TMenuItem *mnClearLoadPort1Message;
        TMenuItem *MenuItem10;
        TPopupMenu *pmLoadPort2;
        TMenuItem *mnSaveLoadProt2ToFile;
        TMenuItem *mnClearLoadPort2Message;
        TMenuItem *MenuItem13;
        TYbCommDevice *ybRFID212;
        TYbCommDevice *ybRFID28;
        TYbCommDevice *ybRFID112;
        TYbCommDevice *ybRFID18;
        TSaveDialog *sdAIMessages;
        TPanel *pnlOpeationMessage;
        TServerSocket *ssYuanliSocket;
        TPanel *pnlYuanli;
        TEdit *edYuanliCmd;
        TButton *btnYuanliSend;
        TPanel *pnlYuanliSend;
        TMemo *mmYuanli;
        TPanel *pnlAIMessage;
        TRadioGroup *rgYuanliCommandSet;
        TLabel *Label393;
        TLabel *Label394;
        TPanel *pnlErrorCode;
        TPanel *pnlSocketConnect;
        TRadioGroup *rgYuanliPoint;
        TLMDButton *btnCassetteLoad;
        TPanel *pnlCassetteLoad;
        TLMDRadioGroup *rgLoadPortSelect;
        TButton *btnRorzeEFEMSetup;
        TPanel *pnlLoadPortInterLockCode1;
        TPanel *pnlLoadPortInterLockMsg;
        TLabel *Label395;
        TPanel *pnlLoadPort2Ready1;
        TPanel *pnlLoadPort2ErrorCode1;
        TPanel *Panel46;
        TPanel *pnlJoystickActive;
        TPanel *pnlJoystickStatus;
        TLabel *Label423;
        TLMDEdit *edCommandL;
        TLMDEdit *edCounterL;
        TPanel *pnlStatusL;
        TLabel *Label500;
        TLMDEdit *edCommandW;
        TLMDEdit *edCounterW;
        TPanel *pnlStatusW;
        TLabel *Label501;
        TLMDEdit *edReviewVelL;
        TLMDEdit *edHomeVelL;
        TLMDEdit *edPositionL;
        TLMDEdit *edTdecL;
        TLMDEdit *edTaccL;
        TLMDEdit *edDistanceL;
        TLMDEdit *edMaxVelL;
        TLMDEdit *edStartVelL;
        TLMDEdit *edUpLimitL;
        TLMDCheckBox *cbOrgLogicL;
        TLMDComboBox *combHomeModeL;
        TLMDEdit *edLowDistanceL;
        TLabel *Label502;
        TLMDEdit *edReviewVelW;
        TLMDEdit *edHomeVelW;
        TLMDEdit *edPositionW;
        TLMDEdit *edTdecW;
        TLMDEdit *edTaccW;
        TLMDEdit *edDistanceW;
        TLMDEdit *edMaxVelW;
        TLMDEdit *edStartVelW;
        TLMDEdit *edUpLimitW;
        TLMDCheckBox *cbOrgLogicW;
        TLMDComboBox *combHomeModeW;
        TLMDEdit *edLowDistanceW;
        TLabel *Label503;
        TPanel *pnlRDYL;
        TPanel *pnlALML;
        TPanel *pnlPELL;
        TPanel *pnlNELL;
        TPanel *pnlORGL;
        TPanel *pnlDIRL;
        TPanel *pnlReserved1L;
        TPanel *pnlPCSL;
        TPanel *pnlERCL;
        TPanel *pnlEZL;
        TPanel *pnlReserved2L;
        TPanel *pnlLatchL;
        TPanel *pnlSDL;
        TPanel *pnlINPL;
        TPanel *pnlSVONL;
        TLabel *Label504;
        TPanel *pnlRDYW;
        TPanel *pnlALMW;
        TPanel *pnlPELW;
        TPanel *pnlNELW;
        TPanel *pnlORGW;
        TPanel *pnlDIRW;
        TPanel *pnlReserved1W;
        TPanel *pnlPCSW;
        TPanel *pnlERCW;
        TPanel *pnlEZW;
        TPanel *pnlReserved2W;
        TPanel *pnlLatchW;
        TPanel *pnlSDW;
        TPanel *pnlINPW;
        TPanel *pnlSVONW;
        TCheckBox *cbAIJoystick;
        TLabel *Label415;
        TPanel *pnlXYStageReady;
        TPanel *pnlMotionStatusL;
        TLMDEdit *edComparatorL;
        TPanel *pnlIOStatusL;
        TPanel *pnlMotionStatusW;
        TLMDEdit *edComparatorW;
        TPanel *pnlIOStatusW;
        TPanel *pnlRecipeSet;
        TLMDTabSheet *tsRX;
        TLMDGroupBox *LMDGroupBox1;
        TLabel *laCassette1;
        TLabel *laCassette2;
        TLabel *laCassette3;
        TLabel *laCassette4;
        TLMDEdit *edWPosition1;
        TLMDButton *btnSetWPosition1;
        TLMDButton *btnToWPosition1;
        TLMDButton *btnToWPosition2;
        TLMDButton *btnSetWPosition2;
        TLMDEdit *edWPosition2;
        TLMDButton *btnToWPosition3;
        TLMDButton *btnSetWPosition3;
        TLMDEdit *edWPosition3;
        TLMDButton *btnToWPosition4;
        TLMDButton *btnSetWPosition4;
        TLMDEdit *edWPosition4;
        TPanel *pnlToWStatus;
        TPanel *Panel344;
        TImage *Image3;
        TPanel *pnlToUserPosition;
        TPanel *pnlToLensPosition;
        TButton *btnSaveWPosition;
        TButton *btnAlignerSaveR;
        TLabel *Label322;
        TLMDButton *btnBackwardW;
        TLMDButton *btnMoveW;
        TPanel *Panel53;
        TImage *Image4;
        TImage *Image5;
        TPanel *Panel56;
        TImage *Image8;
        TImage *Image9;
        TImage *Image10;
        TLMDRadioGroup *rgJoystickEnabled;
        TPanel *Panel57;
        TImage *Image11;
        TImage *Image12;
        TImage *Image13;
        TImage *Image14;
        TImage *Image15;
        TImage *Image16;
        TPanel *Panel58;
        TLabel *Label508;
        TLabel *Label509;
        TLabel *Label510;
        TLabel *Label511;
        TLabel *Label421;
        TLMDButton *btnMeasure;
        TPanel *pnlMeasure;
        TPanel *pnlLineLength;
        TPanel *pnlMeasureResult;
        TPanel *pnlCassetteStatus;
        TPanel *Panel84;
        TPanel *pnlTray25;
        TPanel *pnlTray24;
        TPanel *pnlTray23;
        TPanel *pnlTray22;
        TPanel *pnlTray21;
        TPanel *pnlTray20;
        TPanel *pnlTray19;
        TPanel *pnlTray18;
        TPanel *pnlTray17;
        TPanel *pnlTray16;
        TPanel *pnlTray15;
        TPanel *pnlTray14;
        TPanel *pnlTray13;
        TPanel *pnlTray12;
        TPanel *pnlTray11;
        TPanel *pnlTray10;
        TPanel *pnlTray9;
        TPanel *pnlTray8;
        TPanel *pnlTray7;
        TPanel *pnlTray6;
        TPanel *pnlTray5;
        TPanel *pnlTray4;
        TPanel *pnlTray3;
        TPanel *pnlTray2;
        TPanel *pnlTray1;
        TPanel *pnlTray1Select;
        TPanel *pnlTray2Select;
        TPanel *pnlTray3Select;
        TPanel *pnlTray4Select;
        TPanel *pnlTray5Select;
        TPanel *pnlTray6Select;
        TPanel *pnlTray7Select;
        TPanel *pnlTray8Select;
        TPanel *pnlTray9Select;
        TPanel *pnlTray10Select;
        TPanel *pnlTray11Select;
        TPanel *pnlTray12Select;
        TPanel *pnlTray13Select;
        TPanel *pnlTray14Select;
        TPanel *pnlTray15Select;
        TPanel *pnlTray16Select;
        TPanel *pnlTray17Select;
        TPanel *pnlTray18Select;
        TPanel *pnlTray19Select;
        TPanel *pnlTray20Select;
        TPanel *pnlTray21Select;
        TPanel *pnlTray22Select;
        TPanel *pnlTray23Select;
        TPanel *pnlTray24Select;
        TPanel *pnlTray25Select;
        TPanel *Panel129;
        TLMDButton *btnAllSelect;
        TLabel *Label522;
        TLabel *Label537;
        TLabel *Label538;
        TLabel *Label539;
        TLabel *Label540;
        TLabel *Label541;
        TLabel *Label542;
        TLabel *Label543;
        TLabel *Label544;
        TLabel *Label545;
        TLabel *Label546;
        TLabel *Label547;
        TLabel *Label548;
        TLabel *Label549;
        TLabel *Label550;
        TLabel *Label551;
        TLabel *Label552;
        TLabel *Label553;
        TLabel *Label554;
        TLabel *Label555;
        TLabel *Label556;
        TLabel *Label557;
        TLabel *Label558;
        TLabel *Label559;
        TLabel *Label560;
        TLMDTabSheet *tsLiftPin;
        TLMDGroupBox *gbRobotCommand;
        TShape *Shape6;
        TButton *btnDemoLFUp;
        TButton *btnDemoLFDown;
        TButton *btnChuckVacuumOn;
        TButton *btnChuckVacuumOff;
        TButton *btnDemoLFVacuumOff;
        TLabel *Label389;
        TLabel *Label391;
        TLabel *Label489;
        TLabel *Label497;
        TLMDEdit *edLUp;
        TLMDEdit *edLDown;
        TLMDEdit *edLVacuumOff;
        TLMDEdit *edLLevel;
        TLabel *Label71;
        TLabel *Label323;
        TScrollBox *sbWaferMap;
        TImage *imWaferMap;
        TPanel *pnlAlignerWithWafer1;
        TLMDButton *btnAlignerGPIO;
        TLMDButton *btnRobotGPIO;
        TPanel *pnlRobotWithWaferUp;
        TPanel *pnlRobotWithWaferDown;
        TLMDButton *btnYunliReConnect;
        TRadioGroup *rgMode;
        TLabel *Label315;
        TEdit *edRecipeName;
        TEdit *edDelayTime;
        TLabel *Label521;
        TRadioGroup *rgCommand;
        TLabel *Label523;
        TLMDButton *btnSECSReConnect;
        TPanel *pnlSECSConnect;
        TEdit *edSECSPort;
        TLabel *Label524;
        TPanel *pnlSECS;
        TEdit *edSECSCmd;
        TButton *btnSECSSend;
        TPanel *pnlSECSSend;
        TMemo *mmSECS;
        TPanel *pnlSECSMessage;
        TPanel *Panel52;
        TPanel *pnlSocketReady;
        TClientSocket *csYuanliSocket;
        TLabel *Label526;
        TLMDButton *btnSECSConnect;
        TPanel *pnlSECSStatus;
        TLMDCheckBox *cbCCDFullImage;
        TServerSocket *ssSECSSocket;
//TClientSocket *csOLS5000;
        TRadioGroup *rgSECSCommand;
        TRadioGroup *rgSecsCommandSet;
        TPanel *pnlSECSAlarmCode;
        TLabel *Label364;
        TLabel *Label366;
        TEdit *edWaferID;
        TCheckBox *cbRobotStep;
        TTimer *tmLoadPort1ORGN;
        TTimer *tmLoadPort2ORGN;
        TTimer *tmAlignerORGN;
        TPanel *Panel3;
        TPanel *Panel12;
        TPanel *Panel14;
        TPanel *Panel15;
        TLMDGroupBox *LMDGroupBox14;
        TLabel *Label368;
        TLabel *Label525;
        TLabel *Label527;
        TLabel *Label528;
        TLabel *Label529;
        TLMDEdit *edRealCenterX;
        TLMDEdit *edRealCenterY;
        TLMDButton *btnRealCenterPosition;
        TLMDButton *btnToRealCenterPosition;
        TLMDEdit *edRealCenterZ;
        TPanel *pnlToRealCenterPosition;
        TLMDEdit *edRealCenterW;
        TLMDEdit *edRealCenterT;
        TLMDButton *btnFindCenter;
        TPanel *pnlFindCenter;
        TLMDTabSheet *tsSetCenter;
        TLMDGroupBox *gbArea;
        TLMDButton *btnSetLeft;
        TLMDButton *btnSetUp;
        TLMDButton *btnSetDown;
        TLMDButton *btnSetRight;
        TLMDButton *btnSetCenter;
        TLMDButton *btnToCenterPosition;
        TPanel *pnlToCenterPosition;
        TPanel *pnlCenterX;
        TPanel *pnlCenterY;
        TPanel *pnlYUp;
        TPanel *pnlYDown;
        TPanel *pnlXLeft;
        TPanel *pnlXRight;
        TShape *shVertEdge;
        TShape *shHorzEdge;
        TPanel *pnlCenterXFind;
        TPanel *pnlCenterYFind;
        TLMDButton *btnRorzeLoadPort1Enable;
        TLMDButton *btnRorzeLoadPort2Enable;
        TLMDButton *btnRorzeRobotEnable;
        TLMDButton *btnRorzeAlignerEnable;
        TLabel *Label530;
        TLabel *Label531;
        TLabel *Label532;
        TLabel *Label533;
        TPanel *pnlRobotStageHome;
        TEdit *edTotalPoint;
        TLabel *Label534;
        TLMDButton *btnBackwardZ1;
        TLMDButton *btnUp100x;
        TLMDButton *btnUp10x;
        TLMDButton *btnUp5x;
        TLMDButton *btnUp1x;
        TLMDButton *btnDown1x;
        TLMDButton *btnDown5x;
        TLMDButton *btnDown10x;
        TLMDButton *btnDown100x;
        TLMDButton *btnMoveZ1;
        TLMDButton *btnMoveY1;
        TLMDButton *btnRear10x;
        TLMDButton *btnRear5x;
        TLMDButton *btnRear1x;
        TLMDButton *btnFront1x;
        TLMDButton *btnFront5x;
        TLMDButton *btnFront10x;
        TLMDButton *btnBackwardY1;
        TLMDButton *btnBackwardX1;
        TLMDButton *btnLeft10x;
        TLMDButton *btnLeft5x;
        TLMDButton *btnLeft1x;
        TLMDButton *btnRight1x;
        TLMDButton *btnRight5x;
        TLMDButton *btnRight10x;
        TLMDButton *btnMoveX1;
        TLMDButton *btnMotionReset;
        TCheckBox *cbCenterStep;
        TLMDButton *btnFocusDone;
        TPanel *pnlToMeasurePosition;
        TLabel *Label535;
        TPopupMenu *pmWaferMapping;
        TMenuItem *mnSetMeasurePoint;
        TMenuItem *mnToMeasurePoint;
        TPanel *Panel18;
        TLabel *Label309;
        TLabel *Label310;
        TLabel *Label351;
        TLMDButton *btnBase1Set;
        TLMDButton *btnBase1To;
        TPanel *pnlBase1X;
        TPanel *pnlBase1Y;
        TPanel *pnlBase2X;
        TPanel *pnlBase2Y;
        TLMDButton *btnBase2Set;
        TLMDButton *btnBase2To;
        TPanel *pnlToBase1Position;
        TPanel *pnlToBase2Position;
        TPanel *pnlBase1Z;
        TPanel *pnlBase2Z;
        TLMDButton *btnMeasureStop;
        TLabel *Label565;
        TLabel *Label566;
        TLabel *Label90;
        TCheckBox *cbOffLine;
        TCheckBox *cbPCDoorRed;
        TCheckBox *cbPCDoorAlarm;
        TCheckBox *cbStageDoorAlarm;
        TCheckBox *cbStageDoorRed;
        TCheckBox *cbMaintenanceModeRed;
        TCheckBox *cbMaintenanceModeAlarm;
        TCheckBox *cbEFEMLeftDoorRed;
        TCheckBox *cbEFEMLeftDoorAlarm;
        TCheckBox *cbEFEMRightDoorRed;
        TCheckBox *cbEFEMRightDoorAlarm;
        TLMDButton *btnSaveAlarmParameter;
        TPanel *pnlTest;
        TPanel *pnlTestMessage;
        TLMDButton *btnTestClose;
        TLMDGroupBox *gbLoopTest;
        TLMDButton *btnLoopTest;
        TLMDButton *btnLoopTestStop;
        TEdit *edLoopTestCount;
        TPanel *pnlLoopTestCount;
        TLMDRadioGroup *rgLoopTest;
        TCheckBox *cbLoopPause;
        TCheckBox *cbPause;
        TPanel *pnlLoopTest;
        TLMDGroupBox *LMDGroupBox15;
        TLMDButton *btnRunTest;
        TPanel *pnlRunTest;
        TCheckBox *cbTestStep;
        TCheckBox *cbTwoWafer;
        TCheckBox *cbFastTest;
        TCheckBox *cbYuanliSimulate;
        TLabel *Label567;
        TLabel *Label568;
        TLabel *Label569;
        TLabel *Label570;
        TButton *btnSvon1;
        TPanel *pnlTestWaferCount;
        TLabel *Label571;
        TLabel *Label572;
        TLMDEdit *edWaferCenterSize;
        TLabel *Label573;
        TLMDEdit *edWaferCenterOffset;
        TButton *btnRobotCLMP;
        TPanel *pnlRobotCLMP;
        TButton *btnRobotUCLM;
        TPanel *pnlRobotUCLM;
        TLMDEdit *edWaferCenterCnt;
        TCheckBox *cbShareImage;
        TTimer *tmPinLiftUp;
        TTimer *tmPinLiftDown;
        TLMDCheckBox *cbTableDirection;
        TLabel *Label576;
        TLabel *Label577;
        TButton *btnLoadPort1Lock;
        TButton *btnLoadPort1Unlock;
        TButton *btnLoadPort1CarrierDock;
        TButton *btnLoadPort1CarrierUnDock;
        TCheckBox *cbLoadPort1GPIO;
        TPanel *pnlAlignerVacuum;
        TPanel *pnlAlignerVacuumValue;
        TLabel *Label578;
        TLabel *Label579;
        TButton *btnAlignerGPRS;
        TCheckBox *cbGPIOLog;
        TButton *btnAlignerCrash;
        TLMDButton *btnAllCancel;
        TTimer *tmAlatm;
        TButton *btnLoadPort2DPRM;
        TButton *btnLoadPort2Lock;
        TButton *btnLoadPort2Unlock;
        TButton *btnLoadPort2CarrierDock;
        TButton *btnLoadPort2CarrierUnDock;
        TCheckBox *cbLoadPort2GPIO;
        TPanel *pnlLoadPort2MinThickness;
        TPanel *pnlLoadPort2MaxThickness;
        TTimer *tmLP2DPRM;
        TTimer *tmLP1DPRM;
        TButton *btnLoadPort1DPRM;
        TPanel *pnlLoadPort1MinThickness;
        TPanel *pnlLoadPort1MaxThickness;
        TLMDTabSheet *tsWaferMap;
        TLabel *Label505;
        TLabel *Label512;
        TLabel *Label513;
        TLabel *Label514;
        TLabel *Label515;
        TLabel *Label516;
        TLabel *Label519;
        TRadioGroup *rgWaferDiameter;
        TEdit *edDieSizeX;
        TEdit *edDieSizeY;
        TRadioGroup *rgWaferNotchType;
        TRadioGroup *rgWaferOrientation;
        TPanel *pnlTestables;
        TPanel *pnlInkdies;
        TPanel *pnlSkipdies;
        TLMDButton *btnGenerateMap;
        TRadioGroup *rgWaferAxisOrientation;
        TPanel *pnlTotaldies;
        TEdit *edDieSizeGapX;
        TEdit *edDieSizeGapY;
        TPanel *pnlDieSetting;
        TImage *imWaferSize;
        TEdit *edDieWidth;
        TEdit *edDieGapX;
        TEdit *edDieHeight;
        TEdit *edDieGapY;
        TRadioGroup *rgWaferDieDirection;
        TCheckBox *cbWaferMap;
        TLMDTrackBar *tbZoom;
        TLMDButton *btnWaferCenter;
        TRadioGroup *rgWheelDirection;
        TLMDButton *btnWaferChip;
        TEdit *edWaferCol;
        TEdit *edWaferRow;
        TCheckBox *cbFontDisplay;
        TPanel *pnlCenterCol;
        TPanel *pnlCenterRow;
        TLMDButton *btnDotMap;
        TLMDButton *btnMapOutput;
        TLMDButton *btnMapAdjust;
        TCheckBox *cbMapAdjust;
        TLMDButton *btnWaferPosition;
        TEdit *edWaferPositionX;
        TEdit *edWaferPositionY;
        TLabel *Label580;
        TLabel *Label581;
        TLabel *Label582;
        TPanel *pnlWaferPositionCol;
        TPanel *pnlWaferPositionRow;
        TLMDGroupBox *gbWaferPosition;
        TLMDButton *btnWaferMoveLeft;
        TLMDButton *btnWaferMoveRight;
        TLMDButton *btnWaferMoveFront;
        TLMDButton *btnWaferMoveRear;
        TLMDButton *btnWaferPositinoY2;
        TPanel *Panel59;
        TLMDButton *btnWaferPositinoY1;
        TPanel *Panel23;
        TPanel *Panel48;
        TLMDButton *btnWaferPositinoX2;
        TLMDButton *btnWaferPositinoX1;
        TLMDButton *btnWaferMoveCenter;
        TPanel *pnlWaferPosition1X;
        TPanel *pnlWaferPosition2X;
        TPanel *pnlWaferPosition3X;
        TPanel *pnlWaferPosition4X;
        TLabel *Label584;
        TLabel *Label585;
        TLabel *Label586;
        TLabel *Label587;
        TPanel *pnlWaferDegreeX;
        TPanel *pnlWaferDegreeY;
        TLMDButton *btnWaferDegree;
        TLabel *Label588;
        TLabel *Label589;
        TPanel *pnlWaferPosition1Y;
        TPanel *pnlWaferPosition2Y;
        TPanel *pnlWaferPosition3Y;
        TPanel *pnlWaferPosition4Y;
        TLabel *Label590;
        TLabel *Label591;
        TCheckBox *cbAlignerActive;
        TCheckBox *cbLoadPort2Active;
        TCheckBox *cbLoadPort1Active;
        TLabel *Label583;
        TPanel *pnlWaferDieCenterX;
        TPanel *pnlWaferDieCenterY;
        TLabel *Label592;
        TLabel *Label593;
        TLMDButton *btnDieCenter;
        TCheckBox *cbWaferDefine;
        TLabel *Label594;
        TLabel *Label595;
        TComboBox *combDieNo;
        TLMDButton *btnToWaferCenter;
        TPanel *pnlFocusDone;
        TMainMenu *MainMenu1;
        TTimer *tmDecodeSECS;
        TTimer *tmDoLoadUnload;
        TTimer *tmAlignerToInPosition;
        TLMDEdit *edWaferEdgeGray;
        TLabel *Label596;
        TPanel *pnlDotNoRun1;
        TPanel *pnlSideNo;
        TTimer *tmButtonDelay;
        TLabel *Label598;
        TLMDEdit *edButtonDelay1;
        TLMDEdit *edButtonDelay2;
        TLMDEdit *edButtonDelay3;
        TLMDEdit *edButtonDelay4;
        TLabel *Label597;
        TLabel *Label599;
        TPanel *pnlColumSelect;
        TPanel *pnlRowSelect;
        TPanel *pnlRFIDOperation;
        TLabel *Label600;
        TEdit *edTestX;
        TLabel *laTestX;
        TLabel *laTestY;
        TEdit *edTestY;
        TCheckBox *cbSECSAtuo;
        TTimer *tmAutoLoadWafer;
        TTimer *tmAutoUnloadWafer;
        TTimer *tmAutoUnload;
        TTimer *tmAutoStart;
        TPanel *pnlMoveTClockwise;
        TLMDButton *btnMoveT1;
        TLMDButton *btnCCW10x;
        TLMDButton *btnCCW5x;
        TLMDButton *btnCCW1x;
        TLMDButton *btnCW1x;
        TLMDButton *btnCW5x;
        TLMDButton *btnCW10x;
        TLMDButton *btnBackwardT1;
        TPanel *pnlMoveTCounterclockwise;
        TLMDGroupBox *LMDGroupBox8;
        TLabel *Label114;
        TLMDButton *btnResetLaserCenter;
        TPanel *pnlLaserCenterPosition;
        TPanel *pnlLaserCenter;
        TLabel *Label601;
        TLMDEdit *edLogReservedDay;
        TLMDButton *btnLogDelete;
        TCheckBox *cbOffLineAtuo;
        TPanel *pnlWaferRobotInformation1;
        TPanel *pnlWaferAlignerInformation1;
        TPanel *pnlWaferChuckInformation1;
        TPanel *Panel38;
        TImage *Image18;
        TLabel *Label603;
        TLabel *Label602;
        TImage *Image19;
        TImage *Image20;
        TImage *Image17;
        TPanel *pnlWaferChuckInformation2;
        TPanel *pnlWaferAlignerInformation2;
        TPanel *pnlWaferRobotInformation2;
        TImage *imUnload;
        TImage *imLoad;
        TCheckBox *cbAutoCancel;
        TLabel *laAlarm;
        TPanel *pnlLocal;
        TLMDButton *btnLocal;
        TPanel *pnlRemote;
        TLMDButton *btnRemote;
        TEdit *edIgnore;
        TLabel *Label604;
        TLabel *Label605;
        TLMDButton *btnReadINF;
        TPanel *pnlColum;
        TPanel *pnlRow;
        TLabel *Label517;
        TLabel *Label518;
        TLabel *Label606;
        TPanel *pnlNFCol;
        TPanel *pnlNFRow;
        TLabel *Label607;
        TPanel *pnlNFLot;
        TPanel *pnlDX;
        TPanel *pnlDY;
        TCheckBox *cbNewMode;
        TPanel *pnlFocusDoneE;
        TGroupBox *gbChangeTime;
        TLabel *Label608;
        TLabel *Label609;
        TEdit *edPasswordSwitchSecond;
        TPanel *pnlZAdjust;
        TLabel *Label610;
        TPanel *Panel61;
        TLMDButton *btnZAdjustOK;
        TLMDButton *btnZAdjustCancel;
        TLabel *Label611;
        TLMDEdit *edZAdjustOffset;
        TCheckBox *cbTCheck;
        TPanel *pnlCassette2Status;
        TLabel *Label614;
        TLabel *Label615;
        TLabel *Label616;
        TLabel *Label617;
        TLabel *Label618;
        TLabel *Label619;
        TLabel *Label620;
        TLabel *Label621;
        TLabel *Label622;
        TLabel *Label623;
        TLabel *Label624;
        TLabel *Label625;
        TLabel *Label626;
        TLabel *Label627;
        TLabel *Label628;
        TLabel *Label629;
        TLabel *Label630;
        TLabel *Label631;
        TLabel *Label632;
        TLabel *Label633;
        TLabel *Label634;
        TLabel *Label635;
        TLabel *Label636;
        TLabel *Label637;
        TLabel *Label638;
        TPanel *Panel64;
        TPanel *pnlTray2_25;
        TPanel *pnlTray2_24;
        TPanel *pnlTray2_23;
        TPanel *pnlTray2_22;
        TPanel *pnlTray2_21;
        TPanel *pnlTray2_20;
        TPanel *pnlTray2_19;
        TPanel *pnlTray2_18;
        TPanel *pnlTray2_17;
        TPanel *pnlTray2_16;
        TPanel *pnlTray2_15;
        TPanel *pnlTray2_14;
        TPanel *pnlTray2_13;
        TPanel *pnlTray2_12;
        TPanel *pnlTray2_11;
        TPanel *pnlTray2_10;
        TPanel *pnlTray2_9;
        TPanel *pnlTray2_8;
        TPanel *pnlTray2_7;
        TPanel *pnlTray2_6;
        TPanel *pnlTray2_5;
        TPanel *pnlTray2_4;
        TPanel *pnlTray2_3;
        TPanel *pnlTray2_2;
        TPanel *pnlTray2_1;
        TPanel *pnlTray2_1Select;
        TPanel *pnlTray2_2Select;
        TPanel *pnlTray2_3Select;
        TPanel *pnlTray2_4Select;
        TPanel *pnlTray2_5Select;
        TPanel *pnlTray2_6Select;
        TPanel *pnlTray2_7Select;
        TPanel *pnlTray2_8Select;
        TPanel *pnlTray2_9Select;
        TPanel *pnlTray2_10Select;
        TPanel *pnlTray2_11Select;
        TPanel *pnlTray2_12Select;
        TPanel *pnlTray2_13Select;
        TPanel *pnlTray2_14Select;
        TPanel *pnlTray2_15Select;
        TPanel *pnlTray2_16Select;
        TPanel *pnlTray2_17Select;
        TPanel *pnlTray2_18Select;
        TPanel *pnlTray2_19Select;
        TPanel *pnlTray2_20Select;
        TPanel *pnlTray2_21Select;
        TPanel *pnlTray2_22Select;
        TPanel *pnlTray2_23Select;
        TPanel *pnlTray2_24Select;
        TPanel *pnlTray2_25Select;
        TPanel *Panel154;
        TLMDButton *LMDButton1;
        TLMDButton *LMDButton3;
        TPanel *pnlWaferRobotInformationLow1;
        TLMDButton *btnCassette2Load;
        TPanel *pnlCassette2Load;
        TLabel *Label639;
        TLabel *Label640;
        TLMDRadioGroup *rgCCDSource;
        TCheckBox *cbLP1E84;
        TCheckBox *cbLP2E84;
        TPanel *Panel156;
        TImage *Image23;
        TLabel *Label320;
        TLabel *Label327;
        TPanel *pnlWaferAlignerInformation;
        TPanel *pnlWaferRobotInformationLow;
        TPanel *pnlWaferRobotInformation;
        TPanel *pnlWaferChuckInformation;
        TLMDButton *btnTest;
        TLMDTabSheet *tsAlarmLog;
        TMemo *mmAlarmLog;
        TImage *Image21;
        TImage *Image22;
        TImage *Image24;
        TImage *Image25;
        TPanel *pnlWaferRobotInformationLow2;
        TLabel *Label422;
        TLabel *Label641;
        TGroupBox *GroupBox5;
        TLabel *Label82;
        TLabel *Label133;
        TLabel *Label115;
        TLabel *Label11;
        TLabel *Label268;
        TLMDButton *btnAutoMatch1;
        TPanel *pnlNCC1;
        TPanel *pnlRotateAngle;
        TCheckBox *cbMoveToCenter;
        TCheckBox *cbRotateBeforeMove;
        TLMDCheckBox *cbTXInvert;
        TLMDCheckBox *cbTYInvert;
        TPanel *pnlMatchedNo;
        TComboBox *cbMatchNo;
        TLMDButton *bnMatchBox;
        TLMDRadioGroup *rgSortMode;
        TLMDEdit *edScore;
        TLabel *Label188;
        TLabel *Label189;
        TPanel *Panel159;
        TLMDProgress *pbWafer;
        TLMDButton *btnSetLimit;
        TPanel *pnlSetLimit;
        TLMDRadioGroup *rgLoadOrder;
        TCheckBox *cbAutoLoad;
        TCheckBox *cbEdgeLog;
        TPanel *Panel7;
        TShape *shDirLeftTop;
        TPanel *pnlLP1Size;
        TPanel *pnlLP2Size;
        TPanel *pnlLP1300DSC;
        TPanel *pnlLP1200DSC;
        TPanel *pnlLP1150DSC;
        TPanel *pnlLP2150DSC;
        TPanel *pnlLP2200DSC;
        TPanel *pnlLP2300DSC;
        TPanel *pnlLP1200mm;
        TPanel *pnlLP1150mm;
        TPanel *pnlLP1Adapter;
        TPanel *pnlLP2200mm;
        TPanel *pnlLP2150mm;
        TPanel *pnlLP2Adapter;
        TPanel *pnlLP2Left;
        TPanel *pnlLP2Right;
        TPanel *pnlLP2Middle;
        TPanel *pnlLP2Presence;
        TPanel *pnlLP1Left;
        TPanel *pnlLP1Right;
        TPanel *pnlLP1Middle;
        TPanel *pnlLP1Presence;
        TPanel *pnlLP1CST;
        TPanel *pnlLP2CST;
        TPanel *pnlLP2Cover;
        TPanel *pnlLP1Cover;
        TPanel *pnlEFEMCassette2;
        TPageControl *PageControl1;
        TTabSheet *tsSECSSystem;
        TRadioGroup *rgEQStatus;
        TRadioGroup *rgSECSType;
        TRadioGroup *rgSECSStatus;
        TRadioGroup *rgSECSLevel;
        TRadioGroup *rgSECSOccur;
        TRadioGroup *rgSECSRecipe;
        TRadioGroup *rgEQExist;
        TRadioGroup *rgUpArmExist;
        TRadioGroup *rgLowArmExist;
        TEdit *edUpArmID;
        TEdit *edLowArmID;
        TEdit *edSECSWaferID;
        TEdit *edEQID;
        TEdit *edSECSRecipeID;
        TPanel *pnlSECSDateTime;
        TPanel *pnlSECSPriority;
        TPanel *pnlSECSRCP;
        TPanel *pnlSECSWaferID;
        TPanel *Panel6;
        TPanel *pnlSECSPortNo;
        TPanel *Panel9;
        TEdit *edSECSSlotNo;
        TPanel *Panel26;
        TEdit *edSECSSourceWID;
        TPanel *Panel31;
        TEdit *edSECSReadWID;
        TRadioGroup *rgSECSPortNo;
        TTabSheet *tsSECSLP1;
        TLabel *Label367;
        TRadioGroup *rgCSTExist;
        TRadioGroup *rgSECSResult;
        TEdit *edMapData;
        TPanel *pnlSECSCSTID;
        TRadioGroup *rgPortStatus;
        TTabSheet *tsSECSLP2;
        TLabel *Label42;
        TRadioGroup *rgCST2Exist;
        TRadioGroup *rgSECSResult2;
        TRadioGroup *rgPortStatus2;
        TEdit *edMapData2;
        TPanel *pnlSECSCST2ID;
        TLabel *Label486;
        TPanel *pnlEFEMVacuum;
        TLabel *Label487;
        TPanel *pnlEFEMCDA;
        TPanel *pnlStatus;
        TLMDGroupBox *gbVieworksCCD;
        TLabel *Label45;
        TEdit *edCCDIndex;
        TPanel *pnlVendor;
        TPanel *pnlModel;
        TPanel *pnlVersion;
        TPanel *pnlID;
        TPanel *pnlWidth;
        TPanel *pnlHeight;
        TPanel *pnlPixelSize;
        TPanel *pnlCCDCount;
        TPanel *pnlInCnt;
        TPanel *pnlSum;
        TPanel *pnlW;
        TPanel *pnlH;
        TPanel *pnlVieworksMessage;
        TButton *btnLive;
        TButton *btnGrab;
        TRadioGroup *rgImageType;
        TPanel *pnlOpenCCD;
        TPanel *pnlCCDRun;
        TPanel *pnlVieworks;
        TImage *imVieworks;
        TPanel *pnlHomeStep;
        TLabel *Label46;
        TLabel *Label47;
        TLabel *Label48;
        TLabel *Label91;
        TPanel *pnlYuanliUnit;
        TPanel *pnlEFEMUnit;
        TPanel *pnlMatchKernelUnit;
        TPanel *pnlSECSUnit;
        TPanel *pnlHome3;
        TPanel *Panel21;
        TImage *imMain;
        TLabel *Label123;
        TPanel *pnlMotionUnit;
        TLabel *Label124;
        TPanel *pnlInspCCDUnit;
        TLabel *Label125;
        TPanel *pnlMatchCCDUnit;
        TLabel *Label126;
        TPanel *pnlCDAVacuumUnit;
        TLabel *Label128;
        TPanel *pnlMotionHomeUnit;
        TPanel *Panel28;
        TImage *imClose;
        TPanel *pnlStartMessage;
        TLabel *Label153;
        TOpenDialog *odINF;
        TImage *Image6;
        TPanel *pnlCST1;
        TPanel *pnlCST2;
        TLMDTabSheet *tsSystemConfig;
        TLMDGroupBox *gbLP1Edge;
        TLMDGroupBox *gbAOICenter;
        TLabel *Label191;
        TLabel *Label192;
        TLabel *Label193;
        TLabel *Label199;
        TLMDEdit *ed12EdgeX1;
        TLMDEdit *ed12EdgeY1;
        TLMDButton *btn12Edge1;
        TLMDButton *btnTo12Edge1;
        TLMDEdit *ed12EdgeZ1;
        TPanel *pnlTo12Edge1;
        TEdit *ed12EdgeIntensity1;
        TLMDGroupBox *LMDGroupBox24;
        TLabel *Label201;
        TLabel *Label204;
        TLabel *Label207;
        TLabel *Label208;
        TLMDEdit *ed12EdgeX2;
        TLMDEdit *ed12EdgeY2;
        TLMDButton *btn12Edge2;
        TLMDButton *btnTo12Edge2;
        TLMDEdit *ed12EdgeZ2;
        TPanel *pnlTo12Edge2;
        TEdit *ed12EdgeIntensity2;
        TLMDGroupBox *LMDGroupBox25;
        TLabel *Label210;
        TLabel *Label211;
        TLabel *Label212;
        TLabel *Label227;
        TLMDEdit *ed12EdgeX3;
        TLMDEdit *ed12EdgeY3;
        TLMDButton *btn12Edge3;
        TLMDButton *btnTo12Edge3;
        TLMDEdit *ed12EdgeZ3;
        TPanel *pnlTo12Edge3;
        TEdit *ed12EdgeIntensity3;
        TLMDGroupBox *gbLP2Edge;
        TLMDGroupBox *LMDGroupBox26;
        TLabel *Label258;
        TLabel *Label259;
        TLabel *Label262;
        TLabel *Label506;
        TLMDEdit *ed8EdgeX1;
        TLMDEdit *ed8EdgeY1;
        TLMDButton *btn8Edge1;
        TLMDButton *btnTo8Edge1;
        TLMDEdit *ed8EdgeZ1;
        TPanel *pnlTo8Edge1;
        TEdit *ed8EdgeIntensity1;
        TLMDGroupBox *LMDGroupBox28;
        TLabel *Label507;
        TLabel *Label642;
        TLabel *Label643;
        TLabel *Label644;
        TLMDEdit *ed8EdgeX2;
        TLMDEdit *ed8EdgeY2;
        TLMDButton *btn8Edge2;
        TLMDButton *btnTo8Edge2;
        TLMDEdit *ed8EdgeZ2;
        TPanel *pnlTo8Edge2;
        TEdit *ed8EdgeIntensity2;
        TLMDGroupBox *LMDGroupBox29;
        TLabel *Label645;
        TLabel *Label646;
        TLabel *Label647;
        TLabel *Label648;
        TLMDEdit *ed8EdgeX3;
        TLMDEdit *ed8EdgeY3;
        TLMDButton *btn8Edge3;
        TLMDButton *btnTo8Edge3;
        TLMDEdit *ed8EdgeZ3;
        TPanel *pnlTo8Edge3;
        TEdit *ed8EdgeIntensity3;
        TGroupBox *GroupBox13;
        TLabel *Label190;
        TEdit *edLampLife;
        TLMDButton *btnSystemConfigSave;
        TGroupBox *GroupBox18;
        TLabel *Label649;
        TEdit *Edit1;
        TLabel *Label154;
        TLMDEdit *edZ1Limit;
        TLabel *Label171;
        TLMDEdit *edZZ1Limit;
        TLMDEdit *edZOffset;
        TLabel *Label353;
        TLabel *Label498;
        TLMDEdit *edZLimit;
        TLabel *Label411;
        TLabel *Label321;
        TLMDEdit *edCCDPrecision;
        TLabel *Label172;
        TLMDEdit *edZZ1Safe;
        TLabel *Label174;
        TPanel *pnlFocusWin;
        TLabel *Label267;
        TLabel *Label279;
        TLabel *Label280;
        TLabel *Label281;
        TLabel *Label342;
        TLabel *Label343;
        TLabel *Label344;
        TLabel *Label345;
        TLabel *Label346;
        TLabel *Label311;
        TLabel *Label520;
        TPanel *Panel35;
        TLMDEdit *edAutoFocus;
        TLMDButton *btnAutoFocus;
        TPanel *pnlAutoFocus;
        TLMDButton *btnUpdateFocus;
        TLMDEdit *edAutoFocusOffset;
        TLMDEdit *edAutoFocusSpeed;
        TPanel *pnlUpZPos;
        TPanel *pnlDownZPos;
        TPanel *pnlUpValue;
        TPanel *pnlDownValue;
        TLMDRadioGroup *rgFocusAlgorithm;
        TPanel *pnlUpZCount;
        TPanel *pnlDownZCount;
        TLMDCheckBox *cbAIFocus;
        TLMDEdit *edDifferenceValue;
        TLMDEdit *edDifferenceRatio;
        TLMDGroupBox *gbOLS5000;
        TLabel *Label185;
        TLabel *Label186;
        TLabel *Label194;
        TLabel *Label195;
        TLMDButton *btnOLS5000ReConnect;
        TPanel *pnlOLS5000Connect;
        TPanel *pnlOLS5000Ready;
        TPanel *Panel33;
        TPanel *pnlOLS5000;
        TPanel *pnlOLS5000Message;
        TLMDPageControl *pcOLS5000;
        TLMDTabSheet *tsOLS5000Setting;
        TLabel *Label200;
        TLabel *Label202;
        TLabel *Label225;
        TLabel *Label226;
        TLabel *Label250;
        TLabel *Label251;
        TLabel *Label252;
        TLabel *Label253;
        TEdit *edOLS5000Port;
        TEdit *edOLS5000IP;
        TButton *btnOLS5000Save;
        TEdit *edOLS5000MacroName1;
        TEdit *edOLS5000Name;
        TEdit *edOLS5000PWD;
        TEdit *edOLS5000MacroName2;
        TEdit *edOLS5000MacroName3;
        TEdit *edOLS5000MacroName4;
        TEdit *edOLS5000MacroName5;
        TLMDTabSheet *tsOLS5000Command;
        TLabel *Label254;
        TLabel *Label255;
        TLabel *Label324;
        TLabel *Label650;
        TLabel *Label651;
        TLabel *Label652;
        TLabel *Label653;
        TLMDButton *btnOLS5000Connect;
        TLMDButton *btnOLS5000LogIn;
        TLMDButton *btnOLS5000WIZEXE;
        TPanel *pnlOLS5000WIZEXE;
        TPanel *pnlOLS5000LogIn;
        TPanel *pnlOLS5000Connect1;
        TLMDButton *btnOLS5000Disconnect;
        TPanel *pnlOLS5000Disconnect;
        TLMDButton *btnOLS5000Remote;
        TPanel *pnlOLS5000Remote;
        TLMDButton *btnOLS5000RDWIZ;
        TPanel *pnlOLS5000RDWIZ;
        TLMDButton *btnOLS5000GETSTS;
        TPanel *pnlOLS5000GETSTS;
        TPanel *pnlOLS5000GETSTSCode;
        TLMDButton *btnOLS5000Start;
        TPanel *pnlOLS5000Start;
        TEdit *edOLS5000Cmd;
        TButton *btnOLS5000Send;
        TPanel *pnlOLS5000Send;
        TLMDButton *btnOLS5000Run;
        TLMDButton *btnOLS5000Stop;
        TCheckBox *cbToLens;
        TEdit *edOLS5000RunCount;
        TRadioGroup *rgLiveMode;
        TButton *btnTriggerTest;
        TLabel *laframe;
        TLMDEdit *edTriggerFrameNo;
        TLabel *Label672;
        TLMDEdit *edTriggerInterval;
        TLabel *Label673;
        TLabel *Label674;
        TLMDEdit *edTriggerStart;
        TPanel *pnlTriggerTest;
        TLabel *Label675;
        TLMDEdit *edTriggerSpeed;
        TLabel *Label676;
        TLabel *Label677;
        TEdit *edTriggerTime;
        TPanel *pnlTriggerCaptureNo;
        TLMDCheckBox *cbTriggerDirection;
        TMenuItem *mnToLensTilt;
        TCheckBox *cbToLensZCompensation;
        TLabel *Label678;
        TPanel *pnl0Position;
        TLMDButton *btn0Position;
        TLMDButton *btnTargetPosition;
        TPanel *pnlTargetPosition;
        TMemo *mmOLS5000;
        TEdit *edOLS5000MacroName6;
        TEdit *edOLS5000MacroName7;
        TEdit *edOLS5000MacroName8;
        TEdit *edOLS5000MacroName9;
        TEdit *edOLS5000MacroName10;
        TClientSocket *csOLS5000;
        TLabel *Label654;
        TPanel *pnlOLS5000Unit;
        TRadioGroup *rgMacroNo;
        TCheckBox *cbDoubleMacro;
        TLMDButton *btnOLS5000Local;
        TPanel *pnlOLS5000Local;
        TRadioGroup *rgSource;
        TRadioGroup *rgCompareMode;
        TShape *shHorizontalVieworks;
        TCheckBox *cb45CrossLine;
        TShape *shVerticalVieworks;
        TPageControl *PageControl2;
        TTabSheet *tsRecipeSet;
        TLabel *Label303;
        TLabel *Label307;
        TLabel *Label305;
        TLabel *Label308;
        TLabel *Label306;
        TLabel *Label304;
        TLabel *Label563;
        TLabel *Label562;
        TLabel *Label564;
        TLabel *Label536;
        TLabel *Label561;
        TLMDButton *btnReBuild;
        TLMDButton *btnRecipeReset;
        TLMDButton *btnReadkmfToPoint;
        TLMDButton *btnZAdjust;
        TPanel *Panel74;
        TComboBox *comboOlympusVisionName1;
        TLMDEdit *edAreaNo;
        TLMDEdit *edAreaTNo;
        TLMDButton *btnAreaSet;
        TLMDButton *btnAreaTo;
        TPanel *pnlToAreaPosition;
        TPanel *pnlToDotPosition;
        TLMDButton *btnDotTo;
        TLMDButton *btnDotSet;
        TLMDEdit *edDotTNo;
        TLMDEdit *edDotNo;
        TPanel *pnlColumSet;
        TPanel *pnlRowSet;
        TTabSheet *tsRecipeParameter;
        TLabel *Label612;
        TLabel *Label613;
        TLabel *Label574;
        TLabel *Label575;
        TLMDEdit *edY45Offset;
        TEdit *edDieSizeY1;
        TEdit *edDieSizeX1;
        TEdit *edDieSizeGapX1;
        TEdit *edDieSizeGapY1;
        TRadioGroup *rgOperationMode;
        TRadioGroup *rgLightMode;
        TPanel *Panel45;
        TPanel *pnl45NiUp;
        TPanel *Panel66;
        TPanel *pnl45NiDown;
        TPanel *Panel73;
        TPanel *pnl45CuUp;
        TPanel *Panel83;
        TPanel *pnl45CuDown;
        TPopupMenu *pm45Set;
        TMenuItem *mn45NiUp;
        TMenuItem *mn45NiDown;
        TMenuItem *mn45CuUp;
        TMenuItem *mn45CuDown;
        TMenuItem *mn45Save;
        TShape *sh45NiUp;
        TShape *sh45NiDown;
        TShape *sh45CuUp;
        TShape *sh45CuDown;
        TMenuItem *mn45Clear;
        TCheckBox *cb45FullImage;
        TPanel *Panel60;
        TPanel *pnl45Resolution;
        TPanel *Panel68;
        TPanel *pnl45Ni;
        TPanel *pnl45Cu;
        TLMDButton *btn45Z1Up;
        TLMDButton *btn45Z1Down;
        TPanel *pnl45Z1;
        TLMDButton *btnOLS5000Connect1;
        TPanel *pnlOLS5000Connect2;
        TCheckBox *cbResetBuzzer;
        TLMDEdit *ed45Gain;
        TLabel *Label655;
        TButton *btn45Gain;
        TLabel *Label656;
        TButton *btn45Reset;
        TPanel *pnlLP2FOUPLeftDoor;
        TPanel *pnlLP2FOUPRightDoor;
        TPanel *pnlLP2CarrierClamp;
        TPanel *pnlLP2Protrusion;
        TPanel *pnlLP1FOUPLeftDoor;
        TPanel *pnlLP1FOUPRightDoor;
        TPanel *pnlLP1CarrierClamp;
        TPanel *pnlLP1Protrusion;
        TLabel *Label657;
        TLabel *Label658;
        TPanel *Panel82;
        TShape *shWaferEmpty;
        TLabel *laWaferEmpty;
        TShape *shWaferExist;
        TLabel *laWaferExist;
        TShape *shWaferSelect;
        TLabel *laWaferSelect;
        TShape *shWaferDoubleSlot;
        TLabel *laWaferDoubleSlot;
        TShape *shWaferCrossSlot;
        TLabel *laWaferCrossSlot;
        TLabel *laWaferProcess;
        TShape *shWaferProcess;
        TShape *shWaferFinish;
        TLabel *laWaferFinish;
        TShape *shWaferError;
        TLabel *laWaferError;
        TColorDialog *cdWaferColor;
        TLMDButton *btnSaveWaferColor;
        TEdit *edSetValue;
        TCheckBox *cbTwoLoadport;
        TPanel *pnlCenterMessage;
        TButton *btnStopSave;
        TTimer *tmFindCenter;
//
        void __fastcall FormShow(TObject *Sender);
//
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
//
        void __fastcall tmSystemTimer(TObject *Sender);
//
        void __fastcall btnMoveXClick(TObject *Sender);
        void __fastcall btnBackwardXClick(TObject *Sender);
        void __fastcall btnStopRelativeClick(TObject *Sender);
        void __fastcall btnMoveClick(TObject *Sender);
        void __fastcall btnBackwardClick(TObject *Sender);
//
        void __fastcall btnMoveMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveXMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveXMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
//
        void __fastcall btnMoveMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveAbsoluteClick(TObject *Sender);
        void __fastcall btnStopAbsoluteClick(TObject *Sender);
        void __fastcall btnResetAllClick(TObject *Sender);
        void __fastcall btnUpdateMotionClick(TObject *Sender);
        void __fastcall btnBackwardXMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardXMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnHomeOneAxisClick(TObject *Sender);
        void __fastcall btnHomeClick(TObject *Sender);
        void __fastcall btnResetOneAxisClick(TObject *Sender);
        void __fastcall btnUpdateRecipeClick(TObject *Sender);
        void __fastcall sgResultDrawCell(TObject *Sender, int ACol,
          int ARow, TRect &Rect, TGridDrawState State);
//
        void __fastcall btnManualOkClick(TObject *Sender);
        void __fastcall combRecipeChange(TObject *Sender);
        void __fastcall cbRecipeChange(TObject *Sender);
        void __fastcall combRecipeSelect(TObject *Sender);
        void __fastcall cbRecipeSelect(TObject *Sender);
        void __fastcall combRecipeExit(TObject *Sender);
        void __fastcall combRecipeDropDown(TObject *Sender);
        void __fastcall combRecipeKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall cbRecipeDropDown(TObject *Sender);
        void __fastcall btnPasswordClick(TObject *Sender);
        void __fastcall btnLogClick(TObject *Sender);
        void __fastcall sgUserDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
        void __fastcall btnUserNewClick(TObject *Sender);
        void __fastcall btnUserDeleteClick(TObject *Sender);
        void __fastcall btnUserRefreshClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall rgCCDSelectChange(TObject *Sender,
          int ButtonIndex);
        void __fastcall btnReviewLiveClick(TObject *Sender);
        void __fastcall btnReviewLoadClick(TObject *Sender);
        void __fastcall btnReviewSaveClick(TObject *Sender);
        void __fastcall imCCDMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall pnlCCDSizeClick(TObject *Sender);
        void __fastcall shCenterMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shCenterMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall shCenterMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shLeftUpMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shLeftUpMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall shLeftUpMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shLeftMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall shLeftMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shLeftDownMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shLeftDownMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall shLeftDownMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shUpMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shUpMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall shUpMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shDownMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shDownMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
        void __fastcall shDownMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shRightUpMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shRightUpMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall shRightUpMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shRightMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shRightMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);

        void __fastcall shRightMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall shRightDownMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shRightDownMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall shRightDownMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall cbStdPatternClick(TObject *Sender);
        void __fastcall cbRulerClick(TObject *Sender);
        void __fastcall rgRulerTypeClick(TObject *Sender);
        void __fastcall rgRulerColorClick(TObject *Sender);
        void __fastcall btnAutoMatchClick(TObject *Sender);
        void __fastcall btnTiltPositionClick(TObject *Sender);
        void __fastcall btnToTiltPositionClick(TObject *Sender);
        void __fastcall tmMotionPollingTimer(TObject *Sender);
        void __fastcall imCCDMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall btnArrayLeftClick(TObject *Sender);
        void __fastcall btnArrayRightClick(TObject *Sender);
        void __fastcall btnArrayUpClick(TObject *Sender);
        void __fastcall btnArrayDownClick(TObject *Sender);
        void __fastcall btnDieLeftClick(TObject *Sender);
        void __fastcall btnDieRightClick(TObject *Sender);
        void __fastcall btnDieUpClick(TObject *Sender);
        void __fastcall btnDieDownClick(TObject *Sender);
        void __fastcall btnRemoteRotateClick(TObject *Sender);
        void __fastcall pnlDOPolarizerClick(TObject *Sender);
        void __fastcall pnlDORedLampClick(TObject *Sender);
        void __fastcall pnlDOYellowLampClick(TObject *Sender);
        void __fastcall btnServoOnClick(TObject *Sender);
        void __fastcall btnServoOffClick(TObject *Sender);
        void __fastcall btnAlarmOnClick(TObject *Sender);
        void __fastcall btnAlarmOffClick(TObject *Sender);

        void __fastcall btnMoveYClick(TObject *Sender);
        void __fastcall btnMoveZClick(TObject *Sender);
        void __fastcall btnMoveTClick(TObject *Sender);
        void __fastcall btnBackwardYClick(TObject *Sender);
        void __fastcall btnBackwardZClick(TObject *Sender);
        void __fastcall btnBackwardTClick(TObject *Sender);

        void __fastcall btnMoveYMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveZMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveTMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveYMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveZMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveTMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);

        void __fastcall btnBackwardYMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardZMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardTMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardYMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardZMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardTMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);

        void __fastcall btnUpdateSystemParameterClick(TObject *Sender);
        void __fastcall rgBaslerShutterClick(TObject *Sender);
        void __fastcall tbBaslerGainChange(TObject *Sender);
        void __fastcall tm500msTimer(TObject *Sender);
        void __fastcall shLeftMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnZeroPositionClick(TObject *Sender);
        void __fastcall btnToZeroPositionClick(TObject *Sender);
        void __fastcall sgResultClick(TObject *Sender);
        void __fastcall btnResetLaserCenterClick(TObject *Sender);
        void __fastcall btnLoadPositionClick(TObject *Sender);
        void __fastcall btnToLoadPositionClick(TObject *Sender);
        void __fastcall tmTMoveTimer(TObject *Sender);
        void __fastcall pnlAlarmMessageClick(TObject *Sender);
        void __fastcall btnResetClick(TObject *Sender);
        void __fastcall btnToLastPositionClick(TObject *Sender);
        void __fastcall btnLastPositionClick(TObject *Sender);
        void __fastcall btnToLastNoClick(TObject *Sender);
        void __fastcall btnToLastYesClick(TObject *Sender);
        void __fastcall btnCCW1xClick(TObject *Sender);
        void __fastcall btnCCW5xClick(TObject *Sender);
        void __fastcall btnCCW10xClick(TObject *Sender);
        void __fastcall btnCW10xClick(TObject *Sender);
        void __fastcall btnCW5xClick(TObject *Sender);
        void __fastcall btnCW1xClick(TObject *Sender);
        void __fastcall btnLeft10xClick(TObject *Sender);
        void __fastcall btnLeft5xClick(TObject *Sender);
        void __fastcall btnLeft1xClick(TObject *Sender);
        void __fastcall btnRight1xClick(TObject *Sender);
        void __fastcall btnRight5xClick(TObject *Sender);
        void __fastcall btnRight10xClick(TObject *Sender);
        void __fastcall btnRear10xClick(TObject *Sender);
        void __fastcall btnRear5xClick(TObject *Sender);
        void __fastcall btnRear1xClick(TObject *Sender);
        void __fastcall btnFront1xClick(TObject *Sender);
        void __fastcall btnFront5xClick(TObject *Sender);
        void __fastcall btnFront10xClick(TObject *Sender);
        void __fastcall btnUp10xClick(TObject *Sender);
        void __fastcall btnUp5xClick(TObject *Sender);
        void __fastcall btnUp1xClick(TObject *Sender);
        void __fastcall btnDown1xClick(TObject *Sender);
        void __fastcall btnDown5xClick(TObject *Sender);
        void __fastcall btnDown10xClick(TObject *Sender);
        void __fastcall btnPos1SetClick(TObject *Sender);
        void __fastcall btnPos2SetClick(TObject *Sender);
        void __fastcall btnPos3SetClick(TObject *Sender);
        void __fastcall btnPos5SetClick(TObject *Sender);
        void __fastcall btnPositionSaveClick(TObject *Sender);
        void __fastcall btnPos1GoClick(TObject *Sender);
        void __fastcall btnPos2GoClick(TObject *Sender);
        void __fastcall btnPos3GoClick(TObject *Sender);
        void __fastcall btnPos4GoClick(TObject *Sender);
        void __fastcall btnPos5GoClick(TObject *Sender);
        void __fastcall btnUp100xClick(TObject *Sender);
        void __fastcall btnDown100xClick(TObject *Sender);
        void __fastcall pnlSystemClick(TObject *Sender);
        void __fastcall pnlMatchDataCloseClick(TObject *Sender);
        void __fastcall gbMatchDataMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall gbMatchDataMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall gbMatchDataMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shLaserShutterInnerMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall shLaserShutterInnerMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shLaserShutterOuterMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall cbAngularHorizontalClick(TObject *Sender);
        void __fastcall btnArray1LeftClick(TObject *Sender);
        void __fastcall btnArray2LeftClick(TObject *Sender);
        void __fastcall btnArray1RightClick(TObject *Sender);
        void __fastcall btnArray2RightClick(TObject *Sender);
        void __fastcall btnArray1UpClick(TObject *Sender);
        void __fastcall btnArray2UpClick(TObject *Sender);
        void __fastcall btnArray1DownClick(TObject *Sender);
        void __fastcall btnArray2DownClick(TObject *Sender);
        void __fastcall pnlRecipeSetClick(TObject *Sender);
        void __fastcall pnlRemoteLeftClick(TObject *Sender);
        void __fastcall pnlRemoteRightClick(TObject *Sender);
        void __fastcall tm400msTimer(TObject *Sender);
        void __fastcall btnPos4SetClick(TObject *Sender);
        void __fastcall btnSetLens1PositionClick(TObject *Sender);
        void __fastcall btnSetLens2PositionClick(TObject *Sender);
        void __fastcall btnSetLens3PositionClick(TObject *Sender);
        void __fastcall btnSetLens4PositionClick(TObject *Sender);
        void __fastcall btnSetLens5PositionClick(TObject *Sender);
        void __fastcall btnSetLens6PositionClick(TObject *Sender);
        void __fastcall btnToLens1PositionClick(TObject *Sender);
        void __fastcall btnToLens2PositionClick(TObject *Sender);
        void __fastcall btnToLens3PositionClick(TObject *Sender);
        void __fastcall btnToLens4PositionClick(TObject *Sender);
        void __fastcall btnToLens5PositionClick(TObject *Sender);
        void __fastcall btnToLens6PositionClick(TObject *Sender);
        void __fastcall btnSaveLensPositionClick(TObject *Sender);
        void __fastcall btnSaveIlluminationClick(TObject *Sender);
        void __fastcall imCCDDblClick(TObject *Sender);
        void __fastcall imCCDMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shLaserShutterOuterMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall shLaserShutterInnerMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shLaserShutterOuterMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnSetLens1ZLimitClick(TObject *Sender);
        void __fastcall btnSetLens2ZLimitClick(TObject *Sender);
        void __fastcall btnSetLens3ZLimitClick(TObject *Sender);
        void __fastcall btnSetLens4ZLimitClick(TObject *Sender);
        void __fastcall btnSetLens5ZLimitClick(TObject *Sender);
        void __fastcall btnSetLens6ZLimitClick(TObject *Sender);
        void __fastcall pnlMeasureResultClick(TObject *Sender);
        void __fastcall shMeasureMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall shMeasureMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall pnlMeasureResultDblClick(TObject *Sender);
        void __fastcall cbMeasureClick(TObject *Sender);
        void __fastcall cbCrossHairClick(TObject *Sender);
        void __fastcall shUpPositionMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shRightPositionMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall shMeasureMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall edYApertureEnter(TObject *Sender);
        void __fastcall edXApertureEnter(TObject *Sender);
        void __fastcall bnMatchBoxClick(TObject *Sender);
        void __fastcall shMarkMatchMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnAbortWithinClick(TObject *Sender);
        void __fastcall tm250msTimer(TObject *Sender);
        void __fastcall tmISCCDTimer(TObject *Sender);
        void __fastcall rgSpeedClick(TObject *Sender);
        void __fastcall pnlStageLockClick(TObject *Sender);
        void __fastcall pnlStageVacuumClick(TObject *Sender);
        void __fastcall pnlStageBarClick(TObject *Sender);
        void __fastcall pnlDOReserved9Click(TObject *Sender);
        void __fastcall rgRulerColor1Click(TObject *Sender);
        void __fastcall btnCalibrationDoneClick(TObject *Sender);
        void __fastcall btnCalibrationSaveClick(TObject *Sender);
        void __fastcall tbContrastChange(TObject *Sender);
        void __fastcall pnlUnitClick(TObject *Sender);
        void __fastcall btnStopMotionClick(TObject *Sender);
        void __fastcall mnClearClick(TObject *Sender);
        void __fastcall mnSaveFileClick(TObject *Sender);
        void __fastcall btnSpeedUpdateClick(TObject *Sender);
        void __fastcall btnAutoFocusClick(TObject *Sender);
        void __fastcall btnUpdateFocusClick(TObject *Sender);
        void __fastcall btnDeleteRecipeClick(TObject *Sender);
        void __fastcall cbLampControl2Click(TObject *Sender);
        void __fastcall tbLED2CH1Change(TObject *Sender);
        void __fastcall tbLED2CH1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall tbLED2CH2Change(TObject *Sender);
        void __fastcall tbLED2CH2MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall tbLED2CH3Change(TObject *Sender);
        void __fastcall tbLED2CH3MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall tbLED2CH4Change(TObject *Sender);
        void __fastcall tbLED2CH4MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnLampControl2Click(TObject *Sender);
        void __fastcall btnSaveLED2Click(TObject *Sender);
        void __fastcall btnCCDPositionClick(TObject *Sender);
        void __fastcall btnToCCDPositionClick(TObject *Sender);
        void __fastcall mnToLensClick(TObject *Sender);
        void __fastcall mnToLens1Click(TObject *Sender);
        void __fastcall mnToLens2Click(TObject *Sender);
        void __fastcall mnToLens3Click(TObject *Sender);
        void __fastcall mnToLens4Click(TObject *Sender);
        void __fastcall mnToCCDClick(TObject *Sender);
        void __fastcall btnAreaSetClick(TObject *Sender);
        void __fastcall btnDotSetClick(TObject *Sender);
        void __fastcall btnBase1SetClick(TObject *Sender);
        void __fastcall btnBase2SetClick(TObject *Sender);
        void __fastcall btnAreaToClick(TObject *Sender);
        void __fastcall btnDotToClick(TObject *Sender);
        void __fastcall btnBase1ToClick(TObject *Sender);
        void __fastcall btnBase2ToClick(TObject *Sender);
        void __fastcall sgAreaClick(TObject *Sender);
        void __fastcall sgDotClick(TObject *Sender);
        void __fastcall btnRunStopClick(TObject *Sender);
        void __fastcall btnReBuildClick(TObject *Sender);
        void __fastcall btnEraseMatchBoxClick(TObject *Sender);
        void __fastcall btnRecipeResetClick(TObject *Sender);
        void __fastcall imPatternClick(TObject *Sender);
        void __fastcall pnlPatternClick(TObject *Sender);
        void __fastcall btnToOriginalClick(TObject *Sender);
        void __fastcall btnToInputClick(TObject *Sender);
        void __fastcall btnFindFocusClick(TObject *Sender);
        void __fastcall btnVacuumClick(TObject *Sender);
        void __fastcall btnSavePatternClick(TObject *Sender);
        void __fastcall btnMoveZ1Click(TObject *Sender);
        void __fastcall btnMoveZ1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveZ1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardZ1Click(TObject *Sender);
        void __fastcall btnBackwardZ1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardZ1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnkmfPositionClick(TObject *Sender);
        void __fastcall btnTokmfPositionClick(TObject *Sender);
        void __fastcall btnReadkmfClick(TObject *Sender);
        void __fastcall pnlkmfFileClick(TObject *Sender);
        void __fastcall sgkmfClick(TObject *Sender);
        void __fastcall btnTokmfClick(TObject *Sender);
        void __fastcall comboOlympusVisionName1Click(TObject *Sender);
        void __fastcall comboOlympusVisionName1DropDown(TObject *Sender);
        void __fastcall btnSavekmfParameterClick(TObject *Sender);
        void __fastcall btnReadkmfToPointClick(TObject *Sender);
        void __fastcall comboPatternChange(TObject *Sender);
        void __fastcall btnAssignPatternClick(TObject *Sender);
        void __fastcall rgMatchSourceChange(TObject *Sender,
          int ButtonIndex);
        void __fastcall btnSetkmfClick(TObject *Sender);
        void __fastcall sgDotDblClick(TObject *Sender);
        void __fastcall sgkmfDblClick(TObject *Sender);
        void __fastcall pnlRecipeClick(TObject *Sender);
        void __fastcall pnlRecipeLabelClick(TObject *Sender);
        void __fastcall sgAreaDblClick(TObject *Sender);
        void __fastcall btnDotSelectClick(TObject *Sender);
        void __fastcall btnDotApplyClick(TObject *Sender);
        void __fastcall sgkmfDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
        void __fastcall sgDotDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
        void __fastcall sgAreaDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
        void __fastcall Panel39Click(TObject *Sender);
        void __fastcall btnReMatchClick(TObject *Sender);
        void __fastcall btnExitMatchClick(TObject *Sender);
        void __fastcall btnDisplayResultClick(TObject *Sender);
        void __fastcall btnMatchToCenterClick(TObject *Sender);
        void __fastcall tmJoystickTimer(TObject *Sender);
        void __fastcall tmTriggerTimer(TObject *Sender);
        void __fastcall btnPos6SetClick(TObject *Sender);
        void __fastcall btnPos7SetClick(TObject *Sender);
        void __fastcall btnPos8SetClick(TObject *Sender);
        void __fastcall btnPos9SetClick(TObject *Sender);
        void __fastcall btnPos10SetClick(TObject *Sender);
        void __fastcall btnPos6GoClick(TObject *Sender);
        void __fastcall btnPos7GoClick(TObject *Sender);
        void __fastcall btnPos8GoClick(TObject *Sender);
        void __fastcall btnPos9GoClick(TObject *Sender);
        void __fastcall btnPos10GoClick(TObject *Sender);
        void __fastcall btnMoveBaseSetClick(TObject *Sender);
        void __fastcall btnMoveBaseGoClick(TObject *Sender);
        void __fastcall btnMoveBaseMoveClick(TObject *Sender);
        void __fastcall tmXTimer(TObject *Sender);
        void __fastcall tmYTimer(TObject *Sender);
        void __fastcall tmZTimer(TObject *Sender);
        void __fastcall btnJoystickSaveClick(TObject *Sender);
        void __fastcall btnSvonClick(TObject *Sender);
        void __fastcall btnFrontOutClick(TObject *Sender);
        void __fastcall btnFrontInClick(TObject *Sender);
        void __fastcall btnRightOutClick(TObject *Sender);
        void __fastcall btnRightInClick(TObject *Sender);
        void __fastcall btnRearOutClick(TObject *Sender);
        void __fastcall btnRearInClick(TObject *Sender);
        void __fastcall btnLeftOutClick(TObject *Sender);
        void __fastcall btnLeftInClick(TObject *Sender);
        void __fastcall btnSafeSaveClick(TObject *Sender);
        void __fastcall FormMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall FormMouseWheelUp(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall pnlMoveTopClick(TObject *Sender);
        void __fastcall btnToCenterClick(TObject *Sender);
        void __fastcall pnlDOMaintenanceLightClick(TObject *Sender);
        void __fastcall pnlDOCDAClick(TObject *Sender);
        void __fastcall pnlDOEFEMFFUClick(TObject *Sender);
        void __fastcall pnlDOStageFFUClick(TObject *Sender);
        void __fastcall pnlStageVacuum1Click(TObject *Sender);
        void __fastcall pnlDOReserved8Click(TObject *Sender);
        void __fastcall pnlDOGreenLampClick(TObject *Sender);
        void __fastcall pnlDOBlueLampClick(TObject *Sender);
        void __fastcall pnlDOBuzzerClick(TObject *Sender);
        void __fastcall btnEFEMMaintenanceModeClick(TObject *Sender);
        void __fastcall btnLoadClick(TObject *Sender);
        void __fastcall btn0PositionClick(TObject *Sender);
        void __fastcall btnTargetPositionClick(TObject *Sender);
        void __fastcall btnLoadWaferClick(TObject *Sender);
        void __fastcall btnUnloadWaferClick(TObject *Sender);
        void __fastcall ybRobotCommNotify(TObject *Sender, int NotifyType);
        void __fastcall btnDemoLFUpClick(TObject *Sender);
        void __fastcall btnDemoLFDownClick(TObject *Sender);
        void __fastcall btnMotionResetClick(TObject *Sender);
        void __fastcall btnRobotConnectClick(TObject *Sender);
        void __fastcall btnLoadPortConnectClick(TObject *Sender);
        void __fastcall btnAlignerConnectClick(TObject *Sender);
        void __fastcall btnAlignerSetClick(TObject *Sender);
        void __fastcall btnAlignerGetClick(TObject *Sender);
        void __fastcall ybAlignerCommNotify(TObject *Sender,
          int NotifyType);
        void __fastcall btnRobotCMDClick(TObject *Sender);
        void __fastcall btnRobotPutClick(TObject *Sender);
        void __fastcall btnRobotGetClick(TObject *Sender);
        void __fastcall btnLoadPortMapClick(TObject *Sender);
        void __fastcall btnLoadPortOpenClick(TObject *Sender);
        void __fastcall btnLoadPortCloseClick(TObject *Sender);
        void __fastcall btnLoadPortClampClick(TObject *Sender);
        void __fastcall btnLoadPortVacuumClick(TObject *Sender);
        void __fastcall btnLoadPortLoadClick(TObject *Sender);
        void __fastcall btnLoadPortUnLoadClick(TObject *Sender);
        void __fastcall pnlStartMessageClick(TObject *Sender);
        void __fastcall btnRobotOriginalClick(TObject *Sender);
        void __fastcall btnRobotPosClick(TObject *Sender);
        void __fastcall btnLoadPortCMDClick(TObject *Sender);
        void __fastcall btnAlignerCMDClick(TObject *Sender);
        void __fastcall ybLoadPortCommNotify(TObject *Sender,
          int NotifyType);
        void __fastcall btnAlignerORGNClick(TObject *Sender);
        void __fastcall btnAlignerAlignmentClick(TObject *Sender);
        void __fastcall btnAlignerVacuumOffClick(TObject *Sender);
        void __fastcall btnLoadPortStasClick(TObject *Sender);
        void __fastcall btnAlignerStasClick(TObject *Sender);
        void __fastcall btnRobotStasClick(TObject *Sender);
        void __fastcall btnAlignerEnableClick(TObject *Sender);
        void __fastcall btnLoadPortEnableClick(TObject *Sender);
        void __fastcall btnRobotEnableClick(TObject *Sender);
        void __fastcall btnRobotVacuumOnClick(TObject *Sender);
        void __fastcall btnRobotVacuumOffClick(TObject *Sender);
        void __fastcall btnRobotWithWaferClick(TObject *Sender);
        void __fastcall btnAlignerWithWaferClick(TObject *Sender);
        void __fastcall btnLoadPortLEDClick(TObject *Sender);
        void __fastcall tmLoadUnloadTimer(TObject *Sender);
        void __fastcall btnCassetteLoadClick(TObject *Sender);
        void __fastcall btnChuckVacuumOnClick(TObject *Sender);
        void __fastcall btnChuckVacuumOffClick(TObject *Sender);
        void __fastcall btnDemoLFVacuumOffClick(TObject *Sender);
        void __fastcall btnLoopTestClick(TObject *Sender);
        void __fastcall btnLoopTestStopClick(TObject *Sender);
        void __fastcall btnAlignerResetClick(TObject *Sender);
        void __fastcall tmSetupEFEMTimer(TObject *Sender);
        void __fastcall btnLoadPortMappingClick(TObject *Sender);
        void __fastcall btnAlignerSaveClick(TObject *Sender);
        void __fastcall btnRobotGetPositionClick(TObject *Sender);
        void __fastcall btnLoadPortResetClick(TObject *Sender);
        void __fastcall Panel94Click(TObject *Sender);
        void __fastcall btnRobotClearAlarmClick(TObject *Sender);
        void __fastcall btnRobotEanbleClick(TObject *Sender);
        void __fastcall btnRobotDisableClick(TObject *Sender);
        void __fastcall pnlTraySelectClick(TObject *Sender);
        void __fastcall rgLoadOrderChange(TObject *Sender,
          int ButtonIndex);
        void __fastcall btnAllSelectClick(TObject *Sender);
        void __fastcall tmBuzzerTimer(TObject *Sender);
        void __fastcall Panel98Click(TObject *Sender);
        void __fastcall Panel93Click(TObject *Sender);
        void __fastcall Panel105Click(TObject *Sender);
        void __fastcall pnlXClick(TObject *Sender);
        void __fastcall pnlEFEMReadyClick(TObject *Sender);
        void __fastcall Label182Click(TObject *Sender);
        void __fastcall btnReStartClick(TObject *Sender);
        void __fastcall cbAutoLoadClick(TObject *Sender);
        void __fastcall rgMaintenanceModeClick(TObject *Sender);
        void __fastcall btnMaintenanceLightClick(TObject *Sender);
        void __fastcall cbMaintenanceModeClick(TObject *Sender);
        void __fastcall btnSetLimitClick(TObject *Sender);
        void __fastcall tmAlignerStasTimer(TObject *Sender);
        void __fastcall tmLFupTimer(TObject *Sender);
        void __fastcall tmLFDownTimer(TObject *Sender);
        void __fastcall pnlSetLimitClick(TObject *Sender);
        void __fastcall tmAlignerORGTimer(TObject *Sender);
        void __fastcall comboOlympusVisionNameClick(TObject *Sender);
        void __fastcall btnSystemRunClick(TObject *Sender);
        void __fastcall btnAlignerSendClick(TObject *Sender);
        void __fastcall btnRorzeAlignerORGNClick(TObject *Sender);
        void __fastcall btnAlignerALGNClick(TObject *Sender);
        void __fastcall btnAlignerSTATClick(TObject *Sender);
        void __fastcall btnAlignerCLMPClick(TObject *Sender);
        void __fastcall btnAlignerUCLMClick(TObject *Sender);
        void __fastcall btnAlignerINITClick(TObject *Sender);
        void __fastcall btnAlignerRSTAClick(TObject *Sender);
        void __fastcall btnAlignerSTOPClick(TObject *Sender);
        void __fastcall btnAlignerzHomeClick(TObject *Sender);
        void __fastcall btnAlignerSSIZClick(TObject *Sender);
        void __fastcall btnAlignerGTADClick(TObject *Sender);
        void __fastcall btnAlignerDoClick(TObject *Sender);
        void __fastcall btnInputClick(TObject *Sender);
        void __fastcall btnRobotSendClick(TObject *Sender);
        void __fastcall btnRobotToHomeClick(TObject *Sender);
        void __fastcall cbRobotActiveClick(TObject *Sender);
        void __fastcall btnRobotORGNClick(TObject *Sender);
        void __fastcall btnRobotSTATClick(TObject *Sender);
        void __fastcall btnRobotRSTAClick(TObject *Sender);
        void __fastcall rgRobotSpeedClick(TObject *Sender);
        void __fastcall btnRobotHOMEClick(TObject *Sender);
        void __fastcall btnRobotStageHomeClick(TObject *Sender);
        void __fastcall btnRorzeRobotGetClick(TObject *Sender);
        void __fastcall btnRorzeRobotPutClick(TObject *Sender);
        void __fastcall csAlignerSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csAlignerSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csAlignerSocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall csAlignerSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall mnSaveAlignerToFileClick(TObject *Sender);
        void __fastcall mnClearAlignerMessageClick(TObject *Sender);
        void __fastcall mnSaveRobotToFileClick(TObject *Sender);
        void __fastcall mnClearRobotMessageClick(TObject *Sender);
        void __fastcall csRobotSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csRobotSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csRobotSocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall csRobotSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnLoadPort1SendClick(TObject *Sender);
        void __fastcall btnLoadPort1ORGNClick(TObject *Sender);
        void __fastcall btnLoadPort1CLMPClick(TObject *Sender);
        void __fastcall btnLoadPort1UCLMClick(TObject *Sender);
        void __fastcall btnLoadPort1WMAPClick(TObject *Sender);
        void __fastcall btnLoadPort1INITClick(TObject *Sender);
        void __fastcall btnLoadPort1STATClick(TObject *Sender);
        void __fastcall btnLoadPort1GMAPClick(TObject *Sender);
        void __fastcall btnLoadPort1RSTAClick(TObject *Sender);
        void __fastcall btnLoadPort1MODEClick(TObject *Sender);
        void __fastcall btnLoadPort1LOADClick(TObject *Sender);
        void __fastcall btnLoadPort1UNLDClick(TObject *Sender);
        void __fastcall cbLoadPort1E84Click(TObject *Sender);
        void __fastcall btnLoadPort1GPIOClick(TObject *Sender);
        void __fastcall pnlLoadPort1PresenceClick(TObject *Sender);
        void __fastcall pnlLoadPort1PlacementClick(TObject *Sender);
        void __fastcall pnlLoadPort1LoadClick(TObject *Sender);
        void __fastcall pnlLoadPort1UnloadClick(TObject *Sender);
        void __fastcall pnlLoadPort1ManualClick(TObject *Sender);
        void __fastcall pnlLoadPort1AlarmClick(TObject *Sender);
        void __fastcall pnlLoadPort1ClampClick(TObject *Sender);
        void __fastcall pnlLoadPort1DockClick(TObject *Sender);
        void __fastcall mnSaveLoadProt1ToFileClick(TObject *Sender);
        void __fastcall mnClearLoadPort1MessageClick(TObject *Sender);
        void __fastcall csLoadPort1SocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csLoadPort1SocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csLoadPort1SocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall csLoadPort1SocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnLoadPort2SendClick(TObject *Sender);
        void __fastcall btnLoadPort2ORGNClick(TObject *Sender);
        void __fastcall btnLoadPort2CLMPClick(TObject *Sender);
        void __fastcall btnLoadPort2UCLMClick(TObject *Sender);
        void __fastcall btnLoadPort2WMAPClick(TObject *Sender);
        void __fastcall btnLoadPort2INITClick(TObject *Sender);
        void __fastcall btnLoadPort2STATClick(TObject *Sender);
        void __fastcall btnLoadPort2GMAPClick(TObject *Sender);
        void __fastcall btnLoadPort2RSTAClick(TObject *Sender);
        void __fastcall btnLoadPort2MODEClick(TObject *Sender);
        void __fastcall btnLoadPort2LOADClick(TObject *Sender);
        void __fastcall btnLoadPort2UNLDClick(TObject *Sender);
        void __fastcall cbLoadPort2E84Click(TObject *Sender);
        void __fastcall btnLoadPort2GPIOClick(TObject *Sender);
        void __fastcall pnlLoadPort2PresenceClick(TObject *Sender);
        void __fastcall pnlLoadPort2PlacementClick(TObject *Sender);
        void __fastcall pnlLoadPort2LoadClick(TObject *Sender);
        void __fastcall pnlLoadPort2UnloadClick(TObject *Sender);
        void __fastcall pnlLoadPort2ManualClick(TObject *Sender);
        void __fastcall pnlLoadPort2AlarmClick(TObject *Sender);
        void __fastcall pnlLoadPort2ClampClick(TObject *Sender);
        void __fastcall pnlLoadPort2DockClick(TObject *Sender);
        void __fastcall mnSaveLoadProt2ToFileClick(TObject *Sender);
        void __fastcall mnClearLoadPort2MessageClick(TObject *Sender);
        void __fastcall csLoadPort2SocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csLoadPort2SocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csLoadPort2SocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall csLoadPort2SocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnRFIDReadClick(TObject *Sender);
        void __fastcall btnRFIDSerialNumberClick(TObject *Sender);
        void __fastcall btnRFIDInitClick(TObject *Sender);
        void __fastcall btnRFIDTestClick(TObject *Sender);
        void __fastcall pnlRFIDOperationClick(TObject *Sender);
        void __fastcall ybRFID18CommNotify(TObject *Sender,
          int NotifyType);
        void __fastcall ybRFID112CommNotify(TObject *Sender,
          int NotifyType);
        void __fastcall ybRFID28CommNotify(TObject *Sender,
          int NotifyType);
        void __fastcall ybRFID212CommNotify(TObject *Sender,
          int NotifyType);
        void __fastcall ssYuanliSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ssYuanliSocketClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall combRFIDComportChange(TObject *Sender);
        void __fastcall btnRorzeEFEMSetupClick(TObject *Sender);
        void __fastcall btnSaveWPositionClick(TObject *Sender);
        void __fastcall btnAlignerSaveRClick(TObject *Sender);
        void __fastcall btnBackwardWClick(TObject *Sender);
        void __fastcall btnBackwardWMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardWMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveWClick(TObject *Sender);
        void __fastcall btnMoveWMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveWMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall pnlJoystick7Click(TObject *Sender);
        void __fastcall pnlJoystick8Click(TObject *Sender);
        void __fastcall pnlJoystick9Click(TObject *Sender);
        void __fastcall pnlJoystick10Click(TObject *Sender);
        void __fastcall rgJoystickEnabledChange(TObject *Sender,
          int ButtonIndex);
        void __fastcall btnMoveT1Click(TObject *Sender);
        void __fastcall btnMoveT1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMoveT1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardT1Click(TObject *Sender);
        void __fastcall btnBackwardT1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnBackwardT1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall imWaferMapMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall tbZoomChange(TObject *Sender);
        void __fastcall cbWaferMapClick(TObject *Sender);
        void __fastcall btnGenerateMapClick(TObject *Sender);
        void __fastcall btnAlignerGPIOClick(TObject *Sender);
        void __fastcall btnRobotGPIOClick(TObject *Sender);
        void __fastcall btnYuanliSendClick(TObject *Sender);
        void __fastcall btnYunliReConnectClick(TObject *Sender);
        void __fastcall ssYuanliSocketClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ssYuanliSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall rgYuanliCommandSetClick(TObject *Sender);
        void __fastcall csYuanliSocketConnecting(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csYuanliSocketDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csYuanliSocketRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csYuanliSocketConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csYuanliSocketError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall btnYuanliConnectClick(TObject *Sender);
        void __fastcall cbCCDFullImageChange(TObject *Sender);
        void __fastcall tbZoomMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall sbWaferMapMouseWheelDown(TObject *Sender,
          TShiftState Shift, TPoint &MousePos, bool &Handled);
        void __fastcall sbWaferMapMouseWheel(TObject *Sender,
          TShiftState Shift, int WheelDelta, TPoint &MousePos,
          bool &Handled);
        void __fastcall pnlMovingClick(TObject *Sender);
        void __fastcall btnWaferCenterClick(TObject *Sender);
        void __fastcall ssSECSSocketClientConnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ssSECSSocketClientDisconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ssSECSSocketClientError(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall ssSECSSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnSECSReConnectClick(TObject *Sender);
        void __fastcall Label523Click(TObject *Sender);
        void __fastcall rgSecsCommandSetClick(TObject *Sender);
        void __fastcall btnSECSSendClick(TObject *Sender);
        void __fastcall btnWaferChipClick(TObject *Sender);
        void __fastcall btnSetWPosition1Click(TObject *Sender);
        void __fastcall btnSetWPosition2Click(TObject *Sender);
        void __fastcall btnSetWPosition3Click(TObject *Sender);
        void __fastcall btnSetWPosition4Click(TObject *Sender);
        void __fastcall btnToWPosition1Click(TObject *Sender);
        void __fastcall btnToWPosition2Click(TObject *Sender);
        void __fastcall btnToWPosition3Click(TObject *Sender);
        void __fastcall btnToWPosition4Click(TObject *Sender);
        void __fastcall btnRunTestClick(TObject *Sender);
        void __fastcall tmLoadPort2ORGNTimer(TObject *Sender);
        void __fastcall tmLoadPort1ORGNTimer(TObject *Sender);
        void __fastcall tmAlignerORGNTimer(TObject *Sender);
        void __fastcall btnRealCenterPositionClick(TObject *Sender);
        void __fastcall btnToRealCenterPositionClick(TObject *Sender);
        void __fastcall btnFindCenterClick(TObject *Sender);
        void __fastcall btnSetUpClick(TObject *Sender);
        void __fastcall btnSetDownClick(TObject *Sender);
        void __fastcall btnSetLeftClick(TObject *Sender);
        void __fastcall btnSetRightClick(TObject *Sender);
        void __fastcall btnSetCenterClick(TObject *Sender);
        void __fastcall btnToCenterPositionClick(TObject *Sender);
        void __fastcall btnRorzeAlignerEnableClick(TObject *Sender);
        void __fastcall btnRorzeRobotEnableClick(TObject *Sender);
        void __fastcall btnRorzeLoadPort1EnableClick(TObject *Sender);
        void __fastcall btnRorzeLoadPort2EnableClick(TObject *Sender);
        void __fastcall btnMeasureClick(TObject *Sender);
        void __fastcall pnlSECSAlarmCodeClick(TObject *Sender);
        void __fastcall btnFocusDoneClick(TObject *Sender);
        void __fastcall mnSetMeasurePointClick(TObject *Sender);
        void __fastcall mnToMeasurePointClick(TObject *Sender);
        void __fastcall btnMeasureStopClick(TObject *Sender);
        void __fastcall pnlAlignerErrorCode1Click(TObject *Sender);
        void __fastcall pnlRobotErrorCode1Click(TObject *Sender);
        void __fastcall pnlLoadPortErrorCode1Click(TObject *Sender);
        void __fastcall pnlLoadPort2ErrorCode1Click(TObject *Sender);
        void __fastcall btnJoystickSaveAIClick(TObject *Sender);
        void __fastcall btnSaveAlarmParameterClick(TObject *Sender);
        void __fastcall btnTestClick(TObject *Sender);
        void __fastcall btnTestCloseClick(TObject *Sender);
        void __fastcall pnlTestMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall pnlTestMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall pnlTestMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnRobotCLMPClick(TObject *Sender);
        void __fastcall btnRobotUCLMClick(TObject *Sender);
        void __fastcall pnlWidthValueClick(TObject *Sender);
        void __fastcall tmPinLiftUpTimer(TObject *Sender);
        void __fastcall tmPinLiftDownTimer(TObject *Sender);
        void __fastcall btnDotMapClick(TObject *Sender);
        void __fastcall btnMapOutputClick(TObject *Sender);
        void __fastcall cbFontDisplayClick(TObject *Sender);
        void __fastcall imWaferMapDblClick(TObject *Sender);
        void __fastcall imWaferMapMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnMapAdjustClick(TObject *Sender);
        void __fastcall btnLoadPort1LockClick(TObject *Sender);
        void __fastcall btnLoadPort1UnlockClick(TObject *Sender);
        void __fastcall btnLoadPort1CarrierDockClick(TObject *Sender);
        void __fastcall btnLoadPort1CarrierUnDockClick(TObject *Sender);
        void __fastcall btnLoadPort2LockClick(TObject *Sender);
        void __fastcall btnLoadPort2UnlockClick(TObject *Sender);
        void __fastcall btnLoadPort2CarrierDockClick(TObject *Sender);
        void __fastcall btnLoadPort2CarrierUnDockClick(TObject *Sender);
        void __fastcall btnAlignerGPRSClick(TObject *Sender);
        void __fastcall btnAlignerCrashClick(TObject *Sender);
        void __fastcall btnAllCancelClick(TObject *Sender);
        void __fastcall Panel129Click(TObject *Sender);
        void __fastcall tmAlatmTimer(TObject *Sender);
        void __fastcall rgWaferDegreeClick(TObject *Sender);
        void __fastcall btnLoadPort2DPRMClick(TObject *Sender);
        void __fastcall tmLP2DPRMTimer(TObject *Sender);
        void __fastcall tmLP1DPRMTimer(TObject *Sender);
        void __fastcall btnLoadPort1DPRMClick(TObject *Sender);
        void __fastcall btnWaferPositionClick(TObject *Sender);
        void __fastcall btnWaferPositinoX1Click(TObject *Sender);
        void __fastcall btnWaferPositinoX2Click(TObject *Sender);
        void __fastcall btnWaferPositinoY1Click(TObject *Sender);
        void __fastcall btnWaferPositinoY2Click(TObject *Sender);
        void __fastcall btnWaferMoveLeftClick(TObject *Sender);
        void __fastcall btnWaferMoveRearClick(TObject *Sender);
        void __fastcall btnWaferMoveCenterClick(TObject *Sender);
        void __fastcall btnWaferMoveRightClick(TObject *Sender);
        void __fastcall btnWaferMoveFrontClick(TObject *Sender);
        void __fastcall btnWaferDegreeClick(TObject *Sender);
        void __fastcall cbAlignerActiveClick(TObject *Sender);
        void __fastcall cbLoadPort2ActiveClick(TObject *Sender);
        void __fastcall cbLoadPort1ActiveClick(TObject *Sender);
        void __fastcall btnDieCenterClick(TObject *Sender);
        void __fastcall btnToWaferCenterClick(TObject *Sender);
        void __fastcall rgYuanliPointClick(TObject *Sender);
        void __fastcall tmDecodeSECSTimer(TObject *Sender);
        void __fastcall tmDoLoadUnloadTimer(TObject *Sender);
        void __fastcall tmAlignerToInPositionTimer(TObject *Sender);
        void __fastcall tmButtonDelayTimer(TObject *Sender);
        void __fastcall pcRecipeChange(TObject *Sender);
        void __fastcall pcSystemChange(TObject *Sender);
        void __fastcall Panel23Click(TObject *Sender);
        void __fastcall cbOffLineClick(TObject *Sender);
        void __fastcall tmAutoLoadWaferTimer(TObject *Sender);
        void __fastcall tmAutoUnloadWaferTimer(TObject *Sender);
        void __fastcall tmAutoUnloadTimer(TObject *Sender);
        void __fastcall tmAutoStartTimer(TObject *Sender);
        void __fastcall pnlWaferDegreeXClick(TObject *Sender);
        void __fastcall pnlWaferChuckInformationClick(TObject *Sender);
        void __fastcall pnlWaferDegreeYClick(TObject *Sender);
        void __fastcall btnLogDeleteClick(TObject *Sender);
        void __fastcall btnLocalClick(TObject *Sender);
        void __fastcall btnRemoteClick(TObject *Sender);
        void __fastcall pnlWaferAlignerInformation2Click(TObject *Sender);
        void __fastcall pnlWaferRobotInformation2Click(TObject *Sender);
        void __fastcall pnlWaferChuckInformation2Click(TObject *Sender);
        void __fastcall btnReadINFClick(TObject *Sender);
        void __fastcall cbNewModeClick(TObject *Sender);
        void __fastcall pcOPChange(TObject *Sender);
        void __fastcall btnZAdjustClick(TObject *Sender);
        void __fastcall btnZAdjustCancelClick(TObject *Sender);
        void __fastcall btnZAdjustOKClick(TObject *Sender);
        void __fastcall pnlWaferRobotInformationLow2Click(TObject *Sender);
        void __fastcall Label188Click(TObject *Sender);
        void __fastcall btnSystemConfigSaveClick(TObject *Sender);
        void __fastcall btnCassette2LoadClick(TObject *Sender);
        void __fastcall rgLoadPortSelectChange(TObject *Sender,
          int ButtonIndex);
        void __fastcall btnLiveClick(TObject *Sender);
        void __fastcall btnGrabClick(TObject *Sender);
        void __fastcall rgCCDSourceChange(TObject *Sender,
          int ButtonIndex);
        void __fastcall imVieworksMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall imCloseClick(TObject *Sender);
        void __fastcall btn12Edge1Click(TObject *Sender);
        void __fastcall btn12Edge2Click(TObject *Sender);
        void __fastcall btn12Edge3Click(TObject *Sender);
        void __fastcall btnTo12Edge1Click(TObject *Sender);
        void __fastcall btnTo12Edge2Click(TObject *Sender);
        void __fastcall btnTo12Edge3Click(TObject *Sender);
        void __fastcall btn8Edge1Click(TObject *Sender);
        void __fastcall btn8Edge2Click(TObject *Sender);
        void __fastcall btn8Edge3Click(TObject *Sender);
        void __fastcall btnTo8Edge1Click(TObject *Sender);
        void __fastcall btnTo8Edge2Click(TObject *Sender);
        void __fastcall btnTo8Edge3Click(TObject *Sender);
        void __fastcall btnTriggerTestClick(TObject *Sender);
        void __fastcall mnToLensTiltClick(TObject *Sender);
        void __fastcall btnOLS5000ConnectClick(TObject *Sender);
        void __fastcall csOLS5000Connect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csOLS5000Disconnect(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall csOLS5000Error(TObject *Sender,
          TCustomWinSocket *Socket, TErrorEvent ErrorEvent,
          int &ErrorCode);
        void __fastcall csOLS5000Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall btnOLS5000SaveClick(TObject *Sender);
        void __fastcall btnOLS5000DisconnectClick(TObject *Sender);
        void __fastcall btnOLS5000LogInClick(TObject *Sender);
        void __fastcall btnOLS5000RemoteClick(TObject *Sender);
        void __fastcall btnOLS5000WIZEXEClick(TObject *Sender);
        void __fastcall btnOLS5000RDWIZClick(TObject *Sender);
        void __fastcall btnOLS5000GETSTSClick(TObject *Sender);
        void __fastcall btnOLS5000SendClick(TObject *Sender);
        void __fastcall btnOLS5000LocalClick(TObject *Sender);
        void __fastcall cb45CrossLineClick(TObject *Sender);
        void __fastcall mn45NiUpClick(TObject *Sender);
        void __fastcall imVieworksMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall mn45NiDownClick(TObject *Sender);
        void __fastcall mn45CuUpClick(TObject *Sender);
        void __fastcall mn45CuDownClick(TObject *Sender);
        void __fastcall mn45SaveClick(TObject *Sender);
        void __fastcall mn45ClearClick(TObject *Sender);
        void __fastcall imVieworksDblClick(TObject *Sender);
        void __fastcall cb45FullImageClick(TObject *Sender);
        void __fastcall btnOLS5000ReConnectClick(TObject *Sender);
        void __fastcall cbResetBuzzerClick(TObject *Sender);
        void __fastcall btn45GainClick(TObject *Sender);
        void __fastcall btn45ResetClick(TObject *Sender);
        void __fastcall laWaferEmptyClick(TObject *Sender);
        void __fastcall laWaferExistClick(TObject *Sender);
        void __fastcall laWaferSelectClick(TObject *Sender);
        void __fastcall laWaferDoubleSlotClick(TObject *Sender);
        void __fastcall laWaferCrossSlotClick(TObject *Sender);
        void __fastcall laWaferProcessClick(TObject *Sender);
        void __fastcall laWaferFinishClick(TObject *Sender);
        void __fastcall laWaferErrorClick(TObject *Sender);
        void __fastcall btnSaveWaferColorClick(TObject *Sender);
        void __fastcall pnlLoopTestCountClick(TObject *Sender);
        void __fastcall pnlTestWaferCountClick(TObject *Sender);
        void __fastcall edSetValueKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall tmFindCenterTimer(TObject *Sender);
//
private:	// User declarations
public:		// User declarations

        __fastcall TMainForm(TComponent* Owner);
        __fastcall ~TMainForm();

        void __fastcall CheckPassword();

        AnsiString LicenseCode;
        AnsiString __fastcall GetPassword(int mode);
        AnsiString __fastcall GetPassword1();
        AnsiString __fastcall GetPassword2();

   long ResetValue;

   // 2016 1 26 - chc 同時讀取Heidenhain - Ch1
   // STX : 02 : Ctrl-B
   // ETX : 03 : Ctrl-C
   double TMainForm::ReadHH1();

   // 2016 2 15 - chc 建立Log檔名
   // 系統目錄
   AnsiString SystemDirectory;
   AnsiString LogDirectory;
   AnsiString LogFileName,ErrorLogFileName,SystemHelpFileName;
   AnsiString RecipeDirectory;
   AnsiString ExportDirectory;
   void __fastcall TMainForm::WriteSystemLog(AnsiString msg);

   // 2016 2 16 - chc Function
   void __fastcall TMainForm::WaitRoutine1(int sleepno);
   void __fastcall TMainForm::SetupMotion();
   // 記錄在move中, 不可以同時Continue move
   bool boolInAxisMove;
   // 連動
   bool boolJogMove;
   #define SYSTEM_INI_FILENAME                  "\\LaserMotion.ini"
   AnsiString SystemINIFilename;
   // 各軸資訊
   // X
   #define X_START_VEL         "X Start Vel"
   #define X_MAX_VEL           "X Max Vel"
   #define X_DISTANCE          "X Distance"
   #define X_TACC              "X Tacc"
   #define X_TDEC              "X Tdec"
   #define X_POSITION          "X Position"
   #define X_HOME_VEL          "X Home Vel"
   #define X_REVIEW_VEL        "X Review Vel"
   #define X_UP_LIMIT          "X Up Limit"
   #define X_LOW_DISTANCE      "X Low Distance"
   // Y
   #define Y_START_VEL         "Y Start Vel"
   #define Y_MAX_VEL           "Y Max Vel"
   #define Y_DISTANCE          "Y Distance"
   #define Y_TACC              "Y Tacc"
   #define Y_TDEC              "Y Tdec"
   #define Y_POSITION          "Y Position"
   #define Y_HOME_VEL          "Y Home Vel"
   #define Y_REVIEW_VEL        "Y Review Vel"
   #define Y_UP_LIMIT          "Y Up Limit"
   #define Y_LOW_DISTANCE      "Y Low Distance"
   // Z
   #define Z_START_VEL         "Z Start Vel"
   #define Z_MAX_VEL           "Z Max Vel"
   #define Z_DISTANCE          "Z Distance"
   #define Z_TACC              "Z Tacc"
   #define Z_TDEC              "Z Tdec"
   #define Z_POSITION          "Z Position"
   #define Z_HOME_VEL          "Z Home Vel"
   #define Z_REVIEW_VEL        "Z Review Vel"
   #define Z_UP_LIMIT          "Z Up Limit"
   #define Z_LOW_DISTANCE      "Z Low Distance"
   // T
   #define T_START_VEL         "T Start Vel"
   #define T_MAX_VEL           "T Max Vel"
   #define T_DISTANCE          "T Distance"
   #define T_TACC              "T Tacc"
   #define T_TDEC              "T Tdec"
   #define T_POSITION          "T Position"
   #define T_HOME_VEL          "T Home Vel"
   #define T_REVIEW_VEL        "T Review Vel"
   #define T_UP_LIMIT          "T Up Limit"
   #define T_LOW_DISTANCE      "T Low Distance"
   int XStartVel ,XMaxVel ,XDistance ,XPosition ,XHomeVel,XReviewVel;
   double XTacc,XTdec,XUpLimit,XLowDistance;
   int YStartVel ,YMaxVel ,YDistance ,YPosition ,YHomeVel,YReviewVel;
   double YTacc,YTdec,YUpLimit,YLowDistance;
   int ZStartVel,ZMaxVel,ZDistance,ZPosition,ZHomeVel,ZReviewVel;
   double ZTacc,ZTdec,ZUpLimit,ZLowDistance;
   int TStartVel ,TMaxVel ,TDistance ,TPosition ,THomeVel,TReviewVel;
   double TTacc,TTdec,TUpLimit,TLowDistance;

   // 2021 4 15 - chc APS
   // L
   #define L_START_VEL         "L Start Vel"
   #define L_MAX_VEL           "L Max Vel"
   #define L_DISTANCE          "L Distance"
   #define L_TACC              "L Tacc"
   #define L_TDEC              "L Tdec"
   #define L_POSITION          "L Position"
   #define L_HOME_VEL          "L Home Vel"
   #define L_REVIEW_VEL        "L Review Vel"
   #define L_UP_LIMIT          "L Up Limit"
   #define L_LOW_DISTANCE      "L Low Distance"
   int LStartVel ,LMaxVel ,LDistance ,LPosition ,LHomeVel,LReviewVel;
   double LTacc,LTdec,LUpLimit,LLowDistance;
   // W
   #define W_START_VEL         "W Start Vel"
   #define W_MAX_VEL           "W Max Vel"
   #define W_DISTANCE          "W Distance"
   #define W_TACC              "W Tacc"
   #define W_TDEC              "W Tdec"
   #define W_POSITION          "W Position"
   #define W_HOME_VEL          "W Home Vel"
   #define W_REVIEW_VEL        "W Review Vel"
   #define W_UP_LIMIT          "W Up Limit"
   #define W_LOW_DISTANCE      "W Low Distance"
   int WStartVel ,WMaxVel ,WDistance ,WPosition ,WHomeVel,WReviewVel;
   double WTacc,WTdec,WUpLimit,WLowDistance;

   #define MOTION_INFORMATION_SECTION           "Motion Information"
   #define BISS_INFORMATION_SECTION             "BiSS Information"
   #define HEIDENHAIN_INFORMATION_SECTION       "Heidenhain Information"
   void __fastcall TMainForm::ResultTitle();
   #define RESULT_FIELD_INDEX                0               // index
   #define RESULT_FIELD_WIDTH                1
   #define RESULT_FIELD_HEIGHT               2
   #define RESULT_FIELD_CX                   3
   #define RESULT_FIELD_CY                   4
   #define RESULT_FIELD_ANGLE                5
   #define RESULT_FIELD_SCALE                6
   #define RESULT_FIELD_SCORE                7
   void __fastcall TMainForm::AddsgResult(int index, int width, int height, int cx, int cy, double angle, double scale, double score);
   #define MEASURE_AUTO         0
   #define MEASURE_MANUAL       1
   #define MEASURE_EXTERNAL     2
   // 2019 12 12 - chc 由50改成500
   #define RECIPE_MAX           500
   #define RECIPE_INFORMATION_SECTION         "Recipe Information"
   #define RECICPE_NAME              "Name"
   #define MAX_ARRAY_ROW        25
   #define MAX_ARRAY_COL        25
   struct BASE_STRU       {
      int X,Y,Z;
   };
   struct AREA_STRU       {
      int X,Y,Z;
   };
   struct DOT_STRU       {
      int X,Y,Z;
      AnsiString Recipe;
      double Intensity;
      int Row;
      int Col;
   };
   struct RECIPE_STRU   {
      AnsiString Name;
      // Array/Die Size
      int ArrayWidth,ArrayHeight;
      int DieWidth,DieHeight;

      // 2016 7 13 - chc @#@# Array & array
      int Array1Width,Array1Height;
      int Array2Width,Array2Height;

      // 2016 8 3 - chc Wafer Size & Pattern/Aperture Position
      int WaferSize;
      int PatternPosition;
      int AperturePosition;

      // 2016 10 13 - chc Pattern position shift offset
      double PatternOffsetX,PatternOffsetY;
      // Laser Size
      double LaserSizeX,LaserSizeY;

      // 2019 7 15 - chc Base/Area/Dot information
      #define MAX_BASE_NO               2
      // 2019 12 12 - chc 由10改成20
      #define MAX_AREA_NO               20
      // 2019 12 12 - chc 由100改成1000
      #define MAX_DOT_NO                1000
      struct AREA_STRU AreaBuf[MAX_AREA_NO];
      struct DOT_STRU DotBuf[MAX_DOT_NO];
      struct BASE_STRU BaseBuf[MAX_BASE_NO];
      int AreaNo,DotNo;

      // 2019 12 9 - chc 加入: 儲存座標檔參數: 路徑, 檔名, 原點座標, 單位, 方向.
      #define KMF_PATH                  "kmf Path"
      #define KMF_FILENAME              "kmf Filename"
      #define KMF_X                     "kmf X"
      #define KMF_Y                     "kmf Y"
      #define KMF_UNIT                  "kmf Unit"
      #define KMF_DIRECTION             "kmf Direction"
      #define KMF_BOOL_DIRECTION        "kmf Bool Direction"
      AnsiString kmfPath,kmfFilename;
      int kmfX,kmfY,kmfUnit,kmfDirection;
      bool boolkmfDirection;

      // 2021 5 5 - chc 加入中心點
      int CenterX,CenterY;

      // 2021 6 16 - chc 加入DieSize
      double DieSizeX;
      double DieSizeY;
      double DieSizeGapX;
      double DieSizeGapY;

      // 2021 8 6 - chc 加入Wafer角度設定
      int Pos1X,Pos1Y;
      int Pos2X,Pos2Y;
      int Pos3X,Pos3Y;
      int Pos4X,Pos4Y;
      double XDegree,YDegree;
      int DieCenterX,DieCenterY;

      // 2023 1 28 - chc edY45Offset
      int Y45Offset;

   };
   struct RECIPE_STRU RecipeBuffer[RECIPE_MAX];

   int RecipeTotalNo,RecipeCurNo;
   AnsiString RecipeName;
   bool __fastcall TMainForm::DisplayRecipe(int no);
   bool __fastcall TMainForm::UpdateRecipe();
   bool __fastcall TMainForm::ReadRecipe(AnsiString rfname);
   bool __fastcall TMainForm::WriteRecipe();

   // 2016 10 14 - chc Recipe Select for Setting
   bool __fastcall TMainForm::DisplayRecipeSet(int no);

   //
   // Wait
   void __fastcall TMainForm::WaitTime(int ms);
   void TMainForm::GetTimeTic(long *time, short *millitm);
   AnsiString DatabaseDirectory;         // 資料庫目錄
   // 累進誤差值
   double AccurateValue;
   int BiSSErrorCount;
   #define DEVICE_MN            0
   #define DEVICE_NQC           1
   #define PRIORITY_OP          0
   #define PRIORITY_PE          1
   #define PRIORITY_AD          2
   #define PRIORITY_EE          3
   int PriorityLevel;
   #define PASSWORD_SECTION     "Password"
   #define USER_NUMS            "UserNums"
   #define USER                 "User"
   #define NAME                 "Name"
   #define LEVEL                "Level"
   #define PASSWORD             "Password"
   int UserNums;
   #define MAX_USER             30
   struct PASSWORD_STRU {
      AnsiString Name;
      AnsiString Level;
      AnsiString Password;

      // 2022 5 17 - chc 要有原始Password: UserList[].PasswordORG
      // => 暫不用
      //AnsiString PasswordORG;

   };
   struct PASSWORD_STRU UserList[MAX_USER];
   void __fastcall TMainForm::SwitchLevel();
   void __fastcall TMainForm::LoadUser();
   void __fastcall TMainForm::UserTitle();
   #define USER_FIELD_NO                  0               // No
   #define USER_FIELD_NAME                1               // Name
   #define USER_FIELD_PASSWORD            2               // Password
   #define USER_FIELD_LEVEL               3               // Level
   void __fastcall TMainForm::SaveUser();
   AnsiString SystemHelpFilename;
   #define SYSTEM_HELP_FILENAME         "\\Help.txt"

   // 2016 3 7 - chc Save Screen
   void __fastcall TMainForm::SaveWindowScreen(TForm *Form);
   int SaveBMPSerialNo;
   // 2020 3 11 - chc 改成1900*1141
   //#define MASTER_SCREEN_WIDTH                     1920
   //#define MASTER_SCREEN_HEIGHT                    1044
   #define MASTER_SCREEN_WIDTH                     1920
   #define MASTER_SCREEN_HEIGHT                    1045
   #define RESULT_OK               1
   #define RESULT_NG               2
   AnsiString InspectStartDateTime;
   AnsiString InspectEndDateTime;

   // 2016 3 31 - chc 讀取網路卡序號
   AnsiString MACAddress;
   AnsiString __fastcall GetMACAddress();

   // 2020 7 17 - chc Not Used
   //bool __fastcall CheckMACAddress();

   #define LICENSE_CODE                 "License Code"
   AnsiString LicenseCodeSet;
   bool ExitYes;

   // 2016 4 16 - chc Laser Motion for Apple
   void __fastcall TMainForm::SetupscA1300();
   // 定義Alarm Code
   struct ALARM_STRU    {
      bool boolCDA;
      bool boolVacuum;
      bool boolDoor;
      bool boolMotion;
      bool boolRobot;
      bool boolAlignBlow;
      bool boolAlignSuck;
      bool boolChuckBlow;
      bool boolChuck2Suck;
      bool boolChuck4Suck;
      bool boolChuck6Suck;
      bool boolAlignCCD;
      bool boolReviewCCD;
      bool boolAOICCD;
      bool boolAOILamp;
      bool boolThickness;
      bool boolDI;
      bool boolDO;
      bool boolEMC;
   };
   struct ALARM_STRU    AlarmStatus;
   void __fastcall TMainForm::UpdateAlarmStatus();
   void __fastcall TMainForm::GigaBuffer1(int ccdtype);
   void __fastcall TMainForm::GigaBuffer2(int ccdtype);
   void __fastcall TMainForm::GigaBuffer3(int ccdtype);
   void __fastcall TMainForm::GigaCapture1();
   void __fastcall TMainForm::GigaCapture2();
   void __fastcall TMainForm::GigaCapture3();
   void __fastcall TMainForm::CaptureGigaFrame1(int no, int mode);
   void __fastcall TMainForm::CaptureGigaFrame2(int no, int mode);
   void __fastcall TMainForm::CaptureGigaFrame3(int no, int mode);
   // 取像時間顯示
   long BaslerCaptureStartTimeAry[3],BaslerCaptureStopTimeAry[3],BaslerCaptureElapsedmsAry[3];
   short BaslerCaptureStartTickAry[3],BaslerCaptureStopTickAry[3];
   // 記錄Basler存檔中...
   bool boolInGigaSaveAry[3];
   // scA1300的影像顯示改由EImageBW8 - CPU效能問題!!!!
   EImageBW8 scA1300ImageAry[3];
   EROIBW8 scA1300ImageROIAry[3];
   EROIBW8 scA1300ImageMarkROIAry[3];
   EImageC24 usb_ImageAry[3];
   EROIC24 usb_ImageROIAry[3];
   EROIC24 usb_ImageMarkROIAry[3];

   // 2023 8 2 - chc 移到此處
   EImageC24 EImageAry;
   EROIC24 EImageAryROI;

   bool boolBaslerImageLoadedAry[3];
   bool boolBaslerGrabbedAry[3];
   int BaslerCaptureNoAry[3];
   long BaslerStartTimeAry[3],BaslerStopTimeAry[3],BaslerElapsedmsAry[3];
   short BaslerStartTickAry[3],BaslerStopTickAry[3];
   #define BASLER_CCD_BW                0
   #define BASLER_CCD_COLOR             1
   int BaslerCCDType[3];
   // _BaslerGigECameraParams.h
   //		PixelFormat_RGB8Packed,  //!<Sets the pixel format to RGB 8 Packed
   //		PixelFormat_BGR8Packed,  //!<Sets the pixel format to BGR 8 Packed
   //		PixelFormat_RGB8Planar,  //!<Sets the pixel format to RGB 8 Planar
   // PixelType.h(均為24Bits)
   //     PixelType_RGB8packed      = PIXEL_COLOR | PIXEL_BIT_COUNT(24) | 0x0014,
   //     PixelType_BGR8packed      = PIXEL_COLOR | PIXEL_BIT_COUNT(24) | 0x0015,
   //     PixelType_RGB8planar      = PIXEL_COLOR | PIXEL_BIT_COUNT(24) | 0x0021,
   int scA1300ShutterAry[3],scA1300GainAry[3],scA1300GrayAry[3];
   void __fastcall TMainForm::GetImageXY(int width,int height,int sx,int sy,int w,int h,int *x,int *y);
   AnsiString BaslerBitmapDirectory;
   AnsiString CCDSN;
   // 進行SetupMotion時間
   int SetupTimeCount;
   bool boolSetupTime;
   // 2016 4 17 - chc 移動Center Pattern區
   void __fastcall TMainForm::UpdateCenterDotPosition();
   // 2016 4 17 - chc Clear 標線
   #define TRANS_PARENT_COLOR  0x123456
   // 2016 4 17 - chc 畫出New尺規: imGrid
   void __fastcall TMainForm::DrawRuler();

   // 2016 4 17 - chc NCC
   bool __fastcall TMainForm::CheckNCCMatch();

   // 2019 11 29 - chc 改成BW
   //EImageC24 ProcessImage;
   //EROIC24 MatchImageROI;
   //EImageC24 StdImage;
   EImageBW8 ProcessImage;
   EROIBW8 MatchImageROI;
   EImageBW8 StdImage;

   // 記錄作業時間長度
   long NCCStartTime,NCCStopTime,NCCElapsedms;
   short NCCStartTick,NCCStopTick;

   // 2016 11 13 - chc 由內到外搜尋: sno為單邊Pattern數量, 固範圍為sno*PatternWidth,sno*PatternHeight
   //bool __fastcall TMainForm::DoNCCMatch();
   // 2019 7 19 - chc 加入patternfname
   //bool __fastcall TMainForm::DoNCCMatch(int sno,int stdwidth,int stdheight);
   bool __fastcall TMainForm::DoNCCMatch(int sno,int stdwidth,int stdheight, AnsiString patternfname);

   int MarkCenterX,MarkCenterY;

   // 2021 4 15 - chc 6軸X/Y/Z/T/L/W
   #define MAX_AXIS_NO        6

   struct MOTION_STRU   {
      int StartVel,MaxVel,Distance,Position,HomeVel,ReviewVel,UpLimit,HomeMode;
      bool ORGLogic;
      double Tacc,Tdec;
      // Home補償量(僅用於Z軸)
      int HomeOffset;
      // Low Distance(慢速用)
      int LowDistance;
   };
   struct MOTION_STRU   MotionParameter[MAX_AXIS_NO];
   // 55 - 上, 56 - 下, 57 - 左, 58 - 右, 59 - 順, 60 - 逆
   bool boolUpMove,boolDownMove,boolLeftMove,boolRightMove,boolCWMove,boolCCWMove;
   #define JOG_LOW_SPEED        0
   #define JOG_MIDDLE_SPEED     1
   #define JOG_HIGH_SPEED       2
   int JogSpeed;
   int CurrentAxisNo;
   bool boolLampStatus;
   // 2016 4 18 - chc Motion Protect
   void __fastcall TMainForm::MotionStatus(bool mode);
   // 2016 4 18 - chc 是否執行過Home? - boolHomeDone
   void __fastcall TMainForm::SetMotionStatus();
   // 是否執行過Home?
   bool boolHomeDone;
   // 分配軸
   #define X_AXIS          3
   #define Y_AXIS          1
   #define Z_AXIS          2
   #define T_AXIS          0
   #define Z1_AXIS         0
   #define L_AXIS          4
   #define W_AXIS          5

   // 記錄各軸Home Position
   int XHomePosition,YHomePosition;
   int XHome,YHome;
   AnsiString AxisName;
   void __fastcall TMainForm::MoveMouseUp();
   void __fastcall TMainForm::BackwardMouseUp();
   // 2016 4 18 - chc 播放音效
   void __fastcall TMainForm::AlarmSound();
   #define DI_X_FORWARD            0x01
   #define DI_X_BACKWARD           0x02
   #define DI_Y_FORWARD            0x04
   #define DI_Y_BACKWARD           0x08
   #define DI_Z_FORWARD            0x10
   #define DI_Z_BACKWARD           0x20
   #define DI_T_FORWARD            0x40
   #define DI_T_BACKWARD           0x80
   #define DI_RESERVE_BIT8         0x100
   #define DI_RESERVE_BIT9         0x200
   #define DI_RESERVE_BIT10        0x400
   #define DI_RESERVE_BIT11        0x800
   #define DI_RESERVE_BIT12        0x1000
   #define DI_RESERVE_BIT13        0x2000
   #define DI_RESERVE_BIT14        0x4000
   #define DI_RESERVE_BIT15        0x8000

   #define DI_X_FORWARD_BIT_NO     0
   #define DI_X_BACKWARD_BIT_NO    1
   #define DI_Y_FORWARD_BIT_NO     2
   #define DI_Y_BACKWARD_BIT_NO    3
   #define DI_Z_FORWARD_BIT_NO     4
   #define DI_Z_BACKWARD_BIT_NO    5
   #define DI_T_FORWARD_BIT_NO     6
   #define DI_T_BACKWARD_BIT_NO    7
   #define DI_RESERVE_BIT8_NO      8
   #define DI_RESERVE_BIT9_NO      9
   #define DI_RESERVE_BIT10_NO     10
   #define DI_RESERVE_BIT11_NO     11
   #define DI_RESERVE_BIT12_NO     12
   #define DI_RESERVE_BIT13_NO     13
   #define DI_RESERVE_BIT14_NO     14
   #define DI_RESERVE_BIT15_NO     15

   // Output DO
   #define DO_DOOR_1_LOCK          0x01
   #define DO_RED_LAMP             0x02
   #define DO_ORANGE_LAMP          0x04
   #define DO_GREEN_LAMP           0x08
   #define DO_CDA                  0x10
   #define DO_VACUUM               0x20
   #define DO_HEPA                 0x40
   #define DO_BUZZER               0x80
   #define DO_DOOR_2_LOCK          0x100
   #define DO_X_RESET              0x200
   #define DO_Y_RESET              0x400
   #define DO_Z_RESET              0x800
   #define DO_T_RESET              0x1000
   #define DO_RESERVE_BIT13        0x2000
   #define DO_RESERVE_BIT14        0x4000
   #define DO_RESERVE_BIT15        0x8000
   int RotateLeftXPos,RotateRightXPos;
   int RotateLeftYPos,RotateRightYPos;
//
   void __fastcall TMainForm::LoadSystemParameter();
   // CCD Precision
   double CCDPrecision;

   // 2019 10 17 - chc 定義CCDPrecision1
   double CCDPrecision1;

   // 2016 6 3 - chc 2~5 Lens
   double CCDPrecision2;
   double CCDPrecision3;
   double CCDPrecision4;
   double CCDPrecision5;

   // 2016 7 14 - chc sixth lens definition
   double CCDPrecision6;

   // Move to Center
   bool boolMoveToCenter;
   // CCD X Direction
   bool boolCCDXDirection;
   // CCD Y Direction
   bool boolCCDYDirection;
   // Rotate Direction
   bool boolRotateDirection;

   // 2016 5 30 - chc 加入旋轉方向
   bool boolCCDTDirection;

   // DirectMove
   bool boolDirectMove;

   // 2016 5 25 - chc Joystick
   // 2020 1 5 - chc 不用
   bool boolJoystick;

   // Continue move
   bool boolContinueMove;
   // Speed
   int iSpeed;
   // Ruler Color
   int iRulerColor;
   // Cross Mark
   int iCrossMark;
   // Com Port: COM1
   int iComPort;

   // 2016 7 14 - chc WDI Baudrate
   int iBaudrate;

   // 2016 9 17 - chc Auto AF Off/On
   bool bAutoAFOffOn;

   int BaslerShutter,BaslerGain;
   // 由外部Joystick呼叫
   bool __fastcall TMainForm::MoveForwardJoystick();
   bool __fastcall TMainForm::MoveBackwardJoystick();
   // 記錄是否有開門或按下EMC
   bool boolDoorEMC;

   // 2016 5 10 - chc 記錄各軸是否運作中
   #define NO_MOVE              0
   #define FORWARD_MOVE         1
   #define BACKWARD_MOVE        -1
   int iAxisMove[MAX_AXIS_NO];
   bool boolInAIXMove;
   bool boolInAIYMove;
   int InAIMoveXSpeed;
   int InAIMoveYSpeed;

   // 2015 5 11 - chc 原始寫法
   void __fastcall TMainForm::CaptureGigaFrame1_old(int no, int mode);

   // 2016 5 20 - chc 加入Position: Center/Unload
   // 2023 8 3 - chc Center改成Tilt
   //int CenterX,CenterY,CenterZ,CenterT;
   int TiltX,TiltY,TiltZ,TiltT;

   // 2023 8 3 - chc Load改成Zero
   //int LoadX,LoadY,LoadZ,LoadT;
   int ZeroX,ZeroY,ZeroZ,ZeroT;

   int LastX,LastY,LastZ,LastT;

   // 2016 5 26 - chc 加入記錄: FindObj
   void __fastcall TMainForm::AddMatchData(int index);
   // Lasr Cneter
   int LaserCenterX,LaserCenterY;
   // 2016 5 26 - chc Display matched data
   void __fastcall TMainForm::DisplayMatchData(int index);
   // 2016 5 26 - chc Move to Center
   void __fastcall TMainForm::MoveMatchData();
   // 2016 5 26 - chc Rotate Before Move
   bool boolRotateBeforeMove;

   // 2016 5 30 - chc 存角度值
   double MarkAngle;

   // 2016 5 30 - chc Position
   int RelativePosition;

   // Original Position
   // 2023 8 3 - chc Original to Load
   //int OriginalX,OriginalY,OriginalZ,OriginalT;
   int LoadX,LoadY,LoadZ,LoadT;

   // 2016 6 2 - chc Rotate Within View
   bool boolRotateWithinView;

   // 2016 6 2 - chc Define total number of pulse of one circle of T Axis
   #define MAX_T_PULSE     3200000

   // 2016 6 3 - chc AI Min Vibrate
   double AIMinVibrate;
   // 2016 6 3 - chc GetLensPrecision
   double __fastcall TMainForm::GetLensPrecision();
   // 2016 6 3 - chc MatchNo & LensNo
   int MatchNo,LensNo;
   // 2016 6 4 - chc From Relative Move
   bool boolRelativeMove;
   int RelativeMoveX,RelativeMoveY;
   int GridPixel;
   // 2016 6 5 - chc Factor of Rotate Within View
   double JogFactor,ContinueFactor;

   #define min(a, b)  (((a) < (b)) ? (a) : (b))
   // Move - 3 Steps
   void __fastcall TMainForm::CWMove(int no);
   void __fastcall TMainForm::CCWMove(int no);
   void __fastcall TMainForm::LeftMove(int no);
   void __fastcall TMainForm::RightMove(int no);
   void __fastcall TMainForm::FrontMove(int no);
   void __fastcall TMainForm::RearMove(int no);
   void __fastcall TMainForm::UpMove(int no);
   void __fastcall TMainForm::DownMove(int no);

   // 2016 7 9 - chc User Position
   #define USER_INI_FILENAME                  "\\UserPosition.ini"
   AnsiString UserINIFilename;
   // Load User Position
   void __fastcall TMainForm::LoadUserPosition();
   #define USER_POSITION_SECTION           "User Position"
   struct LENS_STRU {
      AnsiString Mag;
      AnsiString Name;

      // 2016 9 21 - chc Magnification
      // Sets the objective lens magnification for a specified objective lens number.
      // The supported magnification values are: 2x, 5x, 7x, 10x, 20x, 50x, and 100x.
      int Magnification;

   };
   struct LENS_STRU     LensInfo[6];
   // pnlSelectedLens
   bool boolUpdateLastPosition;

   // Load Profile Parameter
   AnsiString LastProfile;
   // Save X/Y Center Position
   int XCenterPosition,YCenterPosition;

   // 2016 7 18 - chc Backlash control
   #define MOVE_NONE            0
   #define MOVE_FORWARD         1
   #define MOVE_BACKWARD        2
   int XLastPos,YLastPos;
   int XLastDir,YLastDir;
   int XForeReturnCount,XBackReturnCount;
   int YForeReturnCount,YBackReturnCount;

   // 2016 7 18 - chc Backlash control
   void __fastcall TMainForm::ResetBacklash();

   // 2016 7 19 - chc Backlash mode
   #define HD_BACKLASH_MODE             0
   #define PD_BACKLASH_MODE             1
   int BacklashMode;
   bool boolPDXForward,boolPDXBackward;
   bool boolPDYForward,boolPDYBackward;

   // 2016 9 15 - chc Library Function(Auto by Driver)
   #define SYSTEM_BACKLASH_MODE         2
   #define NONE_BACKLASH_MODE           3

   // 2016 7 20 - chc Point Move
   #define POINT_MAX_NO         1000
   int PointTotalNo,PointWorkNo;
   AnsiString PointDirectory;
   struct POINT_STRU    {
      double X,Y;

      // 2016 12 13 - chc 加入點位名稱
      AnsiString Name;

   };
   struct POINT_STRU PointBuffer[1000];

   // 2016 7 24 - chc Blinking
   bool boolStartState;
   bool boolAllHomeState;

   // 2016 7 27 - chc Check front door
   bool boolSystemStarted;

   // 2016 7 28 - chc 要Disable所有移動
   void __fastcall TMainForm::ToggleMove(bool mode);

   // 2016 8 3 - chc Illumination of each Lens
   int LEDPWMLEns[10];
   #define POSITION_CENTER              0
   #define POSITION_LEFT_UP             1
   #define POSITION_LEFT_DOWN           2
   #define POSITION_RIGHT_UP            3
   #define POSITION_RIGHT_DOWN          4
   int PatternPosition,AperturePosition;

   #define ARRAY_NO             0
   #define ARRAY_YES            1
   #define ARRAY_ORI            2
   int ArrayInfo[MAX_ARRAY_ROW][MAX_ARRAY_COL];

   // 2016 9 7 - chc Home Method
   #define ALLHOME_MODE9                0
   #define ALLHOME_ORG                  1
   int AllHomeMethod;

   // 2016 9 15 - chc Mode 1
   #define ALLHOME_MODE1                2

   // 2016 10 3 - chc Lasr Cneter Of Each Lens
   struct LENS_LASER_STRU     {
      int X,Y,Z,T;
      int LaserX,LaserY;

      // 2016 10 9 - chc add Z Limit
      int ZLimit;
   };
   struct LENS_LASER_STRU     LensPosition[6];

   // 2019 11 18 - chc 加入0.55/2x Lens
   struct LENS_LASER_STRU     LensPosition055X[6];
   struct LENS_LASER_STRU     LensPosition2X[6];

   // Laser Position
   #define LASER_INI_FILENAME                  "\\LaserPosition.ini"
   AnsiString LaserINIFilename;
   // Load Laser Position
   void __fastcall TMainForm::LoadLaserPosition(int lensno);
   // 2016 10 9 - chc Switch Lens & Laser Position
   // to LensNo
   void __fastcall TMainForm::SwitchLensLaser();

   // 2016 10 12 - chc AF state
   bool boolAFState;

   // 2016 10 12 - chc Update: edLens1LED
   void __fastcall TMainForm::UpdateLensLED(int lensno);

   // 2016 10 12 - chc Measure
   int MeasureState;
   int Mx1,My1,Mx2,My2;

   // 2016 10 12 - chc Save Laser Position
   #define LASER_INFORMATION_SECTION           "Laser Information"
   void __fastcall TMainForm::SaveLaserPosition(int lensno);

   // 2016 10 13 - chc XY-Aperture Ratio
   AnsiString LaserSizeINIFilename;
   double LaserSizeX,LaserSizeY;
   double LaserSizeXRatio,LaserSizeYRatio;
   double LaserSizeXAperture,LaserSizeYAperture;
   double LaserSizeXApertureRatio,LaserSizeYApertureRatio;

   // 2016 10 17 - chc @@##only to Aperture, not do back
   bool boolDoXAperture;
   bool boolDoYAperture;
   bool boolFromUser;

   // 2016 10 30 - chc CCD FOV vs CCDImage Area
   int CCDRangeX,CCDRangeY,CCDDx,CCDDy;
   // 2016 10 30 - chc Check Range
   void __fastcall TMainForm::CheckRange(int *sx, int *sy);
   #define LASER_CALIBRATION_MODE               "Laser Calibration Mode"
   int LaserCalibrationMode;
   bool boolSetLaserAperture;
   bool boolToSameSize;

   // 2016 11 3 - chc Variable
   // 2016 11 6 - chc set by XAperture/YAperture
   //int ApertureWidthCalibration;
   //int ApertureStdCalibration;
   //double ApertureSizeCalibration;
   int ApertureWidthCalibrationX,ApertureWidthCalibrationY;
   int ApertureStdCalibrationX,ApertureStdCalibrationY;
   double ApertureSizeCalibrationX,ApertureSizeCalibrationY;

   // 2016 11 4 - chc 加入Position的記錄, 否則長距離的轉正與單畫面的轉正方向相反!!
   int RotateLeftXCmd,RotateRightXCmd;
   int RotateUpYCmd,RotateDownYCmd;

   // 2016 11 17 - chc Sleep : for Recipe Run
   void __fastcall TMainForm::DelayRecipeRun(int no);

   // 2016 8 2 - chc Lens Position
   #define LENS_INI_FILENAME                  "\\LensPosition.ini"
   #define LENS_POSITION_SECTION              "Lens Position"
   AnsiString LensINIFilename;
   // Load Lens Position
   void __fastcall TMainForm::LoadLensPosition(int lensno);

   // 2016 11 28 - chc ImagingSource Name
   AnsiString ISCCDName, ISCCDSerialNo;
   // 2016 11 28 - chc Init ImagingSource CCD
   void __fastcall TMainForm::MakeDeviceSettings();

   // 2016 11 29 - chc Output DO
   #define STAGE_LOCK               0x01
   #define STAGE_VACUUM             0x02
   #define HIGH_SPEED_LIGHT         0x04

   // 2021 6 3 - chc Vacuum1 - Bit7
   #define STAGE_VACUUM1             0x80

   // 2016 12 12 - chc MaxTraceSpeed
   #define MAX_TRACE_SPEED              "Max Trace Speed"
   int MaxTraceSpeed;
   struct POINT_SET_STRU    {
      int X;
      int Y;
      AnsiString Name;
   };
   struct POINT_SET_STRU    PointSetBuffer[100];

   // 2016 10 16 - chc 加入訊息 : mmMeasure
   void __fastcall TMainForm::AddMeasureMessage(AnsiString msg);

   // 2016 12 18 - chc 軌跡作業時禁用/起用Motion
   void __fastcall TMainForm::SetMove(bool mode);

   // 2016 12 22 - chc Load Factor
   // Calibration.ini
   void __fastcall TMainForm::LoadCalibrationFactor();

   // 2016 12 22 - chc 取得Factor
   void __fastcall TMainForm::GetFactor(double *fx,double *fy,double x1, double y1, double x2, double y2);

   // 2016 12 30 - chc Speed ini
   #define SPEED_INI_FILENAME                  "\\SpeedParameter.ini"
   AnsiString SpeedINIFilename;
   #define SPEED_INFORMATION_SECTION           "Speed Information"
   // 2016 12 30 - chc Load Speed Parameter
   void __fastcall TMainForm::LoadSpeedParameter();

   // 2017 1 3 - chc 影像對焦演算法: Sobel
   // focus.ini
   #define FOCUS_INI_FILENAME                  "\\FocusParameter.ini"
   AnsiString FocusINIFilename;
   #define FOCUS_INFORMATION_SECTION           "Focus Information"
   // Load Focus Parameter
   void __fastcall TMainForm::LoadFocusParameter();

   // 2017 11 6 - chc Olympus NoseSwitch
   #define LENS_SECTION                         "Lens Section"
   #define LENS_BAUDRATE                        "Lens Baudrate"
   int LensBaudrate;

   // 2020 4 25 - chc ComPort設定值
   // Robot
   #define ROBOT_BAUDRATE                        "Robot Baudrate"
   #define ROBOT_COM_PORT                        "Robot Com Port"
   int RobotBaudrate;
   int RobotComPort;
   // LoadPort
   #define LOADPORT_BAUDRATE                        "LoadPort Baudrate"
   #define LOADPORT_COM_PORT                        "LoadPort Com Port"
   int LoadPortBaudrate;
   int LoadPortComPort;
   // Aligner
   #define ALIGNER_BAUDRATE                        "Aligner Baudrate"
   #define ALIGNER_COM_PORT                        "Aligner Com Port"
   int AlignerBaudrate;
   int AlignerComPort;

   // 2019 6 24 - chc LED Controller
   #define LED_PARAMETER_SECTION        "LED Parameter"
   #define LED2_CH1_VALUE                "LED2 CH1 Value"
   #define LED2_CH2_VALUE                "LED2 CH2 Value"
   #define LED2_CH3_VALUE                "LED2 CH3 Value"
   #define LED2_CH4_VALUE                "LED2 CH4 Value"
   #define LED_INI_FILENAME                    "\\LEDParameter.ini"
   AnsiString LEDINIFilename;
   int LED2CH1Value,LED2CH2Value,LED2CH3Value,LED2CH4Value;
   bool LampControlStatus2;
   // LED Lamp Active
   void __fastcall TMainForm::ActiveLampControl2();
   void __fastcall TMainForm::UpdateLampStatus2();
   void __fastcall TMainForm::SetLED2Value(int chno, int value);
   void __fastcall TMainForm::InitLampControl2();
   // 讀取亮度值
   void __fastcall TMainForm::ReadLEDValue();

   // 2019 7 9 - chc Close all Timer
   void __fastcall TMainForm::CloseAllTimer();
   double Intensity;

   // 2019 7 14 - chc CCD Position
   int CCDX,CCDY,CCDZ,CCDT;

   // 2019 12 5 - chc TXT Position
   // 2019 12 11 - chc 不需要
   //int TXTX,TXTY;

   // 2019 7 15 - chc GetBrukerLensPrecision
   double __fastcall TMainForm::GetOlympusLensPrecision();
   void __fastcall TMainForm::CCDToLens(int lensno, int mode);
   void __fastcall TMainForm::AreaPointTitle();

   void __fastcall TMainForm::WaitRun(int sleepno, int mode);
   #define RESULT_FIELD_INDEX                0               // index
   #define RESULT_FIELD_AREA                 1
   #define RESULT_FIELD_DOT                  2
   #define RESULT_FIELD_VISIONRECIPE         3
   #define RESULT_FIELD_RESULT               4
   #define RESULT_FIELD_TIME                 5
   // 2019 7 19 - chc 加入結果: resultcode 1-Z, 2-Intensity, 3-Measurement, 0-ok
   void __fastcall TMainForm::AddMeasureData(int recordno,int areano, int dotno, AnsiString visionrecipe, int resultcode,long elapsedms);
   // 2019 7 24 - chc 設定Z Button Status
   void __fastcall TMainForm::SetZMoveStatus(bool mode);
   // 2019 8 4 - chc Database Name
   AnsiString DatabaseNameRun;

   // 2019 10 29 - chc 存檔的DatabaseName: DatabaseNameSave
   AnsiString DatabaseNameSave;

   // 2019 11 12 - chc 設定各軸RDY
   int XRDY,YRDY,ZRDY;
   // 2019 11 12 - chc Vision64
   bool boolVision64;
   int XSvon,YSvon,ZSvon;

   // 2019 11 18 - chc 也顯示在軸控頁面, 也要切換顯示值
   #define MMD_055X             0
   #define MMD_1X               1
   #define MMD_2X               2
   // 2019 11 18 - chc 也顯示在軸控頁面, 也要切換顯示值
   void __fastcall TMainForm::DisplayLensPosition();

   // 2019 11 26 - chc 軸控異常
   bool boolMotionError;

   EROIBW8 PatternROI;

   // 2019 12 3 - chc 也取消顯示
   void __fastcall TMainForm::DisVisibleLensData(int lensno);
   // 2019 12 3 - chc Offset & Alignment
   bool __fastcall TMainForm::FindOffsetAlignment();
   void __fastcall TMainForm::DelayTime(no);
   int OffsetXBase,OffsetYBase;
   int OffsetXArea,OffsetYArea;

   // 2019 12 5 - chc kmf file
   #define KMF_FIELD_INDEX                0               // index
   #define KMF_FIELD_ITEM                 1
   #define KMF_FIELD_X                    2
   #define KMF_FIELD_Y                    3
   #define KMF_FIELD_NX                   4
   #define KMF_FIELD_NY                   5

   // 2019 12 7 - chc 複製資料夾: pnlRecipeTypeRecipe to combRecipe->Text
   void __fastcall TMainForm::CopyRecipeFile();
   // 2019 12 7 - chc for test
   bool boolForTest;

   // 2019 12 11 - chc 清除點位數據表
   void __fastcall TMainForm::ClearDotArray();
   void __fastcall TMainForm::ClearAreaArray();
   #define DOT_FIELD_INDEX                0               // index
   #define DOT_FIELD_X                    1
   #define DOT_FIELD_Y                    2
   #define DOT_FIELD_Z                    3
   #define DOT_FIELD_INTENSITY            4
   #define DOT_FIELD_VISIONRECIPE         5
   #define DOT_FIELD_LENS                 6
   #define DOT_FIELD_MMD                  7

   // 2020 1 21 - chc 將Operator/SheetNo加入CSV
   void __fastcall TMainForm::AddItemToCSV();
   // 存檔的DatabaseName: DatabaseNameSave
   AnsiString DatabaseNameSaveMain;

   // 2020 2 12 - chc Joystick Active
   void __fastcall TMainForm::SetJoystickActive(bool flag);
   // 2020 2 12 - chc Joystick Active
   void __fastcall TMainForm::DoMoveX();
   void __fastcall TMainForm::DoBackwardX();
   void __fastcall TMainForm::DoMoveY();
   void __fastcall TMainForm::DoBackwardY();
   void __fastcall TMainForm::DoMoveZ();
   void __fastcall TMainForm::DoBackwardZ();

   // 2020 2 11 - chc Joystick參數儲存
   #define JOYSTICK_START                   "Joystick Start"
   #define JOYSTICK_STOP                    "Joystick Stop"
   int JoystickStart,JoystickStop;
   // 2020 2 11 - chc 夾板參數儲存
   void __fastcall TMainForm::LoadJoystick();

   bool boolMotionPowerOff;

   // 2020 2 16 - chc Save Protect
   #define SAFE_FRONT_OUT                   "Safe Front Out"
   #define SAFE_FRONT_IN                    "Safe Front In"
   #define SAFE_RIGHT_OUT                   "Safe Right Out"
   #define SAFE_RIGHT_IN                    "Safe Right In"
   #define SAFE_REAR_OUT                    "Safe Rear Out"
   #define SAFE_REAR_IN                     "Safe Rear In"
   #define SAFE_LEFT_OUT                    "Safe Left Out"
   #define SAFE_LEFT_IN                     "Safe Left In"
   int SafeFrontOut,SafeFrontIn;
   int SafeRightOut,SafeRightIn;
   int SafeRearOut,SafeRearIn;
   int SafeLeftOut,SafeLeftIn;
   void __fastcall TMainForm::LoadSafe();

   // 2020 2 16 - chc 記錄目前做連續移動中: 軸與移動方向(1/2: 正/反, 0-沒有移動)
   int MoveAxis, MoveDirection;
   bool MoveIgnore;
   int MoveIgnoreAxis,MoveIgnoreDirection;

   // 2020 2 28 - chc CCD
   bool boolCCD;
   // 2020 2 28 - chc 取消不顯示
   void __fastcall TMainForm::NonVisible();

   // 2020 3 10 - chc L: Up/Down
   int LUp,LDown,LUp1;
   #define L_UP                                 "L Up"
   #define L_UP1                                "L Up1"
   #define L_DOWN                               "L Down"
   #define T_OVER                               "T Over"

   // 2020 4 23 - chc 解真空高度
   int LVacuumOff;
   #define L_VACUUM_OFF                        "L Vacuum Off"

   // 2020 5 20 - chc L水平高度
   int LLevel;
   #define L_LEVEL                             "L Level"

   // 2020 3 7 - chc Robot
   bool boolRobotStatus,boolAlignerStatus,boolLoadPortStatus;
   void __fastcall TMainForm::UpdateRobotStatus();
   void __fastcall TMainForm::UpdateLoadPortStatus();
   void __fastcall TMainForm::UpdateAlignerStatus();
   bool __fastcall TMainForm::SetupEFEM();

   // Robot Recv
   void __fastcall TMainForm::AddRobotSendMessage(AnsiString msg);
   void __fastcall TMainForm::AddRobotRecvMessage(AnsiString msg);
   // LoadPort Recv
   void __fastcall TMainForm::AddLoadPortSendMessage(AnsiString msg);
   void __fastcall TMainForm::AddLoadPortRecvMessage(AnsiString msg);
   // Aligner Recv
   void __fastcall TMainForm::AddAlignerSendMessage(AnsiString msg);
   void __fastcall TMainForm::AddAlignerRecvMessage(AnsiString msg);

   bool __fastcall TMainForm::WaitRobotDone(timems);

   // 2020 4 14 - chc Robot點位
   bool __fastcall TMainForm::SendRobotPosCMD(int pot);

   // 2023 8 2 - chc LP1/LP2
   //void __fastcall TMainForm::UpdateCassetteState(int mode);
   void __fastcall TMainForm::UpdateCassetteState(int portno, int mode);

   void __fastcall TMainForm::UpdateLoadPortStatus_1();
   void __fastcall TMainForm::UpdateAlignerStatus_1();
   void __fastcall TMainForm::UpdateRobotStatus_1(int mode);
   bool __fastcall TMainForm::WaitLoadPortDone(timems);
   #define ROBOT_WAFER_UNKOWN           0
   #define ROBOT_WAFER_YES              1
   #define ROBOT_WAFER_NO               2
   int RobotWithWafer;
   //unsigned char LoadPortLED[8];
   void __fastcall TMainForm::UpdateLoadPortLED_1();
   bool __fastcall TMainForm::ChckChuckVacuumOn();
   bool __fastcall TMainForm::ChckChuckVacuumOff();

   // 2020 4 24 - chc Init ComPort
   void __fastcall TMainForm::InitRobotCom();
   void __fastcall TMainForm::InitLoadPortCom();
   void __fastcall TMainForm::InitAlignerCom();
   int __fastcall TMainForm::GetFirstNo();
   int __fastcall TMainForm::GetLastNo();
   int __fastcall TMainForm::GetNextNo(int cno);
   bool __fastcall TMainForm::CheckWithWafer(int cno);

   // 2020 4 27 - chc Robot是否已動作?
   bool boolRobot4401;

   // 2020 5 4 - chc 先做Robot ORGN(GP1/GP0) & 偵測pnlLoadPortS12是否為1?
   bool __fastcall TMainForm::BeforeLoadPortLoadUnload();

   bool boolLoadUnloadStatus;
   // 2020 5 4 - chc Read Aligner Parameters
   void __fastcall TMainForm::LoadAlignerParameter();
   // Aligner
   int AlignerDegree,AlignerDegreeOut;
   int AlignerSpeed;
   int AlignerType;
   // 2020 5 4 - chc 共用Routine
   void __fastcall TMainForm::SetLevel(bool boolset);

   // 2020 5 12 - chc 選擇角度: AlignmentDegreeMode
   #define ALIGNMENT_DEGREE_LOAD          1
   #define ALIGNMENT_DEGREE_UNLOAD        2
   int AlignmentDegreeMode;

   // 2020 5 12 - chc AutoLoad時指到下一片
   // In(no): 1-25
   // Out: 1-25(-1: None)
   int __fastcall TMainForm::ToNextWafer(int no);
   void __fastcall TMainForm::GreenLamp(bool mode);
   void __fastcall TMainForm::YellowLamp(bool mode);
   void __fastcall TMainForm::RedLamp(bool mode);
   void __fastcall TMainForm::Buzzer(bool mode);
   void __fastcall TMainForm::BlueLamp(bool mode);

   // 2020 5 14 - chc LoadPort Error Code
   void __fastcall TMainForm::PutLoadPortErrorCodeMsg();
   void __fastcall TMainForm::PutLoadPortInterLockMsg();
   void __fastcall TMainForm::PutAlignerCodeMsg();
   void __fastcall TMainForm::PutRobotErrorCodeMsg();
   // 2020 5 14 - chc 設定第一片
   void __fastcall TMainForm::SetFristWafer();

   // 2020 5 20 - chc Enable/Disable
   void __fastcall TMainForm::RobotButton();
   void __fastcall TMainForm::LoadPortButton(int mode);
   void __fastcall TMainForm::AlignerButton();

   // 2020 5 20a - chc 若HomeDone檢查Vacuum, CDA
   bool __fastcall TMainForm::CheckCDAVacuum();
   // 2020 5 20a - chc Error Log
   // ErrorLog.txt
   void __fastcall TMainForm::LoadErrorLog();
   void __fastcall TMainForm::AddErrorLog(AnsiString msg);
   void __fastcall TMainForm::SaveErrorLog();
   void __fastcall TMainForm::ClearErrorLog();

   // 2020 5 21 - chc 記錄是否開始做DIO
   bool boolDIO;

   // 2020 5 21 - chc 記錄Chuck有Wafer
   bool boolChuckWithWafer;
   // 2020 5 22 - chc 更新pbWafer
   void __fastcall TMainForm::UpdateProgress(int no);

   // 2020 6 22 - chc 維護模式
   void __fastcall TMainForm::ReadMaintenanceMode();
   #define MAINTENANCE_LIGHT       0x08
   // 開/關維修燈
   void __fastcall TMainForm::MaintenanceLight(bool mode);
   // 2020 6 22 - chc 要開靜電Bar及FFU
   void __fastcall TMainForm::StageBarFFU(bool mode);

   // 2020 8 12 - chc TSMC修改
   void __fastcall TMainForm::StageBar(bool mode);
   void __fastcall TMainForm::StageFFU(bool mode);
   void __fastcall TMainForm::EFEMFFU(bool mode);

   // 2020 7 14 - chc Stage門檢
   // DO0-On, 若DI13未On則不能作業
   void __fastcall TMainForm::CheckStageDoor();

   // 2020 7 15 - chc 記錄是否在Update?
   bool boolInMotionUpdate;

   // 2020 7 16 - chc ZLimit, ZOffset
   int ZLimit,ZOffset;
   #define Z_LIMIT                      "Z Limit"
   #define Z_OFFSET                     "Z Offset"

   // 2023 8 3 - chc Z1/Z+Z1 Limit
   int Z1Limit,ZZ1Limit,ZZ1Safe;
   #define Z1_LIMIT                     "Z1 Limit"
   #define ZZ1_LIMIT                    "ZZ1 Limit"
   #define ZZ1_SAFE                     "ZZ1 Safe"

   // 2020 7 16 - chc 取得Z限制下限
   int __fastcall TMainForm::GetZLimit();

   // 2020 7 17 - chc Robot/Chuck/Aligner has wafer?
   bool __fastcall TMainForm::BeforeUnload();

   // 2020 8 12 - chc TSMC修改
   bool boolPCDoor,boolPower,boolLeftMaintenanceDoor,boolRightMaintenanceDoor,boolInspectDoor,boolMaintenanceMode;
   bool boolRedLamp,boolBuzzer,boolEFEMError;

   // 2021 5 8 - chc 加入Olympus/SECS socket error
   bool boolYuanliSocket,boolSECSSocket;

   // 2021 4 11 - chc Rorze
   // LoadPort1 Message
   void TMainForm::AddLoadPort1Message(AnsiString msg);
   void TMainForm::AddLoadPort2Message(AnsiString msg);
   void TMainForm::AddAlignerMessage(AnsiString msg);
   AnsiString AlignerCmd;
   void __fastcall TMainForm::WaitDelayTime(int timedelay);
   int __fastcall TMainForm::WaitAlignerComplete(int mode, int timeout);
   bool boolAlignerInit;

   // Robot
   AnsiString sRobotCmd;
   void TMainForm::AddRobotMessage(AnsiString msg);
   bool boolRobotInit;
   AnsiString RobotCode1,RobotCode2,RobotErrorCode;
   // 記錄RobotState & RobotCommand
   AnsiString RobotCommand;
   int RobotMoveStateSave;
   // Robot動作中
   #define ROBOT_IDLE           0
   #define ROBOT_MOVING         1
   #define ROBOT_DONE           2
   #define ROBOT_RESET          3
   #define ROBOT_HOME           4
   #define ROBOT_HOME_MOVE      5
   int RobotMoveState;
   // 是否執行過Home?
   bool boolRobotDone;
   int __fastcall TMainForm::WaitRobotComplete(int mode, int timeout);
   // 第二片取完後會Timeout問題: SystemInfo.In.CurrentNo=1
   // 取片動作在5秒內會完成, 若超過7秒則看RobotCode1 / RobotCode2 = 11000 / 0000 表示已Done
   bool boolWaitSecondDone;
   // 定義Alarm Code
   // 點位: 1(LoadPort1-11)/2(LoadPort2-21/3(Aligner-1)/4(Chuck-6)
   // 2021 6 30 - chc 分取放片: ROBOT_HOME_PUT, ROBOT_HOME_GET
   //int __fastcall TMainForm::GetStageNo();
   int __fastcall TMainForm::GetStageNo(int mode);

   bool boolLoadPort1Init;
   bool boolLoadPort2Init;
   AnsiString LoadPort1Cmd;
   AnsiString LoadPort2Cmd;
   int __fastcall TMainForm::WaitLoadPort1Complete(int mode, int timeout);
   int __fastcall TMainForm::WaitLoadPort2Complete(int mode, int timeout);
   // Presence: 44
   // Placement: 45
   // Load: 42
   // UnLoad: 43
   // Manual: 46
   // Alarm: 47
   // Clamp: 48
   // Dock: 49
   #define LOADPORT_PRESENCE_BIT        44
   #define LOADPORT_PLACEMENT_BIT       45
   #define LOADPORT_LOAD_BIT            42
   #define LOADPORT_UNLOAD_BIT          43
   #define LOADPORT_MANUAL_BIT          46
   #define LOADPORT_ALARM_BIT           47
   #define LOADPORT_CLAMP_BIT           48
   #define LOADPORT_DOCK_BIT            49

   #define LOADPORT_PRESENCE_LEFT_BIT           18
   #define LOADPORT_PRESENCE_RIGHT_BIT          19
   #define LOADPORT_PRESENCE_MIDDLE_BIT         20

   // RFID
   void TMainForm::AddRFIDMessage(AnsiString msg);
   void __fastcall TMainForm::GetRFIDCheckcode(char *buf,char *code1,char *code2);
   void __fastcall TMainForm::InitRFIDCom();
   bool boolRFIDStatus[4];

   // 2021 4 11 - chc SetupEFEMSocket
   void __fastcall TMainForm::SetupEFEMSocket();

   // Yuanli Port
   int YuanliPort;
   // RFID ComPort
   int RFIDComPort;

   // 2021 4 19 - chc PCI-7856(APS_)
   void __fastcall TMainForm::AxisSVON();
   // 2021 4 19 - chc 先SERVO off, DO off 再 DO on, SERVO on
   bool __fastcall TMainForm::DOServoOnOff(int axisno, int cnt);
   int AlignerSize;
   // 2021 4 21 - chc 指定7/8/9/10何者為Enable/Disable
   int JoystickEnabledKey,JoystickEnabledMode;
   void __fastcall TMainForm::SetJoystickEnabledKey();
   void __fastcall TMainForm::SetJoystickEnabledName();
   // 2021 4 23 - chc 測試Load Big Image
   int ZoomW,ZoomH;
   void __fastcall TMainForm::LoadFromFile();
   // 2021 4 23 - chc 測試Load Big Image
   void __fastcall TMainForm::DrawBigImage();
   struct WAFER_STRU    {
      int X,Y,Dx,Dy;
      bool boolSet;
   };
   struct WAFER_STRU Wafer;
   void __fastcall TMainForm::InitWaferMap();
   bool boolEFEMStatus;
   bool boolCDAVacuum;
   // 2021 4 25 - chc Aligner上是否有Wafer?
   bool __fastcall TMainForm::IsAlignerWithWafer();
   bool __fastcall TMainForm::IsRobotWithWafer();
   bool __fastcall TMainForm::IsChuckWithWafer();
   // 2021 4 25 - chc Yuanli socket
   void TMainForm::AddYuanliMessage(AnsiString msg);

// Sockeet
#define CMD_MAX                 12
// to YUANLI: YuanLi, Init, SetRecipe, Mode, Start, InPos, Stop, Busy, Invalid
#define CMD_YUANLI              0
#define CMD_MODE                1
#define CMD_SET_RECIPE          2
#define CMD_INIT                3
#define CMD_START               4
#define CMD_STOP                5
#define CMD_BUSY                6
#define CMD_INVALID             7
#define CMD_INPOS               8

// 2021 12 18 - chc 傳送RFID(CST ID)
#define CMD_RFID                9

// to Motin: Motion, ReadRecipe, GetErr
// 2021 12 18 - chc 傳送RFID(CST ID)
//#define CMD_MOTION              9
//#define CMD_READ_RECIPE         10
//#define CMD_GET_ERR             11
#define CMD_MOTION              10
#define CMD_READ_RECIPE         11
#define CMD_GET_ERR             12

   AnsiString CmdSet[CMD_MAX];
   void __fastcall TMainForm::SetCmdSet();
   int __fastcall TMainForm::GetCmdSet(AnsiString cmd);
   void __fastcall TMainForm::Decode(AnsiString scmd, AnsiString *spar, int parcnt, int mode);
   void __fastcall TMainForm::SnedSocket(AnsiString str, int mode);
   bool __fastcall TMainForm::IsEFEMCDAVacuumError();
   void __fastcall TMainForm::LogInStatus(int no, char *dibuf);

// STAT, PortNo, PID, RC, CRCP, Stop, DateT
#define SECS_CMD_MAX               14
// to Motin: STAT, PortNo, PID, RC, CRCP, Stop, DateT
#define SECS_CMD_STAT              0
#define SECS_CMD_PTST              1
#define SECS_CMD_PIDN              2
#define SECS_CMD_RCMD              3
#define SECS_CMD_CRCP              4
#define SECS_CMD_STOP              5
#define SECS_CMD_DATE              6
// to SECS: oSTAT, oPTST, oPREV, oWIDR, oRCPC, oALRM, oSTWR
#define SECS_CMD_STAT_1            7
#define SECS_CMD_PTST_1            8
#define SECS_CMD_PREV              9
#define SECS_CMD_WIDR              10
#define SECS_CMD_RCPM              11
#define SECS_CMD_ALRM              12
#define SECS_CMD_STWR              13
   AnsiString SECSCmdSet[SECS_CMD_MAX];
   void __fastcall TMainForm::SendSECSSocket(AnsiString str, int mode);
   void __fastcall TMainForm::SetSECSCmdSet();
   int __fastcall TMainForm::GetSECSCmdSet(AnsiString cmd);
   void __fastcall TMainForm::DecodeSECS(AnsiString scmd, AnsiString *spar, int parcnt, int mode);
   void __fastcall TMainForm::AddSECSMessage(AnsiString msg);
   void __fastcall TMainForm::ssSECSClientReadTest(AnsiString cmd);
   void __fastcall TMainForm::DrawRowCol(int sx,int sy,int col,int row,int type, int factor);
   bool __fastcall TMainForm::GetBitValue(char *buf, int bitno);
   void __fastcall TMainForm::SetLoadPortPresence(int portno, bool mode);
   void __fastcall TMainForm::SetLoadPortPlacement(int portno, bool mode);
   void __fastcall TMainForm::SetLoadPortLoad(int portno, bool mode);
   void __fastcall TMainForm::SetLoadPortUnload(int portno, bool mode);
   void __fastcall TMainForm::SetLoadPortManual(int portno, bool mode);
   void __fastcall TMainForm::SetLoadPortAlarm(int portno, bool mode);
   void __fastcall TMainForm::SetLoadPortClamp(int portno, bool mode);
   void __fastcall TMainForm::SetLoadPortDock(int portno, bool mode);
   // 2021 4 29 - chc 4個W點位
   void __fastcall TMainForm::LoadWPosition();
   // RobotW.ini檔名與目錄名
   #define ROBOTW_INI_FILENAME             "\\RobotW.ini"
   AnsiString RobotWINIFilename;
   #define ROBOTW_PARAMETER_SECTION        "RobotW Parameter"
   #define MAX_W_POSITION              4
   int WPositionSet[MAX_W_POSITION];

   // 2021 5 3 - chc RealCenter Position
   int RealCenterX,RealCenterY,RealCenterZ,RealCenterT;
   bool __fastcall TMainForm::IsHeadTilt();
   bool __fastcall TMainForm::IsHeadHorizontal();
   bool boolSystemCDA,boolSystemVacuum;
   bool boolEFEMCDA,boolEFEMVacuum;
   void __fastcall TMainForm::ClearEdgeMark();

   // 0-Right, 1-Left, 2-Up, 3-Down
   // 2023 8 15 - chc 改成傳回xy
   //int __fastcall TMainForm::FindEdge(int mode);
   int __fastcall TMainForm::FindEdge(int mode, int *x, int *y);

   // BaslerCaptureNoAry[no]
   bool __fastcall TMainForm::WaitMoreFrame(int frameno, int timeout);

   #define ROBOT_STAGE_LP1            0
   #define ROBOT_STAGE_LP2            1
   #define ROBOT_STAGE_ALIGNER        2
   #define ROBOT_STAGE_STAGE          3
   #define ROBOT_ARM_UP               0
   #define ROBOT_ARM_LOW              1
   #define LOADPORT_1                 0
   #define LOADPORT_2                 1
   #define ROBOT_HOME_GET             0
   #define ROBOT_HOME_PUT             1
   #define RECIPE_CHANGE              0
   #define RECIPE_CREATE              1
   #define RECIPE_MODIFY              2
   #define RECIPE_DELETE              3
   #define STATUS_FETCH               0
   #define STATUS_STORE               1
   #define STATUS_RECEIVE             2
   #define STATUS_SEND                3
   #define STATUS_PROCESSEND          4

   // 2021 10 21 - chc 由Idle/Run/Down改成Init/Idle/Setup/Ready/Execution/Pause
   //#define EQ_STATUS_IDLE             0
   //#define EQ_STATUS_RUN              1
   //#define EQ_STATUS_DOWN             2
   #define EQ_STATUS_INIT             0
   #define EQ_STATUS_IDLE             1
   #define EQ_STATUS_SETUP            2
   #define EQ_STATUS_READY            3
   #define EQ_STATUS_EXECUTING        4
   #define EQ_STATUS_PAUSE            5

   #define WAFER_EXIST_NO             0
   #define WAFER_EXIST_YES            1
   //
   #define PORT_STATUS_LR             0
   #define PORT_STATUS_LC             1
   #define PORT_STATUS_MAP            2
   #define PORT_STATUS_PROC           3
   #define PORT_STATUS_LOTEND         4
   #define PORT_STATUS_UR             5
   #define PORT_STATUS_UC             6
   #define PORT_STATUS_CSTREAD        7
   // Size
   #define WAFER_SIZE_12       0
   #define WAFER_SIZE_8        1
   #define WAFER_SIZE_6        2
   #define WAFER_SIZE_NONE     -1
   // 2021 5 4 - chc SEC init
   void __fastcall TMainForm::InitSECSStatus();

   // 是否送出Command
   bool boolSendSCESCommand;
   bool boolSendYuanliCommand;

   struct WAFERINFO_STRU {
      AnsiString ID;
      int Priority;
      AnsiString RecipeName;
      int Status;
   };

   // 2023 8 2 - chc LP1/LP2
   //struct WAFERINFO_STRU WaferBuffer[25];
   struct WAFERINFO_STRU WaferBuffer[2][25];

   // 2023 8 1 - chc LP1/LP2
   //void __fastcall TMainForm::ClearWaferBuffer();
   void __fastcall TMainForm::ClearWaferBuffer(int portno);

   AnsiString sErrorCode;
         // 2021 5 5 - chc Error Control: 1-10000
         // 00 - System
         //      001 - Motion Error
         //      002 - CDA Error
         //      003 - Vacuum Error
         //      004 -
         // 01 - EFEM
         //      001 - Connect Error
         //      002 - CDA Error
         //      003 - Vacuum Error
         // 02 - Yuanli Socket
         // 03 - SECS Socket
         //      001 -
         // 04 - RFID
         //      001 - Connect Error
         //      002 - Read Error
   #define SYSTEM_ERROR_HEAD            "00"
   #define EFEM_ERROR_HEAD              "01"
   #define YUANLI_ERROR_HEAD            "02"
   #define SECS_ERROR_HEAD              "03"

   #define SYSTEM_MOTION_ERROR          "001"
   bool __fastcall TMainForm::GoRobotWAxis(int mode);
   AnsiString WorkingWaferID;
   int __fastcall TMainForm::WaitYuanliCmd(int mode);
   #define CMD_ACK_WAIT              0
   #define CMD_ACK_E                 1
   #define CMD_ACK_X                 2
   #define CMD_ACK_TIMEOUT           3
   int YuanliCmdStatus[CMD_MAX];
   bool boolInMeasure;
   // 2021 5 7 - chc YuanLi是否連線
   bool __fastcall TMainForm::YuanLiConnect();
   // from SECS Ack
   bool boolSECS_STAT,boolSECS_PTST,boolSECS_PREV,boolSECS_WIDR;
   bool boolSECS_RCPM,boolSECS_ALRM,boolSECS_STWR;
   bool __fastcall TMainForm::SECSConnect();
   // 更新中心偏移量: 先決定Recipe
   void __fastcall TMainForm::UpdateCenterOffset();
   int SimulatePoint;
   // 中斷量測作業
   bool boolDoMeasure;
   bool __fastcall TMainForm::StopMeasure();
   bool boolLP1CassetteMapping,boolLP2CassetteMapping;

   // 2021 5 26 - chc Joystick參數儲存
   #define AISPEED_START                   "AISpeed Start"
   #define AISPEED_CHANGE                  "AISpeed change"
   int AISpeedStart,AISpeedChange;
   #define BOOL_AISPEED                    "Bool AISpeed"
   bool boolAISpeed;

   // 2021 6 3 - chc Alarm
   void __fastcall TMainForm::LoadAlarmParameter();

   // 2021 6 9 - chc 加入中心點參數: CenterSize, CenterOffset
   #define CENTER_SIZE                     "Center Size"
   #define CENTER_OFFSET                   "Center Offset"
   int CenterSize,CenterOffset;
   #define CENTER_CNT                      "Center Cnt"
   int CenterCnt;
   // 2021 6 16 - chc 計算Die座標
   void __fastcall TMainForm::ComputeRowCol(int x,int y,int *row,int *col);

   // 2021 10 24 - chc 第一次呼叫InMeasure
   //bool __fastcall TMainForm::InMeasure(int row,int col);
   bool __fastcall TMainForm::InMeasure(int row,int col, bool first);

   AnsiString __fastcall TMainForm::GetPasswordCode(AnsiString pwd);

   #define LOADPORT_LOCK_BIT       20
   #define LOADPORT_UNLOCK_BIT     21
   // 2021 6 24 - chc 寫入Recipe Name: 切換時就寫入更新
   void __fastcall TMainForm::SaveRecipeName();
   #define RECIPE_NAME          "Recipe Name"

   // 2021 6 30 - chc 監看Aligner
   bool boolAlignerMonitor;

   // 2021 8 11 - chc 指定點
   bool __fastcall TMainForm::InSelect(int row,int col);

   // 2021 8 24 - chc XY斜率校正
   bool __fastcall TMainForm::InCenterDie(int row,int col);

   // 2021 12 15a - chc XY斜率校正
   bool __fastcall TMainForm::InCenterDie1(int row,int col);

   // 2021 10 26 - chc 分mode: 1-(col,row)to(X,Y), 2-(X,Y)to(col,row)
   //void __fastcall TMainForm::GetAdjustXY(int mx, int my, int *nx,int *ny);
   void __fastcall TMainForm::GetAdjustXY(int mx, int my, int *nx,int *ny, int mode);

   // 2021 9 11 - chc 加速: MOVE_WAIT
   #define MOVE_WAIT            0
   #define MOVE_NOWAIT          1

   // 2021 9 15 - chc 將灰階量改成參數: WaferEdgeGray
   int WaferEdgeGray;
   // SECS Alarm Code/Message
   int SECSAlarmCode,SECSAlarmLevel,SECSAlarmOccur;
   AnsiString SECSAlarmMessage;
   void __fastcall TMainForm::SetSECSAlarm(int code,int resetset,int level,AnsiString mmessage);

   // 2023 8 6 - chc 切換CCD時做Z補償
   bool boolToLensZCompensation;

   // 2021 9 16 - chc Alarm
   #define ROBOT_ALARM_ORGN             0
   #define ROBOT_ALARM_MOTOR_STALL      1
   #define ROBOT_ALARM_SENSOR           2
   #define ROBOT_ALARM_DRIVER           3
   #define ROBOT_ALARM_WAFER_FALL       4
   #define ROBOT_ALARM_FAN              5
   #define ROBOT_ALARM_ENCODER          6
   #define ROBOT_ALARM_POWER            7
   #define ROBOT_ALARM_OVER_HEAT        8
   #define ROBOT_ALARM_CABLE            9
   #define ROBOT_ALARM_COMMUNICATION    10
   #define ROBOT_ALARM_RETAINING        11
   // Aligner
   #define ALIGNER_ALARM_ORGN             0
   #define ALIGNER_ALARM_MOTOR_STALL      1
   #define ALIGNER_ALARM_SENSOR           2
   #define ALIGNER_ALARM_COMMUNICATION    3
   #define ALIGNER_ALARM_DRIVER           4
   #define ALIGNER_ALARM_POWER            5
   #define ALIGNER_ALARM_OVER_HEAT        6
   #define ALIGNER_ALARM_NOTCH_DETECT     7
   #define ALIGNER_ALARM_CHUCK            8
   // LoadPort
   #define LOADPORT_ALARM_ORGN             0
   #define LOADPORT_ALARM_MOTOR_STALL      1
   #define LOADPORT_ALARM_SENSOR           2
   #define LOADPORT_ALARM_COMMUNICATION    3
   #define LOADPORT_ALARM_DRIVER           4
   #define LOADPORT_ALARM_MAPPING_SENSOR   5
   #define LOADPORT_ALARM_FAN              6
   #define LOADPORT_ALARM_POWER            7
   #define LOADPORT_ALARM_OVER_HEAT        8
   #define LOADPORT_ALARM_CABLE            9
   #define LOADPORT_ALARM_CARRY_IN         10
   #define LOADPORT_ALARM_CARRY_OUT        11
   #define LOADPORT_ALARM_BUSY_TIMEOUT     12
   bool boolCSTWithoutWafer;
   bool boolChuckWithoutWafer;
   bool boolAlignerWithoutWafer;
   bool boolWAxisPositionError;
   bool boolChuckPositionError;
   bool boolWaferNotSpecified;
   bool boolCSTWithWafer;
   bool boolChuckWithWaferError;
   bool boolAlignerWithWafer;
   bool boolCenterPointError;
   bool boolImageRecognitionError;
   bool boolWorkflowError;
   bool boolPerformUnauthorizedFunction;

   // 2021 9 23b - chc SetButtonDelay
   void __fastcall TMainForm::SetButtonDelay(int no);

   // 2021 10 6 - chc 顯示目前Table所在的Die Col/Row
   void __fastcall TMainForm::UpdateDiePosition();

   // 2021 10 21 - chc 送出Status: Init/Idle/Setup/Ready/Execution/Pause
   void __fastcall TMainForm::SendSECSStatus(int status);

   // 2021 10 28 - chc Log刪除天數
   #define LOG_RESERVED_DAY              "Log Reserved Day"
   int LogReservedDay;

   // 2021 11 12 - chc 記錄目前是否在做取退片?
   bool boolInLoadWafer,boolInUnloadWafer;
   // 2021 11 12 - chc 確認系統內是否有Wafer
   bool __fastcall TMainForm::WaferInSystem();

   // 2021 12 18 - chc Load Mode Parameter
   void __fastcall TMainForm::LoadModeParameter();

   // 2202 2 13 - chc RCMD: 1-Cancel, 2-Abort SECSRemoteCommand
   #define SECS_REMOTE_NONE             0
   #define SECS_REMOTE_CANCEL           1
   #define SECS_REMOTE_ABORT            2
   #define SECS_REMOTE_MAPPING          3
   int SECSRemoteCommand;

   // 2022 5 17 - chc 是PE: 固定10秒後切換到操作員等級
   int ChangePriorityCount;

   // 2023 6 5 - chc init ViewWorks CCD
   // 2023 8 6 - chc 另建module
   //void __fastcall TMainForm::InitVworks();

   // 2023 7 19 - chc alarm Log
   // AlarmLog.txt
   void __fastcall TMainForm::LoadAlarmLog();
   void __fastcall TMainForm::AddAlarmLog(AnsiString msg);
   AnsiString AlarmLogFileName;

   // 2023 7 25 - chc System Confoig
struct EDGE_STRU {
   int X,Y,Z;
   int Intensity;
};
struct SYSTEM_STRU {
   struct EDGE_STRU W12Edge[3];
   struct EDGE_STRU W8Edge[3];
   // Lamp Life
   int LampLife;
   // 加入SECS Port: edSECSPort
   int SECSPort;
};
   struct SYSTEM_STRU SystemConfig;
   AnsiString SystemConfigName;
   void __fastcall TMainForm::LoadSystemConfigParameters();

   // 2023 7 31 - chc 偵測pnlLoadPortS12是否為1?
   bool __fastcall TMainForm::BeforeLoadPortLoadUnloadFun(int portno);

   // 2023 8 1 - chc Vieworks CCD
   //EImageC24 EImageAry;
   //EROIC24 EImageAryROI;
   // 2023 8 6 - chc 另建module
   //void __fastcall TMainForm::SetupVieworksView();
   //void __fastcall TMainForm::DisplayVCCD(int cnt);

   void __fastcall  TMainForm::Set12EdgePosition(int no);
   void __fastcall  TMainForm::To12EdgePosition(int no);
   void __fastcall  TMainForm::To8EdgePosition(int no);
   // 2023 8 4 - chc 取得Z安全高度
   int __fastcall TMainForm::GetZZ1Safe(int axisno);
   void __fastcall  TMainForm::Set8EdgePosition(int no);
   TColor WaferColor_Select;
   TColor WaferColor_No;
   TColor WaferColor_Exist;
   TColor WaferColor_Process;
   TColor WaferColor_Double;
   TColor WaferColor_Cross;
   TColor WaferColor_Error;
   TColor WaferColor_Done;

   // 2023 8 8 - chc OLS5000 socket
   void TMainForm::AddOLS5000Message(AnsiString msg);
   void __fastcall TMainForm::InitOLS5000();
   bool boolOLS5000;
   void __fastcall TMainForm::LoadOLS5000Parameter();

   #define STAGE_ROBOT_UP            0
   #define STAGE_ROBOT_DOWN          1
   #define STAGE_ALIGNER             2
   #define STAGE_CHUCK               3
   #define STAGE_MAX_NO              4
   struct STAGE_STRU {
      bool boolWithWafer;
      int SlotNo;
      int FoupNo;
      AnsiString WaferID;
   };
   struct STAGE_STRU  StageInformation[STAGE_MAX_NO];
   void __fastcall TMainForm::InitStageInformation();
   AnsiString WaferColorINIFilename;
   #define WAFERCOLOR_INI_FILENAME             "\\WaferColor.ini"
   TColor WaferColor[8];
   #define WAFERCOLOR_PARAMETER_SECTION        "WaferColor Parameter"
   void __fastcall TMainForm::LoadWaferColor();

   // 2023 8 14 - chc 三點定中心
   bool __fastcall TMainForm::FindCenter();
   // 暫不用
   //bool __fastcall TMainForm::FindEdgeFun(int no,int *retx,int *rety);
   void __fastcall TMainForm::CalculateCenter(int x1,int y1,int x2,int y2,int x3,int y3,int *rcx,int *rcy);


};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif
