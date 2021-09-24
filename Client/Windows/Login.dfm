object LoginForm: TLoginForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsNone
  Caption = #1042#1093#1110#1076' '#1091' '#1089#1080#1089#1090#1077#1084#1091
  ClientHeight = 189
  ClientWidth = 317
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
  object Label1: TLabel
    Left = 8
    Top = 68
    Width = 60
    Height = 13
    Caption = #1050#1086#1088#1080#1089#1090#1091#1074#1072#1095
  end
  object Label2: TLabel
    Left = 8
    Top = 95
    Width = 37
    Height = 13
    Caption = #1055#1072#1088#1086#1083#1100
  end
  object RegNewUser: TLabel
    Left = 8
    Top = 153
    Width = 166
    Height = 13
    Cursor = crHandPoint
    Caption = #1057#1090#1074#1086#1088#1080#1090#1080' '#1085#1086#1074#1080#1081' '#1086#1073#1083#1110#1082#1086#1074#1080#1081' '#1079#1072#1087#1080#1089
    Color = 15570276
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentColor = False
    ParentFont = False
    OnClick = RegNewUserClick
  end
  object ForgotPassword: TLabel
    Left = 225
    Top = 153
    Width = 78
    Height = 13
    Cursor = crHandPoint
    Caption = #1071' '#1079#1072#1073#1091#1074' '#1087#1072#1088#1086#1083#1100
    Color = 15570277
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentColor = False
    ParentFont = False
    OnClick = ForgotPasswordClick
  end
  object AuthError: TLabel
    Left = 135
    Top = 7
    Width = 47
    Height = 13
    Caption = 'AuthError'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    Visible = False
  end
  object Label3: TLabel
    Left = 8
    Top = 41
    Width = 37
    Height = 13
    Caption = #1057#1077#1088#1074#1077#1088
  end
  object UserName: TEdit
    Left = 83
    Top = 65
    Width = 145
    Height = 21
    TabOrder = 0
    OnKeyPress = UserNameKeyPress
  end
  object Password: TEdit
    Left = 83
    Top = 92
    Width = 145
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
    OnKeyPress = PasswordKeyPress
  end
  object StartAuth: TButton
    Left = 35
    Top = 119
    Width = 75
    Height = 25
    Caption = #1059#1074#1110#1081#1090#1080
    TabOrder = 2
    OnClick = StartAuthClick
  end
  object ServerName: TEdit
    Left = 83
    Top = 38
    Width = 145
    Height = 21
    TabOrder = 3
    OnKeyPress = UserNameKeyPress
  end
  object Cancel: TButton
    Left = 200
    Top = 119
    Width = 75
    Height = 25
    Caption = #1057#1082#1072#1089#1091#1074#1072#1090#1080
    TabOrder = 4
    OnClick = CancelClick
  end
end
