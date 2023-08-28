#ifndef _db53ERR_H
#define _db53ERR_H

#include "type_def.h"

//System Level
#define ERR_MNET_NoError					(I16)0
#define ERR_MNET_Invalid_Board_Number		(I16)-10500
#define ERR_MNET_CardIDMapToCardNo			(I16)-10501
#define ERR_MNET_Slave_Number				(I16)-10502
#define ERR_MNET_Transfer_Rate				(I16)-10503
#define ERR_MNET_Clock_rate					(I16)-10504
#define ERR_MNET_DBCardNoInitilization		(I16)-10505
#define	ERR_MNET_Invalid_AxisNo				(I16)-10506
#define ERR_MNET_EventAlreadyEnable			(I16)-10507
#define ERR_MNET_EventNotEnableYet			(I16)-10508
#define ERR_MNET_PosOutOfRange				(I16)-10509
#define ERR_MNET_MotionBusy					(I16)-10510
#define ERR_MNET_SpeedError  				(I16)-10511
#define ERR_MNET_AxisRangeError				(I16)-10512
#define ERR_MNET_CompareNoError				(I16)-10513
#define ERR_MNET_CompareMethodError			(I16)-10514
#define ERR_MNET_CmpSrc						(I16)-10515
#define ERR_MNET_CmpAction					(I16)-10516
#define ERR_MNET_AxisAlreadyStop			(I16)-10517
#define ERR_MNET_EnableRangeError			(I16)-10518
#define ERR_MNET_AutoAccTimeError			(I16)-10519
#define ERR_MNET_DwellTimeError				(I16)-10520
#define ERR_MNET_DwellDistError				(I16)-10521
#define ERR_MNET_CounterNoError				(I16)-10522
#define ERR_MNET_port_type					(I16)-10523
#define ERR_MNET_Time_Out					(I16)-10524
#define ERR_MNET_read_Cmd_dismatch			(I16)-10525
#define ERR_MNET_Invalid_Int_Setting		(I16)-10526
#define ERR_MNET_AxisIntWaitError			(I16)-10527
#define ERR_MNET_Invalid_RW_Method			(I16)-10528
#define ERR_MNET_RWCOMMAND_Other_MaxTry		(I16)-10529
#define ERR_MNET_RWCOMMAND_Other_Enter		(I16)-10530
#define ERR_MNET_RWCOMMAND_MaxTry			(I16)-10531
#define ERR_MNET_RWCOMMAND_NOT_FINISH		(I16)-10532
#define ERR_MNET_FNPARAMETER_Other_MaxTry		(I16)-10533
#define ERR_MNET_FNPARAMETER_Other_Enter		(I16)-10534
#define ERR_MNET_RW_Method					(I16)-10535
#define ERR_MNET_UnknowRWType				(I16)-10536
#define ERR_MNET_Invalid_SlaveNo			(I16)-10537
#define ERR_MNET_RSTFIFO					(I16)-10538
#define ERR_MNET_WRTFIFO					(I16)-10539
#define ERR_MNET_NotVelocityMode			(I16)-10540
#define ERR_MNET_SpeedTargetError			(I16)-10541

#endif