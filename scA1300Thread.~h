//---------------------------------------------------------------------------
#ifndef scA1300ThreadH
#define scA1300ThreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>

#include "MainFrm.h"

//---------------------------------------------------------------------------
class TscA1300 : public TThread
{
private:
protected:
        void __fastcall Execute();
public:
        __fastcall TscA1300(bool CreateSuspended, int no, AnsiString name, int type, int Width, int Height);

   // 2011 10 9 - chc 取像Trigger
   bool boolBaslerLive;
   void __fastcall TscA1300::GigaBuffer();

   // 2015 8 19 - chc 共有三個CCD
   int CCDNo;                                                                   // 編號
   AnsiString CCDName;                                                          // 名稱
   int CCDType;                                                                 // Type: Color(2) or BW(1)
   int CCDHeight,CCDWidth;                                                      // Size

};
//---------------------------------------------------------------------------
#endif
