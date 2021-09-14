object SetPasswordForm: TSetPasswordForm
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = #1042#1089#1090#1072#1085#1086#1074#1083#1077#1085#1085#1103' '#1087#1072#1088#1086#1083#1102
  ClientHeight = 157
  ClientWidth = 219
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
    Left = 43
    Top = 5
    Width = 112
    Height = 13
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1085#1086#1074#1080#1081' '#1087#1072#1088#1086#1083#1100
  end
  object Label4: TLabel
    Left = 35
    Top = 60
    Width = 123
    Height = 13
    Caption = #1055#1086#1074#1090#1086#1088#1110#1090#1100' '#1085#1086#1074#1080#1081' '#1087#1072#1088#1086#1083#1100
  end
  object Password: TEdit
    Left = 8
    Top = 27
    Width = 201
    Height = 21
    PasswordChar = '*'
    TabOrder = 0
  end
  object ConfirmPassword: TEdit
    Left = 8
    Top = 82
    Width = 201
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
  end
  object Apply: TButton
    Left = 8
    Top = 120
    Width = 89
    Height = 25
    Caption = #1047#1072#1089#1090#1086#1089#1091#1074#1072#1090#1080
    TabOrder = 2
    OnClick = ApplyClick
  end
  object Cancel: TButton
    Left = 134
    Top = 120
    Width = 75
    Height = 25
    Caption = #1057#1082#1072#1089#1091#1074#1072#1090#1080
    TabOrder = 3
    OnClick = CancelClick
  end
end
