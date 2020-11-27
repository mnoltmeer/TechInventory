object Form1: TForm1
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'PasswordChangeForm'
  ClientHeight = 153
  ClientWidth = 220
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 16
  object Label3: TLabel
    Left = 56
    Top = 8
    Width = 92
    Height = 16
    Caption = #1042#1082#1072#1078#1110#1090#1100' '#1087#1072#1088#1086#1083#1100
  end
  object Label4: TLabel
    Left = 56
    Top = 60
    Width = 104
    Height = 16
    Caption = #1055#1086#1074#1090#1086#1088#1110#1090#1100' '#1087#1072#1088#1086#1083#1100
  end
  object Password: TEdit
    Left = 8
    Top = 27
    Width = 201
    Height = 24
    PasswordChar = '*'
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 8
    Top = 82
    Width = 201
    Height = 24
    PasswordChar = '*'
    TabOrder = 1
  end
  object Apply: TButton
    Left = 8
    Top = 120
    Width = 89
    Height = 25
    Caption = #1047#1072#1089#1090#1086#1089#1091#1074#1072#1090#1080
    TabOrder = 2
  end
  object Cancel: TButton
    Left = 134
    Top = 120
    Width = 75
    Height = 25
    Caption = #1057#1082#1072#1089#1091#1074#1072#1090#1080
    TabOrder = 3
  end
end
