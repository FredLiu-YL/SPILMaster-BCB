
#ifndef _P8154_1_H
#define _P8154_1_H

#define _MYWIN32

#include "type_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MYWIN32
#define FNTYPE PASCAL
#endif

// System Section 6.3
I16 FNTYPE _8154_initial(U16 *CardID_InBit, I16 Manual_ID);
I16 FNTYPE _8154_close(void);
I16 FNTYPE _8154_get_version(I16 CardId, I16 *firmware_ver, I32 *driver_ver, I32 *dll_ver);
I16 FNTYPE _8154_set_security_key(I16 CardId, I16 old_secu_code, I16 new_secu_code);
I16 FNTYPE _8154_check_security_key(I16 CardId, I16 secu_code);
I16 FNTYPE _8154_reset_security_key(I16 CardId);
I16 FNTYPE _8154_config_from_file();
I16 FNTYPE _8154_config_from_file2(char *Filename);
I16 FNTYPE _8154_get_DBboard_type(I16 CardId, I16 *DBtype);

//Pulse Input/Output Configuration Section 6.4
I16 FNTYPE _8154_set_pls_outmode(I16 AxisNo, I16 pls_outmode);
I16 FNTYPE _8154_set_pls_iptmode(I16 AxisNo, I16 pls_iptmode, I16 pls_logic);
I16 FNTYPE _8154_set_feedback_src(I16 AxisNo, I16 Src);

//Velocity mode motion Section 6.5
I16 FNTYPE _8154_tv_move(I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 FNTYPE _8154_sv_move(I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 SVacc);
I16 FNTYPE _8154_sd_stop(I16 AxisNo, F64 Tdec);
I16 FNTYPE _8154_emg_stop(I16 AxisNo);
I16 FNTYPE _8154_get_current_speed(I16 AxisNo, F64 *speed);
I16 FNTYPE _8154_speed_override(I16 CAxisNo, F64 NewVelPercent, F64 Time);
I16 FNTYPE _8154_speed_override2(I16 CAxisNo, F64 NewVel, F64 Time);
I16 FNTYPE _8154_set_max_override_speed(I16 AxisNo, F64 OvrdSpeed, I16 Enable);

//Single Axis Position Mode Section 6.6
I16 FNTYPE _8154_start_tr_move(I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_ta_move(I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_sr_move(I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_start_sa_move(I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_set_move_ratio(I16 AxisNo, F64 move_ratio);
I16 FNTYPE _8154_position_override(I16 AxisNo, F64 NewPos);

//Linear Interpolated Motion Section 6.7
  // Two Axes Linear Interpolation function
I16 FNTYPE _8154_start_tr_move_xy(I16 CardId, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_tr_move_zu(I16 CardId, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);

I16 FNTYPE _8154_start_ta_move_xy(I16 CardId, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_ta_move_zu(I16 CardId, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);

I16 FNTYPE _8154_start_sr_move_xy(I16 CardId, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_start_sr_move_zu(I16 CardId, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

I16 FNTYPE _8154_start_sa_move_xy(I16 CardId, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_start_sa_move_zu(I16 CardId, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

//Any 2 of former or later 4 axes linear interpolation function
I16 FNTYPE _8154_start_tr_line2(I16 *AxisArray, F64 *DistArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_ta_line2(I16 *AxisArray, F64 *PosArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_sr_line2(I16 *AxisArray, F64 *DistArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_start_sa_line2(I16 *AxisArray, F64 *PosArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

//Any 3 of former or later 4 axes linear interpolation function
I16 FNTYPE _8154_start_tr_line3(I16 *AxisArray, F64 *DistArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_ta_line3(I16 *AxisArray, F64 *PosArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_sr_line3(I16 *AxisArray, F64 *DistArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_start_sa_line3(I16 *AxisArray, F64 *PosArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

//Former or later 4 Axes linear interpolation function
I16 FNTYPE _8154_start_tr_line4(I16 *AxisArray, F64 *DistArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_ta_line4(I16 *AxisArray, F64 *PosArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_sr_line4(I16 *AxisArray, F64 *DistArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_start_sa_line4(I16 *AxisArray, F64 *PosArray, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
/*
I16 FNTYPE _8154_tv_line2(I16 *AxisArray, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 FNTYPE _8154_sv_line2(I16 *AxisArray,  F64 StrVel, F64 MaxVel, F64 Tacc, F64 SVacc);
*/

//Circular Interpolation Motion Section 6.8
  // Two Axes Arc Interpolation function
I16 FNTYPE _8154_start_tr_arc_xy(I16 CardId, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 FNTYPE _8154_start_ta_arc_xy(I16 CardId, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 FNTYPE _8154_start_sr_arc_xy(I16 CardId, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);
I16 FNTYPE _8154_start_sa_arc_xy(I16 CardId, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);

I16 FNTYPE _8154_start_tr_arc_zu(I16 CardId, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 FNTYPE _8154_start_ta_arc_zu(I16 CardId, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 FNTYPE _8154_start_sr_arc_zu(I16 CardId, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);
I16 FNTYPE _8154_start_sa_arc_zu(I16 CardId, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec,F64 SVacc,F64 SVdec);

I16 FNTYPE _8154_start_tr_arc2(I16 *AxisArray, F64 *OffsetCenter, F64 *OffsetEnd, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 FNTYPE _8154_start_ta_arc2(I16 *AxisArray, F64 *CenterPos, F64 *EndPos, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec);
I16 FNTYPE _8154_start_sr_arc2(I16 *AxisArray, F64 *OffsetCenter, F64 *OffsetEnd, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec, F64 SVacc,F64 SVdec);
I16 FNTYPE _8154_start_sa_arc2(I16 *AxisArray, F64 *CenterPos, F64 *EndPos, I16 CW_CCW, F64 StrVel,F64 MaxVel,F64 Tacc,F64 Tdec, F64 SVacc,F64 SVdec);

//Helical Interpolation Motion Section 6.9
I16 FNTYPE _8154_start_tr_helical(I16 card_id, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, F64 PitchDist, I16 CW_CCW, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_ta_helical(I16 card_id, F64 Cx, F64 Cy, F64 Ex, F64 Ey, F64 PitchPos, I16 CW_CCW, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_start_sr_helical(I16 card_id, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, F64 PitchDist, I16 CW_CCW, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_start_sa_helical(I16 card_id, F64 Cx, F64 Cy, F64 Ex, F64 Ey, F64 PitchPos, I16 CW_CCW, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);


//Home Return Mode Section 6.10
I16 FNTYPE _8154_set_home_config(I16 AxisNo, I16 home_mode, I16 org_logic, I16 ez_logic, I16 ez_count, I16 erc_out);
I16 FNTYPE _8154_home_move(I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 FNTYPE _8154_home_search(I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 ORGOffset);

//Manual Pulser Motion Section 6.11
I16 FNTYPE _8154_set_pulser_iptmode(I16 AxisNo, I16 InputMode, I16 Inverse);
I16 FNTYPE _8154_disable_pulser_input(I16 AxisNo, U16 Disable );
I16 FNTYPE _8154_pulser_vmove(I16 AxisNo, F64 SpeedLimit);
I16 FNTYPE _8154_pulser_pmove(I16 AxisNo, F64 Dist, F64 SpeedLimit);
I16 FNTYPE _8154_set_pulser_ratio(I16 AxisNo, I16 DivF, I16 MultiF);

//Motion Status Section 6.12
I16 FNTYPE _8154_motion_done(I16 AxisNo);

//Motion Interface I/O Section 6.13
I16 FNTYPE _8154_set_servo(I16 AxisNo, I16 on_off);
I16 FNTYPE _8154_set_pcs_logic(I16 AxisNo, I16 pcs_logic);
I16 FNTYPE _8154_set_pcs(I16 AxisNo, I16 enable);
I16 FNTYPE _8154_set_clr_mode(I16 AxisNo, I16 clr_mode, I16 targetCounterInBit);
I16 FNTYPE _8154_set_inp(I16 AxisNo, I16 inp_enable, I16 inp_logic);
I16 FNTYPE _8154_set_alm(I16 AxisNo, I16 alm_logic, I16 alm_mode);
I16 FNTYPE _8154_set_erc(I16 AxisNo, I16 erc_logic, I16 erc_pulse_width, I16 erc_mode);
I16 FNTYPE _8154_set_erc_out(I16 AxisNo);
I16 FNTYPE _8154_clr_erc(I16 AxisNo); 
I16 FNTYPE _8154_set_sd(I16 AxisNo, I16 sd_logic, I16 sd_latch, I16 sd_mode);
I16 FNTYPE _8154_enable_sd(I16 AxisNo, I16 enable);
I16 FNTYPE _8154_set_limit_logic(I16 AxisNo, I16 Logic );
I16 FNTYPE _8154_set_limit_mode(I16 AxisNo, I16 limit_mode);
I16 FNTYPE _8154_get_io_status(I16 AxisNo, U16 *io_sts);

//Interrupt Control Section 6.14
I16 FNTYPE _8154_int_control(I16 CardId, I16 intFlag);
I16 FNTYPE _8154_wait_error_interrupt(I16 AxisNo, I32 TimeOut_ms );
I16 FNTYPE _8154_wait_motion_interrupt(I16 AxisNo, I16 IntFactorBitNo, I32 TimeOut_ms );
I16 FNTYPE _8154_set_motion_int_factor(I16 AxisNo, U32 int_factor );

//Position Control and Counters Section 6.15
I16 FNTYPE _8154_get_position(I16 AxisNo, F64 *Pos);
I16 FNTYPE _8154_set_position(I16 AxisNo, F64 Pos);
I16 FNTYPE _8154_get_command(I16 AxisNo, I32 *Cmd);
I16 FNTYPE _8154_set_command(I16 AxisNo, I32 Cmd);
I16 FNTYPE _8154_get_error_counter(I16 AxisNo, I16 *error);
I16 FNTYPE _8154_reset_error_counter(I16 AxisNo);
I16 FNTYPE _8154_reset_counter_after_home(I16 AxisNo, I16 EnableByBit);
I16 FNTYPE _8154_set_general_counter(I16 AxisNo, I16 CntSrc, F64 CntValue);
I16 FNTYPE _8154_get_general_counter(I16 AxisNo, F64 *CntValue);
I16 FNTYPE _8154_reset_target_pos(I16 AxisNo, F64 TargetPos);
I16 FNTYPE _8154_get_target_pos(I16 AxisNo, F64 *TargetPos);
I16 FNTYPE _8154_set_res_distance(I16 AxisNo, F64 ResDistance);
I16 FNTYPE _8154_get_res_distance(I16 AxisNo, F64 *ResDistance);

//Position Compare and Latch Section 6.16
I16 FNTYPE _8154_set_do_cmp_output_selection(I16 CardId, I16 Channel, I16 DoCmpOutputSelection);
I16 FNTYPE _8154_set_trigger_logic(I16 AxisNo, I16 Logic);
I16 FNTYPE _8154_set_error_comparator(I16 AxisNo, I16 CmpMethod, I16 CmpAction, I32 Data);
I16 FNTYPE _8154_set_general_comparator(I16 AxisNo, I16 CmpSrc, I16 CmpMethod, I16 CmpAction, I32 Data);
I16 FNTYPE _8154_set_trigger_comparator(I16 AxisNo, I16 CmpSrc, I16 CmpMethod, I32 Data);
I16 FNTYPE _8154_set_latch_source(I16 AxisNo, I16 LtcSrc);
I16 FNTYPE _8154_set_ltc_logic(I16 AxisNo, I16 LtcLogic);
I16 FNTYPE _8154_get_latch_data(I16 AxisNo, I16 CounterNo, F64 *Pos);
I16 FNTYPE _8154_set_ring_counter( I16 AxisNo, I32 RingVal );
I16 FNTYPE _8154_get_ring_counter( I16 AxisNo, I32 *RingVal );

//Continuous Motion Section 6.17
I16 FNTYPE _8154_set_continuous_move(I16 AxisNo, I16 Enable);
I16 FNTYPE _8154_check_continuous_buffer(I16 AxisNo);
I16 FNTYPE _8154_dwell_move(I16 AxisNo, F64 milliSecond);

//Multiple Axes Simultaneous Operation Section 6.18
I16 FNTYPE _8154_set_tr_move_all(I16 TotalAxes, I16 *AxisArray, F64 *DistA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA);
I16 FNTYPE _8154_set_sa_move_all(I16 TotalAx, I16 *AxisArray, F64 *PosA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA, F64 *SVaccA, F64 *SVdecA);
I16 FNTYPE _8154_set_ta_move_all(I16 TotalAx, I16 *AxisArray, F64 *PosA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA);
I16 FNTYPE _8154_set_sr_move_all(I16 TotalAx, I16 *AxisArray, F64 *DistA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA, F64 *SVaccA, F64 *SVdecA);
I16 FNTYPE _8154_start_move_all(I16 FirstAxisNo);
I16 FNTYPE _8154_stop_move_all(I16 FirstAxisNo);
I16 FNTYPE _8154_set_sync_stop_mode(I16 AxisNo, I16 stop_mode);
I16 FNTYPE _8154_set_sync_option(I16 AxisNo, I16 sync_stop_on, I16 cstop_output_on, I16 sync_option1, I16 sync_option2);
I16 FNTYPE _8154_set_sync_signal_source(I16 AxisNo, I16 sync_axis);
I16 FNTYPE _8154_set_sync_signal_mode(I16 AxisNo, I16 mode);

//General-purposed Input/Output Section 6.19
I16 FNTYPE _8154_set_gpio_output(I16 CardId, I16 DoValue );
I16 FNTYPE _8154_get_gpio_output(I16 CardId, I16 *DoValue );
I16 FNTYPE _8154_get_gpio_input(I16 CardId, I16 *DiValue );
I16 FNTYPE _8154_set_gpio_input_function(I16 CardId, I16 Channel, I16 Select, I16 Logic);

//Extension 16 CH. General-Purposed Input/Output (Only support PCIe-8154)
I16 FNTYPE _8154_set_gpio_output_ex(I16 CardId, U16 Value);
I16 FNTYPE _8154_get_gpio_output_ex(I16 CardId, U16 *Value );
I16 FNTYPE _8154_get_gpio_input_ex(I16 CardId, U16 *Value );
I16 FNTYPE _8154_set_gpio_output_ex_CH(I16 CardId, I16 Channel, U16 Value );
I16 FNTYPE _8154_get_gpio_output_ex_CH(I16 CardId, I16 Channel, U16 *Value );
I16 FNTYPE _8154_get_gpio_input_ex_CH(I16 CardId, I16 Channel, U16 *Value );

//Soft Limit 6.20
I16 FNTYPE _8154_disable_soft_limit(I16 AxisNo);
I16 FNTYPE _8154_enable_soft_limit(I16 AxisNo, I16 Action);
I16 FNTYPE _8154_set_soft_limit(I16 AxisNo, I32 PlusLimit, I32 MinusLimit);
I16 FNTYPE _8154_check_soft_limit(I16 AxisNo, I16 *PlusLimit_sts, I16 *MinusLimit_sts);


//Backlas Compensation / Vibration Suppression 6.21
I16 FNTYPE _8154_backlash_comp(I16 AxisNo, I16 CompPulse, I16 Mode);
I16 FNTYPE _8154_suppress_vibration(I16 AxisNo, U16 ReverseTime, U16 ForwardTime);
I16 FNTYPE _8154_set_fa_speed(I16 AxisNo, F64 FA_Speed);

//Speed Profile Calculation 6.22
I16 FNTYPE _8154_get_tr_move_profile(I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 *pStrVel, F64 *pMaxVel, F64 *pTacc, F64 *pTdec, F64 *pTconst );
I16 FNTYPE _8154_get_ta_move_profile(I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 *pStrVel, F64 *pMaxVel, F64 *pTacc, F64 *pTdec, F64 *pTconst );
I16 FNTYPE _8154_get_sr_move_profile(I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec,F64 *pStrVel, F64 *pMaxVel, F64 *pTacc, F64 *pTdec, F64 *pSVacc, F64 *pSVdec, F64 *pTconst);
I16 FNTYPE _8154_get_sa_move_profile(I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec,F64 *pStrVel, F64 *pMaxVel, F64 *pTacc, F64 *pTdec, F64 *pSVacc, F64 *pSVdec, F64 *pTconst);

//Constant synthesized speed control 6.23
I16 FNTYPE _8154_set_axis_option(I16 AxisNo, I16 option);

/****************************************************************************/
/*      DB-8150  Function  Declerations                                              */
/****************************************************************************/
// Initialization and System Information Section
// System Section 5.2
I16 FNTYPE _8154_db50_initial( I16 CardId );
I16 FNTYPE _8154_db50_close( I16 CardId );
I16 FNTYPE _8154_db50_get_DBfpga_version( I16 CardId, I16 *Version );
I16 FNTYPE _8154_db50_get_PCB_version( I16 CardId, I16 *Version );

//Encoder & Counter: Section 5.3
I16 FNTYPE _8154_db50_set_encoder_input_mode( I16 CardId, I16 Channel, I16 IptMode );
I16 FNTYPE _8154_db50_set_encoder_value( I16 CardId, I16 Channel, I32 EncValue );
I16 FNTYPE _8154_db50_get_encoder_value( I16 CardId, I16 Channel, I32 *EncValue );
I16 FNTYPE _8154_db50_set_encoder_up_down_count(I16 CardId, I16 Channel, I16 Inverse );
I16 FNTYPE _8154_db50_set_ez_clear( I16 CardId, I16 Channel, I16 Enable, I16 ClrLogic );
I16 FNTYPE _8154_db50_set_counter_source( I16 CardId, I16 Channel, I16 CtnSrc );
I16 FNTYPE _8154_db50_enable_encoder_filter( I16 CardId, I16 Channel, I16 Enable );

//PWM Configuration: Section 5.4
I16 FNTYPE _8154_db50_set_pwm_source( I16 CardId, I16 Channel, I16 CmpEn, I16 LinearEn, I16 TimerEn );
I16 FNTYPE _8154_db50_set_pwm_mode( I16 CardId, I16 Channel, I16 PulseOrToggle );
I16 FNTYPE _8154_db50_set_pwm_pulse_width( I16 CardId, I16 Channel, I32 WidthPara );

//TRG-OUT Configuration: Section 5.5
I16 FNTYPE _8154_db50_set_trigger_source( I16 CardId, I16 TriggerLine, I16 Channel, I16 Enable);
I16 FNTYPE _8154_db50_set_trigger_logic( I16 CardId, I16 TriggerLine, I16 Logic );
I16 FNTYPE _8154_db50_reset_trigger_num( I16 CardId, I16 Channel );
I16 FNTYPE _8154_db50_get_trigger_num( I16 CardId, I16 Channel, F64 *TriggerNum );

// Comparator: Section 5.6
I16 FNTYPE _8154_db50_enable_comparator( I16 CardId, I16 Enable );
I16 FNTYPE _8154_db50_set_comparator_data( I16 CardId, I32 CmpData );
I16 FNTYPE _8154_db50_get_comparator_data( I16 CardId, I32 *CmpData );

//FIFO Comparing: Section 5.7
I16 FNTYPE _8154_db50_reset_fifo( I16 CardId );
I16 FNTYPE _8154_db50_get_fifo_status( I16 CardId, I16 *FifoSts );
I16 FNTYPE _8154_db50_set_fifo_array( I16 CardId, I32 ArraySize, I32 *DataArr, I16 ShiftFlag );
I16 FNTYPE _8154_db50_set_fifo_shift( I16 CardId );
I16 FNTYPE _8154_db50_set_fifo_low_level( I16 CardId, I16 Level ); 
I16 FNTYPE _8154_db50_get_fifo_low_level( I16 CardId, I16 *Level );

// Linear Comparing: Section 5.8
I16 FNTYPE _8154_db50_enable_linear_compare( I16 CardId, I16 Channel, I16 Enable );
I16 FNTYPE _8154_db50_set_linear_compare( I16 CardId, I16 Channel, I32 StartPoint, F64 RepeatTimes, I16 Interval );
I16 FNTYPE _8154_db50_get_linear_compare_data( I16 CardId, I16 Channel, F64 *CurrentData);

// Manual Trigger: Section 5.9
I16 FNTYPE _8154_db50_manual_trigger( I16 CardId, I16 Channel );

//General-purposed Input/Output Section 5.10
I16 FNTYPE _8154_db50_set_gpio_output(I16 CardId, I16 DoValue );
I16 FNTYPE _8154_db50_get_gpio_output(I16 CardId, I16 *DoValue );
I16 FNTYPE _8154_db50_get_di_sts( I16 CardId, I16 *DiStsInBit, I16 *EzStsInBit );

// Latch: Section 5.11
I16 FNTYPE _8154_db50_set_di_latch( I16 CardId, I16 Channel, I16 Enable, I16 EdgeSel );
I16 FNTYPE _8154_db50_get_di_latch_value(I16 CardId, I16 Channel, I32 *LatchValue );

// Timer: Section 5.12
I16 FNTYPE _8154_db50_set_Timer( I16 CardId, I16 Channel, I32 Interval );
I16 FNTYPE _8154_db50_start_timer( I16 CardId, I16 Channel, I16 Start );

// Interrupt: Section 5.13
I16 FNTYPE _8154_db50_set_int_control( I16 CardId, I16 intFlag );
I16 FNTYPE _8154_db50_set_int_factor( I16 CardId, I16 IntFactorsInBit );
I16 FNTYPE _8154_db50_get_int_factor( I16 CardId, I16 *IntFactorsInBit );
I16 FNTYPE _8154_db50_wait_single_int( I16 CardId, I16 FactorBitNum, I32 TimeOutMs );
I16 FNTYPE _8154_db50_reset_int( I16 CardId, I16 FactorBitNum ); 

/****************************************************************************/
/*     DB-8151  Function  Declerations                                      */
/****************************************************************************/
// Initialization and System Information Section
//_8154_db51_
I16 FNTYPE _8154_db51_HSL_initial(I16 card_ID);
I16 FNTYPE _8154_db51_HSL_close(I16 card_ID);
I16 FNTYPE _8154_db51_HSL_auto_start(I16 card_ID);
I16 FNTYPE _8154_db51_HSL_start(I16 card_ID, I16 max_slave_No);
I16 FNTYPE _8154_db51_HSL_stop(I16 card_ID);
I16 FNTYPE _8154_db51_HSL_connect_status(I16 card_ID, I16 slave_No, I16 *sts_data);
I16 FNTYPE _8154_db51_HSL_slave_live(I16 card_ID, I16 slave_No, I16 *live_data);
I16 FNTYPE _8154_db51_HSL_get_slave_type(I16 card_ID, I16 slave_No, U16 *type_data);
I16 FNTYPE _8154_db51_HSL_set_scan_condition(I16 card_ID, I16 transfer_rate, I16 hub_number);
I16 FNTYPE _8154_db51_HSL_get_scan_condition(I16 card_ID, I16 *transfer_rate, I16 *hub_number);
I16 FNTYPE _8154_db51_HSL_get_version(I16 card_ID, I32 *Firmware_Version, I32 *Driver_Version, I32 *Software_Version);

// DIO
I16 FNTYPE _8154_db51_HSL_D_write_output(I16 card_ID, I16 slave_No, U32 out_data);
I16 FNTYPE _8154_db51_HSL_D_write_channel_output(I16 card_ID, I16 slave_No, I16 channel, U16 out_data);
I16 FNTYPE _8154_db51_HSL_D_read_input(I16 card_ID, I16 slave_No, U32 *in_data);
I16 FNTYPE _8154_db51_HSL_D_read_channel_input(I16 card_ID, I16 slave_No, I16 channel, U16 *in_data);
I16 FNTYPE _8154_db51_HSL_D_read_output(I16 card_ID, I16 slave_No, U32 *out_data_in_ram);
I16 FNTYPE _8154_db51_HSL_D_read_all_slave_input(I16 card_ID, U16 *in_data);
I16 FNTYPE _8154_db51_HSL_D_write_all_slave_output(I16 card_ID, U16 *out_data);
I16 FNTYPE _8154_db51_HSL_D_set_input_logic(I16 card_ID, I16 slave_No, I16 input_logic);
I16 FNTYPE _8154_db51_HSL_D_set_output_logic(I16 card_ID, I16 slave_No, I16 output_logic);
I16 FNTYPE _8154_db51_HSL_D_write_slave_output(I16 card_ID, I16 slave_No, U16 out_data);
I16 FNTYPE _8154_db51_HSL_D_read_slave_output(U16 card_ID, I16 slave_No, U16 *data_out);
I16 FNTYPE _8154_db51_HSL_D_read_slave_input(U16 card_ID, I16 slave_No, U16 *data_in);

//DI INTERRUPT (ONLY FOR 7853/54)
I16 FNTYPE _8154_db51_HSL_D_set_int_renewal_type(I16 card_ID, I16 type);				
I16 FNTYPE _8154_db51_HSL_D_set_int_renewal_bit(I16 card_ID, I16 slave_No, U16 bitsOfCheck);
I16 FNTYPE _8154_db51_HSL_D_set_int_control(I16 card_ID, I16 enable);						
I16 FNTYPE _8154_db51_HSL_D_wait_di_interrupt(I16 card_ID, I32 time_out_ms);

// FOR DI16-UL
I16 FNTYPE _8154_db51_HSL_D_set_di_latch_function(I16 card_ID, I16 slave_No, I16 channel, I16 active_mode, I16 duration);
I16 FNTYPE _8154_db51_HSL_D_set_di_latch_functionA(I16 card_ID, I16 slave_No, I16 edge, I16 duration);
I16 FNTYPE _8154_db51_HSL_D_get_di_latch_function(I16 card_ID, I16 slave_No, I16 channel, I16 *active_mode, I16 *duration);

// AIO
I16 FNTYPE _8154_db51_HSL_A_start_read(I16 card_ID);
I16 FNTYPE _8154_db51_HSL_A_stop_read(I16 card_ID);
I16 FNTYPE _8154_db51_HSL_A_set_signal_range(I16 card_ID, I16 slave_No, I16 signal_range);
I16 FNTYPE _8154_db51_HSL_A_get_signal_range(I16 card_ID, I16 slave_No, I16 *signal_range);
I16 FNTYPE _8154_db51_HSL_A_get_input_mode(I16 card_ID, I16 slave_No, I16 *mode);
I16 FNTYPE _8154_db51_HSL_A_set_last_channel(I16 card_ID, I16 slave_No, I16 last_channel);
I16 FNTYPE _8154_db51_HSL_A_get_last_channel(I16 card_ID, I16 slave_No, I16 *last_channel);
I16 FNTYPE _8154_db51_HSL_A_read_input(I16 card_ID, I16 slave_No, I16 ai_channel, F64 *ai_data);
I16 FNTYPE _8154_db51_HSL_A_write_output(I16 card_ID, I16 slave_No, I16 ao_channel, F64 ao_data);
I16 FNTYPE _8154_db51_HSL_A_read_output(I16 card_ID, I16 slave_No, I16 ao_channel, F64 *ao_data);
I16 FNTYPE _8154_db51_HSL_A_sync_rw(I16 card_ID, I16 slave_No, I16 ai_channel, F64 *ai_data, I16 ao_channel, F64 ao_data);
I16 FNTYPE _8154_db51_HSL_A_get_version(I16 card_ID, I16 slave_No, I16 *ver);
// AO4
I16 FNTYPE _8154_db51_HSL_set_keep_mode(I16 card_ID, I16 slave_No, I16 Mode);

/****************************************************************************/
// The following function declarations are old								*/
/****************************************************************************/
U16 FNTYPE _8154_db51_W_HSL_Initial(U16 card_ID);
U16 FNTYPE _8154_db51_W_HSL_Close(U16 card_ID);
U16 FNTYPE _8154_db51_W_HSL_Auto_Start(U16 card_ID);
U16 FNTYPE _8154_db51_W_HSL_Start(U16 card_ID, U16 max_slave_No);
U16 FNTYPE _8154_db51_W_HSL_Stop(U16 card_ID);
U16 FNTYPE _8154_db51_W_HSL_Connect_Status(U16 card_ID, U16 slave_No, U8 *sts_data);
U16 FNTYPE _8154_db51_W_HSL_Slave_Live(U16 card_ID, U16 slave_No, U8 *live_data);

U16 FNTYPE _8154_db51_W_HSL_DIO_In(U16 card_ID, U16 slave_No, U32 *in_data);
U16 FNTYPE _8154_db51_W_HSL_DIO_Channel_In(U16 card_ID, U16 slave_No, U16 channel, U16 *in_data);
U16 FNTYPE _8154_db51_W_HSL_DIO_Out(U16 card_ID, U16 slave_No, U32 out_data);
U16 FNTYPE _8154_db51_W_HSL_DIO_Channel_Out(U16 card_ID, U16 slave_No, U16 channel, U16 out_data);
U16 FNTYPE _8154_db51_W_HSL_DI8DO8_DIO_In(U16 card_ID, U16 slave_No, U16 *in_data);
U16 FNTYPE _8154_db51_W_HSL_DI8DO8_DIO_Channel_In(U16 card_ID, U16 slave_No, U16 channel, U16 *in_data);
U16 FNTYPE _8154_db51_W_HSL_DI8DO8_DIO_Out(U16 card_ID, U16 slave_No, U16 out_data);
U16 FNTYPE _8154_db51_W_HSL_DI8DO8_DIO_Channel_Out(U16 card_ID, U16 slave_No, U16 channel, U16 out_data);
U16 FNTYPE _8154_db51_W_HSL_Read_DIO_Out(U16 card_ID, U16 slave_No, U32 *out_data_in_ram);
U16 FNTYPE _8154_db51_W_HSL_Read_DIO_Channel_Out(U16 card_ID, U16 slave_No, U16 channel, U16 *out_channel_data_in_ram);
U16 FNTYPE _8154_db51_W_HSL_Read_DI8DO8_Out(U16 card_ID, U16 slave_No, U16 *out_data_in_ram);
U16 FNTYPE _8154_db51_W_HSL_Read_DI8DO8_Channel_Out(U16 card_ID, U16 slave_No, U16 channel, U16 *out_channel_data_in_ram);
U16 FNTYPE _8154_db51_W_HSL_Set_In_Out_Logic(U16 card_ID, U16 slave_No, U16 Input_Logic, U16 Output_Logic);

U16 FNTYPE _8154_db51_W_HSL_AI_Start_Read(U16 card_ID);
U16 FNTYPE _8154_db51_W_HSL_AI_Stop_Read(U16 card_ID);
U16 FNTYPE _8154_db51_W_HSL_AI_Channel_In(U16 card_ID, U16 slave_No, U16 channel, F64 *ai_data);
U16 FNTYPE _8154_db51_W_HSL_AI_SetConfig(U16 card_ID, U16 slave_No, U16 signal_range, U16 signal_type, U16 cjc_status);
U16 FNTYPE _8154_db51_W_HSL_AI_GetConfig(U16 card_ID, U16 slave_No, U16 *signal_range, U16 *signal_type, U16 *cjc_status);
U16 FNTYPE _8154_db51_W_HSL_AI_OffsetCalib(U16 card_ID, U16 slave_No);
U16 FNTYPE _8154_db51_W_HSL_AI_SpanCalib(U16 card_ID, U16 slave_No);
U16 FNTYPE _8154_db51_W_HSL_AI_WriteDefault(U16 card_ID, U16 slave_No);
U16 FNTYPE _8154_db51_W_HSL_AI_SetCJCOffset(U16 card_ID, U16 slave_No, F64 CJC_data2);
U16 FNTYPE _8154_db51_W_HSL_AI_GetCJCOffset(U16 card_ID, U16 slave_No, F64 *CJC_data);
U16 FNTYPE _8154_db51_W_HSL_AI_SetChannelStatus(U16 card_ID, U16 slave_No, U32 enable_chans);
U16 FNTYPE _8154_db51_W_HSL_AI_GetChannelStatus(U16 card_ID, U16 slave_No, U32 *enable_chans);

U16 FNTYPE _8154_db51_W_HSL_DIO_Memory_In(U16 card_ID, U16 *data_in);
U16 FNTYPE _8154_db51_W_HSL_DIO_Memory_Out(U16 card_ID, U16 *data_out);

// AI16AO2 Module Use
U16 FNTYPE _8154_db51_W_HSL_AI_Set_Last_Channel(U16 card_ID, U16 slave_No, U16 Last_Channel); // Used to set last channel
U16 FNTYPE _8154_db51_W_HSL_AI_Get_Last_Channel(U16 card_ID, U16 slave_No, U16 *Last_Channel); // Used to set last channel
U16 FNTYPE _8154_db51_W_HSL_AI_Get_Version(U16 card_ID, U16 slave_No, U8 *Ver);
U16 FNTYPE _8154_db51_W_HSL_AIO_LoadConfig(U16 card_ID, U16 slave_No);
U16 FNTYPE _8154_db51_W_HSL_AIO_SaveConfig(U16 card_ID, U16 slave_No);
U16 FNTYPE _8154_db51_W_HSL_AO_Channel_Out(U16 card_ID, U16 slave_No, U16 AO_Ch_No, F64 AO_data);
U16 FNTYPE _8154_db51_W_HSL_AIO_Channel_InOut(U16 card_ID, U16 slave_No, U16 AI_CH_No, F64 *AI_data, U16 AO_Ch_No, F64 AO_data);
U16 FNTYPE _8154_db51_W_HSL_AO_Channel_In(U16 card_ID, U16 slave_No, U16 AO_Ch_No, U16 *AO_data);
U16 FNTYPE _8154_db51_W_HSL_AO_OffsetCalib(U16 card_ID, U16 slave_No, U16 DA_CH);
U16 FNTYPE _8154_db51_W_HSL_AO_GainCalib(U16 card_ID, U16 slave_No, U16 DA_CH);

// TC08 Use
U16 FNTYPE _8154_db51_W_HSL_TC08_Offset_Calib(U16 card_ID, U16 slave_No, U16 channel);
U16 FNTYPE _8154_db51_W_HSL_TC08_Span_Calib(U16 card_ID, U16 slave_No, U16 channel);
U16 FNTYPE _8154_db51_W_HSL_TC08_Get_Temperature(U16 card_ID, U16 slave_No, U16 channel, U16 TC_type, F64 *Temperature);


/****************************************************************************/
/* HSL Motion Function Declerations                                        */
/****************************************************************************/
I16 FNTYPE _8154_db51_HSL_M_get_version(I16 card_ID, I16 M_No, U8 *CPLD_Ver, U32 *Kernel_Ver, U32 *Software_Ver);

// Pulse I/O Configuration
I16 FNTYPE _8154_db51_HSL_M_set_pls_outmode(I16 card_ID, I16 AxisNo, I16 pls_outmode);
I16 FNTYPE _8154_db51_HSL_M_set_pls_iptmode(I16 card_ID, I16 AxisNo, I16 pls_iptmode, I16 pls_logic);
I16 FNTYPE _8154_db51_HSL_M_set_feedback_src(I16 card_ID, I16 AxisNo, I16 Src);

// Velocity Mode motion
I16 FNTYPE _8154_db51_HSL_M_tv_move(I16 card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 FNTYPE _8154_db51_HSL_M_sv_move(I16 card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 SVacc);
I16 FNTYPE _8154_db51_HSL_M_v_change(I16 card_ID, I16 AxisNo, F64 NewVel, F64 Tacc);
I16 FNTYPE _8154_db51_HSL_M_sd_stop(I16 card_ID, I16 AxisNo, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_emg_stop(I16 card_ID, I16 AxisNo);//ok
I16 FNTYPE _8154_db51_HSL_M_fix_speed_range(I16 card_ID, I16 AxisNo, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_unfix_speed_range(I16 card_ID, I16 AxisNo);
I16 FNTYPE _8154_db51_HSL_M_get_current_speed(I16 card_ID, I16 AxisNo, F64 *speed);
I16 FNTYPE _8154_db51_HSL_M_verify_speed(I16 card_ID, I16 M_No, F64 StrVel, F64 MaxVel, F64 *minAccTime, F64 *maxAccT, F64 MaxSpeed);

// Single Axis Motion
I16 FNTYPE _8154_db51_HSL_M_start_tr_move(I16 card_ID, I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_move(I16 card_ID, I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_move(I16 card_ID, I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_move(I16 card_ID, I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_set_move_ratio(I16 card_ID, I16 AxisNo, F64 move_ratio);
I16 FNTYPE _8154_db51_HSL_M_p_change(I16 card_ID, I16 AxisNo, F64 NewPos);
I16 FNTYPE _8154_db51_HSL_M_backlash_comp(I16 card_ID, I16 AxisNo, I16 BCompPulse, I16 Mode);
I16 FNTYPE _8154_db51_HSL_M_suppress_vibration(I16 card_ID, I16 AxisNo, U16 T1, U16 T2);
I16 FNTYPE _8154_db51_HSL_M_set_idle_pulse(I16 card_ID, I16 AxisNo, I16 idl_pulse);
I16 FNTYPE _8154_db51_HSL_M_set_fa_speed(I16 card_ID, I16 AxisNo, F64 FA_Speed);

// Point Table
I16 FNTYPE _8154_db51_HSL_M_set_point_data(I16 card_ID, I16 Dimension, I16 *AxisArray, I16 point_index, I16 cmd_func, F64 *DistArray, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_set_arc_data(I16 card_ID, I16 *AxisArray, I16 point_index, I16 cmd_func, F64 *CenterArray, F64 *EndArray, I16 DIR, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_move_point_range(I16 card_ID, I16 Dimension, I16 *AxisArray, I16 start_index, I16 last_index);
I16 FNTYPE _8154_db51_HSL_M_move_point_table(I16 card_ID, I16 Dimension, I16 *AxisArray, I16 *PointArray, I16 total_points);

// Linear Interpolated Motion
I16 FNTYPE _8154_db51_HSL_M_start_tr_move_xy(I16 card_ID, I16 M_No, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_move_xy(I16 card_ID, I16 M_No, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_move_xy(I16 card_ID, I16 M_No, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_move_xy(I16 card_ID, I16 M_No, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_tr_move_zu(I16 card_ID, I16 M_No, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_move_zu(I16 card_ID, I16 M_No, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_move_zu(I16 card_ID, I16 M_No, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_move_zu(I16 card_ID, I16 M_No, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_tr_line2(I16 card_ID, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_line2(I16 card_ID, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_line2(I16 card_ID, I16 *AxisArray, F64 DistX, F64 DistY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_line2(I16 card_ID, I16 *AxisArray, F64 PosX, F64 PosY, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_tr_line3(I16 card_ID, I16 *AxisArray, F64 DistX, F64 DistY, F64 DistZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_line3(I16 card_ID, I16 *AxisArray, F64 PosX, F64 PosY, F64 PosZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_line3(I16 card_ID, I16 *AxisArray, F64 DistX, F64 DistY, F64 DistZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_line3(I16 card_ID, I16 *AxisArray, F64 PosX, F64 PosY, F64 PosZ, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_tr_line4(I16 card_ID, I16 M_No, F64 DistX, F64 DistY, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_line4(I16 card_ID, I16 M_No, F64 PosX, F64 PosY, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_line4(I16 card_ID, I16 M_No, F64 DistX, F64 DistY, F64 DistZ, F64 DistU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_line4(I16 card_ID, I16 M_No, F64 PosX, F64 PosY, F64 PosZ, F64 PosU, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

// Circular Interpolation Motion
I16 FNTYPE _8154_db51_HSL_M_start_r_arc_xy(I16 card_ID, I16 M_No, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_start_a_arc_xy(I16 card_ID, I16 M_No, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_start_r_arc_zu(I16 card_ID, I16 M_No, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_start_a_arc_zu(I16 card_ID, I16 M_No, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_start_r_arc2(I16 card_ID, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_start_a_arc2(I16 card_ID, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_start_tr_arc_xy(I16 card_ID, I16 M_No, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_arc_xy(I16 card_ID, I16 M_No, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_arc_xy(I16 card_ID, I16 M_No, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_arc_xy(I16 card_ID, I16 M_No, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_tr_arc_zu(I16 card_ID, I16 M_No, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_arc_zu(I16 card_ID, I16 M_No, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_arc_zu(I16 card_ID, I16 M_No, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_arc_zu(I16 card_ID, I16 M_No, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_tr_arc2(I16 card_ID, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_ta_arc2(I16 card_ID, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_start_sr_arc2(I16 card_ID, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db51_HSL_M_start_sa_arc2(I16 card_ID, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);

// Home Return Mode
I16 FNTYPE _8154_db51_HSL_M_set_home_config(I16 card_ID, I16 AxisNo, I16 home_mode, I16 org_logic, I16 ez_logic, I16 ez_count, I16 erc_out);
I16 FNTYPE _8154_db51_HSL_M_set_org_offset(I16 card_ID, I16 AxisNo, F64 ORG_ESC_Offset);
I16 FNTYPE _8154_db51_HSL_M_home_move(I16 card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 FNTYPE _8154_db51_HSL_M_escape_home(I16 card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 FNTYPE _8154_db51_HSL_M_home_search(I16 card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 ORGOffset);

// Motion Status
I16 FNTYPE _8154_db51_HSL_M_motion_done(I16 card_ID, I16 AxisNo);
I16 FNTYPE _8154_db51_HSL_M_get_abnormal_stop_status(I16 card_ID, I16 AxisNo, I32 *status);

// Motion Interface I/O
I16 FNTYPE _8154_db51_HSL_M_set_alm(I16 card_ID, I16 AxisNo, I16 alm_logic, I16 alm_mode);
I16 FNTYPE _8154_db51_HSL_M_set_el(I16 card_ID, I16 AxisNo, I16 el_mode);
I16 FNTYPE _8154_db51_HSL_M_set_el_logic(I16 card_ID, I16 AxisNo, I16 el_logic);
I16 FNTYPE _8154_db51_HSL_M_set_inp(I16 card_ID, I16 AxisNo, I16 inp_enable, I16 inp_logic);
I16 FNTYPE _8154_db51_HSL_M_set_erc(I16 card_ID, I16 AxisNo, I16 erc_logic, I16 erc_on_time);
I16 FNTYPE _8154_db51_HSL_M_set_servo(I16 card_ID, I16 AxisNo, I16 on_off);
I16 FNTYPE _8154_db51_HSL_M_set_sd(I16 card_ID, I16 AxisNo, I16 enable, I16 sd_logic, I16 sd_latch, I16 sd_mode);

// Motion I/O Monitoring
I16 FNTYPE _8154_db51_HSL_M_get_io_status(I16 card_ID, I16 AxisNo, U16 *io_sts);

// Position Control and Counters
I16 FNTYPE _8154_db51_HSL_M_get_position(I16 card_ID, I16 AxisNo, F64 *pos);
I16 FNTYPE _8154_db51_HSL_M_set_position(I16 card_ID, I16 AxisNo, F64 pos);
I16 FNTYPE _8154_db51_HSL_M_get_command(I16 card_ID, I16 AxisNo, I32 *cmd);
I16 FNTYPE _8154_db51_HSL_M_set_command(I16 card_ID, I16 AxisNo, I32 cmd);
I16 FNTYPE _8154_db51_HSL_M_get_error_counter(I16 card_ID, I16 AxisNo, I16 *error_counter);
I16 FNTYPE _8154_db51_HSL_M_reset_error_counter(I16 card_ID, I16 AxisNo);
I16 FNTYPE _8154_db51_HSL_M_get_general_counter(I16 card_ID, I16 AxisNo, F64 *CntValue);
I16 FNTYPE _8154_db51_HSL_M_set_general_counter(I16 card_ID, I16 AxisNo, I16 CntSrc, F64 CntValue);
I16 FNTYPE _8154_db51_HSL_M_get_target_pos(I16 card_ID, I16 AxisNo, F64 *pos);
I16 FNTYPE _8154_db51_HSL_M_reset_target_pos(I16 card_ID, I16 AxisNo, F64 pos);
I16 FNTYPE _8154_db51_HSL_M_get_rest_command(I16 card_ID, I16 AxisNo, I32 *rest_command);
I16 FNTYPE _8154_db51_HSL_M_check_rdp(I16 card_ID, I16 AxisNo, I32 *rdp_command);

// Position Compare and Latch
I16 FNTYPE _8154_db51_HSL_M_set_ltc_logic(I16 card_ID, I16 AxisNo, I16 ltc_logic);
I16 FNTYPE _8154_db51_HSL_M_get_latch_data(I16 card_ID, I16 AxisNo, I16 LatchNo, F64 *Pos);
I16 FNTYPE _8154_db51_HSL_M_set_soft_limit(I16 card_ID, I16 AxisNo, I32 PLimit, I32 NLimit);
I16 FNTYPE _8154_db51_HSL_M_enable_soft_limit(I16 card_ID, I16 AxisNo, I16 Action);
I16 FNTYPE _8154_db51_HSL_M_disable_soft_limit(I16 card_ID, I16 AxisNo);
I16 FNTYPE _8154_db51_HSL_M_set_error_counter_check(I16 card_ID, I16 AxisNo, I16 Tolerance, I16 On_Off);
I16 FNTYPE _8154_db51_HSL_M_set_general_comparator(I16 card_ID, I16 AxisNo, I16 CmpSrc, I16 CmpMethod, I16 CmpAction, F64 Data);
I16 FNTYPE _8154_db51_HSL_M_set_trigger_comparator(I16 card_ID, I16 AxisNo, I16 CmpSrc, I16 CmpMethod, F64 Data);
I16 FNTYPE _8154_db51_HSL_M_check_compare_data(I16 card_ID, I16 AxisNo, I16 CompType, F64 *Pos);
I16 FNTYPE _8154_db51_HSL_M_check_compare_status(I16 card_ID, I16 AxisNo, U16 *cmp_sts);
I16 FNTYPE _8154_db51_HSL_M_build_compare_table(I16 card_ID, I16 AxisNo, F64 *TableArray, I16 ArraySize);
I16 FNTYPE _8154_db51_HSL_M_build_compare_function(I16 card_ID, I16 AxisNo, F64 Start, F64 End, F64 Interval);
I16 FNTYPE _8154_db51_HSL_M_set_auto_compare(I16 card_ID, I16 AxisNo, I16 Enable);
I16 FNTYPE _8154_db51_HSL_M_set_compare_dir(I16 card_ID, I16 AxisNo, I16 Inverse);
//I16 FNTYPE _8154_db51_HSL_M_set_compare_output_type(I16 card_ID, I16 AxisNo, I16 Normal_High_or_Low);
  
// Multiple Axes Simultaneous Operation
I16 FNTYPE _8154_db51_HSL_M_set_tr_move_all(I16 card_ID, I16 TotalAxes, I16 *AxisArray, F64 *DistA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA);
I16 FNTYPE _8154_db51_HSL_M_set_ta_move_all(I16 card_ID, I16 TotalAxes, I16 *AxisArray, F64 *PosA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA);
I16 FNTYPE _8154_db51_HSL_M_set_sa_move_all(I16 card_ID, I16 TotalAxes, I16 *AxisArray, F64 *PosA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA, F64 *SVaccA, F64 *SVdecA);
I16 FNTYPE _8154_db51_HSL_M_set_sr_move_all(I16 card_ID, I16 TotalAxes, I16 *AxisArray, F64 *DistA, F64 *StrVelA, F64 *MaxVelA, F64 *TaccA, F64 *TdecA, F64 *SVaccA, F64 *SVdecA);
I16 FNTYPE _8154_db51_HSL_M_start_move_all(I16 card_ID, I16 FirstAxisNo);
I16 FNTYPE _8154_db51_HSL_M_stop_move_all(I16 card_ID, I16 FirstAxisNo);
I16 FNTYPE _8154_db51_HSL_M_set_sync_option(I16 card_ID, I16 AxisNo, I16 sync_stop_on, I16 cstop_output_on, I16 sync_option1, I16 sync_option2);
I16 FNTYPE _8154_db51_HSL_M_set_sync_stop_mode(I16 card_ID, I16 AxisNo, I16 stop_mode);

// General-purposed DIO
I16 FNTYPE _8154_db51_HSL_M_write_do(I16 card_ID, I16 AxisNo, U16 value);
U16 FNTYPE _8154_db51_HSL_M_read_di(I16 card_ID, I16 AxisNo);

// G code based function
I16 FNTYPE _8154_db51_HSL_M_load_G_code(I16 card_ID, I16 M_No, char *filename);
I16 FNTYPE _8154_db51_HSL_M_run_G_code(I16 card_ID, I16 M_No, I16 start_line_num);
I16 FNTYPE _8154_db51_HSL_M_stop_G_code (I16 card_ID, I16 M_No);
I16 FNTYPE _8154_db51_HSL_M_pause_G_code (I16 card_ID, I16 M_No, I16 pause_line_num);
I16 FNTYPE _8154_db51_HSL_M_resume_G_code (I16 card_ID, I16 M_No);
I16 FNTYPE _8154_db51_HSL_M_get_current_G_line (I16 card_ID, I16 M_No, I16 *current_line);
I16 FNTYPE _8154_db51_HSL_M_map_G_code(I16 card_ID, I16 M_No, I16 G_Function, I16 *AxisArray, I16 Motion_Function);

/****************************************************************************/
/*      Simplified Function  for HSL communication                          */
/****************************************************************************/

// Parameter Setting
I16 FNTYPE _8154_db51_HSL_M_set_str_velocity(I16 card_ID, I16 AxisNo, F64 StrVel);
I16 FNTYPE _8154_db51_HSL_M_set_max_velocity(I16 card_ID, I16 AxisNo, F64 MaxVel);
I16 FNTYPE _8154_db51_HSL_M_set_arc_velocity(I16 card_ID, I16 AxisNo, F64 Arc_MaxVel);
I16 FNTYPE _8154_db51_HSL_M_set_Tacc(I16 card_ID, I16 AxisNo, F64 Tacc);
I16 FNTYPE _8154_db51_HSL_M_set_Tdec(I16 card_ID, I16 AxisNo, F64 Tdec);
I16 FNTYPE _8154_db51_HSL_M_set_SVacc(I16 card_ID, I16 AxisNo, F64 SVacc);
I16 FNTYPE _8154_db51_HSL_M_set_SVdec(I16 card_ID, I16 AxisNo, F64 SVdec);

// Single Axis Motion
I16 FNTYPE _8154_db51_HSL_M_move_t_distance(I16 card_ID, I16 AxisNo, F64 Dist);
I16 FNTYPE _8154_db51_HSL_M_move_t_position(I16 card_ID, I16 AxisNo, F64 Pos);
I16 FNTYPE _8154_db51_HSL_M_move_s_distance(I16 card_ID, I16 AxisNo, F64 Dist);
I16 FNTYPE _8154_db51_HSL_M_move_s_position(I16 card_ID, I16 AxisNo, F64 Pos);

// Linear Interpolated Motion
I16 FNTYPE _8154_db51_HSL_M_move_t_distance2(I16 card_ID, I16 *AxisArray, F64 DistX, F64 DistY);
I16 FNTYPE _8154_db51_HSL_M_move_t_position2(I16 card_ID, I16 *AxisArray, F64 PosX, F64 PosY);
I16 FNTYPE _8154_db51_HSL_M_move_s_distance2(I16 card_ID, I16 *AxisArray, F64 DistX, F64 DistY);
I16 FNTYPE _8154_db51_HSL_M_move_s_position2(I16 card_ID, I16 *AxisArray, F64 PosX, F64 PosY);

// Circular Interpolation Motion
I16 FNTYPE _8154_db51_HSL_M_move_t_arc2_distance(I16 card_ID, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR);
I16 FNTYPE _8154_db51_HSL_M_move_t_arc2_position(I16 card_ID, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR);
I16 FNTYPE _8154_db51_HSL_M_move_s_arc2_distance(I16 card_ID, I16 *AxisArray, F64 OffsetCx, F64 OffsetCy, F64 OffsetEx, F64 OffsetEy, I16 DIR);
I16 FNTYPE _8154_db51_HSL_M_move_s_arc2_position(I16 card_ID, I16 *AxisArray, F64 Cx, F64 Cy, F64 Ex, F64 Ey, I16 DIR);

/****************************************************************************/
/*     DB-8152  Function  Declerations                                      */
/****************************************************************************/
// System Section x.1
I16 FNTYPE _8154_db52_initial(I16 CardId);
I16 FNTYPE _8154_db52_close(I16 CardId);
I16 FNTYPE _8154_db52_emg_stop(I16 CardId);

//Pulse Input/Output Configuration Section x.2
I16 FNTYPE _8154_db52_set_master_pls_iptmode(I16 CardId, I16 pls_InputMode);
I16 FNTYPE _8154_db52_set_slave_pls_iptmode(I16 CardId, I16 pls_InputMode);
I16 FNTYPE _8154_db52_set_slave_pls_outmode(I16 CardId, I16 pls_outmode);

//ecam mode motion Section x.3
I16 FNTYPE _8154_db52_get_start_position(I16 CardId, I32 *Master_Position);
I16 FNTYPE _8154_db52_set_start_position(I16 CardId, I32 Master_Position);
I16 FNTYPE _8154_db52_start_ecam(I16 CardId, I16 ecam_Type);
I16 FNTYPE _8154_db52_stop_ecam(I16 CardId, I16 ecam_Type);
I16 FNTYPE _8154_db52_build_ecam_table(I16 CardId, I32 *table_angle, I32 *table_position, I16 table_size);

//slave Motion Section x.4
I16 FNTYPE _8154_db52_slave_v_move(I16 CardId, I32 Vel);  //  Vel set to RFL; dir:0 positive  dir:1 negative
I16 FNTYPE _8154_db52_slave_r_move(I16 CardId, I32 Dist, I32 Vel);  //  Dist set to RMV ;Vel set to RFL; dir:0 positive  dir:1 negative
I16 FNTYPE _8154_db52_slave_home_move(I16 CardId, I32 Vel);  //  Vel set to RFL; dir:0 positive  dir:1 negative
I16 FNTYPE _8154_db52_slave_stop(I16 CardId); 

//Motion Interface I/O Section x.5
I16 FNTYPE _8154_db52_set_EMG_logic(I16 CardId, I16 logic);  //  defalt need to set 1
I16 FNTYPE _8154_db52_get_EMG_logic(I16 CardId, I16 *logic);  
I16 FNTYPE _8154_db52_set_ELL_logic(I16 CardId, I16 logic);  //  defalt need to set 0
I16 FNTYPE _8154_db52_get_ELL_logic(I16 CardId, I16 *logic); 
I16 FNTYPE _8154_db52_set_ORG_logic(I16 CardId, I16 logic);  //  defalt set 0 Negative logic
I16 FNTYPE _8154_db52_get_ORG_logic(I16 CardId, I16 *logic);
I16 FNTYPE _8154_db52_set_ALM_logic(I16 CardId, I16 logic);  //  defalt set 0 Negative logic
I16 FNTYPE _8154_db52_get_ALM_logic(I16 CardId, I16 *logic); 
I16 FNTYPE _8154_db52_set_INP_logic(I16 CardId, I16 logic);  //  defalt set 0 Negative logic
I16 FNTYPE _8154_db52_get_INP_logic(I16 CardId, I16 *logic);
I16 FNTYPE _8154_db52_set_EZ_logic(I16 CardId, I16 logic);  //   defalt set 0 Negative logic
I16 FNTYPE _8154_db52_get_EZ_logic(I16 CardId, I16 *logic); 
I16 FNTYPE _8154_db52_set_ERC_logic(I16 CardId, I16 logic);  //  defalt set 0 Negative logic
I16 FNTYPE _8154_db52_get_ERC_logic(I16 CardId, I16 *logic);
I16 FNTYPE _8154_db52_set_erc(I16 CardId, I16 logic); 
I16 FNTYPE _8154_db52_get_io_status(I16 CardId, I16 *io_sts); 

//Interrupt Control Section x.6
I16 FNTYPE _8154_db52_int_control(I16 CardId, I16 intFlag);
I16 FNTYPE _8154_db52_wait_error_interrupt(I16 CardId, I32 TimeOut_ms );
I16 FNTYPE _8154_db52_wait_ecam_interrupt(I16 CardId, I16 IntFactorBitNo, I32 TimeOut_ms );
I16 FNTYPE _8154_db52_set_ecam_int_factor(I16 CardId, I16 int_factor );

//Position Control and Counters Section x.7
I16 FNTYPE _8154_db52_get_master_position(I16 CardId, I32 *Position);
I16 FNTYPE _8154_db52_set_master_position(I16 CardId, I32 Position);
I16 FNTYPE _8154_db52_get_slave_position(I16 CardId, I32 *Position);
I16 FNTYPE _8154_db52_set_slave_position(I16 CardId, I32 Position);
I16 FNTYPE _8154_db52_get_command(I16 CardId, I32 *Command);
I16 FNTYPE _8154_db52_set_command(I16 CardId, I32 Command);
I16 FNTYPE _8154_db52_get_res_command(I16 CardId, I32 *Command); 
I16 FNTYPE _8154_db52_set_res_command(I16 CardId, I32 Command); 

//Position Compare and Latch Section x.8
I16 FNTYPE _8154_db52_get_EZ_latch_data(I16 CardId, I32 *Latch_Position);
I16 FNTYPE _8154_db52_get_comparator_data(I16 CardId, I16 CompNo, I16 Comp_A_B, I32 *Comp_Data);
I16 FNTYPE _8154_db52_set_comparator_data(I16 CardId, I16 CompNo, I16 Comp_A_B, I32 Comp_Data);
I16 FNTYPE _8154_db52_set_comparator_mode(I16 CardId, I16 CompNo, I16 Comp_A_B, I16 Comp_Mode);
I16 FNTYPE _8154_db52_set_comparator_do(I16 CardId, I16 CompNo, I16 logic);

/****************************************************************************/
/*      DB-8153  Function  Declerations                                     */
/****************************************************************************/
// Initialization and System Information Section
// System Section 6.3
I16 FNTYPE _8154_db53_initial(I16 Card_ID);
I16 FNTYPE _8154_db53_close(I16 Card_ID);
I16 FNTYPE _8154_db53_auto_start(I16 Card_ID);
I16 FNTYPE _8154_db53_stop(I16 Card_ID);
I16 FNTYPE _8154_db53_get_slave_type(I16 Card_ID, I16 slave_No, I16 *type_data);
I16 FNTYPE _8154_db53_set_scan_condition(I16 Card_ID, I16 transfer_rate);
I16 FNTYPE _8154_db53_get_scan_condition(I16 Card_ID, I16 *transfer_rate);
I16 FNTYPE _8154_db53_set_clock_rate(I16 Card_ID, I16 clock_rate);
I16 FNTYPE _8154_db53_get_clock_rate(I16 Card_ID, I16 *clock_rate);
I16 FNTYPE _8154_db53_get_DBcpld_version(I16 Card_ID, I16 *cpld_version);
I16 FNTYPE _8154_db53_get_detected_modules_status(I16 Card_ID, I16 *Maximum_Satellite, I16 *Detect_Module_No, I16 *Detect_Module_Type);
I16 FNTYPE _8154_db53_M_get_AxisNo_mapto_SlaveNo(I16 Card_ID, I16 AxisNo, I16 *Slave_No);
I16 FNTYPE _8154_db53_M_get_start_axisno(I16 Card_ID, I16 Slave_No, I16 *start_axis);
I16 FNTYPE _8154_db53_M_get_comm_errorflag(I16 Card_ID, I16 slave_No, I16 *errorflag);

//Pulse Input/Output Configuration Section 6.4
I16 FNTYPE _8154_db53_M_set_pls_outmode(I16 Card_ID, I16 AxisNo, I16 pls_outmode);
I16 FNTYPE _8154_db53_M_set_pls_iptmode(I16 Card_ID, I16 AxisNo, I16 pls_iptmode, I16 pls_logic);
I16 FNTYPE _8154_db53_M_set_feedback_src(I16 Card_ID, I16 AxisNo, I16 Src);

//Velocity mode motion Section 6.5
I16 FNTYPE _8154_db53_M_tv_move(I16 Card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 FNTYPE _8154_db53_M_sv_move(I16 Card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 SVacc);
I16 FNTYPE _8154_db53_M_sd_stop(I16 Card_ID, I16 AxisNo, F64 Tdec);
I16 FNTYPE _8154_db53_M_emg_stop(I16 Card_ID, I16 AxisNo);
I16 FNTYPE _8154_db53_M_get_current_speed(I16 Card_ID, I16 AxisNo, F64 *speed);
I16 FNTYPE _8154_db53_M_set_max_override_speed(I16 Card_ID, I16 AxisNo, F64 OvrdSpeed, I16 Enable);
I16 FNTYPE _8154_db53_M_v_change(I16 Card_ID, I16 AxisNo, F64 NewVel, F64 Tacc);

//Single Axis Position Mode Section 6.6
I16 FNTYPE _8154_db53_M_start_tr_move(I16 Card_ID, I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db53_M_start_ta_move(I16 Card_ID, I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec);
I16 FNTYPE _8154_db53_M_start_sr_move(I16 Card_ID, I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db53_M_start_sa_move(I16 Card_ID, I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec);
I16 FNTYPE _8154_db53_M_set_move_ratio(I16 Card_ID, I16 AxisNo, F64 move_ratio);

//Home Return Mode Section 6.7
I16 FNTYPE _8154_db53_M_set_home_config(I16 Card_ID, I16 AxisNo, I16 home_mode, I16 org_logic, I16 ez_logic, I16 ez_count, I16 erc_out);
I16 FNTYPE _8154_db53_M_home_move(I16 Card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc);
I16 FNTYPE _8154_db53_M_home_search(I16 Card_ID, I16 AxisNo, F64 StrVel, F64 MaxVel, F64 Tacc, F64 ORGOffset);

//Motion Status Section 6.8
I16 FNTYPE _8154_db53_M_motion_done(I16 Card_ID, I16 AxisNo, I16 *M_sts);

//Motion Interface I/O Section 6.9
I16 FNTYPE _8154_db53_M_set_servo(I16 Card_ID, I16 AxisNo, I16 on_off);
I16 FNTYPE _8154_db53_M_reset_alm(I16 Card_ID, I16 AxisNo, I16 on_off);
I16 FNTYPE _8154_db53_M_set_pcs_logic(I16 Card_ID, I16 AxisNo, I16 pcs_logic);
I16 FNTYPE _8154_db53_M_set_pcs(I16 Card_ID, I16 AxisNo, I16 enable);
I16 FNTYPE _8154_db53_M_set_clr_mode(I16 Card_ID, I16 AxisNo, I16 clr_mode, I16 targetCounterInBit);
I16 FNTYPE _8154_db53_M_set_inp(I16 Card_ID, I16 AxisNo, I16 inp_enable, I16 inp_logic);
I16 FNTYPE _8154_db53_M_set_alm(I16 Card_ID, I16 AxisNo, I16 alm_logic, I16 alm_mode);
I16 FNTYPE _8154_db53_M_set_erc(I16 Card_ID, I16 AxisNo, I16 erc_logic, I16 erc_pulse_width, I16 erc_mode);
I16 FNTYPE _8154_db53_M_set_erc_out(I16 Card_ID, I16 AxisNo);
I16 FNTYPE _8154_db53_M_clr_erc(I16 Card_ID, I16 AxisNo);
I16 FNTYPE _8154_db53_M_set_sd(I16 Card_ID, I16 AxisNo, I16 sd_logic, I16 sd_latch, I16 sd_mode);
I16 FNTYPE _8154_db53_M_enable_sd(I16 Card_ID, I16 AxisNo, I16 enable);
I16 FNTYPE _8154_db53_M_set_limit_mode(I16 Card_ID, I16 AxisNo, I16 limit_mode);
I16 FNTYPE _8154_db53_M_get_io_status(I16 Card_ID, I16 AxisNo, U16 *io_sts);

//Interrupt Control Section 6.10 

//Position Control and Counters Section 6.11
I16 FNTYPE _8154_db53_M_get_position(I16 Card_ID, I16 AxisNo, F64 *Pos);
I16 FNTYPE _8154_db53_M_set_position(I16 Card_ID, I16 AxisNo, F64 Pos);
I16 FNTYPE _8154_db53_M_get_command(I16 Card_ID, I16 AxisNo, I32 *Cmd);
I16 FNTYPE _8154_db53_M_set_command(I16 Card_ID, I16 AxisNo, I32 Cmd);
I16 FNTYPE _8154_db53_M_get_error_counter(I16 Card_ID, I16 AxisNo, I16 *error);
I16 FNTYPE _8154_db53_M_reset_error_counter(I16 Card_ID, I16 AxisNo);
I16 FNTYPE _8154_db53_M_get_target_pos(I16 Card_ID, I16 AxisNo, F64 *pos);
I16 FNTYPE _8154_db53_M_reset_target_pos(I16 Card_ID, I16 AxisNo, F64 Pos);
I16 FNTYPE _8154_db53_M_set_res_distance(I16 Card_ID, I16 AxisNo, F64 Res_Distance);
I16 FNTYPE _8154_db53_M_get_res_distance(I16 Card_ID, I16 AxisNo, F64 *Res_Distance);

//Position Compare and Latch Section 6.12
I16 FNTYPE _8154_db53_M_set_error_comparator(I16 Card_ID, I16 AxisNo, I16 CmpMethod, I16 CmpAction, I32 Data);
I16 FNTYPE _8154_db53_M_set_trigger_comparator(I16 Card_ID, I16 AxisNo, I16 CmpSrc, I16 CmpMethod, I32 Data);
I16 FNTYPE _8154_db53_M_set_latch_source(I16 Card_ID, I16 AxisNo, I16 ltc_src);
I16 FNTYPE _8154_db53_M_set_ltc_logic(I16 Card_ID, I16 AxisNo, I16 ltc_logic);
I16 FNTYPE _8154_db53_M_get_latch_data(I16 Card_ID, I16 AxisNo, I16 CounterNo, F64 *Pos);
I16 FNTYPE _8154_db53_M_check_compare_status(I16 Card_ID, I16 AxisNo, U16 *Cmp_sts);
I16 FNTYPE _8154_db53_M_check_compare_data(I16 Card_ID, I16 AxisNo, I16 CompType, F64 *Pos);

//Soft Limit 6.13
I16 FNTYPE _8154_db53_M_disable_soft_limit(I16 Card_ID, I16 AxisNo);
I16 FNTYPE _8154_db53_M_enable_soft_limit(I16 Card_ID, I16 AxisNo, I16 Action);
I16 FNTYPE _8154_db53_M_set_soft_limit(I16 Card_ID, I16 AxisNo, I32 Plus_Limit, I32 Neg_Limit);

//Backlas Compensation / Vibration Suppression 6.14
I16 FNTYPE _8154_db53_M_backlash_comp(I16 Card_ID, I16 AxisNo, I16 CompPulse, I16 Mode);
I16 FNTYPE _8154_db53_M_suppress_vibration(I16 Card_ID, I16 AxisNo, U16 ReverseTime, U16 ForwardTime);
I16 FNTYPE _8154_db53_M_set_fa_speed(I16 Card_ID, I16 AxisNo, F64 FA_Speed);

//Speed Profile Calculation 6.15
I16 FNTYPE _8154_db53_M_get_tr_move_profile(I16 Card_ID, I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 *pStrVel, F64 *pMaxVel, F64 *pTacc, F64 *pTdec, F64 *pTconst );
I16 FNTYPE _8154_db53_M_get_ta_move_profile(I16 Card_ID, I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 *pStrVel, F64 *pMaxVel, F64 *pTacc, F64 *pTdec, F64 *pTconst );
I16 FNTYPE _8154_db53_M_get_sr_move_profile(I16 Card_ID, I16 AxisNo, F64 Dist, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec,F64 *pStrVel, F64 *pMaxVel, F64 *pTacc, F64 *pTdec, F64 *pSVacc, F64 *pSVdec, F64 *pTconst);
I16 FNTYPE _8154_db53_M_get_sa_move_profile(I16 Card_ID, I16 AxisNo, F64 Pos, F64 StrVel, F64 MaxVel, F64 Tacc, F64 Tdec, F64 SVacc, F64 SVdec,F64 *pStrVel, F64 *pMaxVel, F64 *pTacc, F64 *pTdec, F64 *pSVacc, F64 *pSVdec, F64 *pTconst);

#ifdef __cplusplus
}
#endif

#endif