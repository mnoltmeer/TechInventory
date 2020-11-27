object RegistrationForm: TRegistrationForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'RegistrationForm'
  ClientHeight = 362
  ClientWidth = 475
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 0
    Top = 0
    Width = 475
    Height = 23
    Align = alTop
    Alignment = taCenter
    Caption = #1056#1077#1108#1089#1090#1088#1072#1094#1110#1103' '#1091' '#1057#1080#1089#1090#1077#1084#1110
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ExplicitWidth = 180
  end
  object Label2: TLabel
    Left = 8
    Top = 29
    Width = 79
    Height = 16
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1083#1086#1075#1110#1085
  end
  object Label3: TLabel
    Left = 8
    Top = 80
    Width = 92
    Height = 16
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1087#1072#1088#1086#1083#1100
  end
  object Label4: TLabel
    Left = 8
    Top = 135
    Width = 104
    Height = 16
    Caption = #1055#1086#1074#1090#1086#1088#1110#1090#1100' '#1087#1072#1088#1086#1083#1100
  end
  object Label5: TLabel
    Left = 8
    Top = 191
    Width = 153
    Height = 16
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1072#1076#1088#1077#1089#1091' '#1077#1083'. '#1087#1086#1096#1090#1080
  end
  object Label6: TLabel
    Left = 8
    Top = 253
    Width = 444
    Height = 16
    Caption = 
      #1053#1072' '#1074#1072#1096#1091' '#1087#1086#1096#1090#1091' '#1073#1091#1083#1086' '#1085#1072#1076#1110#1089#1083#1072#1085#1086' '#1082#1086#1076' '#1074#1077#1088#1080#1092#1110#1082#1072#1094#1110#1111', '#1074#1074#1077#1076#1110#1090#1100' '#1081#1086#1075#1086' '#1074' '#1087#1086#1083 +
      #1077' '#1085#1080#1078#1095#1077
  end
  object RegistrationResult: TLabel
    Left = 248
    Top = 282
    Width = 103
    Height = 16
    Alignment = taCenter
    Caption = 'RegistrationResult'
  end
  object Login: TEdit
    Left = 8
    Top = 48
    Width = 201
    Height = 24
    TabOrder = 0
  end
  object Password: TEdit
    Left = 8
    Top = 99
    Width = 201
    Height = 24
    PasswordChar = '*'
    TabOrder = 1
  end
  object Edit2: TEdit
    Left = 8
    Top = 154
    Width = 201
    Height = 24
    PasswordChar = '*'
    TabOrder = 2
  end
  object EMail: TEdit
    Left = 8
    Top = 210
    Width = 289
    Height = 24
    TabOrder = 3
  end
  object VerificationCode: TEdit
    Left = 8
    Top = 276
    Width = 121
    Height = 27
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object SendCode: TButton
    Left = 303
    Top = 210
    Width = 164
    Height = 25
    Caption = #1053#1072#1076#1110#1089#1083#1072#1090#1080' '#1082#1086#1076' '#1074#1077#1088#1080#1092#1110#1082#1072#1094#1110#1111
    TabOrder = 5
  end
  object Confirm: TButton
    Left = 144
    Top = 277
    Width = 84
    Height = 25
    Caption = #1055#1110#1076#1090#1074#1077#1088#1076#1080#1090#1080
    TabOrder = 6
  end
  object Exit: TButton
    Left = 392
    Top = 329
    Width = 75
    Height = 25
    Caption = #1042#1080#1081#1090#1080
    TabOrder = 7
  end
end
