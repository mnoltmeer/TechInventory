object EditItemForm: TEditItemForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1056#1077#1076#1072#1075#1091#1074#1072#1085#1085#1103' '#1055#1088#1080#1089#1090#1088#1086#1102
  ClientHeight = 255
  ClientWidth = 578
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
  object Label7: TLabel
    Left = 6
    Top = 35
    Width = 104
    Height = 16
    Caption = #1030#1085#1074#1077#1085#1090#1072#1088#1085#1080#1081' '#8470' *'
  end
  object Label8: TLabel
    Left = 6
    Top = 69
    Width = 72
    Height = 16
    Caption = #1057#1077#1088#1110#1081#1085#1080#1081' '#8470
  end
  object Label9: TLabel
    Left = 6
    Top = 103
    Width = 97
    Height = 16
    Caption = #1052#1086#1076#1077#1083#1100'/'#1053#1072#1079#1074#1072' *'
  end
  object CurrentLocation: TLabel
    Left = 144
    Top = 153
    Width = 90
    Height = 16
    Caption = 'CurrentLocation'
  end
  object Label11: TLabel
    Left = 8
    Top = 189
    Width = 275
    Height = 16
    Caption = #1087#1086#1083#1103', '#1087#1086#1079#1085#1072#1095#1077#1085#1110' * '#1086#1073#1086#1074#39#1103#1079#1082#1086#1074#1110' '#1076#1083#1103' '#1079#1072#1087#1086#1074#1085#1077#1085#1085#1103
  end
  object Label1: TLabel
    Left = 0
    Top = 0
    Width = 578
    Height = 23
    Align = alTop
    Alignment = taCenter
    Caption = #1056#1077#1076#1072#1075#1091#1074#1072#1085#1085#1103' '#1055#1088#1080#1089#1090#1088#1086#1102
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ExplicitWidth = 204
  end
  object Inn: TEdit
    Left = 120
    Top = 32
    Width = 329
    Height = 24
    TabOrder = 0
  end
  object Sn: TEdit
    Left = 120
    Top = 66
    Width = 329
    Height = 24
    TabOrder = 1
  end
  object Model: TEdit
    Left = 120
    Top = 100
    Width = 449
    Height = 24
    TabOrder = 2
  end
  object SelectLocation: TButton
    Left = 8
    Top = 148
    Width = 120
    Height = 25
    Caption = #1054#1073#1088#1072#1090#1080' '#1051#1086#1082#1072#1094#1110#1102
    TabOrder = 3
    OnClick = SelectLocationClick
  end
  object Apply: TButton
    Left = 8
    Top = 217
    Width = 95
    Height = 25
    Caption = #1047#1072#1089#1090#1086#1089#1091#1074#1072#1090#1080
    TabOrder = 4
    OnClick = ApplyClick
  end
  object Cancel: TButton
    Left = 122
    Top = 217
    Width = 75
    Height = 25
    Caption = #1057#1082#1072#1089#1091#1074#1072#1090#1080
    TabOrder = 5
    OnClick = CancelClick
  end
end
