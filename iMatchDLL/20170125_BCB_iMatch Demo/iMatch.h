//=================================================================================
/*++
iVision iMatch class
C++ code for the iMatch class.
//=================================================================================

created:	2013/10/28

Author: Sean, Hank 

Revision History:

--*/
//=================================================================================

#pragma once 

#ifdef IMATCH_EXPORTS
#define IMATCH_API  __declspec(dllexport)
#else
#define IMATCH_API  __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

IMATCH_API LONG_PTR __cdecl CreateNCCMatch();
IMATCH_API E_iVision_ERRORS __cdecl DestroyNCCMatch(LONG_PTR objptr);
IMATCH_API E_iVision_ERRORS __cdecl CreateNCCModel(LONG_PTR Img,LONG_PTR Model, bool Mask_Used = false);
IMATCH_API E_iVision_ERRORS __cdecl CreateNCCModelFromROI(LONG_PTR Img,LONG_PTR Model, mRect ROI, bool Mask_Used = false);
IMATCH_API E_iVision_ERRORS __cdecl MatchNCCModelEx(LONG_PTR Img,LONG_PTR Model, double minScore, 
												double maxAng , double minAng , 
												double maxScale , double minScale , 
												bool rotated = false, bool scaled = false,int Max_Pos = 1);
IMATCH_API E_iVision_ERRORS __cdecl MatchNCCModel(LONG_PTR Img,LONG_PTR Model);
IMATCH_API E_iVision_ERRORS __cdecl MatchNCCModelFromROI(LONG_PTR Img,LONG_PTR Model, mRect ROI);

IMATCH_API E_iVision_ERRORS __cdecl LoadiMatchModel(LONG_PTR Model,char *path);
IMATCH_API E_iVision_ERRORS __cdecl SaveiMatchModel(LONG_PTR Model,char *path);

IMATCH_API E_iVision_ERRORS	 __cdecl iDrawiMatchResults(LONG_PTR Model, HDC hDC, double Scale);

IMATCH_API E_iVision_ERRORS __cdecl	iGetNCCMatchResults(LONG_PTR Model, int index, NCCFind *data);
IMATCH_API E_iVision_ERRORS	 __cdecl	iGetNCCMatchNum(LONG_PTR Model,int *Nums);

IMATCH_API E_iVision_ERRORS __cdecl iSetDontCareThreshold(LONG_PTR Model,int val);
IMATCH_API E_iVision_ERRORS __cdecl iGetDontCareThreshold(LONG_PTR Model,int *val);

IMATCH_API E_iVision_ERRORS __cdecl iSetMinScore(LONG_PTR Model,double val);
IMATCH_API E_iVision_ERRORS __cdecl iGetMinScore(LONG_PTR Model,double *val);

IMATCH_API E_iVision_ERRORS __cdecl iSetAngle(LONG_PTR Model,double val1,double val2);
IMATCH_API E_iVision_ERRORS __cdecl iGetAngle(LONG_PTR Model,double *val1,double *val2);
IMATCH_API E_iVision_ERRORS __cdecl iSetIsRotated(LONG_PTR Model,bool flag);
IMATCH_API E_iVision_ERRORS __cdecl iGetIsRotated(LONG_PTR Model,bool *flag);

IMATCH_API E_iVision_ERRORS __cdecl iSetScale(LONG_PTR Model,double val1,double val2);
IMATCH_API E_iVision_ERRORS __cdecl iGetScale(LONG_PTR Model,double *val1,double *val2);

IMATCH_API E_iVision_ERRORS __cdecl iSetIsScaled(LONG_PTR Model,bool flag);
IMATCH_API E_iVision_ERRORS __cdecl iGetIsScaled(LONG_PTR Model,bool *flag);

IMATCH_API E_iVision_ERRORS __cdecl iSetIsDontArea(LONG_PTR Model,bool flag);
IMATCH_API E_iVision_ERRORS __cdecl iGetIsDontArea(LONG_PTR Model,bool *flag);

IMATCH_API E_iVision_ERRORS __cdecl iSetOccurrence(LONG_PTR Model,int val);
IMATCH_API E_iVision_ERRORS __cdecl iGetOccurrence(LONG_PTR Model,int *val);

IMATCH_API E_iVision_ERRORS __cdecl iGetModelWidth(LONG_PTR Model,int *val);
IMATCH_API E_iVision_ERRORS __cdecl iGetModelHeight(LONG_PTR Model,int *val);

IMATCH_API E_iVision_ERRORS __cdecl iSetMinReduceArea(LONG_PTR Model,int val);
IMATCH_API E_iVision_ERRORS __cdecl iGetMinReduceArea(LONG_PTR Model,int *val);

IMATCH_API E_iVision_ERRORS __cdecl iSetOutsideFOV(LONG_PTR Model,bool flag);
IMATCH_API E_iVision_ERRORS __cdecl iGetOutsideFOV(LONG_PTR Model,bool *flag);

IMATCH_API E_iVision_ERRORS __cdecl iSetRobustness(LONG_PTR Model,bool flag);
IMATCH_API E_iVision_ERRORS __cdecl iGetRobustness(LONG_PTR Model,bool *flag);

IMATCH_API E_iVision_ERRORS __cdecl iSetColorSimilarity(LONG_PTR Model,bool flag);
IMATCH_API E_iVision_ERRORS __cdecl iGetColorSimilarity(LONG_PTR Model,bool *flag);

IMATCH_API E_iVision_ERRORS __cdecl iSetColorSensitivity(LONG_PTR Model,int val);
IMATCH_API E_iVision_ERRORS __cdecl iGetColorSensitivity(LONG_PTR Model,int *val);

IMATCH_API E_iVision_ERRORS __cdecl iSetSubPixel(LONG_PTR Model,bool flag);
IMATCH_API E_iVision_ERRORS __cdecl iGetSubPixel(LONG_PTR Model,bool *flag);

IMATCH_API E_iVision_ERRORS __cdecl iIsPatternLearn(LONG_PTR Model);
IMATCH_API E_iVision_ERRORS __cdecl iIsColorModel(LONG_PTR Model);
IMATCH_API E_iVision_ERRORS __cdecl iPointerFromiModel( LONG_PTR Img,LONG_PTR Model);

IMATCH_API E_iVision_ERRORS __cdecl iGetKeyState();
IMATCH_API E_iVision_ERRORS __cdecl iVisitingKey();



#ifdef __cplusplus
}
#endif