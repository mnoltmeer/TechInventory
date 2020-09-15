object TechService: TTechService
  OldCreateOrder = False
  DisplayName = 'TechInventService'
  OnExecute = ServiceExecute
  OnStart = ServiceStart
  OnStop = ServiceStop
  Height = 274
  Width = 351
  object StatConnection: TFDConnection
    Params.Strings = (
      'User_Name=sysdba'
      'Password=masterkey'
      'CharacterSet=UTF8'
      'Protocol=TCPIP'
      'DriverID=myFB')
    LoginPrompt = False
    Transaction = WriteTransaction
    Left = 32
    Top = 8
  end
  object WriteTransaction: TFDTransaction
    Options.Isolation = xiSnapshot
    Options.AutoStart = False
    Options.AutoStop = False
    Options.DisconnectAction = xdRollback
    Connection = StatConnection
    Left = 30
    Top = 192
  end
  object WriteQuery: TFDQuery
    Connection = StatConnection
    Transaction = WriteTransaction
    ResourceOptions.AssignedValues = [rvCmdExecMode]
    Left = 30
    Top = 128
  end
  object StatFBDriverLink: TFDPhysFBDriverLink
    DriverID = 'myFB'
    Left = 32
    Top = 64
  end
  object HttpServer: TIdHTTPServer
    Bindings = <>
    OnCommandGet = HttpServerCommandGet
    Left = 118
    Top = 8
  end
  object RemSessionTimer: TTimer
    Enabled = False
    Interval = 86400000
    OnTimer = RemSessionTimerTimer
    Left = 224
    Top = 8
  end
end
