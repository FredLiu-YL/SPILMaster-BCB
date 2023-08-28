#ifndef _db50ERR_H
#define _db50ERR_H

#include "type_def.h"

//System Level
#define ERR_db8150_NoError						(I16)0
#define ERR_db8150_Invalid_Board_Number			(I16)-10400
#define ERR_db8150_DBCardAlreadyInitilization	(I16)-10401
#define ERR_db8150_DBCardNoInitilization		(I16)-10402
#define ERR_db8150_ParameterValueError			(I16)-10403
#define ERR_db8150_EventAlreadyEnable			(I16)-10404
#define ERR_db8150_EventNotEnableYet			(I16)-10405
#define ERR_db8150_IntWaitError					(I16)-10406

#endif