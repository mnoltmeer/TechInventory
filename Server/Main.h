/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ImgList.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.DApt.hpp>
#include <FireDAC.DApt.Intf.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.FB.hpp>
#include <FireDAC.Phys.FBDef.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.IBBase.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Stan.Async.hpp>
#include <FireDAC.Stan.Def.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Pool.hpp>
#include <FireDAC.UI.Intf.hpp>
#include <FireDAC.VCLUI.Wait.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.omnixmldom.hpp>
#include <Xml.XMLIntf.hpp>
//#include <Xml.Win.msxmldom.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdMessageClient.hpp>
#include <IdSMTP.hpp>
#include <IdSMTPBase.hpp>

#define ROLE_ADMIN true
#define ROLE_USER false
#define DEFAULT_SERVER_PORT 9874
#define DEFAULT_CLIENT_PORT 9875

enum OperationType {
OT_ADD = 1,	    //���� ������ ��������
OT_REMOVE = 2,  //���� � ������������
OT_CH_INN = 3,  //���� ������������ ������
OT_CH_SN = 4,   //���� �������� ������
OT_CH_MODEL = 5,//���� ����� ��������
OT_CH_LOC = 6   //���� ������� ��������
};

struct UserInfo
{
  int ID;
  String Role;
};
//---------------------------------------------------------------------------
class TServerForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *MainPanel;
	TPanel *ClientListPanel;
	TPanel *ControlsPanel;
	TPanel *ControlHeaderPanel;
	TLabel *Label1;
	TImage *SwServerOff;
	TImage *SwServerOn;
	TIdTCPServer *Listener;
	TPopupMenu *MainPopupMenu;
	TMenuItem *PPStatus;
	TMenuItem *PPShowWindow;
	TMenuItem *PPClose;
	TTrayIcon *TrayIcon;
	TImageList *MenuImages;
	TLabel *LbVersion;
	TMemo *Log;
	TListBox *AuthorisedClients;
	TFDConnection *StatConnection;
	TFDTransaction *WriteTransaction;
	TFDQuery *WriteQuery;
	TFDPhysFBDriverLink *StatFBDriverLink;
	TIdSMTP *MailSender;
	TBitBtn *Settings;
	TPanel *Panel1;
	TLabel *Label2;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ListenerExecute(TIdContext *AContext);
	void __fastcall ListenerConnect(TIdContext *AContext);
	void __fastcall ListenerDisconnect(TIdContext *AContext);
	void __fastcall SettingsClick(TObject *Sender);
	void __fastcall PPShowWindowClick(TObject *Sender);
	void __fastcall PPCloseClick(TObject *Sender);
	void __fastcall MainPopupMenuPopup(TObject *Sender);
	void __fastcall TrayIconDblClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
    void __fastcall StartServer();
	void __fastcall StopServer();
    void __fastcall ConnectToDB();
	void __fastcall DisconnectFromDB();
//�������� �����������, ���� ������ ������� �� ������ �� ����, ������ ������� NULL
	UserInfo __fastcall Authorisation(const String &login, const String &pass);
    TMemoryStream* __fastcall CryptData(String data, const char *pass);
	String __fastcall EncryptData(TMemoryStream *crypted_data, const char *pass);
    bool __fastcall ConnectToSMTP();
	void __fastcall SendMsg(String mail_addr, String subject, String from, String log);
	bool __fastcall SendToClient(const String &host, TStringStream *buffer);
//������� ��������, �� �������, �������� ���� � ������� ProcessAnswer() ��� ProcessRequest()
//��� ������ ������ ������� ������� � ������ xml-�����
	TStringStream* __fastcall ParseXML(TXMLDocument *ixml);
//�������� ������� �볺��� �� ������ �������� 䳿
	void __fastcall ProcessAnswer(TXMLDocument *ixml);
//�������� ����� �볺��� �� ������ ExecuteCommand()
//��� ������ ������ ������� ������� � ������ xml-�����
	TStringStream* __fastcall ProcessRequest(TXMLDocument *ixml);
//�������� ������� �볺��� � ������ ��������� ����� �� ��
//��� ������ ������ ������� ������� � ������ xml-�����
	TStringStream* __fastcall ExecuteCommand(const String &command, TStringList *params);
//�������� ��������� ������� � �� �� ����� xml-����
	TStringStream* __fastcall CreateAnswer();
//����� ��������� �� ����� ������ �����
	TStringStream* __fastcall CreateAnswer(const String &command, TStringList *data);
//����� ����� �� ��� �����. �����-��������� �������� - ; ������-�������� ����� - &&
	TStringStream* __fastcall CreateAnswer(const String &headers, const String &data);
//������� ����� �� �볺���
	TStringStream* __fastcall CreateRequest(const String &command, const String &params);
//������� ��'��� ��������� XML � ���'��
	TXMLDocument *__fastcall CreatXMLStream(TStringStream *ms);

public:		// User declarations
	__fastcall TServerForm(TComponent* Owner);

	void __fastcall WriteLog(String record);
    void __fastcall WriteSettings();
	bool __fastcall ReadSettings();
};
//---------------------------------------------------------------------------
extern PACKAGE TServerForm *ServerForm;

//---------------------------------------------------------------------------

TFDTransaction *CreateNewTransactionObj();
TFDQuery *CreateNewQueryObj(TFDTransaction *t);
//---------------------------------------------------------------------------
#endif