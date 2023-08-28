Attribute VB_Name = "Module1"
' Copyright (C) 1995-2009 ADLINK Technology INC. All rights reserved.
Option Explicit
'
' #ifndef _P8154_1_H
' #define _P8154_1_H
'
' #define _MYWIN32
'
' #include "type_def.h"
'
' #ifdef __cplusplus
' extern "C" {
' #endif
'
' #ifdef _MYWIN32
' #define FNTYPE PASCAL
' #endif
'
'  System Section 6.3
Declare Function B_8154_initial Lib "8154.dll" Alias "_8154_initial" (CardID_InBit As Integer, ByVal Manual_ID As Integer) As Integer
Declare Function B_8154_close Lib "8154.dll" Alias "_8154_close" () As Integer
Declare Function B_8154_get_version Lib "8154.dll" Alias "_8154_get_version" (ByVal CardId As Integer, firmware_ver As Integer, driver_ver As Long, dll_ver As Long) As Integer
Declare Function B_8154_set_security_key Lib "8154.dll" Alias "_8154_set_security_key" (ByVal CardId As Integer, ByVal old_secu_code As Integer, ByVal new_secu_code As Integer) As Integer
Declare Function B_8154_check_security_key Lib "8154.dll" Alias "_8154_check_security_key" (ByVal CardId As Integer, ByVal secu_code As Integer) As Integer
Declare Function B_8154_reset_security_key Lib "8154.dll" Alias "_8154_reset_security_key" (ByVal CardId As Integer) As Integer
Declare Function B_8154_config_from_file Lib "8154.dll" Alias "_8154_config_from_file" () As Integer
Declare Function B_8154_get_DBboard_type Lib "8154.dll" Alias "_8154_get_DBboard_type" (ByVal CardId As Integer, DBtype As Integer) As Integer
'
' Pulse Input/Output Configuration Section 6.4
Declare Function B_8154_set_pls_outmode Lib "8154.dll" Alias "_8154_set_pls_outmode" (ByVal AxisNo As Integer, ByVal pls_outmode As Integer) As Integer
Declare Function B_8154_set_pls_iptmode Lib "8154.dll" Alias "_8154_set_pls_iptmode" (ByVal AxisNo As Integer, ByVal pls_iptmode As Integer, ByVal pls_logic As Integer) As Integer
Declare Function B_8154_set_feedback_src Lib "8154.dll" Alias "_8154_set_feedback_src" (ByVal AxisNo As Integer, ByVal Src As Integer) As Integer
'
' Velocity mode motion Section 6.5
Declare Function B_8154_tv_move Lib "8154.dll" Alias "_8154_tv_move" (ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_sv_move Lib "8154.dll" Alias "_8154_sv_move" (ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal SVacc As Double) As Integer
Declare Function B_8154_sd_stop Lib "8154.dll" Alias "_8154_sd_stop" (ByVal AxisNo As Integer, ByVal Tdec As Double) As Integer
Declare Function B_8154_emg_stop Lib "8154.dll" Alias "_8154_emg_stop" (ByVal AxisNo As Integer) As Integer
Declare Function B_8154_get_current_speed Lib "8154.dll" Alias "_8154_get_current_speed" (ByVal AxisNo As Integer, speed As Double) As Integer
Declare Function B_8154_speed_override Lib "8154.dll" Alias "_8154_speed_override" (ByVal CAxisNo As Integer, ByVal NewVelPercent As Double, ByVal Time As Double) As Integer
Declare Function B_8154_speed_override2 Lib "8154.dll" Alias "_8154_speed_override2" (ByVal CAxisNo As Integer, ByVal NewVel As Double, ByVal Time As Double) As Integer
Declare Function B_8154_set_max_override_speed Lib "8154.dll" Alias "_8154_set_max_override_speed" (ByVal AxisNo As Integer, ByVal OvrdSpeed As Double, ByVal enable As Integer) As Integer
'
' Single Axis Position Mode Section 6.6
Declare Function B_8154_start_tr_move Lib "8154.dll" Alias "_8154_start_tr_move" (ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_move Lib "8154.dll" Alias "_8154_start_ta_move" (ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_sr_move Lib "8154.dll" Alias "_8154_start_sr_move" (ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_move Lib "8154.dll" Alias "_8154_start_sa_move" (ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_set_move_ratio Lib "8154.dll" Alias "_8154_set_move_ratio" (ByVal AxisNo As Integer, ByVal move_ratio As Double) As Integer
Declare Function B_8154_position_override Lib "8154.dll" Alias "_8154_position_override" (ByVal AxisNo As Integer, ByVal NewPos As Double) As Integer
'
' Linear Interpolated Motion Section 6.7
'  Two Axes Linear Interpolation function
Declare Function B_8154_start_tr_move_xy Lib "8154.dll" Alias "_8154_start_tr_move_xy" (ByVal CardId As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_tr_move_zu Lib "8154.dll" Alias "_8154_start_tr_move_zu" (ByVal CardId As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
'
Declare Function B_8154_start_ta_move_xy Lib "8154.dll" Alias "_8154_start_ta_move_xy" (ByVal CardId As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_move_zu Lib "8154.dll" Alias "_8154_start_ta_move_zu" (ByVal CardId As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
'
Declare Function B_8154_start_sr_move_xy Lib "8154.dll" Alias "_8154_start_sr_move_xy" (ByVal CardId As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sr_move_zu Lib "8154.dll" Alias "_8154_start_sr_move_zu" (ByVal CardId As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
Declare Function B_8154_start_sa_move_xy Lib "8154.dll" Alias "_8154_start_sa_move_xy" (ByVal CardId As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_move_zu Lib "8154.dll" Alias "_8154_start_sa_move_zu" (ByVal CardId As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
' Any 2 of former or later 4 axes linear interpolation function
Declare Function B_8154_start_tr_line2 Lib "8154.dll" Alias "_8154_start_tr_line2" (AxisArray As Integer, DistArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_line2 Lib "8154.dll" Alias "_8154_start_ta_line2" (AxisArray As Integer, PosArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_sr_line2 Lib "8154.dll" Alias "_8154_start_sr_line2" (AxisArray As Integer, DistArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_line2 Lib "8154.dll" Alias "_8154_start_sa_line2" (AxisArray As Integer, PosArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
' Any 3 of former or later 4 axes linear interpolation function
Declare Function B_8154_start_tr_line3 Lib "8154.dll" Alias "_8154_start_tr_line3" (AxisArray As Integer, DistArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_line3 Lib "8154.dll" Alias "_8154_start_ta_line3" (AxisArray As Integer, PosArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_sr_line3 Lib "8154.dll" Alias "_8154_start_sr_line3" (AxisArray As Integer, DistArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_line3 Lib "8154.dll" Alias "_8154_start_sa_line3" (AxisArray As Integer, PosArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
' Former or later 4 Axes linear interpolation function
Declare Function B_8154_start_tr_line4 Lib "8154.dll" Alias "_8154_start_tr_line4" (AxisArray As Integer, DistArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_line4 Lib "8154.dll" Alias "_8154_start_ta_line4" (AxisArray As Integer, PosArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_sr_line4 Lib "8154.dll" Alias "_8154_start_sr_line4" (AxisArray As Integer, DistArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_line4 Lib "8154.dll" Alias "_8154_start_sa_line4" (AxisArray As Integer, PosArray As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
' /*
' I16 FNTYPE _8154_tv_line2(I16 *AxisArray, F64 StrVel, F64 MaxVel, F64 Tacc);
' I16 FNTYPE _8154_sv_line2(I16 *AxisArray,  F64 StrVel, F64 MaxVel, F64 Tacc, F64 SVacc);
' */
'
' Circular Interpolation Motion Section 6.8
'  Two Axes Arc Interpolation function
Declare Function B_8154_start_tr_arc_xy Lib "8154.dll" Alias "_8154_start_tr_arc_xy" (ByVal CardId As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_arc_xy Lib "8154.dll" Alias "_8154_start_ta_arc_xy" (ByVal CardId As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_sr_arc_xy Lib "8154.dll" Alias "_8154_start_sr_arc_xy" (ByVal CardId As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_arc_xy Lib "8154.dll" Alias "_8154_start_sa_arc_xy" (ByVal CardId As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
Declare Function B_8154_start_tr_arc_zu Lib "8154.dll" Alias "_8154_start_tr_arc_zu" (ByVal CardId As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_arc_zu Lib "8154.dll" Alias "_8154_start_ta_arc_zu" (ByVal CardId As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_sr_arc_zu Lib "8154.dll" Alias "_8154_start_sr_arc_zu" (ByVal CardId As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_arc_zu Lib "8154.dll" Alias "_8154_start_sa_arc_zu" (ByVal CardId As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
Declare Function B_8154_start_tr_arc2 Lib "8154.dll" Alias "_8154_start_tr_arc2" (AxisArray As Integer, OffsetCenter As Double, OffsetEnd As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_arc2 Lib "8154.dll" Alias "_8154_start_ta_arc2" (AxisArray As Integer, CenterPos As Double, EndPos As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_sr_arc2 Lib "8154.dll" Alias "_8154_start_sr_arc2" (AxisArray As Integer, OffsetCenter As Double, OffsetEnd As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_arc2 Lib "8154.dll" Alias "_8154_start_sa_arc2" (AxisArray As Integer, CenterPos As Double, EndPos As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
' Helical Interpolation Motion Section 6.9
Declare Function B_8154_start_tr_helical Lib "8154.dll" Alias "_8154_start_tr_helical" (ByVal card_ID As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal PitchDist As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_ta_helical Lib "8154.dll" Alias "_8154_start_ta_helical" (ByVal card_ID As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal PitchPos As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_start_sr_helical Lib "8154.dll" Alias "_8154_start_sr_helical" (ByVal card_ID As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal PitchDist As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_start_sa_helical Lib "8154.dll" Alias "_8154_start_sa_helical" (ByVal card_ID As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal PitchPos As Double, ByVal CW_CCW As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
'
' Home Return Mode Section 6.10
Declare Function B_8154_set_home_config Lib "8154.dll" Alias "_8154_set_home_config" (ByVal AxisNo As Integer, ByVal home_mode As Integer, ByVal org_logic As Integer, ByVal ez_logic As Integer, ByVal ez_count As Integer, ByVal erc_out As Integer) As Integer
Declare Function B_8154_home_move Lib "8154.dll" Alias "_8154_home_move" (ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_escape_home Lib "8154.dll" Alias "_8154_escape_home" (ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_home_search Lib "8154.dll" Alias "_8154_home_search" (ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal ORGOffset As Double) As Integer
'
' Manual Pulser Motion Section 6.11
Declare Function B_8154_set_pulser_iptmode Lib "8154.dll" Alias "_8154_set_pulser_iptmode" (ByVal AxisNo As Integer, ByVal InputMode As Integer, ByVal Inverse As Integer) As Integer
Declare Function B_8154_disable_pulser_input Lib "8154.dll" Alias "_8154_disable_pulser_input" (ByVal AxisNo As Integer, ByVal Disable As Integer) As Integer
Declare Function B_8154_pulser_vmove Lib "8154.dll" Alias "_8154_pulser_vmove" (ByVal AxisNo As Integer, ByVal SpeedLimit As Double) As Integer
Declare Function B_8154_pulser_pmove Lib "8154.dll" Alias "_8154_pulser_pmove" (ByVal AxisNo As Integer, ByVal Dist As Double, ByVal SpeedLimit As Double) As Integer
Declare Function B_8154_set_pulser_ratio Lib "8154.dll" Alias "_8154_set_pulser_ratio" (ByVal AxisNo As Integer, ByVal DivF As Integer, ByVal MultiF As Integer) As Integer
'
' Motion Status Section 6.12
Declare Function B_8154_motion_done Lib "8154.dll" Alias "_8154_motion_done" (ByVal AxisNo As Integer) As Integer
'
' Motion Interface I/O Section 6.13
Declare Function B_8154_set_servo Lib "8154.dll" Alias "_8154_set_servo" (ByVal AxisNo As Integer, ByVal on_off As Integer) As Integer
Declare Function B_8154_set_pcs_logic Lib "8154.dll" Alias "_8154_set_pcs_logic" (ByVal AxisNo As Integer, ByVal pcs_logic As Integer) As Integer
Declare Function B_8154_set_pcs Lib "8154.dll" Alias "_8154_set_pcs" (ByVal AxisNo As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_set_clr_mode Lib "8154.dll" Alias "_8154_set_clr_mode" (ByVal AxisNo As Integer, ByVal clr_mode As Integer, ByVal targetCounterInBit As Integer) As Integer
Declare Function B_8154_set_inp Lib "8154.dll" Alias "_8154_set_inp" (ByVal AxisNo As Integer, ByVal inp_enable As Integer, ByVal inp_logic As Integer) As Integer
Declare Function B_8154_set_alm Lib "8154.dll" Alias "_8154_set_alm" (ByVal AxisNo As Integer, ByVal alm_logic As Integer, ByVal alm_mode As Integer) As Integer
Declare Function B_8154_set_erc Lib "8154.dll" Alias "_8154_set_erc" (ByVal AxisNo As Integer, ByVal erc_logic As Integer, ByVal erc_pulse_width As Integer, ByVal erc_mode As Integer) As Integer
Declare Function B_8154_set_erc_out Lib "8154.dll" Alias "_8154_set_erc_out" (ByVal AxisNo As Integer) As Integer
Declare Function B_8154_clr_erc Lib "8154.dll" Alias "_8154_clr_erc" (ByVal AxisNo As Integer) As Integer
Declare Function B_8154_set_sd Lib "8154.dll" Alias "_8154_set_sd" (ByVal AxisNo As Integer, ByVal sd_logic As Integer, ByVal sd_latch As Integer, ByVal sd_mode As Integer) As Integer
Declare Function B_8154_enable_sd Lib "8154.dll" Alias "_8154_enable_sd" (ByVal AxisNo As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_set_limit_logic Lib "8154.dll" Alias "_8154_set_limit_logic" (ByVal AxisNo As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_set_limit_mode Lib "8154.dll" Alias "_8154_set_limit_mode" (ByVal AxisNo As Integer, ByVal limit_mode As Integer) As Integer
Declare Function B_8154_get_io_status Lib "8154.dll" Alias "_8154_get_io_status" (ByVal AxisNo As Integer, io_sts As Integer) As Integer
'
' Interrupt Control Section 6.14
Declare Function B_8154_int_control Lib "8154.dll" Alias "_8154_int_control" (ByVal CardId As Integer, ByVal intFlag As Integer) As Integer
Declare Function B_8154_wait_error_interrupt Lib "8154.dll" Alias "_8154_wait_error_interrupt" (ByVal AxisNo As Integer, ByVal TimeOut_ms As Long) As Integer
Declare Function B_8154_wait_motion_interrupt Lib "8154.dll" Alias "_8154_wait_motion_interrupt" (ByVal AxisNo As Integer, ByVal IntFactorBitNo As Integer, ByVal TimeOut_ms As Long) As Integer
Declare Function B_8154_set_motion_int_factor Lib "8154.dll" Alias "_8154_set_motion_int_factor" (ByVal AxisNo As Integer, ByVal int_factor As Long) As Integer
'
' Position Control and Counters Section 6.15
Declare Function B_8154_get_position Lib "8154.dll" Alias "_8154_get_position" (ByVal AxisNo As Integer, Pos As Double) As Integer
Declare Function B_8154_set_position Lib "8154.dll" Alias "_8154_set_position" (ByVal AxisNo As Integer, ByVal Pos As Double) As Integer
Declare Function B_8154_get_command Lib "8154.dll" Alias "_8154_get_command" (ByVal AxisNo As Integer, Cmd As Long) As Integer
Declare Function B_8154_set_command Lib "8154.dll" Alias "_8154_set_command" (ByVal AxisNo As Integer, ByVal Cmd As Long) As Integer
Declare Function B_8154_get_error_counter Lib "8154.dll" Alias "_8154_get_error_counter" (ByVal AxisNo As Integer, error As Integer) As Integer
Declare Function B_8154_reset_error_counter Lib "8154.dll" Alias "_8154_reset_error_counter" (ByVal AxisNo As Integer) As Integer
Declare Function B_8154_reset_counter_after_home Lib "8154.dll" Alias "_8154_reset_counter_after_home" (ByVal AxisNo As Integer, ByVal EnableByBit As Integer) As Integer
Declare Function B_8154_set_general_counter Lib "8154.dll" Alias "_8154_set_general_counter" (ByVal AxisNo As Integer, ByVal CntSrc As Integer, ByVal CntValue As Double) As Integer
Declare Function B_8154_get_general_counter Lib "8154.dll" Alias "_8154_get_general_counter" (ByVal AxisNo As Integer, CntValue As Double) As Integer
Declare Function B_8154_reset_target_pos Lib "8154.dll" Alias "_8154_reset_target_pos" (ByVal AxisNo As Integer, ByVal TargetPos As Double) As Integer
Declare Function B_8154_get_target_pos Lib "8154.dll" Alias "_8154_get_target_pos" (ByVal AxisNo As Integer, TargetPos As Double) As Integer
Declare Function B_8154_set_res_distance Lib "8154.dll" Alias "_8154_set_res_distance" (ByVal AxisNo As Integer, ByVal ResDistance As Double) As Integer
Declare Function B_8154_get_res_distance Lib "8154.dll" Alias "_8154_get_res_distance" (ByVal AxisNo As Integer, ResDistance As Double) As Integer
'
' Position Compare and Latch Section 6.16
Declare Function B_8154_set_do_cmp_output_selection Lib "8154.dll" Alias "_8154_set_do_cmp_output_selection" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal DoCmpOutputSelection As Integer) As Integer
Declare Function B_8154_set_trigger_logic Lib "8154.dll" Alias "_8154_set_trigger_logic" (ByVal AxisNo As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_set_error_comparator Lib "8154.dll" Alias "_8154_set_error_comparator" (ByVal AxisNo As Integer, ByVal CmpMethod As Integer, ByVal CmpAction As Integer, ByVal Data As Long) As Integer
Declare Function B_8154_set_general_comparator Lib "8154.dll" Alias "_8154_set_general_comparator" (ByVal AxisNo As Integer, ByVal CmpSrc As Integer, ByVal CmpMethod As Integer, ByVal CmpAction As Integer, ByVal Data As Long) As Integer
Declare Function B_8154_set_trigger_comparator Lib "8154.dll" Alias "_8154_set_trigger_comparator" (ByVal AxisNo As Integer, ByVal CmpSrc As Integer, ByVal CmpMethod As Integer, ByVal Data As Long) As Integer
Declare Function B_8154_set_latch_source Lib "8154.dll" Alias "_8154_set_latch_source" (ByVal AxisNo As Integer, ByVal LtcSrc As Integer) As Integer
Declare Function B_8154_set_ltc_logic Lib "8154.dll" Alias "_8154_set_ltc_logic" (ByVal AxisNo As Integer, ByVal LtcLogic As Integer) As Integer
Declare Function B_8154_get_latch_data Lib "8154.dll" Alias "_8154_get_latch_data" (ByVal AxisNo As Integer, ByVal CounterNo As Integer, Pos As Double) As Integer
Declare Function B_8154_set_ring_counter Lib "8154.dll" Alias "_8154_set_ring_counter" (ByVal AxisNo As Integer, ByVal RingVal As Integer) As Integer
Declare Function B_8154_get_ring_counter Lib "8154.dll" Alias "_8154_get_ring_counter" (ByVal AxisNo As Integer, RingVal As Integer) As Integer
'

' Continuous Motion Section 6.17
Declare Function B_8154_set_continuous_move Lib "8154.dll" Alias "_8154_set_continuous_move" (ByVal AxisNo As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_check_continuous_buffer Lib "8154.dll" Alias "_8154_check_continuous_buffer" (ByVal AxisNo As Integer) As Integer
Declare Function B_8154_dwell_move Lib "8154.dll" Alias "_8154_dwell_move" (ByVal AxisNo As Integer, ByVal milliSecond As Double) As Integer
'
' Multiple Axes Simultaneous Operation Section 6.18
Declare Function B_8154_set_tr_move_all Lib "8154.dll" Alias "_8154_set_tr_move_all" (ByVal TotalAxes As Integer, AxisArray As Integer, DistA As Double, StrVelA As Double, MaxVelA As Double, TaccA As Double, TdecA As Double) As Integer
Declare Function B_8154_set_sa_move_all Lib "8154.dll" Alias "_8154_set_sa_move_all" (ByVal TotalAx As Integer, AxisArray As Integer, PosA As Double, StrVelA As Double, MaxVelA As Double, TaccA As Double, TdecA As Double, SVaccA As Double, SVdecA As Double) As Integer
Declare Function B_8154_set_ta_move_all Lib "8154.dll" Alias "_8154_set_ta_move_all" (ByVal TotalAx As Integer, AxisArray As Integer, PosA As Double, StrVelA As Double, MaxVelA As Double, TaccA As Double, TdecA As Double) As Integer
Declare Function B_8154_set_sr_move_all Lib "8154.dll" Alias "_8154_set_sr_move_all" (ByVal TotalAx As Integer, AxisArray As Integer, DistA As Double, StrVelA As Double, MaxVelA As Double, TaccA As Double, TdecA As Double, SVaccA As Double, SVdecA As Double) As Integer
Declare Function B_8154_start_move_all Lib "8154.dll" Alias "_8154_start_move_all" (ByVal FirstAxisNo As Integer) As Integer
Declare Function B_8154_stop_move_all Lib "8154.dll" Alias "_8154_stop_move_all" (ByVal FirstAxisNo As Integer) As Integer
Declare Function B_8154_set_sync_stop_mode Lib "8154.dll" Alias "_8154_set_sync_stop_mode" (ByVal AxisNo As Integer, ByVal stop_mode As Integer) As Integer
Declare Function B_8154_set_sync_option Lib "8154.dll" Alias "_8154_set_sync_option" (ByVal AxisNo As Integer, ByVal sync_stop_on As Integer, ByVal cstop_output_on As Integer, ByVal sync_option1 As Integer, ByVal sync_option2 As Integer) As Integer
Declare Function B_8154_set_sync_signal_source Lib "8154.dll" Alias "_8154_set_sync_signal_source" (ByVal AxisNo As Integer, ByVal sync_axis As Integer) As Integer
Declare Function B_8154_set_sync_signal_mode Lib "8154.dll" Alias "_8154_set_sync_signal_mode" (ByVal AxisNo As Integer, ByVal mode As Integer) As Integer
'
' General-purposed Input/Output Section 6.19
Declare Function B_8154_set_gpio_output Lib "8154.dll" Alias "_8154_set_gpio_output" (ByVal CardId As Integer, ByVal DoValue As Integer) As Integer
Declare Function B_8154_get_gpio_output Lib "8154.dll" Alias "_8154_get_gpio_output" (ByVal CardId As Integer, DoValue As Integer) As Integer
Declare Function B_8154_get_gpio_input Lib "8154.dll" Alias "_8154_get_gpio_input" (ByVal CardId As Integer, DiValue As Integer) As Integer
Declare Function B_8154_set_gpio_input_function Lib "8154.dll" Alias "_8154_set_gpio_input_function" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal Select_ As Integer, ByVal Logic As Integer) As Integer
'
' Soft Limit 6.20
Declare Function B_8154_disable_soft_limit Lib "8154.dll" Alias "_8154_disable_soft_limit" (ByVal AxisNo As Integer) As Integer
Declare Function B_8154_enable_soft_limit Lib "8154.dll" Alias "_8154_enable_soft_limit" (ByVal AxisNo As Integer, ByVal Action As Integer) As Integer
Declare Function B_8154_set_soft_limit Lib "8154.dll" Alias "_8154_set_soft_limit" (ByVal AxisNo As Integer, ByVal PlusLimit As Long, ByVal MinusLimit As Long) As Integer
Declare Function B_8154_check_soft_limit Lib "8154.dll" Alias "_8154_check_soft_limit" (ByVal AxisNo As Integer, PlusLimit_sts As Integer, MinusLimit_sts As Integer) As Integer
'
'
' Backlas Compensation / Vibration Suppression 6.21
Declare Function B_8154_backlash_comp Lib "8154.dll" Alias "_8154_backlash_comp" (ByVal AxisNo As Integer, ByVal CompPulse As Integer, ByVal mode As Integer) As Integer
Declare Function B_8154_suppress_vibration Lib "8154.dll" Alias "_8154_suppress_vibration" (ByVal AxisNo As Integer, ByVal ReverseTime As Integer, ByVal ForwardTime As Integer) As Integer
Declare Function B_8154_set_fa_speed Lib "8154.dll" Alias "_8154_set_fa_speed" (ByVal AxisNo As Integer, ByVal FA_Speed As Double) As Integer
'
' Speed Profile Calculation 6.22
Declare Function B_8154_get_tr_move_profile Lib "8154.dll" Alias "_8154_get_tr_move_profile" (ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, pStrVel As Double, pMaxVel As Double, pTacc As Double, pTdec As Double, pTconst As Double) As Integer
Declare Function B_8154_get_ta_move_profile Lib "8154.dll" Alias "_8154_get_ta_move_profile" (ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, pStrVel As Double, pMaxVel As Double, pTacc As Double, pTdec As Double, pTconst As Double) As Integer
Declare Function B_8154_get_sr_move_profile Lib "8154.dll" Alias "_8154_get_sr_move_profile" (ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double, pStrVel As Double, pMaxVel As Double, pTacc As Double, pTdec As Double, pSVacc As Double, pSVdec As Double, pTconst As Double) As Integer
Declare Function B_8154_get_sa_move_profile Lib "8154.dll" Alias "_8154_get_sa_move_profile" (ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double, pStrVel As Double, pMaxVel As Double, pTacc As Double, pTdec As Double, pSVacc As Double, pSVdec As Double, pTconst As Double) As Integer
'
' /****************************************************************************/
' /*      DB-8150  Function  Declerations                                              */
' /****************************************************************************/
'  Initialization and System Information Section
'  System Section 5.2
Declare Function B_8154_db50_initial Lib "8154.dll" Alias "_8154_db50_initial" (ByVal CardId As Integer) As Integer
Declare Function B_8154_db50_close Lib "8154.dll" Alias "_8154_db50_close" (ByVal CardId As Integer) As Integer
Declare Function B_8154_db50_get_DBfpga_version Lib "8154.dll" Alias "_8154_db50_get_DBfpga_version" (ByVal CardId As Integer, Version As Integer) As Integer
Declare Function B_8154_db50_get_PCB_version Lib "8154.dll" Alias "_8154_db50_get_PCB_version" (ByVal CardId As Integer, Version As Integer) As Integer
'
' Encoder & Counter: Section 5.3
Declare Function B_8154_db50_set_encoder_input_mode Lib "8154.dll" Alias "_8154_db50_set_encoder_input_mode" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal IptMode As Integer) As Integer
Declare Function B_8154_db50_set_encoder_value Lib "8154.dll" Alias "_8154_db50_set_encoder_value" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal EncValue As Long) As Integer
Declare Function B_8154_db50_get_encoder_value Lib "8154.dll" Alias "_8154_db50_get_encoder_value" (ByVal CardId As Integer, ByVal Channel As Integer, EncValue As Long) As Integer
Declare Function B_8154_db50_set_encoder_up_down_count Lib "8154.dll" Alias "_8154_db50_set_encoder_up_down_count" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal Inverse As Integer) As Integer
Declare Function B_8154_db50_set_ez_clear Lib "8154.dll" Alias "_8154_db50_set_ez_clear" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal enable As Integer, ByVal ClrLogic As Integer) As Integer
Declare Function B_8154_db50_set_counter_source Lib "8154.dll" Alias "_8154_db50_set_counter_source" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal CtnSrc As Integer) As Integer
'
' PWM Configuration: Section 5.4
Declare Function B_8154_db50_set_pwm_source Lib "8154.dll" Alias "_8154_db50_set_pwm_source" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal CmpEn As Integer, ByVal LinearEn As Integer, ByVal TimerEn As Integer) As Integer
Declare Function B_8154_db50_set_pwm_mode Lib "8154.dll" Alias "_8154_db50_set_pwm_mode" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal PulseOrToggle As Integer) As Integer
Declare Function B_8154_db50_set_pwm_pulse_width Lib "8154.dll" Alias "_8154_db50_set_pwm_pulse_width" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal WidthPara As Long) As Integer
'
' TRG-OUT Configuration: Section 5.5
Declare Function B_8154_db50_set_trigger_source Lib "8154.dll" Alias "_8154_db50_set_trigger_source" (ByVal CardId As Integer, ByVal TriggerLine As Integer, ByVal Channel As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_db50_set_trigger_logic Lib "8154.dll" Alias "_8154_db50_set_trigger_logic" (ByVal CardId As Integer, ByVal TriggerLine As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db50_reset_trigger_num Lib "8154.dll" Alias "_8154_db50_reset_trigger_num" (ByVal CardId As Integer, ByVal Channel As Integer) As Integer
Declare Function B_8154_db50_get_trigger_num Lib "8154.dll" Alias "_8154_db50_get_trigger_num" (ByVal CardId As Integer, ByVal Channel As Integer, TriggerNum As Double) As Integer
'
'  Comparator: Section 5.6
Declare Function B_8154_db50_enable_comparator Lib "8154.dll" Alias "_8154_db50_enable_comparator" (ByVal CardId As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_db50_set_comparator_data Lib "8154.dll" Alias "_8154_db50_set_comparator_data" (ByVal CardId As Integer, ByVal CmpData As Long) As Integer
Declare Function B_8154_db50_get_comparator_data Lib "8154.dll" Alias "_8154_db50_get_comparator_data" (ByVal CardId As Integer, CmpData As Long) As Integer
'
' FIFO Comparing: Section 5.7
Declare Function B_8154_db50_reset_fifo Lib "8154.dll" Alias "_8154_db50_reset_fifo" (ByVal CardId As Integer) As Integer
Declare Function B_8154_db50_get_fifo_status Lib "8154.dll" Alias "_8154_db50_get_fifo_status" (ByVal CardId As Integer, FifoSts As Integer) As Integer
Declare Function B_8154_db50_set_fifo_array Lib "8154.dll" Alias "_8154_db50_set_fifo_array" (ByVal CardId As Integer, ByVal ArraySize As Long, DataArr As Long, ByVal ShiftFlag As Integer) As Integer
Declare Function B_8154_db50_set_fifo_shift Lib "8154.dll" Alias "_8154_db50_set_fifo_shift" (ByVal CardId As Integer) As Integer
Declare Function B_8154_db50_set_fifo_low_level Lib "8154.dll" Alias "_8154_db50_set_fifo_low_level" (ByVal CardId As Integer, ByVal Level As Integer) As Integer
Declare Function B_8154_db50_get_fifo_low_level Lib "8154.dll" Alias "_8154_db50_get_fifo_low_level" (ByVal CardId As Integer, Level As Integer) As Integer
'
'  Linear Comparing: Section 5.8
Declare Function B_8154_db50_enable_linear_compare Lib "8154.dll" Alias "_8154_db50_enable_linear_compare" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_db50_set_linear_compare Lib "8154.dll" Alias "_8154_db50_set_linear_compare" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal StartPoint As Long, ByVal RepeatTimes As Double, ByVal Interval As Integer) As Integer
Declare Function B_8154_db50_get_linear_compare_data Lib "8154.dll" Alias "_8154_db50_get_linear_compare_data" (ByVal CardId As Integer, ByVal Channel As Integer, CurrentData As Double) As Integer
'
'  Manual Trigger: Section 5.9
Declare Function B_8154_db50_manual_trigger Lib "8154.dll" Alias "_8154_db50_manual_trigger" (ByVal CardId As Integer, ByVal Channel As Integer) As Integer
'
' General-purposed Input/Output Section 5.10
Declare Function B_8154_db50_set_gpio_output Lib "8154.dll" Alias "_8154_db50_set_gpio_output" (ByVal CardId As Integer, ByVal DoValue As Integer) As Integer
Declare Function B_8154_db50_get_gpio_output Lib "8154.dll" Alias "_8154_db50_get_gpio_output" (ByVal CardId As Integer, DoValue As Integer) As Integer
Declare Function B_8154_db50_get_di_sts Lib "8154.dll" Alias "_8154_db50_get_di_sts" (ByVal CardId As Integer, DiStsInBit As Integer, EzStsInBit As Integer) As Integer
'
'  Latch: Section 5.11
Declare Function B_8154_db50_set_di_latch Lib "8154.dll" Alias "_8154_db50_set_di_latch" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal enable As Integer, ByVal EdgeSel As Integer) As Integer
Declare Function B_8154_db50_get_di_latch_value Lib "8154.dll" Alias "_8154_db50_get_di_latch_value" (ByVal CardId As Integer, ByVal Channel As Integer, LatchValue As Long) As Integer
'
'  Timer: Section 5.12
Declare Function B_8154_db50_set_Timer Lib "8154.dll" Alias "_8154_db50_set_Timer" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal Interval As Long) As Integer
Declare Function B_8154_db50_start_timer Lib "8154.dll" Alias "_8154_db50_start_timer" (ByVal CardId As Integer, ByVal Channel As Integer, ByVal Start As Integer) As Integer
'
'  Interrupt: Section 5.13
Declare Function B_8154_db50_set_int_control Lib "8154.dll" Alias "_8154_db50_set_int_control" (ByVal CardId As Integer, ByVal intFlag As Integer) As Integer
Declare Function B_8154_db50_set_int_factor Lib "8154.dll" Alias "_8154_db50_set_int_factor" (ByVal CardId As Integer, ByVal IntFactorsInBit As Integer) As Integer
Declare Function B_8154_db50_get_int_factor Lib "8154.dll" Alias "_8154_db50_get_int_factor" (ByVal CardId As Integer, IntFactorsInBit As Integer) As Integer
Declare Function B_8154_db50_wait_single_int Lib "8154.dll" Alias "_8154_db50_wait_single_int" (ByVal CardId As Integer, ByVal FactorBitNum As Integer, ByVal TimeOutMs As Long) As Integer
Declare Function B_8154_db50_reset_int Lib "8154.dll" Alias "_8154_db50_reset_int" (ByVal CardId As Integer, ByVal FactorBitNum As Integer) As Integer
'
' /****************************************************************************/
' /*     DB-8151  Function  Declerations                                      */
' /****************************************************************************/
'  Initialization and System Information Section
' _8154_db51_
Declare Function B_8154_db51_HSL_initial Lib "8154.dll" Alias "_8154_db51_HSL_initial" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_HSL_close Lib "8154.dll" Alias "_8154_db51_HSL_close" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_HSL_auto_start Lib "8154.dll" Alias "_8154_db51_HSL_auto_start" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_HSL_start Lib "8154.dll" Alias "_8154_db51_HSL_start" (ByVal card_ID As Integer, ByVal max_slave_No As Integer) As Integer
Declare Function B_8154_db51_HSL_stop Lib "8154.dll" Alias "_8154_db51_HSL_stop" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_HSL_connect_status Lib "8154.dll" Alias "_8154_db51_HSL_connect_status" (ByVal card_ID As Integer, ByVal slave_No As Integer, sts_data As Integer) As Integer
Declare Function B_8154_db51_HSL_slave_live Lib "8154.dll" Alias "_8154_db51_HSL_slave_live" (ByVal card_ID As Integer, ByVal slave_No As Integer, live_data As Integer) As Integer
Declare Function B_8154_db51_HSL_get_slave_type Lib "8154.dll" Alias "_8154_db51_HSL_get_slave_type" (ByVal card_ID As Integer, ByVal slave_No As Integer, type_data As Integer) As Integer
Declare Function B_8154_db51_HSL_set_scan_condition Lib "8154.dll" Alias "_8154_db51_HSL_set_scan_condition" (ByVal card_ID As Integer, ByVal transfer_rate As Integer, ByVal hub_number As Integer) As Integer
Declare Function B_8154_db51_HSL_get_scan_condition Lib "8154.dll" Alias "_8154_db51_HSL_get_scan_condition" (ByVal card_ID As Integer, transfer_rate As Integer, hub_number As Integer) As Integer
Declare Function B_8154_db51_HSL_get_version Lib "8154.dll" Alias "_8154_db51_HSL_get_version" (ByVal card_ID As Integer, Firmware_Version As Long, Driver_Version As Long, Software_Version As Long) As Integer
'
'  DIO
Declare Function B_8154_db51_HSL_D_write_output Lib "8154.dll" Alias "_8154_db51_HSL_D_write_output" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal out_data As Long) As Integer
Declare Function B_8154_db51_HSL_D_write_channel_output Lib "8154.dll" Alias "_8154_db51_HSL_D_write_channel_output" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, ByVal out_data As Integer) As Integer
Declare Function B_8154_db51_HSL_D_read_input Lib "8154.dll" Alias "_8154_db51_HSL_D_read_input" (ByVal card_ID As Integer, ByVal slave_No As Integer, in_data As Long) As Integer
Declare Function B_8154_db51_HSL_D_read_channel_input Lib "8154.dll" Alias "_8154_db51_HSL_D_read_channel_input" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, in_data As Integer) As Integer
Declare Function B_8154_db51_HSL_D_read_output Lib "8154.dll" Alias "_8154_db51_HSL_D_read_output" (ByVal card_ID As Integer, ByVal slave_No As Integer, out_data_in_ram As Long) As Integer
Declare Function B_8154_db51_HSL_D_read_all_slave_input Lib "8154.dll" Alias "_8154_db51_HSL_D_read_all_slave_input" (ByVal card_ID As Integer, in_data As Integer) As Integer
Declare Function B_8154_db51_HSL_D_write_all_slave_output Lib "8154.dll" Alias "_8154_db51_HSL_D_write_all_slave_output" (ByVal card_ID As Integer, out_data As Integer) As Integer
Declare Function B_8154_db51_HSL_D_set_input_logic Lib "8154.dll" Alias "_8154_db51_HSL_D_set_input_logic" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Input_Logic As Integer) As Integer
Declare Function B_8154_db51_HSL_D_set_output_logic Lib "8154.dll" Alias "_8154_db51_HSL_D_set_output_logic" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Output_Logic As Integer) As Integer
Declare Function B_8154_db51_HSL_D_write_slave_output Lib "8154.dll" Alias "_8154_db51_HSL_D_write_slave_output" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal out_data As Integer) As Integer
Declare Function B_8154_db51_HSL_D_read_slave_output Lib "8154.dll" Alias "_8154_db51_HSL_D_read_slave_output" (ByVal card_ID As Integer, ByVal slave_No As Integer, data_out As Integer) As Integer
Declare Function B_8154_db51_HSL_D_read_slave_input Lib "8154.dll" Alias "_8154_db51_HSL_D_read_slave_input" (ByVal card_ID As Integer, ByVal slave_No As Integer, data_in As Integer) As Integer
'
' DI INTERRUPT (ONLY FOR 7853/54)
Declare Function B_8154_db51_HSL_D_set_int_renewal_type Lib "8154.dll" Alias "_8154_db51_HSL_D_set_int_renewal_type" (ByVal card_ID As Integer, ByVal type_ As Integer) As Integer
Declare Function B_8154_db51_HSL_D_set_int_renewal_bit Lib "8154.dll" Alias "_8154_db51_HSL_D_set_int_renewal_bit" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal bitsOfCheck As Integer) As Integer
Declare Function B_8154_db51_HSL_D_set_int_control Lib "8154.dll" Alias "_8154_db51_HSL_D_set_int_control" (ByVal card_ID As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_db51_HSL_D_wait_di_interrupt Lib "8154.dll" Alias "_8154_db51_HSL_D_wait_di_interrupt" (ByVal card_ID As Integer, ByVal time_out_ms As Long) As Integer
'
'  FOR DI16-UL
Declare Function B_8154_db51_HSL_D_set_di_latch_function Lib "8154.dll" Alias "_8154_db51_HSL_D_set_di_latch_function" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, ByVal active_mode As Integer, ByVal duration As Integer) As Integer
Declare Function B_8154_db51_HSL_D_set_di_latch_functionA Lib "8154.dll" Alias "_8154_db51_HSL_D_set_di_latch_functionA" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal edge As Integer, ByVal duration As Integer) As Integer
Declare Function B_8154_db51_HSL_D_get_di_latch_function Lib "8154.dll" Alias "_8154_db51_HSL_D_get_di_latch_function" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, active_mode As Integer, duration As Integer) As Integer
'
'  AIO
Declare Function B_8154_db51_HSL_A_start_read Lib "8154.dll" Alias "_8154_db51_HSL_A_start_read" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_HSL_A_stop_read Lib "8154.dll" Alias "_8154_db51_HSL_A_stop_read" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_HSL_A_set_signal_range Lib "8154.dll" Alias "_8154_db51_HSL_A_set_signal_range" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal signal_range As Integer) As Integer
Declare Function B_8154_db51_HSL_A_get_signal_range Lib "8154.dll" Alias "_8154_db51_HSL_A_get_signal_range" (ByVal card_ID As Integer, ByVal slave_No As Integer, signal_range As Integer) As Integer
Declare Function B_8154_db51_HSL_A_get_input_mode Lib "8154.dll" Alias "_8154_db51_HSL_A_get_input_mode" (ByVal card_ID As Integer, ByVal slave_No As Integer, mode As Integer) As Integer
Declare Function B_8154_db51_HSL_A_set_last_channel Lib "8154.dll" Alias "_8154_db51_HSL_A_set_last_channel" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Last_Channel As Integer) As Integer
Declare Function B_8154_db51_HSL_A_get_last_channel Lib "8154.dll" Alias "_8154_db51_HSL_A_get_last_channel" (ByVal card_ID As Integer, ByVal slave_No As Integer, Last_Channel As Integer) As Integer
Declare Function B_8154_db51_HSL_A_read_input Lib "8154.dll" Alias "_8154_db51_HSL_A_read_input" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal ai_channel As Integer, AI_data As Double) As Integer
Declare Function B_8154_db51_HSL_A_write_output Lib "8154.dll" Alias "_8154_db51_HSL_A_write_output" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal ao_channel As Integer, ByVal AO_data As Double) As Integer
Declare Function B_8154_db51_HSL_A_read_output Lib "8154.dll" Alias "_8154_db51_HSL_A_read_output" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal ao_channel As Integer, AO_data As Double) As Integer
Declare Function B_8154_db51_HSL_A_sync_rw Lib "8154.dll" Alias "_8154_db51_HSL_A_sync_rw" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal ai_channel As Integer, AI_data As Double, ByVal ao_channel As Integer, ByVal AO_data As Double) As Integer
Declare Function B_8154_db51_HSL_A_get_version Lib "8154.dll" Alias "_8154_db51_HSL_A_get_version" (ByVal card_ID As Integer, ByVal slave_No As Integer, Ver As Integer) As Integer
'  AO4
Declare Function B_8154_db51_HSL_set_keep_mode Lib "8154.dll" Alias "_8154_db51_HSL_set_keep_mode" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal mode As Integer) As Integer
'
' /****************************************************************************/
'  The following function declarations are old                                                          */
' /****************************************************************************/
Declare Function B_8154_db51_W_HSL_Initial Lib "8154.dll" Alias "_8154_db51_W_HSL_Initial" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Close Lib "8154.dll" Alias "_8154_db51_W_HSL_Close" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Auto_Start Lib "8154.dll" Alias "_8154_db51_W_HSL_Auto_Start" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Start Lib "8154.dll" Alias "_8154_db51_W_HSL_Start" (ByVal card_ID As Integer, ByVal max_slave_No As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Stop Lib "8154.dll" Alias "_8154_db51_W_HSL_Stop" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Connect_Status Lib "8154.dll" Alias "_8154_db51_W_HSL_Connect_Status" (ByVal card_ID As Integer, ByVal slave_No As Integer, sts_data As Byte) As Integer
Declare Function B_8154_db51_W_HSL_Slave_Live Lib "8154.dll" Alias "_8154_db51_W_HSL_Slave_Live" (ByVal card_ID As Integer, ByVal slave_No As Integer, live_data As Byte) As Integer
'
Declare Function B_8154_db51_W_HSL_DIO_In Lib "8154.dll" Alias "_8154_db51_W_HSL_DIO_In" (ByVal card_ID As Integer, ByVal slave_No As Integer, in_data As Long) As Integer
Declare Function B_8154_db51_W_HSL_DIO_Channel_In Lib "8154.dll" Alias "_8154_db51_W_HSL_DIO_Channel_In" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, in_data As Integer) As Integer
Declare Function B_8154_db51_W_HSL_DIO_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_DIO_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal out_data As Long) As Integer
Declare Function B_8154_db51_W_HSL_DIO_Channel_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_DIO_Channel_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, ByVal out_data As Integer) As Integer
Declare Function B_8154_db51_W_HSL_DI8DO8_DIO_In Lib "8154.dll" Alias "_8154_db51_W_HSL_DI8DO8_DIO_In" (ByVal card_ID As Integer, ByVal slave_No As Integer, in_data As Integer) As Integer
Declare Function B_8154_db51_W_HSL_DI8DO8_DIO_Channel_In Lib "8154.dll" Alias "_8154_db51_W_HSL_DI8DO8_DIO_Channel_In" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, in_data As Integer) As Integer
Declare Function B_8154_db51_W_HSL_DI8DO8_DIO_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_DI8DO8_DIO_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal out_data As Integer) As Integer
Declare Function B_8154_db51_W_HSL_DI8DO8_DIO_Channel_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_DI8DO8_DIO_Channel_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, ByVal out_data As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Read_DIO_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_Read_DIO_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, out_data_in_ram As Long) As Integer
Declare Function B_8154_db51_W_HSL_Read_DIO_Channel_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_Read_DIO_Channel_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, out_channel_data_in_ram As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Read_DI8DO8_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_Read_DI8DO8_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, out_data_in_ram As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Read_DI8DO8_Channel_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_Read_DI8DO8_Channel_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, out_channel_data_in_ram As Integer) As Integer
Declare Function B_8154_db51_W_HSL_Set_In_Out_Logic Lib "8154.dll" Alias "_8154_db51_W_HSL_Set_In_Out_Logic" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Input_Logic As Integer, ByVal Output_Logic As Integer) As Integer
'
Declare Function B_8154_db51_W_HSL_AI_Start_Read Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_Start_Read" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_Stop_Read Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_Stop_Read" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_Channel_In Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_Channel_In" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, AI_data As Double) As Integer
Declare Function B_8154_db51_W_HSL_AI_SetConfig Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_SetConfig" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal signal_range As Integer, ByVal signal_type As Integer, ByVal cjc_status As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_GetConfig Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_GetConfig" (ByVal card_ID As Integer, ByVal slave_No As Integer, signal_range As Integer, signal_type As Integer, cjc_status As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_OffsetCalib Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_OffsetCalib" (ByVal card_ID As Integer, ByVal slave_No As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_SpanCalib Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_SpanCalib" (ByVal card_ID As Integer, ByVal slave_No As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_WriteDefault Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_WriteDefault" (ByVal card_ID As Integer, ByVal slave_No As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_SetCJCOffset Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_SetCJCOffset" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal CJC_data2 As Double) As Integer
Declare Function B_8154_db51_W_HSL_AI_GetCJCOffset Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_GetCJCOffset" (ByVal card_ID As Integer, ByVal slave_No As Integer, CJC_data As Double) As Integer
Declare Function B_8154_db51_W_HSL_AI_SetChannelStatus Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_SetChannelStatus" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal enable_chans As Long) As Integer
Declare Function B_8154_db51_W_HSL_AI_GetChannelStatus Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_GetChannelStatus" (ByVal card_ID As Integer, ByVal slave_No As Integer, enable_chans As Long) As Integer
'
Declare Function B_8154_db51_W_HSL_DIO_Memory_In Lib "8154.dll" Alias "_8154_db51_W_HSL_DIO_Memory_In" (ByVal card_ID As Integer, data_in As Integer) As Integer
Declare Function B_8154_db51_W_HSL_DIO_Memory_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_DIO_Memory_Out" (ByVal card_ID As Integer, data_out As Integer) As Integer
'
'  AI16AO2 Module Use
Declare Function B_8154_db51_W_HSL_AI_Set_Last_Channel Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_Set_Last_Channel" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Last_Channel As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_Get_Last_Channel Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_Get_Last_Channel" (ByVal card_ID As Integer, ByVal slave_No As Integer, Last_Channel As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AI_Get_Version Lib "8154.dll" Alias "_8154_db51_W_HSL_AI_Get_Version" (ByVal card_ID As Integer, ByVal slave_No As Integer, Ver As Byte) As Integer
Declare Function B_8154_db51_W_HSL_AIO_LoadConfig Lib "8154.dll" Alias "_8154_db51_W_HSL_AIO_LoadConfig" (ByVal card_ID As Integer, ByVal slave_No As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AIO_SaveConfig Lib "8154.dll" Alias "_8154_db51_W_HSL_AIO_SaveConfig" (ByVal card_ID As Integer, ByVal slave_No As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AO_Channel_Out Lib "8154.dll" Alias "_8154_db51_W_HSL_AO_Channel_Out" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal AO_Ch_No As Integer, ByVal AO_data As Double) As Integer
Declare Function B_8154_db51_W_HSL_AIO_Channel_InOut Lib "8154.dll" Alias "_8154_db51_W_HSL_AIO_Channel_InOut" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal AI_CH_No As Integer, AI_data As Double, ByVal AO_Ch_No As Integer, ByVal AO_data As Double) As Integer
Declare Function B_8154_db51_W_HSL_AO_Channel_In Lib "8154.dll" Alias "_8154_db51_W_HSL_AO_Channel_In" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal AO_Ch_No As Integer, AO_data As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AO_OffsetCalib Lib "8154.dll" Alias "_8154_db51_W_HSL_AO_OffsetCalib" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal DA_CH As Integer) As Integer
Declare Function B_8154_db51_W_HSL_AO_GainCalib Lib "8154.dll" Alias "_8154_db51_W_HSL_AO_GainCalib" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal DA_CH As Integer) As Integer
'
'  TC08 Use
Declare Function B_8154_db51_W_HSL_TC08_Offset_Calib Lib "8154.dll" Alias "_8154_db51_W_HSL_TC08_Offset_Calib" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer) As Integer
Declare Function B_8154_db51_W_HSL_TC08_Span_Calib Lib "8154.dll" Alias "_8154_db51_W_HSL_TC08_Span_Calib" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer) As Integer
Declare Function B_8154_db51_W_HSL_TC08_Get_Temperature Lib "8154.dll" Alias "_8154_db51_W_HSL_TC08_Get_Temperature" (ByVal card_ID As Integer, ByVal slave_No As Integer, ByVal Channel As Integer, ByVal TC_type As Integer, Temperature As Double) As Integer
'
'
' /****************************************************************************/
' /* HSL Motion Function Declerations                                        */
' /****************************************************************************/
Declare Function B_8154_db51_HSL_M_get_version Lib "8154.dll" Alias "_8154_db51_HSL_M_get_version" (ByVal card_ID As Integer, ByVal M_No As Integer, CPLD_Ver As Byte, Kernel_Ver As Long, Software_Ver As Long) As Integer
'
'  Pulse I/O Configuration
Declare Function B_8154_db51_HSL_M_set_pls_outmode Lib "8154.dll" Alias "_8154_db51_HSL_M_set_pls_outmode" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal pls_outmode As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_pls_iptmode Lib "8154.dll" Alias "_8154_db51_HSL_M_set_pls_iptmode" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal pls_iptmode As Integer, ByVal pls_logic As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_feedback_src Lib "8154.dll" Alias "_8154_db51_HSL_M_set_feedback_src" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Src As Integer) As Integer
'
'  Velocity Mode motion
Declare Function B_8154_db51_HSL_M_tv_move Lib "8154.dll" Alias "_8154_db51_HSL_M_tv_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_db51_HSL_M_sv_move Lib "8154.dll" Alias "_8154_db51_HSL_M_sv_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal SVacc As Double) As Integer
Declare Function B_8154_db51_HSL_M_v_change Lib "8154.dll" Alias "_8154_db51_HSL_M_v_change" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal NewVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_db51_HSL_M_sd_stop Lib "8154.dll" Alias "_8154_db51_HSL_M_sd_stop" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_emg_stop Lib "8154.dll" Alias "_8154_db51_HSL_M_emg_stop" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db51_HSL_M_fix_speed_range Lib "8154.dll" Alias "_8154_db51_HSL_M_fix_speed_range" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_unfix_speed_range Lib "8154.dll" Alias "_8154_db51_HSL_M_unfix_speed_range" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db51_HSL_M_get_current_speed Lib "8154.dll" Alias "_8154_db51_HSL_M_get_current_speed" (ByVal card_ID As Integer, ByVal AxisNo As Integer, speed As Double) As Integer
Declare Function B_8154_db51_HSL_M_verify_speed Lib "8154.dll" Alias "_8154_db51_HSL_M_verify_speed" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, minAccTime As Double, maxAccT As Double, ByVal MaxSpeed As Double) As Integer
'
'  Single Axis Motion
Declare Function B_8154_db51_HSL_M_start_tr_move Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_move Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_move Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_move Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_move_ratio Lib "8154.dll" Alias "_8154_db51_HSL_M_set_move_ratio" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal move_ratio As Double) As Integer
Declare Function B_8154_db51_HSL_M_p_change Lib "8154.dll" Alias "_8154_db51_HSL_M_p_change" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal NewPos As Double) As Integer
Declare Function B_8154_db51_HSL_M_backlash_comp Lib "8154.dll" Alias "_8154_db51_HSL_M_backlash_comp" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal BCompPulse As Integer, ByVal mode As Integer) As Integer
Declare Function B_8154_db51_HSL_M_suppress_vibration Lib "8154.dll" Alias "_8154_db51_HSL_M_suppress_vibration" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal T1 As Integer, ByVal T2 As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_idle_pulse Lib "8154.dll" Alias "_8154_db51_HSL_M_set_idle_pulse" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal idl_pulse As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_fa_speed Lib "8154.dll" Alias "_8154_db51_HSL_M_set_fa_speed" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal FA_Speed As Double) As Integer
'
'  Point Table
Declare Function B_8154_db51_HSL_M_set_point_data Lib "8154.dll" Alias "_8154_db51_HSL_M_set_point_data" (ByVal card_ID As Integer, ByVal Dimension As Integer, AxisArray As Integer, ByVal point_index As Integer, ByVal cmd_func As Integer, DistArray As Double, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_arc_data Lib "8154.dll" Alias "_8154_db51_HSL_M_set_arc_data" (ByVal card_ID As Integer, AxisArray As Integer, ByVal point_index As Integer, ByVal cmd_func As Integer, CenterArray As Double, EndArray As Double, ByVal DIR As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_move_point_range Lib "8154.dll" Alias "_8154_db51_HSL_M_move_point_range" (ByVal card_ID As Integer, ByVal Dimension As Integer, AxisArray As Integer, ByVal start_index As Integer, ByVal last_index As Integer) As Integer
Declare Function B_8154_db51_HSL_M_move_point_table Lib "8154.dll" Alias "_8154_db51_HSL_M_move_point_table" (ByVal card_ID As Integer, ByVal Dimension As Integer, AxisArray As Integer, PointArray As Integer, ByVal total_points As Integer) As Integer
'
'  Linear Interpolated Motion
Declare Function B_8154_db51_HSL_M_start_tr_move_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_move_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_move_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_move_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_move_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_move_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_move_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_move_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_tr_move_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_move_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_move_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_move_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_move_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_move_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_move_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_move_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_tr_line2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_line2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_line2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_line2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_line2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_line2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_line2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_line2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_tr_line3 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_line3" (ByVal card_ID As Integer, AxisArray As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal DistZ As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_line3 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_line3" (ByVal card_ID As Integer, AxisArray As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal PosZ As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_line3 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_line3" (ByVal card_ID As Integer, AxisArray As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal DistZ As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_line3 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_line3" (ByVal card_ID As Integer, AxisArray As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal PosZ As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_tr_line4 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_line4" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal DistZ As Double, ByVal DistU As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_line4 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_line4" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal PosZ As Double, ByVal PosU As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_line4 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_line4" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal DistX As Double, ByVal DistY As Double, ByVal DistZ As Double, ByVal DistU As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_line4 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_line4" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal PosX As Double, ByVal PosY As Double, ByVal PosZ As Double, ByVal PosU As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
'  Circular Interpolation Motion
Declare Function B_8154_db51_HSL_M_start_r_arc_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_r_arc_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_a_arc_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_a_arc_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_r_arc_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_r_arc_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_a_arc_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_a_arc_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_r_arc2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_r_arc2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_a_arc2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_a_arc2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_tr_arc_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_arc_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_arc_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_arc_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_arc_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_arc_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_arc_xy Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_arc_xy" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_tr_arc_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_arc_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_arc_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_arc_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_arc_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_arc_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_arc_zu Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_arc_zu" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_tr_arc2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_tr_arc2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_ta_arc2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_ta_arc2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sr_arc2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sr_arc2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_sa_arc2 Lib "8154.dll" Alias "_8154_db51_HSL_M_start_sa_arc2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
'
'  Home Return Mode
Declare Function B_8154_db51_HSL_M_set_home_config Lib "8154.dll" Alias "_8154_db51_HSL_M_set_home_config" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal home_mode As Integer, ByVal org_logic As Integer, ByVal ez_logic As Integer, ByVal ez_count As Integer, ByVal erc_out As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_org_offset Lib "8154.dll" Alias "_8154_db51_HSL_M_set_org_offset" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal ORG_ESC_Offset As Double) As Integer
Declare Function B_8154_db51_HSL_M_home_move Lib "8154.dll" Alias "_8154_db51_HSL_M_home_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_db51_HSL_M_escape_home Lib "8154.dll" Alias "_8154_db51_HSL_M_escape_home" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_db51_HSL_M_home_search Lib "8154.dll" Alias "_8154_db51_HSL_M_home_search" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal ORGOffset As Double) As Integer
'
'  Motion Status
Declare Function B_8154_db51_HSL_M_motion_done Lib "8154.dll" Alias "_8154_db51_HSL_M_motion_done" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db51_HSL_M_get_abnormal_stop_status Lib "8154.dll" Alias "_8154_db51_HSL_M_get_abnormal_stop_status" (ByVal card_ID As Integer, ByVal AxisNo As Integer, status As Long) As Integer
'
'  Motion Interface I/O
Declare Function B_8154_db51_HSL_M_set_alm Lib "8154.dll" Alias "_8154_db51_HSL_M_set_alm" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal alm_logic As Integer, ByVal alm_mode As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_el Lib "8154.dll" Alias "_8154_db51_HSL_M_set_el" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal el_mode As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_el_logic Lib "8154.dll" Alias "_8154_db51_HSL_M_set_el_logic" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal el_logic As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_inp Lib "8154.dll" Alias "_8154_db51_HSL_M_set_inp" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal inp_enable As Integer, ByVal inp_logic As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_erc Lib "8154.dll" Alias "_8154_db51_HSL_M_set_erc" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal erc_logic As Integer, ByVal erc_on_time As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_servo Lib "8154.dll" Alias "_8154_db51_HSL_M_set_servo" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal on_off As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_sd Lib "8154.dll" Alias "_8154_db51_HSL_M_set_sd" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal enable As Integer, ByVal sd_logic As Integer, ByVal sd_latch As Integer, ByVal sd_mode As Integer) As Integer
'
'  Motion I/O Monitoring
Declare Function B_8154_db51_HSL_M_get_io_status Lib "8154.dll" Alias "_8154_db51_HSL_M_get_io_status" (ByVal card_ID As Integer, ByVal AxisNo As Integer, io_sts As Integer) As Integer
'
'  Position Control and Counters
Declare Function B_8154_db51_HSL_M_get_position Lib "8154.dll" Alias "_8154_db51_HSL_M_get_position" (ByVal card_ID As Integer, ByVal AxisNo As Integer, Pos As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_position Lib "8154.dll" Alias "_8154_db51_HSL_M_set_position" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double) As Integer
Declare Function B_8154_db51_HSL_M_get_command Lib "8154.dll" Alias "_8154_db51_HSL_M_get_command" (ByVal card_ID As Integer, ByVal AxisNo As Integer, Cmd As Long) As Integer
Declare Function B_8154_db51_HSL_M_set_command Lib "8154.dll" Alias "_8154_db51_HSL_M_set_command" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Cmd As Long) As Integer
Declare Function B_8154_db51_HSL_M_get_error_counter Lib "8154.dll" Alias "_8154_db51_HSL_M_get_error_counter" (ByVal card_ID As Integer, ByVal AxisNo As Integer, error_counter As Integer) As Integer
Declare Function B_8154_db51_HSL_M_reset_error_counter Lib "8154.dll" Alias "_8154_db51_HSL_M_reset_error_counter" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db51_HSL_M_get_general_counter Lib "8154.dll" Alias "_8154_db51_HSL_M_get_general_counter" (ByVal card_ID As Integer, ByVal AxisNo As Integer, CntValue As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_general_counter Lib "8154.dll" Alias "_8154_db51_HSL_M_set_general_counter" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal CntSrc As Integer, ByVal CntValue As Double) As Integer
Declare Function B_8154_db51_HSL_M_get_target_pos Lib "8154.dll" Alias "_8154_db51_HSL_M_get_target_pos" (ByVal card_ID As Integer, ByVal AxisNo As Integer, Pos As Double) As Integer
Declare Function B_8154_db51_HSL_M_reset_target_pos Lib "8154.dll" Alias "_8154_db51_HSL_M_reset_target_pos" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double) As Integer
Declare Function B_8154_db51_HSL_M_get_rest_command Lib "8154.dll" Alias "_8154_db51_HSL_M_get_rest_command" (ByVal card_ID As Integer, ByVal AxisNo As Integer, rest_command As Long) As Integer
Declare Function B_8154_db51_HSL_M_check_rdp Lib "8154.dll" Alias "_8154_db51_HSL_M_check_rdp" (ByVal card_ID As Integer, ByVal AxisNo As Integer, rdp_command As Long) As Integer
'
'  Position Compare and Latch
Declare Function B_8154_db51_HSL_M_set_ltc_logic Lib "8154.dll" Alias "_8154_db51_HSL_M_set_ltc_logic" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal ltc_logic As Integer) As Integer
Declare Function B_8154_db51_HSL_M_get_latch_data Lib "8154.dll" Alias "_8154_db51_HSL_M_get_latch_data" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal LatchNo As Integer, Pos As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_soft_limit Lib "8154.dll" Alias "_8154_db51_HSL_M_set_soft_limit" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal PLimit As Long, ByVal NLimit As Long) As Integer
Declare Function B_8154_db51_HSL_M_enable_soft_limit Lib "8154.dll" Alias "_8154_db51_HSL_M_enable_soft_limit" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Action As Integer) As Integer
Declare Function B_8154_db51_HSL_M_disable_soft_limit Lib "8154.dll" Alias "_8154_db51_HSL_M_disable_soft_limit" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_error_counter_check Lib "8154.dll" Alias "_8154_db51_HSL_M_set_error_counter_check" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Tolerance As Integer, ByVal on_off As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_general_comparator Lib "8154.dll" Alias "_8154_db51_HSL_M_set_general_comparator" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal CmpSrc As Integer, ByVal CmpMethod As Integer, ByVal CmpAction As Integer, ByVal Data As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_trigger_comparator Lib "8154.dll" Alias "_8154_db51_HSL_M_set_trigger_comparator" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal CmpSrc As Integer, ByVal CmpMethod As Integer, ByVal Data As Double) As Integer
Declare Function B_8154_db51_HSL_M_check_compare_data Lib "8154.dll" Alias "_8154_db51_HSL_M_check_compare_data" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal CompType As Integer, Pos As Double) As Integer
Declare Function B_8154_db51_HSL_M_check_compare_status Lib "8154.dll" Alias "_8154_db51_HSL_M_check_compare_status" (ByVal card_ID As Integer, ByVal AxisNo As Integer, cmp_sts As Integer) As Integer
Declare Function B_8154_db51_HSL_M_build_compare_table Lib "8154.dll" Alias "_8154_db51_HSL_M_build_compare_table" (ByVal card_ID As Integer, ByVal AxisNo As Integer, TableArray As Double, ByVal ArraySize As Integer) As Integer
Declare Function B_8154_db51_HSL_M_build_compare_function Lib "8154.dll" Alias "_8154_db51_HSL_M_build_compare_function" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Start As Double, ByVal End_ As Double, ByVal Interval As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_auto_compare Lib "8154.dll" Alias "_8154_db51_HSL_M_set_auto_compare" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_compare_dir Lib "8154.dll" Alias "_8154_db51_HSL_M_set_compare_dir" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Inverse As Integer) As Integer
' I16 FNTYPE _8154_db51_HSL_M_set_compare_output_type(I16 card_ID, I16 AxisNo, I16 Normal_High_or_Low);
'
'  Multiple Axes Simultaneous Operation
Declare Function B_8154_db51_HSL_M_set_tr_move_all Lib "8154.dll" Alias "_8154_db51_HSL_M_set_tr_move_all" (ByVal card_ID As Integer, ByVal TotalAxes As Integer, AxisArray As Integer, DistA As Double, StrVelA As Double, MaxVelA As Double, TaccA As Double, TdecA As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_ta_move_all Lib "8154.dll" Alias "_8154_db51_HSL_M_set_ta_move_all" (ByVal card_ID As Integer, ByVal TotalAxes As Integer, AxisArray As Integer, PosA As Double, StrVelA As Double, MaxVelA As Double, TaccA As Double, TdecA As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_sa_move_all Lib "8154.dll" Alias "_8154_db51_HSL_M_set_sa_move_all" (ByVal card_ID As Integer, ByVal TotalAxes As Integer, AxisArray As Integer, PosA As Double, StrVelA As Double, MaxVelA As Double, TaccA As Double, TdecA As Double, SVaccA As Double, SVdecA As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_sr_move_all Lib "8154.dll" Alias "_8154_db51_HSL_M_set_sr_move_all" (ByVal card_ID As Integer, ByVal TotalAxes As Integer, AxisArray As Integer, DistA As Double, StrVelA As Double, MaxVelA As Double, TaccA As Double, TdecA As Double, SVaccA As Double, SVdecA As Double) As Integer
Declare Function B_8154_db51_HSL_M_start_move_all Lib "8154.dll" Alias "_8154_db51_HSL_M_start_move_all" (ByVal card_ID As Integer, ByVal FirstAxisNo As Integer) As Integer
Declare Function B_8154_db51_HSL_M_stop_move_all Lib "8154.dll" Alias "_8154_db51_HSL_M_stop_move_all" (ByVal card_ID As Integer, ByVal FirstAxisNo As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_sync_option Lib "8154.dll" Alias "_8154_db51_HSL_M_set_sync_option" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal sync_stop_on As Integer, ByVal cstop_output_on As Integer, ByVal sync_option1 As Integer, ByVal sync_option2 As Integer) As Integer
Declare Function B_8154_db51_HSL_M_set_sync_stop_mode Lib "8154.dll" Alias "_8154_db51_HSL_M_set_sync_stop_mode" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal stop_mode As Integer) As Integer
'
'  General-purposed DIO
Declare Function B_8154_db51_HSL_M_write_do Lib "8154.dll" Alias "_8154_db51_HSL_M_write_do" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal value As Integer) As Integer
Declare Function B_8154_db51_HSL_M_read_di Lib "8154.dll" Alias "_8154_db51_HSL_M_read_di" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
'
'  G code based function
' I16 FNTYPE _8154_db51_HSL_M_load_G_code(I16 card_ID, I16 M_No, char *filename);
Declare Function B_8154_db51_HSL_M_run_G_code Lib "8154.dll" Alias "_8154_db51_HSL_M_run_G_code" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal start_line_num As Integer) As Integer
Declare Function B_8154_db51_HSL_M_stop_G_code Lib "8154.dll" Alias "_8154_db51_HSL_M_stop_G_code" (ByVal card_ID As Integer, ByVal M_No As Integer) As Integer
Declare Function B_8154_db51_HSL_M_pause_G_code Lib "8154.dll" Alias "_8154_db51_HSL_M_pause_G_code" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal pause_line_num As Integer) As Integer
Declare Function B_8154_db51_HSL_M_resume_G_code Lib "8154.dll" Alias "_8154_db51_HSL_M_resume_G_code" (ByVal card_ID As Integer, ByVal M_No As Integer) As Integer
Declare Function B_8154_db51_HSL_M_get_current_G_line Lib "8154.dll" Alias "_8154_db51_HSL_M_get_current_G_line" (ByVal card_ID As Integer, ByVal M_No As Integer, current_line As Integer) As Integer
Declare Function B_8154_db51_HSL_M_map_G_code Lib "8154.dll" Alias "_8154_db51_HSL_M_map_G_code" (ByVal card_ID As Integer, ByVal M_No As Integer, ByVal G_Function As Integer, AxisArray As Integer, ByVal Motion_Function As Integer) As Integer
'
' /****************************************************************************/
' /*      Simplified Function  for HSL communication                          */
' /****************************************************************************/
'
'  Parameter Setting
Declare Function B_8154_db51_HSL_M_set_str_velocity Lib "8154.dll" Alias "_8154_db51_HSL_M_set_str_velocity" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_max_velocity Lib "8154.dll" Alias "_8154_db51_HSL_M_set_max_velocity" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_arc_velocity Lib "8154.dll" Alias "_8154_db51_HSL_M_set_arc_velocity" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Arc_MaxVel As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_Tacc Lib "8154.dll" Alias "_8154_db51_HSL_M_set_Tacc" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Tacc As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_Tdec Lib "8154.dll" Alias "_8154_db51_HSL_M_set_Tdec" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Tdec As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_SVacc Lib "8154.dll" Alias "_8154_db51_HSL_M_set_SVacc" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal SVacc As Double) As Integer
Declare Function B_8154_db51_HSL_M_set_SVdec Lib "8154.dll" Alias "_8154_db51_HSL_M_set_SVdec" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal SVdec As Double) As Integer
'
'  Single Axis Motion
Declare Function B_8154_db51_HSL_M_move_t_distance Lib "8154.dll" Alias "_8154_db51_HSL_M_move_t_distance" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Dist As Double) As Integer
Declare Function B_8154_db51_HSL_M_move_t_position Lib "8154.dll" Alias "_8154_db51_HSL_M_move_t_position" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double) As Integer
Declare Function B_8154_db51_HSL_M_move_s_distance Lib "8154.dll" Alias "_8154_db51_HSL_M_move_s_distance" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Dist As Double) As Integer
Declare Function B_8154_db51_HSL_M_move_s_position Lib "8154.dll" Alias "_8154_db51_HSL_M_move_s_position" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double) As Integer
'
'  Linear Interpolated Motion
Declare Function B_8154_db51_HSL_M_move_t_distance2 Lib "8154.dll" Alias "_8154_db51_HSL_M_move_t_distance2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal DistX As Double, ByVal DistY As Double) As Integer
Declare Function B_8154_db51_HSL_M_move_t_position2 Lib "8154.dll" Alias "_8154_db51_HSL_M_move_t_position2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal PosX As Double, ByVal PosY As Double) As Integer
Declare Function B_8154_db51_HSL_M_move_s_distance2 Lib "8154.dll" Alias "_8154_db51_HSL_M_move_s_distance2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal DistX As Double, ByVal DistY As Double) As Integer
Declare Function B_8154_db51_HSL_M_move_s_position2 Lib "8154.dll" Alias "_8154_db51_HSL_M_move_s_position2" (ByVal card_ID As Integer, AxisArray As Integer, ByVal PosX As Double, ByVal PosY As Double) As Integer
'
'  Circular Interpolation Motion
Declare Function B_8154_db51_HSL_M_move_t_arc2_distance Lib "8154.dll" Alias "_8154_db51_HSL_M_move_t_arc2_distance" (ByVal card_ID As Integer, AxisArray As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer) As Integer
Declare Function B_8154_db51_HSL_M_move_t_arc2_position Lib "8154.dll" Alias "_8154_db51_HSL_M_move_t_arc2_position" (ByVal card_ID As Integer, AxisArray As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer) As Integer
Declare Function B_8154_db51_HSL_M_move_s_arc2_distance Lib "8154.dll" Alias "_8154_db51_HSL_M_move_s_arc2_distance" (ByVal card_ID As Integer, AxisArray As Integer, ByVal OffsetCx As Double, ByVal OffsetCy As Double, ByVal OffsetEx As Double, ByVal OffsetEy As Double, ByVal DIR As Integer) As Integer
Declare Function B_8154_db51_HSL_M_move_s_arc2_position Lib "8154.dll" Alias "_8154_db51_HSL_M_move_s_arc2_position" (ByVal card_ID As Integer, AxisArray As Integer, ByVal Cx As Double, ByVal Cy As Double, ByVal Ex As Double, ByVal Ey As Double, ByVal DIR As Integer) As Integer
'
' /****************************************************************************/
' /*     DB-8152  Function  Declerations                                      */
' /****************************************************************************/
'  System Section x.1
Declare Function B_8154_db52_initial Lib "8154.dll" Alias "_8154_db52_initial" (ByVal CardId As Integer) As Integer
Declare Function B_8154_db52_close Lib "8154.dll" Alias "_8154_db52_close" (ByVal CardId As Integer) As Integer
Declare Function B_8154_db52_emg_stop Lib "8154.dll" Alias "_8154_db52_emg_stop" (ByVal CardId As Integer) As Integer
'
' Pulse Input/Output Configuration Section x.2
Declare Function B_8154_db52_set_master_pls_iptmode Lib "8154.dll" Alias "_8154_db52_set_master_pls_iptmode" (ByVal CardId As Integer, ByVal pls_InputMode As Integer) As Integer
Declare Function B_8154_db52_set_slave_pls_iptmode Lib "8154.dll" Alias "_8154_db52_set_slave_pls_iptmode" (ByVal CardId As Integer, ByVal pls_InputMode As Integer) As Integer
Declare Function B_8154_db52_set_slave_pls_outmode Lib "8154.dll" Alias "_8154_db52_set_slave_pls_outmode" (ByVal CardId As Integer, ByVal pls_outmode As Integer) As Integer
'
' ecam mode motion Section x.3
Declare Function B_8154_db52_get_start_position Lib "8154.dll" Alias "_8154_db52_get_start_position" (ByVal CardId As Integer, Master_Position As Long) As Integer
Declare Function B_8154_db52_set_start_position Lib "8154.dll" Alias "_8154_db52_set_start_position" (ByVal CardId As Integer, ByVal Master_Position As Long) As Integer
Declare Function B_8154_db52_start_ecam Lib "8154.dll" Alias "_8154_db52_start_ecam" (ByVal CardId As Integer, ByVal ecam_Type As Integer) As Integer
Declare Function B_8154_db52_stop_ecam Lib "8154.dll" Alias "_8154_db52_stop_ecam" (ByVal CardId As Integer, ByVal ecam_Type As Integer) As Integer
Declare Function B_8154_db52_build_ecam_table Lib "8154.dll" Alias "_8154_db52_build_ecam_table" (ByVal CardId As Integer, table_angle As Long, table_position As Long, ByVal table_size As Integer) As Integer
'
' slave Motion Section x.4
Declare Function B_8154_db52_slave_v_move Lib "8154.dll" Alias "_8154_db52_slave_v_move" (ByVal CardId As Integer, ByVal Vel As Long) As Integer
Declare Function B_8154_db52_slave_r_move Lib "8154.dll" Alias "_8154_db52_slave_r_move" (ByVal CardId As Integer, ByVal Dist As Long, ByVal Vel As Long) As Integer
Declare Function B_8154_db52_slave_home_move Lib "8154.dll" Alias "_8154_db52_slave_home_move" (ByVal CardId As Integer, ByVal Vel As Long) As Integer
Declare Function B_8154_db52_slave_stop Lib "8154.dll" Alias "_8154_db52_slave_stop" (ByVal CardId As Integer) As Integer
'
' Motion Interface I/O Section x.5
Declare Function B_8154_db52_set_EMG_logic Lib "8154.dll" Alias "_8154_db52_set_EMG_logic" (ByVal CardId As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db52_get_EMG_logic Lib "8154.dll" Alias "_8154_db52_get_EMG_logic" (ByVal CardId As Integer, Logic As Integer) As Integer
Declare Function B_8154_db52_set_ELL_logic Lib "8154.dll" Alias "_8154_db52_set_ELL_logic" (ByVal CardId As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db52_get_ELL_logic Lib "8154.dll" Alias "_8154_db52_get_ELL_logic" (ByVal CardId As Integer, Logic As Integer) As Integer
Declare Function B_8154_db52_set_ORG_logic Lib "8154.dll" Alias "_8154_db52_set_ORG_logic" (ByVal CardId As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db52_get_ORG_logic Lib "8154.dll" Alias "_8154_db52_get_ORG_logic" (ByVal CardId As Integer, Logic As Integer) As Integer
Declare Function B_8154_db52_set_ALM_logic Lib "8154.dll" Alias "_8154_db52_set_ALM_logic" (ByVal CardId As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db52_get_ALM_logic Lib "8154.dll" Alias "_8154_db52_get_ALM_logic" (ByVal CardId As Integer, Logic As Integer) As Integer
Declare Function B_8154_db52_set_INP_logic Lib "8154.dll" Alias "_8154_db52_set_INP_logic" (ByVal CardId As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db52_get_INP_logic Lib "8154.dll" Alias "_8154_db52_get_INP_logic" (ByVal CardId As Integer, Logic As Integer) As Integer
Declare Function B_8154_db52_set_EZ_logic Lib "8154.dll" Alias "_8154_db52_set_EZ_logic" (ByVal CardId As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db52_get_EZ_logic Lib "8154.dll" Alias "_8154_db52_get_EZ_logic" (ByVal CardId As Integer, Logic As Integer) As Integer
Declare Function B_8154_db52_set_ERC_logic Lib "8154.dll" Alias "_8154_db52_set_ERC_logic" (ByVal CardId As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db52_get_ERC_logic Lib "8154.dll" Alias "_8154_db52_get_ERC_logic" (ByVal CardId As Integer, Logic As Integer) As Integer
Declare Function B_8154_db52_set_erc Lib "8154.dll" Alias "_8154_db52_set_erc" (ByVal CardId As Integer, ByVal Logic As Integer) As Integer
Declare Function B_8154_db52_get_io_status Lib "8154.dll" Alias "_8154_db52_get_io_status" (ByVal CardId As Integer, io_sts As Integer) As Integer
'
' Interrupt Control Section x.6
Declare Function B_8154_db52_int_control Lib "8154.dll" Alias "_8154_db52_int_control" (ByVal CardId As Integer, ByVal intFlag As Integer) As Integer
Declare Function B_8154_db52_wait_error_interrupt Lib "8154.dll" Alias "_8154_db52_wait_error_interrupt" (ByVal CardId As Integer, ByVal TimeOut_ms As Long) As Integer
Declare Function B_8154_db52_wait_ecam_interrupt Lib "8154.dll" Alias "_8154_db52_wait_ecam_interrupt" (ByVal CardId As Integer, ByVal IntFactorBitNo As Integer, ByVal TimeOut_ms As Long) As Integer
Declare Function B_8154_db52_set_ecam_int_factor Lib "8154.dll" Alias "_8154_db52_set_ecam_int_factor" (ByVal CardId As Integer, ByVal int_factor As Integer) As Integer
'
' Position Control and Counters Section x.7
Declare Function B_8154_db52_get_master_position Lib "8154.dll" Alias "_8154_db52_get_master_position" (ByVal CardId As Integer, Position As Long) As Integer
Declare Function B_8154_db52_set_master_position Lib "8154.dll" Alias "_8154_db52_set_master_position" (ByVal CardId As Integer, ByVal Position As Long) As Integer
Declare Function B_8154_db52_get_slave_position Lib "8154.dll" Alias "_8154_db52_get_slave_position" (ByVal CardId As Integer, Position As Long) As Integer
Declare Function B_8154_db52_set_slave_position Lib "8154.dll" Alias "_8154_db52_set_slave_position" (ByVal CardId As Integer, ByVal Position As Long) As Integer
Declare Function B_8154_db52_get_command Lib "8154.dll" Alias "_8154_db52_get_command" (ByVal CardId As Integer, Command As Long) As Integer
Declare Function B_8154_db52_set_command Lib "8154.dll" Alias "_8154_db52_set_command" (ByVal CardId As Integer, ByVal Command As Long) As Integer
Declare Function B_8154_db52_get_res_command Lib "8154.dll" Alias "_8154_db52_get_res_command" (ByVal CardId As Integer, Command As Long) As Integer
Declare Function B_8154_db52_set_res_command Lib "8154.dll" Alias "_8154_db52_set_res_command" (ByVal CardId As Integer, ByVal Command As Long) As Integer
'
' Position Compare and Latch Section x.8
Declare Function B_8154_db52_get_EZ_latch_data Lib "8154.dll" Alias "_8154_db52_get_EZ_latch_data" (ByVal CardId As Integer, Latch_Position As Long) As Integer
Declare Function B_8154_db52_get_comparator_data Lib "8154.dll" Alias "_8154_db52_get_comparator_data" (ByVal CardId As Integer, ByVal CompNo As Integer, ByVal Comp_A_B As Integer, Comp_Data As Long) As Integer
Declare Function B_8154_db52_set_comparator_data Lib "8154.dll" Alias "_8154_db52_set_comparator_data" (ByVal CardId As Integer, ByVal CompNo As Integer, ByVal Comp_A_B As Integer, ByVal Comp_Data As Long) As Integer
Declare Function B_8154_db52_set_comparator_mode Lib "8154.dll" Alias "_8154_db52_set_comparator_mode" (ByVal CardId As Integer, ByVal CompNo As Integer, ByVal Comp_A_B As Integer, ByVal Comp_Mode As Integer) As Integer
Declare Function B_8154_db52_set_comparator_do Lib "8154.dll" Alias "_8154_db52_set_comparator_do" (ByVal CardId As Integer, ByVal CompNo As Integer, ByVal Logic As Integer) As Integer
'
' /****************************************************************************/
' /*      DB-8153  Function  Declerations                                     */
' /****************************************************************************/
'  Initialization and System Information Section
'  System Section 6.3
Declare Function B_8154_db53_initial Lib "8154.dll" Alias "_8154_db53_initial" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db53_close Lib "8154.dll" Alias "_8154_db53_close" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db53_auto_start Lib "8154.dll" Alias "_8154_db53_auto_start" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db53_stop Lib "8154.dll" Alias "_8154_db53_stop" (ByVal card_ID As Integer) As Integer
Declare Function B_8154_db53_get_slave_type Lib "8154.dll" Alias "_8154_db53_get_slave_type" (ByVal card_ID As Integer, ByVal slave_No As Integer, type_data As Integer) As Integer
Declare Function B_8154_db53_set_scan_condition Lib "8154.dll" Alias "_8154_db53_set_scan_condition" (ByVal card_ID As Integer, ByVal transfer_rate As Integer) As Integer
Declare Function B_8154_db53_get_scan_condition Lib "8154.dll" Alias "_8154_db53_get_scan_condition" (ByVal card_ID As Integer, transfer_rate As Integer) As Integer
Declare Function B_8154_db53_set_clock_rate Lib "8154.dll" Alias "_8154_db53_set_clock_rate" (ByVal card_ID As Integer, ByVal clock_rate As Integer) As Integer
Declare Function B_8154_db53_get_clock_rate Lib "8154.dll" Alias "_8154_db53_get_clock_rate" (ByVal card_ID As Integer, clock_rate As Integer) As Integer
Declare Function B_8154_db53_get_DBcpld_version Lib "8154.dll" Alias "_8154_db53_get_DBcpld_version" (ByVal card_ID As Integer, cpld_version As Integer) As Integer
Declare Function B_8154_db53_get_detected_modules_status Lib "8154.dll" Alias "_8154_db53_get_detected_modules_status" (ByVal card_ID As Integer, Maximum_Satellite As Integer, Detect_Module_No As Integer, Detect_Module_Type As Integer) As Integer
Declare Function B_8154_db53_M_get_AxisNo_mapto_SlaveNo Lib "8154.dll" Alias "_8154_db53_M_get_AxisNo_mapto_SlaveNo" (ByVal card_ID As Integer, ByVal AxisNo As Integer, slave_No As Integer) As Integer
Declare Function B_8154_db53_M_get_start_axisno Lib "8154.dll" Alias "_8154_db53_M_get_start_axisno" (ByVal card_ID As Integer, ByVal slave_No As Integer, start_axis As Integer) As Integer
Declare Function B_8154_db53_M_get_comm_errorflag Lib "8154.dll" Alias "_8154_db53_M_get_comm_errorflag" (ByVal card_ID As Integer, ByVal slave_No As Integer, errorflag As Integer) As Integer
'
' Pulse Input/Output Configuration Section 6.4
Declare Function B_8154_db53_M_set_pls_outmode Lib "8154.dll" Alias "_8154_db53_M_set_pls_outmode" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal pls_outmode As Integer) As Integer
Declare Function B_8154_db53_M_set_pls_iptmode Lib "8154.dll" Alias "_8154_db53_M_set_pls_iptmode" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal pls_iptmode As Integer, ByVal pls_logic As Integer) As Integer
Declare Function B_8154_db53_M_set_feedback_src Lib "8154.dll" Alias "_8154_db53_M_set_feedback_src" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Src As Integer) As Integer
'
' Velocity mode motion Section 6.5
Declare Function B_8154_db53_M_tv_move Lib "8154.dll" Alias "_8154_db53_M_tv_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_db53_M_sv_move Lib "8154.dll" Alias "_8154_db53_M_sv_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal SVacc As Double) As Integer
Declare Function B_8154_db53_M_sd_stop Lib "8154.dll" Alias "_8154_db53_M_sd_stop" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Tdec As Double) As Integer
Declare Function B_8154_db53_M_emg_stop Lib "8154.dll" Alias "_8154_db53_M_emg_stop" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db53_M_get_current_speed Lib "8154.dll" Alias "_8154_db53_M_get_current_speed" (ByVal card_ID As Integer, ByVal AxisNo As Integer, speed As Double) As Integer
Declare Function B_8154_db53_M_set_max_override_speed Lib "8154.dll" Alias "_8154_db53_M_set_max_override_speed" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal OvrdSpeed As Double, ByVal enable As Integer) As Integer
Declare Function B_8154_db53_M_v_change Lib "8154.dll" Alias "_8154_db53_M_v_change" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal NewVel As Double, ByVal Tacc As Double) As Integer
'
' Single Axis Position Mode Section 6.6
Declare Function B_8154_db53_M_start_tr_move Lib "8154.dll" Alias "_8154_db53_M_start_tr_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db53_M_start_ta_move Lib "8154.dll" Alias "_8154_db53_M_start_ta_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double) As Integer
Declare Function B_8154_db53_M_start_sr_move Lib "8154.dll" Alias "_8154_db53_M_start_sr_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db53_M_start_sa_move Lib "8154.dll" Alias "_8154_db53_M_start_sa_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double) As Integer
Declare Function B_8154_db53_M_set_move_ratio Lib "8154.dll" Alias "_8154_db53_M_set_move_ratio" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal move_ratio As Double) As Integer
'
' Home Return Mode Section 6.7
Declare Function B_8154_db53_M_set_home_config Lib "8154.dll" Alias "_8154_db53_M_set_home_config" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal home_mode As Integer, ByVal org_logic As Integer, ByVal ez_logic As Integer, ByVal ez_count As Integer, ByVal erc_out As Integer) As Integer
Declare Function B_8154_db53_M_home_move Lib "8154.dll" Alias "_8154_db53_M_home_move" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double) As Integer
Declare Function B_8154_db53_M_home_search Lib "8154.dll" Alias "_8154_db53_M_home_search" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal ORGOffset As Double) As Integer
'
' Motion Status Section 6.8
Declare Function B_8154_db53_M_motion_done Lib "8154.dll" Alias "_8154_db53_M_motion_done" (ByVal card_ID As Integer, ByVal AxisNo As Integer, M_sts As Integer) As Integer
'
' Motion Interface I/O Section 6.9
Declare Function B_8154_db53_M_set_servo Lib "8154.dll" Alias "_8154_db53_M_set_servo" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal on_off As Integer) As Integer
Declare Function B_8154_db53_M_set_pcs_logic Lib "8154.dll" Alias "_8154_db53_M_set_pcs_logic" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal pcs_logic As Integer) As Integer
Declare Function B_8154_db53_M_set_pcs Lib "8154.dll" Alias "_8154_db53_M_set_pcs" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_db53_M_set_clr_mode Lib "8154.dll" Alias "_8154_db53_M_set_clr_mode" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal clr_mode As Integer, ByVal targetCounterInBit As Integer) As Integer
Declare Function B_8154_db53_M_set_inp Lib "8154.dll" Alias "_8154_db53_M_set_inp" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal inp_enable As Integer, ByVal inp_logic As Integer) As Integer
Declare Function B_8154_db53_M_set_alm Lib "8154.dll" Alias "_8154_db53_M_set_alm" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal alm_logic As Integer, ByVal alm_mode As Integer) As Integer
Declare Function B_8154_db53_M_set_erc Lib "8154.dll" Alias "_8154_db53_M_set_erc" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal erc_logic As Integer, ByVal erc_pulse_width As Integer, ByVal erc_mode As Integer) As Integer
Declare Function B_8154_db53_M_set_erc_out Lib "8154.dll" Alias "_8154_db53_M_set_erc_out" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db53_M_clr_erc Lib "8154.dll" Alias "_8154_db53_M_clr_erc" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db53_M_set_sd Lib "8154.dll" Alias "_8154_db53_M_set_sd" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal sd_logic As Integer, ByVal sd_latch As Integer, ByVal sd_mode As Integer) As Integer
Declare Function B_8154_db53_M_enable_sd Lib "8154.dll" Alias "_8154_db53_M_enable_sd" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal enable As Integer) As Integer
Declare Function B_8154_db53_M_set_limit_mode Lib "8154.dll" Alias "_8154_db53_M_set_limit_mode" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal limit_mode As Integer) As Integer
Declare Function B_8154_db53_M_get_io_status Lib "8154.dll" Alias "_8154_db53_M_get_io_status" (ByVal card_ID As Integer, ByVal AxisNo As Integer, io_sts As Integer) As Integer
'
' Interrupt Control Section 6.10
'
' Position Control and Counters Section 6.11
Declare Function B_8154_db53_M_get_position Lib "8154.dll" Alias "_8154_db53_M_get_position" (ByVal card_ID As Integer, ByVal AxisNo As Integer, Pos As Double) As Integer
Declare Function B_8154_db53_M_set_position Lib "8154.dll" Alias "_8154_db53_M_set_position" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double) As Integer
Declare Function B_8154_db53_M_get_command Lib "8154.dll" Alias "_8154_db53_M_get_command" (ByVal card_ID As Integer, ByVal AxisNo As Integer, Cmd As Long) As Integer
Declare Function B_8154_db53_M_set_command Lib "8154.dll" Alias "_8154_db53_M_set_command" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Cmd As Long) As Integer
Declare Function B_8154_db53_M_get_error_counter Lib "8154.dll" Alias "_8154_db53_M_get_error_counter" (ByVal card_ID As Integer, ByVal AxisNo As Integer, error As Integer) As Integer
Declare Function B_8154_db53_M_reset_error_counter Lib "8154.dll" Alias "_8154_db53_M_reset_error_counter" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db53_M_get_target_pos Lib "8154.dll" Alias "_8154_db53_M_get_target_pos" (ByVal card_ID As Integer, ByVal AxisNo As Integer, Pos As Double) As Integer
Declare Function B_8154_db53_M_reset_target_pos Lib "8154.dll" Alias "_8154_db53_M_reset_target_pos" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double) As Integer
Declare Function B_8154_db53_M_set_res_distance Lib "8154.dll" Alias "_8154_db53_M_set_res_distance" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Res_Distance As Double) As Integer
Declare Function B_8154_db53_M_get_res_distance Lib "8154.dll" Alias "_8154_db53_M_get_res_distance" (ByVal card_ID As Integer, ByVal AxisNo As Integer, Res_Distance As Double) As Integer
'
' Position Compare and Latch Section 6.12
Declare Function B_8154_db53_M_set_error_comparator Lib "8154.dll" Alias "_8154_db53_M_set_error_comparator" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal CmpMethod As Integer, ByVal CmpAction As Integer, ByVal Data As Long) As Integer
Declare Function B_8154_db53_M_set_trigger_comparator Lib "8154.dll" Alias "_8154_db53_M_set_trigger_comparator" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal CmpSrc As Integer, ByVal CmpMethod As Integer, ByVal Data As Long) As Integer
Declare Function B_8154_db53_M_set_latch_source Lib "8154.dll" Alias "_8154_db53_M_set_latch_source" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal ltc_src As Integer) As Integer
Declare Function B_8154_db53_M_set_ltc_logic Lib "8154.dll" Alias "_8154_db53_M_set_ltc_logic" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal ltc_logic As Integer) As Integer
Declare Function B_8154_db53_M_get_latch_data Lib "8154.dll" Alias "_8154_db53_M_get_latch_data" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal CounterNo As Integer, Pos As Double) As Integer
'
' Soft Limit 6.13
Declare Function B_8154_db53_M_disable_soft_limit Lib "8154.dll" Alias "_8154_db53_M_disable_soft_limit" (ByVal card_ID As Integer, ByVal AxisNo As Integer) As Integer
Declare Function B_8154_db53_M_enable_soft_limit Lib "8154.dll" Alias "_8154_db53_M_enable_soft_limit" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Action As Integer) As Integer
Declare Function B_8154_db53_M_set_soft_limit Lib "8154.dll" Alias "_8154_db53_M_set_soft_limit" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Plus_Limit As Long, ByVal Neg_Limit As Long) As Integer
'
' Backlas Compensation / Vibration Suppression 6.14
Declare Function B_8154_db53_M_backlash_comp Lib "8154.dll" Alias "_8154_db53_M_backlash_comp" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal CompPulse As Integer, ByVal mode As Integer) As Integer
Declare Function B_8154_db53_M_suppress_vibration Lib "8154.dll" Alias "_8154_db53_M_suppress_vibration" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal ReverseTime As Integer, ByVal ForwardTime As Integer) As Integer
Declare Function B_8154_db53_M_set_fa_speed Lib "8154.dll" Alias "_8154_db53_M_set_fa_speed" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal FA_Speed As Double) As Integer
'
' Speed Profile Calculation 6.15
Declare Function B_8154_db53_M_get_tr_move_profile Lib "8154.dll" Alias "_8154_db53_M_get_tr_move_profile" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, pStrVel As Double, pMaxVel As Double, pTacc As Double, pTdec As Double, pTconst As Double) As Integer
Declare Function B_8154_db53_M_get_ta_move_profile Lib "8154.dll" Alias "_8154_db53_M_get_ta_move_profile" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, pStrVel As Double, pMaxVel As Double, pTacc As Double, pTdec As Double, pTconst As Double) As Integer
Declare Function B_8154_db53_M_get_sr_move_profile Lib "8154.dll" Alias "_8154_db53_M_get_sr_move_profile" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Dist As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double, pStrVel As Double, pMaxVel As Double, pTacc As Double, pTdec As Double, pSVacc As Double, pSVdec As Double, pTconst As Double) As Integer
Declare Function B_8154_db53_M_get_sa_move_profile Lib "8154.dll" Alias "_8154_db53_M_get_sa_move_profile" (ByVal card_ID As Integer, ByVal AxisNo As Integer, ByVal Pos As Double, ByVal StrVel As Double, ByVal MaxVel As Double, ByVal Tacc As Double, ByVal Tdec As Double, ByVal SVacc As Double, ByVal SVdec As Double, pStrVel As Double, pMaxVel As Double, pTacc As Double, pTdec As Double, pSVacc As Double, pSVdec As Double, pTconst As Double) As Integer
'
' #ifdef __cplusplus
' }
' #endif
'
' #endif
