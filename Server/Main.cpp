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

	   FQueryManager.reset(new TQueryManager(StatConnection));
       FQueryManager->LoadFromFile(AppPath + "\\queries.xml");
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

  if (Date().CurrentDate() > DateStart)
	{
      DateStart = Date().CurrentDate();
	  LogFile = DateToStr(DateStart) + ".log";
    }

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

	   TManagedQuery *query = FQueryManager->ItemsByID["Authorisation"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["login"]->AsString = login;
	   query->Execute();

	   if (query->RecordCount == 1)
		 {
		   query->First();

		   if (query->Fields["PASS"]->AsString == pass)
			 {
			   res.ID = query->Fields["ID"]->AsInteger;
			   res.Role = query->Fields["ROLE"]->AsString;
			   res.Mail = query->Fields["MAIL"]->AsString;
			   res.Locked = query->Fields["LOCKED"]->AsInteger;
			 }
		   else
			 res.ID = -1;
		 }
	   else if (query->RecordCount > 1)
		 res.ID = -1;
	   else
		 res.ID = -1;

       query->Close();
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

	   TManagedQuery *query = FQueryManager->ItemsByID["IsLoginFree"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["login"]->AsString = login;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = false;
	   else
		 res = true;
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
										  const String &mail,
										  bool admin)
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

	   String role;
	   int locked;

	   if (admin)
		 {
		   role = "admin";
		   locked = 0;
		 }
	   else
		 {
		   role = "agent";
		   locked = 1;
		 }

	   TManagedQuery *query = FQueryManager->ItemsByID["Registration"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["login"]->AsString = login;
	   query->Params["pass"]->AsString = pass;
	   query->Params["mail"]->AsString = mail;
	   query->Params["role"]->AsString = role;
	   query->Params["lock"]->AsInteger = locked;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
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

	   TManagedQuery *query = FQueryManager->ItemsByID["SetUserPassword"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["userid"]->AsInteger = user_id;
	   query->Params["pass"]->AsString = new_password;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
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

	   TManagedQuery *query = FQueryManager->ItemsByID["ValidUserPassword"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["userid"]->AsInteger = user_id;
	   query->Params["pass"]->AsString = password;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("ValidUserPassword(): " + e.ToString());
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

	   TManagedQuery *query = FQueryManager->ItemsByID["SetUserMail"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["userid"]->AsInteger = user_id;
	   query->Params["mail"]->AsString = new_mail;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("SetUserMail(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::GetItem(int item_id)
{
  TStringStream *res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["GetItem"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["itemid"]->AsInteger = item_id;
	   query->Execute();

	   if (query->RecordCount == 0)
		 res = CreateAnswer("NODATA");
	   else
		 {
		   std::unique_ptr<TStringList> data(new TStringList());

		   query->First();

		   data->Add(query->Fields["INN"]->AsString);
		   data->Add(query->Fields["SN"]->AsString);
		   data->Add(query->Fields["MODEL"]->AsString);
		   data->Add(query->Fields["LOGIN"]->AsString);
		   data->Add(query->Fields["LOCATION_ID"]->AsString);
		   data->Add(query->Fields["LOCATION"]->AsString);

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

       query->Close();
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
	   TManagedQuery *query = FQueryManager->ItemsByID["SetItem"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["itemid"]->AsInteger = item_id;
	   query->Params["inn"]->AsString = inn;
	   query->Params["sn"]->AsString = sn;
	   query->Params["model"]->AsString = model;
	   query->Params["location"]->AsInteger = location_id;
	   query->Params["agent"]->AsInteger = agent_id;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
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
	   TManagedQuery *query = FQueryManager->ItemsByID["GetLocationList"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Execute();

	   if (query->RecordCount == 0)
		 res = CreateAnswer("NODATA");
	   else
		 {
		   std::unique_ptr<TStringList> data(new TStringList());
		   std::unique_ptr<TStringList> row(new TStringList());

		   query->First();

		   String str;

		   while (!query->Eof)
			 {
			   row->Clear();

			   row->Add(query->Fields["ID"]->AsString);
			   row->Add(query->Fields["IND"]->AsString);
			   row->Add(query->Fields["ADDRESS"]->AsString);

			   for (int i = 0; i < row->Count; i++)
				  {
					if (row->Strings[i] == "")
					  row->Strings[i] = "???";
				  }

			   str = ListToStr(row.get(), ";");

			   data->Add(str);

			   query->Next();
			 }

		   String titles = "<Title size='0'>ID</Title>\
<Title size='300'>�������</Title>\
<Title size='200'>������</Title>";

		   res = CreateAnswer("SUCCESS", titles, data.get());
		 }

	   query->Close();
	 }
  catch (Exception &e)
	 {
	   res = CreateAnswer("ERROR");
	   WriteLog("GetLocationList(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::RemoveItem(int item_id)
{
  bool res;

  try
     {
	   TManagedQuery *query = FQueryManager->ItemsByID["RemoveItem"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["itemid"]->AsInteger = item_id;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("RemoveItem(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::AddEvent(int event_id, int item_id, int agent_id)
{
  bool res;

  try
     {
	   TManagedQuery *query = FQueryManager->ItemsByID["AddEvent"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["date"]->AsDateTime = Date().CurrentDateTime();
	   query->Params["item"]->AsInteger = item_id;
	   query->Params["agent"]->AsInteger = agent_id;
	   query->Params["operation"]->AsInteger = event_id;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("AddEvent(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::GetEventList(int search_type,
													const String &item,
													const String &dt_from,
													const String &dt_to)
{
  TStringStream *res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["GetEventList"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   switch (search_type)
		 {
		   case ST_ID:
			 {
			   if (item > 0)
				 {
				   query->Text += " WHERE chn.ITEM_ID = :item";
				   query->Params["item"]->AsInteger = item.ToInt();
				 }

               break;
			 }
		   case ST_INN:
			 {
			   if (item > 0)
				 {
				   query->Text += " WHERE chn.ITEM_ID = (SELECT DISTINCT(ID) FROM ITEMS WHERE INN = :item)";
				   query->Params["item"]->AsString = item;
				 }

               break;
			 }
		   case ST_SN:
			 {
			   if (item > 0)
				 {
				   query->Text += " WHERE chn.ITEM_ID = (SELECT DISTINCT(ID) FROM ITEMS WHERE SN = :item)";
				   query->Params["item"]->AsString = item;
				 }

               break;
			 }
		 }

	   if ((dt_from != "-") && (dt_to != "-"))
		 {
		   TDateTime fr = StrToDateTime(dt_from), to = StrToDateTime(dt_to);

		   fr = fr + StrToTime("00:00:01");
		   to = to + StrToTime("23:59:59");

		   query->Text += " AND chn.DATE_ADD BETWEEN :fr AND :to";

		   query->Params["fr"]->AsDateTime = fr;
		   query->Params["to"]->AsDateTime = to;
		 }

	   query->Execute();

	   if (query->RecordCount == 0)
		 res = CreateAnswer("NODATA");
	   else
		 {
		   std::unique_ptr<TStringList> data(new TStringList());
		   std::unique_ptr<TStringList> row(new TStringList());

		   query->First();

		   String str;

		   while (!query->Eof)
			 {
			   row->Clear();

			   row->Add(query->Fields["DATE_ADD"]->AsString);
			   row->Add(query->Fields["ITEM"]->AsString);
			   row->Add(query->Fields["OPERATION"]->AsString);
			   row->Add(query->Fields["AGENT"]->AsString);

			   for (int i = 0; i < row->Count; i++)
				  {
					if (row->Strings[i] == "")
					  row->Strings[i] = "???";
				  }

			   str = ListToStr(row.get(), ";");

			   data->Add(str);

			   query->Next();
			 }

		   String titles = "<Title size='150'>����</Title>\
<Title size='350'>�������</Title>\
<Title size='300'>��������</Title>\
<Title size='100'>�����</Title>";

		   res = CreateAnswer("SUCCESS", titles, data.get());
		 }

	   query->Close();
	 }
  catch (Exception &e)
	 {
	   res = CreateAnswer("ERROR");
	   WriteLog("GetEventList(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::GetItemList(int loc_id)
{
  TStringStream *res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["GetItemList"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["location"]->AsInteger = loc_id;
	   query->Execute();

	   if (query->RecordCount == 0)
		 res = CreateAnswer("NODATA");
	   else
		 {
		   std::unique_ptr<TStringList> data(new TStringList());
		   std::unique_ptr<TStringList> row(new TStringList());

		   query->First();

		   String str;

		   while (!query->Eof)
			 {
               row->Clear();

			   row->Add(query->Fields["ID"]->AsString);
			   row->Add(query->Fields["INN"]->AsString);
			   row->Add(query->Fields["SN"]->AsString);
			   row->Add(query->Fields["MODEL"]->AsString);
			   row->Add(query->Fields["AGENT"]->AsString);

			   for (int i = 0; i < row->Count; i++)
				  {
					if (row->Strings[i] == "")
					  row->Strings[i] = "???";
				  }

			   str = ListToStr(row.get(), ";");

			   data->Add(str);

			   query->Next();
			 }

		   String titles = "<Title size='0'>ID</Title>\
<Title size='200'>����������� �����</Title>\
<Title size='150'>������� �����</Title>\
<Title size='300'>������</Title>\
<Title size='130'>�������� ������</Title>";

		   res = CreateAnswer("SUCCESS", titles, data.get());
		 }

	   query->Close();
	 }
  catch (Exception &e)
	 {
	   res = CreateAnswer("ERROR");
	   WriteLog("GetItemList(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::IsInnFree(const String &inn)
{
  bool res;

  try
	 {
	   if (inn == "")
		 throw Exception("�������� ����������� �����");

	   TManagedQuery *query = FQueryManager->ItemsByID["IsInnFree"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["inn"]->AsString = inn;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = false;
	   else
		 res = true;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("IsInnFree(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::CheckItemID(int id)
{
  bool res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["CheckItemID"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["id"]->AsInteger = id;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = false;
	   else
		 res = true;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("CheckItemID(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::AddItem(int item_id, const String &inn, const String &sn,
									 const String &model, int location_id, int agent_id)
{
  bool res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["AddItem"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["itemid"]->AsInteger = item_id;
	   query->Params["inn"]->AsString = inn;
	   query->Params["sn"]->AsString = sn;
	   query->Params["model"]->AsString = model;
	   query->Params["location"]->AsInteger = location_id;
	   query->Params["agent"]->AsInteger = agent_id;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("AddItem(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::GetUserList()
{
  TStringStream *res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["GetUserList"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Execute();

	   if (query->RecordCount == 0)
		 res = CreateAnswer("NODATA");
	   else
		 {
		   std::unique_ptr<TStringList> data(new TStringList());
		   std::unique_ptr<TStringList> row(new TStringList());

		   query->First();

		   String str;

		   while (!query->Eof)
			 {
               row->Clear();

			   row->Add(query->Fields["ID"]->AsString);
			   row->Add(query->Fields["LOGIN"]->AsString);
			   row->Add(query->Fields["MAIL"]->AsString);
			   row->Add(query->Fields["ROLE"]->AsString);

			   if (query->Fields["LOCKED"]->AsInteger)
				 row->Add("ͳ");
			   else
                 row->Add("���");

			   for (int i = 0; i < row->Count; i++)
				  {
					if (row->Strings[i] == "")
					  row->Strings[i] = "???";
				  }

			   str = ListToStr(row.get(), ";");

			   data->Add(str);

			   query->Next();
			 }

		   String titles = "<Title size='0'>ID</Title>\
<Title size='100'>����������</Title>\
<Title size='300'>��. �����</Title>\
<Title size='50'>����</Title>\
<Title size='80'>��������</Title>";

		   res = CreateAnswer("SUCCESS", titles, data.get());
		 }

	   query->Close();
	 }
  catch (Exception &e)
	 {
	   res = CreateAnswer("ERROR");
	   WriteLog("GetUserList(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::ControlUser(int user_id, int lock)
{
  bool res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["ControlUser"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["userid"]->AsInteger = user_id;
	   query->Params["locked"]->AsInteger = lock;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("ControlUser(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::RemoveLocation(int location_id)
{
  bool res;

  try
     {
	   TManagedQuery *query = FQueryManager->ItemsByID["RemoveLocation"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["locid"]->AsInteger = location_id;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("RemoveLocation(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::AddLocation(const String &index, const String &name)
{
  bool res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["AddLocation"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["index"]->AsString = index;
	   query->Params["name"]->AsString = name;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("AddLocation(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::EditLocation(int location_id, const String &index, const String &name)
{
  bool res;

  try
	 {
       TManagedQuery *query = FQueryManager->ItemsByID["EditLocation"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["locid"]->AsInteger = location_id;
	   query->Params["index"]->AsString = index;
	   query->Params["name"]->AsString = name;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("EditLocation(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::GetLog(const String &date)
{
  TStringStream *res;

  try
	 {
	   String titles = "<Title size='130'>����</Title><Title size='500'>�����</Title>";

	   std::unique_ptr<TStringList> data(new TStringList());

	   data->LoadFromFile(LogDir + "\\" + date + ".log", TEncoding::UTF8);

	   for (int i = 0; i < data->Count; i++)
		  {
			data->Strings[i] = ParseString(data->Strings[i], " : ", ";");
			data->Strings[i] = ParseString(data->Strings[i], "[", "");
			data->Strings[i] = ParseString(data->Strings[i], "]", "");
		  }

	   res = CreateAnswer("SUCCESS", titles, data.get());
	 }
  catch (Exception &e)
	 {
	   res = CreateAnswer("ERROR");
	   WriteLog("GetLog(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::ExecuteQuery(const String &query)
{
  TStringStream *res;

  try
	 {
	   std::unique_ptr<TFDTransaction> tmp_tr(CreateNewTransactionObj());
	   std::unique_ptr<TFDQuery> tmp_query(CreateNewQueryObj(tmp_tr.get()));
	   std::unique_ptr<TStringList> data(new TStringList());
	   String titles;

	   tmp_tr->StartTransaction();
	   tmp_query->SQL->Add(query);

	   tmp_query->Prepare();

	   if (UpperCase(query.SubString(1, 6)) == "SELECT")
		 {
		   tmp_query->Open();

		   std::unique_ptr<TStringList> row(new TStringList());

		   tmp_query->First();

		   String str;

           for (int i = 0; i < tmp_query->FieldCount; i++)
			  titles += "<Title size='100'>" + tmp_query->Fields->Fields[i]->FieldName + "</Title>";

		   while (!tmp_query->Eof)
			 {
			   row->Clear();

			   for (int i = 0; i < tmp_query->FieldCount; i++)
				  row->Add(tmp_query->Fields->Fields[i]->AsString);

			   for (int i = 0; i < row->Count; i++)
				  {
					if (row->Strings[i] == "")
					  row->Strings[i] = "???";
				  }

			   str = ListToStr(row.get(), ";");

			   data->Add(str);

			   tmp_query->Next();
			 }
		 }
	   else
		 {
		   tmp_query->Execute();

		   tmp_tr->Commit();

		   titles = "<Title size='150'>��������� ������</Title>";
		   data->Add(IntToStr(tmp_query->RowsAffected));
		 }

	   tmp_query->Close();

	   res = CreateAnswer("SUCCESS", titles, data.get());
	 }
  catch (Exception &e)
	 {
	   res = CreateAnswer("ERROR");
	   WriteLog("ExecuteQuery(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::CheckUserMail(const String &mail)
{
  bool res;

  try
	 {
	   if (mail == "")
		 throw Exception("������� ������ ��. �����");

	   TManagedQuery *query = FQueryManager->ItemsByID["CheckUserMail"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["mail"]->AsString = mail;
	   query->Execute();

	   if (query->RecordCount > 0)
		 res = true;
	   else
		 res = false;

	   query->Close();
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("CheckUserMail(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

int __fastcall TServerForm::GetUserID(const String &login)
{
  int res;

  try
	 {
	   TManagedQuery *query = FQueryManager->ItemsByID["GetUserID"];

	   if (!query)
		 throw Exception("�� ������� ���������� SQL-�����");

	   query->Params["login"]->AsString = login;
	   query->Execute();

	   if (query->RecordCount == 0)
		 res = -1;
	   else
		 {
		   query->First();
		   res = query->Fields["ID"]->AsInteger;
         }

	   query->Close();
	 }
  catch (Exception &e)
	 {
	   res = false;
	   WriteLog("GetUserID(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TServerForm::ConnectToSMTP()
{
  MailSender->Username = "<none>";
  MailSender->Password = "<none>";
  MailSender->Host = MailServer;
  MailSender->Port = MailPort;

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

  MailSender->Disconnect();

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

String __fastcall TServerForm::GeneratePassword()
{
  String res;

  try
	 {
	   wchar_t gen_pwd[9];

	   for (int i = 0; i < 8; i++)
		  gen_pwd[i] = pwd_char_base[Random(cb_sz)];

	   gen_pwd[8] = '\0';

	   res = gen_pwd;
	 }
  catch (Exception &e)
	 {
	   res = "";
	   WriteLog("GeneratePassword: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TServerForm::UploadClient(const String &host)
{
  try
	 {
	   std::unique_ptr<TFileStream> fs(new TFileStream(AppPath + "\\TIClient.exe",
													   fmOpenRead|fmShareDenyNone));
	   std::unique_ptr<TMemoryStream> ms(new TMemoryStream());

	   ms->LoadFromStream(fs.get());
       ms->Position = 0;

	   WriteLog("³������� �볺�������� ������ �� " + host);
	   SendToClient(host, ms.get());
	 }
  catch (Exception &e)
	 {
	   WriteLog("UploadClient: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

const char* __fastcall TServerForm::GenHashKey()
{
  AnsiString res;

  try
	 {
	   res = IntToStr(static_cast<int>(Date()) << 3);
	 }
  catch (Exception &e)
	 {
	   res = "";
	   WriteLog("GenHashKey: " + e.ToString());
	 }

  return res.c_str();
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

TXMLDocument *__fastcall TServerForm::CreateXMLStream(TStringStream *ms)
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

bool __fastcall TServerForm::SendToClient(const String &host, TMemoryStream *buffer)
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

TStringStream* __fastcall TServerForm::ParseXML(TXMLDocument *ixml, TIdContext *AContext)
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
		   res = ProcessRequest(ixml, AContext);
		 }
	   else
		 {
		   //������� ����� �����
		   throw Exception("�������� ��� XML-���������");
		 }
	 }
  catch (Exception &e)
	 {
	   res = nullptr;
	   WriteLog("[" + AContext->Binding->PeerIP + "] ParseXML: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::ProcessRequest(TXMLDocument *ixml, TIdContext *AContext)
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

			if (!Param->NodeValue.IsNull())
			  params->Add(Param->NodeValue);
			else
			  params->Add("");
		  }

	   res = ExecuteCommand(command, params.get(), AContext);
	 }
  catch (Exception &e)
	 {
       res = nullptr;
	   WriteLog("[" + AContext->Binding->PeerIP + "] ProcessRequest: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TServerForm::ExecuteCommand(const String &command,
													  TStringList *params,
													  TIdContext *AContext)
{
  TStringStream *res;

  try
	 {
//�� �������� ��������� �������� ����� �� �� � �������� ����
	   if (command == "AUTH") //�������������� �����������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����������� �����������");

		   UserInfo user = Authorisation(params->Strings[0], params->Strings[1]);

		   if (user.ID < 0)
			 res = CreateAnswer("DENIED");
		   else
			 {
			   WriteLog("[" + AContext->Binding->PeerIP + "] ������ ����������: " + params->Strings[0]);

			   res = CreateAnswer("GRANTED", IntToStr(user.ID) + ";" +
											 user.Role + ";" +
											 user.Mail+ ";" +
											 user.Locked);
			 }
		 }
	   else if (command == "GETVERSION") //����� ���� �������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� ���� �������");
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
		   WriteLog("[" + AContext->Binding->PeerIP + "] ��������� ������ �����������");
		   if (Registration(params->Strings[0], params->Strings[1], params->Strings[2], StrToBool(params->Strings[3])))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("FAIL");
		 }
	   else if (command == "VERIFY") //���������� ���� ����������� �� �����
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ³������� ���� �����������");

		   String code = GenerateVerificationCode();

		   if (SendVerificationCode(params->Strings[0], code))
			 res = CreateAnswer(code);
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "SETPWD") //���� ������ �����������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����������� ������ ��� �����������");

		   if (SetUserPassword(params->Strings[0].ToInt(), params->Strings[1]))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "CHECKPWD") //�������� �� ������������ ������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] �������� ���������� ������");

		   if (ValidUserPassword(params->Strings[0].ToInt(), params->Strings[1]))
			 res = CreateAnswer("VALID");
		   else
			 res = CreateAnswer("INVALID");
		 }
	   else if (command == "SETMAIL") //���� ������� ��������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ���� ������ ������� ��������");

		   if (SetUserMail(params->Strings[0].ToInt(), params->Strings[1]))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "GETITEM") //����� ����� ��� �������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� ����� ��� �������");
		   res = GetItem(params->Strings[0].ToInt());
		 }
	   else if (command == "SETITEM") //���� ����� ��������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ���� ����� ��������");

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
	   else if (command == "GETLOCATIONS") //����� ������� �������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� ������� �������");
		   res = GetLocationList();
		 }
       else if (command == "REMOVEITEM") //��������� ����� ��� �������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ��������� �������� � ��");

		   if (RemoveItem(params->Strings[0].ToInt()))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "ADDEVENT") //��������� ��䳿
		 {
		   if (AddEvent(params->Strings[0].ToInt(),
						params->Strings[1].ToInt(),
						params->Strings[2].ToInt()))
			 {
			   res = CreateAnswer("SUCCESS");
			 }
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "GETEVENTS") //����� ������� ��������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� ������� ����");

		   res = GetEventList(params->Strings[0].ToInt(),
							  params->Strings[1],
							  params->Strings[2],
							  params->Strings[3]);
		 }
	   else if (command == "GETITEMS") //����� ������� ��������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� ������� �������� � �������");
		   res = GetItemList(params->Strings[0].ToInt());
		 }
	   else if (command == "CHECKINN") //�������� ���������� ���. ������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] �������� ���������� ���. ������");

		   if (IsInnFree(params->Strings[0]))
			 res = CreateAnswer("FREE");
		   else
			 res = CreateAnswer("EXISTS");
		 }
	   else if (command == "CHECKID") //�������� ���������� id ��������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] �������� ���������� id ��������");

		   if (CheckItemID(params->Strings[0].ToInt()))
			 res = CreateAnswer("FREE");
		   else
			 res = CreateAnswer("EXISTS");
		 }
	   else if (command == "ADDITEM") //������� ������ ��������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ������� � �� ������ ��������");

		   if (AddItem(params->Strings[0].ToInt(),
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
	   else if (command == "GETUSERLIST") //����� ������� ������������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� ������� ������������");
		   res = GetUserList();
		 }
	   else if (command == "CTRLUSER") //��������� ������������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ��������� �������� �����������");

		   if (ControlUser(params->Strings[0].ToInt(), params->Strings[1].ToInt()))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "REMOVELOCATION") //��������� �������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ��������� �������");

		   if (RemoveLocation(params->Strings[0].ToInt()))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "ADDLOCATION") //��������� �������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ��������� �������");

		   if (AddLocation(params->Strings[0], params->Strings[1]))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "EDITLOCATION") //���� ����� �������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����������� �������");

		   if (EditLocation(params->Strings[0].ToInt(), params->Strings[1], params->Strings[2]))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "GETLOG") //����� ���� ������� �� ����� ����
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� ���� �������");
		   res = GetLog(params->Strings[0]);
		 }
       else if (command == "EXECQUERY") //���������� SQL-������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ���������� SQL-������ �� ��");
		   res = ExecuteQuery(params->Strings[0]);
		 }
	   else if (command == "CHECKMAIL") //�������� ���������� � ������� ������ ������� ��������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] �������� ������� �������� �� ����������� � ������� ������");

		   if (CheckUserMail(params->Strings[0]))
			 res = CreateAnswer("SUCCESS");
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "RESTOREPWD") //�������� ������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] �������� ������");

		   String pwd = GeneratePassword();

		   int id = GetUserID(params->Strings[0]);

		   if (SetUserPassword(id, MD5(pwd)))
			 {
			   if (SendMsg(params->Strings[1], "Restored password", "TechInvent@ukrposhta.ua", pwd))
				 res = CreateAnswer("SUCCESS");
			   else
                 res = CreateAnswer("ERROR");
			 }
		   else
			 res = CreateAnswer("ERROR");
		 }
	   else if (command == "GETCLIENTVERSION") //����� ��������� ���� �볺���
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� ��������� ���� �볺���");
		   res = CreateAnswer(GetVersionInString(String(AppPath + "\\TIClient.exe").c_str()));
		 }
	   else if (command == "DOWNLOADMODULE") //����� �� ������������ �볺�������� ������
		 {
		   WriteLog("[" + AContext->Binding->PeerIP + "] ����� �� ������������ �볺�������� ������");
		   UploadClient(AContext->Binding->PeerIP);
		   res = nullptr;
		 }
	   else
		 throw Exception("������� �������");
	 }
  catch (Exception &e)
	 {
	   res = nullptr;
	   WriteLog("[" + AContext->Binding->PeerIP + "] ExecuteCommand: " + e.ToString());
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
	   res = nullptr;
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
	   res = nullptr;
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
	   res = nullptr;
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
	   ms->LoadFromStream(TSAESCypher::Encrypt(ms.get(), GenHashKey()));
	   //ms->Position = 0;
	   //WriteLog(ms->ReadString(ms->Size));
	 }
  catch (Exception &e)
	 {
	   WriteLog("ConnectionServerExecute: ����������� ������� �����: " + e.ToString());

	   return;
	 }

  try //��������� ��� ������ �� ���������� ����
	 {
	   ms->Position = 0;

	   ixml.reset(CreateXMLStream(ms.get()));
	   answer.reset(ParseXML(ixml.get(), AContext));
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
		   //answer->Position = 0;
		   //WriteLog(answer->ReadString(answer->Size));
		   answer->Position = 0;
		   answer->LoadFromStream(TSAESCypher::Crypt(answer.get(), GenHashKey()));
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
  TFDTransaction *t = new TFDTransaction(nullptr);

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
  TFDQuery * q = new TFDQuery(nullptr);

  q->Connection = ServerForm->StatConnection;
  q->Transaction = t;

  return q;
}
//---------------------------------------------------------------------------




