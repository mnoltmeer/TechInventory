/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\work-functions\MyFunc.h"
#include "..\..\work-functions\Cypher.h"
#include "..\..\work-functions\TCPRequester.h"
#include "Settings.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TServerForm *ServerForm;

const char *DataCryptKey = "D@t@Ha$hK3y";

extern String UsedAppLogDir; //вказуємо директорію для логування для функцій з MyFunc.h

String AppPath, LogFile, LogDir, DBHost, DBPath, DBPort, ServerName, Version;
int ListenPort, HideWnd, FullScreen;
TDate DateStart;
//---------------------------------------------------------------------------

__fastcall TServerForm::TServerForm(TComponent* Owner)
	: TForm(Owner)
{
  try
	 {
	   AppPath = GetDirPathFromFilePath(Application->ExeName);
	   UsedAppLogDir = "TIServer\\Log";
	   LogDir = GetEnvironmentVariable("USERPROFILE") + "\\Documents\\TIServer\\Log";

	   if (!DirectoryExists(LogDir))
		 ForceDirectories(LogDir);

	   DateStart = Date().CurrentDate();

	   LogFile = DateToStr(DateStart) + ".log";
	 }
  catch (Exception &e)
	 {
	   WriteLog(e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::WriteLog(String record)
{
  String rec = "["
				+ DateToStr(Date())
				+ " "
				+ TimeToStr(Time())
				+ "]"
				+ " : "
				+ record;

  SaveLog(LogDir + "\\" + LogFile, record);
  SendToLog(rec + "\r\n", Log);
  Log->Perform(WM_VSCROLL, SB_BOTTOM, 0);
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::FormCreate(TObject *Sender)
{
  if (FullScreen && !HideWnd)
	WindowState = wsMaximized;
  else if (HideWnd)
	WindowState = wsMinimized;

  SwServerOff->Show();
  Version = GetVersionInString(Application->ExeName.c_str());
  LbVersion->Caption = "Версія: " + Version;
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::FormShow(TObject *Sender)
{
  if (ReadSettings())
	{
      WriteLog("Початок роботи");

	  try
		 {
		   ConnectToDB();
		   StartServer();
		   PPStatus->Caption = "В мережі";
		   PPStatus->ImageIndex = 3;
		 }
	  catch (Exception &e)
		 {
		   WriteLog(e.ToString());
		   PPStatus->Caption = "Помилка";
		   PPStatus->ImageIndex = 4;
		 }
	}
  else
	{
	  MessageBox(Application->Handle,
				 L"Не всі параметри серверу налаштовані коректно. Відкрийте Налаштування та скорегуйте",
				 L"Сервер АС ТехІнвент", MB_OK|MB_ICONWARNING);

	  PPStatus->Caption = "Помилка";
      PPStatus->ImageIndex = 4;
	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  try
	 {
	   WriteSettings();

	   StopServer();
	   DisconnectFromDB();

	   WriteLog("Кінець роботи");
	 }
  catch (Exception &e)
	 {
	   WriteLog(e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::StartServer()
{
  try
	 {
	   Listener->DefaultPort = ListenPort;
	   Listener->Active = true;
	   WriteLog("Сервер запущено");

	   SwServerOn->Show();
	   SwServerOff->Hide();
	 }
  catch (Exception &e)
	 {
	   SwServerOn->Hide();
	   SwServerOff->Show();

	   WriteLog("Запуск серверу: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::StopServer()
{
  try
	 {
	   Listener->Active = false;
	   WriteLog("Сервер зупинено");

	   SwServerOff->Show();
	 }
  catch (Exception &e)
	 {
	   SwServerOff->Show();

	   WriteLog("Зупинка серверу: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ConnectToDB()
{
  if (!StatConnection->Connected)
	{
	  try
		 {
		   StatFBDriverLink->VendorLib = AppPath + "\\fbclient.dll";

		   StatConnection->Params->Clear();
		   StatConnection->Params->Add("User_Name=SYSDBA");
		   StatConnection->Params->Add("Password=masterkey");
		   StatConnection->Params->Add("Port=" + DBPort);
		   StatConnection->Params->Add("DriverID=myFB");
		   StatConnection->Params->Add("Protocol=TCPIP");
		   StatConnection->Params->Add("Database=" + DBPath);
		   StatConnection->Params->Add("Server=" + DBHost);
		   StatConnection->Params->Add("CharacterSet=UTF8");

		   StatConnection->Connected = true;
		   WriteLog("Підключено до: " + DBHost + ":" + DBPath);
         }
	  catch (Exception &e)
		 {
		   WriteLog("ConnectToDB(): " + e.ToString());
		 }
	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::DisconnectFromDB()
{
  if (StatConnection->Connected)
	{
	  try
		 {
		   WriteQuery->Active = false;
		   StatConnection->Connected = false;
		   WriteLog("Відключено від: " + DBHost + ":" + DBPath);
		 }
	  catch (Exception &e)
		 {
		   WriteLog("DisconnectFromDB(): " + e.ToString());
		 }
	}
}
//---------------------------------------------------------------------------

UserInfo __fastcall TServerForm::Authorisation(const String &login, const String &pass)
{
  UserInfo res;

  String sqltext = "SELECT ID, PASS, ROLE, MAIL FROM AGENTS";

  if (login != "")
	sqltext += " WHERE LOGIN = :login";
  else
	{
	  res.ID = -1;
	  return res;
    }

  std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
  std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

  try
	 {
	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("login")->AsString = login;

	   tmp_query->Prepare();
	   tmp_query->Open();
	   tmp_tr->Commit();
	   //WriteLog("Authorisation(): Record count = " + IntToStr(tmp_query->RecordCount));
	   if (tmp_query->RecordCount == 1)
		 {
		   tmp_query->First();

		   if (tmp_query->FieldByName("PASS")->AsString == pass)
			 {
			   res.ID = tmp_query->FieldByName("ID")->AsInteger;
			   res.Role = tmp_query->FieldByName("ROLE")->AsString;
			   res.Mail = tmp_query->FieldByName("MAIL")->AsString;
			   //WriteLog("Authorisation(): ID = " + tmp_query->FieldByName("ID")->AsString);
			 }
		   else
			 res.ID = -1;
		 }
	   else if (tmp_query->RecordCount > 1)
		 res.ID = -1;
	   else
		 res.ID = -1;

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res.ID = -1;
	   tmp_tr->Rollback();
	   WriteLog("Authorisation(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::ReadSettings()
{
  bool res = true;

  try
	 {
	   std::unique_ptr<TRegistry> reg(new TRegistry(KEY_READ));

	   reg->RootKey = HKEY_CURRENT_USER;

	   if (reg->OpenKey("Software\\TIServer\\Form", false))
		 {
		   if (reg->ValueExists("FullScreen"))
			 FullScreen = reg->ReadBool("FullScreen");
		   else
			 FullScreen = false;

		   if (reg->ValueExists("HideWindow"))
			 HideWnd = reg->ReadBool("HideWindow");
		   else
			 HideWnd = false;

		   if (reg->ValueExists("Height"))
			 ClientHeight = reg->ReadInteger("Height");
		   else
			 ClientHeight = 600;

		   if (reg->ValueExists("Width"))
			 ClientWidth = reg->ReadInteger("Width");
		   else
			 ClientWidth = 800;

		   reg->CloseKey();
		 }
	   else
		 res = false;

	   if (reg->OpenKey("Software\\TIServer\\Params", false))
		 {
		   if (reg->ValueExists("ListenPort"))
			 ListenPort = reg->ReadInteger("ListenPort");
		   else
			 ListenPort = DEFAULT_SERVER_PORT;

		   if (reg->ValueExists("ServerName"))
			 ServerName = reg->ReadString("ServerName");
		   else
			 ServerName = "<noname>";

		   if (reg->ValueExists("DBHost"))
			 DBHost = reg->ReadString("DBHost");

		   if (reg->ValueExists("DBPath"))
			 DBPath = reg->ReadString("DBPath");

		   if (reg->ValueExists("DBPort"))
			 DBPort = reg->ReadString("DBPort");
		   else
			 DBPort = "3050";

		   reg->CloseKey();
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("ReadSettings: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::WriteSettings()
{
  try
	 {
	   std::unique_ptr<TRegistry> reg(new TRegistry(KEY_WRITE));

	   reg->RootKey = HKEY_CURRENT_USER;

	   if (!reg->KeyExists("Software\\TIServer\\Form"))
		 reg->CreateKey("Software\\TIServer\\Form");

	   if (!reg->KeyExists("Software\\TIServer\\Params"))
		 reg->CreateKey("Software\\TIServer\\Params");

	   if (reg->OpenKey("Software\\TIServer\\Form", false))
		 {
		   reg->WriteInteger("Height", ClientHeight);
		   reg->WriteInteger("Width", ClientWidth);

		   if (WindowState == wsMaximized)
			 reg->WriteBool("FullScreen", FullScreen);
		   else
			 reg->WriteBool("FullScreen", false);

		   reg->CloseKey();
		 }

	   if (reg->OpenKey("Software\\TIServer\\Params", false))
		 {
		   reg->WriteInteger("ListenPort", ListenPort);
		   reg->WriteString("ServerName", ServerName);
		   reg->WriteString("DBHost", DBHost);
		   reg->WriteString("DBPath", DBPath);
		   reg->WriteString("DBPort", DBPort);

		   reg->CloseKey();
		 }
	 }
  catch (Exception &e)
	 {
	   WriteLog("WriteSettings: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

TMemoryStream* __fastcall TServerForm::CryptData(String data, const char *pass)
{
  TMemoryStream *res = new TMemoryStream();

  std::unique_ptr<TAESCypher> cypher(new TAESCypher(data, pass));

  res->LoadFromStream(cypher->Data);

  if (cypher->LastError != "")
	WriteLog("CryptData(): " + cypher->LastError);

  return res;
}
//---------------------------------------------------------------------------

String __fastcall TServerForm::EncryptData(TMemoryStream *crypted_data, const char *pass)
{
  String res;

  std::unique_ptr<TAESCypher> cypher(new TAESCypher(crypted_data, pass, coEncrypt));

  res = cypher->DataToString();

  if (cypher->LastError != "")
	WriteLog("EncryptData(): " + cypher->LastError);

  return res;
}
//---------------------------------------------------------------------------

TXMLDocument *__fastcall TServerForm::CreatXMLStream(TStringStream *ms)
{
  TXMLDocument *ixml;

  try
	 {
	   //if (CoInitializeEx(NULL, COINIT_MULTITHREADED) != S_OK)
		 //throw Exception("Помилка CoInitializeEx");

	   ixml = new TXMLDocument(this);

	   ixml->DOMVendor = GetDOMVendor(sOmniXmlVendor);
	   ixml->Active = true;
	   ixml->Encoding = "UTF-8";
	   ixml->Options = ixml->Options << doNodeAutoIndent;
	   ixml->LoadFromStream(ms, xetUTF_8);

       //CoUninitialize();
	 }
  catch (Exception &e)
	 {
	   WriteLog("CreatXMLStream(): " + e.ToString());
	   ixml = NULL;
	 }

  return ixml;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::SendToClient(const String &host, TStringStream *buffer)
{
  std::unique_ptr<TTCPRequester> sender(new TTCPRequester(host, DEFAULT_CLIENT_PORT));

  return sender->SendData(buffer);
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::ConnectToSMTP()
{
  MailSender->Username = "noname@ukrposhta.com";
  MailSender->Password = "noname";
  MailSender->Host = "127.0.0.1";
  MailSender->Port = 465;

  try
	{
	  MailSender->Connect();
	}
  catch (Exception &e)
	{
	  WriteLog("SMTP помилка: " + e.ToString());

	  return false;
	}

  return MailSender->Connected();
}
//-------------------------------------------------------------------------

void __fastcall TServerForm::SendMsg(String mail_addr, String subject, String from, String log)
{
  if (MailSender->Connected())
	{
	  std::unique_ptr<TIdMessage> msg(new TIdMessage(this));

	  msg->CharSet = "UTF-8";
	  msg->Body->Text = log;
	  msg->From->Text = from;
	  msg->Recipients->EMailAddresses = mail_addr;
	  msg->Subject = subject;
	  msg->Priority = TIdMessagePriority(mpHighest);

	  MailSender->Send(msg.get());
	  MailSender->Disconnect();
	}
}
//-------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::CreateRequest(const String &command,
													  const String &params)
{
  TStringStream *ms;

  try
	 {
	   ms = new TStringStream("", TEncoding::UTF8, true);

	   ms->WriteString("<Request>");
	   ms->WriteString("<Command>" + command + "</Command>");
	   ms->WriteString("<Params>");

	   std::unique_ptr<TStringList> lst(new TStringList());

	   StrToList(lst.get(), params, ";");

	   for (int i = 0; i < lst->Count; i++)
		  ms->WriteString("<Param>" + lst->Strings[i] + "</Param>");

	   ms->WriteString("</Params>");
       ms->WriteString("</Request>");
	 }
  catch (Exception &e)
	 {
	   WriteLog("CreateRequest(" + command + "): " + e.ToString());

       if (ms) {delete ms;}

	   ms = NULL;
	 }

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::ParseXML(TXMLDocument *ixml)
{
  TStringStream *res;

  try
	 {
	   _di_IXMLNode Document = ixml->DocumentElement; //тип документу (запит/відповідь)

	   if (Document->GetNodeName() == "Answer")
		 {
		   //оброблюємо відповідь
		   ProcessAnswer(ixml);
		 }
	   else if (Document->GetNodeName() == "Request")
		 {
		   //оброблюємо запит
		   res = ProcessRequest(ixml);
		 }
	   else
		 {
		   //прийшла якась фігня
		   throw Exception("Невідомий тип XML-документу");
		 }
	 }
  catch (Exception &e)
	 {
	   res = NULL;
	   WriteLog("ParseXML: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::ProcessRequest(TXMLDocument *ixml)
{
  TStringStream *res;

  try
	 {
	   _di_IXMLNode Document = ixml->DocumentElement; //тип документу (запит/відповідь)
	   _di_IXMLNode Command; //команда (вказує для чого призначені дані)

	   _di_IXMLNode Params; //позначає секцію з даними
	   _di_IXMLNode Param;

	   Command = Document->ChildNodes->Nodes[0];
	   Params = Document->ChildNodes->Nodes[1];

	   String command;

	   command = Command->NodeValue;

	   std::unique_ptr<TStringList> params(new TStringList());

	   for (int i = 0; i < Params->ChildNodes->Count; i++)
		  {
			Param = Params->ChildNodes->Nodes[i];
			params->Add(Param->NodeValue);
		  }

	   res = ExecuteCommand(command, params.get());
	 }
  catch (Exception &e)
	 {
       res = NULL;
	   WriteLog("ProcessRequest: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::ExecuteCommand(const String &command,
													   TStringList *params)
{
  TStringStream *res;

  try
	 {
//за командою визначаємо потрібний запит до БД і виконуємо його
	   if (command == "AUTH")
		 {
		   UserInfo user = Authorisation(params->Strings[0], params->Strings[1]);

		   if (user.ID < 0)
			 res = CreateAnswer("DENIED", "");
		   else
			 res = CreateAnswer("GRANTED", IntToStr(user.ID) + ";" + user.Role + ";" + user.Mail);
		 }
	   else if (command == "GETVERSION")
		 {
		   res = CreateAnswer("SERVERVERSION", Version);
         }
	 }
  catch (Exception &e)
	 {
       if (res) delete res;
	   res = NULL;
	   WriteLog("ExecuteCommand: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::CreateAnswer(const String &command,
													 TStringList *data)
{
  TStringStream *res;

  try
	 {
	   res = new TStringStream("", TEncoding::UTF8, true);

	   res->WriteString("<Answer>");
	   res->WriteString("<Command>" + command + "</Command>");
	   res->WriteString("<Titles></Titles>");
	   res->WriteString("<Data>");

	   std::unique_ptr<TStringList> fields(new TStringList());

	   for (int i = 0; i < data->Count; i++)
		  {
			res->WriteString("<Row>");

			StrToList(fields.get(), data->Strings[i], ";"); //розбиваємо рядок на стовпці

			for (int j = 0; j < fields->Count; j++)
			   res->WriteString("<Field>" + fields->Strings[j] + "</Field>");

			res->WriteString("</Row>");
		  }

	   res->WriteString("</Data>");
	   res->WriteString("</Answer>");
	 }
  catch (Exception &e)
	 {
       if (res) delete res;
	   res = NULL;
	   WriteLog("CreateAnswer: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::CreateAnswer(const String &command,
													 const String &data)
{
  TStringStream *res;

  try
	 {
	   res = new TStringStream("", TEncoding::UTF8, true);

	   res->WriteString("<Answer>");
	   res->WriteString("<Command>" + command + "</Command>");
	   res->WriteString("<Titles></Titles>");
	   res->WriteString("<Data>");

	   std::unique_ptr<TStringList> rows(new TStringList());
	   std::unique_ptr<TStringList> fields(new TStringList());

	   StrToList(rows.get(), data, ";"); //розбиваємо дані на рядки

	   for (int i = 0; i < rows->Count; i++)
		  {
			res->WriteString("<Row>");

			StrToList(fields.get(), rows->Strings[i], ";"); //розбиваємо рядок на стовпці

			for (int j = 0; j < fields->Count; j++)
			   res->WriteString("<Field>" + fields->Strings[j] + "</Field>");

			res->WriteString("</Row>");
		  }

	   res->WriteString("</Data>");
	   res->WriteString("</Answer>");
	 }
  catch (Exception &e)
	 {
       if (res) delete res;
	   res = NULL;
	   WriteLog("CreateAnswer: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::CreateAnswer()
{
  TStringStream *res;

  try
	 {
	   //беремо дані з джерела даних і формуємо xml-доку
	   TStringStream *answer = new TStringStream("", TEncoding::UTF8, true);

	   //визначаємо, чи треба надсилати відповідь одразу, чи окремими пакетом
	   if (1) //треба надіслати відповідь одразу
		 res = answer;
	   else //відповідь надсилається в окремому потоку
		 {
		   delete answer;
           answer = NULL;
		 }
	 }
  catch (Exception &e)
	 {
	   if (res) delete res;

	   res = NULL;
	   WriteLog("CreateAnswer: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ProcessAnswer(TXMLDocument *ixml)
{
  try
	 {
	   _di_IXMLNode Document = ixml->DocumentElement; //тип документу (запит/відповідь)
	   _di_IXMLNode Command; //команда (вказує для чого призначені дані)

	   _di_IXMLNode Data; //позначає секцію з даними
	   _di_IXMLNode Row;
	   _di_IXMLNode Field;

	   Command = Document->ChildNodes->Nodes[0];
	   Data = Document->ChildNodes->Nodes[1];

	   String datatype, value;

	   for (int i = 0; i < Data->ChildNodes->Count; i++)
		  {
			Row = Data->ChildNodes->Nodes[i];

			for (int j = 0; j < Row->ChildNodes->Count; j++)
			   {
				 Field = Row->ChildNodes->Nodes[j];

				 datatype = Field->GetAttribute("type");
				 value = Field->NodeValue;
			   }
		  }
	 }
  catch (Exception &e)
	 {
	   WriteLog("ProcessAnswer: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ListenerExecute(TIdContext *AContext)
{
  std::unique_ptr<TStringStream> ms(new TStringStream("", TEncoding::UTF8, true));
  std::unique_ptr<TXMLDocument> ixml(nullptr);
  std::unique_ptr<TStringStream> answer(nullptr);

  AContext->Connection->IOHandler->ReadStream(ms.get());

  try //читаємо дані, що надійшли
	 {
	   ms->LoadFromStream(TSAESCypher::Encrypt(ms.get(), DataCryptKey));
	   ms->Position = 0;
	   WriteLog(ms->ReadString(ms->Size));
	 }
  catch (Exception &e)
	 {
	   WriteLog("ConnectionServerExecute: Розшифровка вхідних даних: " + e.ToString());
	 }

  try //визначаємо тип запиту та оброблюємо його
	 {
	   ms->Position = 0;

	   ixml.reset(CreatXMLStream(ms.get()));
	   answer.reset(ParseXML(ixml.get()));

	   answer->Position = 0;
	   WriteLog("Answer: " + answer->ReadString(answer->Size));
	 }
  catch (Exception &e)
	{
	  WriteLog("ConnectionServerExecute: Парсинг: " + e.ToString());
	}

  if (answer) //якщо відповідь сформовано одразу - надсилаємо її клієнту
	{
	  try
		 {
		   answer->Position = 0;
		   WriteLog("Відправка даних: " + answer->ReadString(answer->Size));
		   answer->Position = 0;
		   answer->LoadFromStream(TSAESCypher::Crypt(answer.get(), DataCryptKey));
		   answer->Position = 0;
		 }
	  catch (Exception &e)
		 {
		   WriteLog("ConnectionServerExecute: Шифровка вихідних даних: " + e.ToString());
		 }

	  try
		 {
		   WriteLog("Відправка даних");
		   answer->Position = 0;
		   AContext->Connection->IOHandler->Write(answer.get(), answer->Size, true);
		 }
	  catch (Exception &e)
		 {
		   WriteLog("ConnectionServerExecute: Відправка даних: " + e.ToString());
		 }
	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ListenerConnect(TIdContext *AContext)
{
  //клієнт під'єднався
  WriteLog("Підключився клієнт: " + AContext->Binding->PeerIP);
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ListenerDisconnect(TIdContext *AContext)
{
  //клієнт від'єднався
  WriteLog("Відключився клієнт: " + AContext->Binding->PeerIP);
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::SettingsClick(TObject *Sender)
{
  SettingsForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::MainPopupMenuPopup(TObject *Sender)
{
  if (Listener->Active)
	PPStatus->ImageIndex = 3;
  else
    PPStatus->ImageIndex = 4;
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::PPShowWindowClick(TObject *Sender)
{
  if ((WindowState == wsMaximized) || (WindowState == wsNormal))
	{
	  Hide();
	  WindowState = wsMinimized;
	}
  else if (FullScreen)
	{
	  WindowState = wsMaximized;
	  Show();
	}
  else
	{
	  WindowState = wsNormal;
      Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::PPCloseClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::TrayIconDblClick(TObject *Sender)
{
  PPShowWindow->Click();
}
//---------------------------------------------------------------------------

TFDTransaction *CreateNewTransactionObj()
{
  TFDTransaction *t = new TFDTransaction(NULL);

  t->Connection = ServerForm->StatConnection;
  t->Options->AutoCommit = false;
  t->Options->AutoStart = false;
  t->Options->AutoStop = false;
  t->Options->DisconnectAction = xdRollback;
  t->Options->Isolation = xiSnapshot;

  return t;
}
//---------------------------------------------------------------------------

TFDQuery *CreateNewQueryObj(TFDTransaction *t)
{
  TFDQuery * q = new TFDQuery(NULL);

  q->Connection = ServerForm->StatConnection;
  q->Transaction = t;

  return q;
}
//---------------------------------------------------------------------------



