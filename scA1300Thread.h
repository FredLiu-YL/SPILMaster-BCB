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

   // 2011 10 9 - chc ����Trigger
   bool boolBaslerLive;
   void __fastcall TscA1300::GigaBuffer();

   // 2015 8 19 - chc �@���T��CCD
   int CCDNo;                                                                   // �s��
   AnsiString CCDName;                                                          // �W��
   int CCDType;                                                                 // Type: Color(2) or BW(1)
   int CCDHeight,CCDWidth;                                                      // Size

};
//---------------------------------------------------------------------------
#endif
