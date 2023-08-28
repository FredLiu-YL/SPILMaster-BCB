#ifndef _8154_ODM_H
#define _8154_ODM_H

#include "type_def.h"
#define _MYWIN32

#include "type_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MYWIN32
#define FNTYPE PASCAL
#endif
/****************************************************************************/
/*                         ODM Function Function                            */
/****************************************************************************/
//Main Function

//Pause Function
I16 FNTYPE _8154_pause_move(I16 AxisNo);
I16 FNTYPE _8154_resume_move(I16 AxisNo);
I16 FNTYPE _8154_get_pause_status(I16 AxisNo,I16 *PauseStatus);
I16 FNTYPE _8154_set_safe_speed(I16 AxisNo, F64 SafeSpeed);

//DeadZone Function
I16 FNTYPE _8154_set_deadzone(I16 DzLevel, I16 SetNum, I16 DZAxisX, I16 DZAxisY, F64 Point1X, F64 Point1Y, F64 Point2X,F64 Point2Y);
I16 FNTYPE _8154_get_deadzone(I16 DzLevel,I16 SetNum, I16 *GDZAxisX, I16 *GDZAxisY, F64 *GPoint1X, F64 *GPoint1Y, F64 *GPoint2X,F64 *GPoint2Y);
I16 FNTYPE _8154_deadzone_control(I16 DzLevel, I16 DzFlag);
I16 FNTYPE _8154_check_line_trajectory(I16 DzLevel, F64 StartPosX, F64 StartPosY, F64 TargetPosX, F64 TargetPosY);
I16 FNTYPE _8154_check_traditional_arc(I16 DzLevel,I16 DIR, F64 *PintArray, F64 *CpointArray, F64 *PfinArray );
I16 FNTYPE _8154_check_3points_arc(I16 DzLevel, F64 *PintArray, F64 *PpassArray, F64 *PfinArray);
I16 FNTYPE _8154_check_currpos(I16 DzLevel);
I16 FNTYPE _8154_TwoAxes_Home_Move(I16 *AxisArray, F64 StrVel, F64 MaxVel, F64 Tacc);

//DO Control on the fly
I16 FNTYPE _8154_set_percent(I16 AxisNo, I16 ArraySize, I16 *Percent);
I16 FNTYPE _8154_set_Do_data(I16 SetNum, I16 CardNo, I16 Channel, I16 ModuleId,  I16 ArraySize, U32 ChangeBits, U32 *OutDoDataArray);
I16 FNTYPE _8154_mapping_DO_To_Axis(I16 AxisNo, I16 ArraySize, I16 *DOSetNumArray);
I16 FNTYPE _8154_unmapping_DO_To_Axis(I16 AxisNo);
I16 FNTYPE _8154_set_DoControl(I16 AxisNo, I16 Flag);

//DI Interlock
I16 FNTYPE _8154_set_DI_interlock_data(I16 CardNo, I16 SetNum, I16 ModuleId, U32 bitsOfCheck);
I16 FNTYPE _8154_get_DI_interlock_data(I16 CardNo, I16 SetNum, I16 *ModuleId, U32 *bitsOfCheck);
I16 FNTYPE _8154_mapping_DI_interlock(I16 AxisNo, I16 Active, I16 ArraySize, I16 *SetNumArray);
I16 FNTYPE _8154_unmapping_DI_interlock(I16 AxisNo);
I16 FNTYPE _8154_set_DI_interlock_control(I16 CardNo, I16 Flag);


//Short Command
I16 FNTYPE _8154_set_Sv(I16 AxisNo,F64 StrVel);
I16 FNTYPE _8154_set_Mv(I16 AxisNo,F64 MaxVel);
I16 FNTYPE _8154_set_Tacc(I16 AxisNo,F64 Tacc);
I16 FNTYPE _8154_set_Tdec(I16 AxisNo,F64 Tdec);
I16 FNTYPE _8154_set_Sacc(I16 AxisNo,F64 Sacc);
I16 FNTYPE _8154_set_Sdec(I16 AxisNo,F64 Sdec);
I16 FNTYPE _8154_set_TS(I16 AxisNo,I16 T_S);
I16 FNTYPE _8154_set_AR(I16 AxisNo,I16 A_R);

I16 FNTYPE _8154_set_line_Sv(I16 AxisNo, F64 StrVel);
I16 FNTYPE _8154_set_line_Mv(I16 AxisNo, F64 MaxVel);
I16 FNTYPE _8154_set_line_Tacc(I16 AxisNo, F64 Tacc);
I16 FNTYPE _8154_set_line_Tdec(I16 AxisNo, F64 Tdec);
I16 FNTYPE _8154_set_line_Sacc(I16 AxisNo, F64 Sacc);
I16 FNTYPE _8154_set_line_Sdec(I16 AxisNo, F64 Sdec);
I16 FNTYPE _8154_set_line_TS(I16 AxisNo, I16 T_S);
I16 FNTYPE _8154_set_line_AR(I16 AxisNo, I16 A_R);

I16 FNTYPE _8154_set_arc_Sv(I16 AxisNo, F64 StrVel);
I16 FNTYPE _8154_set_arc_Mv(I16 AxisNo, F64 MaxVel);
I16 FNTYPE _8154_set_arc_Tacc(I16 AxisNo, F64 Tacc);
I16 FNTYPE _8154_set_arc_Tdec(I16 AxisNo, F64 Tdec);
I16 FNTYPE _8154_set_arc_Sacc(I16 AxisNo, F64 Sacc);
I16 FNTYPE _8154_set_arc_Sdec(I16 AxisNo, F64 Sdec);
I16 FNTYPE _8154_set_arc_TS(I16 AxisNo, I16 T_S);
I16 FNTYPE _8154_set_arc_AR(I16 AxisNo, I16 A_R);
I16 FNTYPE _8154_set_arc_DIR(I16 AxisNo, I16 DIR);

I16 FNTYPE _8154_get_short_command_data(I16 AxisNo, I16 MoveType, F64 *StrVel, F64 *MaxVel, F64 *Tacc, F64 *Tdec, F64 *Sacc, F64 *Sdec, I16 *T_S, I16 *A_R, I16 *DIR );

I16 FNTYPE _8154_move(I16 AxisNo, F64 Pos_Dis);
I16 FNTYPE _8154_line_move(I16 Dimension, I16 *AxisArray,F64 *Pos_Dis_Aray);
I16 FNTYPE _8154_arc_move(I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey);
I16 FNTYPE _8154_arc_three_points(I16 *AxisArray, F64 *PintArray, F64 *PpassArray, F64 *PfinArray);

#ifdef __cplusplus
}
#endif

#endif