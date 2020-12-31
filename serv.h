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
//#include <System.ImageList.hpp>
//#include <Vcl.Controls.hpp>
//#include <Vcl.ExtCtrls.hpp>
//#include <Vcl.ImgList.hpp>
//#include <Vcl.Menus.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdMessageClient.hpp>
#include <IdSMTP.hpp>
#include <IdSMTPBase.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Xml.adomxmldom.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.xmldom.hpp>
#include <Xml.XMLIntf.hpp>
#include <Xml.Win.msxmldom.hpp>
//---------------------------------------------------------------------------

#define ROLE_ADMIN true
#define ROLE_USER false
#define DEFAULT_SERVER_PORT 9874
#define DEFAULT_CLIENT_PORT 9875

const char *AccCryptKey = "U$erHa$hK3y";
const char *DataCryptKey = "D@t@Ha$hK3y";

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
	TIdSMTP *MailSender;
	TIdTCPServer *ConnectionServer;
	TFDStoredProc *StoredProc;
	void __fastcall ServiceExecute(TService *Sender);
	void __fastcall ServiceStop(TService *Sender, bool &Stopped);
	void __fastcall ServiceStart(TService *Sender, bool &Started);
	void __fastcall ConnectionServerExecute(TIdContext *AContext);
	void __fastcall ConnectionServerConnect(TIdContext *AContext);
	void __fastcall ConnectionServerDisconnect(TIdContext *AContext);

private:        // User declarations
	void __fastcall ConnectToDB();
	void __fastcall DisconnectFromDB();
	void __fastcall StartServer();
	void __fastcall StopServer();

//�������� �����������, ���� ������ ������� �� ������ �� ����, ������ ������� NULL
	UserInfo __fastcall Authorisation(const String &login, const String &pass);

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
	TStringStream* __fastcall RequestLog(const String &date, TStringStream *ms);
	TStringStream* __fastcall RequestLocations(TStringStream *ms);

//���� ��� �������� � ��
	int __fastcall AddItem(const String &inn, const String &sn,
						   const String &model, const String &loc_id,
                           int user_id,
						   TStringStream *ms);
//�������� ������� � ������������, ���������� ���� � ������� 00000
	void __fastcall RemoveItem(const String &id, int user_id, TStringStream *ms);
//����� ������� � ������ �������� �� �� ��������� ���������� ��
	void __fastcall EditItem(const String &id, TStringStream *ms);
//������� ���� �� ����� �������� � ��
	void __fastcall SetItem(const String &id,
							const String &inn, const String &sn,
							const String &model, const String &loc_id,
							int user_id,
							TStringStream *ms);
//���������� �� ������ �� ����� ��� ��� ������� � ������� ��������
	void __fastcall SetChangingAgent(int itm_id, int user_id);
	void __fastcall ReadSettings();
	void __fastcall SendLogToConsole(const String &msg);
	void __fastcall GenerateLocationList(TStringStream *output);
	void __fastcall AddHistoryRecord(int agent_id, OperationType operation_id, int item_id);
	void __fastcall RemoveLocationID(const String &loc_id);
//������ ����� ��� ����������� ����� �������
	void __fastcall EditLocationID(const String &loc_id, TStringStream *ms);
	void __fastcall SetLocationID(const String &id,
								  const String &index,
								  const String &addr,
								  TStringStream *ms);
	int __fastcall AddLocationID(const String &index, const String &addr, TStringStream *ms);
	bool __fastcall IsAdmin(int user_id);
	void __fastcall AddUser(const String &login,
							const String &pass,
                            const String &name,
							const String &role,
							TStringStream *ms);
	void __fastcall RemoveUser(int user_id, TStringStream *ms);
	void __fastcall SetUserPwd(int user_id,
							   const String &pass,
							   TStringStream *ms);
//������� ���������� AuthID �����������, �� ���������� � ��
	String __fastcall GetUserPwd(int user_id);

	bool __fastcall LoadCryptoDLL();
	void __fastcall UnLoadCryptoDLL();
//����� �������������, ��������� �� �����������
	String __fastcall CryptUserPassword(const String &pass);

    bool __fastcall ConnectToSMTP();
	void __fastcall SendMsg(String mail_addr, String subject, String from, String log);
	int __fastcall SendToClient(const wchar_t *host, TStringStream *buffer);

//������� ��������, �� �������, �������� ���� � ������� ProcessAnswer() ��� ProcessRequest()
//��� ������ ������ ������� ������� � ������ xml-�����
	TStringStream* __fastcall ParseXML(TXMLDocument *ixml);
//�������� ������� �볺��� �� ������ ������� 䳿
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
