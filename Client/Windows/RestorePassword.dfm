object RestorePasswordForm: TRestorePasswordForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1042#1110#1076#1085#1086#1074#1083#1077#1085#1085#1103' '#1087#1072#1088#1086#1083#1102
  ClientHeight = 174
  ClientWidth = 396
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
  object EMailError: TLabel
    Left = 159
    Top = 70
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
  object Label5: TLabel
    Left = 8
    Top = 72
    Width = 133
    Height = 13
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1072#1076#1088#1077#1089#1091' '#1077#1083'. '#1087#1086#1096#1090#1080
  end
  object LoginError: TLabel
    Left = 94
    Top = 11
    Width = 59
    Height = 16
    Caption = 'LoginError'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 13
    Width = 68
    Height = 13
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1083#1086#1075#1110#1085
  end
  object EMail: TEdit
    Left = 8
    Top = 91
    Width = 289
    Height = 24
    TabOrder = 1
    OnKeyPress = EMailKeyPress
  end
  object Login: TEdit
    Left = 8
    Top = 32
    Width = 201
    Height = 24
    TabOrder = 0
    OnKeyPress = LoginKeyPress
  end
  object Apply: TButton
    Left = 8
    Top = 136
    Width = 97
    Height = 25
    Caption = #1057#1082#1080#1085#1091#1090#1080' '#1087#1072#1088#1086#1083#1100
    TabOrder = 2
    OnClick = ApplyClick
  end
  object Cancel: TButton
    Left = 304
    Top = 136
    Width = 75
    Height = 25
    Caption = #1042#1110#1076#1084#1086#1074#1072
    TabOrder = 3
    OnClick = CancelClick
  end
end
