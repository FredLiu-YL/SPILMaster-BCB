//---------------------------------------------------------------------------

#pragma hdrstop

#include "Motion.h"
#include "MainFrm.h"      f

// 2013 10 1 - chc Timer����
#include <time.h>
#include <sys\timeb.h>

// �n�[�J8154_bcb.lib & PCI-Dask_bcb.lib
#include "pci_8154.h"                           // PCI 8154
//#include "dask.h"                               // PCI 7396
extern bool boolMotion,boolDI,boolDO;

// 2013 5 15 - chc �]�wDelayTime
#define MOTION_SLEEP_TIME               0

// 2021 4 15 - chc APS
#define MOTION_MODE_8154        0
#define MOTION_MODE_APS         1
extern int MotionMode;

I16 TotalCard;
I16 Card_Pci_8154_Status[16];
I16 Now_Max_Card_Pci_8154;
I16 ALL_Max_PCI_8154_Card;
I16 MotionStatusCode[MAX_AXIS_NO];

//constants definition
#define CardNumber	0
#define DIPort	Channel_P2A
#define Direction	INPUT_PORT

//variables definition
// DI
I16 cardIDDI = -1;
I16 err = 0;
U32 DIValue = 0;                                // returned DI value
I16 DIPortValue;
// DO: 32Bits�����: Low/High/LED�T�զ@96�I
#define DOPort	PORT_DO_LOW
I16 cardIDDO = -1;
U32 DOValue = 0;                                // DO value

// Motion State
extern bool boolMotionState;

// 2019 8 5 - chc �O�_�b�q����?
extern bool boolInRun;

// Joystick 55 - �W, 56 - �U, 57 - ��, 58 - �k, 59 - ��, 60 - �f
// 2013 2 23 - chc �n�bMainForm���ŧi
//bool boolUpMove,boolDownMove,boolLeftMove,boolRightMove,boolCWMove,boolCCWMove;
#define JOG_LOW_SPEED        0
#define JOG_MIDDLE_SPEED     1
#define JOG_HIGH_SPEED       2
// 2013 2 23 - chc �n�bMainForm���ŧi
//int JogSpeed;

// 2013 2 26 - chc ���`�b�O
int AxisErrorNo = -1;

// 2016 4 19 - chc APS PCI-7856
extern I32 BoardID, BoardName, BoardHSL, BoardMNET;
extern I32 Board7856;
extern I32 StartAxisNo, FirstAxisNo, TotalAxisNo;
extern char MNET_BUS, HSL_BUS;
extern bool bool_APS_Status;
extern bool bool_IO_Status;
extern I32 IO1_ID;
extern bool HSL_IO_InStatus[16];
extern unsigned int HSL_IO_OuStatus;
extern I32 input_IO1 = 0;
extern I32 AI_ID = 5;
extern double AIValue[16];

// 2016 6 2 - chc �]�w�ثe��m&����(x,y,t)
bool boolTMove = false;
int CurrentX,CurrentY,CurrentT;
int CurrentOX,CurrentOY;
double CurrentDegree;
double CurrentRadians;

// 2016 12 13 - chc fast speed
bool boolFastSpeed = false;

// 2021 3 22 - chc L/RX
extern I32 L_Axis;
extern I32 W_Axis;
extern bool bool_L_Status;
extern bool bool_RX_Status;
extern I32 StartAxisNo2, FirstAxisNo2, TotalAxisNo2;
#define EFEM_HIRATA             1
#define EFEM_RORZE              2
extern int EFEMMode;

// 2021 4 30 - chc �令MainForm global
extern int EFEMStatus;

// 2023 1 28 - chc edY45Offset
extern bool boolInMeasureRun;

//---------------------------------------------------------------------------
// Init Motion - PCI-8154
//#define X_AXIS          0
//#define Y_AXIS          1
//#define Z_AXIS          2
//#define T_AXIS          3
//#define L_AXIS          4
//#define W_AXIS          5
//---------------------------------------------------------------------------
void __fastcall InitMotion()
{
// Only for 8154
U16 CardID_InBit;
I16 RET = 666;
I16 i=0;
I16 AxisNum = 0;
I16 outmode;
I16 iptmode;
I16 direction;
I16 feedback;

I32 ret;
AnsiString fname,msg;

   // Message
   MainForm->WriteSystemLog(">Motion : Init");

   // EMC/Door Open Alarm Counter
   DoorCounter = -1;
   EMCCounter = -1;

   // 2021 4 15 - chc 8154 or APS_
   // APS(7856)
   // �U�b�̤j�t: 150�U/150�U/5�U/18�U/10�U/20�U
   if(MotionMode == MOTION_MODE_APS) {
      //---------------------------------------------------------------------------
      // Motion Status
      boolMotion = false;
      boolDI = false;
      boolDO = false;
      bool_APS_Status = true;
      if(APS_initial(&BoardID, 0) != 0){                                           // Initial Card, CardID is assigned by system.
         bool_APS_Status = false;
         MainForm->WriteSystemLog(">>Motion Initial����!");
      }
      else {
         MainForm->WriteSystemLog(">>Motion Initial���\, BoardID = " + IntToStr(BoardID));
         // �n�]�w��0, Ū�^��BaordID��1!!
         //BoardHSL = BoardID;
         //BoardMNET = BoardID;
         BoardHSL = 0;
         BoardMNET = 0;

         HSL_BUS = 0;
         MNET_BUS = 1;
         FirstAxisNo = 1500;
         StartAxisNo = 1500;
         FirstAxisNo2 = 1504;
         StartAxisNo2 = 1504;

         // Start HSL(Default : 1/2/0/0)
         // DIO: 16/16
         APS_set_field_bus_param(BoardHSL, HSL_BUS, 0x00, 1);                      // Half Duplex
         ret = APS_set_field_bus_param(BoardHSL, HSL_BUS, 0x01, 2);                // 6Mps(3M/6M/12M)
         if(ret != 0)
            MainForm->WriteSystemLog(">>APS_set_field_bus_param 0x01 Error");
         ret = APS_set_field_bus_param(BoardHSL, HSL_BUS, 0x02, 0);
         if(ret != 0)
            MainForm->WriteSystemLog(">>APS_set_field_bus_param 0x02 Error");
         APS_set_field_bus_param(BoardHSL, HSL_BUS, 0x03, 0);                      // Reset DO to Zero
         APS_set_field_bus_param(BoardHSL, HSL_BUS, 0x04, 7);                      // Error Count
         ret = APS_start_field_bus(BoardHSL, HSL_BUS, StartAxisNo);                // �Ұ�Bus

         // HSL Start Error
         if(ret != 0) {
            MainForm->WriteSystemLog(">>HSL_IO Start����! ret = " + IntToStr(ret) + "BoardHSL-HSLBUS-StartAxisNo: " + IntToStr(BoardHSL) + "-" + IntToStr(HSL_BUS) + "-" + IntToStr(StartAxisNo));
            bool_APS_Status = false;
            MainForm->pnl7856Status->Color = clRed;
            bool_IO_Status = false;
            MainForm->pnlDIOStatus->Color = clRed;
            MainForm->pnlAIStatus->Color = clRed;
         }
         // Start MNET & Load file
         else {


            MainForm->WriteSystemLog(">>HSL_BUS Start���\.");
            MainForm->pnlDIOStatus->Color = clLime;
            bool_IO_Status = true;
            MainForm->pnl7856Status->Color = clLime;
            MainForm->WriteSystemLog(">>Set APS: BoardMNET, MNET_BUS, StartAxisNo=" + IntToStr(BoardMNET) + "," + IntToStr(MNET_BUS) + "," + IntToStr(StartAxisNo));
            MainForm->pnlAIStatus->Color = clLime;
            // �]�wPolling
            boolDI = true;
            boolDO = true;
            IO1_ID = 1;                                                            // Switch Assign
            HSL_IO_OuStatus = 0x0;
            if(boolDI == true && boolDO == true) {

               // 2021 4 19 - chc ��Timer(2���)�Ұ�
               // => �٬O����
               MainForm->tmMotionPolling->Enabled = true;
               MainForm->WriteSystemLog(">Motion : DIO ok, Polling");

               // �]�w���t
               MainForm->rgSpeed->ItemIndex = JOG_MIDDLE_SPEED;
               MainForm->rgSpeedClick(MainForm);

               // 2021 4 11 - chc �nOn�~�|��DI13 On
               // 2021 5 5 - chc �ˬd: HSL_IO_OuStatus
               //if(MainForm->pnlStageLock->Color != clLime)
               //   MainForm->pnlStageLockClick(MainForm);
               // 2023 8 25 - chc ���oDI�A����l�]�w
               //if((HSL_IO_OuStatus & STAGE_LOCK) == 0) {
               //   MainForm->WriteSystemLog(">DO0��0, �j�1");
               //   HSL_IO_OuStatus |= STAGE_LOCK;
               //   MainForm->pnlStageLock->Color = clLime;
               //   APS_set_field_bus_d_output(BoardHSL, HSL_BUS, IO1_ID, HSL_IO_OuStatus);
               //}
               int hslret = APS_get_field_bus_d_input(BoardHSL, HSL_BUS, IO1_ID, &input_IO1);
               // Stage�W��Wafer?
               if((input_IO1 & STAGE_WAFER) != 0)
                  HSL_IO_OuStatus |= STAGE_VACUUM;
               // ����?
               if((input_IO1 & DOOR_LOCK) != 0) {
                  HSL_IO_OuStatus |= STAGE_LOCK;
                  MainForm->pnlStageLock->Color = clLime;
               }
               else {
                  MainForm->pnlStageLock->Color = clSilver;
               }
               APS_set_field_bus_d_output(BoardHSL, HSL_BUS, IO1_ID, HSL_IO_OuStatus);

            }
            // Set Transfer rate
            // 0/1/2/3 - 2.5M/5M/10M/20M
            ret = APS_set_field_bus_param(BoardMNET, MNET_BUS, PRF_TRANSFER_RATE, 2);
            if(ret != 0)
               MainForm->WriteSystemLog(">>Error APS_set_field_bus_param: " + IntToStr(ret));

            MainForm->WriteSystemLog("Board,Bus,Start= " + IntToStr(BoardMNET) + ","  + IntToStr(MNET_BUS) + "," + IntToStr(StartAxisNo));

            // Start Field bus
            ret = APS_start_field_bus(BoardMNET, MNET_BUS, StartAxisNo);
            if(ret != 0) {
               MainForm->WriteSystemLog(">>MNET_BUS Start����!");
               bool_APS_Status = false;
            }
            else {
               // X/Y/Z/T/L/RX
               MainForm->WriteSystemLog(">>MNET_BUS Start���\.");
               // MNET ModuleID = 0(Board ID=0, 10MHz)
               // Get First/Total Axis No
               ret = APS_get_field_bus_slave_first_axisno(BoardMNET, MNET_BUS, 0, &FirstAxisNo, &TotalAxisNo);
               if(ret != 0 || TotalAxisNo != 4 || FirstAxisNo != StartAxisNo) {
                  MainForm->WriteSystemLog(">>MNET_BUS(0) First-TotalŪ������!");
                  bool_APS_Status = false;
               }
               else {
                  MainForm->WriteSystemLog(">>MNET_BUS(0) First-TotalŪ�����\.");
                  // �]�wAxis No: 1500 ~ 1503, �����B���s��0-3
                  //X_Axis = 0;
                  //Y_Axis = 1;
                  //Z_Axis = 2;
                  //T_Axis = 3;
                  I32 axisno, boardid, portid, moduleid, ret1;
                  // Get Information
                  ret = APS_get_axis_info(FirstAxisNo, &boardid, &axisno, &portid, &moduleid);
                  msg.sprintf(">>MNET 0: First,Total,Boardid,Ansixno,Portid,Moduleid=%d,%d,%d,%d,%d,%d",FirstAxisNo,TotalAxisNo,boardid,
                                                axisno,portid,moduleid);
                  MainForm->WriteSystemLog(msg);
                  //2021/03/22 15:59:47:002->>MNET 0: First,Total,Boardid,Ansixno,Portid,Moduleid=1500,4,0,0,1,0
                  //                                  1500  4     0       0       1      0
                  //if(boardid != 0 || axisno != 0 || portid != 0 || moduleid != 0) {
                  if(moduleid != 0) {
                     bool_APS_Status = false;
                     MainForm->WriteSystemLog("ModuleID=0����!");
                  }
               }
               // MNET ModuleID = 1(Board ID=1, 10MHz)
               // Get First/Total Axis No
               ret = APS_get_field_bus_slave_first_axisno(BoardMNET, MNET_BUS, 1, &FirstAxisNo2, &TotalAxisNo2);
               if(ret != 0 || TotalAxisNo2 != 4 || FirstAxisNo2 != StartAxisNo2) {
                  MainForm->WriteSystemLog(">>MNET_BUS(1) First-TotalŪ������!");
                  bool_APS_Status = false;
               }
               else {
                  MainForm->WriteSystemLog(">>MNET_BUS(1) First-TotalŪ�����\.");
                  // �]�wAxis No: 1504 ~ 1507, �����B���s��4-7
                  //L_Axis = 4;
                  //RX_Axis = 5;
                  I32 axisno, boardid, portid, moduleid, ret1;
                  // Get Information
                  ret = APS_get_axis_info(FirstAxisNo2, &boardid, &axisno, &portid, &moduleid);
                  msg.sprintf(">>MNET 1: First,Total,Boardid,Ansixno,Portid,Moduleid=%d,%d,%d,%d,%d,%d",FirstAxisNo2,TotalAxisNo2,boardid,
                                                axisno,portid,moduleid);
                  MainForm->WriteSystemLog(msg);
                  //2021/03/22 15:59:47:002->>MNET 1: First,Total,Boardid,Ansixno,Portid,Moduleid=1504,4,0,0,1,1
                  //                                  1500  4     0       0       1      1
                  //if(boardid != 0 || axisno != 0 || portid != 1 || moduleid != 1) {
                  if(moduleid != 1) {
                     bool_APS_Status = false;
                  }
               }
            }
         }
      }

      if(bool_APS_Status == false) {
         MainForm->WriteSystemLog(">>Register Motion Card Error!");
         MainForm->pnl7856Status->Color = clRed;
         MainForm->tsMotion->Enabled = false;
         MainForm->sbSystemMessage->Panels->Items[1]->Text = "Register Motion Card Error!";
      }
      else {
         boolMotion = true;
         if(MainForm->shMotionStatus->Brush->Color != clLime) {
            MainForm->shMotionStatus->Brush->Color = clLime;
            MainForm->tsMotion->Enabled = true;
         }
         MainForm->WriteSystemLog(">>Register Motion Card Ok.");
         MainForm->pnl7856Status->Color = clLime;
         MainForm->sbSystemMessage->Panels->Items[1]->Text = "Register Motion Card Ok.";
         // Load �Ѽ���(�|��IPT_MODE/OPT_MODE/IPT_LOGIC����...)
         fname = MainForm->SystemDirectory + "\\Motion.xml";
         ret = APS_load_param_from_file(fname.c_str());
         // �T�{�O�_��Ū��?
         if(ret != ERR_NoError)
            Application->MessageBox((AnsiString("XML��Ū������!") + fname + ":" + IntToStr(ret)).c_str(),"XML�ɼg�J�@�~    ",MB_OK);

         // Load��n��Set: IPT_MODE/OPT_MODE/IPT_LOGIC��Load�J�t��
         // ����2.8���ᤣ���A��Set�ʧ@, Load�N�|�N�ѼƼg�J
         //SetMotionParameter();
         // �U�b�n�]�wINP Condition(MDN CONDI; Motion done condition) - �i�bXML�ɤ��]�w, ���ε{���U�R�O
         // 0: Control command done (default)
         // 1: Command done with INP
         //APS_set_axis_param(axisno, PRA_MDN_CONDI, 1);

      }
      //---------------------------------------------------------------------------
   }

   MainForm->WriteSystemLog(">Motion Completed.");
}
//---------------------------------------------------------------------------
#define MAX_SPEED               70000

// 2016 6 13 - chc �O���ثe��Continue���A
bool boolContinueState;

// ��sMotion Status
void __fastcall UpdateMotionStatus()
{
I16 AxisNum = 0;
I16 TempAxisNum = 0;
I16 i=0;
F64 Pos, Speed;
I32 Cmd;
I16 Motion_status;
AnsiString str;
U16 IO_status;
unsigned char bitno;
int bitposition;
static bool boolbit0 = false;
static bool boolbit1 = false;
static bool boolbit2 = false;
static bool boolbit3 = false;
static bool boolbit4 = false;
static bool boolbit5 = false;
static bool boolbit6 = false;
static bool boolbit7 = false;
static bool boolbit8 = false;
static bool boolbit9 = false;
static bool boolbit10 = false;
static bool boolbit11 = false;
static bool boolbit12 = false;
static bool boolbit13 = false;
static bool boolbit14 = false;
static bool boolbit15 = false;

// Panel �e�Ჾ��
static bool boolPanelMove = false;
static bool boolPanelBackward = false;
static bool boolPanelXMove = false;
static bool boolPanelXBackward = false;
static bool boolPanelYMove = false;
static bool boolPanelYBackward = false;
static bool boolPanelZMove = false;
static bool boolPanelZBackward = false;
static bool boolPanelTMove = false;
static bool boolPanelTBackward = false;

// 2016 5 15 - chc AI���t���q��0.3�W��0.5, Stop�P�w����0.3
double AIMinVibrate = 0.5;
double AIMinStop = 0.3;

AnsiString str1;

// 2020 5 21 - chc EMEM Status
// 2021 4 30 - chc �令MainForm global
//static int EFEMStatus = -1;

// 2021 9 15 - chc Stage Door Alarm
static boolStageDoorAlarm = false;
static boolPCDoorAlarm = false;
static boolEMOAlarm = false;
static boolEFEMLeftDoorAlarm = false;
static boolEFEMRightDoorAlarm = false;

   // 2020 7 15 - chc �O���O�_�bUpdate?
   MainForm->boolInMotionUpdate = true;

   // �i�w�qAI���̤p�ܤƶq
   AIMinVibrate = MainForm->edMinVibrate->Text.ToDouble();

   // ��sI/O Status: Ū��DIO - 7856 + DIO Board
   if(bool_IO_Status == true) {

      // Digital Input, PCI-7856(APS)
      // ��sDI
      int hslret = APS_get_field_bus_d_input(BoardHSL, HSL_BUS, IO1_ID, &input_IO1);
      if(hslret == ERR_NoError) {
         unsigned int bit;
         TPanel *panel;
         bit = 1;
         for(int no=0 ; no<16 ; no++) {
            panel = (TPanel *)(MainForm->FindComponent("pnlBit" + IntToStr(no)));
            if((input_IO1 & bit) != 0) {
               panel->Color = clLime;
               HSL_IO_InStatus[no] = true;

               // 2021 5 4 - chc Update CDA/Vacuum
               if(no == 2) {

                  // 2021 10 7 - chc �n�P�w: true-���`, false-���`
                  if(MainForm->boolSystemCDA == false) {

                     MainForm->boolSystemCDA = true;

                     // Code,Set/Reset,Level,Message
                     MainForm->SetSECSAlarm(11001,0,1,"System CDA Abnormal");
                  }

               }
               else if(no == 3) {

                  // 2021 10 7 - chc �n�P�w: true-���`, false-���`
                  if(MainForm->boolSystemVacuum == false) {

                     MainForm->boolSystemVacuum = true;

                     // Code,Set/Reset,Level,Message
                     MainForm->SetSECSAlarm(12001,0,1,"System Vacuum Abnormal");
                  }

               }

               // 2023 7 23 - chc �令Stage 8" Vacuum
               //else if(no == 11) {
               //   // �n�P�w: true-���`, false-���`
               //   if(MainForm->boolEFEMCDA == false) {
               //      MainForm->boolEFEMCDA = true;
               //      // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(13001,0,1,"EFEM CDA Abnormal");
               //   }
               //}

               // 2023 7 23 - chc �令Stage 12" Vacuum
               //else if(no == 12) {
               //   // �n�P�w: true-���`, false-���`
               //   if(MainForm->boolEFEMVacuum == false) {
               //      MainForm->boolEFEMVacuum = true;
               //      // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(14001,0,1,"EFEM Vacuum Abnormal");
               //   }
               //}

               // 2021 9 15 - chc Stage����
               else if(no == 13) {
                  if(boolStageDoorAlarm == true) {
                     boolStageDoorAlarm = false;
                     // Code,Set/Reset,Level,Message
                     MainForm->SetSECSAlarm(18002,0,0,"Stage Door Open");
                  }

               }

               // PC����
               // 2023 7 23 - chc ����
               //else if(no == 0) {
               //   if(boolPCDoorAlarm == true) {
               //      boolPCDoorAlarm = false;
               //      // Code,Reset/Set,Level,Message
               //      MainForm->SetSECSAlarm(18003,0,0,"PC Door Open");
               //   }
               //}

               // EMO
               else if(no == 8) {
                  if(boolEMOAlarm == false) {
                     boolEMOAlarm = true;
                     // Code,Set/Reset,Level,Message
                     MainForm->SetSECSAlarm(17001,0,1,"EMO Released");
                  }
               }
               // EFEM Left Door
               // 2023 7 23 - chc ����
               //else if(no == 4) {
               //   if(boolEFEMLeftDoorAlarm == false) {
               //      boolEFEMLeftDoorAlarm = true;
               //      // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(18001,0,0,"EFEM Left Door Open");
               //   }
               //}

               // EFEM Right Door
               // 2023 7 23 - chc ����
               //else if(no == 5) {
               //   if(boolEFEMRightDoorAlarm == false) {
               //      boolEFEMRightDoorAlarm = true;
               //      // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(18001,0,0,"EFEM Right Door Open");
               //   }
               //}

            }
            else {
               panel->Color = clSilver;
               HSL_IO_InStatus[no] = false;

               // 2021 5 4 - chc Update CDA/Vacuum
               if(no == 2) {

                  // 2021 10 7 - chc �n�P�w: true-���`, false-���`
                  if(MainForm->boolSystemCDA == true) {

                     MainForm->boolSystemCDA = false;
                     MainForm->WriteSystemLog("SystemCDA[Update] Error!");
                     // Code,Set/Reset,Level,Message
                     MainForm->SetSECSAlarm(11001,1,1,"System CDA Abnormal");
                  }
               }
               else if(no == 3) {

                  // 2021 10 7 - chc �n�P�w: true-���`, false-���`
                  if(MainForm->boolSystemVacuum == true) {

                     MainForm->boolSystemVacuum = false;
                     MainForm->WriteSystemLog("SystemVacuum[Update] Error!");
                     // Code,Set/Reset,Level,Message
                     MainForm->SetSECSAlarm(12001,1,1,"System Vacuum Abnormal");
                  }
               }

               // 2023 7 23 - chc �令Stage 8" Vacuum
               //else if(no == 11) {
               //   // �n�P�w: true-���`, false-���`
               //   if(MainForm->boolEFEMCDA == true) {
               //      MainForm->boolEFEMCDA = false;
               //      MainForm->WriteSystemLog("EFEMCDA[Update] Error!");
               //      // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(13001,1,1,"EFEM CDA Abnormal");
               //   }
               //}

               // 2023 7 23 - chc �令Stage 12" Vacuum
               //else if(no == 12) {
               //   // �n�P�w: true-���`, false-���`
               //   if(MainForm->boolEFEMVacuum == true) {
               //      MainForm->boolEFEMVacuum = false;
               //      MainForm->WriteSystemLog("EFEMVacuum[Update] Error!");
               //      // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(14001,1,1,"EFEM Vacuum Abnormal");
               //   }
               //}

               // 2021 9 15 - chc Stage����
               else if(no == 13) {
                  if(boolStageDoorAlarm == false) {
                     boolStageDoorAlarm = true;
                     // Code,Set/Reset,Level,Message
                     MainForm->SetSECSAlarm(18002,1,0,"Stage Door Open");
                  }
               }

               // PC Door
               // 2023 7 23 - chc ����
               //else if(no == 0) {
               //   if(boolPCDoorAlarm == false) {
               //      boolPCDoorAlarm = true;
               //       // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(18003,1,0,"Stage Door Open");
               //  }
               //}

               // EMO
               else if(no == 8) {
                  if(boolEMOAlarm == true) {
                     boolEMOAlarm = false;
                     // Code,Set/Reset,Level,Message
                     MainForm->SetSECSAlarm(17001,1,1,"EMO Pressed");
                  }
               }

               // EFEM Left Door
               // 2023 7 23 - chc ����
               //else if(no == 4) {
               //   if(boolEFEMLeftDoorAlarm == true) {
               //      boolEFEMLeftDoorAlarm = false;
               //      // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(18001,1,0,"EFEM Left Door Open");
               //   }
               //}

               // EFEM Right Door
               // 2023 7 23 - chc ����
               //else if(no == 5) {
               //   if(boolEFEMRightDoorAlarm == true) {
               //      boolEFEMRightDoorAlarm = false;
               //      // Code,Set/Reset,Level,Message
               //      MainForm->SetSECSAlarm(18001,1,0,"EFEM Right Door Open");
               //   }
               //}

            }
            bit = bit << 1;
         }
      }

      //========================================================================
      // AI-Joystick(���bADLink��AI�ҲդW): �ثe�LAI Joystick, �ثe�u��8154
      // �ثe�L�@��
      if(MainForm->cbAIJoystick->Checked == true) {
         // ��sAI: �M�w��V�P�t��
         static bool boolAIFirst = false;
         static double oldAIValue[16];
         static double oldAIRatio[16];
         if(boolAIFirst == false) {
            for(int i=0 ; i<16 ; i++) {
               oldAIValue[i] = 2.5;                                                // ���I
               oldAIRatio[i] = 0;
            }
            boolAIFirst = true;
         }

         // 0-Y�b, 1-X�b
         hslret = APS_get_field_bus_a_input(BoardHSL, HSL_BUS, AI_ID, 0, &AIValue[0]);
         hslret = APS_get_field_bus_a_input(BoardHSL, HSL_BUS, AI_ID, 1, &AIValue[1]);
         if(hslret == ERR_NoError) {
            // Only to check cbJoystick
            if(MainForm->cbJoystick->Checked == true) {
               // X�b
               if(MainForm->iAxisMove[X_AXIS] == NO_MOVE && MainForm->btnMove->Enabled == true && MainForm->boolInAIYMove == false) {
                  // �Ұ�: ������s��
                  // AI���t���q��0.3�W��0.5
                  if(fabs(AIValue[0] - 2.5) > AIMinVibrate && MainForm->boolInAIXMove == false) {
                     // �O���ثe��Continue���A
                     if(MainForm->boolInAIXMove == false && MainForm->boolInAIYMove == false) {
                        boolContinueState = MainForm->cbContinueMove->Checked;
                     }
                     MainForm->boolInAIXMove = true;
                     oldAIRatio[0] = 0;
                     MainForm->cbContinueMove->Checked = true;
                     // �ϥγ]�w�W����
                     MainForm->WriteSystemLog(">AI1(X): Active, SetMaxSpeed to " + MainForm->edUpLimitX->Text);
                     // ���wAxis
                     MainForm->combAxis->ItemIndex = X_AXIS;
                     MainForm->CurrentAxisNo = MainForm->combAxis->ItemIndex;
                     // ���V
                     if(AIValue[0] < 2.5) {
                        MainForm->WriteSystemLog(">AI1(X): Forward");
                        // �O���bmove��, ���i�H�P��Continue move
                        if(MainForm->boolInAxisMove == false) {
                           MainForm->WriteSystemLog(">AI1(X): Start to Move");
                           MainForm->boolJogMove = true;
                           boolPanelMove = true;
                           F64 ratio;
                           // Devide by zero
                           if(AIMinVibrate != 2.5) {
                              ratio = fabs(AIValue[0] - (2.5+AIMinVibrate)) * 100 / (2.5-AIMinVibrate);
                              if(ratio > 100)
                                 ratio = 100;
                              MainForm->InAIMoveXSpeed = (int)ratio;
                              // define type value: 0-wait, 1-nowait(for UpdateMotionStatus())
                              AxisMove(0,1);
                           }
                        }
                        else
                           MainForm->boolInAIXMove = false;
                     }
                     // �ϦV
                     else {
                        MainForm->WriteSystemLog(">AI1(X): Backward");
                        // �O���bmove��, ���i�H�P��Continue move
                        if(MainForm->boolInAxisMove == false) {
                           MainForm->WriteSystemLog(">AI1(X): Start to Move");
                           MainForm->boolJogMove = true;
                           boolPanelBackward = true;
                           // set boolPanelMove
                           boolPanelMove = true;
                           F64 ratio;
                           // AI���t���q��0.3�W��0.5��, �N2������35000. ��O2.5 vs 35000
                           // Devide by zero
                           if(AIMinVibrate != 2.5) {
                              ratio = fabs(AIValue[0] - (2.5+AIMinVibrate)) * 100 / (2.5-AIMinVibrate);
                              if(ratio > 100)
                                 ratio = 100;
                              MainForm->InAIMoveXSpeed = (int)ratio;
                              // define type value: 0-wait, 1-nowait(for UpdateMotionStatus())
                              AxisMove(1,1);
                           }
                        }
                        else
                           MainForm->boolInAIXMove = false;
                     }
                  }
               }
               //move���ˬdInAIX/Y Move�n��AI�Ȩӳ]�w�t�׭�
               //�ܳt�վ�...
               // �ܳt or ����?
               else {
                  // AI�ʧ@��...
                  if(MainForm->boolInAIXMove == true) {
                     // ����
                     // AI���t���q��0.3�W��0.5, Stop�P�w����0.3
                     if(fabs(AIValue[0] - 2.5) <= AIMinStop) {
                        MainForm->WriteSystemLog(">AI1(X): Stop");
                        MainForm->boolInAIXMove = false;
                        MainForm->boolJogMove = false;
                        boolPanelMove = false;
                        // �R�O����
                        if(MainForm->cbContinueMove->Checked == true) {
//                           _8154_emg_stop(X_AXIS);
                           // define type value: 0-wait, 1-nowait(for UpdateMotionStatus())
                           MainForm->pnlSystemMessage->Caption = "Move Done.";
                           Application->ProcessMessages();
                           // �O���bmove��, ���i�H�P��Continue move
                           MainForm->boolInAxisMove = false;
                           // �O���U�b�O�_�B�@��
                           MainForm->iAxisMove[X_AXIS] = NO_MOVE;
                        }
                        // 2016 6 13 - chc �٭�ثe��Continue���A
                        if(MainForm->boolInAIXMove == false && MainForm->boolInAIYMove == false) {
                           MainForm->cbContinueMove->Checked = boolContinueState;
                           if(boolContinueState == false)
                              MainForm->WriteSystemLog(">AI1(X) Resotore Continuous to false");
                           else
                              MainForm->WriteSystemLog(">AI1(X) Resotore Continuous to true");
                        }
                     }
                     // �����t��
                     else {
                        F64 ratio;
                        AnsiString msg;
                        // AI���t���q��0.3�W��0.5��, �N2������35000. ��O2.5 vs 35000
                        // Devide by zero
                        if(AIMinVibrate != 2.5) {
                           ratio = fabs(AIValue[0] - (2.5+AIMinVibrate)) * 100 / (2.5-AIMinVibrate);
                           if(ratio > 100)
                              ratio = 100;
                           // �t�ק��ܶW�L5%?
                           if(fabs(ratio - oldAIRatio[0]) > 2) {
                              msg.sprintf("%.1f",ratio);
                              MainForm->WriteSystemLog(">AI1(X): ChangeSpeed " + msg);
//                              _8154_speed_override(X_AXIS, ratio, 0.1);
                              oldAIRatio[0] = ratio;
                           }
                        }
                     }
                  }
               }
               // Y�b
               if(MainForm->iAxisMove[Y_AXIS] == NO_MOVE && MainForm->btnMove->Enabled == true && MainForm->boolInAIXMove == false) {
                  // �Ұ�: ������s��
                  // AI���t���q��0.3�W��0.5, Stop�P�w����0.3
                  if(fabs(AIValue[1] - 2.5) > AIMinVibrate && MainForm->boolInAIYMove == false) {
                     // �O���ثe��Continue���A
                     if(MainForm->boolInAIXMove == false && MainForm->boolInAIYMove == false) {
                        boolContinueState = MainForm->cbContinueMove->Checked;
                     }
                     MainForm->boolInAIYMove = true;
                     oldAIRatio[1] = 0;
                     MainForm->cbContinueMove->Checked = true;
                     // �ϥγ]�w�W����
                     MainForm->WriteSystemLog(">AI2(Y): Active, SetMaxSpeed to " + MainForm->edUpLimitY->Text);
//                     _8154_set_max_override_speed(Y_AXIS, (F64)MainForm->edUpLimitY->Text.ToDouble(), 1);
                     // ���wAxis
                     MainForm->combAxis->ItemIndex = Y_AXIS;
                     MainForm->CurrentAxisNo = MainForm->combAxis->ItemIndex;
                     // ���V
                     if(AIValue[1] < 2.5) {
                        MainForm->WriteSystemLog(">AI2(Y): Forward");
                        // �O���bmove��, ���i�H�P��Continue move
                        if(MainForm->boolInAxisMove == false) {
                           MainForm->WriteSystemLog(">AI2(Y): Start to Move");
                           MainForm->boolJogMove = true;
                           boolPanelMove = true;
                           F64 ratio;
                           if(AIMinVibrate != 2.5) {
                              ratio = fabs(AIValue[1] - (2.5+AIMinVibrate)) * 100 / (2.5-AIMinVibrate);
                              if(ratio > 100)
                                 ratio = 100;
                              MainForm->InAIMoveYSpeed = (int)ratio;
                              AxisMove(0,1);
                           }
                        }
                        else
                           MainForm->boolInAIYMove = false;
                     }
                     // �ϦV
                     else {
                        MainForm->WriteSystemLog(">AI2(Y): Backward");
                        // �O���bmove��, ���i�H�P��Continue move
                        if(MainForm->boolInAxisMove == false) {
                           MainForm->WriteSystemLog(">AI2(Y): Start to Move");
                           MainForm->boolJogMove = true;
                           boolPanelBackward = true;
                           boolPanelMove = true;
                           F64 ratio;
                           if(AIMinVibrate != 2.5) {
                              ratio = fabs(AIValue[1] - (2.5+AIMinVibrate)) * 100 / (2.5-AIMinVibrate);
                              if(ratio > 100)
                                 ratio = 100;
                              MainForm->InAIMoveYSpeed = (int)ratio;
                              AxisMove(1,1);
                           }
                        }
                       else
                           MainForm->boolInAIYMove = false;
                     }
                  }
               }
               //move���ˬdInAIX/Y Move�n��AI�Ȩӳ]�w�t�׭�
               //�ܳt�վ�...
               // �ܳt or ����?
               else {
                  // AI�ʧ@��...
                  if(MainForm->boolInAIYMove == true) {
                     if(fabs(AIValue[1] - 2.5) <= AIMinStop) {
                        MainForm->WriteSystemLog(">AI2(Y): Stop");
                        MainForm->boolInAIYMove = false;
                        MainForm->boolJogMove = false;
                        boolPanelMove = false;
                        if(MainForm->cbContinueMove->Checked == true) {
//                           _8154_emg_stop(Y_AXIS);
                           MainForm->pnlSystemMessage->Caption = "Move Done.";
                           Application->ProcessMessages();
                           // �O���bmove��, ���i�H�P��Continue move
                           MainForm->boolInAxisMove = false;
                           // �O���U�b�O�_�B�@��
                           MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
                        }
                        // �٭�ثe��Continue���A
                        if(MainForm->boolInAIXMove == false && MainForm->boolInAIYMove == false) {
                           MainForm->cbContinueMove->Checked = boolContinueState;
                           if(boolContinueState == false)
                              MainForm->WriteSystemLog(">AI2(Y) Resotore Continuous to false");
                           else
                              MainForm->WriteSystemLog(">AI2(Y) Resotore Continuous to true");
                        }
                     }
                     // �����t��
                     else {
                        F64 ratio;
                        AnsiString msg;
                        if(AIMinVibrate != 2.5) {
                           ratio = fabs(AIValue[1] - (2.5+AIMinVibrate)) * 100 / (2.5-AIMinVibrate);
                           if(ratio > 100)
                              ratio = 100;
                           // �t�ק��ܶW�L5%?
                           if(fabs(ratio - oldAIRatio[1]) > 2) {
                              msg.sprintf("%.1f",ratio);
                              MainForm->WriteSystemLog(">AI2(Y): ChangeSpeed " + msg);
//                              _8154_speed_override(Y_AXIS, ratio, 0.1);
                              oldAIRatio[1] = ratio;
                           }
                        }
                     }
                  }
               }
            }

            // ��s
            oldAIValue[0] = AIValue[0];
            oldAIValue[1] = AIValue[1];

            str.sprintf("%.3f",AIValue[0]);
            MainForm->pnlAI1Value->Caption = str;
            str.sprintf("%.3f",AIValue[1]);
            MainForm->pnlAI2Value->Caption = str;
            double value;
            // AI1
            if(AIValue[0] < 2.5) {
               MainForm->pnlAI1Low->Color = clLime;
               MainForm->pnlAI1High->Color = clSilver;
            }
            else if(AIValue[0] > 2.5) {
               MainForm->pnlAI1Low->Color = clSilver;
               MainForm->pnlAI1High->Color = clLime;
            }
            else {
               MainForm->pnlAI1Low->Color = clSilver;
               MainForm->pnlAI1High->Color = clSilver;
            }
            value = fabs(AIValue[0] - 2.5);
            MainForm->pgAI1->Position = (int)(value * MainForm->pgAI1->MaxValue / 2.5);
            // AI2
            if(AIValue[1] < 2.5) {
               MainForm->pnlAI2Low->Color = clLime;
               MainForm->pnlAI2High->Color = clSilver;
            }
            else if(AIValue[1] > 2.5) {
               MainForm->pnlAI2Low->Color = clSilver;
               MainForm->pnlAI2High->Color = clLime;
            }
            else {
               MainForm->pnlAI2Low->Color = clSilver;
               MainForm->pnlAI2High->Color = clSilver;
            }
            value = fabs(AIValue[1] - 2.5);
            MainForm->pgAI2->Position = (int)(value * MainForm->pgAI2->MaxValue / 2.5);
         }
         else {
            MainForm->pnlAI1Value->Caption = "---";
            MainForm->pnlAI2Value->Caption = "---";
         }
      }
      //========================================================================
   }

   // ���S�wDI���B�z - �ثe�L���O������\��: cbPanelJoystick
   if(bool_IO_Status == true) {
      // Stage With Wafer(bit7)
      if(MainForm->pnlBit7->Color == clLime) {
         AnsiString msg;
         msg.sprintf("LP%d.%d",MainForm->rgLoadPortSelect->ItemIndex+1,25-MainForm->rgWaferNo->ItemIndex);
         MainForm->pnlWaferChuckInformation->Caption = msg;
         MainForm->pnlWaferChuckInformation->Color = clLime;
         MainForm->pnlWaferChuckInformation1->Color = clLime;
         MainForm->pnlWaferChuckInformation2->Color = clLime;
         MainForm->pnlWaferChuckInformation->Refresh();
         MainForm->pnlWaferChuckInformation1->Refresh();
         MainForm->pnlWaferChuckInformation2->Refresh();
         // �O��Chuck��Wafer: boolChuckWithWafer
         MainForm->boolChuckWithWafer = true;
      }
      else {

         // 2023 7 25 - chc �g��, ��clSilver ����
         //MainForm->pnlWaferChuckInformation->Color = (TColor)0x0068C6AA;
         MainForm->pnlWaferChuckInformation->Color = clSilver;
         MainForm->pnlWaferChuckInformation->Caption = "";

         MainForm->pnlWaferChuckInformation1->Color = clSilver;
         MainForm->pnlWaferChuckInformation2->Color = clSilver;
         MainForm->pnlWaferChuckInformation->Refresh();
         MainForm->pnlWaferChuckInformation1->Refresh();
         MainForm->pnlWaferChuckInformation2->Refresh();
         // �O��Chuck�LWafer
         MainForm->boolChuckWithWafer = false;
      }

      // Left Door: pnlBit4
      if(MainForm->pnlBit4->Color == clLime) {
         MainForm->pnlEFEMLeftDoor->Color = clLime;
      }
      else {
         MainForm->pnlEFEMLeftDoor->Color = clSilver;
      }

      // Right Door: pnlBit5
      if(MainForm->pnlBit5->Color == clLime) {
         MainForm->pnlEFEMRightDoor->Color = clLime;
      }
      else {
         MainForm->pnlEFEMRightDoor->Color = clSilver;
      }

      // EFEM Key: pnlEFEMKey, Key Off(bit6 On)�O����Maintenance mode
      if(MainForm->pnlBit6->Color == clLime) {
         MainForm->pnlEFEMKey->Color = clSilver;
         MainForm->pnlEFEMMaintenanceMode->Color = clSilver;
         // EMEM Status
         if(EFEMStatus == 1) {
            MainForm->AddErrorLog("[System] ����EFEM Maintenance Mode.");

            // 2021 4 30 - chc �YDO4��on, �n����
            if(MainForm->pnlDOCDA->Color == clLime) {
               HSL_IO_OuStatus &= ~(0x10);
               MainForm->pnlDOCDA->Color = clSilver;
            }

         }
         EFEMStatus = 0;
      }
      // Key on(bit6 Off): �i�i�JMaintenance mode
      else {

         // 2021 4 30 - chc ���b�o�̰�, ��DO4�M�w
         //MainForm->pnlEFEMKey->Color = clRed;
         //MainForm->pnlEFEMMaintenanceMode->Color = clLime;
         //// EMEM Status
         //if(EFEMStatus == 0) {
         //   MainForm->AddErrorLog("[System] �i�JEFEM Maintenance Mode.");
         //}
         //EFEMStatus = 1;
      }

      // Motor Power: Bit1, pnlSystemPower
      if(MainForm->pnlBit1->Color == clLime) {
         MainForm->pnlSystemPower->Color = clLime;
      }
      else {
         MainForm->pnlSystemPower->Color = clSilver;
      }

      // CDA: Bit2, pnlSystemCDA
      if(MainForm->pnlBit2->Color == clLime) {
         MainForm->pnlSystemCDA->Color = clLime;
         MainForm->boolSystemCDA = true;
      }
      else {
         MainForm->pnlSystemCDA->Color = clSilver;
         MainForm->boolSystemCDA = false;
      }

      // Vacuum: Bit3, pnlSystemVacuum
      if(MainForm->pnlBit3->Color == clLime) {
         MainForm->pnlSystemVacuum->Color = clLime;
         MainForm->boolSystemVacuum = true;
      }
      else {
         MainForm->pnlSystemVacuum->Color = clSilver;
         MainForm->boolSystemVacuum = false;
      }

      // EFEM CDA: Bit11, pnlEFEMCDA
      // 2023 8 1 - chc �LEFEM CDA/Vacuum
      //if(MainForm->pnlBit11->Color == clLime) {
      //   MainForm->pnlEFEMCDA->Color = clLime;
      //   MainForm->boolEFEMCDA = true;
      //}
      //else {
      //   MainForm->pnlEFEMCDA->Color = clSilver;
      //   MainForm->boolEFEMCDA = false;
      //}

      // EFEM Vacuum: Bit12, pnlEFEMVacuum
      // 2023 8 1 - chc �LEFEM CDA/Vacuum
      //if(MainForm->pnlBit12->Color == clLime) {
      //   MainForm->pnlEFEMVacuum->Color = clLime;
      //
      //   // 2021 10 7 - chc ����b�o�̳]�w: true-���`, false-���`
      //   //MainForm->boolEFEMVacuum = true;
      //
      //}
      //else {
      //   MainForm->pnlEFEMVacuum->Color = clSilver;
      //
      //   // 2021 10 7 - chc ����b�o�̳]�w: true-���`, false-���`
      //   //MainForm->boolEFEMVacuum = false;
      //
      //}

   }

   // DIĵ��: Motor On?
   if(MainForm->pnlBit1->Color == clSilver) {
      if(MainForm->pnlAxisError->Visible == false) {
         AnsiString msg;
         // ���ާ@��
         if(MainForm->PriorityLevel == PRIORITY_OP) {
            //msg = "�Ы��U�b���q����A��Reset��Motion Home";
            msg = "Power On and restart the SVON and Home";
            MainForm->pcEFEMH->Enabled = false;
            MainForm->pcEFEMR->Enabled = false;
            MainForm->WriteSystemLog("MotionHome: �]�wpcRobot��false");
         }
         else
            //msg = "�Ы��U�b���q���᭫�s��SVON��Motion Home";
            msg = "Power On and restart the SVON and Home";
         MainForm->pnlAxisError->Font->Size = 16;
         MainForm->pnlAxisError->Caption = msg;
         MainForm->pnlAxisError->Visible = true;
         // Error�ɭn�Ұ�Motion
         MainForm->pcMotion->Enabled = true;
         Beep(500);
         // Alarm Message
         MainForm->pnlAlarmMessage->Caption = msg;

         // 2020 2 14a - chc �ʱ��O�_�o��Power Off
         MainForm->boolMotionPowerOff = true;

         // 2021 5 5 - chc ������IPage
         MainForm->pcOP->ActivePage = MainForm->tsHome;

      }
   }
   else {
      // ���ާ@��
      if(MainForm->pnlAxisError->Caption == "�Ы��U�b���q����A��Reset��Motion Home") {
         if(MainForm->btnMotionReset->Visible == false) {
            MainForm->btnMotionReset->Caption = "Reset";
            MainForm->btnMotionReset->Visible = true;
         }
      }
   }

   MainForm->pnlEFEMLeftDoor->Color = MainForm->pnlBit4->Color;
   MainForm->pnlEFEMRightDoor->Color = MainForm->pnlBit5->Color;

   // EFEMKey �ϦV
   // 2021 4 30 - chc ���b�o���ܰ�: pnlEFEMKey�O��ܬO�_�w�i�JMaintenance mode, ���OKey�����A
   //if(MainForm->pnlBit6->Color == clLime)
   //   MainForm->pnlEFEMKey->Color = clSilver;
   //else
   //   MainForm->pnlEFEMKey->Color = clRed;

   // �b��
   TLMDEdit *counterarray[6]    = {MainForm->edCounterT,       MainForm->edCounterY,       MainForm->edCounterZ,       MainForm->edCounterX,            MainForm->edCounterL,           MainForm->edCounterW};
   TLMDEdit *commandarray[6]    = {MainForm->edCommandT,       MainForm->edCommandY,       MainForm->edCommandZ,       MainForm->edCommandX,            MainForm->edCommandL,           MainForm->edCommandW};
   // MotionStatus & IOStatus�Ȧb"�b����T(0.1um/pulse)"�� �ثe�����
   TPanel *motionstatusarray[6] = {MainForm->pnlMotionStatusT, MainForm->pnlMotionStatusY, MainForm->pnlMotionStatusZ, MainForm->pnlMotionStatusX,      MainForm->pnlMotionStatusL,     MainForm->pnlMotionStatusW};
   TPanel *iostatusarray[6]     = {MainForm->pnlIOStatusT,     MainForm->pnlIOStatusY,     MainForm->pnlIOStatusZ,     MainForm->pnlIOStatusX,          MainForm->pnlIOStatusL,         MainForm->pnlIOStatusW};

   // 2021 4 18 - chc Log
   //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 1");

   // 2021 4 15 - chc 8154 or APS_
   // �U�bCommand, position, status
   if(MotionMode == MOTION_MODE_APS) {

      // 2021 4 18 - chc Log
      //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 2");

      I32 ipos,istatus;
      for(int axisno=0 ; axisno<MAX_AXIS_NO ; axisno++) {
         // Position
         APS_get_position(axisno+StartAxisNo,&ipos);
         str = IntToStr(ipos);
         counterarray[axisno]->Text = str;

         // 2023 8 10 - chc Z1(45)
         if(axisno == Z1_AXIS && MainForm->pnlVieworks->Visible == true)
            MainForm->pnl45Z1->Caption = str;

         // Command
         APS_get_command(axisno+StartAxisNo,&ipos);
         str = IntToStr(ipos);
         commandarray[axisno]->Text = str;
         // Motion Status: istatus
         istatus = APS_motion_status(axisno+StartAxisNo);
         Motion_status = istatus;
         str = IntToHex(Motion_status,4);
         motionstatusarray[axisno]->Caption = str;
         if(axisno < MAX_AXIS_NO)
            MotionStatusCode[axisno] = Motion_status;
         // @@
         //MainForm->WriteSystemLog(">Axis: " + IntToStr(axisno) + "MotionStatus: " + str);
         // IO Status
         istatus = APS_motion_io_status(axisno+StartAxisNo);
         IO_status = istatus;
         DecodeIOStatus(axisno,IO_status);
         str = IntToHex(IO_status,4);
         iostatusarray[axisno]->Caption = str;
         // @@
         //MainForm->WriteSystemLog(">Axis: " + IntToStr(axisno) + "IOStatus: " + str);
      }

      // 2021 4 18 - chc Log
      //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 3");

   }

   // 2021 4 30 - chc �O�_�bHome(�J���I)
   int currx,curry,homex,homey;
   currx = MainForm->edCounterX->Text.ToInt();
   curry = MainForm->edCounterY->Text.ToInt();
   homex = MainForm->edLoadX->Text.ToInt();
   homey = MainForm->edLoadY->Text.ToInt();
   if(abs(currx - homex) < 1000 && abs(curry - homey) < 1000)
      MainForm->pnlXYStageReady->Color = clLime;
   else
      MainForm->pnlXYStageReady->Color = clSilver;

   // 2019 7 22 - chc ��sLow/Middle/High���t�׭�
   int basevx,basevy;
   double ratio;

   // 2021 4 18 - chc Log
   //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 4");

   basevx = MainForm->edMaxVelX->Text.ToInt();

   // 2021 4 18 - chc Log
   //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 4a");

   basevy = MainForm->edMaxVelY->Text.ToInt();

   // 2021 4 18 - chc Log
   //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 4b");

   if(MainForm->rgSpeed->ItemIndex == 0)
      ratio = MainForm->edSpeedGeneralLow->Text.ToDouble();
   else if(MainForm->rgSpeed->ItemIndex == 1)
      ratio = MainForm->edSpeedGeneralMiddle->Text.ToDouble();
   else if(MainForm->rgSpeed->ItemIndex == 2)
      ratio = MainForm->edSpeedGeneralHigh->Text.ToDouble();

   // 2021 4 18 - chc Log
   //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 4c");

   if(ratio > 100)
      ratio = 100;
   if(ratio < 1)
      ratio = 1;
   basevx = basevx * ratio / 100;
   basevy = basevy * ratio / 100;
   MainForm->pnlCurrentSpeed->Caption = IntToStr(basevx) + "-" + IntToStr(basevy);

   // 2021 4 18 - chc Log
   MainForm->pnlCurrentSpeed->Refresh();
   //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 4d : " + MainForm->pnlCurrentSpeed->Caption);

   // �O���O�_�}�l��DIO
   MainForm->boolDIO = true;

   // �YMotion�b�B�@���h�����O
   boolMotionState = false;
   for(int i=0 ; i<MAX_AXIS_NO ; i++) {
      if(MotionStatusCode[i] != 0 && MotionStatusCode[i] != 17 && MotionStatusCode[i] != 18)
         boolMotionState = true;
   }

   // �O���O�_�bUpdate?
   MainForm->boolInMotionUpdate = false;

   // 2021 4 18 - chc Log
   //MainForm->WriteSystemLog(">UpdateMotionStatus() ... 5");

}
//---------------------------------------------------------------------------
// 4�b�P��Home
#define HOME_START              0
#define HOME_EL                 1
#define HOME_MOVE               2
#define HOME_DONE               3

// 2016 9 5 - chc ����+EL�A��Home
#define HOME_PEL                4

// 2016 9 7 - chc -EL done
#define HOME_NEL_DONE           5
#define HOME_PORG               7
#define HOME_NORG               8

//---------------------------------------------------------------------------
// 2021 4 15 - chc APS
void __fastcall AllHome()
{
I16 axisno,homemode;
U16 motionstatus,iostatus;
F64 pos,fcmd;
I32 cmd;
I16 ret;
int counter = 1;
I16 Motion_status;
int no;
int status[MAX_AXIS_NO],cnt;
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
bool boolnel = true;
AnsiString name;
TLMDComboBox* combobox;
F64 lowdistance;

// �Ĥ@���i�ӭn�Ұ�CCD Live
static bool first = true;
// Motion Done��n��Timer�Ӱ�EFEM��Initial
static bool efemfirst = true;
bool boolmotiondone = false;

   MainForm->pnlAllHomeStatus->Color = clSilver;
   MainForm->pnlAllHomeStatus1->Color = clSilver;
   MainForm->pnlSystemMessage->Caption = "Homing...";
   // ���]�w��X��HomeMode
   homemode = MainForm->combHomeModeX->ItemIndex;
   MainForm->pnlStatusX->Color = clSilver;
   MainForm->pnlStatusY->Color = clSilver;
   MainForm->pnlStatusT->Color = clSilver;
   MainForm->pnlStatusZ->Color = clSilver;
   MainForm->pnlStatusL->Color = clSilver;
   MainForm->pnlStatusW->Color = clSilver;

   for(no=0 ; no<MAX_AXIS_NO ; no++) {
      status[no] = HOME_START;
   }

   // 2023 8 2 - chc Step
   MainForm->pnlMotionHomeUnit->Caption = "Z,Z1 to -EL...";

   // ����Z/T��-EL�A��AllHome
   TPanel *panelel,*panelst;
   AnsiString aname;
   // Z_AXIS=2, T_AXIS=0
   for(int i=Z_AXIS ; i>=T_AXIS ; i-=2) {
      if(i == Z_AXIS) {
         panelel = (TPanel *)(MainForm->FindComponent("pnlNELZ"));
         panelst = (TPanel *)(MainForm->FindComponent("pnlStatusZ"));
         aname = "ZAxis";
         MainForm->WriteSystemLog(">Z -EL...");
      }
      else {
         panelel = (TPanel *)(MainForm->FindComponent("pnlNELT"));
         panelst = (TPanel *)(MainForm->FindComponent("pnlStatusT"));
         aname = "TAxis";
         MainForm->WriteSystemLog(">T -EL...");
      }
      no = i;
      axisno = no;
      MainForm->WriteSystemLog(">-EL: " + IntToStr(no) + "," + IntToStr(MAX_AXIS_NO));
      GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
      // ����4/5
      maxvel = (maxvel*4) / 5;
      // �����b�ƥH���oStartVel/MaxVel
      MainForm->combAxis->ItemIndex = axisno;
      DelayTimeM3(100);
      panelst->Color = clYellow;
      // Message
      MainForm->WriteSystemLog(">" + aname + " -EL...");
      // ���ϦV��-EL(�]�w��0�I)
      // ret: 0-off, 1-on
      boolnel = GetNELStatus(axisno);
      if(boolnel == true)
         panelel->Color = clRed;
      else
         panelel->Color = clSilver;
      // ���b-EL, Do
      if(boolnel == false) {
         if(MotionMode == MOTION_MODE_APS) {
            I32 ipos;
            APS_get_position(axisno+StartAxisNo,&ipos);
            pos = ipos;
            pos = -9000000;                                                           // 90mm
            // 2021 4 19 - chc Log
            MainForm->WriteSystemLog(">Home -EL: " + aname + " �I�sAPS_relative_move()");
            ret = APS_relative_move(axisno+StartAxisNo,(int)pos,(int)maxvel);
         }
      }
      // ��Z��-EL
      MainForm->pnlSystemMessage->Caption = "Wait " + aname + " -EL Move...";
      MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
      while(1) {
         boolnel = GetNELStatus(axisno);
         if(boolnel == true)
            panelel->Color = clRed;
         else
            panelel->Color = clSilver;
         if(boolnel == true) {
            panelst->Color = clGreen;
            // Message
            MainForm->WriteSystemLog(">" + aname + " -EL Done");
            break;
         }
         DelayTimeM3(100);
      }
      DelayTimeM3(1000);
   }
   MainForm->WriteSystemLog(">ZT -EL end.");

   // 2023 8 2 - chc Step
   MainForm->pnlMotionHomeUnit->Caption = "Z,Z1 to -EL done.";

   // �T�{Z/T�O�_��-EL @@��
   //if(Application->MessageBox("�T�{Z/T�O�_��-EL, ��Home?     ", "Olympus Operation", MB_YESNO|MB_SYSTEMMODAL) == IDNO) {
   //   goto end;
   //}

   // 2023 8 2 - chc Step
   MainForm->pnlMotionHomeUnit->Caption = "X,Y,L,W to -EL...";

   // ?? EFEM�n��Home: �ר�ORobot
   // 1. X/Y/L/W to -EL
   // 2. X/Y/W Home Mode4
   for(no=0 ; no<MAX_AXIS_NO ; no++) {
      axisno = no;
      if(axisno == Z_AXIS || axisno == T_AXIS) {
         // �w��-EL, �ǳƶi��Home
         status[axisno] = HOME_MOVE;
         continue;
      }
      MainForm->WriteSystemLog(">-EL: " + IntToStr(no) + "," + IntToStr(MAX_AXIS_NO));
      status[axisno] = HOME_START;                                                  // 1. X to -EL
      GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
      MainForm->WriteSystemLog(">�b,MaxVel: " + IntToStr(axisno+1) + "," + IntToStr((int)maxvel));

      if(axisno == X_AXIS) {
         MainForm->pnlStatusX->Color = clSilver;
      }
      else if(axisno == Y_AXIS) {
         MainForm->pnlStatusY->Color = clSilver;
      }
      else if(axisno == L_AXIS) {
         MainForm->pnlStatusL->Color = clSilver;
      }
      else if(axisno == W_AXIS) {
         MainForm->pnlStatusW->Color = clSilver;
      }

      // ���o�ӧOHomeMode
      GetAxisName((int)axisno);
      name = MainForm->AxisName;
      combobox = (TLMDComboBox *)(MainForm->FindComponent("combHomeMode" + name));
      homemode = combobox->Text.ToInt();

      // Home Mode 4
      homemode = 4;

      // ����4/5
      if(no == X_AXIS)
         maxvel = (maxvel*2) / 3;

      // 2021 8 10 - chc W�b��1/2
      else if(no == W_AXIS)
         maxvel = maxvel / 2;

      else
         maxvel = (maxvel*4) / 5;
      MainForm->WriteSystemLog(">�b-EL����(�b,�t��)1: " + IntToStr(axisno+1) + "," + IntToStr((int)maxvel));
      // �����b�ƥH���oStartVel/MaxVel
      MainForm->combAxis->ItemIndex = axisno;
      DelayTimeM3(100);

      MainForm->WriteSystemLog(">�b-EL����(�b,�t��)1a");

      // ���ϦV��-EL(�]�w��0�I), �A��Home 9, T�b�n�A�e��8600
      status[axisno] = HOME_EL;
      if(axisno == X_AXIS) {
         MainForm->pnlStatusX->Color = clYellow;
         // Message
         MainForm->WriteSystemLog(">XAxis -EL");
      }
      else if(axisno == Y_AXIS) {
         MainForm->pnlStatusY->Color = clYellow;
         // Message
         MainForm->WriteSystemLog(">YAxis -EL");
      }
      else if(axisno == L_AXIS) {
         MainForm->pnlStatusL->Color = clYellow;
         // Message
         MainForm->WriteSystemLog(">LAxis -EL");
      }
      else if(axisno == W_AXIS) {
         MainForm->pnlStatusW->Color = clYellow;
         // Message
         MainForm->WriteSystemLog(">WAxis -EL");
      }

      MainForm->WriteSystemLog(">�b-EL����(�b,�t��)1b");

      // ���ϦV��-EL(�]�w��0�I)
      // ret: 0-off, 1-on
      boolnel = GetNELStatus(axisno);
      if(boolnel == false) {
         MainForm->WriteSystemLog(">�b-EL����(�b,�۹��m)1: " + IntToStr(axisno+1) + "," + IntToStr((int)pos));
         MainForm->WriteSystemLog(">����500ms...");
         DelayTimeM2(500);
         MainForm->WriteSystemLog(">����500ms.");
         if(MotionMode == MOTION_MODE_APS) {
            I32 ipos;
            APS_get_position(axisno+StartAxisNo,&ipos);
            cmd = ipos;
            pos = -9000000;                                                           // 90mm
            ret = APS_relative_move(axisno+StartAxisNo,(int)pos,(int)maxvel);
         }

         // �T�{L�b�O�_������? �άO�_�w�b-EL
         // L: 4.2um/pulse
         if(axisno == L_AXIS) {
            I32 lpos;
            int cnt = 0;
            int trycnt = 0;
            F64 tdec;
            while(1) {

               // 2021 5 3 - chc �T�{�O�_�w�b-EL?
               // ret: 0-off, 1-on
               boolnel = GetNELStatus(axisno);
               // �w��-EL
               if(boolnel == true)
                  break;

               MainForm->WriteSystemLog(">L�b�w�������ˬd...");
               DelayTimeM2(100);
               if(MotionMode == MOTION_MODE_APS) {
                  I32 ipos;
                  APS_get_position(axisno+StartAxisNo,&ipos);
                  fcmd = ipos;
               }
               lpos = fcmd;

               if(abs(lpos - cmd) > 10) {
                  MainForm->WriteSystemLog(">L�b�w������.");
                  break;
               }
               cnt++;
               // Timeout: 1sec
               if(cnt > 10) {
                  cnt = 0;
                  MainForm->WriteSystemLog(">L�b������, Timeout! ��Stop�A�U�@�����ʩR�O.");
                  tdec = GetTdec(axisno);
                  if(MotionMode == MOTION_MODE_APS)
                     APS_stop_move(axisno+StartAxisNo);
                  DelayTimeM2(100);
                  if(trycnt == 3) {
                     MainForm->WriteSystemLog(">L�b: �U�����m���ʩR�O.");
                     if(MotionMode == MOTION_MODE_APS)
                        ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);
                  }
                  else {
                     MainForm->WriteSystemLog(">L�b: �U�۹��m���ʩR�O.");
                     if(MotionMode == MOTION_MODE_APS)
                        ret = APS_relative_move(axisno+StartAxisNo,(int)pos,(int)maxvel);
                  }
                  DelayTimeM2(300);
                  trycnt++;
                  if(trycnt > 2)
                     break;
               }
            }
         }
      }
   }

   // Log: HOME_MOVE
   MainForm->WriteSystemLog(">XAxis Mode=" + IntToStr(status[X_AXIS]));
   MainForm->WriteSystemLog(">YAxis Mode=" + IntToStr(status[Y_AXIS]));
   MainForm->WriteSystemLog(">ZAxis Mode=" + IntToStr(status[Z_AXIS]));
   MainForm->WriteSystemLog(">TAxis Mode=" + IntToStr(status[T_AXIS]));
   MainForm->WriteSystemLog(">LAxis Mode=" + IntToStr(status[L_AXIS]));
   MainForm->WriteSystemLog(">WAxis Mode=" + IntToStr(status[W_AXIS]));

   MainForm->WriteSystemLog(">����X,Y,L,W�b��-EL...");
   // ���Ҧ��bHOME_MOVE
   // L��-EL�N�i�H, ���ΰ�Home
   MainForm->pnlSystemMessage->Caption = "Wait Home Move...";
   counter = 1;
   while(1) {
      cnt = 0;
      for(no=0 ; no<MAX_AXIS_NO ; no++) {
         axisno = no;
         // �n���w�b��
         MainForm->combAxis->ItemIndex = axisno;
         GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
         // ����2/3
         maxvel = (maxvel*2) / 3;
         // �w����Home_Move
         if(status[axisno] == HOME_MOVE || status[axisno] == HOME_DONE) {
            cnt++;
            if(cnt >= MAX_AXIS_NO) {

               // �T�{X/Y/L/W�O�_��-EL @@��
               //if(Application->MessageBox("�T�{X/Y/L/W�O�_��-EL(1), ��Home?     ", "Olympus Operation", MB_YESNO|MB_SYSTEMMODAL) == IDNO) {
               //   goto end;
               //}

               // ������-EL�AHome
               // ��Home�t��
               if(MotionMode == MOTION_MODE_APS) {
                  APS_home_move(X_AXIS+StartAxisNo);
                  Sleep(100);
                  APS_home_move(Y_AXIS+StartAxisNo);
                  Sleep(100);
                  APS_home_move(Z_AXIS+StartAxisNo);
                  Sleep(100);
                  APS_home_move(T_AXIS+StartAxisNo);
                  Sleep(100);
                  APS_home_move(W_AXIS+StartAxisNo);
                  Sleep(100);
               }
               break;
            }
            continue;
         }

         // Log
         //MainForm->WriteSystemLog(">Mode Axis,Status= " + IntToStr(axisno) + "," + IntToStr(status[axisno]));

         // ��-EL��
         if(status[axisno] == HOME_EL) {
            // ret: 0-off, 1-on
            boolnel = GetNELStatus(axisno);

            if(axisno == X_AXIS)
               panelel = (TPanel *)(MainForm->FindComponent("pnlNELX"));
            else if(axisno == Y_AXIS)
               panelel = (TPanel *)(MainForm->FindComponent("pnlNELY"));
            else if(axisno == L_AXIS)
               panelel = (TPanel *)(MainForm->FindComponent("pnlNELL"));
            else if(axisno == W_AXIS)
               panelel = (TPanel *)(MainForm->FindComponent("pnlNELW"));
            if(boolnel == true)
               panelel->Color = clSilver;
            else
               panelel->Color = clRed;
            panelel->Refresh();
            if(axisno == Y_AXIS && boolnel == false) {
               //MainForm->WriteSystemLog(">YAxis Move EL- ������!");
            }

            // -EL?
            if(boolnel == true) {
               if(axisno == X_AXIS) {
                  MainForm->pnlStatusX->Color = clGreen;
                  MainForm->WriteSystemLog(">XAxis Move EL- Done");

                  // 2023 8 2 - chc Step
                  MainForm->pnlMotionHomeUnit->Caption = "X -EL done.";

               }
               else if(axisno == Y_AXIS) {
                  MainForm->pnlStatusY->Color = clGreen;
                  MainForm->WriteSystemLog(">YAxis Move EL- Done");

                  // 2023 8 2 - chc Step
                  MainForm->pnlMotionHomeUnit->Caption = "Y -EL done.";

               }
               else if(axisno == L_AXIS) {
                  MainForm->pnlStatusL->Color = clGreen;
                  MainForm->WriteSystemLog(">LAxis Move EL- Done");

                  // 2023 8 2 - chc Step
                  MainForm->pnlMotionHomeUnit->Caption = "L -EL done.";

               }
               else if(axisno == W_AXIS) {
                  MainForm->pnlStatusW->Color = clGreen;
                  MainForm->WriteSystemLog(">WAxis Move EL- Done");

                  // 2023 8 2 - chc Step
                  MainForm->pnlMotionHomeUnit->Caption = "W -EL done.";

               }
               status[axisno] = HOME_MOVE;
               cnt++;
               MainForm->combAxis->ItemIndex = axisno;

               // �H-EL �����I
               DelayTimeM3(100);
               // �A���[�@�I
               DelayTimeM3(600);

               // 2023 8 4 - chc Reset Axis Command[����)
               //ResetPosition();
               //ResetCommand();
               ResetPositionAxis(axisno);
               ResetCommandAxis(axisno);

               DelayTimeM3(100);

               if(axisno != L_AXIS) {
                  if(axisno == X_AXIS)
                     MainForm->WriteSystemLog(">XAxis Homing...");
                  else if(axisno == Y_AXIS)
                     MainForm->WriteSystemLog(">YAxis Homing...");
                  else if(axisno == Z_AXIS)
                     MainForm->WriteSystemLog(">ZAxis Homing...");
                  else if(axisno == T_AXIS)
                     MainForm->WriteSystemLog(">TAxis Homing...");
                  else if(axisno == W_AXIS)
                     MainForm->WriteSystemLog(">WAxis Homing...");
                  MainForm->WriteSystemLog(">Home cmd: done.");
               }
               if(cnt >= MAX_AXIS_NO) {

                  // �T�{X/Y/L/W�O�_��-EL @@��
                  //if(Application->MessageBox("�T�{X/Y/L/W�O�_��-EL(2), ��Home?     ", "Olympus Operation", MB_YESNO|MB_SYSTEMMODAL) == IDNO) {
                  //   goto end;
                  //}

                  // ������-EL�AHome
                  // ��Home�t��
                  if(MotionMode == MOTION_MODE_APS) {
                     APS_home_move(X_AXIS+StartAxisNo);
                     Sleep(100);
                     APS_home_move(Y_AXIS+StartAxisNo);
                     Sleep(100);
                     APS_home_move(Z_AXIS+StartAxisNo);
                     Sleep(100);
                     APS_home_move(T_AXIS+StartAxisNo);
                     Sleep(100);
                     APS_home_move(W_AXIS+StartAxisNo);
                     Sleep(100);
                  }
                  break;
               }
               continue;
            }
            else {
               if(axisno == Z_AXIS) {
                  AnsiString msg;
                  msg.sprintf(">ZAxis Move EL- Not! %x,%d",iostatus,iostatus);
                  MainForm->WriteSystemLog(msg);
               }
            }
         }
      }
      // ���i�JHome Moving?
      if(cnt >= MAX_AXIS_NO)
         break;

      DelayTimeM3(50);
      counter++;
      // 100��: 50*20000
      if(counter > 2000) {
         MainForm->pnlSystemMessage->Caption = "Home Move Fail!";
         MainForm->pnlAllHomeStatus->Color = clRed;
         MainForm->pnlAllHomeStatus1->Color = clRed;
         // Beep�n
         Beep(500);

         // Alarm Message
         MainForm->pnlAlarmMessage->Caption = " AllHome Error!";
         return;
      }
   }
   MainForm->WriteSystemLog(">Wait Homing...");

   // 2023 8 2 - chc Step
   MainForm->pnlMotionHomeUnit->Caption = "Wait Homing...";

   // ��Motion Done
   // ��X/Y/Z/T/W�bHOME_MOVE
   boolmotiondone = false;
   MainForm->pnlSystemMessage->Caption = "Wait Homing...";
   counter = 1;
   while(1) {
      cnt = 0;
      for(no=0 ; no<MAX_AXIS_NO ; no++) {
         axisno = no;
         boolmotiondone = GetMotionDoneStatus(axisno);
         // L�b�j�Home done
         if(no == L_AXIS) {
            Motion_status = 0;
            status[axisno] = HOME_DONE;
            MainForm->pnlStatusL->Color = clLime;
         }
         if(status[axisno] == HOME_DONE)
            cnt++;
         else if(boolmotiondone == true && status[axisno] != HOME_DONE)  {
            if(axisno == X_AXIS) {
               MainForm->pnlStatusX->Color = clLime;
               MainForm->WriteSystemLog(">XAxis Home Done.");

               // 2023 8 2 - chc Step
               MainForm->pnlMotionHomeUnit->Caption = "X Home Completed.";

            }
            else if(axisno == Y_AXIS) {
               MainForm->pnlStatusY->Color = clLime;
               MainForm->WriteSystemLog(">YAxis Home Done.");

               // 2023 8 2 - chc Step
               MainForm->pnlMotionHomeUnit->Caption = "Y Home Completed.";

            }
            else if(axisno == Z_AXIS) {
               MainForm->pnlStatusZ->Color = clLime;
               MainForm->WriteSystemLog(">ZAxis Home Done.");

               // 2023 8 2 - chc Step
               MainForm->pnlMotionHomeUnit->Caption = "Z Home Completed.";

            }
            else if(axisno == T_AXIS) {
               MainForm->pnlStatusT->Color = clLime;
               MainForm->WriteSystemLog(">Z1Axis Home Done.");

               // 2023 8 2 - chc Step
               MainForm->pnlMotionHomeUnit->Caption = "Z1 Home Completed.";

            }
            else if(axisno == W_AXIS) {
               MainForm->pnlStatusW->Color = clLime;
               MainForm->WriteSystemLog(">WAxis Home Done.");

               // 2023 8 2 - chc Step
               MainForm->pnlMotionHomeUnit->Caption = "W Home Completed.";

            }
            status[axisno] = HOME_DONE;
            MainForm->combAxis->ItemIndex = axisno;
            DelayTimeM3(200);
            cnt++;
         }
      }
      if(cnt >= MAX_AXIS_NO) {
         // �u�n���@���N�i�H

         // 2021 4 25 - chc All to 0
         int errcnt = 0;
         for(no=0 ; no<MAX_AXIS_NO ; no++) {
            axisno = no;
            GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
            // Absolute move
            maxvel = (maxvel*2) / 3;
            pos = 0;
            GetAxisName((int)axisno);
            name = MainForm->AxisName;
            MainForm->WriteSystemLog(">" + name + "Axis Move to 0...");
            ret = AbsoluteMove(axisno,pos,startvel,maxvel,tacc,tdec);
            if(ret == ERR_NoError)
               MainForm->WriteSystemLog(">" + name + "Axis Move to 0 done.");
            else {
               MainForm->WriteSystemLog(">" + name + "Axis Move to 0 fail!");

               // 2023 8 4 - chc ���O�JError[����]�]��APS_set_position()
               //errcnt++;

            }
            Sleep(100);
         }
         // Error
         if(errcnt > 0) {
            MainForm->pnlSystemMessage->Caption = "Home Done, Move 0 fail!";
            MainForm->WriteSystemLog(">Home Done, Move 0 fail!");
            goto homeerr;
         }

         break;
      }

      DelayTimeM3(50);
      counter++;
      MainForm->pnlSystemMessage->Caption = "Wait Homing... " + IntToStr(counter);
      MainForm->WriteSystemLog(">Wait Homing... " + IntToStr(counter));
      // 10sec: 50*200
      // �����ɶ�100sec
      if(counter > 2000) {
         MainForm->pnlSystemMessage->Caption = "Home Done Timeout!";
         MainForm->WriteSystemLog(">Home Done Fail: Timeout!");
homeerr:
         MainForm->pnlAllHomeStatus->Color = clRed;
         MainForm->pnlAllHomeStatus1->Color = clRed;
         // Beep�n
         Beep(500);
         // Alarm Message
         MainForm->pnlAlarmMessage->Caption = " AllHome(Done) Error!";

         // 2021 5 7 - chc ReStart System
         MainForm->pnlStartMessage->Caption = "Motion abnormal!";
         MainForm->pnlMoving->Caption = "Restart the System.";
         MainForm->pnlMoving->Visible = true;

         // 2023 8 2 - chc Step
         MainForm->pnlMotionHomeUnit->Caption = "Error!";
         MainForm->pnlMotionHomeUnit->Font->Color = clRed;

         return;
      }
   }

allhomedone:

   // 2023 8 21 - chc L�W�h�A�U�Ө�-EL(�]��0)
   MainForm->WriteSystemLog(">HomeAll L�W�A�U��-EL");
   ResetPositionAxis(L_AXIS);
   ResetCommandAxis(L_AXIS);
   MoveToL(5000, false);
   MoveToL(-3000, false);

   MainForm->WriteSystemLog(">HomeAll Completed");
   MainForm->pnlSystemMessage->Caption = "Home Completed.";
   MainForm->pnlSystemMessage->Caption = "Home Completed.";
   // �O�_����LHome?
   MainForm->boolHomeDone = true;
   MainForm->pnlAllHomeStatus->Color = clLime;
   MainForm->pnlAllHomeStatus1->Color = clLime;
   MainForm->pnlAlarmMessage->Caption = "";
   MainForm->pcOP->Enabled = true;

   // �N�Ҧ��bReset
   DelayTimeM5(1000);
   for(no=0 ; no<MAX_AXIS_NO ; no++) {
      MainForm->combAxis->ItemIndex = no;
      // �]�nReset Command
      MainForm->CurrentAxisNo = MainForm->combAxis->ItemIndex;

      // 2023 8 4 - chc Reset Axis Command[����)
      //ResetPosition();
      //ResetCommand();
      ResetPositionAxis(no);
      ResetCommandAxis(no);

      DelayTimeM5(100);
   }

   // ����Motion Home
   if(MainForm->pnlStartMessage->Visible == true) {
      MainForm->pnlStartMessage->Visible = false;
      // �YCCD��Live, �۰ʱҰʬ�Live: �Ĥ@���i�ӭn�Ұ�CCD Live
      if(MainForm->btnReviewLive->Caption == "Live" && first == true) {
         MainForm->btnReviewLiveClick(MainForm);
         first = false;
      }

   }

   // ���X/Y��m: Stage�ܷN��
   MainForm->XHome = 89;
   MainForm->YHome = 89;

   GetCommand(X_AXIS, &cmd);
   MainForm->XHomePosition = cmd;
   GetCommand(Y_AXIS, &cmd);
   MainForm->YHomePosition = cmd;
   // XY total length is 200mm: 100mm*10000(0.1um/pulse)
   MainForm->XCenterPosition = 1000000;
   MainForm->YCenterPosition = 1000000;

   // Door�}��/EMC �n����Home�~���~��
   if(MainForm->boolDoorEMC == true) {
      // �b���L���`�~��Enable
      //if(MainForm->pnlAxisError->Visible == false) {
         MainForm->pnlDoorOpen->Visible = false;

         // To Last Position
         MainForm->pnlToLast->Left = 311;
         MainForm->pnlToLast->Top = 408;
         MainForm->pnlToLast->Visible = true;
         if(MainForm->PriorityLevel > PRIORITY_OP) {
            MainForm->laLast->Caption = "To Last Position = " + MainForm->edLastX->Text + "," + MainForm->edLastY->Text +
            "," + MainForm->edLastZ->Text + "," + MainForm->edLastT->Text;
         }
         else {
            MainForm->laLast->Caption = "Back to Last Position?";
         }

         MainForm->boolDoorEMC = false;
         if(MainForm->boolHomeDone == true) {
            MainForm->WriteSystemLog("EMC: Do SetMotionStatus(). - boolHomeDone is True");
         }
         else
            MainForm->WriteSystemLog("EMC: Do SetMotionStatus(). - boolHomeDone is False");
         //MainForm->SetMotionStatus();
      //}
   }

   // �A�]�w�@��!!!???
   MainForm->boolHomeDone = true;

   // 2020 4 27 - chc Motion Done��n��Timer�Ӱ�
   //
   if(efemfirst == true) {
      efemfirst = false;

      // 2021 4 25 - chc => �]��W�b, �G�n��AllHome()�e��EFEM�~��, �ר�ORobot�W�O�_�����άO�_����ORG?
      //    Timer�Ұ�(1000ms), ������~��ܰ�"���I�_�k"
      /*
      if(MainForm->SetupEFEM() == false) {
         MainForm->pnlEFEMReady->Color = clRed;
         MainForm->pnlLeftWindow->Color = clGray;
      }
      else {
         MainForm->pnlEFEMReady->Color = clLime;
         MainForm->pnlLeftWindow->Color = clSilver;
         // TSMC�ק�: �G���O
         // OneLine, Door Open
         if(MainForm->pnlLoadPortS2->Caption == "0" && MainForm->pnlLoadPortS11->Caption == "0") {
            MainForm->btnCassetteLoad->Caption = "UnLoad";
            MainForm->GreenLamp(true);
            MainForm->YellowLamp(false);
         }
         else {
            MainForm->btnCassetteLoad->Caption = "Load";
            MainForm->GreenLamp(false);
            MainForm->YellowLamp(true);
         }
         MainForm->StageFFU(true);
         MainForm->EFEMFFU(true);

      }
      */

      // 2021 5 4 - chc ����Update
      UpdateMotionStatus();
   }
   MainForm->WriteSystemLog("����Motion Home.");

end:

   // �YHomeDone�ˬdVacuum, CDA
   MainForm->WriteSystemLog("SetupEFEM����(MotionHome): �ˬdVacuum, CDA");
   if(MainForm->CheckCDAVacuum() == false) {
      // ReStart System
      MainForm->pnlStartMessage->Caption = "CDA or Vacuum abnormal!";
      MainForm->pnlMoving->Caption = "Restart the System.";
      MainForm->pnlMoving->Visible = true;
      return;
   }

   // 2021 5 7 - chc �ˬdEFEM CDA/Vacuum
   if(MainForm->boolCDAVacuum == true) {
      // �Ұ�
      if(EFEMMode == EFEM_HIRATA) {
         MainForm->pcEFEMH->Enabled = true;
         MainForm->WriteSystemLog("����MotionHome: �]�wpcRobot��true");
      }
      else {
         MainForm->pcEFEMR->Enabled = true;
         MainForm->WriteSystemLog("����MotionHome: �]�wpcEFEMR��true");
      }
   }

   MainForm->btnMotionReset->Visible = false;
   // Reset�U�bStatus
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Z_AXIS] = NO_MOVE;
   MainForm->iAxisMove[T_AXIS] = NO_MOVE;
   MainForm->iAxisMove[L_AXIS] = NO_MOVE;
   MainForm->iAxisMove[W_AXIS] = NO_MOVE;

   // 2021 5 7 - chc ReStart System
   MainForm->pnlMoving->Visible = false;

}
//---------------------------------------------------------------------------
bool __fastcall MoveForwardMoueUp()
{
TMouseButton Button;
TShiftState Shift;
int X, Y;
static bool active = false;

   // Re-Entrant
   if(active == true)
      return false;
   active = true;

   MainForm->MoveMouseUp();

   // Re-Entrant
   active = false;
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall MoveBackwardMoueUp()
{
TMouseButton Button;
TShiftState Shift;
int X, Y;
static bool active = false;

   // Re-Entrant
   if(active == true)
      return false;
   active = true;

   MainForm->BackwardMouseUp();

   // Re-Entrant
   active = false;
   return true;
}
//---------------------------------------------------------------------------
void __fastcall InitAlarmStatus()
{

   MainForm->AlarmStatus.boolCDA          = false;
   MainForm->AlarmStatus.boolVacuum       = false;
   MainForm->AlarmStatus.boolDoor         = false;
   MainForm->AlarmStatus.boolMotion       = false;
   MainForm->AlarmStatus.boolRobot        = false;
   MainForm->AlarmStatus.boolAlignBlow    = false;
   MainForm->AlarmStatus.boolAlignSuck    = false;
   MainForm->AlarmStatus.boolChuckBlow    = false;
   MainForm->AlarmStatus.boolChuck2Suck   = false;
   MainForm->AlarmStatus.boolChuck4Suck   = false;
   MainForm->AlarmStatus.boolChuck6Suck   = false;
   MainForm->AlarmStatus.boolAlignCCD     = false;
   MainForm->AlarmStatus.boolReviewCCD    = false;
   MainForm->AlarmStatus.boolAOICCD       = false;
   MainForm->AlarmStatus.boolAOILamp      = false;
   MainForm->AlarmStatus.boolThickness    = false;
   MainForm->AlarmStatus.boolDI           = false;
   MainForm->AlarmStatus.boolDO           = false;
   MainForm->AlarmStatus.boolEMC          = false;
   UpdateAlarmStatus();
}
//---------------------------------------------------------------------------
void __fastcall UpdateAlarmStatus()
{

   // 2016 4 18 - chc �Ȥ��B�z
   /*
   // CDA
   if(MainForm->AlarmStatus.boolCDA == false)
      MainForm->pnlCDAAlarm->Color = clSilver;
   else
      MainForm->pnlCDAAlarm->Color = clRed;
   // Vacuum
   if(MainForm->AlarmStatus.boolVacuum == false)
      MainForm->pnlVacuumAlarm->Color = clSilver;
   else
      MainForm->pnlVacuumAlarm->Color = clRed;
   // Door
   if(MainForm->AlarmStatus.boolDoor == false)
      MainForm->pnlDoorAlarm->Color = clSilver;
   else
      MainForm->pnlDoorAlarm->Color = clRed;
   // Motion
   if(MainForm->AlarmStatus.boolMotion == false)
      MainForm->pnlMotionAlarm->Color = clSilver;
   else
      MainForm->pnlMotionAlarm->Color = clRed;
   // Robot
   if(MainForm->AlarmStatus.boolRobot == false)
      MainForm->pnlRobotAlarm->Color = clSilver;
   else
      MainForm->pnlRobotAlarm->Color = clRed;
   // Align Blow
   if(MainForm->AlarmStatus.boolAlignBlow == false)
      MainForm->pnlAlignBlowAlarm->Color = clSilver;
   else
      MainForm->pnlAlignBlowAlarm->Color = clRed;
   // Align Suck
   if(MainForm->AlarmStatus.boolAlignSuck == false)
      MainForm->pnlAlignSuckAlarm->Color = clSilver;
   else
      MainForm->pnlAlignSuckAlarm->Color = clRed;
   // Chuck Blow
   if(MainForm->AlarmStatus.boolChuckBlow == false)
      MainForm->pnlChuckBlowAlarm->Color = clSilver;
   else
      MainForm->pnlChuckBlowAlarm->Color = clRed;
   // Chuck 2 Suck
   if(MainForm->AlarmStatus.boolChuck2Suck == false)
      MainForm->pnlChuck2SuckAlarm->Color = clSilver;
   else
      MainForm->pnlChuck2SuckAlarm->Color = clRed;
   // Chuck 4 Suck
   if(MainForm->AlarmStatus.boolChuck4Suck == false)
      MainForm->pnlChuck4SuckAlarm->Color = clSilver;
   else
      MainForm->pnlChuck4SuckAlarm->Color = clRed;
   // Chuck 6 Suck
   if(MainForm->AlarmStatus.boolChuck6Suck == false)
      MainForm->pnlChuck6SuckAlarm->Color = clSilver;
   else
      MainForm->pnlChuck6SuckAlarm->Color = clRed;
   // Align CCD
   if(MainForm->AlarmStatus.boolAlignCCD == false)
      MainForm->pnlAlignCCDAlarm->Color = clSilver;
   else
      MainForm->pnlAlignCCDAlarm->Color = clRed;
   // Review CCD
   if(MainForm->AlarmStatus.boolReviewCCD == false)
      MainForm->pnlReviewCCDAlarm->Color = clSilver;
   else
      MainForm->pnlReviewCCDAlarm->Color = clRed;
   // AOI CCD
   if(MainForm->AlarmStatus.boolAOICCD == false)
      MainForm->pnlAOICCDAlarm->Color = clSilver;
   else
      MainForm->pnlAOICCDAlarm->Color = clRed;
   // AOI Lamp
   if(MainForm->AlarmStatus.boolAOILamp == false)
      MainForm->pnlAOILampAlarm->Color = clSilver;
   else
      MainForm->pnlAOILampAlarm->Color = clRed;
   // Thickness
   if(MainForm->AlarmStatus.boolThickness == false)
      MainForm->pnlThicknessAlarm->Color = clSilver;
   else
      MainForm->pnlThicknessAlarm->Color = clRed;
   // DI
   if(MainForm->AlarmStatus.boolDI == false)
      MainForm->pnlDIAlarm->Color = clSilver;
   else
      MainForm->pnlDIAlarm->Color = clRed;
   // DO
   if(MainForm->AlarmStatus.boolDO == false)
      MainForm->pnlDOAlarm->Color = clSilver;
   else
      MainForm->pnlDOAlarm->Color = clRed;
   // EMC
   if(MainForm->AlarmStatus.boolEMC == false)
      MainForm->pnlEMCAlarm->Color = clSilver;
   else
      MainForm->pnlEMCAlarm->Color = clRed;
   */
}
//---------------------------------------------------------------------------
// �令PCI-8154
// 2013 10 6 - chc �[�JLow Distance
//void __fastcall GetAxisData(int axisno,F64 *dist,F64 *startvel,F64 *maxvel,F64 *tacc,F64 *tdec,F64 *homevel, F64 *reviewvel, F64*uplimit)
void __fastcall GetAxisData(int axisno,F64 *dist,F64 *startvel,F64 *maxvel,F64 *tacc,F64 *tdec,F64 *homevel, F64 *reviewvel, F64*uplimit, F64 *lowdistance)
{
int ispeed;

   switch(axisno) {
      // X
      case X_AXIS:
         *dist       = MainForm->edDistanceX->Text.ToDouble();
         *startvel   = MainForm->edStartVelX->Text.ToDouble();
         *maxvel     = MainForm->edMaxVelX->Text.ToDouble();
         *tacc       = MainForm->edTaccX->Text.ToDouble();
         *tdec       = MainForm->edTdecX->Text.ToDouble();
         *homevel    = MainForm->edHomeVelX->Text.ToDouble();
         *reviewvel  = MainForm->edReviewVelX->Text.ToDouble();
         *uplimit    = MainForm->edUpLimitX->Text.ToDouble();
         *lowdistance = MainForm->edLowDistanceX->Text.ToDouble();

         // 2023 7 21 - chc Log
         MainForm->WriteSystemLog(">X�bMaxVel: " + IntToStr((int)*maxvel));

         break;
      // Y
      case Y_AXIS:
         *dist       = MainForm->edDistanceY->Text.ToDouble();
         *startvel   = MainForm->edStartVelY->Text.ToDouble();
         *maxvel     = MainForm->edMaxVelY->Text.ToDouble();
         *tacc       = MainForm->edTaccY->Text.ToDouble();
         *tdec       = MainForm->edTdecY->Text.ToDouble();
         *homevel    = MainForm->edHomeVelY->Text.ToDouble();
         *reviewvel  = MainForm->edReviewVelY->Text.ToDouble();
         *uplimit    = MainForm->edUpLimitY->Text.ToDouble();
         *lowdistance = MainForm->edLowDistanceY->Text.ToDouble();

         // 2023 7 21 - chc Log
         MainForm->WriteSystemLog(">Y�bMaxVel: " + IntToStr((int)*maxvel));

         break;
      // Z
      case Z_AXIS:
         *dist       = MainForm->edDistanceZ->Text.ToDouble();
         *startvel   = MainForm->edStartVelZ->Text.ToDouble();
         *maxvel     = MainForm->edMaxVelZ->Text.ToDouble();
         *tacc       = MainForm->edTaccZ->Text.ToDouble();
         *tdec       = MainForm->edTdecZ->Text.ToDouble();
         *homevel    = MainForm->edHomeVelZ->Text.ToDouble();
         *reviewvel  = MainForm->edReviewVelZ->Text.ToDouble();
         *uplimit    = MainForm->edUpLimitZ->Text.ToDouble();
         *lowdistance = MainForm->edLowDistanceZ->Text.ToDouble();

         // 2023 7 21 - chc Log
         MainForm->WriteSystemLog(">Z�bMaxVel: " + IntToStr((int)*maxvel));

         break;
      // T
      case T_AXIS:
         *dist       = MainForm->edDistanceT->Text.ToDouble();
         *startvel   = MainForm->edStartVelT->Text.ToDouble();
         *maxvel     = MainForm->edMaxVelT->Text.ToDouble();
         *tacc       = MainForm->edTaccT->Text.ToDouble();
         *tdec       = MainForm->edTdecT->Text.ToDouble();
         *homevel    = MainForm->edHomeVelT->Text.ToDouble();
         *reviewvel  = MainForm->edReviewVelT->Text.ToDouble();
         *uplimit    = MainForm->edUpLimitT->Text.ToDouble();
         *lowdistance = MainForm->edLowDistanceT->Text.ToDouble();

         // 2023 7 21 - chc Log
         MainForm->WriteSystemLog(">T�bMaxVel: " + IntToStr((int)*maxvel));

         break;
      // L
      case L_AXIS:
         *dist       = MainForm->edDistanceL->Text.ToDouble();
         *startvel   = MainForm->edStartVelL->Text.ToDouble();
         *maxvel     = MainForm->edMaxVelL->Text.ToDouble();
         *tacc       = MainForm->edTaccL->Text.ToDouble();
         *tdec       = MainForm->edTdecL->Text.ToDouble();
         *homevel    = MainForm->edHomeVelL->Text.ToDouble();
         *reviewvel  = MainForm->edReviewVelL->Text.ToDouble();
         *uplimit    = MainForm->edUpLimitL->Text.ToDouble();
         *lowdistance = MainForm->edLowDistanceL->Text.ToDouble();

         // 2023 7 21 - chc Log
         MainForm->WriteSystemLog(">L�bMaxVel: " + IntToStr((int)*maxvel));

         break;
      // T
      case W_AXIS:
         *dist       = MainForm->edDistanceW->Text.ToDouble();
         *startvel   = MainForm->edStartVelW->Text.ToDouble();
         *maxvel     = MainForm->edMaxVelW->Text.ToDouble();
         *tacc       = MainForm->edTaccW->Text.ToDouble();
         *tdec       = MainForm->edTdecW->Text.ToDouble();
         *homevel    = MainForm->edHomeVelW->Text.ToDouble();
         *reviewvel  = MainForm->edReviewVelW->Text.ToDouble();
         *uplimit    = MainForm->edUpLimitW->Text.ToDouble();
         *lowdistance = MainForm->edLowDistanceW->Text.ToDouble();

         // 2023 7 21 - chc Log
         MainForm->WriteSystemLog(">W�bMaxVel: " + IntToStr((int)*maxvel));

         break;
   }

   // �b���o�ѼƮɰ������t��
   // 2015 5 15 - chc �t�פ��
   // 2016 12 8 - chc ��_�οﶵ: Low/Middle/High
   //   0.2%/50%/100%
   MainForm->JogSpeed = MainForm->rgSpeed->ItemIndex;
   if(MainForm->rgSpeed->ItemIndex == JOG_LOW_SPEED) {

      // 2016 12 13 - chc re calculate
      //*maxvel *= 0.002;
      // 2016 12 20 - chc �令1/100
      // => �令6/1000
      ispeed = *maxvel;

      // 2016 12 30 - chc �ϥγ]�w��
      //ispeed = ispeed * 0.005;
      //if(ispeed < 10)
      //   ispeed = 10;
      double factor;
      if(MainForm->pnlBit7->Color == clLime) {
         factor = MainForm->edSpeedTurboLow->Text.ToDouble() / 100.0;
      }
      else {
         factor = MainForm->edSpeedGeneralLow->Text.ToDouble() / 100.0;
      }
      ispeed = ispeed * factor;

      *maxvel = ispeed;

      // 2023 7 21 - chc Log
      MainForm->WriteSystemLog(">�bMaxVel(L): " + IntToStr((int)*maxvel));

   }
   else if(MainForm->rgSpeed->ItemIndex == JOG_MIDDLE_SPEED) {
      // 2016 12 20 - chc �令25%
      // => �令20%

      // 2016 12 30 - chc �ϥγ]�w��
      //*maxvel *= 0.20;
      double factor;
      if(MainForm->pnlBit8->Color == clLime) {
         factor = MainForm->edSpeedTurboMiddle->Text.ToDouble() / 100.0;
      }
      else {
         factor = MainForm->edSpeedGeneralMiddle->Text.ToDouble() / 100.0;
      }
      ispeed = *maxvel;
      ispeed = ispeed * factor;
      *maxvel = ispeed;

      // 2023 7 21 - chc Log
      MainForm->WriteSystemLog(">�bMaxVel(M): " + IntToStr((int)*maxvel));

   }
   else if(MainForm->rgSpeed->ItemIndex == JOG_HIGH_SPEED) {

      // 2016 12 30 - chc �ϥγ]�w��
      //*maxvel *= 1.0;
      double factor;
      if(MainForm->pnlBit9->Color == clLime) {
         factor = MainForm->edSpeedTurboHigh->Text.ToDouble() / 100.0;
      }
      else {
         factor = MainForm->edSpeedGeneralHigh->Text.ToDouble() / 100.0;
      }
      ispeed = *maxvel;
      ispeed = ispeed * factor;
      *maxvel = ispeed;

      // 2023 7 21 - chc Log
      MainForm->WriteSystemLog(">�bMaxVel(H): " + IntToStr((int)*maxvel));

   }
   //

   // 2016 12 13 - chc Display current speed
   // 2019 7 22 - chc ����s, ���UpdateMotionStatus()�B�z
   //MainForm->pnlCurrentSpeed->Caption = IntToStr((int)*maxvel);

   // �ˬd��t
   if(*startvel > *maxvel)
      *startvel = *maxvel / 2;

   // 2016 4 21 - chc Vel�W��: 20000/20000/20000/1000000
   if(*maxvel > *uplimit)
      *maxvel = *uplimit;
   if(*homevel > *uplimit)
      *homevel = *uplimit;
   if(*reviewvel > *uplimit)
      *reviewvel = *uplimit;

   // 2016 12 13 - chc Safe
   if(axisno == X_AXIS || axisno == Y_AXIS) {
      if(*maxvel > 3000000)
         *maxvel = 3000000;
   }
   else {
      if(*maxvel > 3000000)
         *maxvel = 3000000;
   }

   // 2023 7 21 - chc Log
   MainForm->WriteSystemLog(">�bMaxVel(final): " + IntToStr((int)*maxvel));

}
//---------------------------------------------------------------------------
// APS: Home Move Positive
void __fastcall HomeOneAxis()
{
I16 axisno,homemode;
U16 motionstatus,iostatus;
F64 pos;
I32 cmd;
I16 ret;
int counter = 1;
I16 Motion_status;
bool boolnel = true;
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
AnsiString name;
TLMDComboBox* combobox;
F64 lowdistance;

   MainForm->pnlHomeStatus->Color = clSilver;
   axisno = MainForm->combAxis->ItemIndex;

   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   // ���o�ӧOHomeMode
   GetAxisName((int)axisno);
   name = MainForm->AxisName;

   combobox = (TLMDComboBox *)(MainForm->FindComponent("combHomeMode" + name));
   homemode = combobox->Text.ToInt();

   // Home Mode 4
   homemode = 4;
   // ����homevel
   maxvel = maxvel / 3;

   // ������-EL, HomeMove+
   MainForm->pnlSystemMessage->Caption = "Move to -EL...";
   Application->ProcessMessages();

   // ���ϦV��-EL(�]�w��0�I)
   // ret: 0-off, 1-on
   boolnel = GetNELStatus(axisno);
   // ���b-EL
   if(boolnel == false) {
      MainForm->WriteSystemLog(IntToStr(axisno+1) + "Move to -EL: " + FloatToStr(maxvel) + " : " + FloatToStr(pos));
      // ���oPosition
      if(MotionMode == MOTION_MODE_APS) {
         I32 ipos;
         APS_get_position(axisno+StartAxisNo,&ipos);
         cmd = ipos;
         pos = -9000000;                                                           // 90mm
         MainForm->pnlSystemMessage->Caption = IntToStr(cmd) + " To " + FloatToStr(pos);
         ret = APS_relative_move(axisno+StartAxisNo,(int)pos,(int)maxvel);
      }

      counter = 1;
      // ��-EL
      while(1) {
         boolnel = GetNELStatus(axisno);
         if(boolnel == true)
            break;
         DelayTimeM3(50);
         counter++;
         // 10sec: 50*200 �令100��
         if(counter > 2000) {
            MainForm->pnlSystemMessage->Caption = "-EL Timeout!";
            MainForm->pnlHomeStatus->Color = clRed;
            // Beep�n
            Beep(500);
            MainForm->pnlAlarmMessage->Caption = " OneHome(-EL) Error!";
            return;
         }
      }
   }
   else{
      MainForm->WriteSystemLog(IntToStr(axisno+1) + "-EL On, Stop Moving");
   }
dohome:

   // �H-EL �����I
   DelayTimeM3(100);
   // HomeMove+
   MainForm->pnlSystemMessage->Caption = "Homing...";
   if(MotionMode == MOTION_MODE_APS) 
       APS_home_move(axisno+StartAxisNo);

   DelayTimeM3(500);
   // ��Motion Done
   counter = 1;
   bool boolmotiondone = false;
   while(1) {
      boolmotiondone = GetMotionDoneStatus(axisno);
      if(boolmotiondone == true)
         break;

      DelayTimeM3(50);
      counter++;
      // 20sec: 50*400, ��100��
      if(counter > 2000) {
         MainForm->pnlSystemMessage->Caption = "Home Timeout!";
         MainForm->pnlHomeStatus->Color = clRed;
         // Beep�n
         Beep(500);
         MainForm->pnlAlarmMessage->Caption = " AllHome Error!";
         return;
      }
   }
nothome:

   //----------------------------------------
oneaxisdone:

   DelayTimeM3(200);
   MainForm->pnlSystemMessage->Caption = "Home Completed.";
   MainForm->pnlHomeStatus->Color = clLime;
   // ���X/Y��m, �O���U�bHome Position
   GetCommand(axisno, &cmd);
   if(axisno == X_AXIS) {
      MainForm->XHomePosition = cmd;
      MainForm->XHome = 87;
   }
   else if(axisno == Y_AXIS) {
      MainForm->YHomePosition = cmd;
      MainForm->YHome = 90;
   }

   // ���������~�O0�I
   DelayTimeM3(100);

   ResetPosition();
   ResetCommand();

}
//---------------------------------------------------------------------------
// Wait Motion done
bool __fastcall WaitMotionDone(int axisno, int ms)
{
static bool active = false;
I32 cmd;
I16 Motion_status;
int counter;
int max;

   // Re-Entrant
   if(active == true) {
      //@#@# AddAlignMessage("A)WaitMotionDone Re-Entrant!");
      return false;
   }
   active = true;

   max = ms / 10;
   DelayTimeM2(10);
   counter = 0;
   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         Motion_status = 0;
         I32 done;
         done = APS_motion_status(axisno+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            Motion_status = 1;
      }
      if(Motion_status == 0 || Motion_status == 17 || Motion_status == 18) {
         break;
      }
      else {
         counter++;
         // 10sec: 50*200
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion Timeout!";
            // Re-Entrant
            active = false;
            return false;
         }
         DelayTimeM2(10);
      }
   }
   // Re-Entrant
   active = false;

   return true;
}
//---------------------------------------------------------------------------
void __fastcall ResetCommand()
{
I16 i = 0;
I16 AxisNum = 0;
I16 axisno;

   if(MotionMode == MOTION_MODE_APS) {
      for(axisno=0 ; axisno<MAX_AXIS_NO ; axisno++) {
         APS_set_command(axisno+StartAxisNo,0);
      }
      return;
   }
}
//---------------------------------------------------------------------------
void __fastcall ResetPosition()
{
I16 i = 0;
I16 AxisNum = 0;
I16 axisno;

   MainForm->pnlSystemMessage->Caption = "Reset Counter...";
   MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);

   if(MotionMode == MOTION_MODE_APS) {
      for(axisno=0 ; axisno<MAX_AXIS_NO ; axisno++) {

         // 2023 8 4 - chc �OPosition[����]
         //APS_set_command(axisno+StartAxisNo,0);
         APS_set_position(axisno+StartAxisNo,0);

      }
      return;
   }
}
//---------------------------------------------------------------------------
// 2023 8 4 - chc Reset Axis Command[����)
void __fastcall ResetCommandAxis(int axisno)
{
I32 pos;

   MainForm->pnlSystemMessage->Caption = "ResetAxis Command..." + IntToStr(axisno);
   MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
   pos = 0;
   APS_set_command(axisno+StartAxisNo,pos);
   MainForm->pnlSystemMessage->Caption = "ResetAxis Command." + IntToStr(axisno);
   MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
}
//---------------------------------------------------------------------------
// 2023 8 4 - chc Reset Axis Position[����)
void __fastcall ResetPositionAxis(int axisno)
{
I32 pos;

   MainForm->pnlSystemMessage->Caption = "ResetAxis Counter..." + IntToStr(axisno);
   MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
   pos = 0;
   APS_set_position(axisno+StartAxisNo,pos);
   MainForm->pnlSystemMessage->Caption = "ResetAxis Counter." + IntToStr(axisno);
   MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
}
//---------------------------------------------------------------------------
void __fastcall ResetErrorCounter()
{
I16 i = 0;
I16 AxisNum = 0;
I16 axisno;

   // 7856�L���R�O
   if(MotionMode == MOTION_MODE_APS)
      return;
}
//---------------------------------------------------------------------------
void __fastcall SetTiltPosition()
{
I32 cmd;
F64 fcmd;

   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->edTiltX->Text = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->edTiltY->Text = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->edTiltZ->Text = IntToStr(ipos);
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      MainForm->edTiltT->Text = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// ��AOI�I - �T�b�P�ɲ���
// ??? Table���ʫe�n���ULF�b!!!
// ��ɱ׶q���I
void __fastcall ToTiltPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z,t;

// 2013 10 6 - chc �[�JLow Distance
F64 lowdistance;

// 2016 8 31 - chc Set position
bool flag = true;
AnsiString msg;
int dx,dy,dz,zlimit;
bool booloffset = false;

   MainForm->pnlToTiltPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->edTiltX->Text.ToInt();
   y = MainForm->edTiltY->Text.ToInt();
   z = MainForm->edTiltZ->Text.ToInt();
   t = MainForm->edTiltT->Text.ToInt();

   // 2021 5 4 - chc �Y�O�b������m, �n���vX/Y/Z
   // 2023 8 3 - chc �W�߶b���ݭn��
   /*
   if(MainForm->IsHeadHorizontal() == true) {
      booloffset = true;
      zlimit = MainForm->GetZLimit();
      dx = MainForm->edTiltX->Text.ToInt() - MainForm->edZeroX->Text.ToInt();
      dy = MainForm->edTiltY->Text.ToInt() - MainForm->edZeroY->Text.ToInt();
      dz = MainForm->edTiltZ->Text.ToInt() - MainForm->edZeroZ->Text.ToInt();
      msg.sprintf("Check�b������m: dx,dy,dz=%d,%d,%d",dx,dy,dz);
      MainForm->WriteSystemLog(msg);
      x += dx;
      y += dx;
      z += dx;
      if(z > zlimit)
         z = zlimit;
   }
   */

   // 2023 1 28 - chc edY45Offset
   // 2023 2 21 - chc ���B�z
   /*
   if(boolInMeasureRun == true) {
      double foffset;
      int ioffset;
      foffset = MainForm->edY45Offset->Text.ToDouble();
      if(foffset != 0) {
         AnsiString msg;
         ioffset = (int)(foffset / Y_RESOLUTION);
         msg.sprintf("[Run-ToAOIPosition]45��Y,YOffset=%d,%d",(int)y,ioffset);
         MainForm->WriteSystemLog(msg);
         y -= ioffset;

         // 2023 2 21 - chc ��ڦ�m
         msg.sprintf("[Run-ToAOIPosition]45��FinalY= %d",(int)y);
         MainForm->WriteSystemLog(msg);

      }
   }
   */
   
   // �̦��ǰ�X/Y/Z/T
   MoveToXYZT(x,y,z,t,2);

   // 2021 5 4 - chc �Y�O�b������m, �n���vX/Y/Z
   // �]MoveToXYZT()���|��X/Y/Z
   if(booloffset == true) {
      msg.sprintf("Low speed compensation: dx,dy,dz=%d,%d,%d",dx,dy,dz);
      MainForm->WriteSystemLog(msg);
      MainForm->pnlSystemMessage->Caption = msg;
      int oldspeed = MainForm->rgSpeed->ItemIndex;
      MainForm->rgSpeed->ItemIndex = 0;
      DoRelativeMove(X_AXIS, dx);
      DoRelativeMove(Y_AXIS, dy);
      DoRelativeMove(Z_AXIS, dz);
      MainForm->rgSpeed->ItemIndex = oldspeed;
   }

   return;
}
//---------------------------------------------------------------------------
// 2013 2 17 - chc Wait Motion X/Y/Z done
bool __fastcall WaitMotionXYZDone(int ms)
{
I32 cmd;
I16 mstatusx,mstatusy,mstatusz;
int counter;
int max,axisno;

   counter = 0;
   max = ms / 10;
   DelayTimeM4(10);

   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         mstatusx = 0;
         mstatusy = 0;
         mstatusz = 0;
         I32 done;
         done = APS_motion_status(X_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusx = 1;
         done = APS_motion_status(Y_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusy = 1;
         done = APS_motion_status(Z_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusz = 1;
      }
      if((mstatusx == 0 || mstatusx == 17 || mstatusx == 18) &&
         (mstatusy == 0 || mstatusy == 17 || mstatusy == 18) &&
         (mstatusz == 0 || mstatusz == 17 || mstatusz == 18)) {
         break;
      }
      else {
         DelayTimeM4(10);
         counter++;
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion XYZ Done Timeout!";
            return false;
         }
      }
   }
   return true;
}
//---------------------------------------------------------------------------
// 2021 4 19 - chc Wait Motion X/Y/Z/T done
bool __fastcall WaitMotionXYZTDone(int ms)
{
I32 cmd;
I16 mstatusx,mstatusy,mstatusz,mstatust;
int counter;
int max,axisno;

   counter = 0;
   max = ms / 10;
   DelayTimeM4(10);

   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         mstatusx = 0;
         mstatusy = 0;
         mstatusz = 0;
         mstatust = 0;
         I32 done;
         done = APS_motion_status(X_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusx = 1;
         done = APS_motion_status(Y_AXIS+StartAxisNo);
         if((done & 0x01) == 0)
            mstatusy = 1;
         done = APS_motion_status(Z_AXIS+StartAxisNo);
         if((done & 0x01) == 0)
            mstatusz = 1;
         done = APS_motion_status(T_AXIS+StartAxisNo);
         if((done & 0x01) == 0)
            mstatust = 1;
      }
      if((mstatusx == 0 || mstatusx == 17 || mstatusx == 18) &&
         (mstatusy == 0 || mstatusy == 17 || mstatusy == 18) &&
         (mstatusz == 0 || mstatusz == 17 || mstatusz == 18) &&
         (mstatust == 0 || mstatust == 17 || mstatust == 18)) {
         break;
      }
      else {
         DelayTimeM4(10);
         counter++;
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion XYZT Done Timeout!";
            return false;
         }
      }
   }

   // 2021 9 11 - chc �[�t: MOVE_WAIT, �n�]��NO_MOVE
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Z_AXIS] = NO_MOVE;
   MainForm->iAxisMove[T_AXIS] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2013 2 17 - chc ������
// mode 1 - X
//      2 - Y
//      3 - XY
void __fastcall WaitMotionDoneXY(int mode, int ms)
{
I32 cmd;
I16 mstatusx,mstatusy;
int counter;
int max,axisno;

   counter = 0;
   max = ms / 10;
   DelayTimeM5(10);

   mstatusx = 0;
   mstatusy = 0;
   if(mode == 1 || mode == 3) {
      if(MotionMode == MOTION_MODE_APS) {
         mstatusx = 0;
         I32 done;
         done = APS_motion_status(X_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusx = 1;
      }
   }
   if(mode == 2 || mode == 3) {
      if(MotionMode == MOTION_MODE_APS) {
         mstatusy = 0;
         I32 done;
         done = APS_motion_status(Y_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusy = 1;
      }
   }
   while(1) {
      if(mode == 1 || mode == 3) {
         if(mstatusx != 0) {
            if(MotionMode == MOTION_MODE_APS) {
               mstatusx = 0;
               I32 done;
               done = APS_motion_status(X_AXIS+StartAxisNo);
               // ��bit 0 : ������0(Done)
               if((done & 0x01) == 0)
                  mstatusx = 1;
            }
         }
      }
      if(mode == 2 || mode == 3) {
         if(mstatusy != 0) {
            if(MotionMode == MOTION_MODE_APS) {
               mstatusy = 0;
               I32 done;
               done = APS_motion_status(Y_AXIS+StartAxisNo);
               // ��bit 0 : ������0(Done)
               if((done & 0x01) == 0)
                  mstatusy = 1;
            }
         }
      }
      if((mstatusx == 0 || mstatusx == 17 || mstatusx == 18) &&
         (mstatusy == 0 || mstatusy == 17 || mstatusy == 18)) {
         break;
      }
      else {
         DelayTimeM5(10);
         counter++;
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion XY Done Timeout!";

// 2013 2 17 - chc �Ȥ���
//            return false;

            // 2019 7 29 - chc �n���_
            break;

         }
      }

   }

// 2013 2 17 - chc �Ȥ���
//   return true;
}
//---------------------------------------------------------------------------
// 2013 3 14 - chc ������X/Y/Z
// mode : ����
void __fastcall WaitMotionDoneXYZ(int mode, int ms)
{
I32 cmd;
I16 mstatusx,mstatusy,mstatusz;
int counter;
int max,axisno;

   counter = 0;
   max = ms / 10;
   DelayTimeM5(10);

   mstatusx = 0;
   mstatusy = 0;
   mstatusz = 0;
   if(MotionMode == MOTION_MODE_APS) {
      I32 done;
      done = APS_motion_status(X_AXIS+StartAxisNo);
      // ��bit 0 : ������0(Done)
      if((done & 0x01) == 0)
         mstatusx = 1;
      done = APS_motion_status(Y_AXIS+StartAxisNo);
      // ��bit 0 : ������0(Done)
      if((done & 0x01) == 0)
         mstatusy = 1;
      done = APS_motion_status(Z_AXIS+StartAxisNo);
      // ��bit 0 : ������0(Done)
      if((done & 0x01) == 0)
         mstatusz = 1;
   }

   while(1) {
      if(mstatusx != 0) {
         if(MotionMode == MOTION_MODE_APS) {
            I32 done;
            mstatusx = 0;
            done = APS_motion_status(X_AXIS+StartAxisNo);
            // ��bit 0 : ������0(Done)
            if((done & 0x01) == 0)
               mstatusx = 1;
         }
      }
      if(mstatusy != 0) {
         if(MotionMode == MOTION_MODE_APS) {
            I32 done;
            mstatusy = 0;
            done = APS_motion_status(Y_AXIS+StartAxisNo);
            // ��bit 0 : ������0(Done)
            if((done & 0x01) == 0)
               mstatusy = 1;
         }
      }
      if(mstatusz != 0) {
         if(MotionMode == MOTION_MODE_APS) {
            I32 done;
            mstatusz = 0;
            done = APS_motion_status(Z_AXIS+StartAxisNo);
            // ��bit 0 : ������0(Done)
            if((done & 0x01) == 0)
               mstatusz = 1;
         }
      }
      if((mstatusx == 0 || mstatusx == 17 || mstatusx == 18) &&
         (mstatusy == 0 || mstatusy == 17 || mstatusy == 18) &&
         (mstatusz == 0 || mstatusz == 17 || mstatusz == 18)) {

         break;
      }
      else {
         DelayTimeM5(10);
         counter++;
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion XY Done Timeout!";
            break;
         }
      }
   }
}
//---------------------------------------------------------------------------
// 2013 2 17 - chc io status
void __fastcall DecodeIOStatus(int axisno,U16 io_sts)
{
TPanel *rdy,*alm,*pel,*nel,*org,*dir,*reserved1,*pcs,*erc,*ez,*reserved2,*latch,*sd,*inp,*svon;
AnsiString name,msg;

   GetAxisName(axisno);
   name = MainForm->AxisName;

   rdy       = (TPanel *)(MainForm->FindComponent("pnlRDY" + name));
   alm       = (TPanel *)(MainForm->FindComponent("pnlALM" + name));
   pel       = (TPanel *)(MainForm->FindComponent("pnlPEL" + name));
   nel       = (TPanel *)(MainForm->FindComponent("pnlNEL" + name));
   org       = (TPanel *)(MainForm->FindComponent("pnlORG" + name));
   dir       = (TPanel *)(MainForm->FindComponent("pnlDIR" + name));
   reserved1 = (TPanel *)(MainForm->FindComponent("pnlReserved1" + name));
   pcs       = (TPanel *)(MainForm->FindComponent("pnlPCS" + name));
   erc       = (TPanel *)(MainForm->FindComponent("pnlERC" + name));
   ez        = (TPanel *)(MainForm->FindComponent("pnlEZ" + name));
   reserved2 = (TPanel *)(MainForm->FindComponent("pnlReserved2" + name));
   latch     = (TPanel *)(MainForm->FindComponent("pnlLatch" + name));
   sd        = (TPanel *)(MainForm->FindComponent("pnlSD" + name));
   inp       = (TPanel *)(MainForm->FindComponent("pnlINP" + name));
   svon      = (TPanel *)(MainForm->FindComponent("pnlSVON" + name));

   // ALM       - 0     0x0001          *
   // PEL       - 1     0x0002  *
   // NEL       - 2     0x0004  *
   // ORG       - 3     0x0008  *
   // EMG       - 4     0x0010
   // EZ        - 5     0x0020  *
   // INP       - 6     0x0040  *
   // SVON      - 7     0x0080  *
   // RDY       - 8     0x0100          *
   // DIR       - 9     0x0200  *
   // PCS       - 10    0x0400  *
   // ERC       - 11    0x0800  *
   // Reserved2 - 12    0x1000
   // Latch     - 13    0x2000  *
   // SD        - 14    0x4000  *
   if(MotionMode == MOTION_MODE_APS) {
      // ALM
      if(io_sts & 0x0001) {
         alm->Color = clRed;

         // 2021 9 15 - chc Axis Error
         if(alm->Color == clSilver) {
            if(axisno == X_AXIS)
               MainForm->SetSECSAlarm(23001,1,1,"X_Axis Abnormal");
            else if(axisno == Y_AXIS)
               MainForm->SetSECSAlarm(24001,1,1,"Y_Axis Abnormal");
            else if(axisno == Z_AXIS)
               MainForm->SetSECSAlarm(25001,1,1,"Z_Axis Abnormal");
            else if(axisno == T_AXIS)
               MainForm->SetSECSAlarm(26001,1,1,"T_Axis Abnormal");
            else if(axisno == L_AXIS)
               MainForm->SetSECSAlarm(27001,1,1,"L_Axis Abnormal");
            else if(axisno == W_AXIS)
               MainForm->SetSECSAlarm(28001,1,1,"W_Axis Abnormal");
         }

      }
      else {
         alm->Color = clSilver;

         // 2021 9 15 - chc Axis Error
         if(alm->Color == clRed) {
            if(axisno == X_AXIS)
               MainForm->SetSECSAlarm(23001,0,1,"X_Axis Abnormal");
            else if(axisno == Y_AXIS)
               MainForm->SetSECSAlarm(24001,0,1,"Y_Axis Abnormal");
            else if(axisno == Z_AXIS)
               MainForm->SetSECSAlarm(25001,0,1,"Z_Axis Abnormal");
            else if(axisno == T_AXIS)
               MainForm->SetSECSAlarm(26001,0,1,"T_Axis Abnormal");
            else if(axisno == L_AXIS)
               MainForm->SetSECSAlarm(27001,0,1,"L_Axis Abnormal");
            else if(axisno == W_AXIS)
               MainForm->SetSECSAlarm(28001,0,1,"W_Axis Abnormal");
         }

      }
      // RDY
      if(io_sts & 0x0100)
         rdy->Color = clRed;
      else
         rdy->Color = clSilver;
      // PEL
      if(io_sts & 0x0002)
         pel->Color = clRed;
      else
         pel->Color = clSilver;
      // NEL
      if(io_sts & 0x0004)
         nel->Color = clRed;
      else
         nel->Color = clSilver;
      // ORG
      if(io_sts & 0x0008)
         org->Color = clRed;
      else
         org->Color = clSilver;
      // DIR
      if(io_sts & 0x0200)
         dir->Color = clRed;
      else
         dir->Color = clSilver;
      // Reserved1
      //if(io_sts & 0x0040)
      //   reserved1->Color = clRed;
      //else
      //   reserved1->Color = clSilver;
      // PCS
      if(io_sts & 0x0400)
         pcs->Color = clRed;
      else
         pcs->Color = clSilver;
      // ERC
      if(io_sts & 0x0800)
         erc->Color = clRed;
      else
         erc->Color = clSilver;
      // EZ
      if(io_sts & 0x0020)
         ez->Color = clRed;
      else
         ez->Color = clSilver;
      // Reserved2
      //if(io_sts & 0x0400)
      //   reserved2->Color = clRed;
      //else
      //   reserved2->Color = clSilver;
      // Latch
      if(io_sts & 0x2000)
         latch->Color = clRed;
      else
         latch->Color = clSilver;
      // SD
      if(io_sts & 0x4000)
         sd->Color = clRed;
      else
         sd->Color = clSilver;
      // INP
      if(io_sts & 0x0040)
         inp->Color = clRed;
      else
         inp->Color = clSilver;
      // SVON
      if(io_sts & 0x0080)
         svon->Color = clRed;
      else
         svon->Color = clSilver;
      return;
   }

   // RDY
   // 2019 7 8 - chc �令��Ready
   //if(io_sts & 0x0001)
   //   rdy->Color = clRed;
   //else
   //   rdy->Color = clSilver;

   // ALM
   // 2019 7 8 - chc �令��Ready
   //if(io_sts & 0x0002) {
   //   alm->Color = clRed;
   // 2019 8 5 - chc X/Y���V, Z�ϦV
   //if((io_sts & 0x0001) == 0) {
   // 2019 11 12 - chc �]�w�U�bRDY: X/Y/Z=1/1/0
   //if(((axisno == X_AXIS || axisno == Y_AXIS) && (io_sts & 0x0001) == 0) || (axisno == Z_AXIS && (io_sts & 0x0001) == 1)) {
   if((axisno == X_AXIS && (io_sts & 0x0001) != MainForm->XRDY) ||
      (axisno == Y_AXIS && (io_sts & 0x0001) != MainForm->YRDY) ||
      (axisno == Z_AXIS && (io_sts & 0x0001) != MainForm->ZRDY)) {

      rdy->Color = clSilver;

      // 2013 2 26 - chc �b�����`!
      if(MainForm->pnlAxisError->Visible == false) {
         AxisErrorNo = axisno;
         msg = AnsiString("Axis-") + name + " Abnormal! System Stop.";

         // 2019 11 26 - chc �b�����`
         MainForm->boolMotionError = true;

         // 2016 7 27 - chc Check front door
         MainForm->pnlAxisError->Font->Size = 24;
         if(MainForm->boolSystemStarted == false) {
            if(axisno == X_AXIS) {
               msg = "Please restart after pressing the power";

               // 2021 5 5 - chc ������IPage
               MainForm->pcOP->ActivePage = MainForm->tsHome;

               MainForm->pnlAxisError->Font->Size = 16;
            }
         }

         MainForm->pnlAxisError->Caption = msg;
         MainForm->pnlAxisError->Visible = true;

         // 2016 4 21 - chc ���i����
         //MainForm->MotionStatus(false);

         // 2016 4 20 - chc Error�ɭn�Ұ�Motion
         MainForm->pcMotion->Enabled = true;

         Beep(500);

         // 2016 6 4 - chc Alarm Message
         MainForm->pnlAlarmMessage->Caption = msg;

      }

   }
   else {

      // 2020 2 17 - chc ��lAxisErrorNo
      // 2020 3 16 - chc �n���᭱
      //AxisErrorNo = -1;

      // 2016 4 2 - chc �Y��Alm�ܦ�Ok�h�n�Ұ�Motion & AllHome
      // 2019 7 8 - chc ���RDY
      //if(alm->Color == clLime) {
      if(rdy->Color == clSilver) {

         MainForm->pcMotion->Enabled = true;
         MainForm->btnHome->Enabled = true;
      }

      // 2019 7 8 - chc ���RDY
      //alm->Color = clSilver;
      rdy->Color = clRed;

      // 2013 2 26 - chc �b�����`! ����Alarm Message
      if(MainForm->pnlAxisError->Visible == true && axisno == AxisErrorNo) {
         MainForm->pnlAxisError->Visible = false;

         // 2021 5 5 - chc �Ұ�"���I����
         MainForm->pcOP->Enabled = true;

      }

      // 2020 3 16 - chc �n���᭱
      AxisErrorNo = -1;

   }
   // PEL
   if(io_sts & 0x0004)
      pel->Color = clRed;
   else
      pel->Color = clSilver;
   // NEL
   if(io_sts & 0x0008)
      nel->Color = clRed;
   else
      nel->Color = clSilver;
   // ORG
   if(io_sts & 0x0010)
      org->Color = clRed;
   else
      org->Color = clSilver;
   // DIR
   if(io_sts & 0x0020)
      dir->Color = clRed;
   else
      dir->Color = clSilver;
   // Reserved1
   if(io_sts & 0x0040)
      reserved1->Color = clRed;
   else
      reserved1->Color = clSilver;
   // PCS
   if(io_sts & 0x0080)
      pcs->Color = clRed;
   else
      pcs->Color = clSilver;
   // ERC
   if(io_sts & 0x0100)
      erc->Color = clRed;
   else
      erc->Color = clSilver;
   // EZ
   if(io_sts & 0x0200)
      ez->Color = clRed;
   else
      ez->Color = clSilver;
   // Reserved2
   if(io_sts & 0x0400)
      reserved2->Color = clRed;
   else
      reserved2->Color = clSilver;
   // Latch
   if(io_sts & 0x0800)
      latch->Color = clRed;
   else
      latch->Color = clSilver;
   // SD
   if(io_sts & 0x1000)
      sd->Color = clRed;
   else
      sd->Color = clSilver;
   // INP
   if(io_sts & 0x2000)
      inp->Color = clRed;
   else
      inp->Color = clSilver;
   // SVON
   if(io_sts & 0x4000)
      svon->Color = clRed;
   else
      svon->Color = clSilver;
}
//---------------------------------------------------------------------------
void __fastcall SetRXPosition(int no)
{
F64 pos;
TLMDEdit *edit;
int wpos;

   // LP1
   if(no == 1)
      edit = (TLMDEdit *)(MainForm->FindComponent("edWPositionLP1"));
   else if(no == 2)
      edit = (TLMDEdit *)(MainForm->FindComponent("edWPositionLP2"));
   else if(no == 3)
      edit = (TLMDEdit *)(MainForm->FindComponent("edWPositionAligner"));
   else if(no == 4)
      edit = (TLMDEdit *)(MainForm->FindComponent("edWPositionChuck"));
   // ŪRX Position��
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(W_AXIS+StartAxisNo,&ipos);
      wpos = ipos;
   }
   edit->Text = IntToStr(wpos);
}
//---------------------------------------------------------------------------
void __fastcall GetAxisPosition(int axisno, F64 *position)
{

   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(axisno+StartAxisNo,&ipos);
      *position = ipos;
   }
}
//---------------------------------------------------------------------------
bool __fastcall MoveAbsolute(int axisno)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
TLMDEdit* edit;
AnsiString name;
I16 mstatus;
int counter,max,ms;

// 2013 10 6 - chc �[�JLow Distance
F64 lowdistance;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE)
      return false;
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // 2013 10 6 - chc �[�JLow Distance
   //GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit);
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   // ���oPosition
   // 0 - 7(12 - 19)
   GetAxisName(axisno);
   name = MainForm->AxisName;
   edit = (TLMDEdit *)(MainForm->FindComponent("edPosition" + name));

   pos = edit->Text.ToInt();

   // 2023 1 15 - chc MoveAbsolute(): ZLimit
   // 2023 8 3 - chc �bAbsoluteMove�A��Limit�ˬd
   //if(axisno == Z_AXIS) {
   //   int zlimit = MainForm->edZLimit->Text.ToInt();
   //   if(pos > zlimit)
   //      pos = zlimit;
   //}

   // Absolute move
   AbsoluteMove(axisno,pos,startvel,maxvel,tacc,tdec);

   // ��Done: 10Sec
   ms = 10000;
   counter = 0;
   max = ms / 10;

   // 2013 5 21 - chc �Τ@Sleep(1)
   //Sleep(10);
   DelayTimeM5(10);

   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         I32 done;
         mstatus = 0;
         done = APS_motion_status(X_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatus = 1;
      }
      if(mstatus == 0 || mstatus == 17 || mstatus == 18) {
         break;
      }
      else {

         // 2013 5 21 - chc �Τ@Sleep(1)
         //Sleep(10);
         //Application->ProcessMessages();
         DelayTimeM5(10);

         //MainForm->pnlCounter->Caption = counter;
         counter++;
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion Timeout!";

            // 2016 5 10 - chc �O���U�b�O�_�B�@��
            MainForm->iAxisMove[axisno] = NO_MOVE;

            return false;
         }
      }
   }

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
void __fastcall StopAxis(int axisno)
{

   // 2019 7 8 - chc ��δ�t����: I16 _8158_sd_stop(I16 AxisNo, F64 Tdec);
   F64 tdec = GetTdec(axisno);

   // 2021 4 15 - chc APS
   if(MotionMode == MOTION_MODE_APS)
      APS_stop_move(axisno+StartAxisNo);
}
//---------------------------------------------------------------------------
// 0 - 7(12 - 19)
void __fastcall GetAxisName(int axisno)
{
AnsiString name;

   switch(axisno) {
      // X
      case X_AXIS:
         name = "X";
         break;
      // Y
      case Y_AXIS:
         name = "Y";
         break;
      // Z
      case Z_AXIS:
         name = "Z";
         break;
      // T
      case T_AXIS:
         name = "T";
         break;
      // L
      case L_AXIS:
         name = "L";
         break;
      // W
      case W_AXIS:
         name = "W";
         break;
   }
   MainForm->AxisName = name;
   //return name;

}
//---------------------------------------------------------------------------
// �]�wAlm Logic: 4&6-High, �l-Low
void __fastcall SetAlmOn()
{
I16 axisno;

   // ���wAxis
   axisno = MainForm->combAxis->ItemIndex;

   // 2021 4 19 - chc APS
   if(MotionMode == MOTION_MODE_APS)
      APS_set_axis_param(axisno+StartAxisNo, PRA_ALM_LOGIC, 1);         // High
}
//---------------------------------------------------------------------------
// �]�wAlm Logic: 4&6-High, �l-Low
void __fastcall SetAlmOff()
{
I16 axisno;

   // ���wAxis
   axisno = MainForm->combAxis->ItemIndex;

   // 2021 4 19 - chc APS
   if(MotionMode == MOTION_MODE_APS)
      APS_set_axis_param(axisno+StartAxisNo, PRA_ALM_LOGIC, 0);         // High
}
//---------------------------------------------------------------------------
// Set Servo On
void __fastcall SetServoOn()
{
int axisno;

   // ���wAxis
   axisno = MainForm->combAxis->ItemIndex;

   // 2021 4 19 - chc APS
   if(MotionMode == MOTION_MODE_APS)
      APS_set_servo_on(axisno+StartAxisNo, 1);
}
//---------------------------------------------------------------------------
// Set Servo Off
void __fastcall SetServoOff()
{
int axisno;

   // ���wAxis
   axisno = MainForm->combAxis->ItemIndex;

   // 2021 4 19 - chc APS
   if(MotionMode == MOTION_MODE_APS)
      APS_set_servo_on(axisno+StartAxisNo, 0);
}
//---------------------------------------------------------------------------
// 2013 2 17 - chc Org Logic Switch
void __fastcall ORGLogicSwitch(int axisno, bool mode)
{
AnsiString name;
TLMDComboBox* combobox;
int logic,homemode;

   // 2021 4 20 - chc APS
   // => �L���R�O
   if(MotionMode == MOTION_MODE_APS)
      return;
}
//---------------------------------------------------------------------------
// 2013 2 17 - chc �s�򲾰�
// mode : 0���e, ������
// mode : 1����, �t����
// Low/High Speed�令����������, �ݩ�}��A�U������O
// �ݩw�q: �t��
// 2016 8 26 - chc define type value: 0-wait, 1-nowait(for UpdateMotionStatus())
//void __fastcall AxisMove(int mode)
void __fastcall AxisMove(int mode, int type)

{
F64 dist,startvel,maxvel,tacc,tdec,posi,homevel,reviewvel,uplimit;
bool moveflag = false;
static bool active = false;
int axisno;

// 2013 10 6 - chc �[�JLow Distance
F64 lowdistance;

   // Re-Entrant
   if(active == true)
      return;

   MainForm->WriteSystemLog("AxisMove() Enter.");

   active = true;

   // �O���bmove��, ���i�H�P��Continue move
   MainForm->boolInAxisMove = true;

   MainForm->pnlSystemMessage->Caption = "Start to Move.";
   Application->ProcessMessages();

   // 2016 5 11 - chc Log
   // 2016 8 26 - chc define type value: 0-wait, 1-nowait(for UpdateMotionStatus())
   //MainForm->WriteSystemLog(">AxisMove()Enter: " + IntToStr(mode));
   MainForm->WriteSystemLog(">AxisMove()Enter: mode=" + IntToStr(mode) + ", type=" + IntToStr(type));

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   axisno = MainForm->CurrentAxisNo;
   if(MainForm->iAxisMove[axisno] != NO_MOVE)
      goto mdone;
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   while(MainForm->boolJogMove) {
      axisno = MainForm->CurrentAxisNo;

      if(moveflag == false) {

         // �������Ǥ�Trigger����, �w���ʴN����
         //cbOpticalRulerTrigger->Checked = false;

         GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

         // 2013 10 6 - chc �[�JLow Distance
         // 2016 4 18 - chc �Ȥ��B�z
         //if(MainForm->rgMoveSpeed->ItemIndex == 0) {
         //   startvel = reviewvel;
         //   maxvel = uplimit;
         //}

         // �e�i
         if(mode == 0) {

            // 2013 10 3 - chc �]���L����
            //posi = uplimit;
            //if(axisno == T_AXIS)
            //   posi = uplimit * 100;
            posi = 8000000;

            // 2021 4 21 - chc �Y��Z�h�n����U��
            if(axisno == Z_AXIS) {
               int limit;
               limit = MainForm->GetZLimit();
               posi = limit;
            }

         }
         // ��h
         else {

            // 2013 10 3 - chc �]���t�L����
            //posi = 0;
            posi = -8000000;
         }

         // 2016 5 11 - chc AI Speed
         if(MainForm->boolInAIXMove == true && axisno == X_AXIS) {

            // 2016 6 3 - chc XY�b��פw��1um�令0.1um
            //maxvel = 25000 * MainForm->InAIMoveXSpeed / 100.0;
            maxvel = maxvel * MainForm->InAIMoveXSpeed / 100.0;

            MainForm->WriteSystemLog(">AI1(X): ta_move " + FloatToStr(maxvel));
         }

         // 2016 6 3 - chc �S������Y�b�t��, XY�b��פw��1um�令0.1um
         if(MainForm->boolInAIYMove == true && axisno == Y_AXIS) {
            maxvel = maxvel * MainForm->InAIMoveYSpeed / 100.0;
            MainForm->WriteSystemLog(">AI2(Y): ta_move " + FloatToStr(maxvel));
         }

         // 2020 2 12 - chc Joystick Speed
         if(MainForm->pnlJoystickActive->Color == clLime) {
            if(axisno == Z_AXIS) {
               if(MainForm->rgJoystickSpeed->ItemIndex == 0)
                  maxvel = (0.1 * 1000) / Z_RESOLUTION;
               else
                  maxvel = (5 * 1000) / Z_RESOLUTION;
            }
            else {
               if(MainForm->rgJoystickSpeed->ItemIndex == 0)
                  maxvel = (1 * 1000) / X_RESOLUTION;
               else
                  maxvel = (50 * 1000) / X_RESOLUTION;
            }
            // 2020 2 13 - chc AI Speed: 100~1000, 10000~500000
            int value,base;
            double unit;
            base = MainForm->edAISpeedStart->Text.ToInt();
            if(axisno == X_AXIS)
               value = MainForm->pnlJoystickX->Caption.ToInt();
            else if(axisno == Y_AXIS)
               value = MainForm->pnlJoystickY->Caption.ToInt();
            else if(axisno == Z_AXIS)
               value = MainForm->pnlJoystickZ->Caption.ToInt();
            if(MainForm->cbAISpeed->Checked == true /*&& value > 0*/) {
               if(axisno == Z_AXIS) {
                  if(MainForm->rgJoystickSpeed->ItemIndex == 0)
                     unit = 100.0 / (1000.0 - base);
                  else
                     unit = 5000.0 / (1000.0 - base);
               }
               else {
                  if(MainForm->rgJoystickSpeed->ItemIndex == 0)
                     unit = 10000.0 / (1000.0 - base);
                  else
                     unit = 500000.0 / (1000.0 - base);
               }
               maxvel = (abs(value) - base + 1) * unit;
               if(axisno == X_AXIS)
                  MainForm->WriteSystemLog(">Joystick: AI��t��(X)= " + FloatToStr(maxvel) + "," + IntToStr(value));
               else if(axisno == Y_AXIS)
                  MainForm->WriteSystemLog(">Joystick: AI��t��(Y)= " + FloatToStr(maxvel) + "," + IntToStr(value));
               else if(axisno == Z_AXIS)
                  MainForm->WriteSystemLog(">Joystick: AI��t��(Z)= " + FloatToStr(maxvel) + "," + IntToStr(value));
            }

            MainForm->WriteSystemLog(">Joystick: ta_move " + FloatToStr(maxvel));
         }

         // Absolute move
         int ispeed;
         ispeed = maxvel;
         MainForm->WriteSystemLog("AbsoluteMove: �b,Speed=" + IntToStr(axisno) + "," + IntToStr(ispeed));
         AbsoluteMove(axisno,posi,startvel,maxvel,tacc,tdec);

         // 2020 2 16 - chc �O���ثe���s�򲾰ʤ�: �b�P���ʤ�V(1/2: ��/��, 0-�S������)
         MainForm->MoveAxis = axisno;
         if(posi > 0)
            MainForm->MoveDirection = 1;
         else
            MainForm->MoveDirection = 2;
         if(MainForm->MoveIgnore == true && (MainForm->MoveIgnoreAxis != axisno || MainForm->MoveIgnoreDirection != MainForm->MoveDirection))
            MainForm->MoveIgnore = false;
      }
      moveflag = true;
      MainForm->pnlSystemMessage->Caption = "Moving...";

      // Wait
      WaitRoutine1(10);

      // 2016 8 26 - chc no wait
      if(type == 1)
         break;

   }

   // 2016 8 26 - chc no wait
   if(type == 0) {
      MainForm->WriteSystemLog("AbsoluteMove: emg_stop");

      // 2019 7 8 - chc ��δ�t����: I16 _8158_sd_stop(I16 AxisNo, F64 Tdec);
      F64 tdec = GetTdec(axisno);

      // 2021 4 15 - chc APS
      if(MotionMode == MOTION_MODE_APS)
         APS_stop_move(axisno+StartAxisNo);

      // 2020 2 12 - chc Joystick������٭n�ˬd�䥦�b
      if(MainForm->pnlJoystickActive->Color == clLime) {
         StopOtherAxis(axisno);
      }

   }

mdone:

   // 2016 8 26 - chc no wait
   if(type == 0) {

      MainForm->pnlSystemMessage->Caption = "Move Done.";
      Application->ProcessMessages();
      // �O���bmove��, ���i�H�P��Continue move
      MainForm->boolInAxisMove = false;

      // 2016 5 10 - chc �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;

   }
   MainForm->WriteSystemLog("AxisMove() Done.");

   // Re-Entrant
   active = false;

}
//---------------------------------------------------------------------------
// �e�i: �n�P�wLimit���D
void __fastcall MoveForward()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
AnsiString str;

// 2013 10 6 - chc �[�JLow Distance
F64 lowdistance;

// 2016 8 9 - chc R of Within point(mm): 0~10mm(20000), 10mm~20mm(10000), 20mm~30mm(7500), 30mm~40mm(5000), 40mm~(2500)
F64 tmaxvel;

   // 2016 5 10 - chc �s�ʫh����: MoveBackward()�]�O�p��!
   if(MainForm->cbContinueMove->Checked == true)
      return;

   // �bMouseDown���w�@�ʶb
   axisno = MainForm->combAxis->ItemIndex;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {

      // 2019 11 27 - chc Message
      MainForm->pnlSystemMessage->Caption = "The previous action has not been completed(F), unable to move! " + IntToStr(axisno+1);
      MainForm->WriteSystemLog(str);

      return ;
   }

   // 2013 10 6 - chc �[�JLow Distance
   //GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit);
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   // 2020 3 3 - chc Log
   str.sprintf("�b��+����(���o): No,Dist,SV,MV,TA,TD= %d,%d,%d,%d,%.2f,%.2f",axisno,(int)dist,(int)startvel,(int)maxvel,tacc,tdec);
   MainForm->WriteSystemLog(str);

   // Disable
   MainForm->btnMove->Enabled = false;

   // �W���ˬd&�վ�
   CheckUpDownLimit(axisno,&dist,uplimit);

   str.sprintf("�b��+����(���ʫe): No,Dist,SV,MV,TA,TD= %d,%d,%d,%d,%.2f,%.2f",axisno,(int)dist,(int)startvel,(int)maxvel,tacc,tdec);
   MainForm->WriteSystemLog(str);

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // ����
   // Relative move
   int ret = RelativeMove(axisno,dist,startvel,maxvel,tacc,tdec);
   str.sprintf("�b��+����(���ʫ�): No,Dist,SV,MV,TA,TD= %d,%d,%d,%d,%.2f,%.2f",axisno,(int)dist,(int)startvel,(int)maxvel,tacc,tdec);
   MainForm->WriteSystemLog(str);

   // ��Motion done
   MainForm->pnlSystemMessage->Caption = "Axis+ moving...";

   int counter = 1;
   I32 cmd;
   I16 Motion_sts;

   // 2013 5 21 - chc �Τ@Sleep(1)
   //Sleep(100);
   DelayTimeM5(100);

   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         I32 done;
         Motion_sts = 0;
         done = APS_motion_status(axisno+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            Motion_sts = 1;
      }
      //Motion_sts = MotionStatusCode[axisno];
      if(Motion_sts == 0 || Motion_sts == 17 || Motion_sts == 18) {
         break;
      }
      else {
         DelayTimeM5(50);

         //MainForm->pnlCounter->Caption = counter;
         counter++;
         // 10sec: 50*200
         if(counter > 200) {
            MainForm->pnlSystemMessage->Caption = "Wait Motion Done Timeout!";
            // �O���U�b�O�_�B�@��
            MainForm->iAxisMove[axisno] = NO_MOVE;
            return;
         }
      }
   }
   MainForm->btnMove->Enabled = true;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   // 2016 7 22 - chc message: "Move Done."
   MainForm->pnlSystemMessage->Caption = "Move Done.";

}
//---------------------------------------------------------------------------
// �U�b�W�U���ˬd
// dist: �۹ﲾ�ʶq
void __fastcall CheckUpDownLimit(int axisno,F64 *dist, F64 uplimit)
{
F64 posi;

   // 2013 9 28 - chc ���ˬd����
   return;

   // T�b���γ]��
   if(axisno == T_AXIS)
      return;

   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(axisno+StartAxisNo,&ipos);
      posi = ipos;
   }
   posi = posi + *dist;
   if(posi < 0)
      *dist = 0 - posi;
   else if(posi > uplimit)
      *dist = uplimit - posi;
}
//---------------------------------------------------------------------------
// ��h, �n�P�wLimit���D
void __fastcall MoveBackward()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;

// 2013 10 6 - chc �[�JLow Distance
F64 lowdistance;

// 2016 8 9 - chc R of Within point(mm): 0~10mm(20000), 10mm~20mm(10000), 20mm~30mm(7500), 30mm~40mm(5000), 40mm~(2500)
F64 tmaxvel;

   // �s��
   if(MainForm->cbContinueMove->Checked == true)
      return;

   // �bMouseDown�����w�@�ʶb
   axisno = MainForm->combAxis->ItemIndex;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {

      // 2019 11 27 - chc Message
      MainForm->pnlSystemMessage->Caption = "The previous action has not been completed(B), unable to move! " + IntToStr(axisno+1);

      return;
   }

   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   // Disable
   MainForm->btnBackward->Enabled = false;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = BACKWARD_MOVE;

   // �W���ˬd
   dist = 0 - dist;
   CheckUpDownLimit(axisno,&dist,uplimit);

   // 2016 7 18 - chc Relative move
   int ret = RelativeMove(axisno,dist,startvel,maxvel,tacc,tdec);

   // ��Motion done
   // 2016 7 22 - chc change to "Motion Moving..."
   //MainForm->pnlSystemMessage->Caption = "Motion Done...";
   MainForm->pnlSystemMessage->Caption = "Axis- moving...";

   int counter = 1;
   I32 cmd;
   I16 Motion_sts;

   // 2013 5 21 - chc �Τ@Sleep(1)
   //Sleep(100);
   DelayTimeM5(100);

   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         I32 done;
         Motion_sts = 0;
         done = APS_motion_status(axisno+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            Motion_sts = 1;
      }
      //Motion_sts = MotionStatusCode[axisno];
      if(Motion_sts == 0 || Motion_sts == 17 || Motion_sts == 18) {
         break;
      }
      else {

         // 2013 5 21 - chc �Τ@Sleep(1)
         //Sleep(50);
         //Application->ProcessMessages();
         DelayTimeM5(50);

         //MainForm->pnlCounter->Caption = counter;
         counter++;
         // 10sec: 50*200
         if(counter > 200) {
            MainForm->pnlSystemMessage->Caption = "Motion Done Timeout!";

            // 2016 5 10 - chc �O���U�b�O�_�B�@��
            MainForm->iAxisMove[axisno] = NO_MOVE;

            return;
         }
      }
   }
   MainForm->btnBackward->Enabled = true;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   // 2016 7 22 - chc message: "Move Done."
   MainForm->pnlSystemMessage->Caption = "Move Done.";

}
//---------------------------------------------------------------------------
// Enable/Disable the external feedback pulse input
// src: 0 External Feedback
//      1 Command pulse
void __fastcall SetFeedbackSource(int axisno, int src)
{

   // �L���R�O
   if(MotionMode == MOTION_MODE_APS)
      return;

}
//---------------------------------------------------------------------------
// Position
void __fastcall GetPosition(int axisno, F64 *pos)
{

   // APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(axisno+StartAxisNo,&ipos);
      *pos = ipos;
   }
}
//---------------------------------------------------------------------------
// ������wXY��m
void __fastcall GotoXYZ(int x, int y, int z, bool mode, int review, F64 movevel)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,posi;
int sx,sy;

// 2013 10 6 - chc �[�JLow Distance
F64 lowdistance;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE || MainForm->iAxisMove[Z_AXIS] != NO_MOVE)
      return;
   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Z_AXIS] = FORWARD_MOVE;

   // 2021 4 24 - chc Z Limit
   int limit = MainForm->GetZLimit();
   if(z > limit)
      z = limit;

   // Message
   // 2016 4 18 - chc �Ȥ��B�z
   //if(MainForm->cbLogDetail->Checked == true)
   //   MainForm->WriteSystemLog(">GotoXYZ 1");

   // goto (x,y,z)
   // X
   MainForm->CurrentAxisNo = X_AXIS;
   MainForm->combAxis->ItemIndex = MainForm->CurrentAxisNo;

   // 2013 10 6 - chc �[�JLow Distance
   //GetAxisData(X_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit);
   GetAxisData(X_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   // 2013 10 6 - chc �i�]�wLow Speed
   // 2016 4 18 - chc �Ȥ��B�z
   //if(MainForm->rgMoveSpeed->ItemIndex == 0) {
   //   startvel = reviewvel;
   //   maxvel = uplimit;
   //}

   // Review�W��
   if(review == 1) {
      maxvel = reviewvel;
   }

   posi = x;
   // X�b�n�ޱ�
   // 2015 3 26 - chc @#@# ����check
   //if(posi > uplimit)
   //   posi = uplimit;
   //if(posi < 0)
   //   posi = 0;

   // �ץ�Tdec & Tacc
   if(mode == true) {
      if(tdec < 0.1)
         tdec = 0.1;
      if(tacc < 0.1)
         tacc = 0.1;
   }

   // 2013 2 22 - chc �ϥθ����t
   if(movevel != 0 && maxvel < movevel)
      maxvel = movevel;

   // Review
   // 2016 4 18 - chc �Ȥ��B�z
   //if(review == 1 && MainForm->cbReviewLowSpeed->Checked == true) {
   //   maxvel = maxvel / 5;
   //}

   // 2015 5 8 - chc �Ȭ�0������
   if(x != 0) {
      AbsoluteMove(X_AXIS,posi,startvel,maxvel,tacc,tdec);
   }
   // Y
   MainForm->CurrentAxisNo = Y_AXIS;
   MainForm->combAxis->ItemIndex = MainForm->CurrentAxisNo;

   // 2013 10 6 - chc �[�JLow Distance
   //GetAxisData(Y_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit);
   GetAxisData(Y_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   // 2013 10 6 - chc �i�]�wLow Speed
   // 2016 4 18 - chc �Ȥ��B�z
   //if(MainForm->rgMoveSpeed->ItemIndex == 0) {
   //   dist = lowdistance;
   //   startvel = reviewvel;
   //   maxvel = uplimit;
   //}

   // Review�W��
   if(review == 1) {
      maxvel = reviewvel;
   }

   posi = y;
   // Y�b�n�ޱ�
   // 2015 3 26 - chc @#@# ����check
   //if(posi > uplimit)
   //   posi = uplimit;
   //if(posi < 0)
   //   posi = 0;

   // �ץ�Tdec & Tacc
   if(mode == true) {
      if(tdec < 0.1)
         tdec = 0.1;
      if(tacc < 0.1)
         tacc = 0.1;
   }

   // Review
   // 2016 4 18 - chc �Ȥ��B�z
   //if(review == 1 && MainForm->cbReviewLowSpeed->Checked == true) {
   //   maxvel = maxvel / 5;
   //}

   // 2015 5 8 - chc �Ȭ�0������
   if(y != 0) {
      AbsoluteMove(Y_AXIS,posi,startvel,maxvel,tacc,tdec);
   }
   // 2013 3 14 - chc �[�JZ
   // Z
   if(z != 0) {
      MainForm->CurrentAxisNo = Z_AXIS;
      MainForm->combAxis->ItemIndex = MainForm->CurrentAxisNo;
      GetAxisData(Z_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
      // Review�W��
      if(review == 1) {
         maxvel = reviewvel;
      }
      posi = z;

      // Z�b�n�ޱ�
      // 2015 3 26 - chc @#@# ����check
      //if(posi > uplimit)
      //   posi = uplimit;
      //if(posi < 0)
      //   posi = 0;

      // �ץ�Tdec & Tacc
      if(mode == true) {
         if(tdec < 0.1)
            tdec = 0.1;
         if(tacc < 0.1)
            tacc = 0.1;
      }
      AbsoluteMove(Z_AXIS,posi,startvel,maxvel,tacc,tdec);
   }

   // Message
   // 2016 4 18 - chc �Ȥ��B�z
   //if(MainForm->cbLogDetail->Checked == true)
   //   MainForm->WriteSystemLog(">GotoXYZ 2");

   if(z != 0)
      WaitMotionDoneXYZ(3,1000);
   else

      WaitMotionDoneXY(3,1000);

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Z_AXIS] = NO_MOVE;

}
//---------------------------------------------------------------------------
void __fastcall DoAxisTaMove(int axisno, F64 pos, F64 startvel, F64 maxvel, F64 tacc, F64 tdec)
{

   AbsoluteMove(axisno,pos,startvel,maxvel,tacc,tdec);
}
//---------------------------------------------------------------------------
void __fastcall DoAxisTrMove(int axisno, F64 pos, F64 startvel, F64 maxvel, F64 tacc, F64 tdec)
{

   // Relative move
   int ret = RelativeMove(axisno,pos,startvel,maxvel,tacc,tdec);
}
//---------------------------------------------------------------------------
// Command
void __fastcall GetCommand(int axisno, I32 *cmd)
{

   if(MotionMode == MOTION_MODE_APS)
      APS_get_command(axisno+StartAxisNo,cmd);
}
//---------------------------------------------------------------------------
// 2013 2 17 - chc Wait Motion done - for CCD Capture
bool __fastcall WaitMotionDoneCCD(int axisno, int ms)
{
I32 cmd;
I16 Motion_sts;
int counter;
int max;

   max = ms / 10;

   // 2013 5 21 - chc �Τ@Sleep(1)
   //Sleep(10);
   //Application->ProcessMessages();
   DelayTimeM9(10);

   counter = 0;
   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         I32 done;
         Motion_sts = 0;
         done = APS_motion_status(axisno+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            Motion_sts = 1;
      }
      //Motion_sts = MotionStatusCode[axisno];
      if(Motion_sts == 0 || Motion_sts == 17 || Motion_sts == 18) {
         break;
      }
      else {
         //MainForm->pnlCounter->Caption = counter;
         counter++;
         // 10sec: 50*200
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion Done Timeout!";
            return false;
         }
      }

      // 2013 5 21 - chc �Τ@Sleep(1)
      //Sleep(10);
      //Application->ProcessMessages();
      DelayTimeM9(10);

   }
   return true;
}
//---------------------------------------------------------------------------
// 2013 2 22 - chc Wait Motion X/Y/Z done for Scan
bool __fastcall WaitMotionXYDoneForScan(int ms)
{
I32 cmd;
I16 mstatusx,mstatusy;
int counter;
int max,axisno;

   max = ms / 10;

   // 2013 6 5 - chc �|���]�w��0!!!
   counter = 0;

   while(1) {

      // 2013 5 21 - chc �Τ@Sleep(1)
      //Sleep(10);
      //Application->ProcessMessages();
      DelayTimeM10(10);

      if(MotionMode == MOTION_MODE_APS) {
         I32 done;
         mstatusx = 0;
         done = APS_motion_status(X_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusx = 1;
         mstatusy = 0;
         done = APS_motion_status(Y_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusy = 1;
      }
      if((mstatusx == 0 || mstatusx == 17 || mstatusx == 18) &&
         (mstatusy == 0 || mstatusy == 17 || mstatusy == 18)) {
         break;
      }

      counter++;
      //MainForm->pnlCounter->Caption = counter;
      if(counter > max) {
         MainForm->pnlSystemMessage->Caption = "Motion XY Done for Scan Timeout!";
         MainForm->WriteSystemLog("Motion XY Done for Scan timeout!");
         return false;
      }
   }
   return true;
}
//---------------------------------------------------------------------------
// 2013 2 22 - chc Wait Routine : �b��
void __fastcall WaitRoutine1(int sleepno)
{
static bool active = false;

   if(active == false) {
      active = true;

      // 2013 5 21 - chc �Τ@Sleep(1)
      //Sleep(sleepno);
      //Application->ProcessMessages();
      DelayTimeM10(sleepno);

      active = false;
   }
}
//---------------------------------------------------------------------------
// Command
void __fastcall SetCommand(int axisno, I32 cmd)
{

   // 2021 4 20 - chc 8154 or APS_
   if(MotionMode == MOTION_MODE_APS) {
      APS_set_command(axisno+StartAxisNo,cmd);
   }
}
//---------------------------------------------------------------------------
// Position
void __fastcall SetMPosition(int axisno, F64 pos)
{

   // 2021 4 20 - chc 8154 or APS_
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      ipos = pos;
      APS_set_position(axisno+StartAxisNo,ipos);
   }
}
//---------------------------------------------------------------------------
void __fastcall GetIOStatus(int axisno, U16 *iostatus)
{

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 istatus;
      istatus = APS_motion_io_status(axisno+StartAxisNo);
      *iostatus = istatus;
   }
}
//---------------------------------------------------------------------------
// 2013 2 23 - chc DO Reset 0
// mode: 1-��bit0, 2-All
void __fastcall InitDO(int mode)
{

   // 2021 5 8 - chc �令0x01(Stage Door)
   if(mode == 1)
      HSL_IO_OuStatus = 0x01;
   else

      HSL_IO_OuStatus = 0;

   // 2021 6 11 - chc InitDO()�YChuck�����n�l�u��Bit7
   if(MainForm->pnlBit7->Color == clLime || HSL_IO_InStatus[7] == true) {
      // Bit1 - �u��(8")
      // 2023 7 23 - chc �n�[on Bit1 <����>
      //HSL_IO_OuStatus = STAGE_VACUUM;
      HSL_IO_OuStatus |= STAGE_VACUUM;

      MainForm->pnlStageVacuum->Color = clLime;
   }
   else
      MainForm->pnlStageVacuum->Color = clSilver;

   APS_set_field_bus_d_output(BoardHSL, HSL_BUS, IO1_ID, HSL_IO_OuStatus);

   // 2021 5 5 - chc Reset Color
   // 2021 5 8 - chc �令0x01(Stage Door)
   if(mode == 2)

      MainForm->pnlStageLock->Color = clSilver;

   // 2021 6 11 - chc Chuck�W�O�_����?
   //MainForm->pnlStageVacuum->Color = clSilver;

   MainForm->pnlStageBar->Color = clSilver;
   MainForm->pnlDOMaintenanceLight->Color = clSilver;
   MainForm->pnlDOCDA->Color = clSilver;
   MainForm->pnlDOEFEMFFU->Color = clSilver;
   MainForm->pnlDOStageFFU->Color = clSilver;
   MainForm->pnlStageVacuum1->Color = clSilver;
   MainForm->pnlDOReserved8->Color = clSilver;
   MainForm->pnlDOReserved9->Color = clSilver;
   MainForm->pnlDOPolarizer->Color = clSilver;
   MainForm->pnlDORedLamp->Color = clSilver;
   MainForm->pnlDOYellowLamp->Color = clSilver;
   MainForm->pnlDOGreenLamp->Color = clSilver;
   MainForm->pnlDOBlueLamp->Color = clSilver;
   MainForm->pnlDOBuzzer->Color = clSilver;

}
//---------------------------------------------------------------------------
// Bit20
void __fastcall Beep(int mstime)
{
unsigned int value;

}
//---------------------------------------------------------------------------
// Bit20
void __fastcall BeepStop()
{
int no;

}
//---------------------------------------------------------------------------
// 2013 3 14 - chc �p�GChuck��Wafer�h�n���l��
void __fastcall ChuckWaferVacuum()
{

   // Vacuum off?
   // 2016 4 18 - chc without sensor to detect is there a Wafer on chuck
   //if(MainForm->pnlBit21->Color == clLime) {
   //   if(MainForm->SetChuckVacuum(true,MainForm->WaferSize) == false) {
   //      MainForm->pnlSystemMessage->Caption = "Chuck Vacuum Error!";
   //   }
   //}
}
//---------------------------------------------------------------------------
// 2013 5 15 - chc Sleep : ToRXPositionFun(int no)�ϥ�
void __fastcall DelayTimeM1(int no)
{
long starttime,stoptime,elapsedms;
short starttick,stoptick;
int cnt = 0;

   MainForm->GetTimeTic(&starttime,&starttick);
   while(1) {
      Application->ProcessMessages();
      Sleep(MOTION_SLEEP_TIME);
      cnt++;
      if(cnt >= 10) {
         cnt = 0;
         MainForm->GetTimeTic(&stoptime,&stoptick);
         elapsedms = ((stoptime*1000+stoptick) - (starttime*1000+starttick));
         if(elapsedms > no)
            return;
      }
   }
}
//---------------------------------------------------------------------------
// 2013 5 20 - chc Sleep : WaitMotionDone()�ϥ�
void __fastcall DelayTimeM2(int no)
{
long starttime,stoptime,elapsedms;
short starttick,stoptick;
int cnt = 0;

   MainForm->GetTimeTic(&starttime,&starttick);
   while(1) {
      Application->ProcessMessages();
      Sleep(MOTION_SLEEP_TIME);
      cnt++;
      if(cnt >= 10) {
         cnt = 0;
         MainForm->GetTimeTic(&stoptime,&stoptick);
         elapsedms = ((stoptime*1000+stoptick) - (starttime*1000+starttick));
         if(elapsedms > no)
            return;
      }
   }
}
//---------------------------------------------------------------------------
// 2013 5 21 - chc Sleep : AllHome()�ϥ�
void __fastcall DelayTimeM3(int no)
{
long starttime,stoptime,elapsedms;
short starttick,stoptick;
int cnt = 0;

   MainForm->GetTimeTic(&starttime,&starttick);
   while(1) {
      Application->ProcessMessages();
      Sleep(MOTION_SLEEP_TIME);
      cnt++;
      if(cnt >= 10) {
         cnt = 0;
         MainForm->GetTimeTic(&stoptime,&stoptick);
         elapsedms = ((stoptime*1000+stoptick) - (starttime*1000+starttick));
         if(elapsedms > no)
            return;
      }
   }
}
//---------------------------------------------------------------------------
// 2013 5 21 - chc Sleep : WaitMotionXYZDone()�ϥ�
void __fastcall DelayTimeM4(int no)
{
long starttime,stoptime,elapsedms;
short starttick,stoptick;
int cnt = 0;

   MainForm->GetTimeTic(&starttime,&starttick);
   while(1) {
      Application->ProcessMessages();
      Sleep(MOTION_SLEEP_TIME);
      cnt++;
      if(cnt >= 10) {
         cnt = 0;
         MainForm->GetTimeTic(&stoptime,&stoptick);
         elapsedms = ((stoptime*1000+stoptick) - (starttime*1000+starttick));
         if(elapsedms > no)
            return;
      }
   }
}
//---------------------------------------------------------------------------
// 2013 5 21 - chc Sleep : WWaitMotionDoneXY(), WaitMotionDoneXYZ(), WaitMotionDLFDone�ϥ�
void __fastcall DelayTimeM5(int no)
{
long starttime,stoptime,elapsedms;
short starttick,stoptick;
int cnt = 0;

   GetTimeTicM(&starttime,&starttick);
   while(1) {
      Application->ProcessMessages();

      // 2013 10 1 - chc ���@��, �ťX�ɶ���CCD
      //Sleep(MOTION_SLEEP_TIME);
      Sleep(1);

      cnt++;
      if(cnt >= 10) {
         cnt = 0;

         // 2013 10 1 - chc Timer����
         //MainForm->GetTimeTic(&stoptime,&stoptick);
         GetTimeTicM(&stoptime,&stoptick);

         elapsedms = ((stoptime*1000+stoptick) - (starttime*1000+starttick));
         if(elapsedms > no)
            return;
      }
   }
}
//---------------------------------------------------------------------------
// 2013 5 21 - chc Sleep : WaitMotionDoneCCD�ϥ�
void __fastcall DelayTimeM9(int no)
{
long starttime,stoptime,elapsedms;
short starttick,stoptick;
int cnt = 0;

   MainForm->GetTimeTic(&starttime,&starttick);
   while(1) {
      Application->ProcessMessages();
      Sleep(MOTION_SLEEP_TIME);
      cnt++;
      if(cnt >= 10) {
         cnt = 0;
         MainForm->GetTimeTic(&stoptime,&stoptick);
         elapsedms = ((stoptime*1000+stoptick) - (starttime*1000+starttick));
         if(elapsedms > no)
            return;
      }
   }
}
//---------------------------------------------------------------------------
// 2013 5 21 - chc Sleep : WaitMotionXYDoneForScan�ϥ�
void __fastcall DelayTimeM10(int no)
{
long starttime,stoptime,elapsedms;
short starttick,stoptick;
int cnt = 0;

   MainForm->GetTimeTic(&starttime,&starttick);
   while(1) {
      Application->ProcessMessages();
      Sleep(MOTION_SLEEP_TIME);
      cnt++;
      if(cnt >= 10) {
         cnt = 0;
         MainForm->GetTimeTic(&stoptime,&stoptick);
         elapsedms = ((stoptime*1000+stoptick) - (starttime*1000+starttick));
         if(elapsedms > no)
            return;
      }
   }
}
//---------------------------------------------------------------------------
// 2013 5 21 - chc Sleep : WaitRoutine1�ϥ�
void __fastcall DelayTimeM11(int no)
{
long starttime,stoptime,elapsedms;
short starttick,stoptick;
int cnt = 0;

   MainForm->GetTimeTic(&starttime,&starttick);
   while(1) {
      Application->ProcessMessages();
      Sleep(MOTION_SLEEP_TIME);
      cnt++;
      if(cnt >= 10) {
         cnt = 0;
         MainForm->GetTimeTic(&stoptime,&stoptick);
         elapsedms = ((stoptime*1000+stoptick) - (starttime*1000+starttick));
         if(elapsedms > no)
            return;
      }
   }
}
//---------------------------------------------------------------------------
// 2013 9 27 - chc Z�babsolute����
// mode: 0 - wait, 1 - nowait
bool __fastcall MoveToZ(int position, int speed, int mode)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   axisno = Z_AXIS;

   // �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE)
      return false;
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   // 2021 5 8 - chc Z Limit
   // 2023 8 4 - chc Check z Limit
   //int limit = MainForm->GetZLimit();
   //if(position > limit)
   //   position = limit;
   CheckZLimit(axisno,&position);

   pos = position;
   maxvel = speed;
   startvel = speed / 5;

   if(MotionMode == MOTION_MODE_APS)
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);

   // no wait
   if(mode == 1)
      return true;

   // timeout from 5sec to 30sec : MOTION_TIMEOUT
   if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
      // �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
      return false;
   }

   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2013 9 27 - chc Y�babsolute����
bool __fastcall MoveToY(int position)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   axisno = Y_AXIS;

   // �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToY: Y in moving!");
      return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   pos = position;

   // 2016 12 9 - chc Home���n��HomeSpeed
   // 2021 4 30 - chc ����
   //if(MainForm->boolHomeDone == false)
   //   maxvel = homevel;

   if(MotionMode == MOTION_MODE_APS)
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);

   // timeout from 5sec to 30sec : MOTION_TIMEOUT
   if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
      // �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
      MainForm->WriteSystemLog("MoveToY: Y Timeout!");
      return false;
   }

   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2013 9 27 - chc T�babsolute����
bool __fastcall MoveToT(int position)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno,pos;
I16 ret;
F64 lowdistance;

// 2022 5 18 - chc �O�_�A���@��
bool boolagain = false;

   axisno = T_AXIS;

   // 2022 5 18 - chc ����e��
   pos = position;

   // 2023 8 4 - chc Check z Limit : CheckZLimit(axisno,&pos)
   CheckZLimit(axisno,&pos);

   // 2022 5 18 - chc Log
   AnsiString msg;
   msg.sprintf("MoveToT: Move���ʦ�m = %d,%d",position,pos);
   MainForm->WriteSystemLog(msg);

   // �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToT: T in moving!");
      return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   // 2022 5 18 - chc ����e��
   //pos = position;

   // 2021 4 30 - chc ����
   //if(MainForm->boolHomeDone == false)
   //   maxvel = homevel;

// 2022 5 18 - chc �O�_�A���@��
again:

   // 2022 5 18 - chc Log
   msg.sprintf("MoveToT: Move���ʦ�m(�A�T�{) = %d,%d",position,pos);
   MainForm->WriteSystemLog(msg);

   if(MotionMode == MOTION_MODE_APS)
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);

   // 2022 5 18 - chc Log
   MainForm->WriteSystemLog("Wait(40sec)...");

   // timeout from 5sec to 30sec : MOTION_TIMEOUT
   if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
      // �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
      MainForm->WriteSystemLog("MoveToT: T Timeout!");
      return false;
   }

   // 2022 5 18 - chc Log
   MainForm->WriteSystemLog("MoveToT: Move����, �ˬd��m...");

   // T�����
   double fcmd;
   int cmd,cnd,max;
   cnd = 0;

   // 2022 5 18 - chc �令200
   //max = 300;
   max = 200;

   while(1) {

      // 2021 4 19 - chc �x�n�q�֦��q! ??????
      if(MotionMode == MOTION_MODE_APS) {
         I32 ipos;
         APS_get_position(axisno+StartAxisNo,&ipos);
         cmd = ipos;
      }
      // MoveToT()InPosition��100um�H���N�i�H(��10um)
      // 2022 5 18 - chc ���position
      //if(abs(pos - cmd) < 100) {
      if(abs(position - cmd) < 100) {

         MainForm->WriteSystemLog("MoveToT: ����(pos,cmd) = " + IntToStr(position) + "," + IntToStr(cmd));
         break;
      }

      Sleep(9);
      Application->ProcessMessages();
      cnd++;
      if(cnd > max) {
         MainForm->WriteSystemLog("MoveToT: Timeout(pos,cmd) = " + IntToStr(position) + "," + IntToStr(cmd));

         // 2022 5 18 - chc �O�_�A���@��
         // 2022 5 19 - chc T�����/�ɱצA�T�{: cbTCheck->Checked
         if(MainForm->cbTCheck->Checked == true) {

            if(boolagain == false) {
               MainForm->WriteSystemLog("MoveToT: Again");
               boolagain = true;
               goto again;
            }   
         }

         break;
      }
   }

   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2013 11 12 - chc ���e����90��, �W����95��
void __fastcall MoveToTAdd90()
{
I16 axisno;
I32 cmd,offset;

   axisno = T_AXIS;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_command(axisno+StartAxisNo,&ipos);
      cmd = ipos;
   }
   offset = 90 / T_RESOLUTION;
   MainForm->WriteSystemLog("cmd, offset=" + IntToStr(cmd) + "," + IntToStr(offset));
   cmd += offset;
   MoveToT(cmd);
}
//---------------------------------------------------------------------------
// 2014 9 8 - chc ���Ჾ��90��, �U����-5��
void __fastcall MoveToTSub90()
{
I16 axisno;
I32 cmd,offset;

   axisno = T_AXIS;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_command(axisno+StartAxisNo,&ipos);
      cmd = ipos;
   }
   offset = 90 / T_RESOLUTION;
   cmd -= offset;
   MoveToT(cmd);
}
//---------------------------------------------------------------------------
// 2013 10 1 - chc Timer����
void __fastcall GetTimeTicM(long *time, short *millitm)
{
struct timeb t;

   ftime(&t);
   *time = t.time;
   *millitm = t.millitm;
}
//---------------------------------------------------------------------------
// 2013 10 8 - chc ��X��AOI�I
void __fastcall ToXAOIPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z;
F64 lowdistance;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE)
      return;
   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;

   MainForm->MotionStatus(false);
   // �n��Edit����
   x = MainForm->edTiltX->Text.ToInt();
   axisno = X_AXIS;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   AbsoluteMove(axisno,x,startvel,maxvel,tacc,tdec);

   WaitMotionDoneXY(1,10000);
   MainForm->MotionStatus(true);

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;

}
//---------------------------------------------------------------------------
// 2013 10 8 - chc ����X
bool __fastcall MoveToAxisGap(int axisno, int offset)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
I16 ret;
F64 lowdistance;

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE)
      return false;
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   pos = offset;

   // 2021 5 8 - chc Z Limit
   if(axisno == Z_AXIS) {
      double fcmd;
      int cmd;
      GetPosition(axisno, &fcmd);
      cmd = fcmd;
      cmd += offset;
      int limit = MainForm->GetZLimit();
      if(cmd > limit)
         pos = limit - cmd;
   }

   // 2016 5 10 - chc �O���U�b�O�_�B�@��
   if(offset > 0)
      MainForm->iAxisMove[axisno] = FORWARD_MOVE;
   else
      MainForm->iAxisMove[axisno] = BACKWARD_MOVE;

   // Relative move
   ret = RelativeMove(axisno,pos,startvel,maxvel,tacc,tdec);

   // timeout from 5sec to 30sec
   if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
      // �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
      return false;
   }

   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2013 10 16 - chc X�babsolute����
bool __fastcall MoveToX(int position)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   axisno = X_AXIS;

   // �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToX: X in moving!");
      return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   pos = position;

   // 2016 12 9 - chc Home���n��HomeSpeed
   // 2021 4 30 - chc ����
   //if(MainForm->boolHomeDone == false)
   //   maxvel = homevel;

   // Absolute move
   if(MotionMode == MOTION_MODE_APS)
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);

   // timeout from 5sec to 30sec
   if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
      // �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
      MainForm->WriteSystemLog("MoveToX: X Timeout!");
      return false;
   }

   // �n����e��: �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2013 11 12 - chc �T�{�w������
bool __fastcall CheckTSafeDegree()
{
I16 axisno;
I32 cmd;
double degree;
int degree0,degree90,degree45,degreestd;

   // 2016 4 18 - chc �Ȥ��B�z
   return true;
}
//---------------------------------------------------------------------------
// 2013 11 12 - chc Ū��Y�b�ثe��m
int __fastcall GetYPosition()
{
int axisno;
I32 cmd;
F64 fcmd;

   axisno = Y_AXIS;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(axisno+StartAxisNo,&ipos);
      fcmd = ipos;
   }
   cmd = fcmd;

   return cmd;
}
//---------------------------------------------------------------------------
// 2015 6 17 - chc Laser Shutter1 - Bit12
void __fastcall SetShutter1(bool mode)
{

   // On
   /*
   if(mode == true) {
      if(MainForm->cbBit12->Checked == false)
         MainForm->cbBit12->Checked = true;
   }
   // Off
   else {
      if(MainForm->cbBit12->Checked == true)
         MainForm->cbBit12->Checked = false;
   }
   */
}
//---------------------------------------------------------------------------
// 2015 6 17 - chc Laser Shutter2 - Bit13
void __fastcall SetShutter2(bool mode)
{

   // On
   /*
   if(mode == true) {
      if(MainForm->cbBit13->Checked == false)
         MainForm->cbBit13->Checked = true;
   }
   // Off
   else {
      if(MainForm->cbBit13->Checked == true)
         MainForm->cbBit13->Checked = false;
   }
   */
}
//---------------------------------------------------------------------------
// 2016 4 20 - chc Reset Driver on
// mode: true-On, false-Off
// Bit9/10/11/12 - X/Y/Z/T
void __fastcall ResetDriver(int axisno,bool mode)
{

   // 2021 4 15 - chc �O�d, ���ϥ�: �ثe����|�۰�Clear Error
   /*
   // On
   if(mode == true) {
      switch(axisno) {
         case X_AXIS:
            if(MainForm->pnlDOXReset->Color != clLime) {
               MainForm->pnlDOXResetClick(MainForm);
            }
            break;
         case Y_AXIS:
            if(MainForm->pnlDOYReset->Color != clLime) {
               MainForm->pnlDOYResetClick(MainForm);
            }
            break;
         case Z_AXIS:
            if(MainForm->pnlDOZReset->Color != clLime) {
               MainForm->pnlDOZResetClick(MainForm);
            }
            break;
         case T_AXIS:
            if(MainForm->pnlDOTReset->Color != clLime) {
               MainForm->pnlDOTResetClick(MainForm);
            }
            break;
         case L_AXIS:
            if(MainForm->pnlDOLReset->Color != clLime) {
               MainForm->pnlDOLResetClick(MainForm);
            }
            break;
         case W_AXIS:
            if(MainForm->pnlDOWReset->Color != clLime) {
               MainForm->pnlDOWResetClick(MainForm);
            }
            break;
      }
   }
   // Off
   else {
      switch(axisno) {
         case X_AXIS:
            if(MainForm->pnlDOXReset->Color == clLime) {
               MainForm->pnlDOXResetClick(MainForm);
            }
            break;
         case Y_AXIS:
            if(MainForm->pnlDOYReset->Color == clLime) {
               MainForm->pnlDOYResetClick(MainForm);
            }
            break;
         case Z_AXIS:
            if(MainForm->pnlDOZReset->Color == clLime) {
               MainForm->pnlDOZResetClick(MainForm);
            }
            break;
         case T_AXIS:
            if(MainForm->pnlDOTReset->Color == clLime) {
               MainForm->pnlDOTResetClick(MainForm);
            }
            break;
         case L_AXIS:
            if(MainForm->pnlDOLReset->Color == clLime) {
               MainForm->pnlDOLResetClick(MainForm);
            }
            break;
         case W_AXIS:
            if(MainForm->pnlDOWReset->Color == clLime) {
               MainForm->pnlDOWResetClick(MainForm);
            }
            break;
      }
   }
   */
}
//---------------------------------------------------------------------------
void __fastcall SetZeroPosition()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->edZeroX->Text = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->edZeroY->Text = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->edZeroZ->Text = IntToStr(ipos);
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      MainForm->edZeroT->Text = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2016 5 20 - chc ��Load�I - �T�b�P�ɲ���
void __fastcall ToZeroPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z,t;
F64 lowdistance;

// 2016 8 31 - chc Set position x/y
bool flag = true;
AnsiString msg;
int dx,dy,dz,zlimit;
bool booloffset = false;

   MainForm->pnlToZeroPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->edZeroX->Text.ToInt();
   y = MainForm->edZeroY->Text.ToInt();
   z = MainForm->edZeroZ->Text.ToInt();
   t = MainForm->edZeroT->Text.ToInt();

   // 2021 5 4 - chc �Y�O�b�ɱצ�m, �n���vX/Y/Z
   // 2023 8 3 - chc �W�߶b���ݭn��
   /*
   if(MainForm->IsHeadTilt() == true) {
      booloffset = true;
      zlimit = MainForm->GetZLimit();
      dx = MainForm->edZeroX->Text.ToInt() - MainForm->edTiltX->Text.ToInt();
      dy = MainForm->edZeroY->Text.ToInt() - MainForm->edTiltY->Text.ToInt();
      dz = MainForm->edZeroZ->Text.ToInt() - MainForm->edTiltZ->Text.ToInt();
      msg.sprintf("Check�b�ɱצ�m: dx,dy,dz=%d,%d,%d",dx,dy,dz);
      MainForm->WriteSystemLog(msg);
      x += dx;
      y += dx;
      z += dx;
      if(z > zlimit)
         z = zlimit;
   }
   */

   // �̦��ǰ�X/Y/Z
   MoveToXYZT(x,y,z,t,1);

   // 2021 5 4 - chc �Y�O�b�ɱצ�m, �n���vX/Y/Z
   // �]MoveToXYZT()���|��X/Y/Z
   if(booloffset == true) {
      msg.sprintf("Low speed compensation: dx,dy,dz=%d,%d,%d",dx,dy,dz);
      MainForm->WriteSystemLog(msg);
      MainForm->pnlSystemMessage->Caption = msg;
      int oldspeed = MainForm->rgSpeed->ItemIndex;
      MainForm->rgSpeed->ItemIndex = 0;
      DoRelativeMove(X_AXIS, dx);
      DoRelativeMove(Y_AXIS, dy);
      DoRelativeMove(Z_AXIS, dz);
      MainForm->rgSpeed->ItemIndex = oldspeed;
   }

   return;
}
//---------------------------------------------------------------------------
// 2016 5 30 - chc Set Original Position
void __fastcall SetLoadPosition()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->edLoadX->Text = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->edLoadY->Text = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->edLoadZ->Text = IntToStr(ipos);
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      MainForm->edLoadT->Text = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2016 5 30 - chc ��Original�I - �T�b�P�ɲ���
void __fastcall ToLoadPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z,t;
F64 lowdistance;

// 2016 8 31 - chc Set position x/y
bool flag = true;

   MainForm->pnlLoad->Color = clSilver;
   MainForm->pnlToLoadPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->edLoadX->Text.ToInt();
   y = MainForm->edLoadY->Text.ToInt();
   z = MainForm->edLoadZ->Text.ToInt();
   t = MainForm->edLoadT->Text.ToInt();

   // 2023 8 11 - chc �O�_�w�b��m�W?
   int ox,oy,oz,oz1,diff;
   double fcmd;
   GetPosition(X_AXIS, &fcmd);
   ox = fcmd;
   GetPosition(Y_AXIS, &fcmd);
   oy = fcmd;
   GetPosition(Z_AXIS, &fcmd);
   oz = fcmd;
   GetPosition(Z1_AXIS, &fcmd);
   oz1 = fcmd;
   diff = 100;
   if(abs(x - ox) < diff && abs(y - oy) < diff && abs(z - oz) < 2*diff && abs(t - oz1) < diff) {
      MainForm->WriteSystemLog("TO Load: �ثe��m�b�J���I, �L�ݲ���.");
      MainForm->pnlToLoadPosition->Color = clLime;
      MainForm->pnlLoad->Color = clLime;
      return;
   }

   // �̦��ǰ�X/Y/Z
   MoveToXYZT(x,y,z,t,0);
   return;
}
//---------------------------------------------------------------------------
// Adjust X/Y after R-Axis moving(Within function)
void __fastcall ToAdjustXY()
{
I32 cmd;
I16 axisno;
double r,degree,x1,y1,radians,x2,y2;
int tpos,dx,dy;
AnsiString msg;
bool flag = false;

   // T , ���ե�(0 ~ 320�U)
   axisno = T_AXIS;
   GetCommand(axisno, &cmd);
   tpos = cmd;

   // 2016 8 11 - chc Adjust T Value
   tpos += MainForm->edDistanceT->Text.ToInt();

   while(1) {
      if(tpos > MAX_T_PULSE) {
         tpos -= MAX_T_PULSE;
      }
      else
         break;
   }
   while(1) {
      if(tpos < (0-MAX_T_PULSE)) {
         tpos += MAX_T_PULSE;
      }
      else
         break;
   }

   // 2016 8 11 - chc not force to positive
   //if(tpos < 0)
   //   tpos += MAX_T_PULSE;

   // r
   x1 = CurrentX;
   x1 = x1 * x1;
   y1 = CurrentY;
   y1 = y1 * y1;
   r = sqrt(x1 + y1);
   // Degree
   degree = 360.0 * tpos / MAX_T_PULSE;
   degree -= CurrentDegree;
   radians = (degree * 2 * M_PI) / 360.0;
   radians += CurrentRadians;
   x1 = r * cos(radians);
   y1 = r * sin(radians);

   // 2016 6 4 - chc ��1/4�H���~�n��(X,Y): -:- or -:+
   int mx,my;
   // X
   axisno = X_AXIS;
   GetCommand(axisno, &cmd);
   mx = cmd;
   mx = cmd - MainForm->edTiltX->Text.ToInt();
   // Y
   axisno = Y_AXIS;
   GetCommand(axisno, &cmd);
   my = cmd;
   my = cmd - MainForm->edTiltY->Text.ToInt();
   if((mx < 0 && my < 0) || (mx < 0 && my > 0)) {
      x1 = 0 - x1;
      y1 = 0 - y1;
   }

   // 2016 6 28 - chc Log
   msg.sprintf("ToAdjustXY(x1,y1,CurrentX,CurrentY): %.1f, %.1f, %.1f, %.1f",x1,y1,CurrentX,CurrentY);
   MainForm->WriteSystemLog(msg);

   x1 -= CurrentX;
   y1 -= CurrentY;

   // 2016 6 28 - chc Log
   msg.sprintf("ToAdjustXY(x1-CurrentX,,y1-CurrentY): %.1f, %.1f",x1,y1);
   MainForm->WriteSystemLog(msg);

   // Jog : do after stop
   int maxdiff = 5000;
   if(MainForm->cbContinueMove->Checked == false)
      maxdiff = 5000000;

   // 2016 6 4 - chc Offset too big?
   if(fabs(x1) > maxdiff) {
      flag = true;
      x1 = r * cos(radians);
      if((mx < 0 && my < 0) || (mx < 0 && my > 0)) {
         x1 = x1;
      }
      else {
         x1 = 0 - x1;
      }

      // 2016 6 28 - chc Log
      msg.sprintf("ToAdjustXY(x1 too big, x1,CurrentX): %.1f, %.1f",x1,CurrentX);
      MainForm->WriteSystemLog(msg);

      x1 -= CurrentX;
   }
   if(fabs(y1) > maxdiff) {
      flag = true;
      y1 = r * sin(radians);
      if((mx < 0 && my < 0) || (mx < 0 && my > 0)) {
         y1 = y1;
      }
      else {
         y1 = 0 - y1;
      }

      // 2016 6 28 - chc Log
      msg.sprintf("ToAdjustXY(y1 too big, y1,CurrentY): %.1f, %.1f",y1,CurrentY);
      MainForm->WriteSystemLog(msg);

      y1 -= CurrentY;
   }

   // �s�ʮ������q: 200000/200000/35000
   // Jog : do after stop
   if(MainForm->cbContinueMove->Checked == true) {
      x1 = x1 * MainForm->edContinueFactor->Text.ToDouble();
      y1 = y1 * MainForm->edContinueFactor->Text.ToDouble();
   }
   else {
      x1 = x1 * MainForm->edJogFactor->Text.ToDouble();
      y1 = y1 * MainForm->edJogFactor->Text.ToDouble();
   }

   // 2016 6 28 - chc Log
   msg.sprintf("ToAdjustXY(x1,y1 after adjusting): %.1f, %.1f",x1,y1);
   MainForm->WriteSystemLog(msg);

   if(MainForm->cbTXInvert->Checked == true)
      x2 = CurrentOX + x1;
   else
      x2 = CurrentOX - x1;
   if(MainForm->cbTYInvert->Checked == true)
      y2 = CurrentOY + y1;
   else
      y2 = CurrentOY - y1;

   // 2016 6 4 - chc X/Y Axis absolute move
   //MoveToX((int)x2);
   //MoveToY((int)y2);
   if(x2 != 0 && y2 != 0)

      // 2021 9 11 - chc �[�t: MOVE_WAIT
      //MoveToXY(x2,y2);
      MoveToXY(x2,y2,MOVE_WAIT);

   // 2016 6 3 - chc Log
   msg.sprintf("ToAdjustXY(dd,x,y,r:dx,dy:ra,cra): %.3f, %d, %d, %.1f : %d, %d : %.4f, %.4f",degree,(int)x2,(int)y2,r,(int)x1,(int)y1,radians,CurrentRadians);
   MainForm->WriteSystemLog(msg);

}
//---------------------------------------------------------------------------
// 2016 6 4 - chc X/Y Axis absolute move
// 2021 9 11 - chc �[�t: MOVE_WAIT
//bool __fastcall MoveToXY(int xpos,int ypos)
bool __fastcall MoveToXY(int xpos,int ypos, int mode)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   // X
   axisno = X_AXIS;
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToXY: X in Moving!");
      // ����
      //return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;
   // Y
   axisno = Y_AXIS;
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToXY: Y in Moving!");
      // ����
      //return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   axisno = X_AXIS;
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   F64 fxpos,fypos;
   fxpos = xpos;
   fypos = ypos;
   int ispeed;
   ispeed = maxvel;
   MainForm->WriteSystemLog("MoveToXY: Speed = " + IntToStr(ispeed));
   ret = AbsoluteMoveXY(0,fxpos,fypos,startvel,maxvel,tacc,tdec);

   // timeout : MOTION_TIMEOUT
   // 2021 9 11 - chc �[�t: MOVE_WAIT
   if(mode == MOVE_WAIT) {

      WaitMotionDoneXY(3,MOTION_TIMEOUT);
      axisno = X_AXIS;
      MainForm->iAxisMove[axisno] = NO_MOVE;
      axisno = Y_AXIS;
      MainForm->iAxisMove[axisno] = NO_MOVE;
   }

   return true;
}
//---------------------------------------------------------------------------
// 2016 7 8 - chc Set Last Position
void __fastcall SetLastPosition()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->edLastX->Text = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->edLastY->Text = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->edLastZ->Text = IntToStr(ipos);
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      MainForm->edLastT->Text = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2016 7 8 - chc to Last Position - 3 Axises move
void __fastcall ToLastPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z,t;
F64 lowdistance;

// 2016 8 31 - chc Set position x/y
bool flag = true;

   MainForm->pnlToLastPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->edLastX->Text.ToInt();
   y = MainForm->edLastY->Text.ToInt();
   z = MainForm->edLastZ->Text.ToInt();
   t = MainForm->edLastT->Text.ToInt();
   // �̦��ǰ�X/Y/Z
   MoveToXYZT(x,y,z,t,3);
   return;
}
//---------------------------------------------------------------------------
// 2016 7 9 - chc User Position
void __fastcall SetUserPosition(int no)
{
I32 cmd;
F64 fcmd;
TLMDEdit *edx,*edy,*edz,*edt;

   // 2016 7 29 - chc to Check
   if(Application->MessageBox(("Sure to set user position" + IntToStr(no) + "? ").c_str(), "User Position", MB_YESNO|MB_SYSTEMMODAL) == IDNO)
      return;

   edx = (TLMDEdit *)(MainForm->FindComponent("edPos" + IntToStr(no) + "X"));
   edy = (TLMDEdit *)(MainForm->FindComponent("edPos" + IntToStr(no) + "Y"));
   edz = (TLMDEdit *)(MainForm->FindComponent("edPos" + IntToStr(no) + "Z"));
   edt = (TLMDEdit *)(MainForm->FindComponent("edPos" + IntToStr(no) + "T"));

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      edx->Text = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      edy->Text = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      edz->Text = IntToStr(ipos);
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      edt->Text = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2016 7 9 - chc User Position
void __fastcall ToUserPosition(int no)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z,t;
F64 lowdistance;
TLMDEdit *edx,*edy,*edz,*edt;

// 2016 8 31 - chc Set position x/y
bool flag = true;

   MainForm->pnlToUserPosition->Color = clSilver;
   edx = (TLMDEdit *)(MainForm->FindComponent("edPos" + IntToStr(no) + "X"));
   edy = (TLMDEdit *)(MainForm->FindComponent("edPos" + IntToStr(no) + "Y"));
   edz = (TLMDEdit *)(MainForm->FindComponent("edPos" + IntToStr(no) + "Z"));
   edt = (TLMDEdit *)(MainForm->FindComponent("edPos" + IntToStr(no) + "T"));
   x = edx->Text.ToInt();
   y = edy->Text.ToInt();
   z = edz->Text.ToInt();
   t = edt->Text.ToInt();

   // �̦��ǰ�X/Y/Z
   MoveToXYZT(x,y,z,t,4);
}
//---------------------------------------------------------------------------
// 2016 7 18 - chc Backlash Control
// ret : 0-Ok, -1:Fail
int __fastcall RelativeMove(I16 axisno,F64 pos,F64 startvel,F64 maxvel,F64 tacc,F64 tdec)
{
I16 ret;
int pno,odir,ndir;
F64 opos;
TColor color;

// 2021 12 18 - chc Error motion busy
int trycnt = 0;

   // 2020 3 3 - chc Log
   AnsiString str;
   str.sprintf("RelativeMove(���ʫe): No,Dist,SV,MV,TA,TD= %d,%d,%d,%d,%.2f,%.2f",axisno,(int)pos,(int)startvel,(int)maxvel,tacc,tdec);
   MainForm->WriteSystemLog(str);

   // 2021 4 24 - chc �w���ˬd
   // 2023 8 4 - chc Check z Limit : CheckZLimit(axisno,&pos)
   //if(axisno == Z_AXIS && pos > 0) {
   //   if(MotionMode == MOTION_MODE_APS) {
   //      I32 ipos;
   //      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
   //      int limit = MainForm->GetZLimit();
   //      if((ipos + pos) > limit)
   //         pos = limit - ipos;
   //   }
   //}
   if((axisno == Z_AXIS || axisno == T_AXIS) && pos > 0) {
      I32 ipos;
      APS_get_position(axisno+StartAxisNo,&ipos);
      int position;
      position = ipos + pos;

      str.sprintf("RelativeMove(���ʫe): �b��,�첾,�ثe��m,�ؼЦ�m= %d,%d,%d,%d",axisno,(int)pos,(int)ipos,position);
      MainForm->WriteSystemLog(str);

      CheckZLimit(axisno,&position);
      pos = position - ipos;

      str.sprintf("RelativeMove(���ʫe): �̲צ�m,�첾= %d,%d",position,(int)pos);
      MainForm->WriteSystemLog(str);

      // 2023 8 4 - chc
      if(pos == 0) {
         str.sprintf("RelativeMove(���ʫe): ���ʶq��0, ������");
         MainForm->WriteSystemLog(str);
         return 0;
      }
   }

// 2021 12 18 - chc Error motion busy
retry:

   // ���B�zBacklash
   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {

      str.sprintf("RelativeMove(���ʩR�O�e): ���ʶq,MVel=%d,%d",(int)pos,(int)maxvel);
      MainForm->WriteSystemLog(str);

      ret = APS_relative_move(axisno+StartAxisNo,(int)pos,(int)maxvel);
   }

   // 2021 12 18 - chc Motion Busy Error Code: �y��joystick���|��!
   if(ret != 0) {
      MainForm->WriteSystemLog(">Motion Error(RelativeMove): " + IntToStr(ret));
      // Error motion busy
      if(ret == -10313) {
         MainForm->WriteSystemLog(">Motion Error(RelativeMove): Error motion busy, �A���UCommand");
         Sleep(200);
         trycnt++;
         if(trycnt < 3)
            goto retry;
      }
      MainForm->iAxisMove[axisno] = NO_MOVE;
      return -1;
   }

   // 2021 5 4 - chc ��Motion Done�γ]��
   if(WaitMotionDone(axisno, 10000) == false)
      ret = -1;
   else {
      MainForm->WriteSystemLog(">RelativeMove: ok");
      ret = 0;
   }

   MainForm->iAxisMove[axisno] = NO_MOVE;

   return ret;

}
//---------------------------------------------------------------------------
// 2016 7 18 - chc Backlash Control
int __fastcall AbsoluteMove(I16 axisno,F64 pos,F64 startvel,F64 maxvel,F64 tacc,F64 tdec)
{
I16 ret;

// 2021 12 18 - chc Motion Busy
int trycnt = 0;

   // 2021 4 24 - chc �w���ˬd
   // 2023 8 4 - chc Check z Limit : CheckZLimit(axisno,&pos)
   //if(axisno == Z_AXIS) {
   //   int limit = MainForm->GetZLimit();
   //   if(pos > limit)
   //      pos = limit;
   //}
   int position;
   position = pos;
   CheckZLimit(axisno,&position);
   pos = position;

// 2021 12 18 - chc Error motion busy
retry:

   // ���B�zBacklash
   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);
   }

   // 2021 12 18 - chc Motion Busy Error Code: �y��joystick���|��!
   if(ret != 0) {
      MainForm->WriteSystemLog(">Motion Error(AbsoluteMove): " + IntToStr(ret));
      // Error motion busy
      if(ret == -10313) {
         MainForm->WriteSystemLog(">Motion Error(AbsoluteMove): Error motion busy, �A���UCommand");
         Sleep(200);
         trycnt++;
         if(trycnt < 3)
            goto retry;
      }
      MainForm->iAxisMove[axisno] = NO_MOVE;
      return -1;
   }

   // 2021 6 30 - chc ��Motion Done�γ]�� => ���ˬd�O�_Done!!!
   if(WaitMotionDone(axisno, 10000) == false)
      ret = -1;
   else
      ret = 0;
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return ret;
}
//---------------------------------------------------------------------------
// 2016 7 18 - chc Backlash Control
int __fastcall AbsoluteMoveXY(I16 axisno,F64 fxpos,F64 fypos,F64 startvel,F64 maxvel,F64 tacc,F64 tdec)
{
I16 ret;
I16 xmstatus,ymstatus;
int counter = 0;
int maxtimeout;

   maxtimeout = 2000;                                                        // 100sec

   // 2016 12 14 - chc Log
   MainForm->WriteSystemLog("��AbsoluteMoveXY�ֳt, MaxVel= " + FloatToStr(maxvel));

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      MainForm->WriteSystemLog("��APS_absolute_move, (px,py)= " + FloatToStr(fxpos) + "," + FloatToStr(fypos));
      ret = APS_absolute_move(X_AXIS+StartAxisNo,(int)fxpos,(int)maxvel);
      ret = APS_absolute_move(Y_AXIS+StartAxisNo,(int)fypos,(int)maxvel);
      MainForm->WriteSystemLog("��APS_absolute_move, ��Done...");
   }
   // 2016 12 13 - chc fast speed
   boolFastSpeed = false;

   DelayTimeM5(50);
   // Wait Done
   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         xmstatus = 0;
         ymstatus = 0;
         I32 done;
         done = APS_motion_status(X_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            xmstatus = 1;
         done = APS_motion_status(Y_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            ymstatus = 1;
      }
      if((xmstatus == 0 || xmstatus == 17 || xmstatus == 18) && (ymstatus == 0 || ymstatus == 17 || ymstatus == 18)) {
         break;
      }
      else {
         DelayTimeM5(50);
         counter++;
         // 500sec: 50*maxtimeout
         if(counter > maxtimeout) {
            MainForm->pnlSystemMessage->Caption = "Wait Motion Done Timeout!";
            break;
         }
      }
   }
   return ret;
}
//---------------------------------------------------------------------------
// 2016 9 9 - chc round function
int __fastcall round(double f)
{
int value;

   if(f >= 0)
      value = (int)(f + 0.5);
   else
      value = (int)(f - 0.5);
   return value;
}
//---------------------------------------------------------------------------
// 2016 8 2 - chc Lens Position
void __fastcall SetLensPosition(int no)
{
I32 cmdx,cmdy,cmdz,cmdt;
F64 fcmdx,fcmdy,fcmdz,fcmdt;
TLMDEdit *editx,*edity,*editz,*editt;

   // 2016 10 14 - chc Confirm
   if(Application->MessageBox((AnsiString("Set Center of Lens ") + IntToStr(no) + " ? ").c_str(), "Center Setting Operation", MB_YESNO|MB_SYSTEMMODAL) == IDNO) {
      return;
   }

   editx = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "X"));
   edity = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "Y"));
   editz = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "Z"));
   editt = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "T"));

   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      editx->Text = IntToStr(ipos);
      cmdx = ipos;
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      edity->Text = IntToStr(ipos);
      cmdy = ipos;
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      editz->Text = IntToStr(ipos);
      cmdz = ipos;
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      editt->Text = IntToStr(ipos);
      cmdt = ipos;
   }
   // 2016 10 3 - chc Cneter Of Each Lens
   MainForm->LensPosition[no-1].X = cmdx;
   MainForm->LensPosition[no-1].Y = cmdy;
   MainForm->LensPosition[no-1].Z = cmdz;
   MainForm->LensPosition[no-1].T = cmdt;

   // 2016 10 9 - chc Set Current Lens
   // 2017 1 3 - chc �Ȥ���
   /*
   if(no == MainForm->LensNo) {
      MainForm->TiltX = MainForm->LensPosition[no-1].X;
      MainForm->edTiltX->Text = IntToStr(MainForm->TiltX);
      MainForm->TiltY = MainForm->LensPosition[no-1].Y;
      MainForm->edTiltY->Text = IntToStr(MainForm->TiltY);
      MainForm->TiltZ = MainForm->LensPosition[no-1].Z;
      MainForm->edTiltZ->Text = IntToStr(MainForm->TiltZ);
      MainForm->TiltT = MainForm->LensPosition[no-1].T;
      MainForm->edTiltT->Text = IntToStr(MainForm->TiltT);
   }
   */

}
//---------------------------------------------------------------------------
// 2016 8 2 - chc to Lens Center
void __fastcall ToLensPosition(int no)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z,t;
F64 lowdistance;
TLMDEdit *editx,*edity,*editz,*editt;
TPanel *panel;

   // pnlToLens1Position
   panel = (TPanel *)(MainForm->FindComponent("pnlToLens" + IntToStr(no) + "Position"));
   editx = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "X"));
   edity = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "Y"));
   editz = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "Z"));
   editt = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "T"));
   // �n��Edit����
   x = editx->Text.ToInt();
   y = edity->Text.ToInt();
   z = editz->Text.ToInt();
   t = editt->Text.ToInt();
   panel->Color = clSilver;

   // �̦��ǰ�X/Y/Z
   MoveToXYZT(x,y,z,t,5);
   panel->Color = MainForm->pnlToLensPosition->Color;
}
//---------------------------------------------------------------------------
// 2016 8 21 - chc ������X/Y/T
// mode : ����
void __fastcall WaitMotionDoneXYT(int mode, int ms)
{
I32 cmd;
I16 mstatusx,mstatusy,mstatust;
int counter;
int max,axisno;

   counter = 0;
   max = ms / 10;
   DelayTimeM5(10);

   if(MotionMode == MOTION_MODE_APS) {
      mstatusx = 0;
      mstatusy = 0;
      mstatust = 0;
      I32 done;
      done = APS_motion_status(X_AXIS+StartAxisNo);
      // ��bit 0 : ������0(Done)
      if((done & 0x01) == 0)
         mstatusx = 1;
      done = APS_motion_status(Y_AXIS+StartAxisNo);
      // ��bit 0 : ������0(Done)
      if((done & 0x01) == 0)
         mstatusy = 1;
      done = APS_motion_status(T_AXIS+StartAxisNo);
      // ��bit 0 : ������0(Done)
      if((done & 0x01) == 0)
         mstatust = 1;
   }
   while(1) {
      if(mstatusx != 0) {
         if(MotionMode == MOTION_MODE_APS) {
            mstatusx = 0;
            I32 done;
            done = APS_motion_status(X_AXIS+StartAxisNo);
            // ��bit 0 : ������0(Done)
            if((done & 0x01) == 0)
               mstatusx = 1;
         }
      }
      if(mstatusy != 0) {
         if(MotionMode == MOTION_MODE_APS) {
            mstatusy = 0;
            I32 done;
            done = APS_motion_status(Y_AXIS+StartAxisNo);
            // ��bit 0 : ������0(Done)
            if((done & 0x01) == 0)
               mstatusy = 1;
         }
      }
      if(mstatust != 0) {
         if(MotionMode == MOTION_MODE_APS) {
            mstatust = 0;
            I32 done;
            done = APS_motion_status(T_AXIS+StartAxisNo);
            // ��bit 0 : ������0(Done)
            if((done & 0x01) == 0)
               mstatust = 1;
         }
      }
      if((mstatusx == 0 || mstatusx == 17 || mstatusx == 18) &&
         (mstatusy == 0 || mstatusy == 17 || mstatusy == 18) &&
         (mstatust == 0 || mstatust == 17 || mstatust == 18)) {
         break;
      }
      else {
         DelayTimeM5(10);
         counter++;
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion XYT Done Timeout!";
         }
      }
   }
}
//---------------------------------------------------------------------------
// 2016 10 9 - chc Lens Z Limit
void __fastcall SetLensZLimit(int no)
{
I32 cmdz;
F64 fcmdz;
TLMDEdit *editz;

   editz = (TLMDEdit *)(MainForm->FindComponent("edLens" + IntToStr(no) + "ZLimit"));
   // Command

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      fcmdz = ipos;
   }
   cmdz = fcmdz;

   editz->Text = cmdz;
   MainForm->LensPosition[no-1].ZLimit = cmdz;
}
//---------------------------------------------------------------------------
// 2016 10 12 - chc ������wXYZ��m
void __fastcall RelativeMoveXYZ(double dx, double dy, double dz)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,posi;
int sx,sy,ret;
F64 lowdistance;

   // 2019 12 18 - chc For Test
   if(MainForm->boolForTest == true)
      return;

   // �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE || MainForm->iAxisMove[Z_AXIS] != NO_MOVE)
      return;
   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Z_AXIS] = FORWARD_MOVE;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      int ret;
      GetAxisData(X_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
      ret = RelativeMove(X_AXIS,dx,startvel,maxvel,tacc,tdec);
      GetAxisData(Y_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
      ret = RelativeMove(Y_AXIS,dy,startvel,maxvel,tacc,tdec);
      GetAxisData(Z_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
      ret = RelativeMove(Z_AXIS,dz,startvel,maxvel,tacc,tdec);
   }

   WaitMotionDoneXYZ(3,5000);
   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Z_AXIS] = NO_MOVE;

}
//---------------------------------------------------------------------------
// 2016 10 14 - chc X/Y Axis absolute move
bool __fastcall MoveToXYDirect(int xpos,int ypos)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   // X
   axisno = X_AXIS;
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;
   // Y
   axisno = Y_AXIS;
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   axisno = X_AXIS;
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   F64 fxpos,fypos;
   fxpos = xpos;
   fypos = ypos;

   ret = AbsoluteMoveXY(0,fxpos,fypos,startvel,maxvel,tacc,tdec);
   WaitMotionDoneXY(3,MOTION_TIMEOUT);

   axisno = X_AXIS;
   MainForm->iAxisMove[axisno] = NO_MOVE;
   axisno = Y_AXIS;
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2019 7 8 - chc ���otdec
double __fastcall GetTdec(int axisno)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
F64 lowdistance;

   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   return tdec;
}
//---------------------------------------------------------------------------
// 2019 7 14 - chc CCD Position
void __fastcall SetCCDPosition()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->edCCDX->Text = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->edCCDY->Text = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->edCCDZ->Text = IntToStr(ipos);
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      MainForm->edCCDT->Text = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2019 7 14 - chc Wait Motion X/Y done
bool __fastcall WaitMotionXYDone(int ms)
{
I32 cmd;
I16 mstatusx,mstatusy;
int counter;
int max,axisno;

   counter = 0;
   max = ms / 10;
   DelayTimeM4(10);

   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         mstatusx = 0;
         mstatusy = 0;
         I32 done;
         done = APS_motion_status(X_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusx = 1;
         done = APS_motion_status(Y_AXIS+StartAxisNo);
         // ��bit 0 : ������0(Done)
         if((done & 0x01) == 0)
            mstatusy = 1;
      }
      if((mstatusx == 0 || mstatusx == 17 || mstatusx == 18) &&
         (mstatusy == 0 || mstatusy == 17 || mstatusy == 18)) {
         break;
      }
      else {
         DelayTimeM4(10);
         counter++;
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Motion XY Done Timeout!";
            return false;
         }
      }
   }
   return true;
}
//---------------------------------------------------------------------------
// 2019 7 14 - chc to CCD Position
void __fastcall ToCCDPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z,t;
F64 lowdistance;

bool flag = true;

   MainForm->pnlToCCDPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->edCCDX->Text.ToInt();
   y = MainForm->edCCDY->Text.ToInt();
   z = MainForm->edCCDZ->Text.ToInt();
   t = MainForm->edCCDT->Text.ToInt();
   // �̦��ǰ�X/Y/Z
   MoveToXYZT(x,y,z,t,6);
   return;
}
//---------------------------------------------------------------------------
// 2019 7 15 - chc Area: �ϰ���I
void __fastcall SetAreaPosition()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->pnlAreaX->Caption = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->pnlAreaY->Caption = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->pnlAreaZ->Caption = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2019 7 15 - chc Area
void __fastcall SetDotPosition()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->pnlDotX->Caption = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->pnlDotY->Caption = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->pnlDotZ->Caption = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2019 7 15 - chc Base1
void __fastcall SetBase1Position()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->pnlBase1X->Caption = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->pnlBase1Y->Caption = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->pnlBase1Z->Caption = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2019 7 15 - chc Base2
void __fastcall SetBase2Position()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->pnlBase2X->Caption = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->pnlBase2Y->Caption = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->pnlBase2Z->Caption = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2019 7 14 - chc to Area Position
bool __fastcall ToAreaPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z;
F64 lowdistance;

bool flag = true;

   MainForm->pnlToAreaPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->pnlAreaX->Caption.ToInt();
   y = MainForm->pnlAreaY->Caption.ToInt();
   z = MainForm->pnlAreaZ->Caption.ToInt();
   // �̦��ǰ�X/Y/Z: for Area/Dot
   MoveToXYZ(x,y,z,0);
   if(MainForm->pnlToAreaPosition->Color == clRed)
      flag = false;
   return flag;
}
//---------------------------------------------------------------------------
// 2019 7 14 - chc to Dot Position
bool __fastcall ToDotPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z;
F64 lowdistance;

bool flag = true;

   MainForm->pnlToDotPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->pnlDotX->Caption.ToInt();
   y = MainForm->pnlDotY->Caption.ToInt();
   z = MainForm->pnlDotZ->Caption.ToInt();
   // ���O�Ĥ@�ϭn�ഫ
   int basex,basey,basez,i;
   i = MainForm->edAreaNo->Text.ToInt();

   // 2021 5 5 - chc �H�����I�����v
   //basex = MainForm->sgArea->Cells[1][i].ToInt() - MainForm->sgArea->Cells[1][1].ToInt();
   //basey = MainForm->sgArea->Cells[2][i].ToInt() - MainForm->sgArea->Cells[2][1].ToInt();
   //basez = MainForm->sgArea->Cells[3][i].ToInt() - MainForm->sgArea->Cells[3][1].ToInt();
   if(MainForm->pnlCenterXFind->Caption != "0")
      basex = MainForm->pnlCenterXFind->Caption.ToInt() - MainForm->sgArea->Cells[1][1].ToInt();
   else
      basex = 0;
   if(MainForm->pnlCenterYFind->Caption != "0")
      basey = MainForm->pnlCenterYFind->Caption.ToInt() - MainForm->sgArea->Cells[2][1].ToInt();
   else
      basey = 0;
   basez = 0;

   x = x + basex;
   y = y + basey;
   z = z + basez;
   // �̦��ǰ�X/Y/Z: for Area/Dot
   MoveToXYZ(x,y,z,1);
   if(MainForm->pnlToDotPosition->Color == clRed)
      flag = false;
   return flag;
}
//---------------------------------------------------------------------------
// 2019 7 14 - chc to Base1 Position
bool __fastcall ToBase1Position()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z;
F64 lowdistance;

bool flag = true;

   MainForm->pnlToBase1Position->Color = clSilver;
   // �n��Edit����
   x = MainForm->pnlBase1X->Caption.ToInt();
   y = MainForm->pnlBase1Y->Caption.ToInt();
   z = MainForm->pnlBase1Z->Caption.ToInt();
   // �̦��ǰ�X/Y/Z: for Area/Dot
   MoveToXYZ(x,y,z,2);
   if(MainForm->pnlToBase1Position->Color == clRed)
      flag = false;
   return flag;
}
//---------------------------------------------------------------------------
// 2019 7 14 - chc to Base2 Position
bool __fastcall ToBase2Position()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z;
F64 lowdistance;

bool flag = true;

   MainForm->pnlToBase2Position->Color = clSilver;
   // �n��Edit����
   x = MainForm->pnlBase2X->Caption.ToInt();
   y = MainForm->pnlBase2Y->Caption.ToInt();
   z = MainForm->pnlBase2Z->Caption.ToInt();
   // �̦��ǰ�X/Y/Z: for Area/Dot
   MoveToXYZ(x,y,z,3);
   if(MainForm->pnlToBase2Position->Color == clRed)
      flag = false;
   return flag;
}
//---------------------------------------------------------------------------
// 2019 7 23 - chc X/Y Axis absolute move Ratio
bool __fastcall MoveToXYRatio(int xpos,int ypos, double ratio)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   // X
   axisno = X_AXIS;
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToXY: X in Moving!");
      // ����
      //return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;
   // Y
   axisno = Y_AXIS;
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToXY: Y in Moving!");
      // ����
      //return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   axisno = X_AXIS;
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   F64 fxpos,fypos;
   fxpos = xpos;
   fypos = ypos;
   maxvel *= ratio;
   ret = AbsoluteMoveXY(0,fxpos,fypos,startvel,maxvel,tacc,tdec);
   // timeout : MOTION_TIMEOUT
   WaitMotionDoneXY(3,MOTION_TIMEOUT);

   axisno = X_AXIS;
   MainForm->iAxisMove[axisno] = NO_MOVE;
   axisno = Y_AXIS;
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2019 11 18 - chc ������wXY��m
void __fastcall RelativeMoveXY(double dx, double dy)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,posi;
int sx,sy,ret;
F64 lowdistance;

   // 2019 12 18 - chc For Test
   if(MainForm->boolForTest == true)
      return;

   // �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE)
      return;
   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;

   // 2019 11 29 - chc �n���ostartvel...
   GetAxisData(X_AXIS,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   // �ϥ�XY�P��
   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      ret = APS_relative_move(X_AXIS+StartAxisNo,(int)dx,(int)maxvel);
      ret = APS_relative_move(Y_AXIS+StartAxisNo,(int)dy,(int)maxvel);
   }
   WaitMotionDoneXY(3,5000);
   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;

}
//---------------------------------------------------------------------------
// 2019 12 5 - chc to TXT Position
void __fastcall ToTXTPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z;
F64 lowdistance;

bool flag = true;

   MainForm->pnlToTXTPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->edkmfX->Text.ToInt();
   y = MainForm->edkmfY->Text.ToInt();

   // From Relative Move
   if(MainForm->boolRelativeMove == true) {
      x += MainForm->RelativeMoveX;
      y += MainForm->RelativeMoveY;
      // Set position x/y
      flag = false;
   }

   // Check moving?
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE)
      return;

   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;

   // 2021 9 11 - chc �[�t: MOVE_WAIT
   //MoveToXY(x,y);
   MoveToXY(x,y,MOVE_WAIT);

   Sleep(100);

   if(WaitMotionXYDone(60000) == false) {
      MainForm->pnlSystemMessage->Caption = "kmf Original Move Fail!";
      MainForm->pnlToTXTPosition->Color = clRed;
   }
   else {
      MainForm->pnlSystemMessage->Caption = "kmf Original Move Completed.";
      MainForm->pnlToTXTPosition->Color = clLime;
   }

   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;

}
//---------------------------------------------------------------------------
// 2019 12 5 - chc TXT Position
void __fastcall SetTXTPosition()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->edkmfX->Text = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->edkmfY->Text = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2019 12 5 - chc to TXT Position
void __fastcall TokmfPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z;
F64 lowdistance;

bool flag = true;

   MainForm->pnlToTXTPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->pnlkmfX->Caption.ToInt();
   y = MainForm->pnlkmfY->Caption.ToInt();

   // From Relative Move
   if(MainForm->boolRelativeMove == true) {
      x += MainForm->RelativeMoveX;
      y += MainForm->RelativeMoveY;
      // Set position x/y
      flag = false;
   }

   // Check moving?
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE)
      return;

   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;

   // 2021 9 11 - chc �[�t: MOVE_WAIT
   //MoveToXY(x,y);
   MoveToXY(x,y,MOVE_WAIT);

   Sleep(100);

   if(WaitMotionXYDone(60000) == false) {
      MainForm->pnlSystemMessage->Caption = "kmf Point Move Fail!";
      MainForm->pnlToTXTPosition->Color = clRed;
   }
   else {
      MainForm->pnlSystemMessage->Caption = "kmf Point Move Completed.";
      MainForm->pnlToTXTPosition->Color = clLime;
   }

   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;

}
//---------------------------------------------------------------------------
// 2020 2 11 - chc ����I�۹ﲾ��
void __fastcall SetMoveBasePosition()
{
I32 cmd;
F64 fcmd;

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->pnlMoveBaseX->Caption = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->pnlMoveBaseY->Caption = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2020 2 11 - chc ����I�۹ﲾ��
bool __fastcall ToMoveBasePosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y;
F64 lowdistance;

bool flag = true;

   MainForm->pnlToMoveBasePosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->pnlMoveBaseX->Caption.ToInt();
   y = MainForm->pnlMoveBaseY->Caption.ToInt();

   // From Relative Move
   if(MainForm->boolRelativeMove == true) {
      x += MainForm->RelativeMoveX;
      y += MainForm->RelativeMoveY;
   }

   // Check moving?
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE) {
      flag = false;
      return flag;
   }

   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;

   // �ϥ�XY�P��
   // 2021 9 11 - chc �[�t: MOVE_WAIT
   //MoveToXY(x,y);
   MoveToXY(x,y,MOVE_WAIT);

   Sleep(100);
   if(WaitMotionXYDone(60000) == false) {
      MainForm->pnlSystemMessage->Caption = "Base Point Move Fail!";
      MainForm->pnlToMoveBasePosition->Color = clRed;
   }
   else {
      MainForm->pnlSystemMessage->Caption = "Base Point Move Completed.";
      MainForm->pnlToMoveBasePosition->Color = clLime;
   }

   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;

   return flag;
}
//---------------------------------------------------------------------------
// 2020 2 14a - chc ServoOn
void __fastcall ServoOn()
{
int svmode,axisno;

   // 2021 4 19 - chc 8154 or APS_
   // APS(7856)
   if(MotionMode == MOTION_MODE_APS) {
      int rdycnt = 0;
      // �Ұ�Motion: Servo on
      if(bool_APS_Status == true) {
         for(int axisno=0 ; axisno<MAX_AXIS_NO ; axisno++) {
            if(MainForm->DOServoOnOff(axisno,1) == true)
               rdycnt++;
         }
      }
      return;
   }
}
//---------------------------------------------------------------------------
// 2020 2 16 - chc Save Protect: pnlFrontOut
void __fastcall SetSaveProtect(int mode)
{
I32 cmd;
F64 fcmd;
TPanel *panel;
int axisno;

   switch(mode) {
      case 1:
         panel = (TPanel *)MainForm->pnlFrontOut;
         axisno = Y_AXIS;
         break;
      case 2:
         panel = (TPanel *)MainForm->pnlFrontIn;
         axisno = Y_AXIS;
         break;
      case 3:
         panel = (TPanel *)MainForm->pnlRightOut;
         axisno = X_AXIS;
         break;
      case 4:
         panel = (TPanel *)MainForm->pnlRightIn;
         axisno = X_AXIS;
         break;
      case 5:
         panel = (TPanel *)MainForm->pnlRearOut;
         axisno = Y_AXIS;
         break;
      case 6:
         panel = (TPanel *)MainForm->pnlRearIn;
         axisno = Y_AXIS;
         break;
      case 7:
         panel = (TPanel *)MainForm->pnlLeftOut;
         axisno = X_AXIS;
         break;
      case 8:
         panel = (TPanel *)MainForm->pnlLeftIn;
         axisno = X_AXIS;
         break;
   }

   // 2021 4 20 - chc APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(axisno+StartAxisNo,&ipos);
      fcmd = ipos;
   }
   cmd = fcmd;
   panel->Caption = cmd;
}
//---------------------------------------------------------------------------
// 2020 2 17 - chc Joystick������٭n�ˬd�䥦�b
void __fastcall StopAllAxis()
{
F64 tdec;

   for(int i=0 ; i<MAX_AXIS_NO ; i++) {
      if(MotionMode == MOTION_MODE_APS) {
         APS_stop_move(i+StartAxisNo);
      }
   }
}
//---------------------------------------------------------------------------
// 2020 3 5 - chc �̦��ǰ�X/Y/Z
// mode: 0-�J���I(��T), 1-����, 2-�ɱ�(��T), 3-Last(����T), 4-User(����T), 5-Lens(����T), 6-CCD(��T), 7-Center(����T), 8-�q���I(����T)
// 6-CCD�n�]�bT=0�צ�m
// 4-User, 5-Lens: ����T
// Z�b�b�w�����ץH�W�ɤ��ˬdT
// 2023 8 4 - chc �վ�
// 1. ���NZ/Z1����w����m - ��XY - �NZ/Z1������w��m
//    Z/Z1�w����m: Limit�A���WNum
// 2. ����mode�ʧ@���@��
//
void __fastcall MoveToXYZT(int x,int y,int z, int t, int mode)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos;
F64 lowdistance;
bool booltmove = false;
bool boolxyzt = false;
bool booldot = false;
F64 zpos,tpos;
I32 ipos;
AnsiString msg;
int waitmode = MOVE_WAIT;

   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE ||
      MainForm->iAxisMove[Z_AXIS] != NO_MOVE || MainForm->iAxisMove[T_AXIS] != NO_MOVE) {
      if(MainForm->iAxisMove[X_AXIS] != NO_MOVE)
         MainForm->WriteSystemLog("MoveToXYZT: X������!");
      if(MainForm->iAxisMove[Y_AXIS] != NO_MOVE)
         MainForm->WriteSystemLog("MoveToXYZT: Y������!");
      if(MainForm->iAxisMove[Z_AXIS] != NO_MOVE)
         MainForm->WriteSystemLog("MoveToXYZT: Z������!");
      if(MainForm->iAxisMove[T_AXIS] != NO_MOVE)
         MainForm->WriteSystemLog("MoveToXYZT: T������!");
      return;
   }

   // 2023 8 6 - chc MoveToXYZT���Χ���Z/Z1
   if(MainForm->boolMoveToXYZT_DoZ == true) {

      // ���NZ/Z1����w����m - ��XY - �NZ/Z1������w��m
      //  Z/Z1�w����m: Limit�A���WNum
      int zsafe;
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      zsafe = MainForm->GetZZ1Safe(Z_AXIS);
      if(ipos > zsafe) {
         if(MoveToZ(zsafe,MOVE_WAIT) == false) {
            MainForm->pnlAlarmMessage->Caption = "Z�b�w����m���ʥ���!";
            goto end;
         }
         msg.sprintf("MoveToXYZT: ZMove���ʦw����m = %d,%d",z,zsafe);
         MainForm->WriteSystemLog(msg);
      }
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      zsafe = MainForm->GetZZ1Safe(T_AXIS);
      if(ipos > zsafe) {
         if(MoveToT(zsafe) == false) {
            MainForm->pnlAlarmMessage->Caption = "Z1�b�w����m���ʥ���!";
            goto end;
         }
         msg.sprintf("MoveToXYZT: Z1Move���ʦw����m = %d,%d",t,zsafe);
         MainForm->WriteSystemLog(msg);
      }
   }

   // XY Move
   MainForm->pnlAlarmMessage->Caption = "����XY...";
   waitmode = MOVE_WAIT;
   msg.sprintf("MoveToXYZT: x,y= %d,%d",x,y);
   MainForm->WriteSystemLog(msg);
   if(MoveToXY(x,y,waitmode) == false) {
      MainForm->pnlAlarmMessage->Caption = "XY�b���ʥ���!";
      goto end;
   }

   // 2023 8 6 - chc MoveToXYZT���Χ���Z/Z1
   if(MainForm->boolMoveToXYZT_DoZ == true) {

      // Z��w��
      msg.sprintf("MoveToXYZT: Z���ʦ�m = %d",z);
      MainForm->WriteSystemLog(msg);
      if(MoveToZ(z,MOVE_WAIT) == false) {
         MainForm->pnlAlarmMessage->Caption = "Z�b��m���ʥ���!";
         goto end;
      }

      // Z1��w��
      msg.sprintf("MoveToXYZT: Z1���ʦ�m = %d",t);
      MainForm->WriteSystemLog(msg);
      if(MoveToT(t) == false) {
         MainForm->pnlAlarmMessage->Caption = "Z1�b��m���ʥ���!";
         goto end;
      }
      // �O���ثeT��m
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      MainForm->WriteSystemLog("MoveToXYZT: ����T. �зǦ�m,�ثe��m= " + IntToStr(t) + "," + IntToStr(ipos));
   }

   Sleep(100);
   if(WaitMotionXYZTDone(90000) == false) {
end:
      boolxyzt = false;
      // mode: 0-���I, 1-����, 2-�ɱ�, 3-�J��(last), 4-User, 5-Lens(����T), 6-CCD
      // ���I
      if(mode == 0) {
         MainForm->pnlSystemMessage->Caption = "���ʨ�J���I ����!";
         MainForm->pnlToLoadPosition->Color = clRed;
         MainForm->pnlLoad->Color = clRed;

         // 2021 9 20a - chc Alarm
         if(MainForm->boolChuckPositionError == false) {
            MainForm->boolChuckPositionError = true;
            MainForm->SetSECSAlarm(41005,1,1,"Chuck Position Abnormal");
         }

      }
      // �����q���I
      else if(mode == 1) {
         MainForm->pnlSystemMessage->Caption = "Zero Point Move Fail!";
         MainForm->pnlToZeroPosition->Color = clRed;

         // 2023 8 3 - chc to 0
         //MainForm->pnlZeroPosition->Color = clRed;
         MainForm->pnl0Position->Color = clRed;
      }
      // �ɱ׶q���I
      else if(mode == 2) {
         MainForm->pnlSystemMessage->Caption = "Tilt Point Move Fail!";
         MainForm->pnlToTiltPosition->Color = clRed;
         MainForm->pnlTargetPosition->Color = clRed;
      }
      // Last�I
      else if(mode == 3) {
         MainForm->pnlSystemMessage->Caption = "Last Point Move Fail!";
         MainForm->pnlToLastPosition->Color = clRed;
      }
      // User�I
      else if(mode == 4) {
         MainForm->pnlSystemMessage->Caption = "User Point Move Fail!";
         MainForm->pnlToUserPosition->Color = clRed;
      }
      // Lens�I
      else if(mode == 5) {
         MainForm->pnlSystemMessage->Caption = "Lens Point Move Fail!";
         MainForm->pnlToLensPosition->Color = clRed;
      }
      // CCD
      else if(mode == 6) {
         MainForm->pnlSystemMessage->Caption = "CCD Point Move Fail!";
         MainForm->pnlToCCDPosition->Color = clRed;
      }
      // Center
      else if(mode == 7) {
         MainForm->pnlSystemMessage->Caption = "Center Point Move Fail!";
         MainForm->pnlToRealCenterPosition->Color = clRed;
      }
      // Measure
      else if(mode == 8) {
         MainForm->pnlSystemMessage->Caption = "Measure Point Move Fail!";
         MainForm->pnlToMeasurePosition->Color = clRed;
      }
   }
   else {
      boolxyzt = true;
      // ���I
      if(mode == 0) {
         MainForm->pnlSystemMessage->Caption = "Move to Load point Done.";
         MainForm->pnlToLoadPosition->Color = clLime;
         MainForm->pnlLoad->Color = clLime;

         // 2021 9 20a - chc Alarm
         if(MainForm->boolChuckPositionError == true) {
            MainForm->boolChuckPositionError = false;
            MainForm->SetSECSAlarm(41005,0,1,"Chuck Position Abnormal");
         }

      }
      // �����q���I
      else if(mode == 1) {
         MainForm->pnlSystemMessage->Caption = "Zero Point Move Completed";
         MainForm->pnlToZeroPosition->Color = clLime;

         // 2023 8 3 - chc to 0
         //MainForm->pnlZeroPosition->Color = clLime;
         MainForm->pnl0Position->Color = clLime;
      }
      // �ɱ׶q���I
      else if(mode == 2) {
         MainForm->pnlSystemMessage->Caption = "Tilt Point Move Completed";
         MainForm->pnlToTiltPosition->Color = clLime;
         MainForm->pnlTargetPosition->Color = clLime;
      }
      // Last�I
      else if(mode == 3) {
         MainForm->pnlSystemMessage->Caption = "Last Point Move Completed";
         MainForm->pnlToLastPosition->Color = clLime;
      }
      // Last�I
      else if(mode == 4) {
         MainForm->pnlSystemMessage->Caption = "User Point Move Completed";
         MainForm->pnlToUserPosition->Color = clLime;
      }
      // Lens�I
      else if(mode == 5) {
         MainForm->pnlSystemMessage->Caption = "Lens Point Move Completed";
         MainForm->pnlToLensPosition->Color = clLime;
      }
      // CCD
      else if(mode == 6) {
         MainForm->pnlSystemMessage->Caption = "CCD Point Move Completed";
         MainForm->pnlToCCDPosition->Color = clLime;
      }
      // Center
      else if(mode == 7) {
         MainForm->pnlSystemMessage->Caption = "Center Point Move Completed";
         MainForm->pnlToRealCenterPosition->Color = clLime;
      }
      // Measure
      else if(mode == 8) {
         MainForm->pnlSystemMessage->Caption = "Measure Point Move Completed";
         MainForm->pnlToMeasurePosition->Color = clLime;
      }
   }

   if(boolxyzt == true) {
      MainForm->WriteSystemLog("MoveToXYZT: ����.");
      MainForm->pnlAlarmMessage->Caption = "���ʧ���.";
   }
   else {
      MainForm->WriteSystemLog("MoveToXYZT: ����!");
      MainForm->pnlAlarmMessage->Caption = "���ʥ���!";
   }

   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Z_AXIS] = NO_MOVE;
   MainForm->iAxisMove[T_AXIS] = NO_MOVE;

   return;
}
//---------------------------------------------------------------------------
// 2021 4 20 - chc �̦��ǰ�X/Y/Z
// mode: 0-Area, 1-Dot, 2-Base1, 3-Base2
void __fastcall MoveToXYZ(int x,int y,int z, int mode)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno,orgt;
F64 pos;
F64 lowdistance;
bool booltmove = false;
bool boolxyz = false;

   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE ||
      MainForm->iAxisMove[Z_AXIS] != NO_MOVE || MainForm->iAxisMove[T_AXIS] != NO_MOVE) {
      if(MainForm->iAxisMove[X_AXIS] != NO_MOVE)
         MainForm->WriteSystemLog("MoveToXYZ: X������!");
      if(MainForm->iAxisMove[Y_AXIS] != NO_MOVE)
         MainForm->WriteSystemLog("MoveToXYZ: Y������!");
      if(MainForm->iAxisMove[Z_AXIS] != NO_MOVE)
         MainForm->WriteSystemLog("MoveToXYZ: Z������!");
      if(MainForm->iAxisMove[T_AXIS] != NO_MOVE)
         MainForm->WriteSystemLog("MoveToXYZ: T������!");
      return;
   }

   // Set Move State
   // 2021 6 9 - chc ���i�H�]�w!!
   //MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   //MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;
   //MainForm->iAxisMove[Z_AXIS] = FORWARD_MOVE;
   //MainForm->iAxisMove[T_AXIS] = FORWARD_MOVE;

   // T�w������: ���פj��0�׮�, �n�����0��
   // mode: 0 - wait, 1 - nowait
   int zero,cmd,over;
   double fcmd;
   // �����OLoadY
   zero = MainForm->edZeroT->Text.ToInt();
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      fcmd = ipos;
   }
   cmd = fcmd;
   // ���T��
   orgt = cmd;

   // Log
   MainForm->WriteSystemLog("MoveToXYZ: T��(cmd,����) " + IntToStr(cmd) + "," + IntToStr(zero));

   // �n�t100pulse�H�W�~�n��
   // 2021 4 2 - chc Z�w������ => T���������
   //if((cmd - zero) > 100) {
   F64 zpos;
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      zpos = ipos;
   }
   if((cmd - zero) > 100) {

      MainForm->pnlAlarmMessage->Caption = "T�����ʨ����...";
      MainForm->WriteSystemLog("MoveToXYZ: T�����ʨ����(cmd>zero)...");
      // ����T�b
      MainForm->WriteSystemLog("MoveToXYZ: T�����ʨ����, �}�l(����)..." + IntToStr(zero));
      MoveToT(zero);
      MainForm->WriteSystemLog("MoveToXYZ: T�����ʨ����, ����.");
      booltmove = true;
      // �O���ثeT��m
      if(MotionMode == MOTION_MODE_APS) {
         I32 ipos;
         APS_get_position(T_AXIS+StartAxisNo,&ipos);
         fcmd = ipos;
      }
      cmd = fcmd;
      MainForm->WriteSystemLog("MoveToXYZ: T�����ʨ����, ����. �зǦ�m,�ثe��m= " + IntToStr(zero) + "," + IntToStr(cmd));
   }

   // X
   MainForm->pnlAlarmMessage->Caption = "����X...";
   MainForm->WriteSystemLog("MoveToXYZ: ����X...");
   if(MoveToX(x) == false) {
      MainForm->pnlAlarmMessage->Caption = "X�b���ʥ���!";

      // 2021 4 24 - chc �n�]�w��NO_MOVE
      //return;
      goto end;
   }
   // Y
   MainForm->pnlAlarmMessage->Caption = "����Y...";
   MainForm->WriteSystemLog("MoveToXYZ: ����Y...");
   if(MoveToY(y) == false) {
      MainForm->pnlAlarmMessage->Caption = "Y�b���ʥ���!";

      // 2021 4 24 - chc �n�]�w��NO_MOVE
      //return;
      goto end;
   }

   // Z
   MainForm->WriteSystemLog("MoveToXYZ: ����Z...");
   MainForm->pnlAlarmMessage->Caption = "����Z...";

   // 2021 9 11 - chc �[�t: MOVE_WAIT
   //if(MoveToZ(z) == false) {
   if(MoveToZ(z,MOVE_WAIT) == false) {

      MainForm->pnlAlarmMessage->Caption = "Z�b���ʥ���!";

      // 2021 4 24 - chc �n�]�w��NO_MOVE
      //return;
      goto end;
   }

   // T
   // ������q���I, ��T > 0 ��, �n�L�Y�A�^�����
   if(booltmove == true) {
      MainForm->WriteSystemLog("MoveToXY: ����T...");
      MainForm->pnlAlarmMessage->Caption = "����T...";
      if(MoveToT(orgt) == false) {
         MainForm->pnlAlarmMessage->Caption = "T�b���ʥ���!";

         // 2021 4 24 - chc �n�]�w��NO_MOVE
         //return;
         goto end;
      }
      // �O���ثeT��m
      if(MotionMode == MOTION_MODE_APS) {
         I32 ipos;
         APS_get_position(T_AXIS+StartAxisNo,&ipos);
         fcmd = ipos;
      }
      cmd = fcmd;
      MainForm->WriteSystemLog("MoveToXYZ: ����T. �зǦ�m,�ثe��m= " + IntToStr(orgt) + "," + IntToStr(cmd));
   }

   Sleep(100);
   if(WaitMotionXYZDone(60000) == false) {
end:
      boolxyz = false;
      // Area
      if(mode == 0) {
         MainForm->pnlSystemMessage->Caption = "Moving to Area Fail!";
         MainForm->pnlToAreaPosition->Color = clRed;
      }
      // Dot
      else if(mode == 1) {
         MainForm->pnlSystemMessage->Caption = "Measure Dot Move Fail!";
         MainForm->pnlToDotPosition->Color = clRed;
      }
      // Base1
      else if(mode == 2) {
         MainForm->pnlSystemMessage->Caption = "Moving to Base1 Fail!";
         MainForm->pnlToBase1Position->Color = clRed;
      }
      // Base2
      else if(mode == 3) {
         MainForm->pnlSystemMessage->Caption = "Moving to Base2 Fail!";
         MainForm->pnlToBase2Position->Color = clRed;
      }
   }
   else {
      boolxyz = true;
      // Area
      if(mode == 0) {
         MainForm->pnlSystemMessage->Caption = "Moving to Area Completed";
         MainForm->pnlToAreaPosition->Color = clLime;
      }
      // Dot
      else if(mode == 1) {
         MainForm->pnlSystemMessage->Caption = "Measure Dot Move Completed";
         MainForm->pnlToDotPosition->Color = clLime;
      }
      // Base1
      else if(mode == 2) {
         MainForm->pnlSystemMessage->Caption = "Moving to Base1 Completed!";
         MainForm->pnlToBase1Position->Color = clLime;
      }
      // Base2
      else if(mode == 3) {
         MainForm->pnlSystemMessage->Caption = "Moving to Base2 Completed!";
         MainForm->pnlToBase2Position->Color = clLime;
      }
   }

   if(boolxyz == true) {
      MainForm->WriteSystemLog("MoveToXYZ: ����.");
      MainForm->pnlAlarmMessage->Caption = "���ʧ���.";
   }

   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Z_AXIS] = NO_MOVE;
   MainForm->iAxisMove[T_AXIS] = NO_MOVE;

   return;
}
//---------------------------------------------------------------------------
// 2020 3 6 - chc Z�babsolute����
// 2021 9 11 - chc �[�t: MOVE_WAIT
//bool __fastcall MoveToZ(int position)
bool __fastcall MoveToZ(int position, int mode)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   axisno = Z_AXIS;

   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToZ: Z in moving!");
      return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // 2021 5 8 - chc Z Limit
   // 2023 8 4 - chc Check z Limit : CheckZLimit(axisno,&pos)
   //int limit = MainForm->GetZLimit();
   //if(position > limit)
   //   position = limit;
   CheckZLimit(axisno,&position);

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   pos = position;

   // Home���n��HomeSpeed
   // 2021 4 30 - chc ����
   //if(MainForm->boolHomeDone == false)
   //   maxvel = homevel;

   int ispeed;
   ispeed = maxvel;
   MainForm->WriteSystemLog("MoveToZ: speed= " + IntToStr(ispeed));

   // Absolute move
   if(MotionMode == MOTION_MODE_APS)
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);

   // timeout from 5sec to 30sec
   // 2021 9 11 - chc �[�t: MOVE_WAIT
   if(mode == MOVE_WAIT) {

      if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
         // �O���U�b�O�_�B�@��
         MainForm->iAxisMove[axisno] = NO_MOVE;
         MainForm->WriteSystemLog("MoveToZ: Z Timeout!");
         return false;
      }

      // �n����e����: �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
   }
   return true;
}
//---------------------------------------------------------------------------
// ret: true or false
bool __fastcall GetNELStatus(int axisno)
{

   if(MotionMode == MOTION_MODE_APS) {
      I32 io_sts;
      io_sts = APS_motion_io_status(axisno+StartAxisNo);
      // NEL(Low/Inverse) - 2
      if((io_sts & 0x0004) != 0) {
         return true;
      }
      else {
         return false;
      }
   }
   return false;
}
//---------------------------------------------------------------------------
// ret: ture or false
bool __fastcall GetMotionDoneStatus(int axisno)
{
I16 Motion_status;

   //if(MotionMode == MOTION_MODE_APS) {
      I32 mstatus;
      mstatus = APS_motion_status(axisno+StartAxisNo);
      if((mstatus & 0x01) != 0)
         return true;
      else
         return false;
   //}
}
//---------------------------------------------------------------------------
// 2021 4 15 - chc �����w�b�~����
void __fastcall StopOtherAxis(int axisno)
{
F64 tdec;

   for(int i=0 ; i<MAX_AXIS_NO ; i++) {
      if(i != axisno) {
         if(MotionMode == MOTION_MODE_APS) {
            APS_stop_move(i+StartAxisNo);
         }
      }
   }
}
//---------------------------------------------------------------------------
// 2021 4 21 - chc �ߧY����
void __fastcall StopOneAxis(int axisno)
{

   F64 tdec = GetTdec(axisno);

   // 2021 4 15 - chc APS
   if(MotionMode == MOTION_MODE_APS)
      APS_stop_move(axisno+StartAxisNo);

   // 2020 4 20 - chc �n�]��0, �_�htm50msTimer�|����ʧ@!
   MainForm->MoveDirection = 0;
}
//---------------------------------------------------------------------------
// 2021 4 25 - chc Relative Move
void __fastcall DoRelativeMove(int axisno, int offset)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
I16 ret;
F64 lowdistance;

   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   pos = offset;

   // �O���U�b�O�_�B�@��
   if(pos > 0)
      MainForm->iAxisMove[axisno] = FORWARD_MOVE;
   else
      MainForm->iAxisMove[axisno] = BACKWARD_MOVE;

   // Relative move
   ret = RelativeMove(axisno,pos,startvel,maxvel,tacc,tdec);

}
//---------------------------------------------------------------------------
// 2021 4 29 - chc W Set
void __fastcall SetWPosition(int no)
{
F64 fcmd;
TLMDEdit *edit;
I16 axisno;
I32 cmd;

   axisno = W_AXIS;
   edit = (TLMDEdit *)(MainForm->FindComponent("edWPosition" + IntToStr(no)));

   if(MotionMode == MOTION_MODE_APS){
      APS_get_position(axisno+StartAxisNo,&cmd);
   }
   edit->Text = IntToStr(cmd);
}
//---------------------------------------------------------------------------
// 2021 4 29 - chc ��W�I��, W��׬�: 1um
// 1 - 19
void __fastcall ToWPositionFun(int no)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
TLMDEdit *edit;
I16 ret;
I32 posi,wpos;
I16 axisno;

int retry;
int tolerance;
int looptry = 0;
F64 fpos;
F64 lowdistance;

   tolerance = 40;
   MainForm->pcSystem->Enabled = false;

   // 2021 7 19 - chc ���runabort
   MainForm->WriteSystemLog("�����@�~����14.");

   MainForm->pnlToWStatus->Color = clSilver;
   edit = (TLMDEdit *)(MainForm->FindComponent("edWPosition" + IntToStr(no)));
   posi = edit->Text.ToInt();
   fpos = posi;

   MainForm->pnlSystemMessage->Caption = "W-Axis moving: " + IntToStr(no) + "...";

   // 2021 8 10 - chc Log
   MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);

   // ����Absolute Position
   axisno = W_AXIS;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
loopagain:
   ret = AbsoluteMove(axisno,fpos,startvel,maxvel,tacc,tdec);
   if(ret == ERR_NoError)
      MainForm->WriteSystemLog(">WAxis Move done.");
   else {
      MainForm->WriteSystemLog(">WAxis Move fail!");
      MainForm->pnlToWStatus->Color = clRed;
      goto end;
   }
   // check done?
   retry = 0;
   DelayTimeM1(200);
recheck:
   // �A���ֹ�RX Position�O�_���T
   if(MotionMode == MOTION_MODE_APS) {
      APS_get_position(axisno+StartAxisNo,&wpos);
   }
   if(abs(posi - wpos) > tolerance) {
      MainForm->pnlSystemMessage->Caption = "W-Axis move failed- incorrect location! now(W)=" + IntToStr(wpos) + ", set(W)=" + IntToStr(posi) + ", test times:" + IntToStr(retry);
      MainForm->pnlToWStatus->Color = clRed;
      DelayTimeM1(100);
      retry++;
      if(retry < 30)
         goto recheck;
      looptry++;
      if(looptry < 2) {
         MainForm->WriteSystemLog("W���ʦA�U�@���R�O.");
         goto loopagain;
      }
   }
   else {
      MainForm->pnlSystemMessage->Caption = "W-Axis move succ. now(W)= " + IntToStr(wpos) + ", set(W)=" + IntToStr(posi) + ", test times:" + IntToStr(retry);
      MainForm->pnlToWStatus->Color = clLime;
   }

end:
   MainForm->pcSystem->Enabled = true;

   // 2021 8 10 - chc Log
   MainForm->WriteSystemLog("W�b�I�첾�ʧ���");

}
//---------------------------------------------------------------------------
// 2021 4 29 - chc L�babsolute����
// 2021 9 11 - chc �O�_�[�t
//bool __fastcall MoveToL(int position)
bool __fastcall MoveToL(int position, bool boolspeedup)

{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   axisno = L_AXIS;

   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToL: L in moving!");
      return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   pos = position;

   // 2021 9 11 - chc �O�_�[�t
   // 2023 8 21 - chc LiftPin���n���t: false(1000), ���t��5000
   //if(boolspeedup == true)
   //   maxvel += (maxvel*2/3);
   if(boolspeedup == false)
      maxvel = maxvel / 5;

   // Home���n��HomeSpeed
   // 2021 4 29 - chc �j��̰��t
   //if(MainForm->boolHomeDone == false)
   //   maxvel = homevel;

   // Absolute move
   if(MotionMode == MOTION_MODE_APS)
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);

   // timeout from 5sec to 30sec
   if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
      // �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
      MainForm->WriteSystemLog("MoveToL: L Timeout!");
      return false;
   }

   // �n����e����: �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2021 5 3 - chc Center Position
void __fastcall SetRealCenterPosition()
{
I32 cmd;
F64 fcmd;

   // APS
   if(MotionMode == MOTION_MODE_APS) {
      I32 ipos;
      APS_get_position(X_AXIS+StartAxisNo,&ipos);
      MainForm->edRealCenterX->Text = IntToStr(ipos);
      APS_get_position(Y_AXIS+StartAxisNo,&ipos);
      MainForm->edRealCenterY->Text = IntToStr(ipos);
      APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      MainForm->edRealCenterZ->Text = IntToStr(ipos);
      APS_get_position(T_AXIS+StartAxisNo,&ipos);
      MainForm->edRealCenterT->Text = IntToStr(ipos);
   }
}
//---------------------------------------------------------------------------
// 2021 5 3 - chc Center Position
void __fastcall ToRealCenterPosition()
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno;
F64 pos,x,y,z,t;
F64 lowdistance;
bool flag = true;

   MainForm->pnlToRealCenterPosition->Color = clSilver;
   // �n��Edit����
   x = MainForm->edRealCenterX->Text.ToInt();
   y = MainForm->edRealCenterY->Text.ToInt();
   z = MainForm->edRealCenterZ->Text.ToInt();
   t = MainForm->edRealCenterT->Text.ToInt();
   // �̦��ǰ�X/Y/Z
   MoveToXYZT(x,y,z,t,7);
   return;
}
//---------------------------------------------------------------------------
// 2021 5 5 - chc W�babsolute����
bool __fastcall MoveToW(int position)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit,pos;
int axisno;
I16 ret;
F64 lowdistance;

   axisno = W_AXIS;

   // �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToW: W in moving!");
      return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   pos = position;

   // Absolute move
   if(MotionMode == MOTION_MODE_APS)
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);

   // timeout from 5sec to 30sec
   if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
      // �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
      MainForm->WriteSystemLog("MoveToW: W Timeout!");
      return false;
   }

   // �n����e��: �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2023 8 3 - chc 12Edge
void __fastcall Set12EdgePos(int no)
{

   I32 iposx,iposy,iposz;
   APS_get_position(X_AXIS+StartAxisNo,&iposx);
   APS_get_position(Y_AXIS+StartAxisNo,&iposy);
   APS_get_position(Z_AXIS+StartAxisNo,&iposz);
   if(no == 1) {
      MainForm->ed12EdgeX1->Text = IntToStr(iposx);
      MainForm->ed12EdgeY1->Text = IntToStr(iposy);
      MainForm->ed12EdgeZ1->Text = IntToStr(iposz);
   }
   else if(no == 2) {
      MainForm->ed12EdgeX2->Text = IntToStr(iposx);
      MainForm->ed12EdgeY2->Text = IntToStr(iposy);
      MainForm->ed12EdgeZ2->Text = IntToStr(iposz);
   }
   else if(no == 3) {
      MainForm->ed12EdgeX3->Text = IntToStr(iposx);
      MainForm->ed12EdgeY3->Text = IntToStr(iposy);
      MainForm->ed12EdgeZ3->Text = IntToStr(iposz);
   }
}
//---------------------------------------------------------------------------
// 2023 8 3 - chc 8Edge
void __fastcall Set8EdgePos(int no)
{

   I32 iposx,iposy,iposz;
   APS_get_position(X_AXIS+StartAxisNo,&iposx);
   APS_get_position(Y_AXIS+StartAxisNo,&iposy);
   APS_get_position(Z_AXIS+StartAxisNo,&iposz);
   if(no == 1) {
      MainForm->ed8EdgeX1->Text = IntToStr(iposx);
      MainForm->ed8EdgeY1->Text = IntToStr(iposy);
      MainForm->ed8EdgeZ1->Text = IntToStr(iposz);
   }
   else if(no == 2) {
      MainForm->ed8EdgeX2->Text = IntToStr(iposx);
      MainForm->ed8EdgeY2->Text = IntToStr(iposy);
      MainForm->ed8EdgeZ2->Text = IntToStr(iposz);
   }
   else if(no == 3) {
      MainForm->ed8EdgeX3->Text = IntToStr(iposx);
      MainForm->ed8EdgeY3->Text = IntToStr(iposy);
      MainForm->ed8EdgeZ3->Text = IntToStr(iposz);
   }
}
//---------------------------------------------------------------------------
// 2023 8 3 - chc 12Edge
void __fastcall To12EdgePos(int no)
{
F64 tacc,tdec;
F64 dist,startvel,maxvel,homevel,reviewvel,uplimit,lowdistance,ret;
int axisno;
int pos,x,y,z,t;
TPanel *panel;

   t = 0;
   panel = (TPanel *)(MainForm->FindComponent("pnlTo12Edge" + IntToStr(no)));
   if(no == 1) {
      // �n��Edit����
      x = MainForm->ed12EdgeX1->Text.ToInt();
      y = MainForm->ed12EdgeY1->Text.ToInt();
      z = MainForm->ed12EdgeZ1->Text.ToInt();
   }
   else if(no == 2) {
      // �n��Edit����
      x = MainForm->ed12EdgeX2->Text.ToInt();
      y = MainForm->ed12EdgeY2->Text.ToInt();
      z = MainForm->ed12EdgeZ2->Text.ToInt();
   }
   else if(no == 3) {
      // �n��Edit����
      x = MainForm->ed12EdgeX3->Text.ToInt();
      y = MainForm->ed12EdgeY3->Text.ToInt();
      z = MainForm->ed12EdgeZ3->Text.ToInt();
   }
   panel->Color = clSilver;

   // �ϥγ̰��t: rgSpeed
   int oldspeed;
   oldspeed = MainForm->rgSpeed->ItemIndex;
   MainForm->rgSpeed->ItemIndex = JOG_HIGH_SPEED;

   // Check Move State
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE ||
      MainForm->iAxisMove[Z_AXIS] != NO_MOVE) {
      MainForm->WriteSystemLog("Motion Busy!");
      return;
   }

   // 2023 8 4 - chc �ˬdZ
   CheckZLimit(Z_AXIS,&z);

   // Set Move State
   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Z_AXIS] = FORWARD_MOVE;

   // ��XY�AZT
   // XY
   axisno = X_AXIS;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   ret = APS_absolute_move(axisno+StartAxisNo,x,maxvel);
   MainForm->WriteSystemLog("To12Edge(x) = " + IntToStr(x));

   axisno = Y_AXIS;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   ret = APS_absolute_move(axisno+StartAxisNo,y,maxvel);
   MainForm->WriteSystemLog("To12Edge(y) = " + IntToStr(y));

   // ����500ms
   Sleep(500);
   // ��WaitMotionXYDone(ms,x,y)
   if(WaitMotionXYDone(30000,x,y) == false) {
      MainForm->pnlSystemMessage->Caption = "12Edge move failed!";
      panel->Color = clRed;
   }

   // Z
   // 2023 3 14 - chc ������Z
   /*
   axisno = Z_AXIS;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   ret = APS_absolute_move(axisno+StartAxisNo,z,maxvel);
   MainForm->WriteSystemLog("To12Edge(z) = " + IntToStr(z));
   WaitMotionDone(axisno,10000);

   MainForm->WriteSystemLog("To12Edge: ���ݧ���...");
   if(WaitMotionXYZTDone(30000) == false) {
      MainForm->pnlSystemMessage->Caption = "12Edge�I���ʥ���!";
      panel->Color = clRed;
      MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
   }
   else {
      // �ˬdZ?�~�t�n�b2000�H��
      WaitZFinish(z);
      MainForm->pnlSystemMessage->Caption = "12Edge�I���ʧ���(x,y,z): " + IntToStr(x) + "," + IntToStr(y) + "," + IntToStr(z);
      panel->Color = clLime;
      MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
   }
   */

   // Reset Move State
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Z_AXIS] = NO_MOVE;

   // �ϥγ̰��t: rgSpeed
   MainForm->rgSpeed->ItemIndex = oldspeed;
   MainForm->WriteSystemLog("12Edge�I����: Leave.");
}
//---------------------------------------------------------------------------
// 2023 3 14 - chc 8Edge
void __fastcall To8EdgePos(int no)
{
F64 tacc,tdec;
F64 dist,startvel,maxvel,homevel,reviewvel,uplimit,lowdistance,ret;
int axisno;
int pos,x,y,z,t;
TPanel *panel;

   t = 0;
   panel = (TPanel *)(MainForm->FindComponent("pnlTo8Edge" + IntToStr(no)));
   if(no == 1) {
      // �n��Edit����
      x = MainForm->ed8EdgeX1->Text.ToInt();
      y = MainForm->ed8EdgeY1->Text.ToInt();
      z = MainForm->ed8EdgeZ1->Text.ToInt();
   }
   else if(no == 2) {
      // �n��Edit����
      x = MainForm->ed8EdgeX2->Text.ToInt();
      y = MainForm->ed8EdgeY2->Text.ToInt();
      z = MainForm->ed8EdgeZ2->Text.ToInt();
   }
   else if(no == 3) {
      // �n��Edit����
      x = MainForm->ed8EdgeX3->Text.ToInt();
      y = MainForm->ed8EdgeY3->Text.ToInt();
      z = MainForm->ed8EdgeZ3->Text.ToInt();
   }
   panel->Color = clSilver;

   // �ϥγ̰��t: rgSpeed
   int oldspeed;
   oldspeed = MainForm->rgSpeed->ItemIndex;
   MainForm->rgSpeed->ItemIndex = JOG_HIGH_SPEED;

   // Check Move State
   if(MainForm->iAxisMove[X_AXIS] != NO_MOVE || MainForm->iAxisMove[Y_AXIS] != NO_MOVE ||
      MainForm->iAxisMove[Z_AXIS] != NO_MOVE)
      return;

   // 2023 8 4 - chc �ˬdZ
   CheckZLimit(Z_AXIS,&z);

   // Set Move State
   MainForm->iAxisMove[X_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Y_AXIS] = FORWARD_MOVE;
   MainForm->iAxisMove[Z_AXIS] = FORWARD_MOVE;

   // ��XY�AZT
   // XY
   axisno = X_AXIS;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   ret = APS_absolute_move(axisno+StartAxisNo,x,maxvel);
   MainForm->WriteSystemLog("To8Edge(x) = " + IntToStr(x));

   axisno = Y_AXIS;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);
   ret = APS_absolute_move(axisno+StartAxisNo,y,maxvel);
   MainForm->WriteSystemLog("To8Edge(y) = " + IntToStr(y));

   // ����500ms
   Sleep(500);
   if(WaitMotionXYDone(30000,x,y) == false) {
      MainForm->pnlSystemMessage->Caption = "8Edge move failed!";
      panel->Color = clRed;
   }

   // Z
   // 2023 3 14 - chc ������Z
   /*
   axisno = Z_AXIS;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   ret = APS_absolute_move(axisno+StartAxisNo,z,maxvel);
   MainForm->WriteSystemLog("To8Edge(z) = " + IntToStr(z));
   WaitMotionDone(axisno,10000);

   MainForm->WriteSystemLog("To8Edge: ���ݧ���...");
   if(WaitMotionXYZTDone(30000) == false) {
      MainForm->pnlSystemMessage->Caption = "8Edge�I���ʥ���!";
      panel->Color = clRed;
      MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
   }
   else {
      // �ˬdZ?�~�t�n�b2000�H��
      WaitZFinish(z);
      MainForm->pnlSystemMessage->Caption = "8Edge�I���ʧ���(x,y,z): " + IntToStr(x) + "," + IntToStr(y) + "," + IntToStr(z);
      panel->Color = clLime;
      MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
   }
   */

   // Reset Move State
   MainForm->iAxisMove[X_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Y_AXIS] = NO_MOVE;
   MainForm->iAxisMove[Z_AXIS] = NO_MOVE;

   // �ϥγ̰��t: rgSpeed
   MainForm->rgSpeed->ItemIndex = oldspeed;
   MainForm->WriteSystemLog("8Edge�I����: Leave.");
}
//---------------------------------------------------------------------------
// 2023 8 4 - chc Check z Limit
// for Z / Z1(T)
void __fastcall CheckZLimit(int axisno, int *position)
{
int pos;

   pos = *position;

   // ZLimmit
   if(axisno == Z_AXIS) {
      int limit = MainForm->GetZLimit();
      if(pos > limit)
         pos = limit;
   }

   // Z1Limit
   else if(axisno == T_AXIS) {
      int z1limit = MainForm->edZ1Limit->Text.ToInt();
      if(pos > z1limit)
         pos = z1limit;
   }

   // Z+Z1 Limit
   /*
   if(axisno == T_AXIS || axisno == Z_AXIS) {
      int zzlimit = MainForm->edZZ1Limit->Text.ToInt();
      int zvalue;
      I32 ipos;
      if(axisno == Z_AXIS)
         APS_get_position(T_AXIS+StartAxisNo,&ipos);
      else
         APS_get_position(Z_AXIS+StartAxisNo,&ipos);
      zvalue = ipos;
      if((pos + zvalue) > zz1lime) {
         pos = zz1limit - zvalue;
      }
   }
   */

   *position = pos;

}
//---------------------------------------------------------------------------
// 2023 8 4 - chc Wait Motion X/Y done
bool __fastcall WaitMotionXYDone(int ms, int x, int y)
{
I32 cmd;
I16 mstatusx,mstatusy;
int counter;
int max,axisno;
// ���INP or Position
I32 px,py;

   counter = 0;
   max = ms / 10;
   DelayTimeM4(10);
   MainForm->WriteSystemLog("��WaitMotionXYDone...");

   while(1) {
      mstatusx = 0;
      mstatusy = 0;
      I32 done;
      done = APS_motion_status(X_AXIS+StartAxisNo);
      // ��bit 0 : ������0(Done)
      if((done & 0x01) == 0)
         mstatusx = 1;

      done = APS_motion_status(Y_AXIS+StartAxisNo);
      // ��bit 0 : ������0(Done)
      if((done & 0x01) == 0)
         mstatusy = 1;

      if(mstatusx == 0 && mstatusy == 0) {
         MainForm->WriteSystemLog("��WaitMotionXYDone, Done.");
         break;
      }
      else {
         // ���INP or Position
         if(MainForm->pnlINPX->Color != clSilver && MainForm->pnlINPY->Color != clSilver) {
            MainForm->WriteSystemLog("��WaitMotionXYDone, INP Done.");
            break;
         }
         // Position: TAZMO(VisEra) 0.2um/0.2um
         APS_get_position(X_AXIS+StartAxisNo,&px);
         APS_get_position(Y_AXIS+StartAxisNo,&py);
         // 40um
         if(abs(px - x) < 200 && abs(py - y) < 200) {
            MainForm->WriteSystemLog("��WaitMotionXYDone, Position Done.");
            break;
         }

         DelayTimeM4(10);
         counter++;
         if(counter > max) {
            MainForm->pnlSystemMessage->Caption = "Do WaitMotionXYDone, Timeout!";
            MainForm->WriteSystemLog(MainForm->pnlSystemMessage->Caption);
            return false;
         }
      }
   }
   MainForm->WriteSystemLog("��WaitMotionXYDone.");
   return true;
}
//---------------------------------------------------------------------------
// 2013 8 6 - chc A1�babsolute����
bool __fastcall MoveToZ1(int position, int speed)
{
F64 dist,startvel,maxvel,tacc,tdec,homevel,reviewvel,uplimit;
int axisno,pos;
I16 ret;
F64 lowdistance;

   axisno = Z1_AXIS;
   pos = position;

   // Check z Limit : CheckZLimit(axisno,&pos)
   CheckZLimit(axisno,&pos);

   AnsiString msg;
   msg.sprintf("MoveToZ1: Move���ʦ�m = %d,%d",position,pos);
   MainForm->WriteSystemLog(msg);

   // �O���U�b�O�_�B�@��
   if(MainForm->iAxisMove[axisno] != NO_MOVE) {
      MainForm->WriteSystemLog("MoveToZ1: Z1 in moving!");
      return false;
   }
   MainForm->iAxisMove[axisno] = FORWARD_MOVE;

   // �����b�ƥH���oStartVel/MaxVel
   MainForm->combAxis->ItemIndex = axisno;
   GetAxisData(axisno,&dist,&startvel,&maxvel,&tacc,&tdec,&homevel,&reviewvel,&uplimit,&lowdistance);

   // ���wSpeed
   maxvel = speed;
   msg.sprintf("MoveToZ1: Move���ʦ�m(�A�T�{) = %d,%d",position,pos);
   MainForm->WriteSystemLog(msg);

   if(MotionMode == MOTION_MODE_APS)
      ret = APS_absolute_move(axisno+StartAxisNo,(int)pos,(int)maxvel);

   MainForm->WriteSystemLog("Wait(40sec)...");
   // timeout from 5sec to 30sec : MOTION_TIMEOUT
   if(WaitMotionDone(axisno, MOTION_TIMEOUT) == false) {
      // �O���U�b�O�_�B�@��
      MainForm->iAxisMove[axisno] = NO_MOVE;
      MainForm->WriteSystemLog("MoveToZ1: T Timeout!");
      return false;
   }

   MainForm->WriteSystemLog("MoveToZ1: Move����, �ˬd��m...");
   // T�����
   double fcmd;
   int cmd,cnd,max;
   cnd = 0;
   max = 200;
   while(1) {
      if(MotionMode == MOTION_MODE_APS) {
         I32 ipos;
         APS_get_position(axisno+StartAxisNo,&ipos);
         cmd = ipos;
      }
      // MoveToT()InPosition��100um�H���N�i�H(��10um)
      if(abs(position - cmd) < 100) {
         MainForm->WriteSystemLog("MoveToZ1: ����(pos,cmd) = " + IntToStr(position) + "," + IntToStr(cmd));
         break;
      }

      Sleep(9);
      Application->ProcessMessages();
      cnd++;
      if(cnd > max) {
         MainForm->WriteSystemLog("MoveToZ1: Timeout(pos,cmd) = " + IntToStr(position) + "," + IntToStr(cmd));
         break;
      }
   }

   // �O���U�b�O�_�B�@��
   MainForm->iAxisMove[axisno] = NO_MOVE;

   return true;
}
//---------------------------------------------------------------------------
// 2023 8 6 - chc Trigger Parameter
//Motion(TRG CH0)
//  Trigger Parameter
//    Compare Source: Command Counter                           ok
//    Compare Enable: =(Counting Down)                          ok
//    Trigger Source: CMP 0                                     ok
//    Trigger Pulse Width: 10(?)                                ok, => 200ns(�C�@�Ӭ�20ns)
//    Trigger Config: Pulse+Not Inverse                         ok
//    Compare Type: Linear                                      ok
//  Compare Setting
//    Linear Compare 0: LCMP0
//    StartPoint: 100
//    RepeatTimes: 100
//    Interval: 14
// BoardID=1, BoardMNET=0, MNET_BUS=1, MOD_No=0
bool __fastcall SetTriggerParameter(int start, int loop, int interval, bool direction)
{
// Module No
I32 MOD_No = 0;

   // Log Message
   MainForm->WriteSystemLog(">>Trigger: Set parameters...");

   //Setting Compare source 0 is from position counter(Encoder).
   // CMP source 0~3�O���b�d����0~3�b(�]��MNET-4XMO-C �|�Ӷb���i�H�ϥ�Trigger�\��) - �ثe��X�b��Trigger
   // 0-Command, 1-Encoder(Position) => Encoder
   //#define TG_CMP0_SRC             (0x00)
   //#define TG_CMP1_SRC             (0x01)
   //#define TG_CMP2_SRC             (0x02)
   //#define TG_CMP3_SRC             (0x03)
   // 0 - Command counter
   // 1 - Position counter
   // => �n��command or position ???
   if(MainForm->rgSource->ItemIndex == 0)
      APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_CMP0_SRC     ,0);
   else
      APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_CMP0_SRC     ,1);

   //Setting CMP0 Compare type is Linear.
   // �]�w�nCMP 0~3�n�����ϥΪ�Ĳ�o����覡��Linear CMP Trigger or Table CMP Trigger
   //#define TG_CMP0_TYPE            (0x08)
   //#define TG_CMP1_TYPE            (0x09)
   //#define TG_CMP2_TYPE            (0x0A)
   //#define TG_CMP3_TYPE            (0x0B)
   // 0-Table, 1-Linear => Table
   APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_CMP0_TYPE    ,1);
   //Trigger Width is 100ns
   // �]�wCMP��Trigger�T���e�סA�e�ת��p��覡��Pulse Width = ( N+ 5) * 10 ns�A N�O�n��J���ѼơA�W�����d��N=5(default)�A�ҥHTrigger Width��100ns
   // �e�׷|�v�T��Trigger���t�סA��s����Ĳ�o���t�׭n�V�֮ɡA�e�׭n�V�p�C
   // Width

   // 2021 7 28 - chc ��CMP0 : 0x00 ~ 0x1F
   // Bit 0 - CMP0
   // Bit 1 - CMP1
   // Bit 2 - CMP2
   // Bit 3 - CMP3
   // Bit 4 - CMPH
   //#define TG_TRG0_SRC           (0x10)
   //#define TG_TRG1_SRC           (0x11)
   //#define TG_TRG2_SRC           (0x12)
   //#define TG_TRG3_SRC           (0x13)
   APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_TRG0_SRC    ,1);

   // 40 => nnnn(ns), �H�ѼƳB�z, 20ns���@�ӳ��
   //#define TG_TRG0_PWD           (0x14)
   //#define TG_TRG1_PWD           (0x15)
   //#define TG_TRG2_PWD           (0x16)
   //#define TG_TRG3_PWD           (0x17)
   int nsno;
   nsno = MainForm->edTriggerTime->Text.ToInt();                                          // 200ns

   // (N+5)*10ns: DFK(1150ns-105), Vieworks(150ns-10)
   //nsno /= 20;                                                                  // 10
   nsno = (nsno / 10) - 5;
   APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_TRG0_PWD     ,nsno);

   // 0- Pulse ( not Inverse )
   // 1- Pulse ( Inverse )
   // 2- Toggle ( not Inverse )
   // 3- Toggle ( Inverse )
   // => Pulse(Not Inverse; 0)
   // => �����|�y������On
   //Bit 0: Pulse logic inverse. Not Inverse (0) / Inverse (1)
   // Bit 1~2: pulse (0) / toggle (1) / ByPass (2) / Disable (3)
   // Bit 3~31: Reserved (set 0)
   //APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_TRG0_CFG     ,0);
   // 2021 7 28 - chc ��Pulse, NotInverse
   APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_TRG0_CFG     ,0);

   //Set Linear Data
   // �]�wLinear CMP������I��(�T�w�����m)�A�䤤LCmpCh�Ѽƭn��J�O�ĴX��channel(0~3)�AStartPoint(�n������_�l��m)�A
   // RepeatTime(Trigger�ƶq)�AInterval(�C�h��Pulse�o�eTrigger)�C
   //APS_set_field_bus_trigger_table(BoardMNET, MNET_BUS,MOD_No, channel, table, intno);

   // Ch0(LCMP0)
   APS_set_field_bus_trigger_linear(BoardMNET, MNET_BUS, MOD_No, 0, start, loop, interval); //Set CMP0 linear compare algorithm.
   // Start point = 1000, RepeatTimes = 100000, Interval = 100.

   // 2-While counting up
   // Enable
   // TG_CMP0_EN
   // 0 - Disable
   // Other: Enable.
   //   1:data = cmp counter (regardless of counting direction)
   //   2: data = cmp counter (while counting up)
   //   3: data = cmp counter (while counting down)
   //   4: data > cmp counter
   //   5: data < cmp counter
   // �j��p: true(3)
   // 2021 7 28 - chc ��1
   //#define TG_CMP0_EN              (0x04)
   //#define TG_CMP1_EN              (0x05)
   //#define TG_CMP2_EN              (0x06)
   //#define TG_CMP3_EN              (0x07)
   //Enable CMP0
   //APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, 0x04, 1 );      //Enable CMP0
   if(MainForm->rgCompareMode->ItemIndex == 1) {
      APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_CMP0_EN      ,1);
   }
   else {
      // Down to Up
      if(direction == true)
         APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_CMP0_EN      ,3);
      // Up to Down
      else
         APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, (I32)TG_CMP0_EN      ,2);
   }
   // Log Message
   MainForm->WriteSystemLog(">>Trigger: Set Position(start,repeat) and Enable: " + IntToStr(start) + "," + IntToStr(loop));

   //---------------------------------------------------------------------------

   // Table�d��
   //I16 ret = 0;
   //I32 axis;
   //I32 data[4];
   //axis = rgAxisSel->ItemIndex;
   //ret = APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, 1, TG_CMP0_SRC+axis,  cboCMPSource->ItemIndex);
   //ret = APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, 1, TG_CMP0_EN+axis,   cboCMPEnable->ItemIndex);
   //ret = APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, 1, TG_CMP0_TYPE+axis, cboCMPType->ItemIndex);
   //ret = APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, 1, TG_TRG0_CFG+axis,  cboTriConfig->ItemIndex);
   //ret = APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, 1, TG_TRG0_PWD+axis,  edPulseWidth->Text.ToInt());
   //data[0] = ledCMPPoint->Text.ToInt();
   //ret = APS_set_field_bus_trigger_table(BoardMNET, MNET_BUS, 1, axis, data, 1);

   return true;
}

/*
Below example is for MNET-4XMO-C, HSL-4XMO:
I32 BoardId = 0, Bus_No = 1, Mod_No = 0
APS_set_field_bus_trigger_param(BoardId, Bus_No, Mod_No, 0x0, 1 );      //Set CMP0 as linear type
APS_set_field_bus_trigger_param(BoardId, Bus_No, Mod_No, 0x10, 1 );     //Set CMP0 as TRG0��s source
APS_set_field_bus_trigger_linear(BoardId, Bus_No, Mod_No, 0, 1000, 100000, 100 ); //Set CMP0 linear compare algorithm.
// Start point = 1000, RepeatTimes = 100000, Interval = 100.
APS_set_field_bus_trigger_param(BoardId, Bus_No, Mod_No, 0x04, 1 );     //Enable CMP0
// Trigger operation�K
//When finish the trigger operation.
APS_set_field_bus_trigger_param(BoardId, Bus_No, Mod_No, 0x04, 0 );     //Disable CMP0

//�O�i�d
I32 BoardId = 0;
APS_set_trigger_param(BoardId, 0x0, 0 );                                //Set linear compare source
APS_set_trigger_param(BoardId, 0x10, 0 );                               //Set LCMP0 as TRG0��s source
APS_set_trigger_linear(BoardId, 0, 100, 49999, 10 );                    //Set LCMP0 linear compare algorithm.675
// Start point = 100, RepeatTimes = 49999, Interval = 10.
APS_set_trigger_param(BoardId, 0x04, 1 );                               //Enable LCMP0
// Trigger operation.
APS_set_trigger_param( 0, 0x04, 0 );                                    //Disable LCMP0*/

//---------------------------------------------------------------------------
// 2023 8 6 - chc Stop Trigger
//#define TG_CMP0_EN              (0x04)
//#define TG_CMP1_EN              (0x05)
//#define TG_CMP2_EN              (0x06)
//#define TG_CMP3_EN              (0x07)
bool __fastcall StopTrigger()
{
// Module No
I32 MOD_No =0;

   // Trigger operation�K
   //When finish the trigger operation.
   //APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, 0x04, 0 );          //Disable CMP0
   APS_set_field_bus_trigger_param(BoardMNET, MNET_BUS, MOD_No, TG_CMP0_EN, 0 );      //Disable CMP0
}
//---------------------------------------------------------------------------


#pragma package(smart_init)
