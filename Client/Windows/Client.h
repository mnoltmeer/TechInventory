/*!
Copyright 2020 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#ifndef ClientH
#define ClientH
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
#include <Vcl.Imaging.GIFImg.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.BaseImageCollection.hpp>
#include <Vcl.ImageCollection.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.omnixmldom.hpp>
//#include <Xml.Win.msxmldom.hpp>
#include <Vcl.Menus.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdMessageClient.hpp>
#include <IdSMTP.hpp>
#include <IdSMTPBase.hpp>

#define DEFAULT_SERVER_PORT 9874
#define DEFAULT_CLIENT_PORT 9875

//---------------------------------------------------------------------------
class TClientForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *MenuPanel;
	TPanel *InfoPanel;
	TPanel *LogPanel;
	TMemo *ActionLog;
	TPanel *Panel1;
	TButton *SaveSessionLog;
	TLabel *Label6;
	TBitBtn *MnCheckItems;
	TSaveDialog *SaveCfgDialog;
	TOpenDialog *OpenCfgDialog;
	TBitBtn *MnShowItems;
	TBitBtn *MnAddItem;
	TLabel *ClientVersion;
	TLabel *ServerInfo;
	TLabel *UserInfo;
	TBitBtn *MnShowEvents;
	TBitBtn *MnHome;
	TBitBtn *MnAdmUsers;
	TBitBtn *MnAdmLocations;
	TBitBtn *MnAdmLogs;
	TBitBtn *MnAdmManage;
	TBitBtn *MnCheckItem;
	TPanel *PnHome;
	TLabel *Label1;
	TLabel *ActualClientVersion;
	TButton *UpdateClient;
	TPanel *PnCheckItem;
	TEdit *CheckItemScannedCode;
	TLabel *Label3;
	TTimer *LoadAnimTimer;
	TImage *PnLoading;
	TImageCollection *LoadingAnimImageList;
	TImageCollection *PanelImages;
	TIdTCPServer *Listener;
	TStringGrid *CheckItemResult;
	TLabel *Label4;
	TPanel *EditDataPanel;
	TBitBtn *CheckItemRemove;
	TPopupMenu *PPEditItem;
	TMenuItem *PPEdit;
	TMenuItem *PPRemove;
	TBitBtn *CheckItemEdit;
	TBitBtn *Reconnect;
	TBitBtn *CheckItemRefresh;
	TMenuItem *PPRefresh;
	TPanel *PnAddItem;
	TLabel *Label5;
	TLabel *Label7;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TEdit *AddItemNewInn;
	TEdit *AddItemNewSn;
	TEdit *AddItemNewModel;
	TButton *AddItemCreate;
	TButton *AddItemClearFields;
	TButton *AddItemSelectLocation;
	TLabel *AddItemCurrentLocation;
	TLabel *Label11;
	TPanel *PnShowItems;
	TPanel *Panel2;
	TLabel *Label12;
	TLabel *ShowItemsCurrentLocation;
	TPanel *Panel3;
	TBitBtn *ShowItemsRemove;
	TBitBtn *ShowItemsEdit;
	TBitBtn *ShowItemsRefresh;
	TStringGrid *ShowItemsResult;
	TPanel *PnShowEvents;
	TStringGrid *ShowEventsResult;
	TPanel *Panel4;
	TLabel *Label13;
	TLabel *Label14;
	TEdit *ShowEventsInn;
	TLabel *ShowEventsCurrentLocation;
	TButton *ShowEventsSelectLocation;
	TLabel *Label15;
	TLabel *Label16;
	TDateTimePicker *ShowEventsDateFrom;
	TDateTimePicker *ShowEventsDateTo;
	TButton *ShowEventsApply;
	TButton *ShowItemsSelectLocation;
	TLabel *Label17;
	TPanel *PnAdmUsers;
	TLabel *Label18;
	TPanel *Panel5;
	TStringGrid *AdmUsersResult;
	TPopupMenu *PPEditUser;
	TMenuItem *PPSetPwd;
	TMenuItem *PPRemoveUser;
	TPanel *PnAdmLocations;
	TLabel *Label19;
	TBitBtn *AdmUsersRefresh;
	TPanel *Panel6;
	TBitBtn *AdmLocationsRefresh;
	TBitBtn *AdmLocationsAdd;
	TBitBtn *AdmLocationsEdit;
	TBitBtn *AdmLocationsRemove;
	TBitBtn *AdmUsersAdd;
	TBitBtn *AdmUsersSetPwd;
	TBitBtn *AdmUsersRemove;
	TPopupMenu *PPEditLoc;
	TMenuItem *PPEditLocation;
	TMenuItem *PPRemoveLocation;
	TStringGrid *AdmLocationsResult;
	TPanel *PnAdmLogs;
	TLabel *Label20;
	TPanel *Panel7;
	TDateTimePicker *AdmLogsDate;
	TButton *AdmLogsShow;
	TPanel *PnAdmManage;
	TMemo *AdmLogsResult;
	TLabel *Label21;
	TEdit *AdmManageServerPort;
	TButton *AdmServerSetServerPort;
	TLabel *Label22;
	TPanel *PnCheckItems;
	TLabel *Label23;
	TPanel *Panel9;
	TLabel *Label24;
	TLabel *CheckItemsCurrentLocation;
	TButton *CheckItemsSelectLocation;
	TPanel *Panel10;
	TBitBtn *CheckItemsSendToUnknown;
	TBitBtn *CheckItemsEdit;
	TBitBtn *CheckItemsRefresh;
	TStringGrid *CheckItemsResult;
	TLabel *Label25;
	TEdit *AdmManageConnectionPort;
	TButton *AdmManageSetConnectionPort;
	TLabel *Label26;
	TPopupMenu *PPItemOptions;
	TMenuItem *PPCheckRefresh;
	TMenuItem *PPCheckEdit;
	TMenuItem *PPCheckSetUnknown;
	TMenuItem *PPAddLocation;
	TMenuItem *PPLocationsRefresh;
	TMenuItem *PPUsersRefresh;
	TLabel *Label2;
	TLabel *CurrentMail;
	TButton *ChangeMail;
	TButton *ChangePassword;
	void __fastcall LoadAnimTimerTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall MnHomeClick(TObject *Sender);
	void __fastcall MnCheckItemClick(TObject *Sender);
	void __fastcall MnCheckItemsClick(TObject *Sender);
	void __fastcall MnAddItemClick(TObject *Sender);
	void __fastcall MnShowItemsClick(TObject *Sender);
	void __fastcall MnShowEventsClick(TObject *Sender);
	void __fastcall MnAdmUsersClick(TObject *Sender);
	void __fastcall MnAdmLocationsClick(TObject *Sender);
	void __fastcall MnAdmLogsClick(TObject *Sender);
	void __fastcall MnAdmManageClick(TObject *Sender);
    void __fastcall ListenerExecute(TIdContext *AContext);
	void __fastcall ListenerConnect(TIdContext *AContext);
	void __fastcall ListenerDisconnect(TIdContext *AContext);
	void __fastcall CheckItemScannedCodeKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall PPEditClick(TObject *Sender);
	void __fastcall PPRemoveClick(TObject *Sender);
	void __fastcall CheckItemResultMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall CheckItemEditClick(TObject *Sender);
	void __fastcall CheckItemRemoveClick(TObject *Sender);
	void __fastcall ReconnectClick(TObject *Sender);
	void __fastcall CheckItemRefreshClick(TObject *Sender);
	void __fastcall AddItemCreateClick(TObject *Sender);
	void __fastcall AddItemClearFieldsClick(TObject *Sender);
	void __fastcall AddItemSelectLocationClick(TObject *Sender);
	void __fastcall PPSetPwdClick(TObject *Sender);
	void __fastcall PPRemoveUserClick(TObject *Sender);
	void __fastcall AdmUsersAddClick(TObject *Sender);
	void __fastcall AdmUsersSetPwdClick(TObject *Sender);
	void __fastcall AdmUsersRemoveClick(TObject *Sender);
	void __fastcall AdmLocationsAddClick(TObject *Sender);
	void __fastcall AdmLocationsEditClick(TObject *Sender);
	void __fastcall AdmLocationsRemoveClick(TObject *Sender);
	void __fastcall PPEditLocationClick(TObject *Sender);
	void __fastcall PPRemoveLocationClick(TObject *Sender);
	void __fastcall AdmLogsShowClick(TObject *Sender);
	void __fastcall PPCheckSetUnknownClick(TObject *Sender);
	void __fastcall PPRefreshClick(TObject *Sender);
	void __fastcall PPLocationsRefreshClick(TObject *Sender);
	void __fastcall PPAddLocationClick(TObject *Sender);
	void __fastcall ChangeMailClick(TObject *Sender);
	void __fastcall ChangePasswordClick(TObject *Sender);

private:	// User declarations
	void __fastcall ShowLoadingImage();
	void __fastcall HideLoadingImage();
	void __fastcall HideAllPanels();
	void __fastcall ParseXML(TXMLDocument *ixml);
	void __fastcall WriteSettings();
	void __fastcall ReadSettings();
	void __fastcall SetUIImages();
	TMemoryStream* __fastcall CryptData(String data, const char *pass);
	String __fastcall EncryptData(TMemoryStream *crypted_data, const char *pass);

public:		// User declarations
	__fastcall TClientForm(TComponent* Owner);

	void __fastcall LockUI();
	void __fastcall UnlockUI();

	void __fastcall AddActionLog(String status);

//створює об'єкт документу XML у пам'яті
	TXMLDocument *__fastcall CreatXMLStream(TStringStream *ms);
	TStringStream* __fastcall CreateRequest(const String &command, const String &params);
	TStringStream* __fastcall CreateRequest(const String &command);
//відправка запиту на сервер
	bool __fastcall SendToServer(const String &host, TStringStream *buffer);
//відправка запиту та очікування відповіді у той самий контекст підключення
	bool __fastcall AskToServer(const String &host, TStringStream *buffer);
    void __fastcall ProcessAnswer(TXMLDocument *ixml);
	void __fastcall ProcessRequest(TXMLDocument *ixml);
	void __fastcall GetServerVersion();
	bool __fastcall SetUserPassword(int user_id, const String &new_password);
	bool __fastcall ValidUserPassword(int user_id, const String &password);
	bool __fastcall SetUserMail(int user_id, const String &new_mail);
};
//---------------------------------------------------------------------------
extern PACKAGE TClientForm *ClientForm;

//---------------------------------------------------------------------------
#endif
