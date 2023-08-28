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
	int x;
	int y;
}iIPoint;

typedef struct
{
	double x;
	double y;
}iDPoint;

typedef struct	                                           
{
    float x;
    float y;
}iFPoint;

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
	INT32  top;
	INT32  down;
	INT32  left;
	INT32  right;
}mRect;

typedef struct
{
	INT32	Width;
	INT32	Height;

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
}sGeometryFind;


typedef struct
{
	iDPoint	Cp;
	double	Diameter;
	double  Roundness;
	double  PL_Difference;
}iMCircle_Measured;

typedef struct
{
	iIPoint	p1;
	iIPoint	p2;
	double	A;
	double	B;
	double   C;
	double   angle;
}iMLine_Measured;

typedef struct
{
	iIPoint	p1;
	iIPoint	p2;
	iIPoint	p3;
	iIPoint	p4;
	iDPoint	cp;
	double   angle;
	double	width;
	double	height;
}iMRectangle_Measured;

typedef struct
{
	iIPoint	crosspoint;
	double   angle;
}iMTriangle_Measured;

typedef struct
{
	iIPoint	p1;
	iIPoint	p2;
	double   distance;
}iMCLLC_Measured;


/**** ROI 結構 ****/
typedef struct
{
	int  OrgX;
	int  OrgY;
	int  Width;
	int  Height;
}iBaseROI;

/**** iAdvPairROI 結構 ****/
typedef struct
{
	int  m_center_x;
	int  m_center_y;
	int  m_advPair_width_1;
	int  m_advPair_width_2;
	int  m_width_1;
	int  m_height_1;
	int  m_width_2;
	int  m_height_2;
	double m_rotation_angle;
}iAdvPairROI;

/**** iTriAdvPairROI 結構 ****/
typedef struct
{
	int  m_center_x;
	int  m_center_y;
	int  m_begin_width;
	int  m_begin_height;
	int  m_end_width;
	int  m_end_height;
	double m_begin_angle;
	double m_end_angle;
	double m_begin_radius;
	double m_end_radius;
}iTriAdvPairROI;

/**** AdvanceROI 結構 ****/
typedef struct
{
	int  m_center_x;
	int  m_center_y;
	int  m_width;
	int  m_height;
	double m_rotation_angle;
}iAdvanceROI;

/**** RectangleROI 結構 ****/
typedef struct
{
	int  m_center_x;
	int  m_center_y;
	int  m_width;
	int  m_height;
	int  m_gap;
	double m_rotation_angle;
}iRectangleROI;

/**** RingROI 結構 ****/
typedef struct
{
	int  m_center_x;
	int  m_center_y;
	int  m_gap;
	double m_radius;
}iRingROI;

/**** iAdvRingROI 結構 ****/
typedef struct
{
	int  m_center_x;
	int  m_center_y;
	int  m_ring_gap;
	double m_begin_angle;
	double m_end_angle;
	double m_radius;
}iAdvRingROI;

/**** ROI 結構 ****/
typedef struct
{
	int  m_center_x;
	int  m_center_y;
	double m_radius;
}iCircleROI;

enum iROI_Type
{
	iBase = 0,
	iAdvance,	
	iAdvPair,
	iRectangle,
	iCircle,
	iRing,
	iAdvRing,
	iTriAdvPair,
	iNULL = 9
};

typedef struct
{
	long	area;
	double  XCenter;
	double	YCenter;
	iMinBox	MinRect;

	int		Blob_index;
}iObject_BlobFEA;


enum IgnoreType{
	UnknownType		=   0,
	InnerRectangle	= 	1,
	OuterRectangle	= 	2,
	InnerCircle		=	3,
	OuterCircle		=	4
}; 

typedef struct
{
	iAdvanceROI	m_advance;
	iCircleROI	m_circle;
	IgnoreType	m_type;
}sIgnore_Para;