object iMatchfrm: TiMatchfrm
  Left = 343
  Top = 270
  Width = 740
  Height = 556
  BorderIcons = [biSystemMenu]
  Caption = 'iMatch Dialog'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label12: TLabel
    Left = 585
    Top = 456
    Width = 115
    Height = 13
    Caption = 'ColorSensitivity (0-100%)'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 0
    Width = 145
    Height = 473
    Caption = 'iMatch Parameters'
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 45
      Height = 13
      Alignment = taCenter
      Caption = 'MinScore'
      Layout = tlCenter
    end
    object Label2: TLabel
      Left = 16
      Top = 48
      Width = 47
      Height = 13
      Caption = 'MaxAngle'
    end
    object Label3: TLabel
      Left = 16
      Top = 72
      Width = 44
      Height = 13
      Caption = 'MinAngle'
    end
    object Label4: TLabel
      Left = 16
      Top = 96
      Width = 47
      Height = 13
      Caption = 'MaxScale'
    end
    object Label5: TLabel
      Left = 16
      Top = 120
      Width = 47
      Height = 13
      Caption = 'MaxScale'
    end
    object Label6: TLabel
      Left = 8
      Top = 144
      Width = 62
      Height = 13
      Caption = 'Detect Nums'
    end
    object Label10: TLabel
      Left = 8
      Top = 168
      Width = 100
      Height = 13
      Caption = 'Don'#39't Care Threshold'
    end
    object Label11: TLabel
      Left = 8
      Top = 208
      Width = 77
      Height = 13
      Caption = 'MinReduceArea'
    end
    object Lab_State: TLabel
      Left = 16
      Top = 424
      Width = 36
      Height = 20
      Caption = 'state'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 248
      Width = 129
      Height = 169
      Caption = 'Option'
      TabOrder = 0
      object Label7: TLabel
        Left = 8
        Top = 32
        Width = 40
        Height = 13
        Caption = 'Rotation'
      end
      object Label8: TLabel
        Left = 16
        Top = 80
        Width = 27
        Height = 13
        Caption = 'Scale'
      end
      object Label9: TLabel
        Left = 8
        Top = 128
        Width = 50
        Height = 13
        Caption = 'Don'#39't Care'
      end
      object Panel1: TPanel
        Left = 64
        Top = 8
        Width = 57
        Height = 57
        BevelOuter = bvNone
        TabOrder = 0
        object RB_RotationYes: TRadioButton
          Left = 8
          Top = 8
          Width = 41
          Height = 25
          Caption = 'Yes'
          TabOrder = 0
        end
        object RB_RotationNo: TRadioButton
          Left = 8
          Top = 32
          Width = 41
          Height = 25
          Caption = 'No'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
      end
      object Panel2: TPanel
        Left = 64
        Top = 56
        Width = 57
        Height = 57
        BevelOuter = bvNone
        TabOrder = 1
        object RB_ScaleYes: TRadioButton
          Left = 8
          Top = 8
          Width = 41
          Height = 25
          Caption = 'Yes'
          TabOrder = 0
        end
        object RB_ScaleNo: TRadioButton
          Left = 8
          Top = 32
          Width = 41
          Height = 25
          Caption = 'No'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
      end
      object Panel3: TPanel
        Left = 64
        Top = 112
        Width = 57
        Height = 49
        BevelOuter = bvNone
        TabOrder = 2
        object RB_dontcareModelYes: TRadioButton
          Left = 8
          Top = 0
          Width = 41
          Height = 25
          Caption = 'Yes'
          TabOrder = 0
        end
        object RB_dontcareModelNo: TRadioButton
          Left = 8
          Top = 24
          Width = 41
          Height = 25
          Caption = 'No'
          Checked = True
          TabOrder = 1
          TabStop = True
        end
      end
      object GroupBox4: TGroupBox
        Left = 0
        Top = 168
        Width = 185
        Height = 105
        Caption = 'GroupBox4'
        TabOrder = 3
      end
    end
    object edt_MinScore: TEdit
      Left = 72
      Top = 24
      Width = 57
      Height = 21
      AutoSize = False
      TabOrder = 1
      Text = '0.75'
    end
    object edt_MaxAngle: TEdit
      Left = 72
      Top = 48
      Width = 57
      Height = 21
      AutoSize = False
      TabOrder = 2
      Text = '30'
    end
    object edt_MinAngle: TEdit
      Left = 72
      Top = 72
      Width = 57
      Height = 21
      AutoSize = False
      TabOrder = 3
      Text = '-30'
    end
    object edt_MaxScale: TEdit
      Left = 72
      Top = 96
      Width = 57
      Height = 21
      AutoSize = False
      TabOrder = 4
      Text = '1.1'
    end
    object edt_MinScale: TEdit
      Left = 72
      Top = 120
      Width = 57
      Height = 21
      AutoSize = False
      TabOrder = 5
      Text = '0.9'
    end
    object edt_DetectNums: TEdit
      Left = 72
      Top = 144
      Width = 57
      Height = 21
      AutoSize = False
      TabOrder = 6
      Text = '1'
    end
    object edt_DontCareThreshold: TEdit
      Left = 72
      Top = 184
      Width = 57
      Height = 21
      AutoSize = False
      TabOrder = 7
      Text = '0'
    end
    object edt_MinReduceArea: TEdit
      Left = 72
      Top = 224
      Width = 57
      Height = 21
      AutoSize = False
      TabOrder = 8
      Text = '64'
    end
  end
  object btn_LoadColorImg: TButton
    Left = 168
    Top = 16
    Width = 113
    Height = 49
    Caption = 'Load Color Img'
    TabOrder = 1
    OnClick = btn_LoadColorImgClick
  end
  object btn_LoadGrayImg: TButton
    Left = 296
    Top = 16
    Width = 113
    Height = 49
    Caption = 'Load Gray Img'
    TabOrder = 2
    OnClick = btn_LoadGrayImgClick
  end
  object btn_Training: TButton
    Left = 416
    Top = 32
    Width = 113
    Height = 33
    Caption = 'Training'
    TabOrder = 3
    OnClick = btn_TrainingClick
  end
  object btn_Matching: TButton
    Left = 552
    Top = 32
    Width = 113
    Height = 33
    Caption = 'Matching'
    TabOrder = 4
    OnClick = btn_MatchingClick
  end
  object GroupBox3: TGroupBox
    Left = 168
    Top = 384
    Width = 113
    Height = 97
    Caption = 'iMatch Model'
    TabOrder = 5
    object btn_LoadiMatchmodel: TButton
      Left = 8
      Top = 16
      Width = 97
      Height = 33
      Caption = 'Load'
      TabOrder = 0
      OnClick = btn_LoadiMatchmodelClick
    end
    object btn_SaveiMatchmodel: TButton
      Left = 8
      Top = 56
      Width = 97
      Height = 33
      Caption = 'Save'
      TabOrder = 1
      OnClick = btn_SaveiMatchmodelClick
    end
  end
  object StringGrid1: TStringGrid
    Left = 168
    Top = 80
    Width = 513
    Height = 305
    ColCount = 7
    DefaultColWidth = 70
    RowCount = 2
    TabOrder = 6
  end
  object Button1: TButton
    Left = 288
    Top = 400
    Width = 89
    Height = 33
    Caption = 'VisitingKeyPro'
    TabOrder = 7
    OnClick = Button1Click
  end
  object btn_GetKeyState: TButton
    Left = 288
    Top = 440
    Width = 89
    Height = 33
    Caption = 'GetKeyState'
    TabOrder = 8
    OnClick = btn_GetKeyStateClick
  end
  object CheckBox1: TCheckBox
    Left = 423
    Top = 8
    Width = 113
    Height = 25
    Caption = 'TrainingFromROI'
    TabOrder = 9
  end
  object CheckBox2: TCheckBox
    Left = 551
    Top = 8
    Width = 113
    Height = 25
    Caption = 'MatchFromROI'
    TabOrder = 10
  end
  object GroupBox5: TGroupBox
    Left = 384
    Top = 392
    Width = 137
    Height = 89
    Caption = 'ROI'
    TabOrder = 11
    object Button2: TButton
      Left = 10
      Top = 13
      Width = 113
      Height = 33
      Caption = 'Setting Training ROI'
      TabOrder = 0
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 10
      Top = 48
      Width = 113
      Height = 33
      Caption = 'Setting Match ROI'
      TabOrder = 1
      OnClick = Button3Click
    end
  end
  object CheckBox3: TCheckBox
    Left = 535
    Top = 400
    Width = 113
    Height = 25
    Caption = 'robustness'
    TabOrder = 12
    OnClick = CheckBox3Click
  end
  object CheckBox4: TCheckBox
    Left = 535
    Top = 424
    Width = 113
    Height = 25
    Caption = 'ColorSimilarity'
    TabOrder = 13
    OnClick = CheckBox4Click
  end
  object edt_ColorSensitivity: TEdit
    Left = 534
    Top = 453
    Width = 49
    Height = 21
    TabOrder = 14
  end
  object CheckBox5: TCheckBox
    Left = 536
    Top = 480
    Width = 97
    Height = 17
    Caption = 'Subpixel'
    Checked = True
    State = cbChecked
    TabOrder = 15
    OnClick = CheckBox5Click
  end
  object OpenDialog1: TOpenDialog
    Filter = 'BMP|*.bmp|Jpeg|*jpeg|Jpeg|*.jpg|Png|*.png|TIFF|*.tiff|TIFF|*.tif'
    Left = 608
    Top = 392
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = 'imm'
    Filter = '*.imm'
    Left = 640
    Top = 392
  end
end
