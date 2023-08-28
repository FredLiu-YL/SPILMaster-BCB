//=================================================================================
/*++
iVision 
Basic data types
//=================================================================================

created:	2013/10/28

Author: Sean, Hank 

Revision History:

--*/
//=================================================================================
#pragma once

typedef struct
{
	long x;
	long y;
}iIPoint;

typedef struct
{
	double x;
	double y;
}iDPoint;

typedef struct
{
	int  top;
	int  bottom;
	int  left;
	int  right;
}mRect;

typedef struct
{
	int		Width;
	int		Height;

	double   CX;
	double   CY;
	double	Angle;
	double	Scale;
	double	Score;
}NCCFind;

typedef struct
{
	double x;
	double y;
	double Score;
	double Angle;
	double Scale;
}GeoFind;
