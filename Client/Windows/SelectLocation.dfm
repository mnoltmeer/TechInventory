object SelectLocationForm: TSelectLocationForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1042#1080#1073#1110#1088' '#1083#1086#1082#1072#1094#1110#1111
  ClientHeight = 252
  ClientWidth = 381
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
  object LocationGrid: TStringGrid
    Left = 0
    Top = 0
    Width = 381
    Height = 224
    Align = alClient
    ColCount = 3
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
    ScrollBars = ssVertical
    TabOrder = 0
    OnDblClick = LocationGridDblClick
    OnMouseUp = LocationGridMouseUp
    ColWidths = (
      3
      113
      377)
  end
  object Panel1: TPanel
    Left = 0
    Top = 224
    Width = 381
    Height = 28
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Select: TButton
      Left = 0
      Top = 0
      Width = 75
      Height = 25
      Caption = #1042#1080#1073#1088#1072#1090#1080
      TabOrder = 0
      OnClick = SelectClick
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
