//---------------------------------------------------------------------------
#ifndef servH
#define servH
//---------------------------------------------------------------------------
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.SvcMgr.hpp>
#include <vcl.h>
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
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdContext.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdHTTPServer.hpp>
#include <System.ImageList.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
//---------------------------------------------------------------------------

#define CookieValidDays 15
#define BUILD_APP
#define ROLE_ADMIN true
#define ROLE_USER false

enum ResultPageType {
RT_ITEM = 0,
RT_HIST = 1,
RT_EDIT = 2,
RT_USER = 3,
RT_SESS = 4
};

enum OperationType {
OT_ADD = 1,	    //Ввод нового пристрою
OT_REMOVE = 2,  //Вивід з експлуатації
OT_CH_INN = 3,  //Зміна інвентарного номеру
OT_CH_SN = 4,   //Зміна серійного номеру
OT_CH_MODEL = 5,//Зміна моделі пристрою
OT_CH_LOC = 6   //Зміна локації пристрою
};

typedef __stdcall const wchar_t *(*ENCRYPTTEXT)(const wchar_t*, const char*);
ENCRYPTTEXT EncryptText;

typedef __stdcall const wchar_t *(*DECRYPTTEXT)(const wchar_t*, const char*);
DECRYPTTEXT DecryptText;

class TTechService : public TService
{
__published:    // IDE-managed Components
	TFDConnection *StatConnection;
	TFDTransaction *WriteTransaction;
	TFDQuery *WriteQuery;
	TFDPhysFBDriverLink *StatFBDriverLink;
	TIdHTTPServer *HttpServer;
	TTimer *RemSessionTimer;
	void __fastcall HttpServerCommandGet(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
          TIdHTTPResponseInfo *AResponseInfo);
	void __fastcall ServiceExecute(TService *Sender);
	void __fastcall ServiceStop(TService *Sender, bool &Stopped);
	void __fastcall RemSessionTimerTimer(TObject *Sender);
	void __fastcall ServiceStart(TService *Sender, bool &Started);

private:        // User declarations
	void __fastcall ConnectToDB();
	void __fastcall DisconnectFromDB();
	void __fastcall StartHttpServer();
	void __fastcall StopHttpServer();

	TStringStream* __fastcall RequestHistory(TStringStream *ms,
											 String p_inn,
											 String p_sn,
											 String p_datefrom,
											 String p_dateto,
											 String p_sortby);
	TStringStream* __fastcall RequestAllChanges(TStringStream *ms);
	TStringStream* __fastcall RequestAllItems(TStringStream *ms);
	TStringStream* __fastcall RequestItem(TStringStream *ms,
										  const String &inn,
										  const String &sn);
	TStringStream* __fastcall RequestItems(TStringStream *ms,
										   const String &ind);
	TStringStream* __fastcall RequestUsers(TStringStream *ms);
	TStringStream* __fastcall RequestSessions(TStringStream *ms);
    TStringStream* __fastcall RequestLog(const String &date, TStringStream *ms);

//додає дані пристрою у БД
	int __fastcall AddItem(const String &inn, const String &sn,
						   const String &model, const String &loc_id,
                           int user_id,
						   TStringStream *ms);
//виводить Пристрій з експлуатації, переносить його у локацію 00000
	void __fastcall RemoveItem(const String &id, int user_id, TStringStream *ms);
//формує сторінку з даними Пристрою та дає можливість редагувати їх
	void __fastcall EditItem(const String &id, TStringStream *ms);
//вносить зміни по даним Пристрою у БД
	void __fastcall SetItem(const String &id,
							const String &inn, const String &sn,
							const String &model, const String &loc_id,
							int user_id,
							TStringStream *ms);
//встановлює ід Агента що змінив дані про Пристрій у таблицю Пристроїв
	void __fastcall SetChangingAgent(int itm_id, int user_id);
	void __fastcall ReadSettings();
	void __fastcall SendLogToConsole(const String &msg);

	void __fastcall GenerateResultPage(ResultPageType type,
									   TFDQuery *dataset,
									   TStringStream *output);
	void __fastcall GenerateErrorPage(String error, TStringStream *output);
	void __fastcall GenerateSuccessPage(String msg, TStringStream *output);
	void __fastcall GenerateLocationList(TStringStream *output);

	void __fastcall AddHistoryRecord(int agent_id, OperationType operation_id, int item_id);

//авторизує користувача, якщо успішно повертає ІД Агента, інакше повертає 0
	int __fastcall Authorisation(const String &login, const String &pass, TStringStream *ms);
//якщо Агент авторизований успішно повертає ІД Агента, інакше повертає 0
	int __fastcall Authorised(TIdHTTPRequestInfo *RequestInfo);
//якщо хеш сессії дійсний повертає ІД Агента, що прив'язаний до сесії, інакше повертає 0
	int __fastcall IsValidSessionID(const String &cookie_hash);
//додає нову сесію в БД, повертає ІД сесії (не хеш)
	int __fastcall AddSessionID(const String &session_hash, int user_id);
//видаляє сессію зі списку, коли користувач виходить з системи
	void __fastcall RemoveSessionID(const String &session_hash, int user_id);
//просто видаляє сесію з БД (для адміна)
	void __fastcall RemoveSessionID(const String &session_id);
//генерує хеш сесії - символьний рядок довжиною 32 символу
//за базу для хешу береться поточне значення дати (включно з мілісекундами)
	String __fastcall GenerateSessionHash();
//видаляє з БД сессії, старіші за CookieValidDays
	void __fastcall RemoveOldSessions();
	bool __fastcall IsAdmin(int user_id);
	int __fastcall CheckAuthAndLoad(const String &page_file,
                                    bool check_admin,
									TIdHTTPRequestInfo *RequestInfo,
									TStringStream *ms);
	int __fastcall CheckAuth(bool check_admin,
							 TIdHTTPRequestInfo *RequestInfo,
							 TStringStream *ms);
	void __fastcall AddUser(const String &login,
							const String &pass,
                            const String &name,
							const String &role,
							TStringStream *ms);
	void __fastcall RemoveUser(int user_id, TStringStream *ms);
	void __fastcall SetUserPwd(int user_id,
							   const String &pass,
							   TStringStream *ms);
//повертає шифрований AuthID користувача, що зберігається у БД
	String __fastcall GetUserPwd(int user_id);

	bool __fastcall LoadCryptoDLL();
	void __fastcall UnLoadCryptoDLL();
//шифрує ідентифікатор, отриманий від користувача
	String __fastcall CryptUserPassword(const String &pass);

public:         // User declarations
	__fastcall TTechService(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);

	friend void __stdcall ServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TTechService *TechService;
//---------------------------------------------------------------------------

TFDTransaction *CreateNewTransactionObj();
TFDQuery *CreateNewQueryObj(TFDTransaction *);
void DeleteTransactionObj(TFDTransaction *t);
void DeleteQueryObj(TFDQuery *q);
//---------------------------------------------------------------------------
#endif
