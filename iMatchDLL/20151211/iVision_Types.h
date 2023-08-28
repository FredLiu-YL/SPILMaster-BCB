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

#define  PI			 3.141592653589793238462643383279
#define	BlackObj		 0
#define  WhiteObj		 255

typedef struct
{
	long x;
	long y;
}iIPoint;

typedef struct	                                           
{
    float x;
    float y;
}iFPoint;

typedef struct
{
	double x;
	double y;
}iDPoint;

typedef struct
{
	int  top;
	int  down;
	int  left;
	int  right;
}mRect;

typedef struct
{
	float	X_center;
	float	Y_center;
	float	Height;
	float	width;
	float	Angle;
	iFPoint	Pos[4];
}iMinBox;

typedef struct	                                           
{
    double    R;
    double    G;
    double    B;
}ColMean;

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

enum IgnoreType{
	Region_InnerRectangle	= 	0x1000,
	Region_OuterRectangle	= 	0x1001,
	Region_InnerCircle		=	0x1002,
	Region_OuterCircle		=	0x1003,
	Region_RingCircle		=	0x1004
}; 

typedef struct
{
	iDPoint		Cp;
	iDPoint		Pt1;
	iDPoint		Pt2;
	double		InnerR;
	double		OuterR;
	UINT32		TypeofRegion;
}ignore_Para;

typedef struct 
{
	double Cx;
	double Cy;
	double InnerR;
	double OuterR;
}iMCircle_Region;

typedef struct
{
	iDPoint	Cp;
	double	Radius;
	double  Roundness;
	double  PL_Difference;
}iMCircle_Measured;

typedef struct 
{
	iIPoint  Cp;
	iIPoint  StP;
	iIPoint  EnP;
	UINT32   wid;
	UINT32   hei;
	double   angle;
}iMLine_Region;

typedef struct
{
	iIPoint	p1;
	iIPoint	p2;
	double	A;
	double	B;
	double  C;
}iMLine_Measured;

typedef struct
{
	long	area;
	double  XCenter;
	double	YCenter;
	iMinBox	MinRect;
}iObject_BlobFEA;

//typedef struct
//{
//	UINT32		u32_realedgeNum;
//	iIPoint		iip_Cp;
//	iIPoint		iip_CorPt1;
//	iIPoint		iip_CorPt2;
//	iIPoint		iip_CorPt3;
//	iIPoint		iip_CorPt4;
//	UINT32		u32_Region_Wid;
//	UINT32		u32_Region_Hei;
//	double		d_Angle;
//	UINT32		u32_SampleNum;
//
//	iIPoint		Line1StrP;
//	iIPoint		Line1EndP;
//	iIPoint		Line1EdgeP;
//
//	iIPoint		Line2StrP;
//	iIPoint		Line2EndP;
//	iIPoint		Line2EdgeP;
//
//	UINT32		PixelsofLine1;
//	UINT32		PixelsofLine2;
//}LineCheck;
