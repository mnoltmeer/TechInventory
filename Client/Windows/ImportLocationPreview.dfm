object ImportLocationPreviewForm: TImportLocationPreviewForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1030#1084#1087#1086#1088#1090' '#1087#1077#1088#1077#1083#1110#1082#1091' '#1083#1086#1082#1072#1094#1110#1081
  ClientHeight = 385
  ClientWidth = 561
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LocationGrid: TStringGrid
    Left = 0
    Top = 0
    Width = 561
    Height = 357
    Align = alClient
    ColCount = 3
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 0
    ExplicitWidth = 565
    ExplicitHeight = 256
    ColWidths = (
      3
      171
      377)
  end
  object Panel1: TPanel
    Left = 0
    Top = 357
    Width = 561
    Height = 28
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    ExplicitTop = 224
    ExplicitWidth = 381
    object Import: TButton
      Left = 0
      Top = 0
      Width = 75
      Height = 25
      Caption = #1030#1084#1087#1086#1088#1090#1091#1074#1072#1090#1080
      TabOrder = 0
      OnClick = ImportClick
    end
    object Cancel: TButton
      Left = 104
      Top = 0
      Width = 75
      Height = 25
      Caption = #1057#1082#1072#1089#1091#1074#1072#1090#1080
      TabOrder = 1
      OnClick = CancelClick
    end
  end
end
