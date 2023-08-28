//---------------------------------------------------------------------------

#ifndef MotionH
#define MotionH

#include "type_def.h"

   void __fastcall InitMotion();
   // 測厚度
   void __fastcall InitAlarmStatus();
   void __fastcall UpdateAlarmStatus();
   void __fastcall UpdateMotionStatus();
   void __fastcall AllHome();
   void __fastcall HomeOneAxis();
   void __fastcall HomeOneAxis8154();
   void __fastcall ResetCommand();
   void __fastcall ResetPosition();
   bool __fastcall MoveForwardMoueUp();
   bool __fastcall MoveBackwardMoueUp();

   // 2013 10 6 - chc 加入Low Distance
   //void __fastcall GetAxisData(int axisno,F64 *dist,F64 *startvel,F64 *maxvel,F64 *tacc,F64 *tdec,F64 *homevel, F64 *reviewvel, F64*uplimit);
   void __fastcall GetAxisData(int axisno,F64 *dist,F64 *startvel,F64 *maxvel,F64 *tacc,F64 *tdec,F64 *homevel, F64 *reviewvel, F64* uplimit, F64 *lowdistance);

   bool __fastcall WaitMotionDone(int axisno, int ms);
   void __fastcall SetTiltPosition();
   void __fastcall SetBasePosition();
   void __fastcall ToTiltPosition();
   // 2013 2 17 - chc Wait Motion X/Y/Z done
   bool __fastcall WaitMotionXYZDone(int ms);
   void __fastcall DecodeIOStatus(int axisno,U16 io_sts);
   void __fastcall SetRXPosition(int no);
   void __fastcall GetAxisPosition(int axisno, F64 *position);
   bool __fastcall MoveAbsolute(int axisno);
   void __fastcall StopAxis(int axisno);
   void __fastcall GetAxisName(int axisno);
   void __fastcall ResetErrorCounter();
   void __fastcall SetAlmOn();
   void __fastcall SetAlmOff();
   void __fastcall SetServoOn();
   void __fastcall SetServoOff();
   void __fastcall ORGLogicSwitch(int axisno, bool mode);

   // 2016 8 26 - chc define type value: 0-wait, 1-nowait(for UpdateMotionStatus())
   //void __fastcall AxisMove(int mode);
   void __fastcall AxisMove(int mode, int type);

   // 前進: 要判定Limit問題
   void __fastcall MoveForward();
   // 各軸上下限檢查
   // dist: 相對移動量
   void __fastcall CheckUpDownLimit(int axisno,F64 *dist, F64 uplimit);
   void __fastcall SetFeedbackSource(int axisno, int src);
   void __fastcall GetPosition(int axisno, F64 *pos);
   void __fastcall WaitMotionDoneXY(int mode, int ms);
   void __fastcall WaitMotionDoneXYZ(int mode, int ms);
   // 移到指定XY位置
   void __fastcall GotoXYZ(int x, int y, int z, bool mode, int review, F64 movevel);
   void __fastcall DoAxisTaMove(int axisno, F64 pos, F64 startvel, F64 maxvel, F64 tacc, F64 tdec);
   void __fastcall DoAxisTaMove(int axisno, F64 pos, F64 startvel, F64 maxvel, F64 tacc, F64 tdec);
   void __fastcall GetCommand(int axisno, I32 *cmd);
   bool __fastcall WaitMotionDoneCCD(int axisno, int ms);
   bool __fastcall WaitMotionXYDoneForScan(int ms);
   void __fastcall WaitRoutine1(int sleepno);
   void __fastcall SetCommand(int axisno, I32 cmd);
   void __fastcall SetMPosition(int axisno, F64 pos);
   void __fastcall GetIOStatus(int axisno, U16 *iostatus);
   // 2013 2 23 - chc DO Reset 0
   void __fastcall InitDO(int mode);
   void __fastcall Beep(int mstime);
   void __fastcall BeepStop();
   // 2013 3 14 - chc 如果Chuck有Wafer則要先吸住
   void __fastcall ChuckWaferVacuum();

   // 2013 4 8 - chc EMC/Door Open Alarm Counter
   int DoorCounter;
   int EMCCounter;

   // 2013 5 15 - chc Sleep - Motion
   void __fastcall DelayTimeM1(int no);                                         // ToRXPositionFun(int no)使用
   void __fastcall DelayTimeM2(int no);                                         // WaitMotionDone()使用
   void __fastcall DelayTimeM3(int no);                                         // AllHome()使用
   void __fastcall DelayTimeM4(int no);                                         // WaitMotionXYZDone()使用
   void __fastcall DelayTimeM5(int no);                                         // WaitMotionDoneXY(), WaitMotionDoneXYZ(), WaitMotionDLFDone使用
   void __fastcall DelayTimeM9(int no);                                         // WaitMotionDoneCCD使用
   void __fastcall DelayTimeM10(int no);                                        // WaitMotionXYDoneForScan使用
   void __fastcall DelayTimeM11(int no);                                        // WaitRoutine1使用

   // 2013 9 27 - chc Z軸移動
   bool __fastcall MoveToZ(int position, int speed, int mode);
   bool __fastcall MoveToY(int position);
   bool __fastcall MoveToT(int position);

   // 2013 10 1 - chc Timer控制
   void __fastcall GetTimeTicM(long *time, short *millitm);

   // 2013 10 8 - chc 到X的AOI點
   void __fastcall ToXAOIPosition();
   // 2013 10 8 - chc 移動X
   bool __fastcall MoveToAxisGap(int axisno, int offset);

   // 2013 10 16 - chc X軸absolute移動
   bool __fastcall MoveToX(int position);

   // 2013 11 12 - chc 確認安全角度
   //#define T_RESOLUTION    0.0003795
   bool __fastcall CheckTSafeDegree();
   // 2013 11 12 - chc 讀取Y軸目前位置
   int __fastcall GetYPosition();
   // 2013 11 12 - chc 往前移動90度, 上限為93度
   void __fastcall MoveToTAdd90();

   // 2014 9 8 - chc 往後移動90度, 下限為-5度
   void __fastcall MoveToTSub90();

   // 2015 6 17 - chc Laser Shutter1 - Bit12
   void __fastcall SetShutter1(bool mode);
   void __fastcall SetShutter2(bool mode);
   void __fastcall ResetDriver(int axisno,bool mode);

   // 2016 6 4 - chc X/Y Axis absolute move
   // 2021 9 11 - chc 加速: MOVE_WAIT
   //bool __fastcall MoveToXY(int xpos,int ypos);
   bool __fastcall MoveToXY(int xpos,int ypos, int mode);

   // 2016 7 8 - chc Last Position
   void __fastcall SetLastPosition();
   void __fastcall ToLastPosition();
   bool __fastcall WaitMotionXYZTDone(int ms);
   // 2016 7 9 - chc User Position
   void __fastcall SetUserPosition(int no);
   // 2016 7 9 - chc User Position
   void __fastcall ToUserPosition(int no);

   // 2016 7 18 - chc Backlash Control
   int __fastcall RelativeMove(I16 axisno,F64 pos,F64 startvel,F64 maxvel,F64 tacc,F64 tdec);
   int __fastcall AbsoluteMove(I16 axisno,F64 pos,F64 startvel,F64 maxvel,F64 tacc,F64 tdec);
   int __fastcall AbsoluteMoveXY(I16 axisno,F64 fxpos,F64 fypos,F64 startvel,F64 maxvel,F64 tacc,F64 tdec);

   // 2016 8 2 - chc Lens Position
   void __fastcall SetLensPosition(int no);
   void __fastcall ToLensPosition(int no);

   // 2016 8 9 - chc R of Within point
   double WithinR;

   // 2016 8 21 - chc 等完成X/Y/T
   void __fastcall WaitMotionDoneXYT(int mode, int ms);

   // 2016 9 9 - chc round function
   int __fastcall round(double f);

   // 2016 10 9 - chc Lens Z Limit
   void __fastcall SetLensZLimit(int no);

   // 2016 10 12 - chc 移到指定XYZ位置
   void __fastcall RelativeMoveXYZ(double dx, double dy, double dz);

   // 2016 10 14 - chc X/Y Axis absolute move
   bool __fastcall MoveToXYDirect(int xpos,int ypos);

   // 2019 7 8 - chc 取得tdec
   double __fastcall GetTdec(int axisno);

   // 2019 7 14 - chc to CCD Position
   void __fastcall SetCCDPosition();
   void __fastcall ToCCDPosition();
   bool __fastcall WaitMotionXYDone(int ms);

   void __fastcall SetAreaPosition();
   void __fastcall SetDotPosition();
   void __fastcall SetBase1Position();
   void __fastcall SetBase2Position();
   bool __fastcall ToAreaPosition();
   bool __fastcall ToDotPosition();
   bool __fastcall ToBase1Position();
   bool __fastcall ToBase2Position();

   // 2019 7 23 - chc X/Y Axis absolute move Ratio
   bool __fastcall MoveToXYRatio(int xpos,int ypos, double ratio);

   // 2019 11 18 - chc 移到指定XY位置
   void __fastcall RelativeMoveXY(double dx, double dy);

   // 2019 12 5 - chc to TXT Position
   void __fastcall ToTXTPosition();
   void __fastcall SetTXTPosition();

   // 2020 2 11 - chc 基準點相對移動
   void __fastcall SetMoveBasePosition();
   bool __fastcall ToMoveBasePosition();

   // 2020 2 14a - chc ServoOn
   void __fastcall ServoOn();

   // 2020 2 16 - chc Save Protect
   void __fastcall SetSaveProtect(int mode);
   // 2020 2 17 - chc Joystick停止時還要檢查其它軸
   void __fastcall StopAllAxis();

   // 2020 3 5 - chc 依次序做X/Y/Z
   void __fastcall MoveToXYZT(int x,int y,int z, int t, int mode);

   // 2020 3 6 - chc Z軸absolute移動
   // 2021 9 11 - chc 加速: MOVE_WAIT
   //bool __fastcall MoveToZ(int position);
   bool __fastcall MoveToZ(int position,int mode);

   // ret: true or false
   bool __fastcall GetNELStatus(int axisno);
   bool __fastcall GetMotionDoneStatus(int axisno);
   // 2021 4 15 - chc 除指定軸外全停
   void __fastcall StopOtherAxis(int axisno);
   // 2021 4 20 - chc 依次序做X/Y/Z
   // mode: 0-Area, 1-Dot
   void __fastcall MoveToXYZ(int x,int y,int z, int mode);
   // 2021 4 21 - chc 立即停止
   void __fastcall StopOneAxis(int axisno);

   // 2021 4 25 - chc Relative Move
   void __fastcall DoRelativeMove(int axisno, int offset);
   // 2021 4 29 - chc W Set
   void __fastcall SetWPosition(int no);
   void __fastcall ToWPositionFun(int no);

   // 2021 9 11 - chc 是否加速
   //bool __fastcall MoveToL(int position);
   bool __fastcall MoveToL(int position, bool boolspeedup);

   // 2021 5 3 - chc Center Position
   void __fastcall ToRealCenterPosition();
   void __fastcall SetRealCenterPosition();

   // 2021 5 5 - chc W軸absolute移動
   bool __fastcall MoveToW(int position);
   void __fastcall CheckZLimit(int axisno, int *position);
   // 2023 8 4 - chc Wait Motion X/Y done
   bool __fastcall WaitMotionXYDone(int ms, int x, int y);

   // 2023 8 4 - chc Reset Axis Command[彰化)
   void __fastcall ResetCommandAxis(int axisno);
   void __fastcall ResetPositionAxis(int axisno);
   bool __fastcall MoveToZ1(int position, int speed);
   // 2023 8 6 - chc Trigger Parameter
   bool __fastcall SetTriggerParameter(int start, int loop, int interval, bool direction);
   bool __fastcall StopTrigger();


//---------------------------------------------------------------------------
#endif
