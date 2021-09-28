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
      Top = 118
      Width = 769
      Height = 357
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      TabOrder = 0
      OnMouseUp = CheckItemResultMouseUp
    end
    object Panel4: TPanel
      Left = 1
      Top = 24
      Width = 769
      Height = 94
      Align = alTop
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
  end
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
      Top = 59
      Width = 769
      Height = 391
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditItem
      TabOrder = 2
      OnMouseUp = CheckItemResultMouseUp
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
      Top = 100
      Width = 769
      Height = 350
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPItemOptions
      TabOrder = 2
      OnDrawCell = CheckItemsResultDrawCell
      OnMouseUp = CheckItemResultMouseUp
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
      Top = 24
      Width = 769
      Height = 426
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditUser
      TabOrder = 1
      OnMouseUp = CheckItemResultMouseUp
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
    end
    object AdmLocationsResult: TStringGrid
      Left = 1
      Top = 24
      Width = 769
      Height = 426
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditLoc
      TabOrder = 1
      OnMouseUp = CheckItemResultMouseUp
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
      Top = 65
      Width = 769
      Height = 410
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditUser
      TabOrder = 1
      OnMouseUp = CheckItemResultMouseUp
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
      Top = 24
      Width = 769
      Height = 267
      Align = alClient
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goRowSelect]
      PopupMenu = PPEditLoc
      TabOrder = 0
      OnMouseUp = CheckItemResultMouseUp
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
              F40000000473424954080808087C086488000000097048597300000EC400000E
              C401952B0E1B000002BE494441545885ED96CB4BD45114C73FE7FECA99A4898A
              9E5028F6206C518BA2287B182442F4585A2DB43F20883691619395D14A8CA04D
              48B4E841206E83D27484147A489B317A51B8305032B1D469FADDD3621ECE8C43
              8CCE4F5AE4177EF0BBF79C7BCFF7F7BDE79EDF8139CCE17F87A40EF47EC90170
              6E226C023133DFD6DD8D4531CEF394DD2DCA5B704FCB894FED5308E8BD8DCB10
              FD844860E6817380EA282A2572F2DD10C0E4578ABBCBB3E0AA8DA83666B58904
              10775762386F7291F8D20F241F0291ABB160FEB3D9EDE29B4AC04B185F57AEAE
              B34340E35AE6A0E82C118894C508F8BFE54EC0680FD60631720664495E048CFF
              02D86CCC86B1DA84D19EC4CC1491F4E1862D585E20323F2F125336D62886ED52
              F5FE4D1AD74CBFB84328BF68EEEED893865066F0AC043C83457371FBE7473059
              8A1FAC5B8B95539E2461BC0A8EE09CFDA0058CAB61A9B8AC97C87081DA268CDE
              91E31FFB21F51658D98931F579058EE3E2EF958FBADDC2F3226053445E88BBE4
              88335A7F98EF7D403FCC420EBCB40B786D1774ABC8519B71C23F70B8EF2EA62A
              5A545BD65CB91C3C2E44FD761E97A22B98C02423D7EDAB05203CD8474BB81500
              41B6FA1CDB4290FD9E12B8ED2E652243D47DC57B93EF2DB4A658644F79514555
              CAEF5823F9041F51438F2D9CD61A63A4C6B386E495F5732EBA1A88C99EFAE599
              B8DCD140E84B17AA3A9C5420D6A1B8C7500D83662BE47FC5B84E3F9F0509A4E5
              40BC57DB3CED9D80FDCD0777380E3D104BB804124A0CFE1C4CCE0F8E0D01A0D8
              01AF7A204A83A505AB8AD77C15492F624FAB1F03D0F939C495CE6B696B54F5AE
              6775205C1FFEA5A2B772F55755578C7BC3D36B385E38DA5038B6E890205B1373
              973B1A8049D9930444AFB757B7F57A7604099435572EF739B605644F36BBAABA
              2A7AFD59CD933A403D27004010535E5451658CD4A8EA3641028A1D006917E3DE
              68AB6EEB4DB8FE01231D06F1A7E9633F0000000049454E44AE426082}
          end>
      end
      item
        Name = 'bootloader_users_person_people_6080'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000000473424954080808087C086488000000097048597300000EC400000E
              C401952B0E1B000006B1494441545885DD976B8C165719C77F672E6766DEBDBE
              7B8165B9955D9662297209863BA67C28F62284A4D1D8D69834B589D454AD69AC
              D6A435E007E3255AACB50D694A299A5628C4D206342D88462AA504A448902CBB
              94B2BBB0EFFD3EF39E99E3876509967DC16CED077D9293333367CEFC7FE739CF
              73CE19F85FB1DF3C4CE7CE6F32E9BFFD5D71A3177E72BFF350CCE1079E233A62
              3149ACAE7ED836F56BBE3FF8A3753FA4EF1305F8CE5DDEFA3A4FBCE63AE0D81A
              D7113435B7D0DCD681B4291613A7BFF0F94DF9373F0E8059AB61CB0334B4B71A
              CF46DA989A2D08C28891A214081BDB8B4BCB6D5E7757F7C0CB3B8F901B2F8051
              AB21B2E4A3D2164BE7DC3283852BD652F26D0A254126A74826B3A4533994D952
              AFBCF66F8D57FCBA00998258582809E2533FC3DA2F3FCABD5F7B8AC868225F82
              54AA4C32992593CA51158D777C2200E93CD97C59D079D3020C55E296798BD9F0
              DD9F11EFB8996C312291C8934CE52896F474C01E2F40CD18E89E684D6C8BC7EF
              5E73F77D085D454421F50D4D2C59F539E2ED93A954AAA486CE93CD6652074FF9
              BF00C2F100D4F4C05B47FCD71BDB6FCE1861052A59F0B3E0E730A3328B972CE7
              C10D8FD1D9313138D65FDA08F8E31107B06A357C5866A0B563E6CB04C5AF532D
              82E582E98029C1B4A19242C67B9EDB73F4E81680ED8FD0232DF99469EA95A649
              BD21749F69F0DB3339B5F91B9B6B03D6F400A0BB3BDBF7A301BF00E534945350
              1A864C1F0445264D99B617F09F7F90591AF9AE8AC4BD2A34A62A25E261642C54
              91F1E3EE7AFBC0AB1BA81F0F006FFCE59D9385A25F443642A8202842250FAA8A
              1FCAD2AFB71E380A204CE7E72A144D2A846A082A1234C53B500A542496C87AF3
              FBB5346A0621C0FE23FD99E4D03F8757CCEB5AE3798D269102535250F0D3ADBB
              9E7C66E7A13F3CB99EF63AD77A562384D60234F42CBC93655F791513C550DF11
              B416F396CF889ED97BE2DAA9B8AE0780F0F937CEBC58213C339C38CF5032C9A5
              F4252C4F30F7D64FED0122DB7616A84818550561084E2CCEFCD50F23C20A3DB7
              3DCEC4EECFA222A3A1A5D55E3F9640CD2004D8F2D2BE5B43BFBA2E3F69CAB4F6
              963AD2A93CEDAD4DF8A6495B90DEF4E2F67B767FB8EFA159ADCD0566F62C2208
              2A4C99B518DB00823C02839B16DDC7B95307D111EB80ADD705D8B6EDCDC66C29
              BCA7582ADF81102BD2E97C87E73A1C3E9162C1BC387DE715E54810860AD374D7
              CE9F3B73AD7D6135CDE10916ADFA22512585E1C6C1CF8136004163633B4A8161
              8AA58C6C7E7A4C80CD5B7677E6CBD1BB8964BAD39636AE944829F15C07DBB2E8
              ED1DC4716C52A93C966D61590641A0C827CE522A0C8130312235B25E20400B40
              50CDF4530D05F5928E475633E1E9B7B9382640CC729F184E663A6DDBC6950EAE
              2B711D49CC73F1BC917B47DAD8B689659998A6417AE014177A4F6391A3EAFBD8
              610851057406B486D225127D47A82A28FB8278DC9A0A6A6C00218C55611421E5
              88B0E78C887A9E3302E048A4B4B02D93C1DEF7E83BFE16C31FFC1DBF9C23B235
              83831798D6D604AA0451198232180643972E52F6054115CAC1B531379A059630
              44B7699838B6C471E488075C076FB47823B5E34ABAE62E4395060872E7883428
              25F8DD2B2F902BFA60480843C248D03F98E2C09F0E713165E207517AC76175F6
              A30026C0C68DCFCD686C6EF9B61F542F8B4ABCCBAE8F79CEC834B80E8E63236D
              0BCB3299307536D56A95A1FEF7D191A6582A53E742537D3DD5C8E0745F1FEF1C
              3DC6C5C1015C4765FF7AA6FAF8E15EFDE731B320DEDED61345119669615B16D2
              B691D2C29136EE55DE90B6891002A542BCE62E5A66ACC43CBC97A09424A80ADA
              3A26D338A115A5AACC5B761BCAF6F40B7B8EBD77FC6CE57B399FFD1FCD802B00
              9974A221166BD0966908CB1A0932CBB290D2464A1BDBB6310D03A534A0D11AD2
              993427FB2E71DE5D4E223F4863630327FBB37C7A8E89655A504EF0B79343C299
              BC74D19CE6E2EFF3F9FC1F53A9D4AE818181DD40FA4AEC5DAEEBD7AEBFFFAB93
              3BA72F4118789733C019ADA5C5D58BE6B973BDB376ECD83EDFF33C62B1189EE7
              E1791E73DACB3CFDD87A1002047CE9895738DE5FFCB711572A95623E9FBF3391
              481CBC1A60F4DAE2C6477521843826A59C3D2A3C0AD1EA9479FB970F60581661
              A499B8661325FFDA734A1445C77CDF5F08E8ABD34203D51B8803ACD45ACF0E82
              80200828168BB8AE8BE779240829E733D435B570E8F839929902428C399EF9C0
              EDC0BE1B6D46B53A5F0926A514854281643249329DE3830B4908235E3FF88F5A
              E2A3763BDC6033AA61DB80486BDD75F5C3300C09C3905FED3E4AD7F421761D78
              1FADAF09FA511B02B6C37FF06B761D1B8FF7462DFA187DFFCFEC5F3E0ACE60EF
              55FC550000000049454E44AE426082}
          end>
      end
      item
        Name = 'checklist_icon_129185'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C0000023A504C5445000000DC8744F6C358F7C659FDD4
              5EFED65FF5C258FFDA60FFD75FEAA74FE7A14DDC8744DC8744DC8744DC8744DC
              8744DC8744DC8744DC8744DC8744DC8744DC8744DC8744DC8744DC8744DC8744
              DC8744DC8744DC8744DC8744DC8744DC8744F6C358F6C358F6C255F6C153F6C2
              54E49949DC8744E49A4AF6C254F6C358F6C358F6C258F6C358F4BF56F4BE56F3
              BB55F2B955E4994AE8A24DE8A24DE49A4ADC8644DC8744F6C358F8D180FADC9D
              F9D897E49C56DB8440DB8541F6C357FBE6BAFFFFFFFCF6F1E9B287E4A471E5A5
              72F6C257FFFFFEFFFDFAFFFCF9FEFBF9FEFBF8FFFEFEFCE7BBECF0F4B5BFC7B1
              BCC5B0BBC4D1D8DDFEFEFEFBFCFCFCFCFDFEE8BCD7DDE38D9DA9BEC8CFBFC9D0
              A3A4ADBB9393F7EDECECF0F2ECEFF1EEF1F3FDFDFDD6DDE4A7A5ACFCDCD8FEE5
              E2D59590C1A5A6FEFDFCD6DDE3A8ADB5F4B2AAF5B3AABFB2B5A3B1BCFEFFFFD8
              DEE48395A3A2A5AEA3A8B1899AA7A4B0BAF9FAFBF7FAFCF0F3F7C3CBD1BFC8CF
              BFC7CFDBE0E4FDE8BBE9EDF1A6B2BCA3AFB9A1AFBAC9CACFFEFBFB8C9BA7BDC5
              CCBDC7CEAA989DC38E8CF7EDEDA7A4ACF8C6BFFAC7C0CC928FB3ADB3A9B3BCF7
              C6C0F8C4BDC0C3C9A3B1BBFAFBFCFDFEFFD9DFE58798A5A8B3BDA9B5BEEBEFF1
              F7F9FCF4F7FAD3D9DECFD6DBD0D6DBE5E8EBA2AFB9A1AEB8C9D1D68C9CA8BDC6
              CDBEC7CE97A5B1C2CAD1D6DCE3FDFEFEF8F9FAFCFEFF8999A6AAB6BF8E9EAAA7
              B3BDEDF0F1F8FAFCF6F8FBD9DEE2D6DBE0D6DCE0E8EBEEF4D89AF3E7CBF3E6C9
              F6C258F6C35AF5C45BE8A34D50B456F70000003574524E530000000000000000
              0000005DDBDA59042B3E3D42BF6364BE2A4AE6F6F981E5482F90979695C8FCC1
              942B8E7D968F8F96886AFBFA5C76547BBA00000001624B474440FED95CD80000
              00097048597300000E6B00000E6B0154FE0D060000018C4944415438CB636040
              028C8CDC3CBC7C8C8C0CD80023BF80A090B088A898B8B090A0043FA622464929
              696969195959192025278FA280494151495945D5D40C08D4D440A4A9BA86B292
              A226134C8196B985A595B58D2D1CD8585B595A986B33C314E8D8D93B383A39BB
              C081B393A383BDAB2E0BB202377777770F4F28F0F2F4062AD0634528F0F1F5F3
              F70F080C0A06821007304055101A161E1119151D131B1717179F804D41625272
              4A6A5A7A100860352123332B3B27D721180EF2D014E4171416159794C6C14199
              0FAA23CB2B2A2BABAA1D82E000CD0A7B070C80AAA0A6B6AEBEBEA1B1096C3D76
              6F36B7B4B6B577E0F1666757774FAF031E6FF6F54F9838296F321C4C41533075
              DAF419E175086FCE9C85E6CDD973E6CE9D379F326F2EA85FB82808B73733162F
              59BAAC1EEC06ECDECC98E1E0B0BC048F37578015AC5C0507ABD1BDB966C6DA75
              EB4B37C0FDB911CD9B9B366FD9B2759B431E1C90EA4DFB3C0C80A4804DC76EFB
              8E9D6860C7763B5D980276FD5DBBF76080DDBB0C38A00A380D8DF66201C6265C
              404900C2510199670DC6600000002574455874646174653A6372656174650032
              3032302D30312D30335430313A30313A33392B30303A3030DBF5A2D300000025
              74455874646174653A6D6F6469667900323032302D30312D30335430313A3031
              3A33392B30303A3030AAA81A6F0000004674455874736F66747761726500496D
              6167654D616769636B20362E372E382D3920323031392D30322D303120513136
              20687474703A2F2F7777772E696D6167656D616769636B2E6F7267417BE2C800
              000018744558745468756D623A3A446F63756D656E743A3A50616765730031A7
              FFBB2F00000018744558745468756D623A3A496D6167653A3A68656967687400
              353132C0D0505100000017744558745468756D623A3A496D6167653A3A576964
              7468003531321C7C03DC00000019744558745468756D623A3A4D696D65747970
              6500696D6167652F706E673FB2564E00000017744558745468756D623A3A4D54
              696D65003135373830313332393986E7550500000013744558745468756D623A
              3A53697A6500392E39384B42428F2A844800000048744558745468756D623A3A
              5552490066696C653A2F2F2E2F75706C6F6164732F32353431362F3379785458
              4A672F323130342F636865636B6C6973745F69636F6E5F3132393138352E706E
              6792F76AE90000000049454E44AE426082}
          end>
      end
      item
        Name = 'confirm_shipping_ecommerce_logistic_box_package_icon_142005'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C000001CB504C5445FFBF8E000000FFBE8EB5E08C00FF
              00FFBF8EFFBF8EFFBF8EFFC08FF9B484E89366E79165EA966AFCBA89FFBF8EFF
              BF8EFFBE8ED7D18DACE48CB5E08CB5E08CB5E08CB5E08CB5E08CB5E08CB5E08C
              B5E08CB5E08CB5E08CB5E08CB5E08CB5E08CB5E08CB5E08CFFBF8EFFBF8EFFBE
              8ED9D08DB5E08CFFC08EFFC08EB7DF8CB5E08CB5E08CB5E08CB5E08CB5E08CB5
              E08CB5E08CB5E08CB5E08CB5E08CB5E08CB5E08CB5E08CB5E08CB5E08CB4E08C
              B5E08CB5E08CB5E08CB5E08CB5E08CFFBF8EFFC08FF9B484E89366E79165EA96
              6AFCBA89E89266E79064E69064EE9F71EE9F72EA9669F0A174FEBD8CFEBC8CFB
              B888FEBE8DFDBB8BFCBE8EF9BD8EFFC08EFFBE8EFABD8EBBA191999292E5B48F
              FBC18EEDC78EE2CC8DE1CC8DFDBE8EC2A490758393697E94989292EDB78FFEBF
              8EE6CA8DC7D88DB9DE8CB5E08C8C8D926D7F94CEAA90FBBD8EDDCE8DB8DF8CB4
              E18C8E8E926A7E94DAAF8FB4E08CB5E08B929092708194DBAF8FC7D88CB4E08B
              CCEAAFD3ECBAB6E08EFEBE8EE3B38FF6BB8ECCEAB0F8FCF4E3F3D4B7E190CBE9
              AEDAEFC5B8E191B4E08AE6F5D9BCE397D2ECB9FBFDF9DFF1CDCFEBB4F7FCF3BC
              E396B6E08DD5EDBEFAFDF8FDFEFBE6F5D8D5EEBEE4F4D5B8E190FFFFFFE13223
              AB0000003F74524E53000000000072ACAAAAAAAAAAAAAA4669698C1601F9D372
              0FFBA215FE8602E63B7FA873AEAACEAA03044DF88E1AD1F250FCA60BCE2C85E8
              F32B043A80AB8F4F1B70AA9200000001624B47449876D1063E00000009704859
              7300009D7B00009D7B013C9F77C4000001474944415438CB6360656387000E4E
              2E6E6E6E1E5E28979D8D8F81110818D8EDA1C0C1D1C9D9D9D9C515C6B7E7C750
              E0E6EEEC815781A797B78F176E05F6BE7EBEFE018101B815A083510503A12028
              3804433A34548009A6202C3C22124D3A2A3A265650489819AC202E3E21312919
              593A25352D3D234344544C9C19A4202539332B3B07593E372F3F03042424A598
              C156141416213B2235AF182C5F52222D230B56505A568EA420AA02A2BFB2AABA
              464E1EA4A0B6AEA81EC980E874887C436353738602D89B21C81684C66494B4B4
              B6B537347674966428322829B3A10215D58C92AEEE9EDEBE8EFECA8C0C350675
              0D34C0A2A9953161E2A4C95340F219DAE0E04401CC3ABA191913A64EEB04C9EB
              E96351C02C66005431BD04E45243234C058CCCE292D21910606CC28C450123B3
              94A91948DADCD08219AB0246664B2B6B451B5B3B2360640100F07FD1E4582464
              480000002574455874646174653A63726561746500323032302D30342D323454
              31383A31363A32352B30313A303046C465730000002574455874646174653A6D
              6F6469667900323032302D30342D32345431383A31363A32352B30313A303037
              99DDCF0000004674455874736F66747761726500496D6167654D616769636B20
              362E372E382D3920323031392D30322D30312051313620687474703A2F2F7777
              772E696D6167656D616769636B2E6F7267417BE2C80000001874455874546875
              6D623A3A446F63756D656E743A3A50616765730031A7FFBB2F00000018744558
              745468756D623A3A496D6167653A3A68656967687400353132C0D05051000000
              17744558745468756D623A3A496D6167653A3A5769647468003531321C7C03DC
              00000019744558745468756D623A3A4D696D657479706500696D6167652F706E
              673FB2564E00000017744558745468756D623A3A4D54696D6500313538373734
              38353835BE89646600000013744558745468756D623A3A53697A6500392E3339
              4B42427D26FB8C0000006B744558745468756D623A3A5552490066696C653A2F
              2F2E2F75706C6F6164732F35362F3379536C476C5A2F323331332F636F6E6669
              726D5F7368697070696E675F65636F6D6D657263655F6C6F6769737469635F62
              6F785F7061636B6167655F69636F6E5F3134323030352E706E67C376274F0000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'google_admin_icon_131692'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C00000282504C5445000000202D40222D3E212B43222F
              40212C3F1F2E411F2C41212D3F202C41222D401F2D40202D3F202E421D2D4020
              2D3D1D2A441E2B3F1F2D41F14625F64624B03E2DAE3E2D202D40202D40202D40
              202D40202D40202D40202D40202D40202D40202D40202D40202D40202D40202E
              41202D40202D40202D40202D40202D40202D40202D40202D40202D40202D4020
              2D40202D40202D40202D40202D40202D40202D40202D40202D40202D40202D40
              202D40202D40202D40202D40202D40202D40202D40202D40202D40202D40202D
              40202D40202D40202D40202D40202D40202D40202D40202D40202D40202D4020
              2D40202D40202D40202D40202D40202D40202D40202D40202D40202C41202D40
              202D40202D40212D40202D40202D40202D40202D40202D40202D41202D40202D
              40202D40202D40202D40202D40202D40202D40202D40202D40202D40202D4020
              2D40202D40202D401D2D401D2D40202D40192C4149323B603538172C410D2B43
              4D323A6635370A2A4300274754333970363500264700008D5F34388139330000
              80753735BA3F2CC0402BBE402B9D3C30B23F2DBD402CC0402BC0402BBC3F2CAF
              3E2D202D401F2D40222D4038303D232D40242E3F272E3F7537358E3A32262E3F
              8739327A3834282E3F212D40723735C2402B993B308F3A31793834242D3F1E2D
              404B323AB63F2CC3402B983B30252E3FBB3F2C5333398539339A3B30913A318D
              3A322E2F3EA63D2EC1402B312F3E302F3EB53F2DAF3E2D37303D3B303CB33E2D
              C0402BA03C2F5B34385A34389F3C2FBA3F2C47323BBC402BBC402C8639338C3A
              32242D4050333ABF402B793734713735B93F2C783734603538BD402B1D2D4046
              323B5D343848323B5E3438B83F2CBE402BFFFFFFA70DDEFE0000009074524E53
              0000000000000000000000000000000000000000000000041D23221E5CD9DFDA
              5A01A1A3020CC3C60D1FE0E1211C330B53F5F6341B0FB0F1BA72278BE68C2873
              BCAF1065FAFEE2DB61D0CF8584E53651F7F9540974EFF0770A0357550447ED48
              EE5904780A31E3E432837FCDCE640EB86B8AE6E56C53F5F6531FE0E1210CC4C5
              0D01A1A2015DDADFDB5A041E23221E055D7FEFD900000001624B4744D57EBC3B
              13000000097048597300000EC400000EC401952B0E1B0000022F4944415438CB
              636040004671094929294969714606EC805146560E08E41570286054549A0006
              CA2AD85530AAAA4114A86BE050A0A90551A0AD83A68051574F9F918991D9C010
              A2C0C8808591954DD5D804AA8ED1D4CCDCC2D24AD2DA660214D8D84ADAD93B98
              3B3A8155B0333ABB4C98E0EAE6EE3A010E5CE5DD803C170F460E9001D29E30F1
              8928D484095E9A8C20CF79C3A4274D9E02A2274D9E0A53E2C3C9C8C068EC0B95
              9F367DC64C1063CAACD973A02A6CFC800AFC03209CB9F3E62F802858387FD162
              88586010504170482888BD64E9B2E52B568215CC58BE6AF512102B2C3C02E488
              C8283990016B96CF5FBB1268F4C429EBE62F5F0F32422E3A06EC4F46C6D8B809
              13376C9CBF69D9F4CD4B966C99B775D3A66DDB274E888BE5E2868694B4F68425
              3B766EDAB569D3EE3D7BF76DDAB46BD7FE034B26684BC3421CAE60D7AEF9070F
              CD0752A80A7878E313C056EC8203B01509F11C102744266A831C79783942C1F2
              234741B19A9804F244707218D49B9BE006EC3F06F166720A4A401D87AAD874FC
              047240A5A6C182FA24D48C53A761419D9E0154C097098FCB3367C1069C9C048B
              AC2C7E902374B3A1DC73E7F7834DB8700E2A90038A6E6040E64213CC928B1005
              97CEC1130CC49F798E61F905565285453005C5D652762516B02407B224439F91
              9151A0B40CA2A0BC4210C845245A78E2AEAC3A05923F5E5D83235FD4D65D0629
              B852DF804341631358C1D9E61621EC9953B8B5AD1D083A3A4570E46ED1AEEE9E
              DEDE9EBE7E31244100C26564201A7EDB0D0000002574455874646174653A6372
              6561746500323032302D30322D30345431313A34383A33302B30303A3030C101
              20E20000002574455874646174653A6D6F6469667900323032302D30322D3034
              5431313A34383A33302B30303A3030B05C985E0000004674455874736F667477
              61726500496D6167654D616769636B20362E372E382D3920323031392D30322D
              30312051313620687474703A2F2F7777772E696D6167656D616769636B2E6F72
              67417BE2C800000018744558745468756D623A3A446F63756D656E743A3A5061
              6765730031A7FFBB2F00000018744558745468756D623A3A496D6167653A3A68
              656967687400353132C0D0505100000017744558745468756D623A3A496D6167
              653A3A5769647468003531321C7C03DC00000019744558745468756D623A3A4D
              696D657479706500696D6167652F706E673FB2564E0000001774455874546875
              6D623A3A4D54696D6500313538303831363931300AF5A6DC0000001374455874
              5468756D623A3A53697A650031382E314B4242C6822FB1000000487445587454
              68756D623A3A5552490066696C653A2F2F2E2F75706C6F6164732F35362F5775
              53773759692F323133362F676F6F676C655F61646D696E5F69636F6E5F313331
              3639322E706E67E9FC64D60000000049454E44AE426082}
          end>
      end
      item
        Name = 'homeflat_106039'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C00000006624B474400FF00FF00FFA0BDA79300000009
              7048597300000F1E00000F1E01FAEC7D44000004904944415458C3ED965D6C94
              4518859F776677BB5D7E96A2D6A4A082810611AC2255440595043162B940228A
              F293EC16A2629480468B02210A8209090162D1845A6380588D02A16893264A48
              9460B81008061B0C5A53D4D0DA65BBDBDDFDE6F562B7FED45AB6FC042F38C977
              35DFBCE7CC9939332F5C66C8F94C8A4422F87C3E7F6B6BEB8DEDEDED38E74E1A
              6352F5F5F597564059591913264C4055871A63AADADADA669C3E7D1A11D91708
              04D6251289E3814080868686BC6BFAF2FD71FEFCF9343636A2AA771963D688C8
              6411415551D505A954AADCE7F3BD120E87F74E9932C553D51B9C73C30105C45A
              FBE3E1C3879BA64E9DCA8E1D3BFAE640341A45557DC698A74464A5885C0F78F1
              787C7F7373B33AE7260156445AADB51B83C1E086783CFEAAAA3E0764009FB576
              4F381C9E9D4EA753BB77EFCEDF81458B16E19C2BB2D62E039E0506007155B765
              B0CF5BDBEE75B8B82FB4C473BA58558B3299CCF24422711BD00FF0E73E547570
              3A9DB6CEB9FCB6A0B2B21200E7DC4D22B206980E58E0277199AA6FAF9B5677E0
              DA999399880E6BFB726DE9BE9587D24E5E57D5319EE755E4AC3F27CC7F599E4E
              A74544A61963768AC80CC0AAEA5736157FFCED3BB6EE3B503C730DCA87383EFA
              61E0A4F59FCF6BFCBABFA4675A6BEB72B6E7B5BDFF1210894450D5C24020F08C
              88D40063810CAADB0A32B1599B27D6A6D593EDC0E29CCD21E069126CDF3D677F
              D1D5DEEF0B7CD65689C82FDD4A8BAA8AEA3F8DB1DD576E8C2931C6AC159165C0
              20A04D9CB7BAB9A8F48DF7C7BE5581630B50D6C30A87E39876F496CAD6F6D1F7
              540F3DFAC94135768CAA96E4C60764329998DFEF3F525A5A9A3E71E244561564
              233662C4084E9D3A35DE18F326F0406ED2719B49BC583B6EFD37317B4D15303F
              B7E2DE90006A2960E58C6D77FA63B6FF72E7DC3CA040445222B2331008AC3A73
              E64CD3C89123B1914804C0178BC59E30C66C026E0740759FDF25239B26D4B814
              FD3603B3C89DE873C00F8CC7A3FCBB5BA387CA8F6DADE9147F8BC238551DA4AA
              65CEB949858585A742A1509344A3D101C698A522F202D9882571DEBBBF8586AC
              ABBB79C583385601257910F7846684D5C1C2D47BF7D73E3CBED373AB9D73F701
              88C8CFD6DAA831C63C2A222FE5C85B8C977A7ED7A8251BEA46AFA8C2B1F102C8
              0186A06C48760436D6CF69F8BEBF179B6DADDD24221DC05540B1CF39D7648C39
              2642C229AF5597BF9356353528F75E00F1DF510844E864D4AE270F5655EC7D64
              69472CD9A0AAA15028B457E6CE9D2BC160B0389C6C49ADBFFBD312600F30EC22
              9177C749A00238C2C26C88FE8A52B5024C06EA73AA2F0512C043C0175D02CC05
              95BB08C8FB390640C16FC067BA2E7A45356BA3022927F93D00E7254061D420C7
              CB633A290E2A8A904C26387B368E001EF0714B985DA7075E3A07A60FC9743E36
              2C53E01410889F4DD1E68F670B49D689CF7E1D40A7CBBFD1EA8B002DF4A9E729
              EA29824246C1D32E32C5D0F726B34F87309FFDEDEB19B8EC29B822E08A80EE02
              6264EFEB4B85448EE34F74BF078E025B8139643B9BEEA94A02417A8F7B4F4914
              200D7C90E3E841C042816AED045602D540410F55B47772ED6D3009B4009D5D2F
              E1FF027F006164DEA38D876D520000002574455874646174653A637265617465
              00323031382D30362D30355431313A34303A34302B30323A3030FABC22CA0000
              002574455874646174653A6D6F6469667900323031382D30362D30355431313A
              34303A34302B30323A30308BE19A760000004674455874736F66747761726500
              496D6167654D616769636B20362E372E382D3920323031362D30362D31362051
              313620687474703A2F2F7777772E696D6167656D616769636B2E6F7267E6BF34
              B600000018744558745468756D623A3A446F63756D656E743A3A506167657300
              31A7FFBB2F00000018744558745468756D623A3A496D6167653A3A6865696768
              7400353132C0D0505100000017744558745468756D623A3A496D6167653A3A57
              69647468003531321C7C03DC00000019744558745468756D623A3A4D696D6574
              79706500696D6167652F706E673FB2564E00000017744558745468756D623A3A
              4D54696D650031353238313931363430545965BB00000013744558745468756D
              623A3A53697A650031392E334B4242A7D7349F0000003F744558745468756D62
              3A3A5552490066696C653A2F2F2E2F75706C6F6164732F35362F5642774A6D76
              642F313532302F686F6D65666C61745F3130363033392E706E675C34A74C0000
              000049454E44AE426082}
          end>
      end
      item
        Name = 'list_1153'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000000473424954080808087C086488000000097048597300000EC400000E
              C401952B0E1B000002CF494441545885E596CF4BDB6018C7BF6FFBA624D231D4
              32D84E0AFB1B74C8AE9EBC79D4C304A1A752F4E8C18347110541BCAA4741140F
              42450A32B78346F058855DA487CDB65321FD91266FF2EEB0F5356F93B2065361
              EC0B0F79F225EDF3797FE47903FCEF22AD646363E3FDDB776F762855466AF51A
              658C41511411092501AA2848280A28FDEDD1781C20048EE380311BB6DD292CC4
              6271F4F5698C31E7E2C7F7D2A74C26F30D00680B6060F0F5F687D1B1B1818141
              104282609F2DCE39BDBFBF1FFBF2F5F336808F1280CD9CD164F2159ACD664F8A
              B7944C26E138CE68EB3ED64A7E56CA9473DED3E200C03947B95C12031749B556
              83EBBA3D070000C3A88A5CCC80E338D243ABABAB181E1E46B95C8E1CC05B8B7A
              4DEF12CCCDCD41D7750090FCF1F1F150C54E4E4EFC006E0080DB064008114BE2
              F5CFCECE4201341A0D3F00EB620696979771757585D9D9591C1C1C08BF5EAF87
              0208927709C41E607F005AB1B8B888DBDB5BE47239C98F2282F70093DF805EF6
              830E9B90A1BD0F542A15F4F7F7231E8FBF04802BF581959515DCDDDDA1582C62
              7777F72500E43EB0B0B08042A180A5A525C99F98980855ECE8E82800E069A01D
              DF82CBCB4BACAFAF63737353F24F4F4F430154AB559FD75523CA66B3A094627A
              7A1A878787C2370C23144090BA02D0755D1CCB51140D0D10755109A09B4ED84B
              059E05ED005B5B5BD0751DAAAA626D6D2D5A80E04E28034C4D4D61686808C7C7
              C7923F393919AAD8FEFEBE1FA09B2528954A48A55228168B929FCFE743013C3E
              3EFA013A7542AF72B91C745D472A95FAEB1F86555767413A9DC6FCFC3C9ACD26
              4CD37C76511920A013121293006CDB8E64B4418AC5C457C01380A6A9CC755D1A
              F88B88A5F5694CC03CD9E4FCFAFA3AF28F8FF6B8B9B9010139F7CD806118337B
              7B7B3BAAAA8E58964539E7D0344D84AAAABE6B2291002104B66DC3344D98A689
              46A321AEDE9C730E4551986559170F0F0F332F31D3FF867E0155A450E9E0C862
              080000000049454E44AE426082}
          end>
      end
      item
        Name = 'LOG_29710'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000000473424954080808087C086488000000097048597300000EC400000E
              C401952B0E1B000003BC494441545885C5975D6C935518C77FCFFBD1BEEDBA6E
              76C05C37D9948A306083962931310B214B3023646AA6A0682426AE2160C40B67
              FC08189504F5C630858889E20D22A844E385D345EE1C06C322094C304625CB08
              30C99695766DD7E3C5C6D68F7594AD2BFF9B37EF39CFFB3CBFF39C739E735E21
              8BDE2B6A5AE0D0ED0794A86611B165B39B4EB1443C717EE8CA8BFBF96D5F361B
              2D5B8765D83E43E39199060750A02534F5419BB6EAB55B06005933D3C0295E10
              11B4B783E2DF7B6B004A493E002649E4E5A0F8F7A7C79C26037320916050FC87
              1AC1280880213A1A698914D9B254024777E0B3CF3980264295A3341D01849698
              B8BFDB425D9131D587F994DBB458A4CDE34A344454C593BB9A5C589D730E0060
              E92655560931128C309ADCF560C116A18860139D224CF4A44929EC2E606C5D38
              C4C01AC728C814A44B104CD1319456F80CA48088DC5E00B80D6B205D462BE81E
              FC4F8B50A798ACFFFD23830E917C1D0782CBB0536CD833013CE2EF1091E098D9
              64C0FF62E13C051FD3403444B9E5A6CC74A2250D4C6F908A6388A4EC86406B13
              4397AE120B8FA438A95E5DCBCA96B5786BEF61B0FF2AD1D02464F97DD5F81F5B
              474D432D91A1EB84060633204655029B698E05BE71502362A51B3EF3E92E96AC
              7B20A56DC3EE203BBB0EB030B0848627D7F366EFD7D4DCBF0C80B53B36D1DEFD
              39DEE53E16FA97F27ACF61EA363666002814005146091123AE1253D70111016D
              324D25DEF93CFCEA560E3EDE4ECFF113003C7FF45D5ADED9CEC74FB4F3E8DE17
              38B47537A78E7402D077E64F4A2AE64DE53A0906C2C473DB05952B7C68BACEB9
              1F4F4EB49DFDE1172AEBEFA572B90FC36EA3B7EB5744D368D8BC9EF0E0307D67
              2EE4E23AB74A18190A01E0F4B819199F77A7C7CDC87098F0789FA3B498C8F075
              AAEA175355BF98E2F977B067F55337F59D350365D51513CE2E5FF897817FFA69
              D9B31D47890BEFB245346E6BE5F4575DF4FD7E9EFEB37FB161571B22C2B76F7C
              C4C5D3BD13F37D3349500B6458BE74E2209EBBCA27DE7FEE38C2B9CE6E367FF8
              0A77AF5941341CE1D4179D7CB9F37DE2912865355E3675B4E37B6815025CECF9
              83EFDFFA84DE9F4EA6F8B5EB06773A4B5201DA241015C1CC097796B2749372A7
              3BA54D53A86385080EE034327F318C6BEAF2731EB5A05744AD54497BCF65D89A
              13A2F2921941B074139799598AB316FB7DEEE66BA3A24A23C4735C4E33D3B475
              C0108D224CCC393C34B37B1651630FC112032746E61D7F96524AA96986A6BA93
              DF74D170626047CF27C2DF590122F1E8B324F8462915BDD1967CB33566990DA5
              D42550DBFE07222101320DD03DD00000000049454E44AE426082}
          end>
      end
      item
        Name = 'notepad'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000000473424954080808087C086488000000097048597300000EC400000E
              C401952B0E1B000003C8494441545885BD964B4C5C551CC67FE7D241E8BC4AE9
              800E2D584D28895BF1312A315512C5685AA2C6B4E2A3AE5ABB6A5CBA90A5D556
              831016C62E2436A961C14257A08BDBC4D634A9A6412D26C55011280373E77167
              06B88FE3A2BD309DB9C30CD3A1DF6AEEFFE4FFFFBE7BBEEF9E398222383B32F2
              D00342B9280562CDB69F3DD5D7370F30F4DDF96F91F2B094E283937D47BE0718
              1C39FFA610F21B096327DF3EDAB7597F3E9462023C528920C4A302F188475122
              394B4711C287227B37A6C85E84F009218E94D17F1776B81555550DCDC4E29DC9
              B40E40832F1099502F0B80A97FA71580DA1A4FEB847AF97580E9B99BAD866502
              284E6D418B3E9DD05300ECF2FA3B555555BBBABAA2F95C22BFF0B3FAEB0B36D6
              582A9BF1CD2D2D02106E0C11F0FA00B87EF31F00FCF53B69093503F0DFD222A9
              4C1A808ED6FD0024336972FBFD5EAF2EE170F77391895CBE020B6CEC412184AF
              C88E550C81F00929BECAAFBB58200F80C0362D129A06C083BB76AFAFEA890496
              6D532B36B4AF66B324340D45D9A8B9F7CB03250508210440D0EFA769F71E6EFF
              0EACAF3FDCB28F654D237C67FB01C2A1668C3583C68686F59A5BBF33FB2EBEFC
              C24F172FC9FC5A3520A524BD9265F6D6C28742D6A827DE796B1236F90CAB4D3E
              B71C65367A0B14316462FCFEC9D92FDFBD6F0202413FE9952C00B66D138FC56A
              6CD33C0DDB6D81B46899FD91C683C75948AEA25EB9C272348A659A48292DA1A7
              EAB66F07A445CBE43081EB1730478FB367E70E5A9B9AB12DCB79C11FFAFBFB4D
              D7933017CEC1B3150869F3F8FC2881D43500ACB94962675EC3DBF3198FB577F0
              E7DF5357B3C6CAFB508605CE715C3639366D7F7D4DB37615B87D1E2467E6B156
              D73042EDC40F7DF1DB9ABFE1C59722911814F92FC8857304970569119E1C26E8
              42EEC03BFC4AF7C13162CE73F532E0902F5C72253742EDC47B0778728CE5DCB6
              AA64C0F13C78C7F362E4B22E58D05B5240B831B439B9E37905E46509D8340325
              3C2F450EF79281323DDF8C1C2ACC801082CECC2F45C9F5601BD79EF808733146
              47EB3D0A70CB40DBBEBDEC6B7C0673F406D6DC1F056FBEDC739A268FB7D4E8F2
              04B865A0D6538BA80BC2A12162675E45ACCEAC93C77B07A8AF0B525F167D8519
              183C7781A91B334CCF6B2CF57C8E116A2FDBF37C549481F9C528A73EFE9413EF
              BDC1DE7033F1DE01802D939725C02D032F3FFF14997496CCCA4AC5C4650B70CB
              40607FF52ECDF7E546B4250196656D1B996517CE2E10A0E92963BB0468A9C2D9
              0519588A6BE36BA6D1E3ADABC7E51A5F119C2B7952D7C74B0A30148E2575FD5C
              22AD770BF05445001842325EAB702C7FED7F9859F6ED2DC3C3E1000000004945
              4E44AE426082}
          end>
      end
      item
        Name = 'signposts3x_99162'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C0000013E504C5445000000E2BC00E2BD00E05951F355
              3C5E6DC57569B0E3BD00E2BC00E2BC00E2BC00E2BC00E2BC00E2BD00E2BD00E0
              5951E05951E05951E05356E1872BE2AF0BE05951E05951E05951E05951E05951
              E05951E05951E05B50E06448E05951E05951E05951E05951E05951E05951E059
              51E05951E05951E05951E05951E05951E05951E05951E05951E5584CE8584AE7
              584AE8514FE58926E3B009E7584AE95849F3553C5D6DC56C6AB86E6AB76E6AB7
              6665C3A6925ED4B2166D6AB7706AB57569B07569B07569B07569B07569B07569
              B07569B07569B0776AAD81729D7569B07569B07569B07569B07569B07569B075
              69B07569B07569B07569B07569B07569B07569B07569B07569B07569B07569B0
              6E64BBA8905ED4B117E3BD00E3BD00E2BC00E2BC00E2BC00E2BC00E2BC00E2BC
              00E05951E058527569B07468B1FFFFFF1DB28ECC0000006574524E5300000000
              00000000131012B5B21EE3131F1E1D39E6160106A1E4E1E0E4FCE2D04E09C0E8
              6304F36C6AE65DCE4A1D1C1C1B37E61D150101151D1C1B37E61C1D1F12014FD0
              E2E1E0E4FCE4A1060466E8C00972F36C60E74BCE161E1D39E61EE31EE318C502
              1970CBDBF700000001624B474469BC6BC4B40000000970485973000021370000
              21370133589F7A0000010A4944415438CB6360A02E6064E4E06464C4A7808B9B
              870B9F02265E3E3E5E262C12CCCCFC02824020242C22222C242828202AC68CAA
              405C42520A08A465646565A4A5A4E4E4155055302B2AA542405A1A8456565165
              C6AA000ED4D49999F12BD0C0AE006685A616AA15E88ED4D6417324D09BBA7AFA
              FA068646468606FAFAC626A62C6821C16A666E616969656D63636D6569696B67
              EFC0C6862CCFE6E8E4ECE2EAEAE6EEE1E1EEE60A049E5EDEC80AD87C7CFDD2C1
              20230342A7FB07202960630B0C4A4703680A82F12B005A11128ACF0A9023C3C2
              F13912A422C23E32322A3A26263A2A1208D0BD0905ECB17171B1ECF8925C7C42
              423CE3905790989494885741724A4A323E05E40000745F64A4119DCB83000000
              2574455874646174653A63726561746500323031382D30342D31345431383A31
              373A33352B30323A3030EB25E5840000002574455874646174653A6D6F646966
              7900323031382D30342D31345431383A31373A33352B30323A30309A785D3800
              00004674455874736F66747761726500496D6167654D616769636B20362E372E
              382D3920323031362D30362D31362051313620687474703A2F2F7777772E696D
              6167656D616769636B2E6F7267E6BF34B600000018744558745468756D623A3A
              446F63756D656E743A3A50616765730031A7FFBB2F0000001874455874546875
              6D623A3A496D6167653A3A68656967687400333834FCFC329F00000017744558
              745468756D623A3A496D6167653A3A5769647468003338342050611200000019
              744558745468756D623A3A4D696D657479706500696D6167652F706E673FB256
              4E00000017744558745468756D623A3A4D54696D650031353233373232363535
              8C13896D00000013744558745468756D623A3A53697A6500322E34364B424295
              62633000000041744558745468756D623A3A5552490066696C653A2F2F2E2F75
              706C6F6164732F35362F346249386F32382F313434392F7369676E706F737473
              33785F39393136322E706E67FC964EA20000000049454E44AE426082}
          end>
      end
      item
        Name = 
          '3592821-garbage-can-general-office-recycle-bin-rubbish-bin-trash' +
          '-bin-trash'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C00000117504C5445000000647F94647E946EC3A86EC4
              A7647F94647F94647F94647F94647F94647F94647F94647F94647F94647E9464
              7E94647E946EC3A86EC3A86EC3A86EC3A86EC7A870D2AC70D3AC6EC3A86EC4A7
              6EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4
              A76EC4A76EC4A7647F94647F94647F94647F94647F94647F94647F94647F9464
              7F94647F94647F94647F94647F93647F946EC4A7658095688297678297668196
              6883987892A78BA5B96F8A9F637E93859FB3839CB1728DA18CA5BA738DA2819B
              AF97B0C47893A76A859A90A9BD6A84997A95A996AFC37B95A96A85998FA9BD7A
              94A997B0C37B95AA728CA189A2B686A0B4678296748EA37590A46B859A698499
              6983986B869BFFFFFFA9C58A150000003474524E5300000000002AA5ABAA3FF6
              3DEDF50F3A3C010F15141311110C079ED5D27B09C096044F6A696B3E3E979691
              2569DC5ADBDACE5901F582014200000001624B47445CEAD80097000000097048
              59730000531100005311010DF18749000000F44944415438CB63604000465636
              760E0E7636564606EC809193CB0408B838712AE0E6E1E2E5E5E2E1C6A580898F
              5F0008F8F99850C59905858445C040544C1C08C444213C610966880216492969
              192C405A9605AA404EDE142B50205A81A292B20A16A0AAC6C2402C6054D7D0C4
              005ADA88E060D431C104C8014A9C02337390B0852588B432C3A2C0DAC6D6CEC4
              C2DEC1D2C4CED1C9D90E53818BAB9B9D89BB8787A7899D97B70F3605DED67626
              BE1E7EBE2676FE7815788E2AA0544100242E7C417111884581BF47909D897970
              48A8895D98473816059611C044601219054A1AD19644A4285DE434A9A76F8006
              F40D8D8CC10A00B83F7D21083D45120000002574455874646174653A63726561
              746500323031382D30392D32365431373A34363A35332B30323A3030146E25A8
              0000002574455874646174653A6D6F6469667900323031382D30392D32365431
              373A34363A35332B30323A303065339D140000004674455874736F6674776172
              6500496D6167654D616769636B20362E372E382D3920323031362D30362D3136
              2051313620687474703A2F2F7777772E696D6167656D616769636B2E6F7267E6
              BF34B600000018744558745468756D623A3A446F63756D656E743A3A50616765
              730031A7FFBB2F00000018744558745468756D623A3A496D6167653A3A686569
              67687400353132C0D0505100000017744558745468756D623A3A496D6167653A
              3A5769647468003531321C7C03DC00000019744558745468756D623A3A4D696D
              657479706500696D6167652F706E673FB2564E00000017744558745468756D62
              3A3A4D54696D6500313533373937363831334EEF998C00000013744558745468
              756D623A3A53697A6500352E30314B42423892C3C70000008574455874546875
              6D623A3A5552490066696C653A2F2F2E2F75706C6F6164732F35362F57666E59
              6667322F313537322F333539323832312D676172626167652D63616E2D67656E
              6572616C2D6F66666963652D72656379636C652D62696E2D727562626973682D
              62696E2D74726173682D62696E2D74726173682D63616E5F3130373736302E70
              6E6702B1E2820000000049454E44AE426082}
          end>
      end
      item
        Name = '3592815-compose-create-edit-edit-file-office-pencil'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C000001A4504C544500000095AEC2647F94647E946480
              95647E936EC4A76AA79F6EC4A86AA9A06AA99F6EC3A671DEAF6CC2AB6DC3A86E
              C4A695AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC2
              95AEC295AEC295AEC295AEC295AEC295AEC2647F944F6B8195AEC295AEC295AE
              C2647F94647F94647F945C798D97B0C495AEC295AEC2647F94647F94647F9464
              7F945C788C95AEC295AEC295AEC25D778D97AFC395AEC2647F945D788D95AEC2
              95AEC297AFC395AEC295AEC2647F94647F94647E94647F94647F94647E94647F
              94647F94647F94647F94647F94647F94647F946EC4A76EC4A76EC4A76EC4A76E
              C4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A7647F94647F94
              6EC4A76EC4A76EC4A76EC4A7647F94647F946EC4A76EC4A76EC4A76EC4A76EC4
              A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76E
              C4A76EC4A76EC4A76EC4A695AEC2647F94658095637E936B869B849EB27B95A9
              89A2B697B0C4859FB396AFC38BA5B96D889C637F946A859988A2B6738DA294AD
              C18BA4B9668196748EA36C869B637E946EC4A7FFFFFF16F22433000000737452
              4E53000000000000000000000000000000000660AAAD6B0C0572F2F88E0D45ED
              FB9103021197FC047075060E968F72F3F67A06F769C0060EBF7B068A0B11500F
              FC8705FB8C0C73057419CB43DA313288D33409B8CF28E65DFD94D68E12C6D133
              2A103EEDFCE8BE863581FBE9C28A592A0A646F0F011DEA821100000001624B47
              448BF26F47E000000009704859730000531100005311010DF187490000013749
              44415438CBBDD05553033110C0F1BD0302C58A15285AA4489116290EC5A1B8BB
              4B71BD724071877C6A2E390A33DCE68117F62933BF7FB23301C0468A8B4F484C
              B24820182939255551AC69E9A242CAC854B4C9CAC60BD996939B97AF17D816D9
              5E505854ECD08B120BE2A565E54ED757515189B9DFFF5354A1CE8A6A372F6A70
              D78A5A5EFC5A11F4335ED4B91DD6FA06C4D5F38B4B5EB81A9B9A25CC0357D7FC
              0DA75D46EF076E6EEFD8A2164F6B88C855EDD4D6DEF137EFFC0FBF177A5737FF
              BF8747DC41EEE965AE3E3DBFA00EA161DE3E56BCBEBD7F604EFA07C2F5825D37
              7A04191C1A36E905E6404646E9D877617420E313542B2279813890C9291A2C30
              87A8694A7961F2CECC220E73F33CA00B8BD14BCBB2D1616555D3B5F58D4D1F01
              74B6B67776F7F60F0E63627187A363DFC9A91984F30951FCA836A521E4DE0000
              002574455874646174653A63726561746500323031382D30392D32365431373A
              34363A31322B30323A3030365320E60000002574455874646174653A6D6F6469
              667900323031382D30392D32365431373A34363A31322B30323A3030470E985A
              0000004674455874736F66747761726500496D6167654D616769636B20362E37
              2E382D3920323031362D30362D31362051313620687474703A2F2F7777772E69
              6D6167656D616769636B2E6F7267E6BF34B600000018744558745468756D623A
              3A446F63756D656E743A3A50616765730031A7FFBB2F00000018744558745468
              756D623A3A496D6167653A3A68656967687400353132C0D05051000000177445
              58745468756D623A3A496D6167653A3A5769647468003531321C7C03DC000000
              19744558745468756D623A3A4D696D657479706500696D6167652F706E673FB2
              564E00000017744558745468756D623A3A4D54696D6500313533373937363737
              3264EE49A100000013744558745468756D623A3A53697A650031302E384B4242
              57D9E25600000072744558745468756D623A3A5552490066696C653A2F2F2E2F
              75706C6F6164732F35362F57666E596667322F313537322F333539323831352D
              636F6D706F73652D6372656174652D656469742D656469742D66696C652D6F66
              666963652D70656E63696C2D77726974696E675F3130373733342E706E67565F
              7EF90000000049454E44AE426082}
          end>
      end
      item
        Name = 'Logout_37127'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000000473424954080808087C086488000000097048597300000EC400000E
              C401952B0E1B00000427494441545885C5975D681C5514C77F777676374D368D
              F96AA5684B21585AC42268DA5262A4546B890F8A4D41100441A40FBE14041151
              2A08BEF8A20FF6B120E2834F42151F94D6DA12BBD62F101A859AB6B64DFA5D37
              893BB333F71C1F2693647767B33305F1C03077CEFDF8FFEFFF9E73EF1DF89FCD
              A46DF8D12BF76E519CF751362DEFD751308C3C50309D0572154F99AD0A95AA32
              5B55663D75E77D45EB011D0505BECBA107DC34E0E3E3E4549DA3C0C6D8A70BA3
              6E59E7D2DFED00CAAAA261CDEAA81CD52B5660DE57E63C5D7CDFA92AD72BBA2F
              54241581919EB5EB5523F09CDBC7D0F617C8AFEA414418AC7D01767219A92570
              00C7407707948A6641B8A8FEE24DA1FCA77D34150175C45175400D4FBD7A847B
              D60D1104014110E0FEF2333A3319B76C20D1AAACDCDF67F8631AE3A4218017CD
              AEA37B80C10D9B5BD15C015C516DAE2FE6211D014055314E73F346D993C11B7D
              D1780AA45A82184835B12623F8329F6A16020A3433D0B6802BD7A72750D7B99E
              C1DDC81F79245D0CF8C44BD082C15D8047CCDB04E18DB1B1E199B1B1F7E28E89
              210019D65EEB7C2A9A4C40C199D9BBF78D40F524AADBC05F90BA550CA4016FF4
              819010039777EF5E7FC5753F36F018AA88EAC093B71E7C62B2EB1A1DB31D04E5
              32D65A240CD1CE4E8CD234B358B1D6BE85B26AFD617469CF9EFD46F5B01AD39B
              A44C93158BE45EEEC799FE0650A6AE5BF28EB2AE37D71E1CF8763238EF025C1D
              1D2DD5F2F90F55E44505D322E19B2D0C17D350044E9FB3E4B4C673DBBA52A9A1
              0AEEC55DBB863D633E01865203C726422E4E43A3ACE986A2EBA6028FDFEE9CC8
              9B1D8E33E464058F46581C1C85C737E713F7FC96690838BF1D3FFEEC5C18BE5D
              13094584AC4F5AA997A761EC53559CFD601F3A71E29D4A108C54AD3D9789C0E2
              DED09CE3EDE48F3558DC071E3975EAFBDBD63E5CB1F648A8AA114BC5AAE28B24
              3F85C2B2AD382378521AC6767AC78EF14E630E178CE953289F593D7D70BAAB72
              B2D4B396E7DFFA92300808C210EB3898B3EF62AE7C9D9866EDD2F0D8D9E07CE2
              4EB86D62E2B3F930DC3A2F724C446A53AB6FCC784E809FB7E4070670070670FB
              FB714AA5E82448187C69ED1B7D4B65D1165B31C0F672F9D2E71313BB6F07C1C1
              682E2DEE0375F22F0D9E44A849216973181D02D979E6CC0FF87E1DFB2416C96B
              BF02380D41B89279AC741A660CBCE53D55B25DC9BCF9BF111B34F94D1BC0D6CA
              65BC94FAD5398E7D7A289144567055F0C21669D868AF3FD3DDEF1ABDE6988870
              BED845615537A0ECDCE8B3A137CC0C7EF9B6F0D5AFFE4FB9C4160D7672B256DD
              B9A930680CC300360CA87973D4BC79064BBAF03BD60C6E0542815A0877FE51AE
              5694BF6E09BF4F0B3F4E057ECD9A03A97F4E015E7BBA346A0C43F1B760EC7DBD
              79B3676BFE2563D8A0CA052B72DE8A33550BB9307327F42EDCB45CBA2158218C
              FB1935D6337EF983A3DEC52CF8FF89FD0B272DDFA34012B52C0000000049454E
              44AE426082}
          end>
      end
      item
        Name = 'refresh_arrow_1546'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D4948445200000020000000200806000000737A7A
              F40000000473424954080808087C086488000000097048597300000EC400000E
              C401952B0E1B000005BC494441545885C5967B4C145714C6BF73EFCCCE2E0B2E
              20B2888A4A10157C5BD4E0ABD56AFFB19A4631356D535BE2235A93D6D8863431
              1A639326D66AA289468DADD46A7DE02362AAD16A1445502AA2698B515090F763
              61615FCCB37FEC5A8D59D895D0F624377B3333E77CBF3BB3E77E97A38F23F9BD
              DC7829EE8D0857F5154F38CFB3BE06481F3D72CBC4CCD9470148FF0700970DE9
              5D5D8C9B3B7DF9D115E1D4EF5380514BF332209813DD3E033143D2B72666AC4F
              099543BD11B28FDB668D1D3178923D21365910C56855D35557A7A7C51A6D9B0F
              29E153C3003827486AE3C50BDB662E02D0D52700B3B2CFCF1B34C4FE994735CD
              872099BD0AA068003182203280009F4F07114044889080D6CA9255C58796ED07
              60F41A206DC1A1A47193D3F6F98CC8779A9C3A1010001188117403D00CC03000
              830225198188D04FF03AEE5F3A98D154B2B3B257006FADC8CF8C1F9474A6A68D
              0FD00110018A0AC89A01450374C3FF0618F7C3B0C0A0C0103943845C7FEEEA8E
              194B00C8AFD6E73D89CFCC3E35A5FFC0E1176BDA58ACA6036E9F0EA75B874FD1
              A119040484B9C0C03903131838E7FE39F75F23CE2045468D8C1B3CADB2EE7E5E
              59D800C3E7ECB78F481B73B5AA95C575B835F8BA5408865731A98E3FB8D25AC4
              15C75DA6BA2A99A1CA5C34C57293C85900840BFEC102BF1A71C4C4C54D7777B0
              63AEFA62E7CB3A427700E333D2773FAC47A2A2C8B050DB135F6BF9C127253FE5
              B91A8AEB00F8F0E24F250E9A9133263173791198098C073E032730C6408C0043
              43BBD3D5A0723D0640754880A91F9C7EB3DE695E2CE82EA7D67A777BE9F99C03
              80A7058012E4713976D4BC642E998140FB314E609C415715DDDD545BD0F2D78D
              BD5597722E01687F353928C080047B4E634BC3DDAAC27D6B1C8FCE94A1873E06
              008B2D663E0181D74ED0BABAE4CEBAA7F94DF7F2F7D415EDBC03A013801E2C37
              1800D53E7B5C5C7AEEEB7DF0D6D47797F8F2F3DC6499CB0506D5E7EAF454551C
              AB2BC9DDDBF2E04439000FBAE9FF5011F6169D9C753C69EA86D2E6B465BF6C8B
              4ACC1C09C0825EEEB0BD0D06D8A211A6FBF5590C9DBDC90CCCEEB68BC28DD72E
              90BAE0E7B8A43123D65A6362D79AFA0D5CFDE8DCB553FF09406AD6F1E1A9A9C9
              EB79A4ED134856ABAE7895EAD21FEF87959C95C5174DDCB2B5ECD2C9BD4FAF6E
              AC7A2D80B14BF3260D4D1DB68147D8962864123546E006A07BDBCABA6A8A9A42
              E58FC9BE6CCFC84CCB159996F2F4EAC6EF5EBDDF1D004DFEF0ECDB89494336C0
              1C39CFAB0B0495818B00238228125A9BEB0B0078BB97CEE20BB76EFE7848DAE0
              6FCD36EB80DB274F7F09A02324C0D0D93F448F9D9A7E992CB6C91D3203C90426
              10380180DF62234C843FEB1B6A9FC3E245AFD3F0F78FC4A78F9BB0D83E2C7E5D
              3F7BCC28050CCD159565057B96E722C84E1AAC5F85CCD505D778BFF84CFAC7E1
              5E180B17184C12872402B2D7D768185AB94170807349344BC3ACD11123236322
              B94EE4077675B8F2BFDFBCB0EAFA8E6B08B2A905FB046A43C5EFAB12D3E7DC26
              8BC5F21CD35FCF3FD10CC0AB719025CACE046617440E2E7208260E9838BA34FF
              5980CB5EB9F8F4B1CFABAEEF280C260E7463C76D95179AA35316E8165BEC5CC6
              39883130C66004C4159DFCD518F9EF710626327081431018B84080BBD3557AEA
              E8BA92432B8FC0EF9E41A3872D33459AB2F67081B57F7C860E820AFF014408AC
              5410394453606EF2CF4589C32202CEEAEA3B05C7F67E557B6DFB2D8430B21EDA
              F07197A3E2EE2A5D9C550893D9CC450E813118BA0ED2098C38180102015C53A1
              385D1E4F7B736169C98DC30F4EACC907D086D04616D23468F447BF6EB2268CD8
              C403AB7637565C697B7873B72536B1BF204A66C5E7717B1D35CFAA6F1F2887B7
              B60DFED60C291C2E0030789A65C2A25D855274DC04416068BC77F18BC76757EE
              7A45A457960B8463BB35455E67D58395BA2CCBAACFAB34DC3B7E118016107D3E
              FEF5A071D9BF7D337EF5F54200517D59B8C763F9CBD1D8E0281294F65B9DCF6E
              D6A20F57FD37EDDB1919700A3B980000000049454E44AE426082}
          end>
      end
      item
        Name = '3592814-document-general-letter-note-office-page'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C0000012F504C54450000006EC4A76FC4A66DC4A7647F
              9469A09D637F94668F99648195647E946480946EC4A76EC4A76EC4A76EC4A76E
              C4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A7
              647F94647F94647F94647F94647F94647F94637F94647F946EC4A76EC4A76EC4
              A7647F94637F9470D1AA70D1AA70D1AA647F94647F94647E94647D94647F9464
              7F94647F94647F94647F94637F94647F94647F94647F94647F94647F94647F94
              6EC4A7647F94637E936B869B7792A67892A76C879C819BB097B0C496AFC3859F
              B3658095728DA2819BAF758FA46C879B6D889D869FB4718CA1819AAF748EA36D
              879C7791A66984996681967893A7738DA26A859A7691A56F899E93ACC097AFC3
              90A9BD7C96AB708A9F809AAE7E98AD6882977C96AA7993A77F99AD637E94FFFF
              FFE696E4220000003A74524E530000000000000000000000076CCBC90666F3F2
              615899969DE6E53E6B696A2B4A02967DD7D4B3060B1312A4393535AAFDF3F0B0
              058788EAE6E4264190D10600000001624B474464C2DAB8090000000970485973
              0000531100005311010DF187490000010A4944415438CB636040028CDC3CBC7C
              3CFC8C0C3800239380A0959590303356158C22A262E212564020292E262A82A9
              8651CC0A098891A480454A5A46568E155501AB9CAC8CACBC021B5881A2B5B5B5
              0CBB92B20A1C282BB1CB000555D5901470A86B68C281863A872C9A022D6D1D5D
              24A0A3AD87A640DFC0100518E8A329C00A9015D860005405B676F6E8C0014581
              A393331A7072714556E0E68E013C487424C5BEF0C4F084BD17215F78A3F8C2C7
              17C3177EB4F0052A89AAC01FE8EC80C0200FFBE010D7503B101B4D01D81761E1
              11CE9151B6D1204F04A085434CACBB7B9C6D7C82BB7B62907F12888DDD91C940
              0790EB0BACC0C8988002134E2EB0025333736CC0C2C89285810100AE34AAFE00
              DDA5F60000002574455874646174653A63726561746500323031382D30392D32
              365431373A34373A31372B30323A30308BA9647F000000257445587464617465
              3A6D6F6469667900323031382D30392D32365431373A34373A31372B30323A30
              30FAF4DCC30000004674455874736F66747761726500496D6167654D61676963
              6B20362E372E382D3920323031362D30362D31362051313620687474703A2F2F
              7777772E696D6167656D616769636B2E6F7267E6BF34B6000000187445587454
              68756D623A3A446F63756D656E743A3A50616765730031A7FFBB2F0000001874
              4558745468756D623A3A496D6167653A3A68656967687400353132C0D0505100
              000017744558745468756D623A3A496D6167653A3A5769647468003531321C7C
              03DC00000019744558745468756D623A3A4D696D657479706500696D6167652F
              706E673FB2564E00000017744558745468756D623A3A4D54696D650031353337
              3937363833377BB43F1700000013744558745468756D623A3A53697A6500382E
              32394B4242E631D9880000006D744558745468756D623A3A5552490066696C65
              3A2F2F2E2F75706C6F6164732F35362F57666E596667322F313537322F333539
              323831342D646F63756D656E742D67656E6572616C2D6C65747465722D6E6F74
              652D6F66666963652D706167652D70617065725F3130373737362E706E67A1E2
              102C0000000049454E44AE426082}
          end>
      end
      item
        Name = '3592828-general-key-key-lock-lock-office-password'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C00000231504C5445000000647F9456769F6480946681
              8F657E94647E9567819668839865809595AEC27F99AD869FB496AEC289AEB294
              AEC295B0C196ACBD95AEC196AFC496ADC294AFC2647F94647F94647F94647F94
              647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F
              94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F9464
              7F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94
              647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F
              94647F94647F94648193647F94647F94647F94647F94647F94647F94647F9464
              7F94647F9495AEC295AEC295AEC295AEC295AEC295AEC295AEC29BB4C8627D92
              6D889D97B0C495AEC295AEC295AEC295AEC295AEC295AEC295AEC292ABBF6882
              978DA7BB95AEC295AEC288A2B6668196748EA38AA4B891AABE89A3B795AEC295
              AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC2
              95AEC295AEC295AEC295AEC295AEC295AEC294AEC295AEC295AEC295AEC295AE
              C295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295
              AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC2
              95AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AE
              C295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC295AEC264
              7F94637E93658095758FA495AEC26F8A9E7A94A993ACC096AEC296AFC38FA9BD
              FFFFFFD1EF25F5000000AF74524E530000000000000000000000000000000000
              00000000000D539ECADBDAC19140063FB3F4EB9C2959E5F9F2F3FBCF36DC814B
              383A54962109B1BB2D0346D68437EEE03055F5D116630110F1697B07BAF678B8
              07203C3F40381A04079069B3E0F4F6F2D8A55EC3F4FBF9F869F680FA5427D9B6
              0E7FFDFEF74ED56478EB86197603AC041EE16996C009BB0811CC6E9E9D02A1C6
              455BE37054F5F8E22B0BAA7B2CCD13981473D2FAC15A0A0161DAD7B78B52CBB2
              F28800000001624B4744BAA3B147DA0000000970485973000053110000531101
              0DF187490000018D4944415438CB63608003463171094929691959397946064C
              C0C8A8A0A8B41E0C9455541931943032A9A903E53434B5B481948E2E2333BA02
              39A0BC9EBE81A191B189F2FAF592A66846309A99AF5F6F61C9021466B4B2B659
              BFDE96155505A39DFD7A074788181BA393F37A175734056EEBD7ABB843ED65F4
              905CEF6987A6C06BFD7A6F9810A38FEF7A3F054C05FE080501642A600F0C0A0E
              090D0B8F88C4AA604354744C6C5C7C7C42625272CA064C051B37A5A66D8682F4
              8C2DE80A3832B76EDBBE190E76ECCC52E04496E7E2CEDEB61905E4E4F2A028C8
              CBDF8C060A0AB910F2BC5C4530F1E21228A3B40C490157600154B8BCA2B20ACA
              ACE6E24328A881D950CB55970465D637F02314343641459BB9B85AA0CCD636AE
              0157D0DE81A4A0B30B2ADACD25D00365F60A0A2114F4F54345274C9C3419CA9C
              8214500C5C534BA1C2D3A643193366A22898351B2D2A8AE708232B60E09A3B0F
              55C1ECF928F20C5C5C730B8A11D2A50B6A50E5414A162E5ABC04EA8EA5CB9663
              C80355AC685CD9B274D5EA356BD7CD1711850B03003F5327435E32F842000000
              2574455874646174653A63726561746500323031382D30392D32365431373A34
              363A35322B30323A3030B2192E1C0000002574455874646174653A6D6F646966
              7900323031382D30392D32365431373A34363A35322B30323A3030C34496A000
              00004674455874736F66747761726500496D6167654D616769636B20362E372E
              382D3920323031362D30362D31362051313620687474703A2F2F7777772E696D
              6167656D616769636B2E6F7267E6BF34B600000018744558745468756D623A3A
              446F63756D656E743A3A50616765730031A7FFBB2F0000001874455874546875
              6D623A3A496D6167653A3A68656967687400353132C0D0505100000017744558
              745468756D623A3A496D6167653A3A5769647468003531321C7C03DC00000019
              744558745468756D623A3A4D696D657479706500696D6167652F706E673FB256
              4E00000017744558745468756D623A3A4D54696D650031353337393736383132
              39E8A91A00000013744558745468756D623A3A53697A650031342E364B42422C
              97D77300000071744558745468756D623A3A5552490066696C653A2F2F2E2F75
              706C6F6164732F35362F57666E596667322F313537322F333539323832382D67
              656E6572616C2D6B65792D6B65792D6C6F636B2D6C6F636B2D6F66666963652D
              70617373776F72642D73656375726974795F3130373735392E706E679B612056
              0000000049454E44AE426082}
          end>
      end
      item
        Name = '3592827-access-general-house-key-key-lock-key-login'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C000002A6504C5445000000648094647F946482936481
              94647E946CC2A56EC4A76383946EC2A76584966DBDA56EC3A6668D986AAAA06B
              B1A26EC2A66CB8A4689D9C6DBAA4668B97668C986BAFA165829570C3A7689A9C
              616D96638095657E93667D92667D956D73946F7194648094647F94647F94647F
              94647F94648094647F94647F94647F94647F94647F94647F94647F94647F9464
              7F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94
              647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F
              94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F9464
              7F94647F94647F946EC4A76EC4A7647F94647F94647F94647F94647F94647F94
              647F946EC4A76EC4A76EC4A76EC4A76EC4A76EC4A76EC4A7647F94647F94647F
              94647F94647F94657E946EC4A76EC4A76EC4A76EC4A7647F94647F94647F9464
              7F94647F946EC4A76EC4A76EC4A76EC4A7647F94647F94647F94647F946EC4A7
              6EC4A76EC4A7637F93647F94647F94647F946EC4A76EC4A7647F94647F946EC4
              A76EC4A76EC4A7647F94647F94647F946EC4A76EC4A76EC4A76EC4A7647F9464
              7F94647F94647F94647F946EC4A76EC4A76EC4A76EC4A7647F94647F94647F94
              647F94647F946EC4A76EC4A76EC4A76EC4A76EC4A76EC4A7647F94647F94647F
              946EC4A76EC4A76EC4A76EC4A7647F94647F94647F94647F94647F94647F9464
              8094647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94
              647F94647F94647F94647F94647F94647F94647F94647F94647F94647F946480
              94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F9464
              7F94647F94647F94647F94658093647F94647F94647F94647F94647F94647F94
              647F94647F94647F94647F94647F94647F946EC4A7FFFFFF8EA1C4AF000000DF
              74524E5300000000000000000000000000000000000000000000000000000000
              00000000000108181C0C024D93BCD8DDC5A16117013FB5F6FCCB5C070262E6F9
              8B696880BBF3F58A0D57ED63130B4ABE850427D6CF3205071AACF2508CE94320
              7BB1B88C33011DC7121ED90130CAE153FA5553FB3D0CB3DA2915927BD23FF36F
              01C096096795DA0E55FB8397D0281FD7F448B8A533EC6565FD940838FE70B3C6
              5CCCF6DC7D12069B2B15393E026AF47E2374191BB07A3A1F2F67CE05F0F1E1E0
              FDAD299059034EC8196E42A0EAB45B71EE6648CD4B542C066C31EFD1872E88AF
              5DE76DEF5965A300000001624B4744E15F08CFA6000000097048597300005311
              00005311010DF18749000002164944415438CB6360201D302A2A29ABA8AA31E2
              90665255D7D0D4D2D6D1D5D36762C2226D6068647C1F0C4C4CCDCC3154305958
              5ADDB736B5B1B5B37770BCEFE4EC82A68289C9D5EDBE96BB0733230B93A797F7
              7D131F5F54154C7EFEF703025959D88282D9D9994242EF8785A32860E288B81F
              19C5C8191D131B179F90C895947CDF210545416ADA7D9B74EE8CCC07409095CD
              C36296E3948BA2202F3FAC80B7B0E801181497F09506DC2F4351507EBFA294BF
              B20AA2E041B5408DEEFD5A140575F76BEBB91BA0F20F1AD981024D280A9CEF27
              370BB6B44215B4B133B5DFEF4051E07EDFAA53A8AB1B22DFD32B5CDF77BF1F45
              C18489F72731724E063B62CAD46922D327CE9889A2A07ED6FDD921A24173E656
              CD9BBF60A1D8A2C5F7B597A0866478D8FD3A557189A5CB9677AD90545BB9EAFE
              6A2954056B9AEEE72F4E959601B19BD7BADDD75C871AD4EB3700A37946C7C64D
              9B53B76C75B0BEBF6D0B932C546A7B60122B587E479FDBFD193B77ED9EB8E7BE
              F5DE25A024C3B46FFF81834C87DC0E6F3902940F3B5A7FECF82E6B60723971F2
              5433D87CA6D3F7CF9C953BB7F3FE79CD1940795F2626DF3517EC6C2F5EAA875A
              CFB4641B50C5E52B3BEFDF07CB63A642A6ABDBEE5F9BB4E63A0E7906790546A0
              8A89DBF6E09067D87CE346C8CD005CE603C1ADFBF76F4F70C02DCF7067C77D93
              BB26B8E5197CEF85E1311FE40BDFA361F8E441C1AC77D21D8F3C28379B2B32E2
              940500394EFCA32FC3FD8E0000002574455874646174653A6372656174650032
              3031382D30392D32365431373A34363A35302B30323A303025863F3500000025
              74455874646174653A6D6F6469667900323031382D30392D32365431373A3436
              3A35302B30323A303054DB87890000004674455874736F66747761726500496D
              6167654D616769636B20362E372E382D3920323031362D30362D313620513136
              20687474703A2F2F7777772E696D6167656D616769636B2E6F7267E6BF34B600
              000018744558745468756D623A3A446F63756D656E743A3A50616765730031A7
              FFBB2F00000018744558745468756D623A3A496D6167653A3A68656967687400
              353132C0D0505100000017744558745468756D623A3A496D6167653A3A576964
              7468003531321C7C03DC00000019744558745468756D623A3A4D696D65747970
              6500696D6167652F706E673FB2564E00000017744558745468756D623A3A4D54
              696D650031353337393736383130D7E6C83600000013744558745468756D623A
              3A53697A650032302E394B4242DE8D9FAE00000071744558745468756D623A3A
              5552490066696C653A2F2F2E2F75706C6F6164732F35362F57666E596667322F
              313537322F333539323832372D6163636573732D67656E6572616C2D686F7573
              652D6B65792D6B65792D6C6F636B2D6B65792D6C6F67696E2D6F66666963655F
              3130373735382E706E672920A71A0000000049454E44AE426082}
          end>
      end
      item
        Name = '3592855-business-man-employee-general-human-member-office'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C0000029D504C5445000000647F946A8598658095637E
              95648094637F945E8095678294638094657F94579695637EA564859765859668
              9B9C647F956BACA06690996AAAA06791996BB2A268989B6CB4A36FCDA9648093
              5B4483647F94647F94647F94647F94647F94647F94647F94647F94647F94647F
              94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F9464
              7F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94
              647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F
              94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F9464
              7F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94
              647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F
              94647F94647F94647F94647F94647F94647F94647F94647F94648094647F9464
              7F94647F94647F94647F94647F94647F94647C93647D93648094647F94647F94
              647F94647F94647F94647F94647F946FC9A86FC9A8647F94647F94647F94647F
              94647F94647F946EC4A76EC4A7647F94647F94647F94647F94647F94647E9472
              E4B06EC4A76EC4A7647F94647F946379926FC8A86EC4A76EC4A775F0B3647E94
              647F94647F94647F94551A786EC4A76EC4A76EC4A76FC8A8637A93647F946EC4
              A76EC4A76EC5A75A3780647F946EC4A7647F94647F94647F947AFFBE6EC4A76E
              C4A7637B936FCAA96EC4A76EC4A77AFFBF647F945F5A8A6EC5A76EC4A76EC4A7
              6FCAA9647F94647F94647F946EC4A76EC4A76EC4A76EC5A75E5989647F94647F
              94647F94647F94647F946EC4A76EC4A76EC4A76EC4A76FC7A8637892647F9464
              7F94647F94647F94647F94647F946EC4A76EC4A76EC4A76EC5A8647F94647F94
              647F94648094647F946EC4A7FFFFFF039DF4C5000000DC74524E530000000000
              00000000000000000000000000000000000000000000043383ADC8BEA4681D21
              8FE4FEFACF670B32CAF9961228CDFD9208069FF75B42F0C3118EF648BB7219D9
              931CDD0C799A5254F8D21B0FB7733EE3B31450B62417013FB9ED911A022AABC6
              105599DFD8BA823804096DD326E57C0D1C1708053AA69E0ED72E110C4CAFECFB
              645F8C6390B407F2F13807C49466DA1720E4BE063BF3E11E0343F8DF1D19896D
              F54003656594F54103B6891E18D9B503BD0639F2DA19DE30DB5AFDEE33061527
              6BB087189BFB7D0B08D04F2D629D370F8069054749180216EB5F7A0000000162
              4B4744DEE96EE29B00000009704859730000531100005311010DF18749000001
              CA4944415438CB63608003466919593979054525652666064CC0C8A8A2AAA67E
              07083434B5B419B1C8EBE8DE81013D7D030C158C86467710C0D8C4144D05A399
              F91D646061C988AA82D1CA1A45C11D1B5B14052CAC76A8F277EC1D5014309A3A
              A229B8E384AAC0D9055D812BAA0237777405FAA80A3C6CD01578A2286063F742
              93D7F046F3A68F2FAA023F7F3405018128F2C6418CE841191C82AC20340C3D32
              1839C2D510F2119118F21E51D131B11A10E9B8F884C4286964259C5C49C92931
              DCA969E929199959D939B979F905B2C831CE58084C0B45C5CA3C8925A565E5BC
              15955516778CAB6BE02A18A35DC12EAFD5AFE3AB6FE06F6C6A06715B5A190560
              0A12322196ABB7B1B6770876425DDAD50D338231A70722D4DBD73F61A2D024A8
              82C909700531F610A1CC2953A74D9F31731684377B0E8682AEB9F3E62F58B868
              324E058B8597DC5DBA6C79044E052B4426DEBDBB5274152E05ABD7AC5D77F7EE
              7AB17C5C0A32366CDC74F7EEE62D6B56E350B075DBF61D77EFEEDCB56137BA82
              3D7BC199D2447CDFFEBB770F1C3C044EE21A5987E10A128F1C3DA6A671E7B8C4
              8993A7769C3E73F6D89D59E75CCF1F96448E2ED30B17ED2E5D16BB72F5DA75A9
              1BFA9E376FDD6685C80000D0509DD8DCEAD7FD0000002574455874646174653A
              63726561746500323031382D30392D32365431373A34363A33312B30323A3030
              459E3D060000002574455874646174653A6D6F6469667900323031382D30392D
              32365431373A34363A33312B30323A303034C385BA0000004674455874736F66
              747761726500496D6167654D616769636B20362E372E382D3920323031362D30
              362D31362051313620687474703A2F2F7777772E696D6167656D616769636B2E
              6F7267E6BF34B600000018744558745468756D623A3A446F63756D656E743A3A
              50616765730031A7FFBB2F00000018744558745468756D623A3A496D6167653A
              3A68656967687400353132C0D0505100000017744558745468756D623A3A496D
              6167653A3A5769647468003531321C7C03DC00000019744558745468756D623A
              3A4D696D657479706500696D6167652F706E673FB2564E000000177445587454
              68756D623A3A4D54696D65003135333739373637393163643595000000137445
              58745468756D623A3A53697A650031372E394B4242F260B58B00000074744558
              745468756D623A3A5552490066696C653A2F2F2E2F75706C6F6164732F35362F
              57666E596667322F313537322F333539323835352D627573696E6573732D6D61
              6E2D656D706C6F7965652D67656E6572616C2D68756D616E2D6D656D6265722D
              6F66666963652D7469655F3130373734352E706E671C3BA6660000000049454E
              44AE426082}
          end>
      end
      item
        Name = '3592852-general-office-open-padlock-safety-unlock-unlock-padlock'
        SourceImages = <
          item
            Image.Data = {
              89504E470D0A1A0A0000000D494844520000002000000020080300000044A48A
              C60000000467414D410000B18F0BFC6105000000017352474200AECE1CE90000
              00206348524D00007A26000080840000FA00000080E8000075300000EA600000
              3A98000017709CBA513C00000225504C544500000045596B43596D465A694659
              6B43596B455A6B45596A44596C647F9444596A647F93647F96506779657F9464
              7D9467828F647F9545596B45596B45596B45596B45596B45596B45596B45596B
              45596B45596B45596B45596B45596B45596B45596B45596B45596B45596B4659
              6B45596B45596B45596B45596B45596B45596B45596B45596B45596B45596B45
              596B45596B45596B45596B45596B45596B45596B45596B45596B45596B45596B
              45596B45596B45596B45596B45596B45596B45596B45596B45596B45596B4559
              6B45596B45596B45596B45596B45596B45596B45596B45596B45596B45596B45
              596B45596B44596C647F94647F94647F94647F94647F94647F94647F94647F94
              4D6376658095647F94647F94647F94647F94647F94647F94647F94647F94647F
              9445586B607B8F647F94647F94647F94647F94485C6E647F945B75895E778C64
              7F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94
              647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F
              94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F9464
              7F94647F94647F94647F94647F94647F94647F94647F94647F94647F94647F94
              647F94647F94647F94647F94648094647F94647F94647F94647F94647F94647F
              94647F94647F94647F94648094647F94647F94647F94647F94647F94647F9463
              7F9445596B465A6C52687C647F94566E82637E93FFFFFF50CD98B7000000B074
              524E530000000000000000000000000000000000000F559DC6DBD6B5832F0201
              43B7F5FEE186190164E8F9F6FCB82349E9D9804C3E405EAAAEBD290860E6FA5F
              46D72775B0067226E4DC1B8A690EC41A8C506105010D2D42534B3A1C048C7BC2
              EAF7FBF9F3DBA50C8CF7FEF6B02F8BD6019BD12B38E79C8FFCEB350FC7BD4972
              F0651EE068C487E16309C0969015D26AC57002A354814852F5FAFDBBA0EE1FBA
              6E0321A4F8DF6259B6DC8E0140ABA784602603723E893400000001624B4744B6
              AA070BF100000009704859730000531100005311010DF187490000018D494441
              5438CB63608003462161115131710949296946064CC028232B27BF0104141495
              94315530AAA8AA0125D535343481949636BA0A26461DDD0D1BF4F40D0C8D8C4D
              8006990AA1A9601432DBB041C29C1928CC686169B5C1DA065D81ADFC063B7B88
              200BAB83C206472754158CCE1B362831B241392EAE1BDCDC5115B0796CD8E009
              1362F4F2DEA0E783A6C0175901A39FA3BF341E050CECEC01811C0C5814040587
              848685474472628623484154744C6C5C7C42625272680A8612AED48D9BD2D237
              4341466616370FAA02DEEC2D5B3723819C104E6E6479CEDC3C14F9CD9BF30B50
              6CE12C2CDA8C068A919DCAC95702134F288532CACA911554544285ABAA6B6AA1
              CC3A6405F50D50D146CE942628B31945410B54B495B3AD1DCAEC18040A3A9115
              747543457B38837AA1CC3E6405FD13A0A29513272542236C327258734E990A55
              316D3A9431A3024541DB4CB4A89855CDC98F125BB3E7A0C827CE9D87966638E7
              2F5888905FB41833D971A62C593A0B9CA6A62D5B1EBC024BB214100C5A59D3B1
              6AF59AB5EBD62349030011111DBE1D8631CF0000002574455874646174653A63
              726561746500323031382D30392D32365431373A34373A31352B30323A30301C
              3675560000002574455874646174653A6D6F6469667900323031382D30392D32
              365431373A34373A31352B30323A30306D6BCDEA0000004674455874736F6674
              7761726500496D6167654D616769636B20362E372E382D3920323031362D3036
              2D31362051313620687474703A2F2F7777772E696D6167656D616769636B2E6F
              7267E6BF34B600000018744558745468756D623A3A446F63756D656E743A3A50
              616765730031A7FFBB2F00000018744558745468756D623A3A496D6167653A3A
              68656967687400353132C0D0505100000017744558745468756D623A3A496D61
              67653A3A5769647468003531321C7C03DC00000019744558745468756D623A3A
              4D696D657479706500696D6167652F706E673FB2564E00000017744558745468
              756D623A3A4D54696D65003135333739373638333595BA5E3B00000013744558
              745468756D623A3A53697A650031352E314B42427A1C3C6F0000008174455874
              5468756D623A3A5552490066696C653A2F2F2E2F75706C6F6164732F35362F57
              666E596667322F313537322F333539323835322D67656E6572616C2D6F666669
              63652D6F70656E2D7061646C6F636B2D7361666574792D756E6C6F636B2D756E
              6C6F636B2D7061646C6F636B2D756E6C6F636B696E675F3130373737352E706E
              67875753B60000000049454E44AE426082}
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
end
