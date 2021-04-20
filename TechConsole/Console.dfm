object ConsoleForm: TConsoleForm
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'TIService Console'
  ClientHeight = 419
  ClientWidth = 731
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object SendCmdPanel: TPanel
    Left = 0
    Top = 394
    Width = 731
    Height = 25
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitTop = 227
    ExplicitWidth = 537
    object CmdText: TEdit
      Left = 0
      Top = 0
      Width = 656
      Height = 25
      Align = alClient
      TabOrder = 0
      ExplicitTop = 4
      ExplicitWidth = 121
      ExplicitHeight = 21
    end
    object CmdSend: TButton
      Left = 656
      Top = 0
      Width = 75
      Height = 25
      Align = alRight
      Caption = #1053#1072#1076#1110#1089#1083#1072#1090#1080
      TabOrder = 1
      ExplicitLeft = 432
    end
  end
  object ConsoleWindow: TListBox
    Left = 0
    Top = 0
    Width = 731
    Height = 394
    Align = alClient
    ItemHeight = 13
    TabOrder = 1
    ExplicitLeft = 24
    ExplicitTop = 16
    ExplicitWidth = 121
    ExplicitHeight = 97
  end
  object Listener: TIdTCPServer
    Bindings = <>
    DefaultPort = 0
    OnExecute = ListenerExecute
    Left = 680
    Top = 8
  end
end
