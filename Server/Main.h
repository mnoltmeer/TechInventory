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
OT_ADD = 1,	    //Ввод нового пристрою
OT_REMOVE = 2,  //Вивід з експлуатації
OT_CH_INN = 3,  //Зміна інвентарного номеру
OT_CH_SN = 4,   //Зміна серійного номеру
OT_CH_MODEL = 5,//Зміна моделі пристрою
OT_CH_LOC = 6   //Зміна локації пристрою
};

struct UserInfo
{
  int ID;
  String Role;
  String Mail;
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

//методи, що викликаються з ExecuteCommand() і повертають туди результат
//авторизує користувача, якщо успішно повертає ІД Агента та роль, інакше повертає NULL
	UserInfo __fastcall Authorisation(const String &login, const String &pass);
	bool __fastcall Registration(const String &login, const String &pass, const String &mail);
	bool __fastcall IsLoginFree(const String &login);
	bool __fastcall SetUserPassword(int user_id, const String &new_password);
	bool __fastcall ValidUserPassword(int user_id, const String &password);
	bool __fastcall SetUserMail(int user_id, const String &new_mail);
//---------------------------------------------------------------------------

	TMemoryStream* __fastcall CryptData(String data, const char *pass);
	String __fastcall EncryptData(TMemoryStream *crypted_data, const char *pass);
	bool __fastcall SendToClient(const String &host, TStringStream *buffer);
//парсить документ, що надійшов, перевіряє вміст і запускає ProcessAnswer() або ProcessRequest()
//при потребі одразу повертає відповідь у вигляді xml-файлу
	TStringStream* __fastcall ParseXML(TXMLDocument *ixml);
//оброблює відповідь клієнта та виконує відповідні дії
	void __fastcall ProcessAnswer(TXMLDocument *ixml);
//оброблює запит клієнта та виконує ExecuteCommand()
//при потребі одразу повертає відповідь у вигляді xml-файлу
	TStringStream* __fastcall ProcessRequest(TXMLDocument *ixml);
//обробляє команду клієнта і виконує відповідний запит до БД
//при потребі одразу повертає відповідь у вигляді xml-файлу
	TStringStream* __fastcall ExecuteCommand(const String &command, TStringList *params);
//оброблює результат виборки з БД та формує xml-файл
	TStringStream* __fastcall CreateAnswer();
//формує результат на основі набору даних
	TStringStream* __fastcall CreateAnswer(const String &command, TStringList *data);
//формує результат на базі строк. Сивол-роздільник стовпців - ; Символ-роздільик рядків - &&
	TStringStream* __fastcall CreateAnswer(const String &command, const String &data);
//формує результат з однієї лише команди
	TStringStream* __fastcall CreateAnswer(const String &command);
//створює запит до клієнта
	TStringStream* __fastcall CreateRequest(const String &command, const String &params);
//створює об'єкт документу XML у пам'яті
	TXMLDocument *__fastcall CreatXMLStream(TStringStream *ms);
    bool __fastcall ConnectToSMTP();
	bool __fastcall SendMsg(String mail_addr, String subject, String from, String text);
	String __fastcall GenerateVerificationCode();
    bool __fastcall SendVerificationCode(const String &mail, const String &code);

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
