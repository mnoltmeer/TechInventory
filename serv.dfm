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
  object MailSender: TIdSMTP
    SASLMechanisms = <>
    Left = 144
    Top = 112
  end
  object ConnectionServer: TIdTCPServer
    Bindings = <
      item
        IP = '0.0.0.0'
        Port = 9874
      end>
    DefaultPort = 0
    OnConnect = ConnectionServerConnect
    OnDisconnect = ConnectionServerDisconnect
    OnExecute = ConnectionServerExecute
    Left = 240
    Top = 112
  end
  object StoredProc: TFDStoredProc
    Connection = StatConnection
    Left = 128
    Top = 192
  end
end
