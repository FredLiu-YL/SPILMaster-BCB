//=================================================================================
/*++
iVision iImage class
C++ code for the iImage class.
//=================================================================================

created:	2013/10/28

Author: Sean, Hank 

Revision History:

--*/
//=================================================================================
#pragma  once


#ifdef IIMAGE_EXPORTS
#define IIMAGE_API __declspec(dllexport)
#else
#define IIMAGE_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
IIMAGE_API LONG_PTR __cdecl CreateGrayiImage();
IIMAGE_API LONG_PTR __cdecl CreateColoriImage();

IIMAGE_API LONG_PTR __cdecl CreateGrayiImageEx(int wid,int hei);
IIMAGE_API LONG_PTR __cdecl CreateColoriImageEx(int wid,int hei);

IIMAGE_API E_iVision_ERRORS __cdecl iImageCopy(LONG_PTR DestiImg, LONG_PTR SrciImg);
IIMAGE_API E_iVision_ERRORS  __cdecl DestroyiImage(LONG_PTR iImg);

IIMAGE_API E_iVision_ERRORS __cdecl  DoBitBlt(LONG_PTR iImg, HDC hdc,int nXdest,int nYdest, int width, int height,
									 int nXsrc,int nYsrc);
IIMAGE_API E_iVision_ERRORS __cdecl  DoStretchBitBlt(LONG_PTR iImg, HDC hdc,int nXdest,int nYdest,
									 int nDestWidth,int nDestHeight,int nXsrc,int nYsrc,int xSrcWidth,int xSrcHeight);
IIMAGE_API E_iVision_ERRORS __cdecl  iImageResize(LONG_PTR iImg, int width, int height);
IIMAGE_API E_iVision_ERRORS __cdecl  GetSubiImage(LONG_PTR iImgDes,LONG_PTR iImgSrc,mRect ROI );
IIMAGE_API int   __cdecl GetWidth(LONG_PTR iImage);
IIMAGE_API int   __cdecl GetHeight(LONG_PTR iImage);
IIMAGE_API E_iVision_ERRORS   __cdecl  iImageIsNULL(LONG_PTR iImg);
IIMAGE_API HBITMAP* __cdecl iGetBitmapAddress(LONG_PTR iImg);

IIMAGE_API E_iVision_ERRORS __cdecl iGetCameraAlignSize(LONG_PTR iImg, int *AlignWid, int *AlignHei);
IIMAGE_API E_iVision_ERRORS __cdecl iPointerToiImage(LONG_PTR iImg,LONG_PTR DataSrc,int AlignWid,int AlignHei);
IIMAGE_API E_iVision_ERRORS __cdecl iPointerFromiImage(LONG_PTR iImg,LONG_PTR DestData,int wid,int hei);

IIMAGE_API E_iVision_ERRORS  __cdecl iReadImage(LONG_PTR iImg ,char* filename);
IIMAGE_API E_iVision_ERRORS  __cdecl iSaveImage(LONG_PTR iImg ,char* filename);

IIMAGE_API void* __cdecl iVarPtr(void *ptr);
IIMAGE_API E_iVision_ERRORS __cdecl iGetAlignedBits( int *val );

#ifdef __cplusplus
}
#endif