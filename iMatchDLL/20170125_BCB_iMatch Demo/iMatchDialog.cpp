//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "iMatchDialog.h"
#include "iVisionErrs.h"
#include "iVision_Types.h"
#include "iVision.h"
#include "iImage.h"
#include "iMatch.h"
#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TiMatchfrm *iMatchfrm;
//---------------------------------------------------------------------------
__fastcall TiMatchfrm::TiMatchfrm(TComponent* Owner)
    : TForm(Owner)
{

}
//---------------------------------------------------------------------------
void __fastcall TiMatchfrm::FormCreate(TObject *Sender)
{
    this->Width = 720;
    this->Height = 550;
     SetWindowLong(edt_MinScore->Handle, GWL_STYLE,
    GetWindowLong(edt_MinScore->Handle, GWL_STYLE) | ES_CENTER);
    edt_MinScore->Invalidate();

    SetWindowLong(edt_MaxAngle->Handle, GWL_STYLE,
    GetWindowLong(edt_MaxAngle->Handle, GWL_STYLE) | ES_CENTER);
    edt_MaxAngle->Invalidate();

    SetWindowLong(edt_MinAngle->Handle, GWL_STYLE,
    GetWindowLong(edt_MinAngle->Handle, GWL_STYLE) | ES_CENTER);
    edt_MinAngle->Invalidate();

    SetWindowLong(edt_MaxScale->Handle, GWL_STYLE,
    GetWindowLong(edt_MaxScale->Handle, GWL_STYLE) | ES_CENTER);
    edt_MaxScale->Invalidate();

    SetWindowLong(edt_MinScale->Handle, GWL_STYLE,
    GetWindowLong(edt_MinScale->Handle, GWL_STYLE) | ES_CENTER);
    edt_MinScale->Invalidate();

    SetWindowLong(edt_DetectNums->Handle, GWL_STYLE,
    GetWindowLong(edt_DetectNums->Handle, GWL_STYLE) | ES_CENTER);
    edt_DetectNums->Invalidate();

    SetWindowLong(edt_DontCareThreshold->Handle, GWL_STYLE,
    GetWindowLong(edt_DontCareThreshold->Handle, GWL_STYLE) | ES_CENTER);
    edt_DontCareThreshold->Invalidate();

    SetWindowLong(edt_MinReduceArea->Handle, GWL_STYLE,
    GetWindowLong(edt_MinReduceArea->Handle, GWL_STYLE) | ES_CENTER);
    edt_MinReduceArea->Invalidate();

    iGetMinScore(Mainfrm->iMatchModel,&Mainfrm->MinScore);
    iGetAngle(Mainfrm->iMatchModel,&Mainfrm->MaxAngle,&Mainfrm->MinAngle);
    iGetScale(Mainfrm->iMatchModel,&Mainfrm->MaxScale,&Mainfrm->MinScale);
    iGetOccurrence(Mainfrm->iMatchModel,&Mainfrm->DetectNums);
    iGetDontCareThreshold(Mainfrm->iMatchModel,&Mainfrm->DontcareThreshold);
    iGetMinReduceArea(Mainfrm->iMatchModel,&Mainfrm->MinReduceArea);
    iGetIsRotated(Mainfrm->iMatchModel,&Mainfrm->Rotated);
    iGetIsScaled(Mainfrm->iMatchModel,&Mainfrm->Scaled);
    iGetIsDontArea(Mainfrm->iMatchModel,&Mainfrm->UsingDoncare);
    iGetColorSimilarity(Mainfrm->iMatchModel,&Mainfrm->UsingColorSimialrity);
    iGetColorSensitivity(Mainfrm->iMatchModel,&Mainfrm->ColorSensitivity);
    iGetSubPixel(Mainfrm->iMatchModel,&Mainfrm->UsingSubpixel);
    iGetRobustness(Mainfrm->iMatchModel,&Mainfrm->UsingRobustness);

    UpdataToUI();

    CheckBox3->Checked = Mainfrm->UsingRobustness;
    CheckBox4->Checked = Mainfrm->UsingColorSimialrity;
    CheckBox5->Checked = Mainfrm->UsingSubpixel;

    for(int i=1; i<StringGrid1->Row ; i++)
        StringGrid1->Rows[i]->Clear();

    StringGrid1->Cols[0]->Text = "Nums";
    StringGrid1->Cols[1]->Text = "Score";
    StringGrid1->Cols[2]->Text = "Angle";
    StringGrid1->Cols[3]->Text = "Scale";
    StringGrid1->Cols[4]->Text = "Cx";
    StringGrid1->Cols[5]->Text = "Cy";
    StringGrid1->Cols[6]->Text = "Time(ms)";
}

void __fastcall TiMatchfrm::btn_LoadColorImgClick(TObject *Sender)
{
     AnsiString CurrentFile;
     E_iVision_ERRORS  err;
     char *str;
     if(OpenDialog1->Execute()){              //開啟檔案
          CurrentFile = OpenDialog1->FileName;

          err = iReadImage(Mainfrm->ColorImg,CurrentFile.c_str());
          str = iGetErrorText(err);
          Lab_State->Caption = str;
          if(err != E__OK)
          {
            ShowMessage("Load Image FAIL");
            return;
          }

          for(int i=1; i<StringGrid1->Row ; i++)
            StringGrid1->Rows[i]->Clear();

          Mainfrm->LoadGray = false;

          Mainfrm->bmp->Handle= (void*)(iGetBitmapAddress(Mainfrm->ColorImg));   //轉接至BCB顯示
          Mainfrm->Image1->AutoSize=true;
          Mainfrm->Image1->Picture->Bitmap->ReleaseHandle();
          Mainfrm->Image1->Picture->Assign(Mainfrm->bmp);
     }
}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::btn_LoadGrayImgClick(TObject *Sender)
{
     AnsiString CurrentFile;
     E_iVision_ERRORS  err;
     if(OpenDialog1->Execute()){              //開啟檔案
          CurrentFile = OpenDialog1->FileName;

          err = iReadImage(Mainfrm->GrayImg,CurrentFile.c_str());

          if(err != E__OK)
          {
            ShowMessage("Load Image FAIL");
            return;
          }

          for(int i=1; i<StringGrid1->Row ; i++)
                StringGrid1->Rows[i]->Clear();

          Mainfrm->LoadGray = true;

          Mainfrm->Image1->AutoSize=true;
          Mainfrm->bmp->Handle= (void*)(iGetBitmapAddress(Mainfrm->GrayImg));   //轉接至BCB顯示
          Mainfrm->Image1->Picture->Bitmap->ReleaseHandle();
          Mainfrm->Image1->Picture->Assign(Mainfrm->bmp);
     }
}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::btn_TrainingClick(TObject *Sender)
{
    E_iVision_ERRORS err;

    UpdataToPara();

    iSetDontCareThreshold( Mainfrm->iMatchModel, Mainfrm->DontcareThreshold);

    if(CheckBox1->Checked)
    {
        if(Mainfrm->LoadGray)
            err = CreateNCCModelFromROI(Mainfrm->GrayImg,Mainfrm->iMatchModel,Mainfrm->ROI,Mainfrm->UsingDoncare);
        else
            err = CreateNCCModelFromROI(Mainfrm->ColorImg,Mainfrm->iMatchModel,Mainfrm->ROI,Mainfrm->UsingDoncare);
    }
    else
    {
        if(Mainfrm->LoadGray)
            err = CreateNCCModel(Mainfrm->GrayImg,Mainfrm->iMatchModel,Mainfrm->UsingDoncare);
        else
            err = CreateNCCModel(Mainfrm->ColorImg,Mainfrm->iMatchModel,Mainfrm->UsingDoncare);
    }

    Lab_State->Caption = iGetErrorText(err);

}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::btn_MatchingClick(TObject *Sender)
{
    NCCFind Findobj;
    int objnums;
    E_iVision_ERRORS err;
    char *str;
    AnsiString MStr[7];

	float           t2,dfFreq;
    LARGE_INTEGER   tt1,tt2,fre;
    QueryPerformanceFrequency(&fre);
    dfFreq=(float)fre.QuadPart;

    for(int i=1; i<StringGrid1->RowCount ; i++)
        StringGrid1->Rows[i]->Clear();

    StringGrid1->RowCount = 2;

    UpdataToPara();

    iSetMinScore(Mainfrm->iMatchModel,Mainfrm->MinScore);
    iSetAngle(Mainfrm->iMatchModel,Mainfrm->MaxAngle,Mainfrm->MinAngle);
    iSetScale(Mainfrm->iMatchModel,Mainfrm->MaxScale,Mainfrm->MinScale);
    iSetOccurrence(Mainfrm->iMatchModel,Mainfrm->DetectNums);
    iSetMinReduceArea(Mainfrm->iMatchModel,Mainfrm->MinReduceArea);
    iSetIsRotated(Mainfrm->iMatchModel,Mainfrm->Rotated);
    iSetIsScaled(Mainfrm->iMatchModel,Mainfrm->Scaled);
    iSetColorSimilarity(Mainfrm->iMatchModel, Mainfrm->UsingColorSimialrity);
    iSetColorSensitivity(Mainfrm->iMatchModel, Mainfrm->ColorSensitivity);

    err = iIsColorModel(Mainfrm->iMatchModel);

    if(err == E_TRUE)
    {
        err = iImageIsNULL(Mainfrm->ColorImg);
        if(err == E_TRUE)
        {
            str = iGetErrorText(err);
            ShowMessage(str);
            Lab_State->Caption = str;
            return;
        }
        else
        {
            if(CheckBox2->Checked)
            {
    	        QueryPerformanceCounter(&tt1);
                err = MatchNCCModelFromROI(Mainfrm->ColorImg,Mainfrm->iMatchModel,Mainfrm->MatchROI);
                QueryPerformanceCounter(&tt2);
            }
            else
            {
    	        QueryPerformanceCounter(&tt1);
                err = MatchNCCModel(Mainfrm->ColorImg,Mainfrm->iMatchModel);
                QueryPerformanceCounter(&tt2);
            }
        }
    }
    else
    {
        err = iImageIsNULL(Mainfrm->GrayImg);
        if(err == E_TRUE)
        {
            str = iGetErrorText(err);
            Lab_State->Caption = str;
            return;
        }
        else
        {
            if(CheckBox2->Checked)
            {
                QueryPerformanceCounter(&tt1);
                err = MatchNCCModelFromROI(Mainfrm->GrayImg,Mainfrm->iMatchModel,Mainfrm->MatchROI);
                QueryPerformanceCounter(&tt2);
            }
            else
            {
                QueryPerformanceCounter(&tt1);
                err = MatchNCCModel(Mainfrm->GrayImg,Mainfrm->iMatchModel);
                QueryPerformanceCounter(&tt2);
            }
        }
    }
    t2= (tt2.QuadPart - tt1.QuadPart)*1000/dfFreq;

    str = iGetErrorText(err);
    Lab_State->Caption = str;

    if(err != E__OK)
        return;

    //Mainfrm->Image1->Picture->Bitmap->ReleaseHandle();
    Mainfrm->Image1->Picture->Bitmap->FreeImage();
    Mainfrm->Image1->Picture->Assign(Mainfrm->bmp);
    Mainfrm->Image1->Picture->Bitmap->PixelFormat = pf24bit;
    iDrawiMatchResults(Mainfrm->iMatchModel,Mainfrm->Image1->Canvas->Handle,1);

    iGetNCCMatchNum(Mainfrm->iMatchModel,&objnums);

    if (objnums != 0)
        t2 /= (double)objnums;

    for(int i=0; i<objnums ; i++)
    {
        iGetNCCMatchResults(Mainfrm->iMatchModel,i,&Findobj);

        MStr[0].sprintf("%d",i+1);
        MStr[1].sprintf("%.3f",Findobj.Score);
        MStr[2].sprintf("%.3f",Findobj.Angle);
        MStr[3].sprintf("%.3f",Findobj.Scale);
        MStr[4].sprintf("%.3f",Findobj.CX);
        MStr[5].sprintf("%.3f",Findobj.CY);
        MStr[6].sprintf("%.3f",t2);

        StringGrid1->Cells[0][i+1] = MStr[0].c_str();
        StringGrid1->Cells[1][i+1] = MStr[1].c_str();
        StringGrid1->Cells[2][i+1] = MStr[2].c_str();
        StringGrid1->Cells[3][i+1] = MStr[3].c_str();
        StringGrid1->Cells[4][i+1] = MStr[4].c_str();
        StringGrid1->Cells[5][i+1] = MStr[5].c_str();
        StringGrid1->Cells[6][i+1] = MStr[6].c_str();
        StringGrid1->RowCount++;
    }
}
//---------------------------------------------------------------------------
void __fastcall TiMatchfrm::UpdataToUI()
{
    this->edt_MinScore->Text = FloatToStr(Mainfrm->MinScore);
    this->edt_MaxAngle->Text = FloatToStr(Mainfrm->MaxAngle);
    this->edt_MinAngle->Text = FloatToStr(Mainfrm->MinAngle);
    this->edt_MaxScale->Text = FloatToStr(Mainfrm->MaxScale);
    this->edt_MinScale->Text = FloatToStr(Mainfrm->MinScale);
    this->edt_DetectNums->Text = IntToStr(Mainfrm->DetectNums);
    this->edt_DontCareThreshold->Text = IntToStr(Mainfrm->DontcareThreshold);
    this->edt_MinReduceArea->Text = IntToStr(Mainfrm->MinReduceArea);
    this->edt_ColorSensitivity->Text = IntToStr(Mainfrm->ColorSensitivity);


    if(Mainfrm->Rotated)
        RB_RotationYes->Checked = true;
    else
        RB_RotationNo->Checked = true;

    if(Mainfrm->Scaled)
        RB_ScaleYes->Checked = true;
    else
        RB_ScaleNo->Checked = true;

    if(Mainfrm->UsingDoncare)
        RB_dontcareModelYes->Checked = true;
    else
        RB_dontcareModelNo->Checked = true;

    CheckBox3->Checked = Mainfrm->UsingRobustness;
    CheckBox4->Checked = Mainfrm->UsingColorSimialrity;
    CheckBox5->Checked = Mainfrm->UsingSubpixel;
}


void __fastcall TiMatchfrm::UpdataToPara()
{
    Mainfrm->MinScore = StrToFloat(this->edt_MinScore->Text);
    Mainfrm->MaxAngle = StrToFloat(this->edt_MaxAngle->Text);
    Mainfrm->MinAngle = StrToFloat(this->edt_MinAngle->Text);
    Mainfrm->MaxScale = StrToFloat(this->edt_MaxScale->Text);
    Mainfrm->MinScale = StrToFloat(this->edt_MinScale->Text);
    Mainfrm->DetectNums = StrToInt(this->edt_DetectNums->Text);
    Mainfrm->DontcareThreshold = StrToInt(this->edt_DontCareThreshold->Text);
    Mainfrm->MinReduceArea = StrToInt(this->edt_MinReduceArea->Text);
    Mainfrm->ColorSensitivity = StrToInt(this->edt_ColorSensitivity->Text);

    if(this->RB_RotationYes->Checked == true)
        Mainfrm->Rotated = true;
    else
        Mainfrm->Rotated = false;

    if(this->RB_ScaleYes->Checked == true)
        Mainfrm->Scaled = true;
    else
        Mainfrm->Scaled = false;

    if(this->RB_dontcareModelYes->Checked == true)
        Mainfrm->UsingDoncare = true;
    else
        Mainfrm->UsingDoncare = false;

    Mainfrm->UsingRobustness = CheckBox3->Checked;
    Mainfrm->UsingColorSimialrity = CheckBox4->Checked;
    Mainfrm->UsingSubpixel = CheckBox5->Checked;

}


void __fastcall TiMatchfrm::btn_LoadiMatchmodelClick(TObject *Sender)
{
     AnsiString CurrentFile;
     E_iVision_ERRORS  err;
     char *str;
     OpenDialog1->Filter = ".imm";
     if(OpenDialog1->Execute()){              //開啟檔案
          CurrentFile = OpenDialog1->FileName;

          err = LoadiMatchModel(Mainfrm->iMatchModel,CurrentFile.c_str());
          str = iGetErrorText(err);
          Lab_State->Caption = str;
          if(err != E__OK)
          {
            ShowMessage(str);
            return;
          }
          for(int i=1; i<StringGrid1->Row ; i++)
                StringGrid1->Rows[i]->Clear();
     }

    iGetMinScore(Mainfrm->iMatchModel,&Mainfrm->MinScore);
    iGetAngle(Mainfrm->iMatchModel,&Mainfrm->MaxAngle,&Mainfrm->MinAngle);
    iGetScale(Mainfrm->iMatchModel,&Mainfrm->MaxScale,&Mainfrm->MinScale);
    iGetOccurrence(Mainfrm->iMatchModel,&Mainfrm->DetectNums);
    iGetDontCareThreshold(Mainfrm->iMatchModel,&Mainfrm->DontcareThreshold);
    iGetMinReduceArea(Mainfrm->iMatchModel,&Mainfrm->MinReduceArea);
    iGetIsRotated(Mainfrm->iMatchModel,&Mainfrm->Rotated);
    iGetIsScaled(Mainfrm->iMatchModel,&Mainfrm->Scaled);
    iGetIsDontArea(Mainfrm->iMatchModel,&Mainfrm->UsingDoncare);
    iGetRobustness(Mainfrm->iMatchModel,&Mainfrm->UsingRobustness);
    iGetColorSimilarity(Mainfrm->iMatchModel, &Mainfrm->UsingColorSimialrity);
    iGetColorSensitivity(Mainfrm->iMatchModel, &Mainfrm->ColorSensitivity);
    iGetSubPixel(Mainfrm->iMatchModel, &Mainfrm->UsingSubpixel);

    UpdataToUI();


}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::btn_SaveiMatchmodelClick(TObject *Sender)
{
     AnsiString CurrentFile;
     E_iVision_ERRORS  err;
     char *str;
     SaveDialog1->Filter = ".imm";

    if(Mainfrm->LoadGray)
    {
        err = iImageIsNULL(Mainfrm->GrayImg);
        if(err == E_TRUE)
        {
            str = iGetErrorText(err);
            ShowMessage(str);
            Lab_State->Caption = str;
            return;
        }
    }
    else
    {
        err = iImageIsNULL(Mainfrm->ColorImg);
        if(err == E_TRUE)
        {
            str = iGetErrorText(err);
            ShowMessage(str);
            Lab_State->Caption = str;
            return;
        }
    }

    UpdataToPara();

    iSetMinScore(Mainfrm->iMatchModel,Mainfrm->MinScore);
    iSetAngle(Mainfrm->iMatchModel,Mainfrm->MaxAngle,Mainfrm->MinAngle);
    iSetScale(Mainfrm->iMatchModel,Mainfrm->MaxScale,Mainfrm->MinScale);
    iSetOccurrence(Mainfrm->iMatchModel,Mainfrm->DetectNums);
    iSetMinReduceArea(Mainfrm->iMatchModel,Mainfrm->MinReduceArea);
    iSetIsRotated(Mainfrm->iMatchModel,Mainfrm->Rotated);
    iSetIsScaled(Mainfrm->iMatchModel,Mainfrm->Scaled);
    iSetIsDontArea(Mainfrm->iMatchModel,Mainfrm->UsingDoncare);
    iSetRobustness(Mainfrm->iMatchModel,Mainfrm->UsingRobustness);
    iSetColorSimilarity(Mainfrm->iMatchModel, Mainfrm->UsingColorSimialrity);
    iSetColorSensitivity(Mainfrm->iMatchModel, Mainfrm->ColorSensitivity);
    iSetSubPixel(Mainfrm->iMatchModel, Mainfrm->UsingSubpixel);

    if(SaveDialog1->Execute()){              //開啟檔案
          CurrentFile = SaveDialog1->FileName;

          err = SaveiMatchModel(Mainfrm->iMatchModel,CurrentFile.c_str());
          str = iGetErrorText(err);
          Lab_State->Caption = str;
          if(err != E__OK)
          {
            ShowMessage(str);
            return;
          }
    }
}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::Button1Click(TObject *Sender)
{
    Lab_State->Caption = iGetErrorText(iVisitingKey());
}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::btn_GetKeyStateClick(TObject *Sender)
{
    Lab_State->Caption = iGetErrorText(iGetKeyState());
}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::Button2Click(TObject *Sender)
{
    Mainfrm->StartROI = true;
}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::Button3Click(TObject *Sender)
{
    Mainfrm->StartMatchROI = true;
}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::CheckBox3Click(TObject *Sender)
{
    Mainfrm->UsingRobustness = !Mainfrm->UsingRobustness;
    iSetRobustness(Mainfrm->iMatchModel, Mainfrm->UsingRobustness);
    //CheckBox3->Checked = Mainfrm->UsingRobustness;
}
//---------------------------------------------------------------------------

void __fastcall TiMatchfrm::CheckBox4Click(TObject *Sender)
{
    Mainfrm->UsingColorSimialrity = !Mainfrm->UsingColorSimialrity;

    iSetColorSimilarity(Mainfrm->iMatchModel, Mainfrm->UsingColorSimialrity);
    Mainfrm->ColorSensitivity = StrToInt(this->edt_ColorSensitivity->Text);
    iSetColorSensitivity(Mainfrm->iMatchModel, Mainfrm->ColorSensitivity);

    //CheckBox3->Checked = Mainfrm->UsingRobustness;
}
//---------------------------------------------------------------------------


void __fastcall TiMatchfrm::CheckBox5Click(TObject *Sender)
{
    Mainfrm->UsingSubpixel = !Mainfrm->UsingSubpixel;
    iSetSubPixel(Mainfrm->iMatchModel, Mainfrm->UsingSubpixel);
    //CheckBox5->Checked = Mainfrm->UsingSubpixel;
}
//---------------------------------------------------------------------------

