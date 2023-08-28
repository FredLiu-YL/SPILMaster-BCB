//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TMainfrm : public TForm
{
__published:	// IDE-managed Components
     TImage *Image1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *Open1;
    TMenuItem *Exit1;
    TMenuItem *Information1;
    TMenuItem *Version1;
    TMenuItem *Key1;
          void __fastcall Exit1Click(TObject *Sender);
     void __fastcall FormCreate(TObject *Sender);
     void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Open1Click(TObject *Sender);
    void __fastcall Version1Click(TObject *Sender);
    void __fastcall Key1Click(TObject *Sender);
    void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
    void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);

private:	// User declarations
public:		// User declarations
        __fastcall TMainfrm(TComponent* Owner);

        LONG_PTR ColorImg,GrayImg;
        LONG_PTR iMatchModel;
        Graphics::TBitmap *bmp;

        double MinScore,MaxAngle,MinAngle,MaxScale,MinScale;
        int    DetectNums,DontcareThreshold,MinReduceArea,ColorSensitivity;

        bool   Rotated,Scaled,UsingDoncare, UsingRobustness, UsingColorSimialrity;
        bool   UsingSubpixel;
        bool   UsingColor;
        bool   LoadGray;
        bool   StartROI,SettingROI;
        bool   StartMatchROI,SettingMatchROI;
        mRect  ROI;
        mRect  MatchROI;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainfrm *Mainfrm;
//---------------------------------------------------------------------------
#endif
