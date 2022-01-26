object ClientForm: TClientForm
  Left = 286
  Top = 193
  Caption = #1058#1077#1093#1030#1085#1074#1077#1085#1090' '#1050#1083#1110#1108#1085#1090
  ClientHeight = 617
  ClientWidth = 811
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 16
  object PnAddItem: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 5
    object Label5: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1042#1074#1086#1076' '#1074' '#1073#1072#1079#1091' '#1076#1072#1085#1080#1093' '#1085#1086#1074#1086#1075#1086' '#1055#1088#1080#1089#1090#1088#1086#1102
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 319
    end
    object LbInn: TLabel
      Left = 6
      Top = 112
      Width = 104
      Height = 16
      Caption = #1030#1085#1074#1077#1085#1090#1072#1088#1085#1080#1081' '#8470' *'
    end
    object Label8: TLabel
      Left = 6
      Top = 146
      Width = 72
      Height = 16
      Caption = #1057#1077#1088#1110#1081#1085#1080#1081' '#8470
    end
    object LbModel: TLabel
      Left = 6
      Top = 180
      Width = 97
      Height = 16
      Caption = #1052#1086#1076#1077#1083#1100'/'#1053#1072#1079#1074#1072' *'
    end
    object AddItemCurrentLocation: TLabel
      Left = 150
      Top = 226
      Width = 138
      Height = 16
      Caption = 'AddItemCurrentLocation'
    end
    object Label11: TLabel
      Left = 8
      Top = 269
      Width = 275
      Height = 16
      Caption = #1087#1086#1083#1103', '#1087#1086#1079#1085#1072#1095#1077#1085#1110' * '#1086#1073#1086#1074#39#1103#1079#1082#1086#1074#1110' '#1076#1083#1103' '#1079#1072#1087#1086#1074#1085#1077#1085#1085#1103
    end
    object LbID: TLabel
      Left = 6
      Top = 59
      Width = 86
      Height = 16
      Caption = 'ID '#1055#1088#1080#1089#1090#1088#1086#1102' *'
    end
    object IDError: TLabel
      Left = 249
      Top = 59
      Width = 41
      Height = 16
      Caption = 'IDError'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object InnError: TLabel
      Left = 468
      Top = 111
      Width = 47
      Height = 16
      Caption = 'InnError'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object ModelError: TLabel
      Left = 585
      Top = 176
      Width = 63
      Height = 16
      Caption = 'ModelError'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object AddItemNewInn: TEdit
      Left = 120
      Top = 109
      Width = 329
      Height = 24
      TabOrder = 1
    end
    object AddItemNewSn: TEdit
      Left = 120
      Top = 143
      Width = 329
      Height = 24
      TabOrder = 2
    end
    object AddItemNewModel: TEdit
      Left = 120
      Top = 177
      Width = 449
      Height = 24
      TabOrder = 3
    end
    object AddItemCreate: TButton
      Left = 6
      Top = 307
      Width = 75
      Height = 25
      Caption = #1057#1090#1074#1086#1088#1080#1090#1080
      TabOrder = 5
      OnClick = AddItemCreateClick
    end
    object AddItemClearFields: TButton
      Left = 112
      Top = 307
      Width = 75
      Height = 25
      Caption = #1054#1095#1080#1089#1090#1080#1090#1080
      TabOrder = 6
      OnClick = AddItemClearFieldsClick
    end
    object AddItemSelectLocation: TButton
      Left = 6
      Top = 223
      Width = 128
      Height = 25
      Caption = #1054#1073#1088#1072#1090#1080' '#1051#1086#1082#1072#1094#1110#1102
      TabOrder = 4
      OnClick = AddItemSelectLocationClick
    end
    object AddItemNewID: TEdit
      Left = 120
      Top = 56
      Width = 112
      Height = 24
      TabOrder = 0
    end
  end
  object PnHome: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 3
    object Label1: TLabel
      Left = 6
      Top = 11
      Width = 153
      Height = 16
      Caption = #1040#1082#1090#1091#1072#1083#1100#1085#1072' '#1074#1077#1088#1089#1110#1103' '#1082#1083#1110#1108#1085#1090#1072':'
    end
    object ActualClientVersion: TLabel
      Left = 165
      Top = 11
      Width = 110
      Height = 16
      Caption = 'ActualClientVersion'
    end
    object Label2: TLabel
      Left = 6
      Top = 43
      Width = 215
      Height = 16
      Caption = #1055#1086#1090#1086#1095#1085#1072' '#1072#1076#1088#1077#1089#1072' '#1077#1083#1077#1082#1090#1088#1086#1085#1085#1086#1111' '#1087#1086#1096#1090#1080':'
    end
    object CurrentMail: TLabel
      Left = 230
      Top = 43
      Width = 66
      Height = 16
      Caption = 'CurrentMail'
    end
    object UpdateClient: TButton
      Left = 455
      Top = 3
      Width = 75
      Height = 25
      Caption = #1054#1085#1086#1074#1080#1090#1080
      TabOrder = 0
      OnClick = UpdateClientClick
    end
    object ChangeMail: TButton
      Left = 455
      Top = 34
      Width = 75
      Height = 25
      Caption = #1047#1084#1110#1085#1080#1090#1080
      TabOrder = 1
      OnClick = ChangeMailClick
    end
    object ChangePassword: TButton
      Left = 6
      Top = 81
      Width = 105
      Height = 25
      Caption = #1047#1084#1110#1085#1080#1090#1080' '#1087#1072#1088#1086#1083#1100
      TabOrder = 2
      OnClick = ChangePasswordClick
    end
  end
  object MenuPanel: TPanel
    Left = 0
    Top = 33
    Width = 40
    Height = 476
    Align = alLeft
    TabOrder = 0
    object MnCheckItems: TBitBtn
      Left = 1
      Top = 75
      Width = 36
      Height = 36
      Hint = #1047#1083#1110#1095#1091#1074#1072#1083#1100#1085#1072' '#1074#1110#1076#1086#1084#1110#1089#1090#1100
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = MnCheckItemsClick
    end
    object MnShowItems: TBitBtn
      Left = 1
      Top = 149
      Width = 36
      Height = 36
      Hint = #1055#1077#1088#1077#1075#1083#1103#1076' '#1055#1088#1080#1089#1090#1088#1086#1111#1074
      ParentShowHint = False
      ShowHint = True
      TabOrder = 4
      OnClick = MnShowItemsClick
    end
    object MnAddItem: TBitBtn
      Left = 1
      Top = 112
      Width = 36
      Height = 36
      Hint = #1044#1086#1076#1072#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081
      ParentShowHint = False
      ShowHint = True
      TabOrder = 3
      OnClick = MnAddItemClick
    end
    object MnShowEvents: TBitBtn
      Left = 1
      Top = 186
      Width = 36
      Height = 36
      Hint = #1055#1077#1088#1077#1075#1083#1103#1076' '#1055#1086#1076#1110#1081
      ParentShowHint = False
      ShowHint = True
      TabOrder = 5
      OnClick = MnShowEventsClick
    end
    object MnHome: TBitBtn
      Left = 1
      Top = 1
      Width = 36
      Height = 36
      Hint = #1043#1086#1083#1086#1074#1085#1072
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = MnHomeClick
    end
    object MnAdmUsers: TBitBtn
      Left = 1
      Top = 223
      Width = 36
      Height = 36
      Hint = #1042#1077#1076#1077#1085#1085#1103' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1110#1074
      ParentShowHint = False
      ShowHint = True
      TabOrder = 6
      OnClick = MnAdmUsersClick
    end
    object MnAdmLocations: TBitBtn
      Left = 1
      Top = 260
      Width = 36
      Height = 36
      Hint = #1059#1087#1088#1072#1074#1083#1110#1085#1085#1103' '#1051#1086#1082#1072#1094#1110#1103#1084#1080
      ParentShowHint = False
      ShowHint = True
      TabOrder = 7
      OnClick = MnAdmLocationsClick
    end
    object MnAdmLogs: TBitBtn
      Left = 1
      Top = 297
      Width = 36
      Height = 36
      Hint = #1055#1077#1088#1077#1075#1083#1103#1076' '#1083#1086#1075#1110#1074
      ParentShowHint = False
      ShowHint = True
      TabOrder = 8
      OnClick = MnAdmLogsClick
    end
    object MnAdmManage: TBitBtn
      Left = 1
      Top = 334
      Width = 36
      Height = 36
      Hint = #1050#1077#1088#1091#1074#1072#1085#1085#1103' '#1057#1077#1088#1074#1077#1088#1086#1084
      ParentShowHint = False
      ShowHint = True
      TabOrder = 9
      OnClick = MnAdmManageClick
    end
    object MnCheckItem: TBitBtn
      Left = 1
      Top = 38
      Width = 36
      Height = 36
      Hint = #1057#1082#1072#1085#1091#1074#1072#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = MnCheckItemClick
    end
  end
  object InfoPanel: TPanel
    Left = 0
    Top = 0
    Width = 811
    Height = 33
    Align = alTop
    TabOrder = 1
    object ClientVersion: TLabel
      Left = 3
      Top = 6
      Width = 75
      Height = 16
      Caption = 'ClientVersion'
    end
    object ServerInfo: TLabel
      Left = 278
      Top = 6
      Width = 60
      Height = 16
      Caption = 'ServerInfo'
    end
    object UserInfo: TLabel
      Left = 608
      Top = 6
      Width = 48
      Height = 16
      Caption = 'UserInfo'
    end
    object Reconnect: TBitBtn
      Left = 248
      Top = 3
      Width = 24
      Height = 24
      Hint = #1047#1084#1110#1085#1080#1090#1080' '#1089#1077#1088#1074#1077#1088
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = ReconnectClick
    end
  end
  object PnCheckItem: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 4
    object Label3: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1055#1077#1088#1077#1075#1083#1103#1076' '#1076#1072#1085#1080#1093' '#1087#1088#1086' '#1055#1088#1080#1089#1090#1088#1110#1081
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 265
    end
    object Label4: TLabel
      Left = 3
      Top = 63
      Width = 325
      Height = 16
      Alignment = taCenter
      Caption = #1042#1110#1076#1089#1082#1072#1085#1091#1081#1090#1077', '#1072#1073#1086' '#1074#1074#1077#1076#1110#1090#1100' '#1074#1088#1091#1095#1085#1091' '#1082#1086#1076' '#1090#1072' '#1085#1072#1090#1080#1089#1085#1110#1090#1100' Enter'
    end
    object Label27: TLabel
      Left = 3
      Top = 106
      Width = 92
      Height = 16
      Caption = #1030#1085#1074#1077#1085#1090#1072#1088#1085#1080#1081' '#8470
    end
    object Label28: TLabel
      Left = 3
      Top = 140
      Width = 72
      Height = 16
      Caption = #1057#1077#1088#1110#1081#1085#1080#1081' '#8470
    end
    object Label29: TLabel
      Left = 3
      Top = 174
      Width = 85
      Height = 16
      Caption = #1052#1086#1076#1077#1083#1100'/'#1053#1072#1079#1074#1072
    end
    object CheckItemCurrentLocation: TLabel
      Left = 120
      Top = 216
      Width = 150
      Height = 16
      Caption = 'CheckItemCurrentLocation'
    end
    object Label30: TLabel
      Left = 3
      Top = 216
      Width = 102
      Height = 16
      Caption = #1055#1086#1090#1086#1095#1085#1072' '#1083#1086#1082#1072#1094#1110#1103':'
    end
    object Label31: TLabel
      Left = 3
      Top = 256
      Width = 138
      Height = 16
      Caption = #1042#1086#1089#1090#1072#1085#1085#1108' '#1073#1091#1074' '#1079#1084#1110#1085#1077#1085#1080#1081':'
    end
    object CheckItemLastAgent: TLabel
      Left = 152
      Top = 256
      Width = 116
      Height = 16
      Caption = 'CheckItemLastAgent'
    end
    object CheckItemScannedCode: TEdit
      Left = 3
      Top = 35
      Width = 325
      Height = 24
      TabOrder = 0
      OnKeyPress = CheckItemScannedCodeKeyPress
    end
    object EditDataPanel: TPanel
      Left = 1
      Top = 450
      Width = 769
      Height = 25
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 1
      object CheckItemRemove: TBitBtn
        Left = 54
        Top = 0
        Width = 24
        Height = 24
        Hint = #1042#1080#1076#1072#1083#1080#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081' '#1079' '#1073#1072#1079#1080' '#1076#1072#1085#1080#1093
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = CheckItemRemoveClick
      end
      object CheckItemEdit: TBitBtn
        Left = 27
        Top = 0
        Width = 24
        Height = 24
        Hint = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1076#1072#1085#1110' '#1055#1088#1080#1089#1090#1088#1086#1102
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = CheckItemEditClick
      end
      object CheckItemRefresh: TBitBtn
        Left = 0
        Top = 0
        Width = 24
        Height = 24
        Hint = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1110' '#1090#1072#1073#1083#1080#1094#1110
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = CheckItemRefreshClick
      end
      object CheckItemShowHistory: TBitBtn
        Left = 81
        Top = 0
        Width = 24
        Height = 24
        Hint = #1030#1089#1090#1086#1088#1110#1103' '#1086#1087#1077#1088#1072#1094#1110#1081' '#1079' '#1055#1088#1080#1089#1090#1088#1086#1108#1084
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        OnClick = CheckItemShowHistoryClick
      end
    end
    object CheckItemInn: TEdit
      Left = 117
      Top = 103
      Width = 329
      Height = 24
      Enabled = False
      TabOrder = 2
    end
    object CheckItemSn: TEdit
      Left = 117
      Top = 137
      Width = 329
      Height = 24
      Enabled = False
      TabOrder = 3
    end
    object CheckItemModel: TEdit
      Left = 117
      Top = 171
      Width = 449
      Height = 24
      Enabled = False
      TabOrder = 4
    end
  end
  object LogPanel: TPanel
    Left = 0
    Top = 509
    Width = 811
    Height = 108
    Align = alBottom
    BevelOuter = bvLowered
    TabOrder = 2
    object ActionLog: TMemo
      Left = 1
      Top = 22
      Width = 809
      Height = 85
      TabStop = False
      Align = alClient
      BevelOuter = bvRaised
      ScrollBars = ssVertical
      TabOrder = 0
    end
    object Panel1: TPanel
      Left = 1
      Top = 1
      Width = 809
      Height = 21
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object Label6: TLabel
        Left = 2
        Top = 2
        Width = 64
        Height = 16
        Caption = #1051#1086#1075' '#1089#1077#1072#1085#1089#1091
      end
      object SaveSessionLog: TButton
        Left = 72
        Top = 2
        Width = 18
        Height = 17
        Hint = #1047#1073#1077#1088#1077#1075#1090#1080' '#1083#1086#1075' '#1091' '#1092#1072#1081#1083
        Caption = '#'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = SaveSessionLogClick
      end
    end
  end
  object PnShowItems: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 6
    object Label17: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1055#1077#1088#1077#1075#1083#1103#1076' '#1055#1088#1080#1089#1090#1088#1086#1111#1074' '#1091' '#1074#1082#1072#1079#1072#1085#1110#1081' '#1051#1086#1082#1072#1094#1110#1111
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 340
    end
    object Panel2: TPanel
      Left = 1
      Top = 24
      Width = 769
      Height = 35
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object ShowItemsCurrentLocation: TLabel
        Left = 128
        Top = 10
        Width = 154
        Height = 16
        Caption = 'ShowItemsCurrentLocation'
      end
      object ShowItemsSelectLocation: TButton
        Left = 2
        Top = 6
        Width = 120
        Height = 25
        Caption = #1054#1073#1088#1072#1090#1080' '#1051#1086#1082#1072#1094#1110#1102
        TabOrder = 0
        OnClick = ShowItemsSelectLocationClick
      end
      object ShowItemsRequest: TButton
        Left = 507
        Top = 6
        Width = 108
        Height = 25
        Caption = #1054#1090#1088#1080#1084#1072#1090#1080' '#1076#1072#1085#1110
        TabOrder = 1
        OnClick = ShowItemsRequestClick
      end
    end
    object Panel3: TPanel
      Left = 1
      Top = 450
      Width = 769
      Height = 25
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 1
      object ShowItemsRemove: TBitBtn
        Left = 54
        Top = 0
        Width = 24
        Height = 24
        Hint = #1042#1080#1076#1072#1083#1080#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081' '#1079' '#1073#1072#1079#1080' '#1076#1072#1085#1080#1093
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = ShowItemsRemoveClick
      end
      object ShowItemsEdit: TBitBtn
        Left = 27
        Top = 0
        Width = 24
        Height = 24
        Hint = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1076#1072#1085#1110' '#1055#1088#1080#1089#1090#1088#1086#1102
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = ShowItemsEditClick
      end
      object ShowItemsRefresh: TBitBtn
        Left = 0
        Top = 0
        Width = 24
        Height = 24
        Hint = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1110' '#1090#1072#1073#1083#1080#1094#1110
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = ShowItemsRefreshClick
      end
    end
    object ShowItemsResult: TStringGrid
      Left = 1
      Top = 79
      Width = 769
      Height = 371
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 2
      Visible = False
    end
    object ShowItemsFiltered: TStringGrid
      Left = 1
      Top = 79
      Width = 769
      Height = 371
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditItem
      TabOrder = 3
      OnMouseUp = FilteredGridMouseUp
    end
    object Panel16: TPanel
      Left = 1
      Top = 59
      Width = 769
      Height = 20
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 4
      object Label34: TLabel
        Left = 229
        Top = 0
        Width = 98
        Height = 20
        Align = alLeft
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1087#1086#1083#1102':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitHeight = 16
      end
      object Label35: TLabel
        Left = 327
        Top = 0
        Width = 46
        Height = 20
        Align = alLeft
        Caption = '<none>'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ExplicitHeight = 16
      end
      object Image7: TImage
        Left = 0
        Top = 0
        Width = 20
        Height = 20
        Align = alLeft
        Picture.Data = {
          0954506E67496D61676589504E470D0A1A0A0000000D49484452000000800000
          00800803000000F4E091F90000000467414D410000B18F0BFC61050000018050
          4C5445000000FF9900FF9A00FF9800FF9700FF9B00FF9D00FF9600F57B00F57C
          00F77C00F47C00F67E00F57D00F47B00F87E00FF7700FFAB00FFFF00FF9900FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800
          FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9700FD9300FD9200FD9200FD
          9300FF9800FF9800FF9900FF9800FE9300F67F00F67D00F67D00F67D00F67F00
          FD9200FF9800F47B00F57C00F57C00F57C00F57B00F57C00F57C00F57C00F57C
          00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F5
          7C00F57C00F77D00F57C00F57C00F57C00F57C00F67D00F47C00F57C00F57C00
          F57C00F57C00F57C00F57C00F57C00F57D00F57D00FC8F00FD9100FC9000FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800F57C00F57D00FD9100
          FFFFFF413EC9140000007B74524E530000000000000000000000000000000000
          00000811080A4FAECDB1530B0983F5F7905D07ADB710CB4EF45E85F351AFC5CA
          F0FBFAF2C658050C1079F7FCF88711060C98FDA20E16B1B91923C6CD2834D8DD
          3A48E7EA52015FF2F46F02067BF9FA89070C0EFEDE6CFD8AFE8081E65BB23703
          FCD15FE78C1C1D41020145DF2FF300000001624B47447F48BF71E50000000970
          48597300021BEF00021BEF0149171B830000000774494D4507E40B020D1B3B8C
          3DBB43000002D24944415478DAEDD93D6B145114C6F1FBCC18D889B0E00B0445
          5450110B85141629420A4929015F10C10F61A3DF412D05D17E15096229821616
          CA22585858681110C5AC88C6882FCBE20E6B0C24B23377EE3DF7DE73672CCE94
          33C99CDF9E9D7F180854C30704200001FC4700605B3D1CACA85C034877003501
          80DEA6607364BA1BB850CB7CA56EE3E7970DC10600C9CE565DF395EAA4EFF2D1
          3820DD8F73B5CD576A7175252F000EE04C8D807BA3A522A0F10DA8433855DBFC
          CED637AA0058ABA08D85BAE627C3E562057FBF8449AC1F51678F92E1C4873DBD
          E5F2DF01A526301D1FB076FF41AB9B0FFF9D18BFDE9A016622CEEF024FFBE3A2
          C24F64B3381E11F0024FC6E797009398C374B4F92FF138FD6106A84CCDE368A4
          F9AFF070CBF7C2B9F223D7C6091C8932FF351E0DFAC5939A673E3B091C8C307F
          09B85F9AAF7D23CA4E037BD9E7BF07EE96E7EB5FC9B2F36FD963EC62DF1DCDFC
          8A77C2083196033401F863D4046802B0C7A80BD008608E511BA019C01AA33E40
          0B8031C68A006D00B618AB02B402B862AC0AD00EE089B132403B8025C6EA0009
          0086180D015200C1319A02240102633406480304C5680E90080889D11C2015E0
          1FA325402AC03B465B806480678CD600E900AF18ED013A003C622404E802708E
          9112A013C035464A806E00B7184901BA019C62A405E80870889118A02B801C23
          3540670031467280EE00528CF4003D009418E901FA00EC313A04E803588FF158
          AFF2F2AE8F9FE9017A01543B3D6BF895A94F8B7DA72FC0E37F46E9E1B9EDD557
          BFDECAE9B7128000042000010840000210800004200001084000021080000420
          801880D59BCD02BEE1469380CE0270BD39C02FE0D9F374E8783B3EC000B896B8
          7E7C3E80D7F6F9009EDB6703F86E9F09E0BF7D1640C8F6390041DB0F07046E3F
          1410BCFD40C000C9D5B0ED070138B61F00E0D9BE3F20FCD90F015C7C30CFB47D
          4FC0A5DF5CDBF7045CC615B68FEF03E03E04200001340EF80395EC6A90A3E611
          2E0000002574455874646174653A63726561746500323032302D31312D303254
          31333A32373A35392B30303A30307EB49C380000002574455874646174653A6D
          6F6469667900323032302D31312D30325431333A32373A35392B30303A30300F
          E924840000002074455874736F6674776172650068747470733A2F2F696D6167
          656D616769636B2E6F7267BCCF1D9D00000018744558745468756D623A3A446F
          63756D656E743A3A50616765730031A7FFBB2F00000018744558745468756D62
          3A3A496D6167653A3A486569676874003531328F8D5381000000177445587454
          68756D623A3A496D6167653A3A5769647468003531321C7C03DC000000197445
          58745468756D623A3A4D696D657479706500696D6167652F706E673FB2564E00
          000017744558745468756D623A3A4D54696D6500313630343332333637392AB1
          878100000012744558745468756D623A3A53697A65003435393842423A1CC9BC
          00000046744558745468756D623A3A5552490066696C653A2F2F2E2F75706C6F
          6164732F35362F584E724946746D2F323632312F6775695F66696C7465725F69
          636F6E5F3135373134372E706E6755BBDFA00000000049454E44AE426082}
        Stretch = True
      end
      object Edit5: TEdit
        Left = 20
        Top = 0
        Width = 209
        Height = 20
        Align = alLeft
        TabOrder = 0
        OnChange = FilterChange
        ExplicitHeight = 24
      end
    end
  end
  object PnShowEvents: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 7
    object Label13: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1055#1077#1088#1077#1075#1083#1103#1076' '#1087#1086#1076#1110#1081
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 137
    end
    object ShowEventsResult: TStringGrid
      Left = 1
      Top = 138
      Width = 769
      Height = 337
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 0
      Visible = False
    end
    object Panel4: TPanel
      Left = 1
      Top = 24
      Width = 769
      Height = 94
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object Label15: TLabel
        Left = 81
        Top = 62
        Width = 7
        Height = 16
        Caption = #1047
      end
      object Label16: TLabel
        Left = 209
        Top = 62
        Width = 14
        Height = 16
        Caption = #1087#1086
      end
      object Label14: TLabel
        Left = 5
        Top = 6
        Width = 61
        Height = 16
        Caption = #1064#1091#1082#1072#1090#1080' '#1079#1072
      end
      object Label32: TLabel
        Left = 165
        Top = 6
        Width = 103
        Height = 16
        Caption = #1042#1074#1077#1076#1110#1090#1100' '#1079#1085#1072#1095#1077#1085#1085#1103
      end
      object ShowEventsInn: TEdit
        Left = 165
        Top = 27
        Width = 283
        Height = 24
        TabOrder = 0
        OnChange = ShowEventsInnChange
        OnKeyPress = ShowEventsInnKeyPress
      end
      object ShowEventsDateFrom: TDateTimePicker
        Left = 99
        Top = 58
        Width = 104
        Height = 24
        Date = 44154.000000000000000000
        Time = 0.639949120370147300
        TabOrder = 1
      end
      object ShowEventsDateTo: TDateTimePicker
        Left = 229
        Top = 57
        Width = 103
        Height = 24
        Date = 44154.000000000000000000
        Time = 0.640191886574029900
        TabOrder = 2
      end
      object ShowEventsApply: TButton
        Left = 467
        Top = 28
        Width = 75
        Height = 25
        Caption = #1055#1086#1082#1072#1079#1072#1090#1080
        TabOrder = 3
        OnClick = ShowEventsApplyClick
      end
      object ShowEventsDateFilter: TCheckBox
        Left = 5
        Top = 61
        Width = 59
        Height = 17
        Caption = #1047#1072' '#1076#1072#1090#1091
        TabOrder = 4
        OnClick = ShowEventsDateFilterClick
      end
      object ShowEventsSearchType: TComboBox
        Left = 5
        Top = 28
        Width = 154
        Height = 24
        ItemIndex = 0
        TabOrder = 5
        Text = 'ID '#1055#1088#1080#1089#1090#1088#1086#1102
        Items.Strings = (
          'ID '#1055#1088#1080#1089#1090#1088#1086#1102
          #1030#1085#1074#1077#1085#1090#1072#1088#1085#1080#1084' '#1085#1086#1084#1077#1088#1086#1084
          #1057#1077#1088#1110#1081#1085#1080#1084' '#1085#1086#1084#1077#1088#1086#1084)
      end
    end
    object ShowEventsFiltered: TStringGrid
      Left = 1
      Top = 138
      Width = 769
      Height = 337
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 2
      OnMouseUp = FilteredGridMouseUp
    end
    object Panel17: TPanel
      Left = 1
      Top = 118
      Width = 769
      Height = 20
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 3
      object Label36: TLabel
        Left = 229
        Top = 0
        Width = 98
        Height = 20
        Align = alLeft
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1087#1086#1083#1102':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitHeight = 16
      end
      object Label37: TLabel
        Left = 327
        Top = 0
        Width = 46
        Height = 20
        Align = alLeft
        Caption = '<none>'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ExplicitHeight = 16
      end
      object Image6: TImage
        Left = 0
        Top = 0
        Width = 20
        Height = 20
        Align = alLeft
        Picture.Data = {
          0954506E67496D61676589504E470D0A1A0A0000000D49484452000000800000
          00800803000000F4E091F90000000467414D410000B18F0BFC61050000018050
          4C5445000000FF9900FF9A00FF9800FF9700FF9B00FF9D00FF9600F57B00F57C
          00F77C00F47C00F67E00F57D00F47B00F87E00FF7700FFAB00FFFF00FF9900FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800
          FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9700FD9300FD9200FD9200FD
          9300FF9800FF9800FF9900FF9800FE9300F67F00F67D00F67D00F67D00F67F00
          FD9200FF9800F47B00F57C00F57C00F57C00F57B00F57C00F57C00F57C00F57C
          00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F5
          7C00F57C00F77D00F57C00F57C00F57C00F57C00F67D00F47C00F57C00F57C00
          F57C00F57C00F57C00F57C00F57C00F57D00F57D00FC8F00FD9100FC9000FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800F57C00F57D00FD9100
          FFFFFF413EC9140000007B74524E530000000000000000000000000000000000
          00000811080A4FAECDB1530B0983F5F7905D07ADB710CB4EF45E85F351AFC5CA
          F0FBFAF2C658050C1079F7FCF88711060C98FDA20E16B1B91923C6CD2834D8DD
          3A48E7EA52015FF2F46F02067BF9FA89070C0EFEDE6CFD8AFE8081E65BB23703
          FCD15FE78C1C1D41020145DF2FF300000001624B47447F48BF71E50000000970
          48597300021BEF00021BEF0149171B830000000774494D4507E40B020D1B3B8C
          3DBB43000002D24944415478DAEDD93D6B145114C6F1FBCC18D889B0E00B0445
          5450110B85141629420A4929015F10C10F61A3DF412D05D17E15096229821616
          CA22585858681110C5AC88C6882FCBE20E6B0C24B23377EE3DF7DE73672CCE94
          33C99CDF9E9D7F180854C30704200001FC4700605B3D1CACA85C034877003501
          80DEA6607364BA1BB850CB7CA56EE3E7970DC10600C9CE565DF395EAA4EFF2D1
          3820DD8F73B5CD576A7175252F000EE04C8D807BA3A522A0F10DA8433855DBFC
          CED637AA0058ABA08D85BAE627C3E562057FBF8449AC1F51678F92E1C4873DBD
          E5F2DF01A526301D1FB076FF41AB9B0FFF9D18BFDE9A016622CEEF024FFBE3A2
          C24F64B3381E11F0024FC6E797009398C374B4F92FF138FD6106A84CCDE368A4
          F9AFF070CBF7C2B9F223D7C6091C8932FF351E0DFAC5939A673E3B091C8C307F
          09B85F9AAF7D23CA4E037BD9E7BF07EE96E7EB5FC9B2F36FD963EC62DF1DCDFC
          8A77C2083196033401F863D4046802B0C7A80BD008608E511BA019C01AA33E40
          0B8031C68A006D00B618AB02B402B862AC0AD00EE089B132403B8025C6EA0009
          0086180D015200C1319A02240102633406480304C5680E90080889D11C2015E0
          1FA325402AC03B465B806480678CD600E900AF18ED013A003C622404E802708E
          9112A013C035464A806E00B7184901BA019C62A405E80870889118A02B801C23
          3540670031467280EE00528CF4003D009418E901FA00EC313A04E803588FF158
          AFF2F2AE8F9FE9017A01543B3D6BF895A94F8B7DA72FC0E37F46E9E1B9EDD557
          BFDECAE9B7128000042000010840000210800004200001084000021080000420
          801880D59BCD02BEE1469380CE0270BD39C02FE0D9F374E8783B3EC000B896B8
          7E7C3E80D7F6F9009EDB6703F86E9F09E0BF7D1640C8F6390041DB0F07046E3F
          1410BCFD40C000C9D5B0ED070138B61F00E0D9BE3F20FCD90F015C7C30CFB47D
          4FC0A5DF5CDBF7045CC615B68FEF03E03E04200001340EF80395EC6A90A3E611
          2E0000002574455874646174653A63726561746500323032302D31312D303254
          31333A32373A35392B30303A30307EB49C380000002574455874646174653A6D
          6F6469667900323032302D31312D30325431333A32373A35392B30303A30300F
          E924840000002074455874736F6674776172650068747470733A2F2F696D6167
          656D616769636B2E6F7267BCCF1D9D00000018744558745468756D623A3A446F
          63756D656E743A3A50616765730031A7FFBB2F00000018744558745468756D62
          3A3A496D6167653A3A486569676874003531328F8D5381000000177445587454
          68756D623A3A496D6167653A3A5769647468003531321C7C03DC000000197445
          58745468756D623A3A4D696D657479706500696D6167652F706E673FB2564E00
          000017744558745468756D623A3A4D54696D6500313630343332333637392AB1
          878100000012744558745468756D623A3A53697A65003435393842423A1CC9BC
          00000046744558745468756D623A3A5552490066696C653A2F2F2E2F75706C6F
          6164732F35362F584E724946746D2F323632312F6775695F66696C7465725F69
          636F6E5F3135373134372E706E6755BBDFA00000000049454E44AE426082}
        Stretch = True
      end
      object Edit6: TEdit
        Left = 20
        Top = 0
        Width = 209
        Height = 20
        Align = alLeft
        TabOrder = 0
        OnChange = FilterChange
        ExplicitHeight = 24
      end
    end
  end
  object PnCheckItems: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 12
    object Label23: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1047#1083#1110#1095#1091#1074#1072#1083#1100#1085#1072' '#1074#1110#1076#1086#1084#1110#1089#1090#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 191
    end
    object Panel9: TPanel
      Left = 1
      Top = 24
      Width = 769
      Height = 76
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object CheckItemsCurrentLocation: TLabel
        Left = 132
        Top = 14
        Width = 156
        Height = 16
        Caption = 'CheckItemsCurrentLocation'
      end
      object CheckError: TLabel
        Left = 528
        Top = 44
        Width = 63
        Height = 16
        Caption = 'CheckError'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object CheckItemsSelectLocation: TButton
        Left = 2
        Top = 10
        Width = 121
        Height = 25
        Caption = #1054#1073#1088#1072#1090#1080' '#1051#1086#1082#1072#1094#1110#1102
        TabOrder = 0
        OnClick = CheckItemsSelectLocationClick
      end
      object CheckItemsScannedCode: TLabeledEdit
        Left = 237
        Top = 41
        Width = 138
        Height = 24
        EditLabel.Width = 228
        EditLabel.Height = 16
        EditLabel.Caption = #1042#1074#1077#1076#1110#1090#1100' '#1072#1073#1086' '#1074#1110#1076#1089#1082#1072#1085#1091#1081#1090#1077' '#1082#1086#1076' '#1055#1088#1080#1089#1090#1088#1086#1102
        LabelPosition = lpLeft
        TabOrder = 1
        OnKeyPress = CheckItemsScannedCodeKeyPress
      end
      object CheckItemsAddToList: TButton
        Left = 381
        Top = 41
        Width = 137
        Height = 25
        Caption = #1044#1086#1076#1072#1090#1080' '#1076#1086' '#1074#1110#1076#1086#1084#1086#1089#1090#1110
        TabOrder = 2
        OnClick = CheckItemsAddToListClick
      end
    end
    object Panel10: TPanel
      Left = 1
      Top = 450
      Width = 769
      Height = 25
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 1
      object CheckItemsSendToUnknown: TBitBtn
        Left = 54
        Top = 0
        Width = 24
        Height = 24
        Hint = #1055#1077#1088#1077#1085#1077#1089#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081' '#1076#1086' '#1053#1077#1079#39#1103#1089#1086#1074#1072#1085#1080#1093
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = CheckItemsSendToUnknownClick
      end
      object CheckItemsEdit: TBitBtn
        Left = 27
        Top = 0
        Width = 24
        Height = 24
        Hint = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1076#1072#1085#1110' '#1055#1088#1080#1089#1090#1088#1086#1102
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = CheckItemsEditClick
      end
      object CheckItemsDelete: TBitBtn
        Left = 0
        Top = 0
        Width = 24
        Height = 24
        Hint = #1042#1080#1076#1072#1083#1080#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081' '#1079' '#1074#1110#1076#1086#1084#1086#1089#1090#1110
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = CheckItemsDeleteClick
      end
    end
    object CheckItemsResult: TStringGrid
      Left = 1
      Top = 120
      Width = 769
      Height = 330
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 2
      Visible = False
      OnMouseUp = CheckItemResultMouseUp
    end
    object Panel15: TPanel
      Left = 1
      Top = 100
      Width = 769
      Height = 20
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 3
      object Label26: TLabel
        Left = 229
        Top = 0
        Width = 98
        Height = 20
        Align = alLeft
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1087#1086#1083#1102':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitHeight = 16
      end
      object Label33: TLabel
        Left = 327
        Top = 0
        Width = 46
        Height = 20
        Align = alLeft
        Caption = '<none>'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ExplicitHeight = 16
      end
      object Image5: TImage
        Left = 0
        Top = 0
        Width = 20
        Height = 20
        Align = alLeft
        Picture.Data = {
          0954506E67496D61676589504E470D0A1A0A0000000D49484452000000800000
          00800803000000F4E091F90000000467414D410000B18F0BFC61050000018050
          4C5445000000FF9900FF9A00FF9800FF9700FF9B00FF9D00FF9600F57B00F57C
          00F77C00F47C00F67E00F57D00F47B00F87E00FF7700FFAB00FFFF00FF9900FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800
          FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9700FD9300FD9200FD9200FD
          9300FF9800FF9800FF9900FF9800FE9300F67F00F67D00F67D00F67D00F67F00
          FD9200FF9800F47B00F57C00F57C00F57C00F57B00F57C00F57C00F57C00F57C
          00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F5
          7C00F57C00F77D00F57C00F57C00F57C00F57C00F67D00F47C00F57C00F57C00
          F57C00F57C00F57C00F57C00F57C00F57D00F57D00FC8F00FD9100FC9000FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800F57C00F57D00FD9100
          FFFFFF413EC9140000007B74524E530000000000000000000000000000000000
          00000811080A4FAECDB1530B0983F5F7905D07ADB710CB4EF45E85F351AFC5CA
          F0FBFAF2C658050C1079F7FCF88711060C98FDA20E16B1B91923C6CD2834D8DD
          3A48E7EA52015FF2F46F02067BF9FA89070C0EFEDE6CFD8AFE8081E65BB23703
          FCD15FE78C1C1D41020145DF2FF300000001624B47447F48BF71E50000000970
          48597300021BEF00021BEF0149171B830000000774494D4507E40B020D1B3B8C
          3DBB43000002D24944415478DAEDD93D6B145114C6F1FBCC18D889B0E00B0445
          5450110B85141629420A4929015F10C10F61A3DF412D05D17E15096229821616
          CA22585858681110C5AC88C6882FCBE20E6B0C24B23377EE3DF7DE73672CCE94
          33C99CDF9E9D7F180854C30704200001FC4700605B3D1CACA85C034877003501
          80DEA6607364BA1BB850CB7CA56EE3E7970DC10600C9CE565DF395EAA4EFF2D1
          3820DD8F73B5CD576A7175252F000EE04C8D807BA3A522A0F10DA8433855DBFC
          CED637AA0058ABA08D85BAE627C3E562057FBF8449AC1F51678F92E1C4873DBD
          E5F2DF01A526301D1FB076FF41AB9B0FFF9D18BFDE9A016622CEEF024FFBE3A2
          C24F64B3381E11F0024FC6E797009398C374B4F92FF138FD6106A84CCDE368A4
          F9AFF070CBF7C2B9F223D7C6091C8932FF351E0DFAC5939A673E3B091C8C307F
          09B85F9AAF7D23CA4E037BD9E7BF07EE96E7EB5FC9B2F36FD963EC62DF1DCDFC
          8A77C2083196033401F863D4046802B0C7A80BD008608E511BA019C01AA33E40
          0B8031C68A006D00B618AB02B402B862AC0AD00EE089B132403B8025C6EA0009
          0086180D015200C1319A02240102633406480304C5680E90080889D11C2015E0
          1FA325402AC03B465B806480678CD600E900AF18ED013A003C622404E802708E
          9112A013C035464A806E00B7184901BA019C62A405E80870889118A02B801C23
          3540670031467280EE00528CF4003D009418E901FA00EC313A04E803588FF158
          AFF2F2AE8F9FE9017A01543B3D6BF895A94F8B7DA72FC0E37F46E9E1B9EDD557
          BFDECAE9B7128000042000010840000210800004200001084000021080000420
          801880D59BCD02BEE1469380CE0270BD39C02FE0D9F374E8783B3EC000B896B8
          7E7C3E80D7F6F9009EDB6703F86E9F09E0BF7D1640C8F6390041DB0F07046E3F
          1410BCFD40C000C9D5B0ED070138B61F00E0D9BE3F20FCD90F015C7C30CFB47D
          4FC0A5DF5CDBF7045CC615B68FEF03E03E04200001340EF80395EC6A90A3E611
          2E0000002574455874646174653A63726561746500323032302D31312D303254
          31333A32373A35392B30303A30307EB49C380000002574455874646174653A6D
          6F6469667900323032302D31312D30325431333A32373A35392B30303A30300F
          E924840000002074455874736F6674776172650068747470733A2F2F696D6167
          656D616769636B2E6F7267BCCF1D9D00000018744558745468756D623A3A446F
          63756D656E743A3A50616765730031A7FFBB2F00000018744558745468756D62
          3A3A496D6167653A3A486569676874003531328F8D5381000000177445587454
          68756D623A3A496D6167653A3A5769647468003531321C7C03DC000000197445
          58745468756D623A3A4D696D657479706500696D6167652F706E673FB2564E00
          000017744558745468756D623A3A4D54696D6500313630343332333637392AB1
          878100000012744558745468756D623A3A53697A65003435393842423A1CC9BC
          00000046744558745468756D623A3A5552490066696C653A2F2F2E2F75706C6F
          6164732F35362F584E724946746D2F323632312F6775695F66696C7465725F69
          636F6E5F3135373134372E706E6755BBDFA00000000049454E44AE426082}
        Stretch = True
      end
      object Edit4: TEdit
        Left = 20
        Top = 0
        Width = 209
        Height = 20
        Align = alLeft
        TabOrder = 0
        OnChange = FilterChange
        ExplicitHeight = 24
      end
    end
    object CheckItemsFiltered: TStringGrid
      Left = 1
      Top = 120
      Width = 769
      Height = 330
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPItemOptions
      TabOrder = 4
      OnDrawCell = CheckItemsResultDrawCell
      OnMouseUp = FilteredGridMouseUp
    end
  end
  object PnAdmUsers: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 8
    object Label18: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1050#1077#1088#1091#1074#1072#1085#1085#1103' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1072#1084#1080
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 230
    end
    object Panel5: TPanel
      Left = 1
      Top = 450
      Width = 769
      Height = 25
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 0
      object AdmUsersRefresh: TBitBtn
        Left = 0
        Top = 0
        Width = 24
        Height = 24
        Hint = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1110' '#1090#1072#1073#1083#1080#1094#1110
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = AdmUsersRefreshClick
      end
      object AdmUsersAdd: TBitBtn
        Left = 27
        Top = 0
        Width = 24
        Height = 24
        Hint = #1057#1090#1074#1086#1088#1080#1090#1080' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1072
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = AdmUsersAddClick
      end
      object AdmUsersSetPwd: TBitBtn
        Left = 54
        Top = 0
        Width = 24
        Height = 24
        Hint = #1042#1089#1090#1072#1085#1086#1074#1080#1090#1080' '#1087#1072#1088#1086#1083#1100
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = AdmUsersSetPwdClick
      end
      object AdmUsersLock: TBitBtn
        Left = 81
        Top = 0
        Width = 24
        Height = 24
        Hint = #1047#1072#1073#1083#1086#1082#1091#1074#1072#1090#1080' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1072
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        OnClick = AdmUsersLockClick
      end
      object AdmUsersUnlock: TBitBtn
        Left = 108
        Top = 0
        Width = 24
        Height = 24
        Hint = #1056#1086#1079#1073#1083#1086#1082#1091#1074#1072#1090#1080' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1072
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        OnClick = AdmUsersUnlockClick
      end
    end
    object AdmUsersResult: TStringGrid
      Left = 1
      Top = 44
      Width = 769
      Height = 406
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditUser
      TabOrder = 1
      Visible = False
    end
    object Panel14: TPanel
      Left = 1
      Top = 24
      Width = 769
      Height = 20
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
      object Label24: TLabel
        Left = 229
        Top = 0
        Width = 98
        Height = 20
        Align = alLeft
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1087#1086#1083#1102':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitHeight = 16
      end
      object Label25: TLabel
        Left = 327
        Top = 0
        Width = 46
        Height = 20
        Align = alLeft
        Caption = '<none>'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ExplicitHeight = 16
      end
      object Image4: TImage
        Left = 0
        Top = 0
        Width = 20
        Height = 20
        Align = alLeft
        Picture.Data = {
          0954506E67496D61676589504E470D0A1A0A0000000D49484452000000800000
          00800803000000F4E091F90000000467414D410000B18F0BFC61050000018050
          4C5445000000FF9900FF9A00FF9800FF9700FF9B00FF9D00FF9600F57B00F57C
          00F77C00F47C00F67E00F57D00F47B00F87E00FF7700FFAB00FFFF00FF9900FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800
          FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9700FD9300FD9200FD9200FD
          9300FF9800FF9800FF9900FF9800FE9300F67F00F67D00F67D00F67D00F67F00
          FD9200FF9800F47B00F57C00F57C00F57C00F57B00F57C00F57C00F57C00F57C
          00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F5
          7C00F57C00F77D00F57C00F57C00F57C00F57C00F67D00F47C00F57C00F57C00
          F57C00F57C00F57C00F57C00F57C00F57D00F57D00FC8F00FD9100FC9000FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800F57C00F57D00FD9100
          FFFFFF413EC9140000007B74524E530000000000000000000000000000000000
          00000811080A4FAECDB1530B0983F5F7905D07ADB710CB4EF45E85F351AFC5CA
          F0FBFAF2C658050C1079F7FCF88711060C98FDA20E16B1B91923C6CD2834D8DD
          3A48E7EA52015FF2F46F02067BF9FA89070C0EFEDE6CFD8AFE8081E65BB23703
          FCD15FE78C1C1D41020145DF2FF300000001624B47447F48BF71E50000000970
          48597300021BEF00021BEF0149171B830000000774494D4507E40B020D1B3B8C
          3DBB43000002D24944415478DAEDD93D6B145114C6F1FBCC18D889B0E00B0445
          5450110B85141629420A4929015F10C10F61A3DF412D05D17E15096229821616
          CA22585858681110C5AC88C6882FCBE20E6B0C24B23377EE3DF7DE73672CCE94
          33C99CDF9E9D7F180854C30704200001FC4700605B3D1CACA85C034877003501
          80DEA6607364BA1BB850CB7CA56EE3E7970DC10600C9CE565DF395EAA4EFF2D1
          3820DD8F73B5CD576A7175252F000EE04C8D807BA3A522A0F10DA8433855DBFC
          CED637AA0058ABA08D85BAE627C3E562057FBF8449AC1F51678F92E1C4873DBD
          E5F2DF01A526301D1FB076FF41AB9B0FFF9D18BFDE9A016622CEEF024FFBE3A2
          C24F64B3381E11F0024FC6E797009398C374B4F92FF138FD6106A84CCDE368A4
          F9AFF070CBF7C2B9F223D7C6091C8932FF351E0DFAC5939A673E3B091C8C307F
          09B85F9AAF7D23CA4E037BD9E7BF07EE96E7EB5FC9B2F36FD963EC62DF1DCDFC
          8A77C2083196033401F863D4046802B0C7A80BD008608E511BA019C01AA33E40
          0B8031C68A006D00B618AB02B402B862AC0AD00EE089B132403B8025C6EA0009
          0086180D015200C1319A02240102633406480304C5680E90080889D11C2015E0
          1FA325402AC03B465B806480678CD600E900AF18ED013A003C622404E802708E
          9112A013C035464A806E00B7184901BA019C62A405E80870889118A02B801C23
          3540670031467280EE00528CF4003D009418E901FA00EC313A04E803588FF158
          AFF2F2AE8F9FE9017A01543B3D6BF895A94F8B7DA72FC0E37F46E9E1B9EDD557
          BFDECAE9B7128000042000010840000210800004200001084000021080000420
          801880D59BCD02BEE1469380CE0270BD39C02FE0D9F374E8783B3EC000B896B8
          7E7C3E80D7F6F9009EDB6703F86E9F09E0BF7D1640C8F6390041DB0F07046E3F
          1410BCFD40C000C9D5B0ED070138B61F00E0D9BE3F20FCD90F015C7C30CFB47D
          4FC0A5DF5CDBF7045CC615B68FEF03E03E04200001340EF80395EC6A90A3E611
          2E0000002574455874646174653A63726561746500323032302D31312D303254
          31333A32373A35392B30303A30307EB49C380000002574455874646174653A6D
          6F6469667900323032302D31312D30325431333A32373A35392B30303A30300F
          E924840000002074455874736F6674776172650068747470733A2F2F696D6167
          656D616769636B2E6F7267BCCF1D9D00000018744558745468756D623A3A446F
          63756D656E743A3A50616765730031A7FFBB2F00000018744558745468756D62
          3A3A496D6167653A3A486569676874003531328F8D5381000000177445587454
          68756D623A3A496D6167653A3A5769647468003531321C7C03DC000000197445
          58745468756D623A3A4D696D657479706500696D6167652F706E673FB2564E00
          000017744558745468756D623A3A4D54696D6500313630343332333637392AB1
          878100000012744558745468756D623A3A53697A65003435393842423A1CC9BC
          00000046744558745468756D623A3A5552490066696C653A2F2F2E2F75706C6F
          6164732F35362F584E724946746D2F323632312F6775695F66696C7465725F69
          636F6E5F3135373134372E706E6755BBDFA00000000049454E44AE426082}
        Stretch = True
      end
      object Edit3: TEdit
        Left = 20
        Top = 0
        Width = 209
        Height = 20
        Align = alLeft
        TabOrder = 0
        OnChange = FilterChange
        ExplicitHeight = 24
      end
    end
    object AdmUsersFiltered: TStringGrid
      Left = 1
      Top = 44
      Width = 769
      Height = 406
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditUser
      TabOrder = 3
      OnMouseUp = FilteredGridMouseUp
    end
  end
  object PnAdmManage: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 11
    object Label7: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1042#1080#1082#1086#1085#1072#1085#1085#1103' '#1079#1072#1087#1080#1090#1110#1074' '#1076#1086' '#1041#1044
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 221
    end
    object AdmRequestResult: TStringGrid
      Left = 1
      Top = 44
      Width = 769
      Height = 247
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 0
      Visible = False
      OnMouseUp = FilteredGridMouseUp
    end
    object QueryText: TMemo
      Left = 1
      Top = 291
      Width = 769
      Height = 143
      Align = alBottom
      TabOrder = 1
      OnKeyUp = QueryTextKeyUp
    end
    object Panel8: TPanel
      Left = 1
      Top = 434
      Width = 769
      Height = 41
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 2
      object Execute: TButton
        Left = 0
        Top = 6
        Width = 140
        Height = 25
        Caption = #1042#1080#1082#1086#1085#1072#1090#1080' '#1079#1072#1087#1080#1090' (F9)'
        TabOrder = 0
        OnClick = ExecuteClick
      end
    end
    object Panel13: TPanel
      Left = 1
      Top = 24
      Width = 769
      Height = 20
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 3
      object Label21: TLabel
        Left = 229
        Top = 0
        Width = 98
        Height = 20
        Align = alLeft
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1087#1086#1083#1102':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitHeight = 16
      end
      object Label22: TLabel
        Left = 327
        Top = 0
        Width = 46
        Height = 20
        Align = alLeft
        Caption = '<none>'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ExplicitHeight = 16
      end
      object Image3: TImage
        Left = 0
        Top = 0
        Width = 20
        Height = 20
        Align = alLeft
        Picture.Data = {
          0954506E67496D61676589504E470D0A1A0A0000000D49484452000000800000
          00800803000000F4E091F90000000467414D410000B18F0BFC61050000018050
          4C5445000000FF9900FF9A00FF9800FF9700FF9B00FF9D00FF9600F57B00F57C
          00F77C00F47C00F67E00F57D00F47B00F87E00FF7700FFAB00FFFF00FF9900FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800
          FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9700FD9300FD9200FD9200FD
          9300FF9800FF9800FF9900FF9800FE9300F67F00F67D00F67D00F67D00F67F00
          FD9200FF9800F47B00F57C00F57C00F57C00F57B00F57C00F57C00F57C00F57C
          00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F5
          7C00F57C00F77D00F57C00F57C00F57C00F57C00F67D00F47C00F57C00F57C00
          F57C00F57C00F57C00F57C00F57C00F57D00F57D00FC8F00FD9100FC9000FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800F57C00F57D00FD9100
          FFFFFF413EC9140000007B74524E530000000000000000000000000000000000
          00000811080A4FAECDB1530B0983F5F7905D07ADB710CB4EF45E85F351AFC5CA
          F0FBFAF2C658050C1079F7FCF88711060C98FDA20E16B1B91923C6CD2834D8DD
          3A48E7EA52015FF2F46F02067BF9FA89070C0EFEDE6CFD8AFE8081E65BB23703
          FCD15FE78C1C1D41020145DF2FF300000001624B47447F48BF71E50000000970
          48597300021BEF00021BEF0149171B830000000774494D4507E40B020D1B3B8C
          3DBB43000002D24944415478DAEDD93D6B145114C6F1FBCC18D889B0E00B0445
          5450110B85141629420A4929015F10C10F61A3DF412D05D17E15096229821616
          CA22585858681110C5AC88C6882FCBE20E6B0C24B23377EE3DF7DE73672CCE94
          33C99CDF9E9D7F180854C30704200001FC4700605B3D1CACA85C034877003501
          80DEA6607364BA1BB850CB7CA56EE3E7970DC10600C9CE565DF395EAA4EFF2D1
          3820DD8F73B5CD576A7175252F000EE04C8D807BA3A522A0F10DA8433855DBFC
          CED637AA0058ABA08D85BAE627C3E562057FBF8449AC1F51678F92E1C4873DBD
          E5F2DF01A526301D1FB076FF41AB9B0FFF9D18BFDE9A016622CEEF024FFBE3A2
          C24F64B3381E11F0024FC6E797009398C374B4F92FF138FD6106A84CCDE368A4
          F9AFF070CBF7C2B9F223D7C6091C8932FF351E0DFAC5939A673E3B091C8C307F
          09B85F9AAF7D23CA4E037BD9E7BF07EE96E7EB5FC9B2F36FD963EC62DF1DCDFC
          8A77C2083196033401F863D4046802B0C7A80BD008608E511BA019C01AA33E40
          0B8031C68A006D00B618AB02B402B862AC0AD00EE089B132403B8025C6EA0009
          0086180D015200C1319A02240102633406480304C5680E90080889D11C2015E0
          1FA325402AC03B465B806480678CD600E900AF18ED013A003C622404E802708E
          9112A013C035464A806E00B7184901BA019C62A405E80870889118A02B801C23
          3540670031467280EE00528CF4003D009418E901FA00EC313A04E803588FF158
          AFF2F2AE8F9FE9017A01543B3D6BF895A94F8B7DA72FC0E37F46E9E1B9EDD557
          BFDECAE9B7128000042000010840000210800004200001084000021080000420
          801880D59BCD02BEE1469380CE0270BD39C02FE0D9F374E8783B3EC000B896B8
          7E7C3E80D7F6F9009EDB6703F86E9F09E0BF7D1640C8F6390041DB0F07046E3F
          1410BCFD40C000C9D5B0ED070138B61F00E0D9BE3F20FCD90F015C7C30CFB47D
          4FC0A5DF5CDBF7045CC615B68FEF03E03E04200001340EF80395EC6A90A3E611
          2E0000002574455874646174653A63726561746500323032302D31312D303254
          31333A32373A35392B30303A30307EB49C380000002574455874646174653A6D
          6F6469667900323032302D31312D30325431333A32373A35392B30303A30300F
          E924840000002074455874736F6674776172650068747470733A2F2F696D6167
          656D616769636B2E6F7267BCCF1D9D00000018744558745468756D623A3A446F
          63756D656E743A3A50616765730031A7FFBB2F00000018744558745468756D62
          3A3A496D6167653A3A486569676874003531328F8D5381000000177445587454
          68756D623A3A496D6167653A3A5769647468003531321C7C03DC000000197445
          58745468756D623A3A4D696D657479706500696D6167652F706E673FB2564E00
          000017744558745468756D623A3A4D54696D6500313630343332333637392AB1
          878100000012744558745468756D623A3A53697A65003435393842423A1CC9BC
          00000046744558745468756D623A3A5552490066696C653A2F2F2E2F75706C6F
          6164732F35362F584E724946746D2F323632312F6775695F66696C7465725F69
          636F6E5F3135373134372E706E6755BBDFA00000000049454E44AE426082}
        Stretch = True
      end
      object Edit2: TEdit
        Left = 20
        Top = 0
        Width = 209
        Height = 20
        Align = alLeft
        TabOrder = 0
        OnChange = FilterChange
        ExplicitHeight = 24
      end
    end
    object AdmRequestFiltered: TStringGrid
      Left = 1
      Top = 44
      Width = 769
      Height = 247
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 4
      OnMouseUp = FilteredGridMouseUp
    end
  end
  object PnAdmLogs: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 10
    object Label20: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1055#1077#1088#1077#1075#1083#1103#1076' '#1083#1086#1075#1110#1074
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 133
    end
    object Panel7: TPanel
      Left = 1
      Top = 24
      Width = 769
      Height = 41
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 0
      object AdmLogsDate: TDateTimePicker
        Left = 2
        Top = 9
        Width = 121
        Height = 24
        Date = 44154.000000000000000000
        Time = 0.640191886574029900
        TabOrder = 0
      end
      object AdmLogsShow: TButton
        Left = 140
        Top = 8
        Width = 75
        Height = 25
        Caption = #1055#1086#1082#1072#1079#1072#1090#1080
        TabOrder = 1
        OnClick = AdmLogsShowClick
      end
    end
    object AdmLogsResult: TStringGrid
      Left = 1
      Top = 85
      Width = 769
      Height = 390
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 1
      Visible = False
    end
    object Panel12: TPanel
      Left = 1
      Top = 65
      Width = 769
      Height = 20
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
      object Label10: TLabel
        Left = 229
        Top = 0
        Width = 98
        Height = 20
        Align = alLeft
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1087#1086#1083#1102':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitHeight = 16
      end
      object Label12: TLabel
        Left = 327
        Top = 0
        Width = 46
        Height = 20
        Align = alLeft
        Caption = '<none>'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ExplicitHeight = 16
      end
      object Image2: TImage
        Left = 0
        Top = 0
        Width = 20
        Height = 20
        Align = alLeft
        Picture.Data = {
          0954506E67496D61676589504E470D0A1A0A0000000D49484452000000800000
          00800803000000F4E091F90000000467414D410000B18F0BFC61050000018050
          4C5445000000FF9900FF9A00FF9800FF9700FF9B00FF9D00FF9600F57B00F57C
          00F77C00F47C00F67E00F57D00F47B00F87E00FF7700FFAB00FFFF00FF9900FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800
          FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9700FD9300FD9200FD9200FD
          9300FF9800FF9800FF9900FF9800FE9300F67F00F67D00F67D00F67D00F67F00
          FD9200FF9800F47B00F57C00F57C00F57C00F57B00F57C00F57C00F57C00F57C
          00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F5
          7C00F57C00F77D00F57C00F57C00F57C00F57C00F67D00F47C00F57C00F57C00
          F57C00F57C00F57C00F57C00F57C00F57D00F57D00FC8F00FD9100FC9000FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800F57C00F57D00FD9100
          FFFFFF413EC9140000007B74524E530000000000000000000000000000000000
          00000811080A4FAECDB1530B0983F5F7905D07ADB710CB4EF45E85F351AFC5CA
          F0FBFAF2C658050C1079F7FCF88711060C98FDA20E16B1B91923C6CD2834D8DD
          3A48E7EA52015FF2F46F02067BF9FA89070C0EFEDE6CFD8AFE8081E65BB23703
          FCD15FE78C1C1D41020145DF2FF300000001624B47447F48BF71E50000000970
          48597300021BEF00021BEF0149171B830000000774494D4507E40B020D1B3B8C
          3DBB43000002D24944415478DAEDD93D6B145114C6F1FBCC18D889B0E00B0445
          5450110B85141629420A4929015F10C10F61A3DF412D05D17E15096229821616
          CA22585858681110C5AC88C6882FCBE20E6B0C24B23377EE3DF7DE73672CCE94
          33C99CDF9E9D7F180854C30704200001FC4700605B3D1CACA85C034877003501
          80DEA6607364BA1BB850CB7CA56EE3E7970DC10600C9CE565DF395EAA4EFF2D1
          3820DD8F73B5CD576A7175252F000EE04C8D807BA3A522A0F10DA8433855DBFC
          CED637AA0058ABA08D85BAE627C3E562057FBF8449AC1F51678F92E1C4873DBD
          E5F2DF01A526301D1FB076FF41AB9B0FFF9D18BFDE9A016622CEEF024FFBE3A2
          C24F64B3381E11F0024FC6E797009398C374B4F92FF138FD6106A84CCDE368A4
          F9AFF070CBF7C2B9F223D7C6091C8932FF351E0DFAC5939A673E3B091C8C307F
          09B85F9AAF7D23CA4E037BD9E7BF07EE96E7EB5FC9B2F36FD963EC62DF1DCDFC
          8A77C2083196033401F863D4046802B0C7A80BD008608E511BA019C01AA33E40
          0B8031C68A006D00B618AB02B402B862AC0AD00EE089B132403B8025C6EA0009
          0086180D015200C1319A02240102633406480304C5680E90080889D11C2015E0
          1FA325402AC03B465B806480678CD600E900AF18ED013A003C622404E802708E
          9112A013C035464A806E00B7184901BA019C62A405E80870889118A02B801C23
          3540670031467280EE00528CF4003D009418E901FA00EC313A04E803588FF158
          AFF2F2AE8F9FE9017A01543B3D6BF895A94F8B7DA72FC0E37F46E9E1B9EDD557
          BFDECAE9B7128000042000010840000210800004200001084000021080000420
          801880D59BCD02BEE1469380CE0270BD39C02FE0D9F374E8783B3EC000B896B8
          7E7C3E80D7F6F9009EDB6703F86E9F09E0BF7D1640C8F6390041DB0F07046E3F
          1410BCFD40C000C9D5B0ED070138B61F00E0D9BE3F20FCD90F015C7C30CFB47D
          4FC0A5DF5CDBF7045CC615B68FEF03E03E04200001340EF80395EC6A90A3E611
          2E0000002574455874646174653A63726561746500323032302D31312D303254
          31333A32373A35392B30303A30307EB49C380000002574455874646174653A6D
          6F6469667900323032302D31312D30325431333A32373A35392B30303A30300F
          E924840000002074455874736F6674776172650068747470733A2F2F696D6167
          656D616769636B2E6F7267BCCF1D9D00000018744558745468756D623A3A446F
          63756D656E743A3A50616765730031A7FFBB2F00000018744558745468756D62
          3A3A496D6167653A3A486569676874003531328F8D5381000000177445587454
          68756D623A3A496D6167653A3A5769647468003531321C7C03DC000000197445
          58745468756D623A3A4D696D657479706500696D6167652F706E673FB2564E00
          000017744558745468756D623A3A4D54696D6500313630343332333637392AB1
          878100000012744558745468756D623A3A53697A65003435393842423A1CC9BC
          00000046744558745468756D623A3A5552490066696C653A2F2F2E2F75706C6F
          6164732F35362F584E724946746D2F323632312F6775695F66696C7465725F69
          636F6E5F3135373134372E706E6755BBDFA00000000049454E44AE426082}
        Stretch = True
      end
      object Edit1: TEdit
        Left = 20
        Top = 0
        Width = 209
        Height = 20
        Align = alLeft
        TabOrder = 0
        OnChange = FilterChange
        ExplicitHeight = 24
      end
    end
    object AdmLogsFiltered: TStringGrid
      Left = 1
      Top = 85
      Width = 769
      Height = 390
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 3
      OnMouseUp = FilteredGridMouseUp
    end
  end
  object PnAdmLocations: TPanel
    Left = 40
    Top = 33
    Width = 771
    Height = 476
    Align = alClient
    TabOrder = 9
    object Label19: TLabel
      Left = 1
      Top = 1
      Width = 769
      Height = 23
      Align = alTop
      Alignment = taCenter
      Caption = #1050#1077#1088#1091#1074#1072#1085#1085#1103' '#1051#1086#1082#1072#1094#1110#1103#1084#1080
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ExplicitWidth = 189
    end
    object Panel6: TPanel
      Left = 1
      Top = 450
      Width = 769
      Height = 25
      Align = alBottom
      BevelOuter = bvNone
      TabOrder = 0
      object AdmLocationsRefresh: TBitBtn
        Left = 0
        Top = 0
        Width = 24
        Height = 24
        Hint = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1110' '#1090#1072#1073#1083#1080#1094#1110
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = AdmLocationsRefreshClick
      end
      object AdmLocationsAdd: TBitBtn
        Left = 26
        Top = 0
        Width = 24
        Height = 24
        Hint = #1044#1086#1076#1072#1090#1080' '#1085#1086#1074#1091' '#1051#1086#1082#1072#1094#1110#1102
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = AdmLocationsAddClick
      end
      object AdmLocationsEdit: TBitBtn
        Left = 52
        Top = 0
        Width = 24
        Height = 24
        Hint = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1074#1083#1072#1089#1090#1080#1074#1086#1089#1090#1110' '#1051#1086#1082#1072#1094#1110#1111
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        OnClick = AdmLocationsEditClick
      end
      object AdmLocationsRemove: TBitBtn
        Left = 78
        Top = 0
        Width = 24
        Height = 24
        Hint = #1042#1080#1076#1072#1083#1080#1090#1080' '#1051#1086#1082#1072#1094#1110#1102
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        OnClick = AdmLocationsRemoveClick
      end
      object AdmLocationsImportCSV: TBitBtn
        Left = 104
        Top = 0
        Width = 24
        Height = 24
        Hint = #1030#1084#1087#1086#1088#1090#1091#1074#1072#1090#1080' '#1087#1077#1088#1077#1083#1110#1082' '#1083#1086#1082#1072#1094#1110#1081' '#1079' CSV'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        OnClick = AdmLocationsImportCSVClick
      end
    end
    object AdmLocationsResult: TStringGrid
      Left = 1
      Top = 44
      Width = 769
      Height = 406
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 1
      Visible = False
    end
    object Panel11: TPanel
      Left = 1
      Top = 24
      Width = 769
      Height = 20
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 2
      object Label9: TLabel
        Left = 229
        Top = 0
        Width = 98
        Height = 20
        Align = alLeft
        Caption = #1060#1110#1083#1100#1090#1088' '#1087#1086' '#1087#1086#1083#1102':'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ExplicitHeight = 16
      end
      object LbFilterField: TLabel
        Left = 327
        Top = 0
        Width = 46
        Height = 20
        Align = alLeft
        Caption = '<none>'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ExplicitHeight = 16
      end
      object Image1: TImage
        Left = 0
        Top = 0
        Width = 20
        Height = 20
        Align = alLeft
        Picture.Data = {
          0954506E67496D61676589504E470D0A1A0A0000000D49484452000000800000
          00800803000000F4E091F90000000467414D410000B18F0BFC61050000018050
          4C5445000000FF9900FF9A00FF9800FF9700FF9B00FF9D00FF9600F57B00F57C
          00F77C00F47C00F67E00F57D00F47B00F87E00FF7700FFAB00FFFF00FF9900FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800
          FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9700FD9300FD9200FD9200FD
          9300FF9800FF9800FF9900FF9800FE9300F67F00F67D00F67D00F67D00F67F00
          FD9200FF9800F47B00F57C00F57C00F57C00F57B00F57C00F57C00F57C00F57C
          00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F57C00F5
          7C00F57C00F77D00F57C00F57C00F57C00F57C00F67D00F47C00F57C00F57C00
          F57C00F57C00F57C00F57C00F57C00F57D00F57D00FC8F00FD9100FC9000FF98
          00FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800FF
          9800FF9800FF9800FF9800FF9800FF9800FF9800FF9800F57C00F57D00FD9100
          FFFFFF413EC9140000007B74524E530000000000000000000000000000000000
          00000811080A4FAECDB1530B0983F5F7905D07ADB710CB4EF45E85F351AFC5CA
          F0FBFAF2C658050C1079F7FCF88711060C98FDA20E16B1B91923C6CD2834D8DD
          3A48E7EA52015FF2F46F02067BF9FA89070C0EFEDE6CFD8AFE8081E65BB23703
          FCD15FE78C1C1D41020145DF2FF300000001624B47447F48BF71E50000000970
          48597300021BEF00021BEF0149171B830000000774494D4507E40B020D1B3B8C
          3DBB43000002D24944415478DAEDD93D6B145114C6F1FBCC18D889B0E00B0445
          5450110B85141629420A4929015F10C10F61A3DF412D05D17E15096229821616
          CA22585858681110C5AC88C6882FCBE20E6B0C24B23377EE3DF7DE73672CCE94
          33C99CDF9E9D7F180854C30704200001FC4700605B3D1CACA85C034877003501
          80DEA6607364BA1BB850CB7CA56EE3E7970DC10600C9CE565DF395EAA4EFF2D1
          3820DD8F73B5CD576A7175252F000EE04C8D807BA3A522A0F10DA8433855DBFC
          CED637AA0058ABA08D85BAE627C3E562057FBF8449AC1F51678F92E1C4873DBD
          E5F2DF01A526301D1FB076FF41AB9B0FFF9D18BFDE9A016622CEEF024FFBE3A2
          C24F64B3381E11F0024FC6E797009398C374B4F92FF138FD6106A84CCDE368A4
          F9AFF070CBF7C2B9F223D7C6091C8932FF351E0DFAC5939A673E3B091C8C307F
          09B85F9AAF7D23CA4E037BD9E7BF07EE96E7EB5FC9B2F36FD963EC62DF1DCDFC
          8A77C2083196033401F863D4046802B0C7A80BD008608E511BA019C01AA33E40
          0B8031C68A006D00B618AB02B402B862AC0AD00EE089B132403B8025C6EA0009
          0086180D015200C1319A02240102633406480304C5680E90080889D11C2015E0
          1FA325402AC03B465B806480678CD600E900AF18ED013A003C622404E802708E
          9112A013C035464A806E00B7184901BA019C62A405E80870889118A02B801C23
          3540670031467280EE00528CF4003D009418E901FA00EC313A04E803588FF158
          AFF2F2AE8F9FE9017A01543B3D6BF895A94F8B7DA72FC0E37F46E9E1B9EDD557
          BFDECAE9B7128000042000010840000210800004200001084000021080000420
          801880D59BCD02BEE1469380CE0270BD39C02FE0D9F374E8783B3EC000B896B8
          7E7C3E80D7F6F9009EDB6703F86E9F09E0BF7D1640C8F6390041DB0F07046E3F
          1410BCFD40C000C9D5B0ED070138B61F00E0D9BE3F20FCD90F015C7C30CFB47D
          4FC0A5DF5CDBF7045CC615B68FEF03E03E04200001340EF80395EC6A90A3E611
          2E0000002574455874646174653A63726561746500323032302D31312D303254
          31333A32373A35392B30303A30307EB49C380000002574455874646174653A6D
          6F6469667900323032302D31312D30325431333A32373A35392B30303A30300F
          E924840000002074455874736F6674776172650068747470733A2F2F696D6167
          656D616769636B2E6F7267BCCF1D9D00000018744558745468756D623A3A446F
          63756D656E743A3A50616765730031A7FFBB2F00000018744558745468756D62
          3A3A496D6167653A3A486569676874003531328F8D5381000000177445587454
          68756D623A3A496D6167653A3A5769647468003531321C7C03DC000000197445
          58745468756D623A3A4D696D657479706500696D6167652F706E673FB2564E00
          000017744558745468756D623A3A4D54696D6500313630343332333637392AB1
          878100000012744558745468756D623A3A53697A65003435393842423A1CC9BC
          00000046744558745468756D623A3A5552490066696C653A2F2F2E2F75706C6F
          6164732F35362F584E724946746D2F323632312F6775695F66696C7465725F69
          636F6E5F3135373134372E706E6755BBDFA00000000049454E44AE426082}
        Stretch = True
      end
      object Filter: TEdit
        Left = 20
        Top = 0
        Width = 209
        Height = 20
        Align = alLeft
        TabOrder = 0
        OnChange = FilterChange
        ExplicitHeight = 24
      end
    end
    object AdmLocationsFiltered: TStringGrid
      Left = 1
      Top = 44
      Width = 769
      Height = 406
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditLoc
      TabOrder = 3
      OnMouseUp = FilteredGridMouseUp
    end
  end
  object SaveCfgDialog: TSaveDialog
    Filter = #1083#1086#1075#1080'|*.log'
    Left = 120
    Top = 544
  end
  object PanelImages: TImageCollection
    Images = <
      item
        Name = 'Add_Ticket_icon'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC400000EC401952B0E1B00000311494441545847ED9651
              4893511480CFFDFF6D3A9BB62D3527C5D497955010FA90640A856F61444F1261
              BD05620F51584A6259410F05D1635444502F412F154119EA5223D4084411CA5A
              CBE9583A657335FFFDFFED3F77779BBAA439FFE18B1F1CEE3D87CB3DE79E7BCE
              FD7FE272B9286C20021F378CCD00360358D60524121C37BB1EE68A92CF061408
              37AF197F59F31B1C2D1377EB98012140657DC1D49CFD7480EA4C0E6E5D120055
              A68B071B4C3A69D6C4F40C11D15B839ECAA741204211EAF12BD0FD768F68E69C
              D2DB4CFE01FA405F5C4D04406824ED942741C3D798ACC2525F99294221CBC924
              0532130016708A459CA100C2D54C52201E8064B4EFF239AE3823866DF3DC943E
              42761B088636AEC5C1BDD107FAE2A6E5EF0042E4F0B7E2A1933BC4885FCF4D9A
              20EB2C92A7E2F14F2A6695721323E90A7041B0E8C80457D3443E109504B8E74A
              E748666A0051D4324C81A400F00A4CD32FCAB89A26621F08623F5718B827EECD
              D538890094C8A471A6DF69FBD4685DF7FDF397709E0A30A464C37B3907C61743
              FAFCE15356F481BEF8CA4411EA17BE76D93E9F39CCACEBA45D2ADC3F20E75C22
              048E2A4B9E0313C8502F06A0AEE26617DD52CA7C695E03838A118615E3002564
              99732408223C91CD7071E4814DA18A176D9A06E05674D02115C21F10E29E2FD7
              B632395E7E8C5B00BC216FF94BD7AB059C6B1AC03DD98ACEB916A5B6A4864979
              C16E6E89D2EDE92DFB117077C75753A24BA96D56030BEE8392C3B5FFE30FCF41
              C760A7A4D90F09567B8B6463734C399E7A35AE765F875E97536D14EA4FE44BFD
              4399DA777F32B0BDDE13B256D190A50AD6228BFA7CBE51EA1020B949DF827499
              0BCF779DEBBFC05A0B0B2E76E7B14CF8167C30EA1B63F367A3CF614C9D53AAB8
              350B4065F67C5F8B38BBE8DFCA75C6DBC6D76CECF9DE0B9D3D37D83C867A058F
              B4EC02EB094743F48829603698E53BD5B7766A99013CD14CEBC7762FF6393741
              8DFD201B7DA15F2CED8825CB0CCD7B9AC64B72ED0E4D0340F085C34706FB1C5B
              6D2578F2B37B9BBEA073D4350F20063E32D8E76A562AB1DA292853AABB7798F6
              3C43DEA1E82A80BF454076501584F46B0000000049454E44AE426082}
          end>
      end
      item
        Name = 'bootloader_users_person_people_6080'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC400000EC401952B0E1B00000713494441545847C5566B
              6C1C67153DF3D879AC9FBB9B64B77682895D2721B6E3D88E29751E8E8350242A
              4CABA8A9A840880A21B58548A994AA08A156A18044D520013FC28F220551A92F
              5189462888D4384D53839AB44EEB25C48DBDBB76BC5EAFF7FDDE9D1777D663C7
              C9C60EB1827AB45733B333DF77CF9C7BBFF30D1308040C7C8E60ADE31D61E85A
              9062D6BABC67B8A302D9F8F52B13EF9F6C484D9DAB93651BDC5BBE96AEF6EC18
              AF6B3EB88161F94DD6636BC6AA04F2E9D8D5774E3CBCD528CE43B41990440675
              F54ED4AFF3C05EEBCA350EBC749D17EBB6588FAF092B96C0308CF9D1D71ECF72
              CA3CD25906E91C83541688C5D288C752C866F276FFDF9F6DA4B2CC5843D68415
              0944AE0D7FA6A626BBDBB66F46F79E41E48A3664884422A5221A4D9649144A46
              55E4DABBFF1F02B190AFDE4CE8D8D48BC1EF3C83C79F7C013A5B474A982AE4CB
              24124422119EFC8235644D5891800AB994CE3368F86217583587ED9D0FE0A91F
              9F80C3B315C9AC8E48248D2811F05D1EAAA7C7630BA3EE1E2B12A8716F4DEA6C
              3DEEF33401A51498521A1EB71BCFFCF4041EFDDE316C6CE9422A963095C850BF
              ACD94B5624D0D8D2D9E26EDE9D62B502504802453352E0F43C1EF8CA6E7CFFA9
              6368F0B84BBD877E36C6308CCB1A76D758751946A7BC97BAEA677BA050FBF312
              C0891402858D48C5F0EADBEFFEB6EFDBBF6CE7386E40D794A979EF1BF142F43F
              9B601445C1EE8AD66CDAE3AF6AE86B27824E6BCA0AAC4A40CDC5879B954BFB91
              9D23ADB885E4E6512BD291C7D0E5E043F77FF58709A5903CFEF11FBFF165351B
              AAE148538E35C0D1632C9DCBF5CD1FB73E76662391586F4D7B13562C81098D15
              F44CB69885504B172AF502295148133305454DC89D3C35FC515353D307FF38D1
              5BCA264235AA062814AA4E86E5F040A521D9D8645762F2CC843565055625204A
              555DAF9C197D391E0B97C0D9C99D181A2120A3B2F8D52BAFBDF8E6B90FC3CF3F
              820D9A86838ACAC00C33E9E61D5F47FFD3E7D1D6FF244C5253EFFDBC9DFA346C
              4D7B13562540700C7EF7B97D05689FCD47A6118A46118E87C1CB0C3ADABF749A
              EEEB369BD8456FCC2A94988840B43BB0F3C0D360A8795B079E83BBA51FF954B8
              3A13F67A17A6BC19DCD1A3475FB0CE2BA0EB7A60F493E9F3754DDDFD35CD7D62
              5CDA869AE63DD01D1DC848ED8DFD070EC9A9C0704FA3137B3A3AFAE07479D0B6
              EB21383D2D349A05C3B060A57A4C8E9E86EC68CED636746D5898F90678EB5886
              E9FFC954FE4A249A5E974C17360667E36402EC8FB2790D5D9D0EF8A655E4A9BE
              1AF503C749833B3BEE1FB4CD1C40BDF62976ED7B0C3AAD0C567294972B0C535C
              06B5B5EB177A217AEDB63BE7520974C3080D9F1FD7DF3EFDE1BE7F5E9AD8EEF3
              CFD71A34892C89B0F13C26266661A3D63637A36C8E5601A15452918E4CE2FA74
              8872716075CA64FAC532DF50127E6A4CDAC802C37586AE577C4F2C11088753C1
              5038E6B6D96C9004111225B6CB664890E9289941FF89A20051B041A0E792A1AB
              9899B88AE05C0C4A9148994DA098C695A08803F171447C17A93941AE1941211B
              ADE8832502996CE93E4DD721D0E412259145B1FCF666F272D0B92409E57BF3FE
              518CFCF9259C7FE31728E65328A90666676953646522A1933479204DAAE4E308
              85E7902F9A5B3903DDBC770B1609C4E6E6D30E8E4C46B4D11B5292723293C062
              582444FABF991A4ECD05698B0850E968DDD3F27BF3F53F5012D3A0C8AC48098D
              7AC53F1BC3F0B911CCC53870B23B29D7AEDF6EE55B429940A9A48C168B9AC4DB
              78D8049E54E0979120352C128B0A9825D87BE859B4F67E934C872B4B1C0A4771
              F1D239EA9179A4F20A3E1D1FC7F0850B28141452534DB63DFCF2472CCB3694B3
              2E439980A26A0C2D39F01C11A08633EB5B26619563B91AA22080A586238B8573
              F35E70920B0A91481779ACF334A276830B428D80CEBE01B477761A17268D8BBF
              FE6BE1D1CDDBBAC9C52AB1404051598681C19391F33C6785A98449C406B33139
              3276956AAD283AF903F557220EAF2F8C696937BC5A2FE66A07E0F527E9253822
              2D83C947F02F6F88111B1FDCD5D6FDE05F8E1C39A28F8D8D0DD18BD2C67203E5
              CDC8B4C98949FFF8850F46D3B3A1685A5E947A4972D32E96FA1581C0C496B7DE
              7A75A72CCBB0DBEDD41F7239DAD6E7F19B638FD0ACF4B2F4FBD64F5EC7653FED
              1FCB505555953B75EAD4747575F556F3FAD6DD30A669DA27D6F96D9148249EEF
              E9E9F9BD2008DB16132F927089790CFDEE09DA28796A4203EE832FD2B7242DCD
              5B70F8F0E1C0F1E3C7C9E42A09DC113333337FEBEBEB3B48DB6BF9DA2C952499
              5E2193461AAEFDE90954D539F1FEE500F6FEE0248951597A87C381B367CF7A5D
              2E57DB0D5DFF47F87C3EB31E4BA455F2D94C26439F665144E3294CCD44CB5EF0
              CE7BFFBE6D7213F1781C434343E4566B50C06CA2919191B16030489F4895D8D1
              DA60ABAEB2B35726834A3C95AB741E82D3E92CEDDFBFBF95BEA436DE35817B8D
              BB2EC1BDC6E74C00F82FF5142B868B56A0FD0000000049454E44AE426082}
          end>
      end
      item
        Name = 'checklist_icon_129185'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000E6A00000E6A0186B9EFE200000479494441545847BD575D
              531B55187E76B3F98290400229055240680B6AF91A0B54AA40AB173AFA031CAF
              9C7AE585B73A5E39DEE89D335E78E378A3CE74B433B5D8113F90426770A60DFD
              1AA653B1562CA4B42498C06E086992CDAEEF3949B1216C9242E933796677CF9E
              8FE7BCEFFB9C24C2FCFCBC8E6D408FCC4FAA3F7FD4C06EA5573E5C14AA7C4399
              378F865205ACE889D815A8F7E956A02535A8E73F73405EFC8237B8EA4F4883EF
              C62088F448D3493608D6F21E7AA82216444902F468F09C7AF68376BAADCCB470
              98889F646EF13E319DB9E558915EFF7856A8F01ECB3E1B225F809EFAC7BA7E7D
              19BA9ADD0E90BAFAA339B110E8629BDF84078B3231FF8346599B1AFDE6CE57D9
              031B254090B444D9212F5D9B789F2CF2045863D72E3AC327FB44671BC4721FE9
              4862796A02F1A510F5CE57B025741DF65A2F6A8E0ED37A1668B10034651672F5
              5BBF27CBDA06B2BD38F205AC5D9E7646BE3D6C6E390169EFCB48C715847FFB1C
              292544EB972640270166A7179E97DE81C9EE847A6F0CA95B5F42F6BCE14F3ABA
              7BB3DD388A0AE0F1D4D4CC4B069A9C3E45C03A50D44D661EB50D016E1250912B
              80E5794BB0DD86E51846272FE2878969CE91737ECCDCBA431937232D9872A809
              120F7786567E2D25658602441ABC1C5EC1ECDC022A1C65705694231A0C223436
              8AC44A04F2DA3AE4686C834A6C1D9AA66547970E43010C3A85B1CE66C28BD576
              0C36B8D1230760717B60ADAC84DBE980DB55B1C14A12288A05A7DB1245469004
              9B1DF76FCC207EE50242BEFD58709093440A3BED7633D5743A8FC5CAA5A00096
              86BF9622381D95703A66857F498140A76032A5E684BF1013A97441F7180AD0A8
              D46B6B3C18EAED80AFA5190D4DFBD07BA80D7D5D4FC3629672C25F8836B389DB
              D2088602D82097C386A3CF7560A8AF2BC3FE2EB436D6F3F76C57A5B0180C0588
              A2805044C1C9B3E3F8E6CCAF9C5F9D19837FFA1A9D8EEA96F9DE0E0C05907E44
              5615DC0D2EA3CEEB415D6D0DECC1009253E348284A9E0DA3B1F8EED8B0DE6EC6
              8010C50B50F05452C16AE341D8DCEE276743D155C9856814E2B5EEE7B14ADFF5
              ACA4D434B35D2E536A3A8F5A111F161460A21DCD2D0631124E63441670F9E66D
              98A8B0526443658D4EBF229489C99DD8B09EF2FEDAF0111C6CD98703CD3E1C3F
              D283C1DECE926DE821DA2C3BB061B9CD8C670F34A3ABBD95B39358B7A79ABFDF
              6C37231683A180876DF8F5031B7EFF0BFC337F70714FC4866166C3D0BFA8A75D
              B374ACC713B83917E0C5F5B00577CD860CBEBD5E1CA3DC0FF777E399FD4D3CAC
              5BD5C0EED8D0A0765881B22FA4CD4C2453794CEFC8862611B7EF2CE1BBD1099C
              FA691297AEFF496D26A89482583C8EB5F5E2647D0B15A3E16F424BEBDB48560D
              2170F71ED274C870D03C6E97137BAAAB8C829307B6F4B67E13B24AB75B25EEFF
              F6D6C60C5B1AF9E20C6CE252580C0553C076F93858088629D06A8E437775D30C
              8F6EAD1CD0FF4541BE0A71793C938262FF0B2CF2A569D7EAA9C36CA05EC24956
              0A047614D34656ABDEBC907276F4679B39F20460E5EFF3D6994F07288152B6E5
              F140472AD1FDDE149CBEE16C0B01F80F9E25D669F37025330000000049454E44
              AE426082}
          end>
      end
      item
        Name = 'confirm_shipping_ecommerce_logistic_box_package_icon_142005'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300009D7A00009D7A01EED895200000045E494441545847ED56CD
              6F1B4514FFCDEEFA6B6392344D9D84A4094D2E8048A1086EA8404E1038C039E2
              DC0BE2D24AE51FE043207AA8B8C00501570E80804820C4A5121C8054AA68D592
              9238554B89436DC75EDBFB3133BCD91D7F75ED0A47517B809FFCFCDE7CBDF9ED
              CC9B37C3F2F9BCC43D84A1F53DC3FF04FAC54091F1BF7F31FC8D6126B92219F6
              517F8C993012636498AA4A83837BB7A803876C79938CFA489998DB9556EE71AA
              3810D577A32701C3CFFF6097CE1C256707F5DC21947366A4901C3946BE33AA86
              84418A3ADCD21ACD5FA73E2CEC1B41AA31656FFCE49A4C1E7946577621BE0552
              DC4C573ECD914593EF0B4612C54FA6C9EF755DEE428C001395DF0C5E38AC8BFB
              02C60BD310E54BBAD8851E41C8D5BA26227BDF40FB14DBE910039E824E274D9B
              B4329B32207A1060309816A3C36E96B5302AB724ACA3915DFDC9B9D2BA8E7E3D
              118F015A2CDB366167B4D81689D2268632649364D209D24912ADC3B215B5EBBE
              E1B8960F33F4ABA7E8429C004927F3D69790A8AF0D3555C65640B5B5C6C4CB91
              E738068C018DBE7B3D7810EC81004DD2673F150C6A3721482B91B0B4EE873D10
              A0D929E50A6F07817385F47658D62DB8184CE12D6719AF565FC16BD5157C507F
              1AD7C528B5F426114BC5A6287E37E1BEF1149999E8E8B69BC332DD01CCCCD29C
              554A6E3E952D1856164150C3C7CE1378DB7F097973961CA9542261F0061E0D2E
              07670FD9E76653E9583A1E7C05D485139442CD180D57DA2FE24BE741BCDE5841
              3EBD00964C2061515F93412433584B1DB556B6C7265C213723276DEC2D083B82
              40596591C687CE7194D52DC903BC901558CE72986427454093086C199987BEAD
              B01BD1A836FE05818E88EB309B50CED7BD8338EFCFD0E41E4D1EE0FDC30C6FDE
              CFF0F902C93CC373366D15E778AF005B4A4941D3465F02920B54AEDD40697D03
              A5AB9BA194B578BB152213B151AA225270028651D1C0C909037329868733065E
              1C35F13CC99C19005E031BF560A42670211CA871E7155073B4924853BAA1EEFF
              31C3C1B05F46A95AC3BB578BD8AC07B858F5F0D5760DAB851AF2953AE0D6B0C0
              DC1DDBC0A21E1AA2FF2990C870DFA748175183CA68891E97241D8D1A37B1927F
              19DFF8C7C24F5A9E18824559F0EBBF1C158708680641BE3E9A4F9E5B1A4BA913
              D642DF15101440C5DF37B073E15228C5CBEB74E6692F6F83623F64FA3831F223
              263D8AB18063F56605AB7F5668DB393C2A0BD7C33C1A6BC7479373D1A8366204
              A44AEC80CFE87AB373E3C84E4F213B33057B3247E7BF375F95EB9686B77066FC
              0B2CF22B301A35F88A2C7D75AAB18B2576DEFDEC9174995625F6D089BF09E949
              9673DF2958726751867BDE6E96A2BBAB0245B5B628CEDC007F38367E726650E0
              43444BE28164114FDEE7AEA7264F67E80BA675D7167A3E4A1362EBFB43EED9C7
              C877EC517A3B3A092833A025E73E2D7B932C43D93970EA57913CF26C54D18D9E
              04084553DCFA3921AE65195C95D322F422A0751BCDD717BD8861F1C09CAD0A73
              5C3DCB294BC5D18FC05DC39DF3C05DC07F9D00F00F6951DA21105DBCE6000000
              0049454E44AE426082}
          end>
      end
      item
        Name = 'google_admin_icon_131692'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC400000EC401952B0E1B000005AA49444154584795576B
              6C9355183EBDEE5AB6B28DB1ADBBB4DD1016611812088889B8FDD0C882C6444D
              5002A864A272898444839808EA0F8410994A40014330C4444920261A86F0C360
              0445401094EED2B14DD6DD61ACDDBAB63ECFE9D7F2B55FD7AD4FF2AEEF39DF7B
              79CE7BCEF9BE773AB7DB1D122920180A9D5B56BF7A15543324E2AB83F8CF9E3A
              F2B55EA77B3C3C3535E895DF29C3D5EC0EE2A74991338AC871734B7B4A8B2152
              2670E3DF162B7E66412AE2A4EAFA3F2E3E4B0929110885423DDF9D3A1D50861A
              7C7FF2347628D4A30CA7849408787DA357DCB7BB0A94A106EE8EFFF247BCBEAB
              CA704AD0100804029DFD03434D5849AF321545B7A797876D42024081A7A74F51
              1F8055E9EB1F6C42EC2E652A8A985B0043CFAB1BB65F75B5B62FB497DBAE6E58
              B73258E52C1FD301172F5DCBFEE2D0717B774FDF0CC53C210A0BF23C0D6B5E68
              5DB860EE70301814B79ADDA67D078F195BDD9D0F57DACB7EFBF2D30F6A102E1A
              2386C0F59BAEB3EBB7EC580AD5149E91D7AC03320A71425881A9807E2E483AC4
              0689F8F9F7EF79FF9739B31CCB94F1832D181F0F747EB8E7C04CA891E4041D4B
              21958A1EBDF889A07A46DB2A087DD5A44D3B3FD95F885C5C944494C0F90B7FBA
              3BBBBAE728430D189CC645868030C89958449E1975A1A4243BBABAAB7FBD78B9
              5D198609F87CA32D8D07BF6189138201D311F8B9CCFBE27988017A3CB8CC1519
              E1E7199390D877E058257236539704EE787A5B71B872A827028D9ECE1811F590
              2C1D5F848941924FA67BC5B320614A4201B972BBEE78DCD42581F2D2E2F98F2E
              7AA411EA20C76A305DB5694CD4213057C9B013850EC182364FA4F9448D794CFA
              26C0D09285F33FC32D9BC78124806B91F7D17B9B5E39B46FC71F3367E4470F08
              C1FD5E92362A2C4A59A503A02611D10DD0A8B312F431C75809C1D8871B77FEFE
              F1F6CDAB91339F73917884D5692FABDDB373EB4DE8FD9CA0BB451F1476A35FEA
              149B715C3C83AD988E79AE906285BE0265AF348D4B1BCE39E0936708AA29F433
              B6A3A2B4167AF49BA1262061B5E6B08AC3D42501EC7964F5942CE8CB4160A365
              483C86522F85505F81B96CD8AAED72418CBA826125760C340426432481039558
              937D4FACCD1E164EE891F954A121D03F20CFA1857F48F75E480F091F2E355866
              A39490E6B0D1F63E7C06837AB59F45891D03358101574BFBCF6F6FDB351BBADC
              23490041DAC64D1A02C9C0A0CDF0E90B18D47E56C6660EE803E129E4E0B700E8
              7B77C7DEA3E72F5C5E83B998F701573717D7F00DCB5DB9AF9395990947B1FACF
              87A7894B63E6447BCC6B7818B7EE25DE04F91CDFF8CB48DE0055F332A2C1DF7E
              B368F2654832C92AC167B439EB4B17D7C64C89921339C8B5BED5DD21FB066953
              5458E0C067345A967830E80FDE4C7112C2BD9D88840FCF7EF2668813DE2CE14F
              4215B9FA4B8A0AD9C68509A4A599ED6FAD5BD94A3D11188AC14F8C64896F47B2
              C578783A06B4F91155E2736F1292C4C686975DC8E9A01EAD12F6A5BCB464E635
              65A80103B219ECC2C10A20413C78367AF1CC8FDF64C96DC585D7172D9827574F
              4409180C86927736BFC6368C312260DCDB10361732ED04FB2AA14A4CBF5B10FA
              AACFAD7FDB96068FD168609322C1AB1C45F543CE6AB44DE7D89239CA6D5736BD
              BE2AE4A8B0F9F57ABDEEC2A5BF7A1BBF3AEE108377266BC9BADF5CFB621B5B32
              F480A2A5ADA365EFFEA3061CBA796CC96657D96B145309CD7F466C4A87EE0EDF
              B0E64E9B1FF96044D0ECEE38B36BD3D6C59B2D4399665CC9781CB96FF1AEDABD
              FBBCB3DCC6F77D146C4AD1E85EC9CDB154A3D2C5CAB484A6A2DC8AE9D69CBAF8
              E404BE6621BCF97AB4A9C375C6D7AF0715084FA880580579D373EBE29313C9B6
              5483CCF4B49AB2B292DE8908D84A8B7BB332D2E78667A68694087025B5F54F25
              6A092581C5F5CB0DB0497A46E2911201A2CC691F84134F789B5A70035C454EA7
              EC235241CA04F22BEC684A451D540A0F1BA52E18D2D5669755247B05248010FF
              03A4822D199966AD220000000049454E44AE426082}
          end>
      end
      item
        Name = 'homeflat_106039'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              0009704859730001D8700001D87001A1D82CC2000002B0494441545847ED97CF
              6BD36018C7F3BB495C6DAD966EB38E21EE32ED50F4A05341C4EDE0B52AFE380D
              0441C493827F827F82E22E5E67275EBC6C52F0E4065B8596B64C44D6AD45745E
              BAAE599AA48DEFD326A55BDA266F5AD841BFF090F757DEEF2779DEF70D2173B9
              9C4E1CA028E37A60EA09E06BB620253205C9A8BA926B8044B6507EB79014628B
              49613593770DE10A2091CD4BB185A4A8EB3A0931BF98720D810DD0304F0960EC
              E11819A217082C80043230CD459E531EDF9DD421A0EC16C2B20D6545533F7ECE
              56094227CE8F87C9D1E3010FB4D7CD918169FEE8CEC5AA6F8067A0AFB8236BAF
              E796684956389224F5E8546417DD2B429F9D2C6F40AEA8FA4A7A935F49E7F9B5
              F5AD12B4B535F7F2CCECFCB28A428332B4B97913B629E8681E5B56F3BF8A220A
              01955D437405584A6E28DDCC8D61442F105D01503A86EDCC4DB985B04D811373
              534D08B4389D425800BEAD6FA11DD090C8B38ECD4DD52160613A84D80300033E
              C4D33C941BE6976A38E6A670209A00D001031A396F9AD3B8E6A69C42D401DA99
              FB7B3037E50482BE3A7DFBD9FB4FA9FA87A5D5FC4D8FE6A6B6CB15F6FBC61F65
              F2EC2873666CB09A5CFBA9AB5A95C9FEF8CDA0375C26DFC6E245B4DD348A2229
              383EFD5E817E35F7A5D20FF3568543BE5DF4705CB1246BAB99CDDD5A4DAFF11E
              96B17C0B8A3BB2F27236CE19D5BEEAC5C3EB0A4AC79EB96DCF81760A1E39A446
              A726A4E733D72A10B7A627A460604035BAB1840D706AE498FCE4FE65E2C2E9B0
              18F0891E0848DDD307572894636C082C008EA5D57B37CF511CCBB04653530C4D
              D1D11B114214382C082C80C8D89082764AC7F58116153B7E325431AA8E840530
              32E4B73CF97E9D18F4632D602C009AA648A3D8510C4DDA8E6915F622ECB7FE03
              58003894C4E1E0E152E8A8777B7FA053CCF647D6E715F476F7C29C30B731ACA9
              7FFDEF9820FE02941C1F26C93B58120000000049454E44AE426082}
          end>
      end
      item
        Name = 'list_1153'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC400000EC401952B0E1B00000344494441545847C557CF
              4B1B4118FDB2BB490DA8079380452DC941FA27B4155ADB8397A67A100BA24741
              F02278F4E0C18BE8C18388397AF466A8D0D80409B605C19283784A72AA712D6D
              154434689266773BDF383B3B1B3690D0B579F0986FDFCEEEBCD9F9E6C77A0A85
              82012D84C4CA96817F015DD77FFCFAFDF30F415FB95C96755D03599641225408
              6559A1D7364AE8DF83CF8246EA6B1A639510AFAB5552927B5A153C1E091EF97C
              9AD7EB53BBBB1F7B2549EAB11950CF4E4F22E148B8AB2B402A7B50721D8661C0
              E5E5259C14BE9FF4F6F48551E30672F9ACF6FCD90B192B3D24B07399CC37ADBF
              FFA98CD73C078A37370FDE3802DBB8216DB14BCB40A952A663F93F582A9558AB
              8201BC21627575152291085C5C5C30C53D886DF11CF8F2751FA26F87A988C04A
              939393B0BEBE0EC16090A9004343432C6A0C7B7B7B2CB2B0FB2901AF5E0ED298
              1BD8FF9C8677D1112A9A181F1F878D8D0D0804024C01F0FBFD2C6A0C7777772C
              B290D8FD08AF07DFD0581802832688C9E5E565383A3A82A9A9299B7E7B7BDB14
              C5674D8A4360CB01B1D2C2C20290AF03C964D2A6BBC1BA064490D590F7C26D38
              1B204B68AD539C0155B29CD6EAFFCA3A5FE0FE86C9959515585A5AA28928EA6E
              D184C24AD00DFB10CCCFCF43369B85C5C545A6DC231A8DB2A8312412091659C0
              CE9AE0D37067E7038C8DBDA722E2F8F818D6D6D6283B3A3A980AD0DEDECEA2C6
              502C165964613BBE0D23C3F753BEEE2C989D9DA5B30017235127EB7853149F35
              895BBD89BA0632990C1C1E1E423A9DB6E96E50CC01CB00C901B112BABFBEBEA6
              147537A86B560E70039A6637F090741C023C4A899536373761666606E6E6E66C
              BA1B749C8606CB0113131313100E8721954AD9F4D1D151163586783CCE220BD8
              5913D63A5063E0FCFC9C6EC3AAAADA744CCA66707575C5220BCE49282C0E08DC
              846ACF02087C61337482A3013C3A634F4D4E4F4FC3D6D616C462319BEE06C5CE
              72036451B45522FF07B40778A0107537281EFBB90172D221FF10CE1B87DB6CF3
              B7F12CE40642A1909ACBE51C1DBBC97C3E0FA1604865CD5A9B11D9F7CF0E0E0E
              AA64057C423EBF84957D3E1FA7D7EBA5A5A228BC4422B0573864222B950A2F91
              F83EF20EBDB3B3F3746060803CAAF4E2B3DC40AB2024612B00F0176B9CB18716
              65EDE70000000049454E44AE426082}
          end>
      end
      item
        Name = 'LOG_29710'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC400000EC401952B0E1B0000040A494441545847C5976D
              6C535518C7FFE7F6DEB6B77BE964E858F78A9B323A11D88B12A3928560108999
              1A7410A3E18B2C04A7EC4B8D2F19C69744D42F04D1380C810FE81081489438DD
              46C207A761A341D35581B575CE0D36601B94765DDBEB39A7A75BB114E6B66EBF
              E6E49EE73937A7FFF39CF39C732EF1783C1A6E426874ACF5FB8A578735A23D41
              08D10BF7FF622C1C0C5734D69DCC5F51BA52B8E290C4330ED781360B6D7D6AAA
              7FCEA023938ED67DFCE80547B743B8E24828E0EAF9FE3C519D16DE8121D2F4E2
              BBD6BF3B9C3715915080A6694454A78D777008876B77585D27ED4EE11A27A180
              9986893856BFB3A463FF713B352F47BC491620131DFD8389403211CD0D8DCBBE
              585BDF4123CC45245580440872D58C1809112E76B957EF79EC154728186A4BFA
              14A42B4614A5CC875951A1CACA78F1BA2F3CBC7BF1F386595903469D825CA319
              79EA1DB84B4D1F2F996AEA43B3B608E97E023D5D132950A08B999459131085AD
              0B95C8300A19B32E8041E84F11D198130151D8B4CCA900C69C0B206E97ABADEF
              CCB9F0154F7F8AF0713A3F3CB8DC373034E593F04608526503D268F92F643329
              FB94CE45ADB0934A9691E6BE62E29910455749B20FD1D5200B9B53BE7E3546FA
              0731E61B159E080515562CABAE82C57A3786FB0611F0FA440BED7C5101CA9E59
              85C24A2BFC23D7E1BD342C5A26086961E81585D759124616212146EE89E185BD
              0D2859F5A0B022ACDB5E8B6D2D9F21BFBC04951BD7E06DE761143E50CADBAA5E
              AE81AD7D3F2CF71523BF6C31DEB47F89FB9F8CBF0469EC8A420920042FC610A4
              826E187914A68CC6495880D972271E7F7D131A9FB5C17EF404F7BDF4F50E54BF
              B7159F3F67C3D31FD461DFA6ED38D5D4CCDB7A7F3B0773F67C5E4F0493E24370
              725990B3A418924E87AE1F7F111EC0F1C3CFC8597A0F72E8A865831ECE965F41
              2409951BD6C0377C8D8A382BDEBC359312E01FF1F2A7695E3A7F32587DF49A0F
              3ED1A666A441A79791BBF45E2EA266A78DFB6F4742019905D9BC33562E9EFD0B
              973C7DA87E7F2B54732A2CA54558B9653D4E7FD382DE337FA2CFD18D750D9BF9
              D47DFBD66EF49C768ECFF7ED20B55279DC9BF5271A312F2F4B5840DBAE267435
              B763C327AF61E18A2508F8FC38F555330E6EFB08417F00998516D4ECB2A1F891
              E5FC80E9B1FF81EFDED903E74F1353C630E8642C3099851581EE03E5012A3C92
              1B4986DD0BB24C13D3C89068A80E897AD231C9F11B2B717577B79E6FED542EBB
              7B33A829DCC0EF7B8F2FBA3A70654622C38E5F36FA54C51049F118127E9A75BE
              B1EFBAE758BBC94F737572CB696ADC320D6522F14B4332AF0D097BA6A1E20367
              2133D2A3C24437CDD83BFE4C40BF0DB48402D28A16F4882A4747A3C14418E831
              327368EE8402166EACFA07611CA12203C2C5A311BDD9CAD38C06EDB71FD0B6FC
              0BC04D2E2D565C706A0000000049454E44AE426082}
          end>
      end
      item
        Name = 'notepad'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC400000EC401952B0E1B000003D1494441545847BD97CF
              4F134114C7DFB6D0D05F5B85FED0165A8B2978104D000F44128D51133C198D9E
              3DAAFF82FF813F2E46E3C1C4830713134E2646A391688C70D090484440C28FA2
              EC96D21FF4774BBBBBCE1B776BEDB6B696C54FB2D979DFE9CC7B3BF3663AC304
              8341096A501284899793533E8901666C6464B54DAF3F85FAF78D8D99CFDF167B
              4F0C0E7EB29A4D27514B65B26FDF4D4F0F1F090456BCFB5C03A8D56B5F8D4E7E
              ABC8E50B3A609883A47D6FAE40CA32D1446280E896582A699725A065D49289C3
              B254B77D35352B24490AADF0FC926CC20AC7AF16B68B13F844B6120C6A3F42E1
              A2A2611935AC5334D27E153584B45FC23E65F30F54532088E2E21A1776C7D329
              33170953CDDDE500D66CA1E5F9B515FAB61A4DE071B868799DFC2E95CDD0F221
              AF9FBE93C4AE6CBF976533DEFD4E4EAFD305A828A31A81D856CA4A8230CBA666
              088268C6BE65B38C2A00923CF4B3C4920089789C3EA220D03A249D4850AD90CF
              CB0A402197A35A8AD429D46AAFF45D892A0086640DBE6D562B383BEDF4B15959
              5A871CF0F4C01E0B0B6E79F8112CA3E627750AB5DA2B7D57A2CA81502406E9EC
              EFAFD30A9284B05DDA26C176BD672D162FC9051FEAFF250074CE4537CB896A68
              6B13468F1E5932198D7D75D7A796B0362B64F2395A164511789ED77F9E9BDF8F
              F6EE062009E0F9FE0CFC2E1B8C0E0D51291E8D82502AC166346A2223B3B87B01
              A0F32F0F809D7F0AA5F16B6037B581D7E9C21541A73CE03FB0C8304CA0610E28
              1BCFBFC048220CF3E3D09D9AA1362EC9588E85C8B95B10CD8BD23ACF7D3D7FF6
              B49304E06818403293964BCDC18008BEB987E08A4F531B9D27833C08856D283A
              FA2073F9FE6C8F3FE020CE9DF4F79AAE0232EC6E32ECB6D014352B9D2325FF08
              ECBDFE6483D1E9CA9B887639D0C0397E7DF1E21DA8748E689203B5E6BCDAF9D6
              85BB60EE74C13E7B27D514769C037F9B7344712E75D8C062EA5005D0700AF06F
              B8EE633242FFF2E3A69CD7A3F51C6862CE1B39475ACA01B284E05876123C6BCF
              A95DED3C6DF3C1CCE80D28192CE5030A526B0A5ACA015F4F37F47499C90E7715
              046E56F5E5DCB99B506CFF75A6C1A952D02C070CED06607068CFDF273B9C5535
              ECC63DAEF26F1BD1520EDC7BF414169682B0CCC7C9F67A9B3A6E76CEAB692907
              5EBDF908213E0CD7AF5C826EB70B98FCAFA35823E79AE5C0463806D94C0E8CA4
              C3BE5E7AB0698A9602D092969270B751058047A6DDA256DFAA00B285C2EF4B80
              C6D4EA5B9503CBEBDCC28FF066BFB9C348773C2DC053311E4ABB9D8E855E8FBB
              5F9629AA00C8B56CE2C587A93CB9569F21EEDB6579471007454682D763C7473A
              C87DA0E29A0EF01330809F9FE12C8C140000000049454E44AE426082}
          end>
      end
      item
        Name = 'signposts3x_99162'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC400000EC401952B0E1B000004D2494441545847C5974B
              6F1B5514C7FF77628FED38769C9793A649D3A4AD49F370A04A287D088A54B140
              5DB0E20BF06158B085051B245620608D10AAA2366C4040C8830482933A8FA6B1
              9BC6CECB8FF1632EE74CC6895DCF383612EA4F3A9A3B2737F79C7BCF63AEC5C6
              C68644E3E4490489C378030A24C7245E12272BEA45319FE751243922D18DB713
              2325E30C8F0324AC2F0821E2F4D448CEE53C075224699226121F493D0E3BA494
              DDF47491F0FF1FB2D28E5A0B1ED34E3CF46C3E79ADA6A0E50DA98197D668A127
              87C7123B07F8F85A6827B60E1E3CDFC7A38F3F31E4F085FD26CD35D809CB9058
              25214FE4E33B434AFCFDCB3C8472B6DBF5C5656476778C7173F00206C6468C71
              09291D180A8F40F5542C55B5F6CB0EF051B1B715C4A33B686D7D889E018E487D
              E8BAC4EFD30548258CD0E4E849CD9C5061A3FC880F295E96F1D6751DAAAB56BA
              54A3280253F79D0885E7F1E8AB2F914D650DBD69E33466E5AB36D58AF97FA5B5
              DD89FE900B478903E3DDB4C155655032C88D849B880D82D3A06176A2197CF799
              86BEEB1FA0AB9F2BF314B695E3412907F848FCACB02297C9E1FBCF3F45E7C553
              C7CF45D7FDB83CFE2E2E8D5C3635552449DA4A0E70A7B35D7D7D7E0DCFD6B64F
              E3C8C437635093EBC638DF318860DFD90E7DED7EDC7C701BBA2C354E4B0C9BEC
              001FBFA5F15C46C3E3AFBFC5C4DD1C025DAAA93D9FE8D23182573E445B4FBBA9
              B1456707F828B88F9F416712995D86CCCD6192329933BA1112310DF19D7BB870
              F5A2A9B145E3242CFFA818FCF5F3227A7A7FC59BEFA90D1B6F14CBB21B7E6B0C
              DB5B37F0DB741E921ACAFF88149B9B9B49AACDCA109868690D33DF349E03DB6B
              0E04871EC01BA86AAA2F936507B6C9815E5361C97E2C018D4AB19C85993F5088
              CC1A63F5B5498CDD9D30C68CAFC38F66BFED47B49C0C3BB0480E8C998ABAE1AF
              61F6872F6824E079FF23F83B6DDB482D520A191F345F5E051E4E426E8BDC0B5E
              054AA913EE9274192A2B6846FA3085E3E41152F4D472792CFC348F773AB6E98F
              028F937D08DF19874B75C2EBF7A2A5CD473940FBAA5DC16C57941CE00CAB48F3
              42BE80A72B9BD83B48612D9E84EC6C83A72F087767000A198ACFCCE27E6C8666
              0A4CF7DD43D7ED0914C9B16C3C81FD8508D44C16D706BAD119F0A16FF8121CCE
              AA7663507280E10BA4377394C1F2EC0AB60A740718BB0AB5D5BA94AC1C90746F
              C8C4F6A8C14A787A3BE906A52047A7A62D46D0EF54303A791D1E9F71A9E1901B
              1E9537A2E2DAE293F4F4D23A1253E368B9F3BAAD712B4AC665A1087777BB619C
              51291CBEB76F2079338C8773AB78B214E58D96365DE1807F606C30E69B081545
              83ED97BB251BD72904EE603B148BE366870253A305FA3C3FA7D7D31F2F15ADD8
              21C4D0945B89A8549BA6AA2E728943E8743D7777B5A1C96DDD3179CD4955AC92
              8D8AB2AF7080F108313CE55256E8EA5A7769F2F1F3513BBCD697565E8BD7F428
              62D8549D52E500C3136FB9C4A61B928FCB125747002B5B1A4916CD74DD72DAE4
              8B47C838AF65659C29AF822A28107BF1A28C46F232AC89CA32659273FF701120
              10BEC6B75D537B824B221752C57C50C115FA9BEDCDA4A60325287CBB7B3A5613
              1283B1BCDECDBF3EBD64AFA7E9C4E8B3A2448A56E138F73844BC5D11D10E4590
              61048D0935A8CB817228E19FA6A5FCD32D708B12AA9575792993691D3FFA14F1
              061550C8985817C0BF289AE27C2B2BD1BF0000000049454E44AE426082}
          end>
      end
      item
        Name = 
          '3592821-garbage-can-general-office-recycle-bin-rubbish-bin-trash' +
          '-bin-trash'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300021BEF00021BEF0149171B8300000255494441545847C5973F
              4F1B3118C6CF3E2A5458C3D00E5DA8042C74CF3760A385202E7C8AB04146FEA4
              4BE93768274ADB0CA54BD5A51DF90A24129512A9CA10324742CAD9DC739C2FF7
              C7F6D9E8809F744ACE8EDFE7895FFB3D1FE9F7FBDC794268F4F964280DB04E97
              CF1E1C32E7CF5F1E10B59A138E09C622867FD9550690A6C03DFFC95E341A8432
              9FE0FEDADBE1E3D6110908FB8B80F8FC7E9357BE9C860338A5CEE0E423F3DFAE
              E7FE70AE212B0E16CE4EC9DC5ED36826B2E28030E6BCDC6D50F7C7398B9A6252
              0664E2021313327181CA449C02E4FCD5DA9A23134FA24A874E3C09D2D1FBF59B
              BB2B4BE1EFE21978DE6EF32271209B0953718099980BB4A2DBA9819B6AB570B0
              2069C2465C3079BD187D4BA400811014C1C31E0346B5AD209FC4A9B4BFE516B3
              8A6BAF1EA4F0384E616A1BDEC7840D597190728E0E2C302CB4A8A93464E22037
              750F6142250EA4B92BD3844E1C28174F19268AC48176F50A1377ABDD8ED1668D
              158903AD8129FA20520A84055A037191B1D8E7824AFB3BCD564C19CAC0B1B845
              85CB62F200931A28435C50642267A04C7181CE44CAC043880B54266203F7111F
              6D6E319B2D2A35818751787DFACC826674195D43AFCE7ABD1EC735F476ACC6FE
              6FBDF7856E3C03B31717419F19C90A278A954DC59CB9FA177D4BA4605CAB111C
              978A9095571B139CBAA156743B35E02E2F111C9D752674B5DDC404C4071F4E98
              380F82941ACEED2A13260F169D0921EEBF4BBF1BE49464264CC40532132A71A0
              7C39C5EB144EAF38404EBC6D6A229E045B6DE6EC2B7BD6E9F0F1C606A56F56A5
              0194061E8B7CB21F15C7B905445000DCD60801E90000000049454E44AE426082}
          end>
      end
      item
        Name = '3592815-compose-create-edit-edit-file-office-pencil'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300021BEF00021BEF0149171B8300000221494441545847E5974B
              4B1B511480CFBDC9C4C9D8D45254C417B6C14D373685A220AE74DBFFE0DA5FE0
              4604BBEB46BA11DC966EBAEC3255698B8BD255104B5BC5570C521F44C14493C9
              3873F4D83B53476734D1B9E3A2DF26B9E70EF93E2EC33061D96C16E11EE1E2F3
              DE901A8016829E5940FDF7B2EF294B0B20B931330BF5F35F99369366FAE20FB1
              E3464A0022423EB350D1967E9DAFD9D95AFBF219BC22020F20F9CAD62EE41E35
              2A3B4F924762EC1B1168802D2FEA062DD9E6B31ECD33626D434C020C40CB02B6
              3859D68FF74B62447846C0F6B67353061240722D338A9D5B6FD581DC88A19805
              DF08BDA9D98ABE489D6F10777E10D9F2A6DD0F4C8CA0107B7A38DF31A5189144
              5C8C086CCF6DE88FFB5ED645D43AE7DA3B9D80979C4854D61E5E3E8958844343
              7F9F7A514EDC3AC04F6E7331E24C8EDD6DCD2CA644C5EE3F6E157093DC862252
              07D3A69F9CA839A05A395178F0DCD253AFEBFDE4444D01B5CAF3BDEF198F25AE
              BDB6EA001972A2AA005972E2C6009972E2DA00D972C237200C39E11910969CB8
              1210A69CB812A0FE9CB0C29213AE00D334B0414D0368DC14234F829213AE003C
              5E05359AE7D0A170BF8820E5842B402D7FFFFB8503F38A085A4EB8023E7D5B87
              134BFCF6A5081972C209A8540C78375762E31F7B5C11E5B616966F1C3C912127
              9C57B2A595751C7B33C938E7303CA4E0AB812E2C69838CC59310892A818B6D9C
              803F3B7B70582C62676B2BC4E3EED72699FCEFFF8E014E01F1A263437C8CD39A
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'Logout_37127'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC400000EC401952B0E1B000004A1494441545847C5575D
              681C55143E33BBB3BBF9D9EC6677D3E687B4C606634430A20F85AAB4FEE18B88
              A43E28E24341104102FA52B0582DA4500B853CF4A52FB52F0AF5B154145A82A1
              B51A52437D49B46962526392AEC96E9ADDECCCEECC5CCF993BB333B399D9CC82
              E0C7DE9C6FBE99F39D33377BEFEC088B8B8B0CFE47046E4057CB8B0B53DFCAF2
              E65A1A0F05AE0284C300073200115117641504B902600F5D2CAB00AE028C19B9
              F13D07967A875ECF066D20377EFE68613BBFDC6B1EA30F8FCFF449F058177661
              96E13AAB464D07282A0C0A32ABC67C8941F6215DC32E076AA0A214AFFF70F6E5
              978887C229E83FF82E484D09D0751DF695AF42BB366B5C575BDCF8EBD2089C2F
              ADEB3039AF2D88A65A1F386D986624BEF6D157F0EC1B1FC013478EC2C00B6F42
              3CD36DE8EE423CBA35827DBE372540B20984600D20283116CF40C7FE4153A985
              BB388753DB793E2A0134D000C376775EEE36B5CDEB6BC890106D68066C2327EA
              15F2D34C1163433340C9B5E08ADBDCE61409FE5AF0065CC90EA0E667CEA39353
              A4EB3967A0076B80F28C04CBC105E36CD5DCE65E1AB2AA88113FF51B50947971
              7AFAE7D5BB3F9D37BA36E55AEC2CE4559CA225728DE975BE03C2F2F28C74F2E4
              3EE9C205F9D6E54FEE608EC3C086ADEC56DC101036C74DD2A3014D5B16AF5CB9
              171A1B1B847C3EACE97AE6D58D275FE95112D0B91583CAE424685353A0DFBE0D
              6C6E8EFCD07067A1FA1AE774E0DE8A37376743A74F77412E973095FA884621F4
              7E1AC495EB78C06021AB812432E86E0FF1F335C52D58FCC7D9CA9F7C0618CBC2
              C4C4B470EAD4005B5F4F30DCE3030D55A50920037C2E00FC724F835B7FC886E2
              5D9C343303235111A7F91A1C3F5E844B979E66F9BCA0A31A78505534418A5F1A
              067BE200DD29FE6434346216F1D0288AC5919192F6E0C1239E77B8DB7098D3E7
              F0A00407FB236621FB6E393799330721365FBC18D747466E96DBDA54BAA34687
              9FB953E3DC6EC8D2288AF880392C0D0D1D8A9C39B324A7528B5E457C071971CB
              AA39E726ABAB91EA5886422CF668F3B973CDDAB163D36A2281D771530D8782C5
              3C472462B8D89E0D14278EC3F3179196CFCF6E9F38D1296D6C24F1E4E454DBCA
              C72B2D0F6FB426F6C2DB9F7D076AA502155C011A3E9E85995110FEBEB6D39C33
              AAC199C7F9F1196B19D620944C3EDE3A3656D48787E7585797B8D0F6CFAA2C56
              4091709D673210A691C6F5DFDA6A4CA39739454B766B36A77FA1FF561C0AF534
              0F0FF7C7464753CFBFF3E5539466E6BA51D5DCE616EA69B417FB366041C4EF46
              CFC0731F5292D3C40DAFA9AEDF1081D8AE0D58A0443BD509BFE2267316747002
              63017F0F1028572E6E82AEE11B8703DCD37DB7561DB7668A35686806945201C6
              BFF9C2A709BB20C159DC0B24CBAACF32AC056EBB6B5F7FFE6287BC95351A96A2
              2D1069C28D1FEFFC509F02FBDBF1A1D460F1E59C0EDFDF517E0D3403B85BEE3D
              F2DED9BBB17887915C968B50C8ADE25883CDAD926F717A2D2B6B00A53240768B
              C17C5687DFEE6B30F1BB0A37EF27CB6F7D7A3517F4DDD040B95498CBADCDFF65
              1E52672C12168496FC8D5E5036DA219ACA4134BD25C43AB621962EAB2CCCE8E5
              B4824D38DF81047C74263BFB0642A1704F430DFCF700F8177A24733704A180D5
              0000000049454E44AE426082}
          end>
      end
      item
        Name = 'refresh_arrow_1546'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300021BEF00021BEF0149171B830000043D494441545847ED967F
              4C5B5514C7CF7D507E49611159C514B21A180EC7C23A4A0633FEC2A831841887
              599C6C661267169873D9B2E96404708B7FB8B06956638C1D4BD898269B66C41F
              D184CD44D62A8BE00F7E93A66390390B4B1845A82DBDC7776F5FDF78FD415F13
              C9FEF193347DEFDE77EFF7DC73CF3DF790B1B13184BB8820FDDF3562F20022C2
              5F2E27F64EFE0AF6693B4EB9A778BB216D15D16BB3A14467026D722AE18D2A51
              658067C10BE7872FE0E9C15618760D4514882371B031B30CB7E66F85670C4F13
              4D5CBCD4E38722854BD77EC0922C13494BD2F2B6A806748D5BE1A0F5004CCC8D
              4B2DEA5893FE301C361DC64DD9A5DC60267EE8C77A38673F0BAF3FB48B1E2A7D
              8B6F7FC418A0A2BB9BACEFE2F6CEEA98C51983B7FB615BE7CBE4F8D50FD0477D
              B238C3433DFC9F11D6034CFC1D7140BBFD8CD4A284B93A4F9B4F0514F8584A28
              118D1466175CBC3F98ACA407F04FF70D79EB76ACAEA18D9B1AF8E2959B2471C4
              761445F190BDCE4EC9C1DAC23AA8305488C1768FC27BF31E37768E5D0273DF49
              1898EE578C5D2C1E4CC8165C19B7E1E991538A016CC57B0BF7E1E5CD97C94B05
              5B88281E3261724212A9C87B8E74547690066323B2316A5018E0F52DF080F3A1
              4F6AF18B1F2B6DC1378BDF209AF8B00E53C0227FC7BA57484ECA2A2A352D89C2
              80EF1CDFE3F8DC75C5EA76AFDD832FE43F1FD185C104A2DDF1B73DC4BBE1507C
              D43EDC2E3DF9D1A764435D516DCCE2816857836CC0CCFC2CFE34695588ED2CD8
              896ADC1E80251935E21A41233D2D3A86336E17B4FC725CDE37F6D16E639D9096
              E8CF586A60739CEC35D3C5E73C18366F4DE1ABC2FDA93AFE1ED35DB01CA80A94
              E5E47F03E418B839EB04CB1F16EAA55EDE118E84B804A85B5F1B5360B2ABFCFD
              ABC7E47959101E30ED1734F1FE93201B70D4F61EFD64E8E3A81EB13C7E0A9F32
              94ABCE0DEDFD9FE1DBDD07E5EF5726EAC0BAC58A62C6E46DB2E0522B0FB0FE5E
              237D2CE751D5E22CB59BFBCCD29B9F325D992CCE501D034CBCEDD936B1CAB993
              44A261EEFD082782527BF59A6DD2931F5506E812B3B8B836517DBDF7E5F045FC
              B0EF84E2FBE28C122CCE322ADA541930E5710A9FFE6E01AF1850D1606EB7FCD6
              8AFB6C7B49F0ADDAB4B1090851AE4195016CA2137D2DE4890B4FE2B981CF71CE
              331F923D5941F2D5E8375879B1129A7B1A15E28C7A6303AE5D5910E241F91434
              5E69A6AD2316D9A074CD0ABCED9D0EEBF2D4782DE893F5D490FE20EF77CC38C4
              BD8E5C9255E76EC7238F348B8B0F9D2EAC0758C0755575414DFE6B612B1B2634
              E41A14BE9DF89AB0DFD0CC4058F1402515499C211BC0920C2310ED62DD4E1ACA
              EA495BF919D48BB520EF8C0136A6ADFC2CAFA4228933EE5CC7FFB8A0FB4637B2
              731E7CD458F09D1FF9023B1C1DF0F3A42D647F17B321C3842FE65641D5EACD62
              0917FDC8C67C1D3B5D53D8E3ECC1D1E95172CB7D8B8FBD2F29037257E4415166
              11D16933975C7130311BF05FA3EA182E1F00FF024D0DE163BE6D778300000000
              49454E44AE426082}
          end>
      end
      item
        Name = '3592814-document-general-letter-note-office-page'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              000970485973000011B7000011B7019A63532B000004B9494441545847AD5759
              731B4510EE3D74AE24EBB09C4392A51853C4241456142705792055BC110255F0
              C2EFE107E43F50BC50C51301BF4285C2908A232B06139C946359570CD6616CD9
              595DBB9BEEDDD57A57962C39D6A7FAA4B934DDD3333DD3CDE47239054640B3DD
              7EF0DD1F4BF7B1780B791919470A48C201328F7C86FCEDAB0F6EDD75D86CB7A9
              6318862AD091A47CA15AAD6572D9C9BA285EC0264EEB1908C9EB726D27E3972A
              B15028C873DCB4DEDE1703155014A55CAC55738F5E6CCC1C341A41BDF954F038
              9DD51B6FCD66A3C1509C6198B0DE6C415F0524592E2C66D2FFEE1E1E5EC72AA3
              B5BE319480203CBA934C4539968DE86D0658FDD740ABD3C9DE4F2FB751F80256
              CF2A9CC0E05C37714EB1DDE96CE96D062C0AE82B57F64571466F1A1B70CED99F
              32E90EC9D09B54185B407BFEE3CAE32C6A7B83D6DDA837A05AAC51BB3A10F047
              080810B8E0EF56F5AF21C0B9CC66A4EDB87BEDFAA5EE99302C40074E158E60F0
              D37C850A146A062BC87A659F3455C7BB6C1CF85CB6A114EC3C30260D4806C9D2
              AB9A05D0D50A3FA49785EE6947EDE0FFFF7621FF67B12B4FB544E0A21F6257A2
              E044E19FCC2720EC731BFD7D41966C756031B309D58396A10879C7E7A9854372
              515581ECCECE935FD79FCE6BDDC315E071A2B9F33EF0BB1D6AFB40E0B8665B82
              B5977B204A8A652B6ECF5DC9C4C3E124F37C63E397C5272BB378C944F5BE1E05
              34015D05A6AFC66804489274B2701DB49D2CC7AA739A819755E1CEFCB5175C78
              211542D7FB02DB2C1E417FB20B3C78420278273DE00D7BC017F682DDE9D0FA59
              7664F60A27A04CCF5AB1708F84D2DD7EEC7AB5BBEC108E4DC154FC9C416FC0A7
              F78E0524F34352801E966368892DA8E42A50DEEAB20CF51ABD3963C53C2970EC
              B1209389FB22949E6DC3CB758DA57FB6A156AA61AFB6EF2C8EE1D8E1A4712760
              9AF9FADB6F8E9DA4615EE0E039F8682E0241AF6BC841C4FBA4DD81074F8BB0FB
              EAC80DCDB01CBC5121CB1234C406341BC4E640B6B0BF218A806F00E9D2176481
              3AFE7AB4AA86AE0572AB476E48960F5C9C50DD903C5A9170D291EE629C8FA3DB
              B0AF0675B20045321628F871084E988CFB0D8690BE292F69A79A92E579A46D24
              0E104EC89302EB5AD9045C98131588BC1385E8E598CAD85C0CFCE703FA80B161
              951458424A6AD50409AF5072BB7A55E33EB279D8D47BC70292F9FBC0AB78AFBC
              07F9BFF00CC8D633107D97821A3C03A36DBF8A7E3BD0BD8A4FF9184DA01BC6C0
              8E6E984C847112FBD073D8966458D9DA81BAD8B628D27D8C5437A4E8959E48B5
              E7446833308A0CE73C768807DC103B81D3413744269C60EBD112655522C16088
              CA464454A8561EFFFCF71A05A1860506BB215EE48A34343E27D0D80E83EB24EA
              F8F8EA7BCB182953CC79741151E88CE1D2432AD39F6C4E1B78265DF81A6A14B0
              ECC2D5901D494199E5A135023B48B37092110904137AD51A9663C058A2E89502
              48DA7C59962DC61BF4B48E8A09B7FB39C68382393C3F520D411D9F2653BCCFE5
              DAA095B21C079C8967158EB981B33737B02840B0F17CE2B3D48293A257BDE9AC
              A0C4E421ADDCD6274DB36C811978F8C6929ADD9C7D7B93F61CAD377A6A660625
              A7A55AAD9ADEDA0C9F26394D2566CAE46A6F9C9CF6424FCFBFC7228570EF237B
              D373CA7856914B989E7F395A7A0EF01A573F74FA67C1073C0000000049454E44
              AE426082}
          end>
      end
      item
        Name = '3592828-general-key-key-lock-lock-office-password'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000B1300000B1301009A9C18000003FF494441545847C5974D
              6C134714C73DBBB6E3AF241B07F3DD24F4031A281110A081D20321E2C2010EAD
              50C509D10B20215471E5445B0E055109557C8803EAA18040158A84101F11AA14
              BEA4463421C2144A891354C0C4641D7F66BDBBD3F73C6307DB63BC4149F8494F
              33EF6F7BE7EDCC9B3763120A85A8AD12C658D78CAB9BAF406F1BD847603E9405
              C4C01E839D1EDED8B9D9263B3764D5B750310092893FAABDBD37664F3CFB0CDC
              2AA65624AD7B1BFAA26B8ED45187F713AE0991782B84A42341A57B572D0CDE0A
              AED5C111973D31B85AE9DEE9255AF421D784940FC0483F51EE7C5723A7C3B3B8
              9203672C03A615196A05B309BF9DABDCDAE386257CCAA512C44B40E9B0727377
              9F3DF66F3B57B218EE5983F1C5BB074DCF9C314A24F81D25EC13420935899C18
              727983279AE4D4CB794C67E8351F5F52D71EFDDC46C80C2EE5110620A523D7FD
              37B62D876E3D53E021DE0F7AD42F7EA987C46AE29218785B081E73A6852B4824
              B2FEB77BD4E5EFE07E1EE112D8D5A0179AFCE0C0F0E8AA1F472A0E8EC8550B46
              577E1F865E840959FC302B32EF17200A60C4F3CF9951DECF71DFACF20B1F20C2
              7405F0BB41E66521DE87275F423BC2DC714A03A026ACFD13937B59324A73D826
              C9CBB85B1922616EE02CE471A8411972AB97BB79CAED8282BC48376C5A004D1D
              F32C53F012E528BF0DDF84E6B27DF2B1160021A55B7592B0F316D7FE0554AD7E
              F7C0C50BE06D6722C3FDF4F768A66EE93508C4D24CB8862EE333BE615E9E80E7
              D1E9B3A9A62D3A75D6B6409ECC44918406066EC8F101A3FADE0F01D8BB0DA061
              C97582BD99F53A1856BA8950FC0C030C2B269C13F343D1B6C36E086411491C6F
              FE0AC4A360B3C1A60DC335F34574F5C17E0CA00FFCA54C9E76EE621236B3FE7B
              A11503184FC4E9C75E691B62F2A5783B25600E88F6B8A6577FD81D6BD947E146
              43899E24D5BD3FD9E0785E079F4DE462521151009A16587962B4F5C056D8F7D9
              BD9A85D2704DCFFE73CE577FEE000F8310058E336AADB8714A02D07D8DDDEABA
              630B7385A200B8A848C9FFFE22A6262848C4468C31C9D777A8C69E185A91152C
              501C80A9AEF9F90F5DF9743DF7270CD162D7EBBBBE6E84EE5B2FA3398AA74B37
              1D3E4BA758392067B0FA0D31AF32C50138242D6AF9E22102CE132CB9F8DFC112
              A539E09DDFA37E79722EE4C01C2E8D43CDB0E3757F90E871A81DA54B4C8CB4C3
              F3F857BF9C7C8E01BC530E204646597C2EDA76A81D82183F1FE0B4ACBDB3AFCB
              A13ED80ADEA4152F5100880E33D19F5CF46DDC70073439F5CAE9F9FB940F4ECB
              25F099837D6572C00092D0BA995B0206875510DFD8D2944E901426E14DD61782
              83E21B4FC5E0F8729D52A4FDACCDF0CCBBCFB4E90396B837B2E17CBD44AB940E
              B5ED30DED93BC1F0C632D5A4C120C98F0C536775C7FFB4C06E4CAEA8C6F80000
              000049454E44AE426082}
          end>
      end
      item
        Name = '3592827-access-general-house-key-key-lock-key-login'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000B1300000B1301009A9C1800000425494441545847B5976F
              681B7518C7EF77B9DCA5DDB44BFF5CB3B4C9B6AE1B0AA283298E8D31264644D4
              17D6E114E6AC537CABA8202ABE7353040527381D8A5327E8ABE11B072BDD1415
              2753D78D8D2A2B9A2535CDBFB6B3ED72C9DDFDCEEF73B976E4EFA569FB812FF7
              7B9EBBF07DFAFB5F168D462D6125B1F4E1D095BB7E456B10EA8634E8C7F10D43
              16973A23228295C3B2526AFC400AAD1720159A85C8F35E353EB85634264FAD5C
              0FD8E64F9E51B48B8F2032B4963BBF9C0CBCB94E34B2AC33F1E266C9488491FF
              76650A2833CFB5EE3892097EB04F60AC835ECBB991E1EEF8FE9D68F2E51F0217
              73C294BA4C3C0A90B2BC0534608E6FD29D8997E6D05A054597AF8006CDD5F8D3
              DFC9F9CB0F20BA0EBDB33C052CC25CD1FED88B88692D771F8BF59F1B587A01CD
              997F92EE39F2A8C0A4DD4B2BA079F3017CD345AFEB2DC32981E77F17F90C17CD
              69C1C3AF499CB5985CEAB0B8B89A5982C4D4F167B28EB9077A2BD6FFDB368179
              76DBBF265CCC89EA05F0FCDFEAF8733F29DAF92D887A209AB11244CB87B6D224
              3405DD0E2910717ABCEF8CC13D6B2276D48039515A00BAD437F7C3A83F7D7093
              642403C8B0E28BC6D0BDE1F3A9D0E769F490A4C69F8DB99913370AB0F8841ADB
              F7B392BFF42022D9CE35C769280A3D0E89F5CC896201969555E3FB4F29DA853D
              C8D1782E85F91ED561FE693D73C25E05B2767104E60FA3B954738286AD217342
              643C37D4917C95CEE9D662AA2A39280BCD40B556CD3CF946CD09C687FCCFE379
              08F2D99952F205E5D693D9C0DBAD9858F8D374A17DE28D2BBEDC591AAACEE227
              15FC12DB78F6BA202AF738715D68081E83AA996363D97E3419FA6ABB2187235C
              6A8F98527724DDFBD1DED9B63D5470BAF859052A130CEEB45DA10236159BA560
              495DCA040F57EB46FF94FADAEB79DF96934E5C4E97C867DD8669012AC05F6C96
              32DDF5F23476B5B54E588E3F1B3844F386E644393EC6E9B46D0C2AC05E09E570
              B18D76BD9A584CA1D94E978A7218B3CC86373032CF179BA5ACC9BC9BC083B6DB
              AA78CC2C99D0165D8E89E2163504746BAD00E7C02EDC5ACF396129164F754CBC
              426740B5C93BC7C57A2BBA142AA0BA8920F4E24A7D135D9DD1BED11396F9AF1A
              7F6AC85B18DBE6644A30BCBD09EE69BFCD095DA17DE07E3C8F43ED76A614EACA
              5841B9E5C27FFE037E915F936F9EFA6CB5A4C769E5D0E958413A78F87B6DD5CE
              5D4EE80A8BFE3336DC7DF5095D2EFC759F936B1A430A4613EB4F580293D73B29
              5744BA16A542C7FA0C29107372CDA2650307C716634ED84BD0125BFA33C1F7FF
              44B3D6EEE606FDE773BCE0BB832E288B62610FD095CD5B27C2DF8C34D1133338
              7C3E4EF71C7D083B40ADF3A126155732C6B531CCF251393FBA03611BA5EC1795
              E474EFBACB99E07B938677C35698579BC4AE2CF4C03C96E8DB980C7D410B7900
              FA10BA0AE91041870C1DCB27A0C164F8EB6943EE8B346B2E0882F03F3FD70E7C
              0349B1240000000049454E44AE426082}
          end>
      end
      item
        Name = '3592855-business-man-employee-general-human-member-office'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000B1300000B1301009A9C18000004DF494441545847AD976B
              4C5B6518C7CF7BDA9E5EB995D2126E0164BA85C9D825C1051525212E3A3F6844
              87CE991843A29865D9972D0E5DE63E6C33998A9B8BFA41DDC50FD30F633296A0
              CECB98CA26CEA0323737C34A596981AE5C4A5BDA9EF3FA3CE71C485BDA53A0FC
              C8BF3CCFD3F79C3EE7BD3CEF7B88DD6EA74C3C94BA73FB1BF683F52AA814C482
              EE808E7B2ABF6961089B0FF6B280378E8552C1E07CAF17AC7740952023480FAA
              00BD691C3A7813DAF0602F0BF3122091BB237AEFF906300D5224064E37F1FD83
              06675B07D882144A8FD804E0C94C770E07C1E2A4404288DE7B6E232384DDB29F
              16710984DD9CEF4A8EEC2991CBD0D0FCB9B304E28640EC55A5A79F45B54C2310
              9F808AC0C7B4642B126218B56CA6476C02446D9BC9A875C95E5242C60D6E86D5
              5965372DE21220ACAF6897192C8F144848C057FC8606DA2E4B17C40D01A032E4
              7B569E990919D7614F444F34B447FC96A62FA82AC32685D227712544288D107E
              7294F0531CD80C559BC294350A0CCB61159C9FB8841086E529C004E508672584
              C064552679024BC01799761F1868C355645A655871FB858267CA2009C5A18A79
              120A659817A82BC2D3E1500425C4890E87E13B68338C6DE5CB44D0FF7AA46B14
              4CAC239A7FFC37CB678410FA8A883D00F0BE1961F4648FD7F59B3D9005F14C90
              465634115018E45B5FA29B7AF101B32553C75AB0ABE11EEED65B076EC37735D8
              10A0ADE53BDD7A954E71E362F1898EFDE4E9DF7EDA990B3F5E0DB132502E0893
              C04D285A19205C2525BF0F062B777CE9CC3BFAC3D8BFD823D3826F27C4170DDB
              7C6A68B0D71EA8023BFE6917027BD511B4BE72C2B9E95DCF9EB3726C51E01CB8
              5F3217C40CE82E680C65CB508F3FBD368B363F94B39A0A2C56D145830928159D
              5970FFEF023DBBADC6BCFDE896C2FE23CF155EDBBBD936F86455A6A5A64CFF7C
              78DA9C6C692A8217FD2D99C9A9B072ED9F6C2DE23E7BA978ACEE3E5DB351CBD6
              9974ECC39C46F04668E4DBE1D0701B15D4386F6296DC2FE357DA6172BA042ACC
              13AE1A6C43EADFBEF43AFC3F0C4AB60BDA3F6C2AFCCFC0B1F503FEC19F3B46BB
              4CAB4DABACD8DF7FFAAE4D8C84C67058102C3AE5A0E8838C038443368F35A64A
              FF53B6C74B318175E07782922D97AF8E6D293912514DEDFBD871BCDA1B9958C8
              7961A1FC85433004728A6E623C8E1525DD07073E68831F4F744C4B8732F6D36D
              45A74B73352372201195FBF7F4651096FF03EC94F36511044027C54A78DD15BC
              74A86BB416028996D224A8C9D35F7B7E5F6B6763BED6DA021B4E4C3B027FDDE3
              3D97FB7D371AC1C5633C428B7585679FC86B30C7556DB1BD41A5E7B335595229
              9E08F017A0AAE15C4836BED7413BA0B77643D97D440AC5C253FEC7B76E1DC26A
              39578A5B8A5FBE58A0CBAF93FD84886B57AF21F8444AA7DC95A0537B3BDCE4F2
              80BFB76F28F02BEA862BD80DCB4969F8522226A05191EAE21C4DAA63B6C5E10D
              D77D74D1B3E1FD0B631B51277ABCF8D292166202D0AD6628A95A31B2081AD767
              87E0DAB4CE866202489985C3D370CAFD3B8A49E835BF6C2F99B904B2F4AAB5F7
              5AB9EFC05CC8819F42DB4EB351B546F697CC5C028079D7266B7D451E77066C5C
              A3C908DE93C7B543DB47A1FBB1FE8BB00C5B55A0CD9F925D24A865B5295F62A3
              136058426C70633C70E06BF9551026327B66C477C63ED06BBB1FB36641DB98D2
              8DF3686B4123DE0F8B150ECDE7D99ACC145B34C3FC0F4EBBEFBA626C81FA0000
              000049454E44AE426082}
          end>
      end
      item
        Name = '3592852-general-office-open-padlock-safety-unlock-unlock-padlock'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000B1300000B1301009A9C18000003F3494441545847C5974D
              68535914C7DF7D792F49B536FD489B9A8FA6B55A156C150AE33020825261DCE8
              C28E0B3F405DBA115C08E2C2951B170A225205B13A8C3ACCCC42988556B1A033
              5070A43628C8B4B549ADA62F69E2476D92F7E939B9B74D9BBCF6454DEB0F0EEF
              9C7FC8BBE77E9D7B1F0987C3066701D1D30FFC433FDE05771F58335839EA267C
              04FB1FECDA6873DF2E8E776CCFAA0B609900D13EBCF48C1E981495F006081D54
              B524AD888D03E3815F5D86AD7C2DD34CE1D9D3149B2A3DAF8F745642E3ED1016
              DB38E21495911FEA237B56F06AE205D34C993701A24F0DD68D1E7409EAB88749
              D3E0882960729EA13667340535EAF58CEE5F0E5338CCA402CCA7C030629E48E7
              805D1E9C3387AAB03292AC3D31A2DA8319F82B53A73138511E2EAB8C9D6D8486
              FD4CCC223BD6FD3D1EB8B99923C4CDA4194C13E055E99EEFD50E1CF61AAA40F7
              C4E09368C3EF35B0B09A98640AF476C813F905D64C6423939089B1A69EA7BA50
              DBC1E2194CA7C0917AB61C1E338D03F198AF2B61D53862F0CEE698EF9204EE04
              55B2540BCA6B1BF3E7609640B222716592F9D38434C12D32DF124DF06E82119B
              3DEFA4327E0E934AD23047E114185A6F60B03D05DECF54E0B88CB3F5B614B8B1
              03DC2AAA58833BC89E0E418324FB7E55F46714470B4EEB9C77CC97C014783BA9
              C07189BAD37D9F5CBB37B3B0A42C580772146E9452516402F95BAE74E4A6C0D0
              A3BC9608AD78F7DB9F15C9AB8740991972D9DED213F79E03EFDB1331889DD36D
              D56D1CE1B3058E84475E3D14E521B5E6EDF15AD8BB41D0B0E4DAC1666F1B150C
              2B5D298073A261440A743B755BD57AA2DFAFDA03E205B0FAECCF4B842A78A231
              DFE510263000712B95979C3E5C84EBA9FF5D68C70404EA7F1704AB6D888B0FAB
              223E17055C0366554696EDAB1F25EACF183A5F6EF0FA24A98E9EE4E078DE02BF
              7DC9C5C412B304E4D4B29FBAE2DE8B7BE1FCAE631A6C604372BF397ABB6CEADF
              231061126689E3881659DC28050928F6558FA30D7FB440A1C8353E0D5C540425
              DC4F0C192A52615122461A46EA948B5DE18AAA5AF909E8E3FEEE5EB96CE33616
              7F31BCF6BEC737BCB511DC35545998FCE152755B85C6FCAF02D60CEEAA088DAC
              C94F40E4B577A6379762E1B524EE98D534B2A6700D88C1FFA2C1BFBC1CB1AD64
              520E43971CA9272F78FD23F4925E346643F44FA26BE2925B50DFE0C7CB57AD01
              44CB38DB6E49FE6BDB6021E69280D3B2EEF5E1078E74FF5E884A56BCCC124054
              38B142EFDDC726E12A9E11D4B70E57FC7C399C96F87554F4DDB0183001BC7E95
              D1B0004C0EE7147BFCED97814252B808FFA1BE29D828F678311AC7CEDDE1C79A
              EE1B8A1808516DE98029EE1F5BD55BCDEB82BB43F2774741BB0386DF788B4D1A
              0CAEF9D7E3BAADB2E333147B7AC7F9B2FB560000000049454E44AE426082}
          end>
      end
      item
        Name = 'import'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000B1300000B1301009A9C180000074D4944415458479D570D
              505455147EEFC1AE42F2CF82A020ACA8240C8833620EFE8C9A464D63638E8E56
              82A5A4F9374419A964458D65532618D8D454988E7F6169F6632950A94D539380
              1019A8010B8B2BEC5B40D89FB7BBEFF59DB70BB1EC22E8377366CF39F7BE7BCE
              BDF79C73CFB24D4D4D12330C44516CE0386E52BBC550BEF2B7ED91504D0671F2
              E0FFB083FE2E9DF5CEAD20A5FF024992EA5996A57977C4E0450683D7EB7BCA0A
              8ACE3574F0B7CB77D5155BA18B0779FACE0B949857577CBB5DDF5D51587CAEDE
              60E83D0F1D2F8F0E81214FC06E175B73F38E97D7D4B6A443544AE19615F64CCD
              2E4664D31C338600275DF23A1895CFEA469D80649A9614FDDDEEFCE50F7B7971
              118E09AEF0780266B3F5FAFACD9FE960FC4955A85FD0BA35F3F4D96B1F563112
              3BDC8931313E91BEA505393B62A243EB21AAAAAE34AF796E6B49B3C562BDE198
              E10AB7057B7ACDF51BB67CC6695AF8E9106FEECC5DF2FBF265A9EAC53393D731
              D2B057C6CC57CD08F1BFCF77DEFEF7579B20E682DA9B9AF533376C29118D46A1
              419E34002E0BD2CE37677FAE68BBD9150B63550CCB3CA956ABB661E8ACC6A4DB
              ED98756794DFFAC360136D17944AEF5CC6D7BE0F6BACC65A75DAB6CEB84DD907
              99C127D11F0374E774ECCE9D578B8BDA8F89295D71B87305649AA3042D028582
              EE840ED0399000621113027729B886BB189C0529714274C86F070AD744232628
              9BFA4F80A78023E3E161FEBA439FACEF485D181D01E34F632C0394095A051ACE
              3881E6D05CFA26036BAC11D3F84EC6C66543D6D175BC927FF23478393B640790
              6A9508B8C560EDDB721EB91A16E6BFF08DA91B5726F8ABBF241DCDB947D89202
              261DF921AD28F387B32FEC4C9DA13E0E9DF4E7E5C6A59D9DBD97690287825191
              FFD6A96EF0E151E383AB12EE1F27170F8EE5C2F64D7B712E9CF80AE2BD38211B
              DF9B9C93EECD792F803CFFF5BCA5CB61E32FF063DFDC73460BDB3FB1F1499BC9
              E05950545141C6853875F87CF0FD10445BF9431736DFC051D17550B119096C22
              C3ECFF71CE07C90A87F17ED4D6B5FCFC42EED1D9609B41E9740574F4E349312E
              22C86DA74A9663B3AD86B711859F42A44A381C04CC2DD82DB41F50E05BA7AE1F
              1363C3688D26D038D07472600948316572448D8F8F3205BC0B3893CE9665ED3A
              70C4DC7614DE1543752727043BC3EE39636AFDFE315BEFC79CB9C36D43A3472B
              52D4B1AA46B094558BC981381AD8F8EC8200FC84103F00BC5FE56E138E735192
              6879BFD4AC3D8D158BA0F7E4846083F16F4D9A5F62256B21BE99E757FD4E1BF4
              2E6F011EA890D5ABD27C9CE25C72808C0A7E7E3EEE81265AAB14DD0D5132CB30
              C9F78B0239F1357639D8090B19FF0EC663245B01E64E25A5C2509B406BC83306
              20323288AA247DAF2207E828EC0A8587F8122996982087205723D98993E6D633
              5686CDC7603DE82A8CEFF8DE691C7364E34E043BD77081AF8F9274B4612539E0
              802457BB61414EC48B4271A5B1519B2BF06B770A7C56B5B1D13841B27D38C8F8
              88400E9841DE569BDD2D6219CE9BC6DDDE73189A328A918A326CDD479EB0751F
              F566A47DD04D740E0F84DEB9860B8C26817474E46662F4204577B7C9FD0E38C5
              346BC064CA574F188D738C02510A8F72A85C2104275DC11A6E99D5D2CAFBE287
              DE987672E01A298B3F2AEBC10F393310C1B7A7ED18835F8343BC2BF03DC92F91
              73FD314440F5D31F3EFA2B9D3AA1821CA0522BD437DC4C341A2D6E112BFA84A7
              5803E3CB9CE2482161F7A7C5D1A1F4B2BAC06412AAFE6D6C8F016B019D2707CA
              411A50546B5B27C9AE40DE763DF0DE03B63131BF401A49A04A363FF5F9EED4B7
              A8951B5C579886EB3A3AFA68500BA88A3BFBF58B1FC54F89A09D7BED79F79B40
              F405543C5CC17A8DEF9C5DA4B6064E3D06A9CBA1F40803765ED299B63F11DFB8
              F580585B5B50F42339C5A5244F2827DB7243C2F33DE757651E48C040F8AC9971
              7B5FCB5BBA16BCCBDDC990A40E94D74ABFEA3D37516412A1E99BA3A780A33B17
              47854CA75373EA07827F39EF446965755316F8B6138737D50504F83ED8D711F1
              2FED3876AABA46F30C785DC9C759B511630317D2574380972B5C5F91A15443C6
              800B96650FD0B4E8CBD63DF76932D8909933D485F9BB9651A31334B025D3A27B
              6D41C7921A1911D880B689C3C3E129B7EF1AC8FB6B1BB7967851AF191BA3BA58
              5C9031117F74E42BEA0F3AEAD1F6EF5D1D0AE3D7D0404E8233A2B6CD40D17F2F
              29D8071E395FD6677C5C64D03F85EF3D35BECF38C1ED8F09B5CEE85E59EA6221
              EAA88DA24E66E047230105F3CE574BCFE0CE1F87184AC68B0B32BD079FAA9B03
              046A9DB7E41CA27E7E0644116DD4DFCF6F49E7F18E5B9D3D83A720938B0CE579
              C3359D02D11EDAAA35C8FF2171ECBFD2CED1AA53FEBBC0A30304DA01BAD75368
              206907E1207A3E35D44CD07B4E4FAAF355637A8D160EC67C51E12C283213A0A2
              0AE80DD222E0BE4056AD18EA048774C0099EBA576A206B6A357320531B45CF37
              811CEAEB21E81DA10243A00AD74279BE7DDBA3B14835AA864366C7700EC8A0CE
              397DC9BB1BC0D262D443CE05A9407DCE90D15BA00A1005EE65B9C8B0AC4B83EB
              0E86F90F93CA4330AF3E1D550000000049454E44AE426082}
          end>
      end
      item
        Name = 'export'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000B1300000B1301009A9C1800000772494441545847A55709
              6C5455177EEFCD42A774996E337401DAB215218542008D4BA2125A8C4850D148
              B4C5051028FC8202FEFE15B51A0C5A8CA5B60A44C425A2B8A135514969110D89
              1AA1958248AB7F6B374ADB9969693B9DE5BDE7F7CD46A7D35AD02F3973CF3DF7
              BC7BCE5DCEB967C4C6C6465518058AA21C5BBC74D71AB08B055518A764F6EC51
              723A36815FC96141144A355F9AF78A6723F2C1374076E4EB2F9ED82B8AE2CDFC
              FEEF20F9DA9160B1587A2B366D7DDF02FE080CE6AA71AE4A25BBE33FE0E95014
              C8087EB37C5BFB1A21DA5D057E3575F14DA7D5DA57C139402362C41D9065A565
              5BC18795A76B9BB3D13561E2336ABC73A3FC70D3ED58F37AC8F41EC5CB700892
              5AA4D9937A5CB469776327A641D6363B73C2573B0A972FD668A444AF5A308675
              6060C0F57BFEA677BA9B9A2DB3D15560FC7BD5E47C465ED9B40CFC3AC8861AF7
              C301C3459A7D13AA44ABEE59F0D741264E9C10F753C92B0F248C19A34BF7AA5D
              468803BD7D03E7F31F7B47D776A13B0DDD5698DFA1CCEDFE4A59D8B905C61F82
              6C24E37E60277027CACD65E29988A5E0B741664A4A34D697BE9AA78687EBA778
              D5BC0872802B7F74C35B92CFF82F82226E703F515F2368849760FC41C8741EC5
              D1E1C2EACB847ECD766D49DA3C1C4D0964D3E144DD1B252B35837722700979E6
              DCF6807159CC73179EAB86C6CB57699CD0798ECA203FEF2E38FF23E782EC6C6B
              9B6DCA86CDEF5E84AD56AFDA65072CBC7038F339665354FBBB6FAEB9B8E79315
              7142AFB608630CB5AB31EE07BF592B38A517F67F9A1B7160DFAA369329AAB3F1
              CFAE054F177EF239C63CD1E171A0ABABF7146EFB22B0F296CDB79D83E2C28B76
              CB73E8F3CCFF89713F3C4E5C72F66F4F1C67BC75E3BA45E7D0577F3ED9B0CC66
              EB3B49054955D5AAC2170FF780378F4F89AD9E313D792A07AE894A3765464F79
              1F6C192EC96BA07DE0DB39360ADAA9CB6FC097618E83A963132772606ED6C449
              B07106ECB8177696B7C2F6313123339F06BF068D2F2DCEFD6E72BA7970F6B2BA
              557949E4374BCEBDA1358E7D5B177548148405BEB16101C33FE4B97B96AF76D9
              2EF56597CFD08A9A728863BCA382507BB6F9DBC7B71DBC01EC9FA01C1E01B73E
              8582E4C41819ED60C46805B1305255B6E7C87D539173878E87803AD9EEBE69D1
              AAB295DF4214304E4C4A33B9D03482924173E8C01D20DDB4A989A70D067D16F8
              2048F67619AB5A2A0AAA8476545047F2EAAE90063A15AFF432C2C27459E96909
              7C2F984F16D181C91C58B7FA96683471E407C112796AC7005ACA39F795FA408A
              8DAC79E902DAA0B7000F54DC03F75D6FF0756FA2039CDC19196908DD5EC555AD
              EBA94BC16C7AB32A87A11DF51242E7F764D56D441BA6B3D6CEE01CBEA1009292
              62EC6878140974600C48D6E93468864071730B7986FA0455BE3B437196BA05F1
              18844C9F0D68075323C62AE62A037B63546505BE6108C6F8E60842B8414F1917
              ACD77A2484FAF7DB8B2FEEFD6CA0C571426378FE0729CC2E0B62D0C45A9CFB8D
              B2DD0007566160B14F3C2A188656B463F7EF79E4787252CCAD5EB10F8AAB32FE
              9B25467073BC02BC0E82D009B281E70AC07A40E7B5F8E1D6F348B9B3C4CF9DD9
              E5DD82A4BBC5D7F7A0A1B1B3724DFE5B3782EDA3621748D7D3630F3D034937DB
              153D95F1EA076FB7092B44480AD341193E223F056309D4F1AAE262C566FE8239
              4222ABB9C5128E8647D441E57A0ACBF61EED4543670623F6D2ECA722D07297AE
              1696DE595B995F82F200B25FD77B074F30B2882A3AF019C879BEEEC2CCFE7E47
              C88D550CE62C9731E3A8AF7BA550B1FACF95B078FFD10560B73BABFFDFD0910A
              D601AAA00395A026D0F896365B60FB0240DC765FBBEB5A7744EA71F478D6A341
              7547A657F4CC7F3107FCD0BC22D4D5B773EBF9363483AA2556AF19D312B972CD
              CEA22F8D78ABDBC00743D4A4D86E284D7719AFF900BD6EAF705858B1F203B6EB
              4B66E29B901A90754071D9113A2566CD9A58E9A99C5911B1F2BD2FEFF5191830
              5FB760F22BCF162C7B187CD0D979A0AA9D48AFA7226B765E40929909895FA78B
              178E67AE8C899BC35DF3C907C3F264C1A18F4FD534AE02DF76E8BDF567A3A3C3
              17FA4B32CBD6A73E385C73BA89EF7F3B8A875ABEDFFC6A04583C19CE9F6424AD
              C4880117EBE90F83A6E6AEA38FACDD3F0B6CDC8279E9BB0BB7DF950B3E265013
              727BD66E3CD08C8A653E6BB7D777AF94F0704CE2D8BF45BFDD59BF6EE3010DCB
              BDB4D484EFCB8A73274992B74C0F5C3AD4ED49289DE359BDB27683334A6B9B95
              B7FF9F84A01F16C4FC51BF7124BADF76EFBA3FC56F9C0829CBFBFB9D75EB1F7B
              5B84137C25DBE7CF4BFFF0B98265CB077F7425E065FEDF331F97E3CCEF44379E
              C6CB8AF3B4437735C401C2E170FD81EAB503C7310F5D0565D4AF9B36E458F08E
              BB7C35C37097CC936418E70CB5E2D223F12DAD56565B12B6FD0457AED76B19FF
              4118D601822B40F57A180524576006F1F96C6231C1F79C4FAAEF5513FAFA1D12
              8C8523C339906418E3CC807CE85A71E13E4254DD33D20E8EE8800F1656AF2C20
              4FD736F1F16019E5FF674487FC3504DF117FF5CC0CD7CC38FFEF96DBD3106ACC
              862346C7680E78C0CA39E78EA247C17232D6903781F8F0F89DA1D18BA02A102F
              EEC92BFB7B2E087F0186C944CD92BFC2E90000000049454E44AE426082}
          end>
      end
      item
        Name = 'notification'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F4000000017352474200AECE1CE90000000467414D410000B18F0BFC61050000
              00097048597300000EC200000EC20115284A80000003B5494441545847CD974B
              48545118C7BF734753477BA02159611499AFE869504116440F3751112D82A845
              4511442D925AD4A216452D5C44448F4511B488A8A8854604655041F624B53292
              914A11951E3A6ACDCCEDFE8EF74E33CE43536CFAC130F771EEF7FFCEB9E77CE7
              7F95C7E331651098A6296D3FBE4A75638DD9F4AD5955BD7FD8D1F9AB2B897B19
              C9E9BED5339664E68ECD314BA796A8F1A3C789524A3F37100326F0CBEF93CAFA
              8752F9AE5A5EB7BEB3AFC6675676BE94E5974A59E1124976E91C631233017A7C
              BFE1A99C7E72459ABB5AC5A50C993BA158E64D2A92BCAC29E6CC0979615D7CD3
              D26036B47BD4F3CF75F2A2A556FC664072D2B3A57CE93659905B1C7344A226E0
              B37A5D517D596EBEBDAB85974F5D245B4BD6C994AC89768BF878DABFC8C59A1B
              72AFF1B14E646DC10AD957BA5992A28C4644029DBD5ED977EBB8D4B57DD03D38
              B86C87CCCF2DB2EFFE1DCF9AEAE4D8FD737A048BC64F978A35072423C56DDFED
              232C017ABEEBFA112D1EEB01079FDF2F351DAFF4B32599B35592CBA5AFF727B4
              43C43CB3FE70D84818F6BF7EE70CFB60C4E1EAA75B72FB6B95E2C7712C88412C
              62121B0DB41C820930E178E70CFB40E2DE9EDE405DEF5BFB4C84E36EEB9A7D1A
              819304B1D178DA546BDFB11360A931DB9970BCF378E210B02696A9FEF482E340
              20A6BE8698C446E3C4830B5A137402AC73260AB37DA8136E30101B0DB4D00483
              F74191213396DA4883065A68A26D505EA9701499C1AEF3E180065A68A26D50DB
              B94185FB57385A681B6C2C9C505EF5D51098D95DDEEE885F678FD76F3709D2D9
              D3ED8BD636DAEA70B4D056058756B65BBB5A66E596F332C69DAE1B506458DB2C
              AFD0D93E1494A9A428A540364E5E6315A0BE62F5DDDB256597B6B38B7618CE96
              1A0A15AEF667FDB0C58118C472AA662896B62B58881284323013F649106A7BF1
              A8423D7CC38518C422A67D2908DA6AEFE5A3E6B5DA2A39B9AADC5C3C6D4E5823
              2650B40AF7A3D7EB3FD57636D93ED5ECC9DAF93323352DE2751A862169A92961
              23FDE8E34B73FF9D136A43F16A31B0515CC44CE8BB21F060BA3B2DE29791EA8E
              D8FA108FD6B6BF38385A681B78384E7032FF0A470B6D03038987C346E164461A
              34D042136D03AF8681C43A61A3461A34D042136DFD7E70AFECD578386CD44841
              6C34D04213740258E7DD0B37E9CCF070D8A87818D66E16BA443966B6C78398C4
              46A3DC72CA8E5D0F3EB52C6F8176AFECD578B87849B8AD994D7975E038DA6C77
              707C21B1D1C0A63B24DC94FE5FB6DC21A11F260E09FD340B25611FA7FD614462
              7C9E9BD6AEE61FDAE7B9C86F89468B54A1D6C5710000000049454E44AE426082}
          end>
      end>
    Left = 424
    Top = 545
  end
  object Listener: TIdTCPServer
    Bindings = <>
    DefaultPort = 0
    OnConnect = ListenerConnect
    OnDisconnect = ListenerDisconnect
    OnExecute = ListenerExecute
    Left = 200
    Top = 544
  end
  object PPEditItem: TPopupMenu
    Left = 488
    Top = 545
    object PPRefresh: TMenuItem
      Caption = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1110' '#1090#1072#1073#1083#1080#1094#1110
      OnClick = PPRefreshClick
    end
    object PPEdit: TMenuItem
      Caption = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081
      OnClick = PPEditClick
    end
    object PPRemove: TMenuItem
      Caption = #1042#1080#1076#1072#1083#1080#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081
      Enabled = False
      OnClick = PPRemoveClick
    end
  end
  object PPEditUser: TPopupMenu
    Left = 551
    Top = 545
    object PPUsersRefresh: TMenuItem
      Caption = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1110' '#1090#1072#1073#1083#1080#1094#1110
    end
    object PPSetPwd: TMenuItem
      Caption = #1042#1089#1090#1072#1085#1086#1074#1080#1090#1080' '#1087#1072#1088#1086#1083#1100
      OnClick = PPSetPwdClick
    end
    object PPLockUser: TMenuItem
      Caption = #1047#1072#1073#1083#1086#1082#1091#1074#1072#1090#1080' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1072
      OnClick = PPLockUserClick
    end
    object PPUnlockUser: TMenuItem
      Caption = #1056#1086#1079#1073#1083#1086#1082#1091#1074#1072#1090#1080' '#1082#1086#1088#1080#1089#1090#1091#1074#1072#1095#1072
      OnClick = PPUnlockUserClick
    end
  end
  object PPEditLoc: TPopupMenu
    Left = 615
    Top = 545
    object PPLocationsRefresh: TMenuItem
      Caption = #1054#1085#1086#1074#1080#1090#1080' '#1076#1072#1085#1110' '#1090#1072#1073#1083#1080#1094#1110
      OnClick = PPLocationsRefreshClick
    end
    object PPAddLocation: TMenuItem
      Caption = #1044#1086#1076#1072#1090#1080' '#1051#1086#1082#1072#1094#1110#1102
      OnClick = PPAddLocationClick
    end
    object PPEditLocation: TMenuItem
      Caption = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1076#1072#1085#1110' '#1051#1086#1082#1072#1094#1110#1111
      OnClick = PPEditLocationClick
    end
    object PPRemoveLocation: TMenuItem
      Caption = #1042#1080#1076#1072#1083#1080#1090#1080' '#1051#1086#1082#1072#1094#1110#1102
      OnClick = PPRemoveLocationClick
    end
  end
  object PPItemOptions: TPopupMenu
    Left = 680
    Top = 545
    object PPCheckDelFromTable: TMenuItem
      Caption = #1055#1088#1080#1073#1088#1072#1090#1080' '#1079' '#1074#1110#1076#1086#1084#1086#1089#1090#1110
      OnClick = PPCheckDelFromTableClick
    end
    object PPCheckEdit: TMenuItem
      Caption = #1056#1077#1076#1072#1075#1091#1074#1072#1090#1080' '#1055#1088#1080#1089#1090#1088#1110#1081
      OnClick = PPEditClick
    end
    object PPCheckSetUnknown: TMenuItem
      Caption = #1055#1077#1088#1077#1085#1077#1089#1090#1080' '#1091' '#1053#1077#1079#39#1103#1089#1086#1074#1072#1085#1110
      OnClick = PPCheckSetUnknownClick
    end
  end
  object OpenCSVDialog: TOpenDialog
    Filter = #1092#1072#1081#1083#1080' CSV|*.csv'
    Left = 32
    Top = 545
  end
end
