#pragma once

#ifdef	_USRDLL
#define	IMAGE_PROCESS_DLL			__declspec(dllexport)
#else
#define	IMAGE_PROCESS_DLL
#endif

class IMAGE_PROCESS_DLL CPixelFormatConvertTBB
	//class CPixelFormatConvert
{
public:
	CPixelFormatConvertTBB(void);
	~CPixelFormatConvertTBB(void);

	/// Comment::20150605, Dong-Uk Lee, TBB YUV 변환 루틴은 정상 동작하지 않음.
	static	void ConvertYUV422_UYVYtoBGR8( const BYTE* pbSrc,  const unsigned int nWidth, const unsigned int nHeight, BYTE* pbDst );
	static	void ConvertYUV422_YUYVtoBGR8( const BYTE* pbSrc, const unsigned int nWidth, const unsigned int nHeight, BYTE* pbDst );
	static	void ConvertYUV422toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertYUV422toBGR8Interlaced( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst, bool bOdd, DWORD width, bool blend, bool _signed );
	static	void ConvertYUV422PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertYUV411toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertYUV411PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	/// Comment::20150605, Dong-Uk Lee, 

	static	void ConvertRGB12PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertRGB8toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertBGR10V2PackedtoBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertYUV444toBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertMonoPackedToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertMonoPackedToMono8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertMono16PackedToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertBAYGB8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYRG8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYGR8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYGB10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYRG10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYBG10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYGR10ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYGB12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYRG12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYBG12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYGR12ToBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertMono10PackedToMono16bit( const BYTE* pbSrc, UINT width, UINT height, BYTE* pbDst );
	static	void ConvertMono12PackedToMono16bit( const BYTE* pbSrc, UINT width, UINT height, BYTE* pbDst );
	static	void ConvertMono10ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertMono10ToMono8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertMono12ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertMono12ToMono8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertMono14ToBGR8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );
	static	void ConvertMono14ToMono8( const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst );

	static	void ConvertMono16ToBGR8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
	static	void ConvertMono16ToMono8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);

	/// Comment::20180620, YoonHyuk Lee, ADD_PFNC_PACKED_START.
	static	void ConvertMono10pToMono8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
	static  void ConvertMono10pmsbToMono8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
	static	void ConvertMono12pToMono8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
	static	void ConvertMono12pmsbToMono8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
	static	void ConvertYCbCr8toBGR8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
	static	void ConvertYCbCr8_CbYCrtoBGR8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
	static	void ConvertYCbCr411_8toBGR8(const BYTE* pbSrc, DWORD cbSrc, BYTE* pbDst);
	static	void ConvertBAYRG16toBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static	void ConvertBAYBG16toBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	static  void ConvertBAYGR16toBGR8(const WORD* pbSrc, BYTE* pbDst, DWORD width, DWORD height);

	static	void ConvertBAYBG8ToBGR8(const BYTE* pbSrc, BYTE* pbDst, DWORD width, DWORD height);
	/// Comment::20180620, YoonHyuk Lee, ADD_PFNC_PACKED_END.

};