//---------------------------------------------------------------------------

#ifndef iMatchDialogH
#define iMatchDialogH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TiMatchfrm : public TForm
{
__published:	// IDE-managed Components
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TGroupBox *GroupBox2;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TPanel *Panel1;
    TRadioButton *RB_RotationYes;
    TRadioButton *RB_RotationNo;
    TPanel *Panel2;
    TRadioButton *RB_ScaleYes;
    TRadioButton *RB_ScaleNo;
    TPanel *Panel3;
    TRadioButton *RB_dontcareModelYes;
    TRadioButton *RB_dontcareModelNo;
    TEdit *edt_MinScore;
    TEdit *edt_MaxAngle;
    TEdit *edt_MinAngle;
    TEdit *edt_MaxScale;
    TEdit *edt_MinScale;
    TEdit *edt_DetectNums;
    TButton *btn_LoadColorImg;
    TButton *btn_LoadGrayImg;
    TButton *btn_Training;
    TButton *btn_Matching;
    TOpenDialog *OpenDialog1;
    TLabel *Label10;
    TEdit *edt_DontCareThreshold;
    TLabel *Label11;
    TEdit *edt_MinReduceArea;
    TGroupBox *GroupBox3;
    TButton *btn_LoadiMatchmodel;
    TButton *btn_SaveiMatchmodel;
    TSaveDialog *SaveDialog1;
    TStringGrid *StringGrid1;
    TButton *Button1;
    TButton *btn_GetKeyState;
    TCheckBox *CheckBox1;
    TGroupBox *GroupBox4;
    TCheckBox *CheckBox2;
    TGroupBox *GroupBox5;
    TButton *Button2;
    TButton *Button3;
    TCheckBox *CheckBox3;
    TLabel *Lab_State;
    TCheckBox *CheckBox4;
    TEdit *edt_ColorSensitivity;
    TLabel *Label12;
    TCheckBox *CheckBox5;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btn_LoadColorImgClick(TObject *Sender);
    void __fastcall btn_LoadGrayImgClick(TObject *Sender);
    void __fastcall btn_TrainingClick(TObject *Sender);
    void __fastcall btn_MatchingClick(TObject *Sender);
    void __fastcall btn_LoadiMatchmodelClick(TObject *Sender);
    void __fastcall btn_SaveiMatchmodelClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall btn_GetKeyStateClick(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
    void __fastcall CheckBox3Click(TObject *Sender);
    void __fastcall CheckBox4Click(TObject *Sender);
    void __fastcall CheckBox5Click(TObject *Sender);


private:	// User declarations
public:		// User declarations
    __fastcall TiMatchfrm(TComponent* Owner);
    void __fastcall UpdataToUI();
    void __fastcall UpdataToPara();
};
//---------------------------------------------------------------------------
extern PACKAGE TiMatchfrm *iMatchfrm;
//---------------------------------------------------------------------------
#endif
