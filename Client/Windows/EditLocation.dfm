object EditLocationForm: TEditLocationForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1057#1090#1074#1086#1088#1077#1085#1085#1103'/'#1056#1077#1076#1072#1075#1091#1074#1072#1085#1085#1103' '#1051#1086#1082#1072#1094#1110#1111
  ClientHeight = 152
  ClientWidth = 441
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
  object Index: TLabeledEdit
    Left = 8
    Top = 24
    Width = 417
    Height = 21
    EditLabel.Width = 39
    EditLabel.Height = 13
    EditLabel.Caption = #1051#1086#1082#1072#1094#1110#1103
    TabOrder = 0
    OnKeyPress = IndexKeyPress
  end
  object Name: TLabeledEdit
    Left = 8
    Top = 72
    Width = 417
    Height = 21
    EditLabel.Width = 75
    EditLabel.Height = 13
    EditLabel.Caption = #1040#1076#1088#1077#1089#1072' '#1051#1086#1082#1072#1094#1110#1111
    TabOrder = 1
    OnKeyPress = NameKeyPress
  end
  object Apply: TButton
    Left = 8
    Top = 112
    Width = 75
    Height = 25
    Caption = #1057#1090#1074#1086#1088#1080#1090#1080
    TabOrder = 2
    OnClick = ApplyClick
  end
  object Cancel: TButton
    Left = 104
    Top = 112
    Width = 75
    Height = 25
    Caption = #1042#1110#1076#1084#1110#1085#1072
    TabOrder = 3
    OnClick = CancelClick
  end
end
