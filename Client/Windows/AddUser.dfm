object AddUserForm: TAddUserForm
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'AddUserForm'
  ClientHeight = 319
  ClientWidth = 437
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
  object Label2: TLabel
    Left = 8
    Top = 8
    Width = 68
    Height = 13
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1083#1086#1075#1110#1085
  end
  object Label3: TLabel
    Left = 8
    Top = 59
    Width = 79
    Height = 13
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1087#1072#1088#1086#1083#1100
  end
  object Label4: TLabel
    Left = 8
    Top = 114
    Width = 90
    Height = 13
    Caption = #1055#1086#1074#1090#1086#1088#1110#1090#1100' '#1087#1072#1088#1086#1083#1100
  end
  object Label5: TLabel
    Left = 8
    Top = 166
    Width = 133
    Height = 13
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1072#1076#1088#1077#1089#1091' '#1077#1083'. '#1087#1086#1096#1090#1080
  end
  object LoginError: TLabel
    Left = 102
    Top = 8
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
  object PasswordError: TLabel
    Left = 112
    Top = 59
    Width = 84
    Height = 16
    Caption = 'PasswordError'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object EMailError: TLabel
    Left = 175
    Top = 166
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
  object ConfirmPasswordError: TLabel
    Left = 128
    Top = 114
    Width = 129
    Height = 16
    Caption = 'ConfirmPasswordError'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label1: TLabel
    Left = 8
    Top = 221
    Width = 67
    Height = 13
    Caption = #1054#1073#1077#1088#1110#1090#1100' '#1088#1086#1083#1100
  end
  object RegistrationResult: TLabel
    Left = 159
    Top = 243
    Width = 88
    Height = 13
    Alignment = taCenter
    Caption = 'RegistrationResult'
  end
  object Login: TEdit
    Left = 8
    Top = 27
    Width = 201
    Height = 21
    TabOrder = 0
  end
  object Password: TEdit
    Left = 8
    Top = 78
    Width = 201
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
  end
  object ConfirmPassword: TEdit
    Left = 8
    Top = 133
    Width = 201
    Height = 21
    PasswordChar = '*'
    TabOrder = 2
  end
  object EMail: TEdit
    Left = 8
    Top = 185
    Width = 289
    Height = 21
    TabOrder = 3
  end
  object UserRole: TComboBox
    Left = 8
    Top = 240
    Width = 145
    Height = 21
    ItemIndex = 0
    TabOrder = 4
    Text = #1040#1075#1077#1085#1090
    Items.Strings = (
      #1040#1075#1077#1085#1090
      #1040#1076#1084#1110#1085#1110#1089#1090#1088#1072#1090#1086#1088)
  end
  object Create: TButton
    Left = 8
    Top = 280
    Width = 75
    Height = 25
    Caption = #1057#1090#1074#1086#1088#1080#1090#1080
    TabOrder = 5
    OnClick = CreateClick
  end
  object Cancel: TButton
    Left = 112
    Top = 280
    Width = 75
    Height = 25
    Caption = #1057#1082#1072#1089#1091#1074#1072#1090#1080
    TabOrder = 6
    OnClick = CancelClick
  end
end
