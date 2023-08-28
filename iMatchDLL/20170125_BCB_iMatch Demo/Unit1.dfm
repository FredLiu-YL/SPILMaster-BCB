object Mainfrm: TMainfrm
  Left = 581
  Top = 179
  Width = 890
  Height = 634
  Caption = 'iVisionDEMO'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 8
    Top = 8
    Width = 457
    Height = 441
    OnMouseDown = Image1MouseDown
    OnMouseMove = Image1MouseMove
    OnMouseUp = Image1MouseUp
  end
  object MainMenu1: TMainMenu
    Left = 376
    Top = 8
    object File1: TMenuItem
      Caption = 'File'
      object Open1: TMenuItem
        Caption = 'Open iMatch Dialog'
        OnClick = Open1Click
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
    object Information1: TMenuItem
      Caption = 'Information'
      object Version1: TMenuItem
        Caption = 'Version'
        OnClick = Version1Click
      end
      object Key1: TMenuItem
        Caption = 'Key'
        OnClick = Key1Click
      end
    end
  end
end
