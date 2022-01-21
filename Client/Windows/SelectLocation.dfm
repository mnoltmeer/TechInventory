object SelectLocationForm: TSelectLocationForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1042#1080#1073#1110#1088' '#1083#1086#1082#1072#1094#1110#1111
  ClientHeight = 280
  ClientWidth = 528
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
    Top = 22
    Width = 528
    Height = 230
    Align = alClient
    ColCount = 3
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSelect]
    ScrollBars = ssVertical
    TabOrder = 0
    Visible = False
    ExplicitTop = 56
    ExplicitHeight = 196
    ColWidths = (
      3
      113
      377)
  end
  object Panel1: TPanel
    Left = 0
    Top = 252
    Width = 528
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
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 528
    Height = 22
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 2
    ExplicitLeft = -33
    ExplicitWidth = 561
    object Label1: TLabel
      Left = 4
      Top = 2
      Width = 98
      Height = 16
      Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1087#1086#1083#1102':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object LbFilterField: TLabel
      Left = 116
      Top = 2
      Width = 46
      Height = 16
      Caption = '<none>'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object Filter: TEdit
      Left = 312
      Top = 1
      Width = 209
      Height = 21
      TabOrder = 0
      OnChange = FilterChange
    end
  end
  object FilteredGrid: TStringGrid
    Left = 0
    Top = 22
    Width = 528
    Height = 230
    Align = alClient
    ColCount = 3
    FixedCols = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 3
    OnDblClick = FilteredGridDblClick
    OnMouseUp = FilteredGridMouseUp
    ExplicitLeft = -33
    ExplicitTop = -55
    ExplicitWidth = 561
    ExplicitHeight = 335
    ColWidths = (
      3
      171
      377)
  end
end
