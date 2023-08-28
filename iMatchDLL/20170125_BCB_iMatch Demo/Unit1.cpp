//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "iVisionErrs.h"
#include "iVision_Types.h"
#include "iVision.h"
#include "iImage.h"
#include "iMatch.h"
#include "Unit1.h"
#include "iMatchDialog.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainfrm *Mainfrm;
//---------------------------------------------------------------------------
__fastcall TMainfrm::TMainfrm(TComponent* Owner)
        : TForm(Owner)
{
     GrayImg = CreateGrayiImage();
     ColorImg = CreateColoriImage();
     iMatchModel = CreateNCCMatch();
     bmp = new Graphics::TBitmap();
     StartROI = SettingROI = false;
     StartMatchROI = SettingMatchROI = false;
     Mainfrm->DoubleBuffered = true;


}
//---------------------------------------------------------------------------
void __fastcall TMainfrm::Exit1Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainfrm::FormCreate(TObject *Sender)
{
     Mainfrm->Image1->Top = 5;
     Mainfrm->Image1->Left = 5;

}
//---------------------------------------------------------------------------


void __fastcall TMainfrm::FormDestroy(TObject *Sender)
{
     if(bmp!=NULL)  delete bmp;                   //刪除已建立物件
     if(GrayImg!=NULL)  DestroyiImage(GrayImg);
     if(ColorImg!=NULL)  DestroyiImage(ColorImg);
     if(iMatchModel != NULL)  DestroyNCCMatch(iMatchModel);
}

void __fastcall TMainfrm::Open1Click(TObject *Sender)
{
     iMatchfrm->Show();
}

void __fastcall TMainfrm::Version1Click(TObject *Sender)
{
    AnsiString str;
	char* VersionStr;
	char* VersionDateStr;

	VersionStr = iGetiMatchVersion();
	VersionDateStr = iGetiMatchVersionDate();

	str.sprintf("Version: %s Date: %s",VersionStr,VersionDateStr);

    MessageBox(NULL,str.c_str(),"Info",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TMainfrm::Key1Click(TObject *Sender)
{
	AnsiString str;
	int  serial;
	char *ErrStr;

	ErrStr = iGetErrorText(iGetKeySerial(&serial));

	str.sprintf("Key: %s Serial: %d",ErrStr,serial);
    MessageBox(NULL,str.c_str(),"Info",MB_OK);
}

void __fastcall TMainfrm::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{

    if ( StartROI )
    {
        ROI.top = Y;
        ROI.left = X;
        StartROI = false;
        SettingROI = true;

    }
    if ( StartMatchROI )
    {
        MatchROI.top = Y;
        MatchROI.left = X;
        StartMatchROI = false;
        SettingMatchROI = true;
    }

}
//---------------------------------------------------------------------------

void __fastcall TMainfrm::Image1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    Graphics::TBitmap *bmp1 = new Graphics::TBitmap();
    if(SettingROI)
    {
        ROI.right = X;
        ROI.down = Y;

        Image1->Picture->Assign(Mainfrm->bmp);
        Image1->Picture->Bitmap->PixelFormat = pf24bit;
        Image1->Canvas->Pen->Color = clRed;
        Image1->Canvas->Brush->Style = bsClear;
        Image1->Canvas->Rectangle(ROI.left,ROI.top,ROI.right,ROI.down);
    }
    if(SettingMatchROI)
    {
        MatchROI.right = X;
        MatchROI.down = Y;

        Image1->Picture->Assign(Mainfrm->bmp);
        Image1->Picture->Bitmap->PixelFormat = pf24bit;
        Image1->Canvas->Pen->Color = clRed;
        Image1->Canvas->Brush->Style = bsClear;
        Image1->Refresh();
        Image1->Canvas->Rectangle(MatchROI.left,MatchROI.top,MatchROI.right,MatchROI.down);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainfrm::Image1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if(SettingROI)
    {
        ROI.right = X;
        ROI.down = Y;

        Image1->Canvas->Rectangle(ROI.left,ROI.top,ROI.right,ROI.down);
        SettingROI = false;
    }
    if(SettingMatchROI)
    {
        MatchROI.right = X;
        MatchROI.down = Y;

        Image1->Canvas->Rectangle(MatchROI.left,MatchROI.top,MatchROI.right,MatchROI.down);
        SettingMatchROI = false;
    }
}
//---------------------------------------------------------------------------

