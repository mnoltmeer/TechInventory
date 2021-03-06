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

extern String UsedAppLogDir; //������� ��������� ��� ��������� ��� ������� � MyFunc.h

String AppPath, LogFile, LogDir, DBHost, DBPath, DBPort, ServerName, Version, MailServer, SenderName;
int ListenPort, HideWnd, FullScreen, MailPort;
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
  LbVersion->Caption = "�����: " + Version;
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::FormShow(TObject *Sender)
{
  if (ReadSettings())
	{
      WriteLog("������� ������");

	  try
		 {
		   ConnectToDB();
		   StartServer();
		   PPStatus->Caption = "� �����";
		   PPStatus->ImageIndex = 3;
		 }
	  catch (Exception &e)
		 {
		   WriteLog(e.ToString());
		   PPStatus->Caption = "�������";
		   PPStatus->ImageIndex = 4;
		 }
	}
  else
	{
	  MessageBox(Application->Handle,
				 L"�� �� ��������� ������� ����������� ��������. ³������� ������������ �� ����������",
				 L"������ �� ���������", MB_OK|MB_ICONWARNING);

	  PPStatus->Caption = "�������";
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

	   WriteLog("ʳ���� ������");
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
	   WriteLog("������ ��������");

	   SwServerOn->Show();
	   SwServerOff->Hide();
	 }
  catch (Exception &e)
	 {
	   SwServerOn->Hide();
	   SwServerOff->Show();

	   WriteLog("������ �������: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::StopServer()
{
  try
	 {
	   Listener->Active = false;
	   WriteLog("������ ��������");

	   SwServerOff->Show();
	 }
  catch (Exception &e)
	 {
	   SwServerOff->Show();

	   WriteLog("������� �������: " + e.ToString());
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
		   WriteLog("ϳ�������� ��: " + DBHost + ":" + DBPath);
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
		   StatConnection->Connected = false;
		   WriteLog("³�������� ��: " + DBHost + ":" + DBPath);
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

  try
	 {
	   if (pass == "")
		 throw Exception("�������� ������");

	   if (login == "")
		 throw Exception("�������� ����");

	   String sqltext = "SELECT ID, PASS, ROLE, MAIL FROM AGENTS WHERE LOGIN = :login";

	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("login")->AsString = login;

	   tmp_query->Prepare();
	   tmp_query->Open();
	   tmp_tr->Commit();

	   if (tmp_query->RecordCount == 1)
		 {
		   tmp_query->First();

		   if (tmp_query->FieldByName("PASS")->AsString == pass)
			 {
			   res.ID = tmp_query->FieldByName("ID")->AsInteger;
			   res.Role = tmp_query->FieldByName("ROLE")->AsString;
			   res.Mail = tmp_query->FieldByName("MAIL")->AsString;
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
	   WriteLog("Authorisation(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::IsLoginFree(const String &login)
{
  bool res;

  try
	 {
	   if (login == "")
		 throw Exception("�������� ����");

	   String sqltext = "SELECT ID FROM AGENTS WHERE LOGIN = :login";

       std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("login")->AsString = login;

	   tmp_query->Prepare();
	   tmp_query->Open();
	   tmp_tr->Commit();

	   if (tmp_query->RecordCount > 0)
		 res = false;
	   else
		 res = true;

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("IsLoginFree(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::Registration(const String &login,
										  const String &pass,
										  const String &mail)
{
//��������� ������ �����������
  bool res;

  try
	 {
	   if (pass == "")
		 throw Exception("�������� ������");

	   if (login == "")
		 throw Exception("�������� ����");

       if (mail == "")
		 throw Exception("�������� email");

	   String sqltext = "INSERT INTO AGENTS (ID, LOGIN, PASS, ROLE, MAIL) VALUES (\
GEN_ID(GEN_AGENTS_ID, 1), :login, :pass, 'agent', :mail)";

	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("login")->AsString = login;
	   tmp_query->ParamByName("pass")->AsString = pass;
	   tmp_query->ParamByName("mail")->AsString = mail;

	   tmp_query->Prepare();
	   tmp_query->Execute();
	   tmp_tr->Commit();

	   if (tmp_query->RowsAffected > 0)
		 res = true;
	   else
		 res = false;

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("Registration(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::SetUserPassword(int user_id, const String &new_password)
{
  bool res;

  try
	 {
       if (new_password == "")
		 throw Exception("�������� ������");

	   String sqltext = "UPDATE AGENTS SET PASS = :pass WHERE ID = :userid";

	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("userid")->AsInteger = user_id;
	   tmp_query->ParamByName("pass")->AsString = new_password;

	   tmp_query->Prepare();
	   tmp_query->Execute();
	   tmp_tr->Commit();

	   if (tmp_query->RowsAffected > 0)
		 res = true;
	   else
		 res = false;

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("SetUserPassword(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::ValidUserPassword(int user_id, const String &password)
{
  bool res;

  try
	 {
       if (password == "")
		 throw Exception("�������� ������");

	   String sqltext = "SELECT ID FROM AGENTS WHERE ID = :userid AND PASS = :pass";

	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("userid")->AsInteger = user_id;
	   tmp_query->ParamByName("pass")->AsString = password;

	   tmp_query->Prepare();
	   tmp_query->Open();
	   tmp_tr->Commit();

	   if (tmp_query->RecordCount > 0)
		 res = true;
	   else
		 res = false;

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("SetUserPassword(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::SetUserMail(int user_id, const String &new_mail)
{
  bool res;

  try
	 {
	   if (new_mail == "")
		 throw Exception("������� ������ ��. �����");

	   String sqltext = "UPDATE AGENTS SET MAIL = :mail WHERE ID = :userid";

	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("userid")->AsInteger = user_id;
	   tmp_query->ParamByName("mail")->AsString = new_mail;

	   tmp_query->Prepare();
	   tmp_query->Execute();
	   tmp_tr->Commit();

	   if (tmp_query->RowsAffected > 0)
		 res = true;
	   else
		 res = false;

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("SetUserPassword(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::GetItem(int item_id)
{
  TStringStream *res;

  try
	 {
	   String sqltext = "SELECT itm.INN, itm.SN, itm.MODEL, ag.LOGIN, \
loc.IND || ' ' || loc.ADDRESS as LOCATION FROM Items itm \
LEFT JOIN Agents ag ON itm.LAST_AGENT_ID = ag.ID \
LEFT JOIN LOCATIONS loc ON loc.ID = itm.LOCATION_ID \
WHERE itm.ID = :itemid";

	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("itemid")->AsInteger = item_id;

	   tmp_query->Prepare();
	   tmp_query->Open();
	   tmp_tr->Commit();

	   if (tmp_query->RecordCount == 0)
		 res = CreateAnswer("NODATA");
	   else
		 {
		   std::unique_ptr<TStringList> data(new TStringList());

		   tmp_query->First();

		   data->Add(tmp_query->FieldByName("INN")->AsString);
		   data->Add(tmp_query->FieldByName("SN")->AsString);
		   data->Add(tmp_query->FieldByName("MODEL")->AsString);
		   data->Add(tmp_query->FieldByName("LOGIN")->AsString);
		   data->Add(tmp_query->FieldByName("LOCATION")->AsString);

		   for (int i = 0; i < data->Count; i++)
			  {
				if (data->Strings[i] == "")
				  data->Strings[i] = "???";
			  }

		   String str = ListToStr(data.get(), ";");
		   data->Clear();
		   data->Add(str);

		   res = CreateAnswer("SUCCESS", "", data.get());
		 }

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res = CreateAnswer("ERROR");
	   WriteLog("GetItem(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::SetItem(int item_id, const String &inn, const String &sn,
									 const String &model, int location_id, int agent_id)
{
  bool res;

  try
     {
	   String sqltext = "UPDATE ITEMS SET INN = :inn, \
SN = :sn, \
MODEL = :model, \
LOCATION_ID = :location, \
LAST_AGENT_ID = :agent \
WHERE ID = :itemid";

	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->ParamByName("itemid")->AsInteger = item_id;
	   tmp_query->ParamByName("inn")->AsString = inn;
	   tmp_query->ParamByName("sn")->AsString = sn;
	   tmp_query->ParamByName("model")->AsString = model;
	   tmp_query->ParamByName("location")->AsInteger = location_id;
       tmp_query->ParamByName("agent")->AsInteger = agent_id;

	   tmp_query->Prepare();
	   tmp_query->Execute();
	   tmp_tr->Commit();

	   if (tmp_query->RowsAffected > 0)
		 res = true;
	   else
		 res = false;

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("SetItem(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::GetLocationList()
{
  TStringStream *res;

  try
	 {
	   String sqltext = "SELECT * FROM Locations itm ORDER BY IND";

	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(sqltext);

	   tmp_query->Open();
	   tmp_tr->Commit();

	   if (tmp_query->RecordCount == 0)
		 res = CreateAnswer("NODATA");
	   else
		 {
		   std::unique_ptr<TStringList> data(new TStringList());
		   std::unique_ptr<TStringList> row(new TStringList());

		   tmp_query->First();

		   String str;

		   while (!tmp_query->Eof)
			 {
               row->Clear();

			   row->Add(tmp_query->FieldByName("ID")->AsString);
			   row->Add(tmp_query->FieldByName("IND")->AsString);
			   row->Add(tmp_query->FieldByName("ADDRESS")->AsString);

			   for (int i = 0; i < row->Count; i++)
				  {
					if (row->Strings[i] == "")
					  row->Strings[i] = "???";
				  }

			   str = ListToStr(row.get(), ";");

			   data->Add(str);

               tmp_query->Next();
			 }

		   String titles = "<Title size='0'>ID</Title>\
<Title size='50'>������</Title>\
<Title size='300'>������</Title>";

		   res = CreateAnswer("SUCCESS", titles, data.get());
		 }

	   tmp_query->Close();
	 }
  catch (Exception &e)
	 {
	   res = CreateAnswer("ERROR");
	   WriteLog("GetItem(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::ConnectToSMTP()
{
  MailSender->Username = "<none>";
  MailSender->Password = "<none>";
  MailSender->Host = "10.255.131.122";
  MailSender->Port = 25;

  try
	{
	  MailSender->Connect();
	}
  catch (Exception &e)
	{
	  WriteLog("SMTP �������: " + e.ToString());

	  return false;
	}

  return MailSender->Connected();
}
//-------------------------------------------------------------------------

bool __fastcall TServerForm::SendMsg(String mail_addr, String subject, String from, String text)
{
  bool res;

  if (ConnectToSMTP())
	{
	  std::unique_ptr<TIdMessage> msg(new TIdMessage(nullptr));

      try
		 {
		   msg->CharSet = "windows-1251";
		   msg->Body->Text = text;
		   msg->From->Text = from;
		   msg->Recipients->EMailAddresses = mail_addr;
		   msg->Subject = subject;
		   msg->Priority = TIdMessagePriority(mpHighest);

		   MailSender->Send(msg.get());
		   MailSender->Disconnect();
           res = true;
		 }
	  catch (Exception &e)
		 {
		   WriteLog("SendMsg: " + e.ToString());
		   res = false;
		 }
	}
  else
	res = false;

  return res;
}
//-------------------------------------------------------------------------

String __fastcall TServerForm::GenerateVerificationCode()
{
  String res = IntToStr(Random(10000));

  while (res.Length() < 4)
	res = "0" + res;

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::SendVerificationCode(const String &mail, const String &code)
{
  if (code == "")
	{
	  WriteLog("SendVerificationCode: ��� ��������");

	  return false;
	}
  else
	return SendMsg(mail, "Verification code", "TechInvent@ukrposhta.ua", code);
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

		   if (reg->ValueExists("MailPort"))
			 MailPort = reg->ReadInteger("MailPort");
		   else
			 MailPort = 25;

		   if (reg->ValueExists("MailServer"))
			 MailServer = reg->ReadString("MailServer");
		   else
			 MailServer = "127.0.0.1";

		   if (reg->ValueExists("SenderName"))
			 SenderName = reg->ReadString("SenderName");
		   else
			 SenderName = "noname@mail.sample";

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
		   reg->WriteInteger("MailPort", MailPort);
		   reg->WriteString("MailServer", MailServer);
		   reg->WriteString("SenderName", SenderName);

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
		 //throw Exception("������� CoInitializeEx");

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
	   _di_IXMLNode Document = ixml->DocumentElement; //��� ��������� (�����/�������)

	   if (Document->GetNodeName() == "Answer")
		 {
		   //���������� �������
		   ProcessAnswer(ixml);
		 }
	   else if (Document->GetNodeName() == "Request")
		 {
		   //���������� �����
		   res = ProcessRequest(ixml);
		 }
	   else
		 {
		   //������� ����� �����
		   throw Exception("�������� ��� XML-���������");
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
	   _di_IXMLNode Document = ixml->DocumentElement; //��� ��������� (�����/�������)
	   _di_IXMLNode Command; //������� (����� ��� ���� ���������� ����)

	   _di_IXMLNode Params; //������� ������ � ������
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
//�� �������� ��������� �������� ����� �� �� � �������� ����
	   if (command == "AUTH") //�������������� �����������
		 {
		   UserInfo user = Authorisation(params->Strings[0], params->Strings[1]);

		   if (user.ID < 0)
			 res = CreateAnswer("DENIED");
		   else
			 {
			   WriteLog("������ ����������: " + params->Strings[0]);

			   res = CreateAnswer("GRANTED", IntToStr(user.ID) + ";" + user.Role + ";" + user.Mail);
			 }
		 }
	   else if (command == "GETVERSION") //����� ���� �������
		 {
		   res = CreateAnswer(Version);
		 }
	   else if (command == "CHECKLOGIN") //�������� ����� �� ���������
		 {
		   if (IsLoginFree(params->Strings[0]))
			 res = CreateAnswer("FREE");
		   else
			 res = CreateAnswer("EXISTS");
		 }
	   else if (command == "REGISTER") //��������� ������ �����������
		 {
		   if (Registration(params->Strings[0], params->Strings[1], params->Strings[2]))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("FAIL");
		 }
	   else if (command == "VERIFY") //���������� ���� ����������� �� �����
		 {
		   String code = GenerateVerificationCode();

		   if (SendVerificationCode(params->Strings[0], code))
			 res = CreateAnswer(code);
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "SETPWD") //���� ������ �����������
		 {
		   if (SetUserPassword(params->Strings[0].ToInt(), params->Strings[1]))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "CHECKPWD") //�������� �� ������������ ������
		 {
		   if (ValidUserPassword(params->Strings[0].ToInt(), params->Strings[1]))
			 res = CreateAnswer("VALID");
		   else
			 res = CreateAnswer("INVALID");
		 }
	   else if (command == "SETMAIL") //���� ������� ��������
		 {
		   if (SetUserMail(params->Strings[0].ToInt(), params->Strings[1]))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "GETITEM") //����� ����� ��� �������
		 res = GetItem(params->Strings[0].ToInt());
       else if (command == "SETITEM") //���� ������� ��������
		 {
		   if (SetItem(params->Strings[0].ToInt(),
					   params->Strings[1],
					   params->Strings[2],
					   params->Strings[3],
					   params->Strings[4].ToInt(),
					   params->Strings[5].ToInt()))
			 {
			   res = CreateAnswer("SUCCESS");
			 }
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "GETLOCATIONS") //����� ����� ��� �������
		 res = GetLocationList();
	   else
         throw Exception("������� �������");
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
                                                    const String &titles,
													TStringList *data)
{
  TStringStream *res;

  try
	 {
	   res = new TStringStream("", TEncoding::UTF8, true);

	   res->WriteString("<Answer>");
	   res->WriteString("<Command>" + command + "</Command>");
	   res->WriteString("<Titles>" + titles + "</Titles>");
	   res->WriteString("<Data>");

	   std::unique_ptr<TStringList> fields(new TStringList());

	   for (int i = 0; i < data->Count; i++)
		  {
			res->WriteString("<Row>");

			StrToList(fields.get(), data->Strings[i], ";"); //��������� ����� �� �������

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

	   StrToList(rows.get(), data, "%"); //��������� ���� �� �����

	   for (int i = 0; i < rows->Count; i++)
		  {
			res->WriteString("<Row>");

			StrToList(fields.get(), rows->Strings[i], ";"); //��������� ����� �� �������

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

TStringStream* __fastcall TServerForm::CreateAnswer(const String &command)
{
  TStringStream *res;

  try
	 {
	   res = new TStringStream("", TEncoding::UTF8, true);

	   res->WriteString("<Answer>");
	   res->WriteString("<Command>" + command + "</Command>");
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

void __fastcall TServerForm::ProcessAnswer(TXMLDocument *ixml)
{
  try
	 {
	   _di_IXMLNode Document = ixml->DocumentElement; //��� ��������� (�����/�������)
	   _di_IXMLNode Command; //������� (����� ��� ���� ���������� ����)

	   _di_IXMLNode Data; //������� ������ � ������
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

  try //������ ����, �� �������
	 {
	   ms->LoadFromStream(TSAESCypher::Encrypt(ms.get(), DataCryptKey));
	   ms->Position = 0;
	   WriteLog(ms->ReadString(ms->Size));
	 }
  catch (Exception &e)
	 {
	   WriteLog("ConnectionServerExecute: ����������� ������� �����: " + e.ToString());

	   return;
	 }

  try //��������� ��� ������ �� ���������� ����
	 {
	   ms->Position = 0;

	   ixml.reset(CreatXMLStream(ms.get()));
	   answer.reset(ParseXML(ixml.get()));
	 }
  catch (Exception &e)
	 {
	   WriteLog("ConnectionServerExecute: �������: " + e.ToString());

	   return;
	 }

  if (answer) //���� ������� ���������� ������ - ��������� �� �볺���
	{
	  try
		 {
           answer->Position = 0;
		   WriteLog(answer->ReadString(answer->Size));
		   answer->Position = 0;
		   answer->LoadFromStream(TSAESCypher::Crypt(answer.get(), DataCryptKey));
		   answer->Position = 0;
		 }
	  catch (Exception &e)
		 {
		   WriteLog("ConnectionServerExecute: �������� �������� �����: " + e.ToString());

		   return;
		 }

	  try
		 {
		   WriteLog("³������� �����");
		   answer->Position = 0;
		   AContext->Connection->IOHandler->Write(answer.get(), answer->Size, true);
		 }
	  catch (Exception &e)
		 {
		   WriteLog("ConnectionServerExecute: ³������� �����: " + e.ToString());

           return;
		 }
	}
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ListenerConnect(TIdContext *AContext)
{
  //�볺�� ��'�������
  WriteLog("ϳ��������� �볺��: " + AContext->Binding->PeerIP);
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::ListenerDisconnect(TIdContext *AContext)
{
  //�볺�� ��'�������
  WriteLog("³��������� �볺��: " + AContext->Binding->PeerIP);
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



