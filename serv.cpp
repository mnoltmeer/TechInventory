//---------------------------------------------------------------------------
#include "..\work-functions\MyFunc.h"
#include "..\work-functions\Cypher.h"
#include "html_headers.h"
#include "serv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int ListenPort, ConsolePort;
String DBHost, DBPath, ServerName, ServerVersion, ConfigPath;

TTechService *TechService;

//---------------------------------------------------------------------------
__fastcall TTechService::TTechService(TComponent* Owner)
	: TService(Owner)
{
}
//---------------------------------------------------------------------------

void __stdcall ServiceController(unsigned CtrlCode)
{
  TechService->Controller(CtrlCode);
}
//---------------------------------------------------------------------------

TServiceController __fastcall TTechService::GetServiceController(void)
{
  return (TServiceController) ServiceController;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ServiceExecute(TService *Sender)
{
  try
	 {
	   while (!Terminated) //просто чекаємо поки працює сервер
		 {
		   ServiceThread->ProcessRequests(true);
		 }
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("ServiceExecute(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ServiceStart(TService *Sender, bool &Started)
{
  try
	 {
	   ReadSettings();
	   ConnectToDB();
	   StartServer();
	   SendLogToConsole("Службу запущено");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("ServiceStart(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ServiceStop(TService *Sender, bool &Stopped)
{
  try
	 {
	   StopServer();
	   DisconnectFromDB();
	   SendLogToConsole("Службу зупинено");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("ServiceStop(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ConnectToDB()
{
  if (!StatConnection->Connected)
	{
	  try
		 {
           StatFBDriverLink->VendorLib = ConfigPath + "\\fbclient.dll";

		   StatConnection->Params->Clear();
		   StatConnection->Params->Add("User_Name=SYSDBA");
		   StatConnection->Params->Add("Password=masterkey");
		   StatConnection->Params->Add("Port=3050");
		   StatConnection->Params->Add("DriverID=myFB");
		   StatConnection->Params->Add("Protocol=TCPIP");
		   StatConnection->Params->Add("Database=" + DBPath);
		   StatConnection->Params->Add("Server=" + DBHost);
		   StatConnection->Params->Add("CharacterSet=UTF8");

		   StatConnection->Connected = true;
		   SendLogToConsole("Підключено до: " + DBHost + ":" + DBPath);
         }
	  catch (Exception &e)
		 {
		   SendLogToConsole("ConnectToDB(): " + e.ToString());
		 }
	}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::DisconnectFromDB()
{
  if (StatConnection->Connected)
	{
	  try
		 {
		   WriteQuery->Active = false;
		   StatConnection->Connected = false;
		   SendLogToConsole("Відключено від: " + DBHost + ":" + DBPath);
		 }
	  catch (Exception &e)
		 {
		   SendLogToConsole("DisconnectFromDB(): " + e.ToString());
		 }
	}
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestHistory(TStringStream *ms,
													   String inn,
													   String sn,
													   String datefrom,
													   String dateto,
													   String sortby)
{
  String sqltext =
"SELECT ch.date_add AS DATE_OP, \
		itm.inn AS INN, \
		itm.sn AS SN, \
		itm.model AS MODEL, \
		ag.name AS AGENT, \
		op.caption AS OPERATION \
FROM CHANGES ch \
INNER JOIN items itm ON itm.id = ch.item_id \
LEFT JOIN AGENTS ag ON ag.id = ch.agent_id \
INNER JOIN OPERATIONS op ON op.id = ch.operation_id";

  bool openfield = true;
  bool use_inn = false, use_sn = false, use_datefr = false, use_dateto = false;

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  if ((inn != "") && (openfield))
	{
	  sqltext += " WHERE itm.inn LIKE :inn";
	  use_inn = true;
	  openfield = false;
	}

  if ((sn != "") && (openfield))
	{
	  sqltext += " WHERE itm.sn LIKE :sn";
	  use_sn = true;
	  openfield = false;
	}
  else if ((sn != "") && (!openfield))
	{
	  sqltext += " AND itm.sn LIKE :sn";
	  use_sn = true;
	}

  if ((datefrom != "") && (openfield))
	{
	  if (dateto != "")
		{
		  sqltext += " WHERE ch.date_add BETWEEN :datefrom AND :dateto";
		  use_dateto = true;
		  use_datefr = true;
        }
	  else
		{
		  sqltext += " WHERE ch.date_add = :datefrom";
		  use_datefr = true;
		}
	}
  else if ((datefrom != "") && (!openfield))
	{
	  if (dateto != "")
		{
		  sqltext += " AND ch.date_add BETWEEN :datefrom AND :dateto";
		  use_dateto = true;
		  use_datefr = true;
        }
	  else
		{
		  sqltext += " AND ch.date_add = :datefrom";
		  use_datefr = true;
		}
	}

  if (sortby == "inn")
	sqltext += " ORDER BY itm.inn";
  else if (sortby == "sn")
	sqltext += " ORDER BY itm.sn";
  else if (sortby == "agent")
	sqltext += " ORDER BY ag.name";
  else if (sortby == "dateadd")
	sqltext += " ORDER BY ch.date_add";

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			if (use_inn)
			  tmp_query->ParamByName("inn")->AsString = "%" + inn + "%";

			if (use_sn)
			  tmp_query->ParamByName("sn")->AsString = "%" + sn + "%";

			if (use_datefr)
			  {
				short d, m, y;
				y = datefrom.SubString(1, 4).ToInt();
				m = datefrom.SubString(6, 2).ToInt();
				d = datefrom.SubString(9, 2).ToInt();

				TDate dt_fr = TDate(y, m, d);
				tmp_query->ParamByName("datefrom")->AsDateTime = dt_fr.FormatString("dd.mm.yyyy 00:00:01");
			  }

			if (use_dateto)
			  {
				short d, m, y;
				y = dateto.SubString(1, 4).ToInt();
				m = dateto.SubString(6, 2).ToInt();
				d = dateto.SubString(9, 2).ToInt();

				TDate dt_to = TDate(y, m, d);
				tmp_query->ParamByName("dateto")->AsDateTime = dt_to.FormatString("dd.mm.yyyy 23:59:59");
			  }

			tmp_query->Prepare();
			tmp_query->Open();
			tmp_tr->Commit();


		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestHistory(): " + e.ToString());
          }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestAllChanges(TStringStream *ms)
{
  String sqltext = "SELECT * FROM SEL_ALL_CHANGES_VIEW";
  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);
			tmp_query->Open();
			tmp_tr->Commit();


		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestAllChanges(): " + e.ToString());

		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestAllItems(TStringStream *ms)
{
  String sqltext = "SELECT * FROM SEL_ALL_ITEMS_VIEW";
  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);
			tmp_query->Open();
			tmp_tr->Commit();


		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestAllItems(): " + e.ToString());

		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestUsers(TStringStream *ms)
{
  String sqltext = "SELECT ID, LOGIN, NAME, ROLE FROM AGENTS";
  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);
			tmp_query->Open();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestUsers(): " + e.ToString());

		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestLog(const String &date, TStringStream *ms)
{
  String format_date;

  try
	 {
	   short y = date.SubString(1, 4).ToInt(),
			 m = date.SubString(6, 2).ToInt(),
			 d = date.SubString(9, 2).ToInt();

	   TDate dt = TDate(y, m, d);
	   format_date = dt.FormatString("dd.mm.yyyy");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("RequestLog(): " + e.ToString());
	 }

  if (!FileExists(ConfigPath + "\\Logs\\" + format_date + ".log"))
	{
	  SendLogToConsole("RequestLog(): відсутній файл " +
					   ConfigPath + "\\Logs\\" +
					   format_date + ".log");
	}
  else
	{
      try
		 {
		   ms->LoadFromFile(ConfigPath + "\\Logs\\" + format_date + ".log");
		   ms->Position = 0;
		   String content = ms->ReadString(ms->Size);
//замінюємо текстові переноси рядків на переноси + html-тег
		   content = ParseString(content, "\r\n", "<br>");
//беремо хідер і замінюємо у ньому [***] на форматовані дані з логу
		   content = ParseString(String(logs_hdr), "[***]", content);
		   ms->Clear();
		   ms->WriteString(content);
		 }
	  catch (Exception &e)
		 {
		   SendLogToConsole("RequestLog(): " + e.ToString());
		 }
	}

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestLocations(TStringStream *ms)
{
  String sqltext = "SELECT * FROM LOCATIONS";
  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);
			tmp_query->Open();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestLocations(): " + e.ToString());

		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestItem(TStringStream *ms,
													const String &inn,
										 			const String &sn)
{
  String sqltext =
"SELECT itm.id as ID, \
		itm.inn AS INN, \
		itm.sn AS SN, \
		itm.model AS MODEL, \
		loc.ind AS IND, \
		loc.address AS ADDRESS, \
		ag.name AS NAME \
FROM ITEMS itm \
LEFT JOIN LOCATIONS loc ON loc.id = itm.location_id \
LEFT JOIN AGENTS ag ON ag.id = itm.last_agent_id";

  bool openfield = true;
  bool use_inn = false, use_sn = false;

  if ((inn != "") && (openfield))
	{
	  sqltext += " WHERE itm.inn LIKE :inn";
	  use_inn = true;
	  openfield = false;
	}

  if ((sn != "") && (openfield))
	{
	  sqltext += " WHERE itm.sn LIKE :sn";
	  use_sn = true;
	  openfield = false;
	}
  else if ((sn != "") && (!openfield))
	{
	  sqltext += " AND itm.sn LIKE :sn";
	  use_sn = true;
	}

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

            if (use_inn)
			  tmp_query->ParamByName("inn")->AsString = "%" + inn + "%";

			if (use_sn)
			  tmp_query->ParamByName("sn")->AsString = "%" + sn + "%";

			tmp_query->Prepare();

			tmp_query->Open();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestItem(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestItems(TStringStream *ms,
													 const String &ind)
{
  String sqltext =
"SELECT itm.id as ID, \
		itm.inn AS INN, \
		itm.sn AS SN, \
		itm.model AS MODEL, \
		loc.ind AS IND, \
		loc.address AS ADDRESS, \
		ag.name AS NAME \
FROM ITEMS itm \
LEFT JOIN LOCATIONS loc ON loc.id = itm.location_id \
LEFT JOIN AGENTS ag ON ag.id = itm.last_agent_id";

  if (ind != "")
	sqltext += " WHERE loc.ind = :ind";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			if (ind != "")
			  tmp_query->ParamByName("ind")->AsString = ind;

            tmp_query->Prepare();
			tmp_query->Open();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestItems(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return ms;
}
//---------------------------------------------------------------------------

int __fastcall TTechService::AddItem(const String &inn, const String &sn,
									 const String &model, const String &loc_id,
									 int user_id,
									 TStringStream *ms)
{
  String sqltext = "INSERT INTO ITEMS VALUES (:id, :inn, :sn, :model, :loc, NULL)";
  int id;

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->Open("SELECT GEN_ID(GEN_ITMS_ID, 1) AS ID FROM RDB$DATABASE");
			tmp_query->First();

			id = tmp_query->FieldByName("ID")->AsInteger;

            tmp_query->Close();

			tmp_query->SQL->Clear();
			tmp_query->SQL->Add(sqltext);

			if (inn != "")
			  tmp_query->ParamByName("inn")->AsString = inn;

			if (sn != "")
			  tmp_query->ParamByName("sn")->AsString = sn;

			if (model != "")
			  tmp_query->ParamByName("model")->AsString = model;

			if (loc_id != "")
			  tmp_query->ParamByName("loc")->AsInteger = loc_id.ToInt();

			tmp_query->ParamByName("id")->AsInteger = id;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();


			AddHistoryRecord(user_id, OT_ADD, id);
			SetChangingAgent(id, user_id);
		  }
		catch (Exception &e)
		  {
			id = -1;
			tmp_tr->Rollback();
			SendLogToConsole("AddItem(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return id;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::EditItem(const String &id, TStringStream *ms)
{
  String sqltext =
"SELECT itm.id AS ID, \
		itm.inn AS INN, \
		itm.sn AS SN, \
		itm.model AS MODEL \
FROM ITEMS itm";

  if (id != "")
	sqltext += " WHERE itm.id = :id";
  else
	{
	  return;
	}


  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("id")->AsInteger = id.ToInt();

			tmp_query->Prepare();

			tmp_query->Open();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("EditItem(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::RemoveItem(const String &id, int user_id, TStringStream *ms)
{
  String sqltext = "UPDATE ITEMS SET LOCATION_ID = 0 WHERE ID = :id";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			if (id != "")
			  tmp_query->ParamByName("id")->AsInteger = id.ToInt();

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();

			AddHistoryRecord(user_id, OT_REMOVE, id.ToInt());
			SetChangingAgent(id.ToInt(), user_id);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RemoveItem(): " + e.ToString());
          }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::SetItem(const String &id,
									  const String &inn, const String &sn,
									  const String &model, const String &loc_id,
                                      int user_id,
									  TStringStream *ms)
{
  String sqltext = "UPDATE ITEMS SET SN = :sn, MODEL = :model, LOCATION_ID = :loc WHERE ID = :id";
  int itm_id = id.ToInt();

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();

			tmp_query->SQL->Add("SELECT INN, SN, MODEL, LOCATION_ID FROM ITEMS WHERE ID = :id");
			tmp_query->ParamByName("id")->AsInteger = itm_id;
			tmp_query->Prepare();
			tmp_query->Open();
			tmp_query->First();

			String old_inn = tmp_query->FieldByName("INN")->AsString,
				   old_sn = tmp_query->FieldByName("SN")->AsString,
				   old_model = tmp_query->FieldByName("MODEL")->AsString;

			int old_loc_id = tmp_query->FieldByName("LOCATION_ID")->AsInteger;

			tmp_query->Close();

			tmp_query->Params->Clear();
			tmp_query->SQL->Clear();

//якщо змінюється інвентарний треба вивести з експлуатації поточний Пристрій
//і додати новий Пристрій з новим інвентарним
			if (old_inn != inn)
			  {
				RemoveItem(id, user_id, ms);
				itm_id = AddItem(inn, sn, model, loc_id, user_id, ms);
              }

			tmp_query->SQL->Add(sqltext);

			if (sn != "")
			  tmp_query->ParamByName("sn")->AsString = sn;

			if (model != "")
			  tmp_query->ParamByName("model")->AsString = model;

			if (loc_id != "")
			  tmp_query->ParamByName("loc")->AsInteger = loc_id.ToInt();

			if (id != "")
			  tmp_query->ParamByName("id")->AsInteger = itm_id;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();

			if (old_sn != sn)
			  AddHistoryRecord(user_id, OT_CH_SN, itm_id);

			if (old_model != model)
			  AddHistoryRecord(user_id, OT_CH_MODEL, itm_id);

			if (old_loc_id != loc_id)
			  AddHistoryRecord(user_id, OT_CH_LOC, itm_id);

			SetChangingAgent(itm_id, user_id);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("SetItem(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::SetChangingAgent(int itm_id, int user_id)
{
  String sqltext = "UPDATE ITEMS SET LAST_AGENT_ID = :user_id WHERE ID = :id";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();

			tmp_query->SQL->Add(sqltext);

			if (user_id)
			  tmp_query->ParamByName("user_id")->AsInteger = user_id;

			if (itm_id)
			  tmp_query->ParamByName("id")->AsInteger = itm_id;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("SetChangingAgent(): " + e.ToString());
          }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

UserInfo __fastcall TTechService::Authorisation(const String &login, const String &pass)
{
  UserInfo res;

  String sqltext = "SELECT ID, PASS, ROLE FROM AGENTS";

  if (login != "")
	sqltext += " WHERE LOGIN = :login";
  else
	{
	  res.ID = -1;
	  return res;
    }

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
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
					res.Role = tmp_query->FieldByName("NAME")->AsString;
				  }
				else
				  {
					res.ID = -1;
				  }
			  }
			else if (tmp_query->RecordCount > 1)
			  {
				res.ID = -1;
			  }
			else
			  {
				res.ID = -1;
			  }

			tmp_query->Close();
		  }
		catch (Exception &e)
		  {
			res.ID = -1;
			tmp_tr->Rollback();
			SendLogToConsole("Authorisation(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TTechService::IsAdmin(int user_id)
{
  bool res;
  String sqltext = "SELECT ROLE FROM AGENTS WHERE ID = :user_id";

  if (!user_id)
	{
	  SendLogToConsole("IsAdmin(): Невідомий користувач!");

	  return false;
	}

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("user_id")->AsInteger = user_id;

			tmp_query->Prepare();
			tmp_query->Open();
			tmp_tr->Commit();

			if (tmp_query->RecordCount > 0)
			  {
				tmp_query->First();

				if (tmp_query->FieldByName("ROLE")->AsString == "admin")
				  res = true;
				else
				  res = false;

				tmp_query->Close();
			  }
			else
			  {
				res = false;
				SendLogToConsole("IsAdmin(): Невідомий користувач!");
			  }
		  }
		catch (Exception &e)
		  {
			res = false;
			tmp_tr->Rollback();
			SendLogToConsole("IsAdmin(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::AddUser(const String &login,
									  const String &pass,
									  const String &name,
                                      const String &role,
									  TStringStream *ms)
{
  String sqltext = "INSERT INTO AGENTS VALUES(GEN_ID(GEN_AGENTS_ID, 1), :login, :pass, :name, :role)";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("login")->AsString = login;
			tmp_query->ParamByName("pass")->AsWideString = CryptUserPassword(pass);
			tmp_query->ParamByName("name")->AsString = name;
			tmp_query->ParamByName("role")->AsString = role;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("AddUser(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::RemoveUser(int user_id, TStringStream *ms)
{
  String sqltext = "DELETE FROM AGENTS WHERE ID = :id";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			if (user_id)
			  tmp_query->ParamByName("id")->AsInteger = user_id;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RemoveUser(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::SetUserPwd(int user_id, const String &pass, TStringStream *ms)
{
  String sqltext = "UPDATE AGENTS SET PASS = :pass WHERE ID = :id";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			if (user_id)
			  tmp_query->ParamByName("id")->AsInteger = user_id;

			if (pass != "")
			  tmp_query->ParamByName("pass")->AsWideString = CryptUserPassword(pass);

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("SetUserPwd(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::RemoveLocationID(const String &loc_id)
{
  String sqltext = "DELETE FROM LOCATIONS WHERE ID = :id";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();

			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("id")->AsInteger = loc_id.ToInt();

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RemoveLocationID(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::EditLocationID(const String &loc_id, TStringStream *ms)
{
  String sqltext = "SELECT * FROM LOCATIONS WHERE ID = :id";
  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("id")->AsInteger = loc_id.ToInt();

			tmp_query->Prepare();
			tmp_query->Open();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestLocations(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::SetLocationID(const String &id,
											const String &index,
											const String &addr,
											TStringStream *ms)
{
  String sqltext = "UPDATE LOCATIONS SET IND = :index, ADDRESS = :addr WHERE ID = :id";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();

			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("id")->AsInteger = id.ToInt();
			tmp_query->ParamByName("index")->AsString = index;
			tmp_query->ParamByName("addr")->AsString = addr;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("SetLocationID(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

int __fastcall TTechService::AddLocationID(const String &index, const String &addr, TStringStream *ms)
{
  String sqltext = "INSERT INTO LOCATIONS VALUES (:id, :index, :addr)";
  int id;

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->Open("SELECT GEN_ID(GEN_LOCS_ID, 1) AS ID FROM RDB$DATABASE");
			tmp_query->First();

			id = tmp_query->FieldByName("ID")->AsInteger;

			tmp_query->Close();

			tmp_query->SQL->Clear();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("id")->AsInteger = id;
			tmp_query->ParamByName("index")->AsString = index;
			tmp_query->ParamByName("addr")->AsString = addr;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();

		  }
		catch (Exception &e)
		  {
			id = -1;
			tmp_tr->Rollback();
			SendLogToConsole("AddLocationID(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return id;
}
//---------------------------------------------------------------------------

String __fastcall TTechService::GetUserPwd(int user_id)
{
  String res;
  String sqltext;

  if (user_id)
	sqltext = "SELECT PASS FROM AGENTS WHERE ID = :user_id";
  else
	{
	  SendLogToConsole("GetUserPwd(): Не вказано користувача!");

	  return "";
	}

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("user_id")->AsInteger = user_id;

			tmp_query->Prepare();
			tmp_query->Open();
			tmp_tr->Commit();

			if (tmp_query->RecordCount > 0)
			  {
				tmp_query->First();
				res = tmp_query->FieldByName("PASS")->AsString;
				tmp_query->Close();
			  }
			else
			  {
				res = "";
				SendLogToConsole("GetUserPwd(): Невідомий користувач!");
			  }
		  }
		catch (Exception &e)
		  {
			res = "";
			tmp_tr->Rollback();
			SendLogToConsole("GetUserPwd(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ReadSettings()
{
  try
	 {
	   TRegistry *reg = new TRegistry();

	   try
		  {
			reg->RootKey = HKEY_LOCAL_MACHINE;

			if (reg->OpenKey("SOFTWARE\\TechInventServer", false))
			  {
				if (reg->ValueExists("ConfigPath"))
				  ConfigPath = reg->ReadString("ConfigPath");
				else
				  throw new Exception("Відсутній параметр ConfigPath");

				reg->CloseKey();
			  }
		  }
	   __finally {delete reg;}

	   ServerVersion = GetVersionInString(String(ConfigPath + "\\TIService.exe").c_str());

	   if (ReadParameter(ConfigPath + "\\service.conf", "ServerName", &ServerName, TT_TO_STR) != RP_OK)
		 throw new Exception("Помилка читання параметру ServerName");

	   if (ReadParameter(ConfigPath + "\\service.conf", "DBHost", &DBHost, TT_TO_STR) != RP_OK)
		 throw new Exception("Помилка читання параметру DBHost");

	   if (ReadParameter(ConfigPath + "\\service.conf", "DBPath", &DBPath, TT_TO_STR) != RP_OK)
		 throw new Exception("Помилка читання параметру DBPath");

	   if (ReadParameter(ConfigPath + "\\service.conf", "ListenPort", &ListenPort, TT_TO_INT) != RP_OK)
		 throw new Exception("Помилка читання параметру ListenPort");

	   if (ReadParameter(ConfigPath + "\\service.conf", "ConsolePort", &ConsolePort, TT_TO_INT) != RP_OK)
		 throw new Exception("Помилка читання параметру ConsolePort");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("ReadSettings(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::StartServer()
{
  try
	 {
	   ConnectionServer->DefaultPort = ListenPort;
	   ConnectionServer->Active = true;
	   SendLogToConsole("StartServer(): OK");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("StartServer(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::StopServer()
{
  try
	 {
	   ConnectionServer->Active = false;
	   SendLogToConsole("StopServer(): OK");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("StopServer(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::SendLogToConsole(const String &msg)
{
  if (!DirectoryExists(ConfigPath + "\\Logs"))
	CreateDir(ConfigPath + "\\Logs");

  SaveLog(ConfigPath + "\\Logs\\" + DateToStr(Date()) + ".log", msg);

  TIdTCPClient *sender;
  TStringStream *data = new TStringStream(msg, TEncoding::UTF8, false);

  try
	 {
	   try
		  {
			sender = CreateSimpleTCPSender(L"127.0.0.1", ConsolePort);
			sender->Connect();
			sender->IOHandler->Write(data, data->Size, true);
		  }
	   catch (Exception &e)
		  {
			SaveLog(ConfigPath + "\\Logs\\" + DateToStr(Date()) + ".log", e.ToString());
          }
	 }
  __finally {delete data; if (sender) FreeSimpleTCPSender(sender);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::GenerateLocationList(TStringStream *output)
{
  try
	 {
        TFDTransaction *tmp_tr = CreateNewTransactionObj();
		TFDQuery *dataset = CreateNewQueryObj(tmp_tr);
		TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

		try
		   {
			 output->Position = 0;
			 String str = output->ReadString(output->Size);

			 try
				{
				  String sqltext = "SELECT * FROM LOCATIONS WHERE ID > 0";

				  tmp_tr->StartTransaction();
				  dataset->SQL->Add(sqltext);

				  dataset->Open();
				  tmp_tr->Commit();
				}
			 catch (Exception &e)
				{
				  tmp_tr->Rollback();
				  SendLogToConsole("GenerateLocationList(): " + e.ToString());
				}

             try
				{
				  dataset->First();

				  while (!dataset->Eof)
					{
					  ms->WriteString("<option value=\"");
					  ms->WriteString(dataset->FieldByName("ID")->AsString);
					  ms->WriteString("\">");
					  ms->WriteString(dataset->FieldByName("IND")->AsString + " | ");
					  ms->WriteString(dataset->FieldByName("ADDRESS")->AsString);
					  ms->WriteString("</option>\r\n");
					  dataset->Next();
					}

                  ms->Position = 0;
				  str = ParseString(str, "[***]", ms->DataString);
				  output->Clear();
                  output->WriteString(str);
				}
			 catch (Exception &e)
				{
				  SendLogToConsole("GenerateLocationList(): " + e.ToString());
				}
		   }
		__finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(dataset); delete ms;}
	 }
  catch (Exception &e)
	 {

	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::AddHistoryRecord(int agent_id, OperationType operation_id, int item_id)
{
  String sqltext =
"INSERT INTO CHANGES \
VALUES (GEN_ID(GEN_CHANGES_ID, 1), :tm, :itm, :agent, :operation)";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("tm")->AsDateTime = Date().CurrentDateTime();
			tmp_query->ParamByName("itm")->AsInteger = item_id;
			tmp_query->ParamByName("agent")->AsInteger = agent_id;
			tmp_query->ParamByName("operation")->AsInteger = operation_id;

            tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("AddHistoryRecord(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
TFDTransaction *CreateNewTransactionObj()
{
  TFDTransaction *t = new TFDTransaction(NULL);

  t->Connection = TechService->StatConnection;
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

  q->Connection = TechService->StatConnection;
  q->Transaction = t;

  return q;
}
//---------------------------------------------------------------------------

void DeleteTransactionObj(TFDTransaction *t)
{
  if (t)
	delete t;
}
//---------------------------------------------------------------------------

void DeleteQueryObj(TFDQuery *q)
{
  if (q)
	delete q;
}
//---------------------------------------------------------------------------

String __fastcall TTechService::CryptUserPassword(const String &pass)
{
  String res;

  try
	 {
	   //res = EncryptText(pass.c_str(), AccCryptKey);
	 }
  catch(Exception &e)
	 {
	   res = "";
	   SendLogToConsole("CryptUserAuthID(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TMemoryStream* __fastcall TTechService::CryptData(String data, const char *pass)
{
  TMemoryStream *res = new TMemoryStream();

  TAESCypher *cypher = new TAESCypher(data, pass);

  try
	 {
	   res->LoadFromStream(cypher->Data);

	   if (cypher->LastError != "")
		 SendLogToConsole("CryptData(): " + cypher->LastError);
	 }
  __finally{delete cypher;}

  return res;
}
//---------------------------------------------------------------------------

String __fastcall TTechService::EncryptData(TMemoryStream *crypted_data, const char *pass)
{
  String res;

  TAESCypher *cypher = new TAESCypher(crypted_data, pass, coEncrypt);

  try
	 {
	   res = cypher->DataToString();

	   if (cypher->LastError != "")
		 SendLogToConsole("EncryptData(): " + cypher->LastError);
	 }
  __finally{delete cypher;}

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ConnectionServerExecute(TIdContext *AContext)
{
  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);
  TXMLDocument *ixml;
  TStringStream *answer;

  AContext->Connection->IOHandler->ReadStream(ms);

  try
	 {
	   try //читаємо дані, що надійшли
		  {
            ms->LoadFromStream(TSAESCypher::Encrypt(ms, DataCryptKey));
			ms->Position = 0;
            SendLogToConsole(ms->ReadString(ms->Size));
		  }
	   catch (Exception &e)
		  {
			SendLogToConsole("ConnectionServerExecute: Розшифровка вхідних даних: " + e.ToString());
		  }

	   try //визначаємо тип запиту та оброблюємо його
		  {
			try
			   {
				 if (CoInitializeEx(NULL, COINIT_MULTITHREADED) != S_OK)
				   throw new Exception("Помилка CoInitializeEx");

				 ixml = CreatXMLStream(ms);
				 answer = ParseXML(ixml);
				 answer->Position = 0;
				 SendLogToConsole("Answer: " + answer->ReadString(answer->Size));
			   }
			catch (Exception &e)
			   {
				 SendLogToConsole("ConnectionServerExecute: Парсинг: " + e.ToString());
			   }
		  }
	   __finally {CoUninitialize(); delete ixml;}
	 }
  __finally {delete ms;}

  if (answer) //якщо відповідь сформовано одразу - надсилаємо її клієнту
	{
	  try
		 {
		   try
			  {
				answer->Position = 0;
				SendLogToConsole(answer->ReadString(ms->Size));
				answer->Position = 0;
				answer->LoadFromStream(TSAESCypher::Crypt(answer, DataCryptKey));
			  }
		   catch (Exception &e)
			 {
			   SendLogToConsole("ConnectionServerExecute: Шифровка вихідних даних: " + e.ToString());
			 }

		   try
			  {
				SendLogToConsole("Відправка даних");
				answer->Position = 0;
				AContext->Connection->IOHandler->Write(answer, answer->Size, true);
			  }
		   catch (Exception &e)
			  {
				SendLogToConsole("ConnectionServerExecute: Відправка даних: " + e.ToString());
			  }
		 }
	  __finally {delete answer;}
	}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ConnectionServerConnect(TIdContext *AContext)
{
  //клієнт під'єднався
  SendLogToConsole("Підключився клієнт: " + AContext->Binding->PeerIP);
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ConnectionServerDisconnect(TIdContext *AContext)
{
  //клієнт від'єднався
  SendLogToConsole("Відключився клієнт: " + AContext->Binding->PeerIP);
}
//---------------------------------------------------------------------------

TXMLDocument *__fastcall TTechService::CreatXMLStream(TStringStream *ms)
{
  TXMLDocument *ixml;

  try
	 {
	   TXMLDocument *ixml = new TXMLDocument(NULL);

	   ixml->DOMVendor = GetDOMVendor("MSXML");
	   ixml->Active = true;
	   ixml->Encoding = "UTF-8";
	   ixml->Options = ixml->Options << doNodeAutoIndent;
	   ixml->LoadFromStream(ms, xetUTF_8);
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("CreatXMLStream(): " + e.ToString());
	   ixml = NULL;
	 }

  return ixml;
}
//---------------------------------------------------------------------------

int __fastcall TTechService::SendToClient(const wchar_t *host, TStringStream *buffer)
{
  TIdTCPClient *TargetClient;
  int res = 0;

  try
	 {
	   TargetClient = CreateSimpleTCPSender(host, DEFAULT_CLIENT_PORT);

	   try
		  {
			TargetClient->Connect();
			TargetClient->IOHandler->Write(buffer, buffer->Size, true);
		  }
	   catch (Exception &e)
		  {
			SendLogToConsole(String(host) + ":" + e.ToString());
			res = -1;
		  }

	   buffer->Clear();
	 }
  __finally
	 {
	   if (TargetClient)
		 FreeSimpleTCPSender(TargetClient);
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TTechService::ConnectToSMTP()
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
	  SendLogToConsole("SMTP помилка: " + e.ToString());

	  return false;
	}

  return MailSender->Connected();
}
//-------------------------------------------------------------------------

void __fastcall TTechService::SendMsg(String mail_addr, String subject, String from, String log)
{
  if (MailSender->Connected())
	{
	  TIdMessage* msg = new TIdMessage(this);

	  msg->CharSet = "UTF-8";
	  msg->Body->Text = log;
	  msg->From->Text = from;
	  msg->Recipients->EMailAddresses = mail_addr;
	  msg->Subject = subject;
	  msg->Priority = TIdMessagePriority(mpHighest);

	  MailSender->Send(msg);
	  MailSender->Disconnect();

	  delete msg;
	}
}
//-------------------------------------------------------------------------

TStringStream* __fastcall TTechService::CreateRequest(const String &command,
													  const String &params)
{
  TStringStream *ms;

  try
	 {
	   ms = new TStringStream("", TEncoding::UTF8, true);

	   ms->WriteString("<Request>");
	   ms->WriteString("<Command>" + command + "</Command>");
	   ms->WriteString("<Params>");

	   TStringList *lst = new TStringList();

	   try
		  {
			StrToList(lst, params, ";");

			for (int i = 0; i < lst->Count; i++)
			   ms->WriteString("<Param>" + lst->Strings[i] + "</Param>");
		  }
	   __finally {delete lst;}

	   ms->WriteString("</Params>");
       ms->WriteString("</Request>");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("CreateRequest(" + command + "): " + e.ToString());

       if (ms) {delete ms;}

	   ms = NULL;
	 }

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::ParseXML(TXMLDocument *ixml)
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
		   throw new Exception("Невідомий тип XML-документу");
		 }
	 }
  catch (Exception &e)
	 {
	   res = NULL;
	   SendLogToConsole("ParseXML: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::ProcessRequest(TXMLDocument *ixml)
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

       TStringList *params = new TStringList();

	   try
		  {
            for (int i = 0; i < Params->ChildNodes->Count; i++)
			   {
				 Param = Params->ChildNodes->Nodes[i];
				 params->Add(Param->NodeValue);
			   }

			res = ExecuteCommand(command, params);
		  }
	   __finally {delete params;}
	 }
  catch (Exception &e)
	 {
       res = NULL;
	   SendLogToConsole("ProcessRequest: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::ExecuteCommand(const String &command,
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
             res = CreateAnswer("GRANTED", IntToStr(user.ID) + ";" + user.Role);
		 }
	 }
  catch (Exception &e)
	 {
	   res = NULL;
	   SendLogToConsole("ExecuteCommand: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::CreateAnswer(const String &command,
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

       TStringList *fields = new TStringList();

	   try
		  {
			for (int i = 0; i < data->Count; i++)
			   {
				 res->WriteString("<Row>");

				 StrToList(fields, data->Strings[i], ";"); //розбиваємо рядок на стовпці

				 for (int j = 0; j < fields->Count; i++)
					res->WriteString("<Field>" + fields->Strings[j] + "</Field>");

				 res->WriteString("</Row>");
               }

		  }
	   __finally {delete fields;}

	   res->WriteString("</Data>");
	   res->WriteString("</Answer>");
	 }
  catch (Exception &e)
	 {
       if (res) delete res;
	   res = NULL;
	   SendLogToConsole("CreateAnswer: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::CreateAnswer(const String &command,
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

	   TStringList *rows = new TStringList();
       TStringList *fields = new TStringList();

	   try
		  {
            StrToList(rows, data, ";"); //розбиваємо дані на рядки

			for (int i = 0; i < rows->Count; i++)
			   {
				 res->WriteString("<Row>");

				 StrToList(fields, rows->Strings[i], ";"); //розбиваємо рядок на стовпці

				 for (int j = 0; j < fields->Count; i++)
					res->WriteString("<Field>" + fields->Strings[j] + "</Field>");

				 res->WriteString("</Row>");
               }

		  }
	   __finally {delete rows; delete fields;}

	   res->WriteString("</Data>");
	   res->WriteString("</Answer>");
	 }
  catch (Exception &e)
	 {
       if (res) delete res;
	   res = NULL;
	   SendLogToConsole("CreateAnswer: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::CreateAnswer()
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
	   SendLogToConsole("CreateAnswer: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ProcessAnswer(TXMLDocument *ixml)
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
	   SendLogToConsole("ProcessAnswer: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

