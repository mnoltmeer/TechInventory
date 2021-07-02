object ChangeMailForm: TChangeMailForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Change mail address'
  ClientHeight = 160
  ClientWidth = 306
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label3: TLabel
    Left = 8
    Top = 64
    Width = 79
    Height = 13
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1087#1072#1088#1086#1083#1100
  end
  object Label5: TLabel
    Left = 8
    Top = 8
    Width = 133
    Height = 13
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1072#1076#1088#1077#1089#1091' '#1077#1083'. '#1087#1086#1096#1090#1080
  end
  object EMailError: TLabel
    Left = 147
    Top = 5
    Width = 59
    Height = 16
    Caption = 'EMailError'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object PasswordError: TLabel
    Left = 93
    Top = 61
    Width = 84
    Height = 16
    Caption = 'PasswordError'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Password: TEdit
    Left = 8
    Top = 83
    Width = 169
    Height = 21
    PasswordChar = '*'
    TabOrder = 0
  end
  object EMail: TEdit
    Left = 8
    Top = 27
    Width = 289
    Height = 24
    TabOrder = 1
  end
  object Apply: TButton
    Left = 8
    Top = 124
    Width = 97
    Height = 25
    Caption = #1047#1072#1089#1090#1086#1089#1091#1074#1072#1090#1080
    TabOrder = 2
    OnClick = ApplyClick
  end
  object Cancel: TButton
    Left = 222
    Top = 124
    Width = 75
    Height = 25
    Caption = #1057#1082#1072#1089#1091#1074#1072#1090#1080
    TabOrder = 3
    OnClick = CancelClick
  end
end
