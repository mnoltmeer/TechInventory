object ChangePasswordForm: TChangePasswordForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1047#1084#1110#1085#1072' '#1087#1072#1088#1086#1083#1102
  ClientHeight = 212
  ClientWidth = 220
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object Label3: TLabel
    Left = 43
    Top = 61
    Width = 131
    Height = 16
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1085#1086#1074#1080#1081' '#1087#1072#1088#1086#1083#1100
  end
  object Label4: TLabel
    Left = 35
    Top = 116
    Width = 143
    Height = 16
    Caption = #1055#1086#1074#1090#1086#1088#1110#1090#1100' '#1085#1086#1074#1080#1081' '#1087#1072#1088#1086#1083#1100
  end
  object Label1: TLabel
    Left = 41
    Top = 8
    Width = 134
    Height = 16
    Caption = #1042#1074#1077#1076#1110#1090#1100' '#1089#1090#1072#1088#1080#1081' '#1087#1072#1088#1086#1083#1100
  end
  object Password: TEdit
    Left = 8
    Top = 83
    Width = 201
    Height = 24
    PasswordChar = '*'
    TabOrder = 1
  end
  object ConfirmPassword: TEdit
    Left = 8
    Top = 138
    Width = 201
    Height = 24
    PasswordChar = '*'
    TabOrder = 2
  end
  object Apply: TButton
    Left = 8
    Top = 176
    Width = 89
    Height = 25
    Caption = #1047#1072#1089#1090#1086#1089#1091#1074#1072#1090#1080
    TabOrder = 3
    OnClick = ApplyClick
  end
  object Cancel: TButton
    Left = 134
    Top = 176
    Width = 75
    Height = 25
    Caption = #1057#1082#1072#1089#1091#1074#1072#1090#1080
    TabOrder = 4
    OnClick = CancelClick
  end
  object OldPassword: TEdit
    Left = 8
    Top = 30
    Width = 201
    Height = 24
    PasswordChar = '*'
    TabOrder = 0
  end
end
