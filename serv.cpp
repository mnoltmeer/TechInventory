//---------------------------------------------------------------------------
#include "..\work-functions\MyFunc.h"
#include "html_headers.h"
#include "serv.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

int HttpPort, RemoteConsolePort;
	String DBHost, DBPath, ServerName, ServerVersion, ConfigPath;
	HINSTANCE dllhandle;

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
	   while (!Terminated) //просто чекаємо поки працює веб-сервер
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

	   if (!LoadCryptoDLL())
		 {
		   SendLogToConsole("LoadCryptoDLL(): Помилка завантаження бібліотеки криптографування! Робота сервісу неможлива!");
		 }
	   else
		 {
		   ConnectToDB();
		   StartHttpServer();
		   RemSessionTimer->Enabled = true;
		   SendLogToConsole("Службу запущено");
		 }
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
	   RemSessionTimer->Enabled = false;
	   StopHttpServer();
	   DisconnectFromDB();
	   UnLoadCryptoDLL();
	   SendLogToConsole("Службу зупинено");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("ServiceStop(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::HttpServerCommandGet(TIdContext *AContext, TIdHTTPRequestInfo *ARequestInfo,
		  TIdHTTPResponseInfo *AResponseInfo)
{
  AResponseInfo->ContentType = "text/html; charset=utf-8";

  if (ARequestInfo->Document == "/") //запит головної сторінки
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   if (!CheckAuthAndLoad(ConfigPath + "\\html\\adm_index.html",
								 ROLE_ADMIN, ARequestInfo, ms))
			 {
			   CheckAuthAndLoad(ConfigPath + "\\html\\usr_index.html",
								ROLE_USER, ARequestInfo, ms);
             }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/auth.html") //спроба логіну у систему
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int login_ind = ARequestInfo->Params->IndexOfName("login"),
			   pass_ind = ARequestInfo->Params->IndexOfName("pass");

		   String login, pass;

		   if (login_ind > -1)
			 {
			   login = ARequestInfo->Params->Strings[login_ind];
			   login.Delete(1, login.Pos("="));
			 }

		   if (pass_ind > -1)
			 {
			   pass = ARequestInfo->Params->Strings[pass_ind];
			   pass.Delete(1, pass.Pos("="));
			 }

		   int user_id = Authorisation(login, pass, ms);

		   if (user_id) //користувач авторизований додамо йому куку
			 {
			   String hash = GenerateSessionHash();
			   TIdCookie *session_cookie = AResponseInfo->Cookies->Add();
			   session_cookie->CookieName = "TISession";
			   session_cookie->Value = hash;
			   //session_cookie->Domain = "testarm";
			   session_cookie->Expires = Date().CurrentDate() + CookieValidDays;

			   AddSessionID(hash, user_id); //додамо нову сессію
			 }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/logout.html") //вихід з системи
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int cookie_ind = ARequestInfo->Cookies->GetCookieIndex("TISession", 0);

		   if (cookie_ind > -1)
			 {
			   String cookie_hash = ARequestInfo->Cookies->Cookies[cookie_ind]->Value;
			   int user_id = IsValidSessionID(cookie_hash);

			   if (user_id)
				 {
				   RemoveSessionID(cookie_hash, user_id);
                   GenerateSuccessPage("Ви вийшли з системи", ms);
				 }
			   else
				 GenerateErrorPage("Невідомий користувач", ms);
			 }
		   else
			 GenerateErrorPage("Не вдається визначити сессію", ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/items.html") //запит сторінки перегляду Пристроїв
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   CheckAuthAndLoad(ConfigPath + "\\html\\items.html", ROLE_USER, ARequestInfo, ms);
		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/item.html") //запит даних Пристрою
	{
	  try
		 {
		   TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

		   try
			  {
				if (CheckAuth(ROLE_USER, ARequestInfo, ms))
				  {
					int inn_ind = ARequestInfo->Params->IndexOfName("inn"),
						sn_ind = ARequestInfo->Params->IndexOfName("sn");

					bool sel_all = false;

					String p_inn, p_sn;

					if (inn_ind > -1)
					  {
						p_inn = ARequestInfo->Params->Strings[inn_ind];
						p_inn = TIdURI::URLDecode(p_inn, IndyTextEncoding_UTF8());
						p_inn.Delete(1, p_inn.Pos("="));
					  }

					if (sn_ind > -1)
					  {
						p_sn = ARequestInfo->Params->Strings[sn_ind];
						p_sn = TIdURI::URLDecode(p_sn, IndyTextEncoding_UTF8());
						p_sn.Delete(1, p_sn.Pos("="));
					  }

					if ((p_inn == "") && (p_sn == ""))
					  sel_all = true;

					if (sel_all)
					  RequestAllItems(ms);
					else
					  RequestItem(ms, p_inn, p_sn);
				  }

				ms->Position = 0;
				AResponseInfo->ContentText = ms->ReadString(ms->Size);
			  }
		   __finally {delete ms;}
		 }
	  catch (Exception &e)
		 {
		   SendLogToConsole(e.ToString());
		 }
	}
  else if (ARequestInfo->Document == "/show_items.html") //запит даних Пристроїв по локації
	{
	  try
		 {
		   TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

		   try
			  {
                int ind_ind = ARequestInfo->Params->IndexOfName("ind");

				String p_ind;

				if (CheckAuth(ROLE_USER, ARequestInfo, ms))
				  {
					if (ind_ind > -1)
					  {
						p_ind = ARequestInfo->Params->Strings[ARequestInfo->Params->IndexOfName("ind")];
						p_ind = TIdURI::URLDecode(p_ind, IndyTextEncoding_UTF8());
						p_ind.Delete(1, p_ind.Pos("="));

						RequestItems(ms, p_ind);
					  }
					else
					  GenerateErrorPage("Помилка парсингу параметру", ms);
				  }

                ms->Position = 0;
				AResponseInfo->ContentText = ms->ReadString(ms->Size);
			  }
		   __finally {delete ms;}
		 }
	  catch (Exception &e)
		 {
		   SendLogToConsole(e.ToString());
		 }
	}
  else if (ARequestInfo->Document == "/history.html") //запит сторінки історії змін
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   CheckAuthAndLoad(ConfigPath + "\\html\\history.html", ROLE_USER, ARequestInfo, ms);
		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/history_request.html") //запит інформації по змінам
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   if (CheckAuth(ROLE_USER, ARequestInfo, ms))
			 {
               int inn_ind = ARequestInfo->Params->IndexOfName("inn"),
				   sn_ind = ARequestInfo->Params->IndexOfName("sn"),
				   date_fr_ind = ARequestInfo->Params->IndexOfName("datefrom"),
				   date_to_ind = ARequestInfo->Params->IndexOfName("dateto"),
				   sort_ind = ARequestInfo->Params->IndexOfName("sortby");

			   bool sel_all;

			   String inn, sn, datefrom, dateto, sort;

			   if (inn_ind > -1)
				 {
				   inn = ARequestInfo->Params->Strings[ARequestInfo->Params->IndexOfName("inn")];
				   inn = TIdURI::URLDecode(inn, IndyTextEncoding_UTF8());
				   inn.Delete(1, inn.Pos("="));
				 }

			   if (sn_ind > -1)
				 {
				   sn = ARequestInfo->Params->Strings[ARequestInfo->Params->IndexOfName("sn")];
				   sn = TIdURI::URLDecode(sn, IndyTextEncoding_UTF8());
				   sn.Delete(1, sn.Pos("="));
				 }

			   if (date_fr_ind > -1)
				 {
				   datefrom = ARequestInfo->Params->Strings[ARequestInfo->Params->IndexOfName("datefrom")];
				   datefrom.Delete(1, datefrom.Pos("="));
				 }

			   if (date_to_ind > -1)
				 {
				   dateto = ARequestInfo->Params->Strings[ARequestInfo->Params->IndexOfName("dateto")];
				   dateto.Delete(1, dateto.Pos("="));
				 }

			   if (sort_ind > -1)
				 {
				   sort = ARequestInfo->Params->Strings[ARequestInfo->Params->IndexOfName("sortby")];
				   sort = TIdURI::URLDecode(sort, IndyTextEncoding_UTF8());
				   sort.Delete(1, sort.Pos("="));
				 }

			   RequestHistory(ms, inn, sn, datefrom, dateto, sort);
			 }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/new.html") //запит сторінки додання нового Пристрою
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   if (CheckAuthAndLoad(ConfigPath + "\\html\\new.html", ROLE_USER, ARequestInfo, ms))
			 GenerateLocationList(ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/add_item.html") //додання нового Пристрою
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int user_id = CheckAuth(ROLE_USER, ARequestInfo, ms);

		   if (!user_id)
			 ms->WriteString(String(login_hdr));
		   else
			 {
               int inn_ind = ARequestInfo->Params->IndexOfName("inn"),
				   sn_ind = ARequestInfo->Params->IndexOfName("sn"),
				   model_ind = ARequestInfo->Params->IndexOfName("model"),
				   loc_ind = ARequestInfo->Params->IndexOfName("location");

				String p_inn, p_sn, p_model, p_loc;

				if (inn_ind > -1)
				  {
					p_inn = ARequestInfo->Params->Strings[inn_ind];
					p_inn = TIdURI::URLDecode(p_inn, IndyTextEncoding_UTF8());
					p_inn.Delete(1, p_inn.Pos("="));
				  }

				if (sn_ind > -1)
				  {
					p_sn = ARequestInfo->Params->Strings[sn_ind];
					p_sn = TIdURI::URLDecode(p_sn, IndyTextEncoding_UTF8());
					p_sn.Delete(1, p_sn.Pos("="));
				  }

				if (model_ind > -1)
				  {
					p_model = ARequestInfo->Params->Strings[model_ind];
					p_model = TIdURI::URLDecode(p_model, IndyTextEncoding_UTF8());
					p_model.Delete(1, p_model.Pos("="));
				  }

				if (loc_ind > -1)
				  {
					p_loc = ARequestInfo->Params->Strings[loc_ind];
					p_loc = TIdURI::URLDecode(p_loc, IndyTextEncoding_UTF8());
		  			p_loc.Delete(1, p_loc.Pos("="));
				  }

			   AddItem(p_inn, p_sn, p_model, p_loc, user_id, ms);
			 }

           ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/edit_item.html") //зміна даних про Пристрій
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   if (CheckAuth(ROLE_USER, ARequestInfo, ms))
			 {
               int id_ind = ARequestInfo->Params->IndexOfName("id");

			   String itm_id;

			   if (id_ind > -1)
				 {
				   itm_id = ARequestInfo->Params->Strings[id_ind];
				   itm_id.Delete(1, itm_id.Pos("="));
				 }

			   EditItem(itm_id, ms);
             }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/set_item.html") //підтвердження змін даних Пристрою
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int user_id = CheckAuth(ROLE_USER, ARequestInfo, ms);

		   if (!user_id)
			 ms->WriteString(String(login_hdr));
		   else
			 {
               int inn_ind = ARequestInfo->Params->IndexOfName("inn"),
				   sn_ind = ARequestInfo->Params->IndexOfName("sn"),
				   model_ind = ARequestInfo->Params->IndexOfName("model"),
				   loc_ind = ARequestInfo->Params->IndexOfName("location"),
				   id_ind = ARequestInfo->Params->IndexOfName("id");

				String p_inn, p_sn, p_model, p_loc, p_id;

				if (inn_ind > -1)
				  {
					p_inn = ARequestInfo->Params->Strings[inn_ind];
					p_inn = TIdURI::URLDecode(p_inn, IndyTextEncoding_UTF8());
					p_inn.Delete(1, p_inn.Pos("="));
				  }

				if (sn_ind > -1)
				  {
					p_sn = ARequestInfo->Params->Strings[sn_ind];
					p_sn = TIdURI::URLDecode(p_sn, IndyTextEncoding_UTF8());
					p_sn.Delete(1, p_sn.Pos("="));
				  }

				if (model_ind > -1)
				  {
					p_model = ARequestInfo->Params->Strings[model_ind];
					p_model = TIdURI::URLDecode(p_model, IndyTextEncoding_UTF8());
					p_model.Delete(1, p_model.Pos("="));
				  }

				if (loc_ind > -1)
				  {
					p_loc = ARequestInfo->Params->Strings[loc_ind];
					p_loc = TIdURI::URLDecode(p_loc, IndyTextEncoding_UTF8());
					p_loc.Delete(1, p_loc.Pos("="));
				  }

				if (id_ind > -1)
				  {
					p_id = ARequestInfo->Params->Strings[id_ind];
					p_id.Delete(1, p_id.Pos("="));
				  }

			   SetItem(p_id, p_inn, p_sn, p_model, p_loc, user_id, ms);
			 }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/remove_item.html") //вивід Пристрою з експлуатації
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int user_id = CheckAuth(ROLE_USER, ARequestInfo, ms);

		   if (!user_id)
			 ms->WriteString(String(login_hdr));
		   else
			 {
               int id_ind = ARequestInfo->Params->IndexOfName("id");

			   String p_id;

			   if (id_ind > -1)
				 {
				   p_id = ARequestInfo->Params->Strings[id_ind];
				   p_id.Delete(1, p_id.Pos("="));
				 }

			   RemoveItem(p_id, user_id, ms);
			 }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/admin.html") //запит сторінки з опціями адміна
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   CheckAuthAndLoad(ConfigPath + "\\html\\admin.html", ROLE_ADMIN, ARequestInfo, ms);
		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/userlist.html") //запит сторінки з переліком користувачів
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 RequestUsers(ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/new_user.html") //запит сторінки додання нового користувача
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   CheckAuthAndLoad(ConfigPath + "\\html\\new_user.html", ROLE_USER, ARequestInfo, ms);
		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/add_user.html") //додання користувача та вивід результату
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int login_ind = ARequestInfo->Params->IndexOfName("login"),
			   pass_ind = ARequestInfo->Params->IndexOfName("pass"),
			   name_ind = ARequestInfo->Params->IndexOfName("name"),
			   role_ind = ARequestInfo->Params->IndexOfName("role");

		   String p_name, p_pass, p_login, p_role;

		   if (login_ind > -1)
			 {
			   p_login = ARequestInfo->Params->Strings[login_ind];
			   p_login = TIdURI::URLDecode(p_login, IndyTextEncoding_UTF8());
			   p_login.Delete(1, p_login.Pos("="));
			 }

		   if (pass_ind > -1)
			 {
			   p_pass = ARequestInfo->Params->Strings[pass_ind];
			   p_pass = TIdURI::URLDecode(p_pass, IndyTextEncoding_UTF8());
			   p_pass.Delete(1, p_pass.Pos("="));
			 }

		   if (name_ind > -1)
			 {
			   p_name = ARequestInfo->Params->Strings[name_ind];
			   p_name = TIdURI::URLDecode(p_name, IndyTextEncoding_UTF8());
			   p_name.Delete(1, p_name.Pos("="));
			 }

		   if (role_ind > -1)
			 {
			   p_role = ARequestInfo->Params->Strings[role_ind];
			   p_role = TIdURI::URLDecode(p_role, IndyTextEncoding_UTF8());
			   p_role.Delete(1, p_role.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 AddUser(p_login, p_pass, p_name, p_role, ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/remove_user.html") //видалення користувача з системи та вивід результату
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int id_ind = ARequestInfo->Params->IndexOfName("id");

		   String p_id;

		   if (id_ind > -1)
			 {
			   p_id = ARequestInfo->Params->Strings[id_ind];
			   p_id.Delete(1, p_id.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 RemoveUser(p_id.ToInt(), ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/set_pwd.html") //вивід форми встановлення AuthID користувача
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int id_ind = ARequestInfo->Params->IndexOfName("id");

		   String p_id;

		   if (id_ind > -1)
			 {
			   p_id = ARequestInfo->Params->Strings[id_ind];
			   p_id.Delete(1, p_id.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 {
			   String final = String(set_pwd_hdr);
			   final = ParseString(final, "[***]", p_id);
			   ms->WriteString(final);
			 }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/change_pwd.html") //вивід форми зміни AuthID для поточного користувача
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int id = Authorised(ARequestInfo); //отримуємо ІД поточного юзера

		   if (CheckAuth(ROLE_USER, ARequestInfo, ms))
			 {
			   String final = String(change_pwd_hdr);
			   final = ParseString(final, "[***]", IntToStr(id));
			   ms->WriteString(final);
			 }

           ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/pwd.html") //зміна AuthID користувача та вивід результату
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int id_ind = ARequestInfo->Params->IndexOfName("id"),
			   pwd_ind = ARequestInfo->Params->IndexOfName("new_pwd"),
			   conf_ind = ARequestInfo->Params->IndexOfName("new_pwd_confirm"),
			   old_ind = ARequestInfo->Params->IndexOfName("old_pwd");

		   String p_id, p_pwd, p_conf, p_old;

		   if (id_ind > -1)
			 {
			   p_id = ARequestInfo->Params->Strings[id_ind];
			   p_id.Delete(1, p_id.Pos("="));
			 }

		   if (pwd_ind > -1)
			 {
			   p_pwd = ARequestInfo->Params->Strings[pwd_ind];
			   p_pwd = TIdURI::URLDecode(p_pwd, IndyTextEncoding_UTF8());
			   p_pwd.Delete(1, p_pwd.Pos("="));
			 }

		   if (conf_ind > -1)
			 {
			   p_conf = ARequestInfo->Params->Strings[conf_ind];
			   p_conf.Delete(1, p_conf.Pos("="));
			 }

		   if (old_ind > -1)
			 {
			   p_old = ARequestInfo->Params->Strings[old_ind];
			   p_old.Delete(1, p_old.Pos("="));
			 }

           if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 SetUserPwd(p_id.ToInt(), p_pwd, ms);
		   else if (CheckAuth(ROLE_USER, ARequestInfo, ms))
			 {
			   if (GetUserPwd(p_id.ToInt()) != CryptUserPassword(p_old))
				 GenerateErrorPage("Не вірний старий пароль", ms);
			   else if (p_pwd != p_conf)
				 GenerateErrorPage("Новий пароль та підтвердження не співпадають", ms);
			   else
				 {
				   SetUserPwd(p_id.ToInt(), p_pwd, ms);
				 }
			 }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/sessions.html") //запит переліку сесій
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 RequestSessions(ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/remove_session.html") //видалення сесії та вивід результату
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int id_ind = ARequestInfo->Params->IndexOfName("id");

		   String p_id;

		   if (id_ind > -1)
			 {
			   p_id = ARequestInfo->Params->Strings[id_ind];
			   p_id.Delete(1, p_id.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 {
			   RemoveSessionID(p_id);
			   GenerateSuccessPage("Сесію видалено", ms);
			 }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/log.html") //запит сторінки вибору логу
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   CheckAuthAndLoad(ConfigPath + "\\html\\log.html", ROLE_ADMIN, ARequestInfo, ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/showlog.html") //видалення сесії та вивід результату
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int date_ind = ARequestInfo->Params->IndexOfName("datelog");

		   String p_date;

		   if (date_ind > -1)
			 {
			   p_date = ARequestInfo->Params->Strings[date_ind];
			   p_date.Delete(1, p_date.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 RequestLog(p_date, ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/locations.html") //вивід всіх локацій з можливістю редагувати
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 RequestLocations(ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/remove_loc.html") //видалення локації та вивід результату
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int id_ind = ARequestInfo->Params->IndexOfName("id");

		   String p_id;

		   if (id_ind > -1)
			 {
			   p_id = ARequestInfo->Params->Strings[id_ind];
			   p_id.Delete(1, p_id.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 {
			   RemoveLocationID(p_id);
			   GenerateSuccessPage("Локацію видалено", ms);
			 }

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/edit_loc.html") //вивід форми редагування локації
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int id_ind = ARequestInfo->Params->IndexOfName("id");

		   String p_id;

		   if (id_ind > -1)
			 {
			   p_id = ARequestInfo->Params->Strings[id_ind];
			   p_id.Delete(1, p_id.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 EditLocationID(p_id, ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/set_loc.html") //вивід форми редагування локації
	{
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int id_ind = ARequestInfo->Params->IndexOfName("id"),
			   ind_ind = ARequestInfo->Params->IndexOfName("index"),
			   adr_ind = ARequestInfo->Params->IndexOfName("addr");

		   String p_id, p_ind, p_adr;

		   if (id_ind > -1)
			 {
			   p_id = ARequestInfo->Params->Strings[id_ind];
			   p_id.Delete(1, p_id.Pos("="));
			 }

		   if (ind_ind > -1)
			 {
			   p_ind = ARequestInfo->Params->Strings[ind_ind];
			   p_ind.Delete(1, p_ind.Pos("="));
			 }

		   if (adr_ind > -1)
			 {
			   p_adr = ARequestInfo->Params->Strings[adr_ind];
			   p_adr = TIdURI::URLDecode(p_adr, IndyTextEncoding_UTF8());
			   p_adr.Delete(1, p_adr.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 SetLocationID(p_id, p_ind, p_adr, ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}
  else if (ARequestInfo->Document == "/add_loc.html") //додання нової локації
	{
//перевірити
	  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

	  try
		 {
		   int ind_ind = ARequestInfo->Params->IndexOfName("index"),
			   adr_ind = ARequestInfo->Params->IndexOfName("addr");

		   String p_ind, p_adr;

		   if (ind_ind > -1)
			 {
			   p_ind = ARequestInfo->Params->Strings[ind_ind];
			   p_ind.Delete(1, p_ind.Pos("="));
			 }

		   if (adr_ind > -1)
			 {
			   p_adr = ARequestInfo->Params->Strings[adr_ind];
			   p_adr = TIdURI::URLDecode(p_adr, IndyTextEncoding_UTF8());
			   p_adr.Delete(1, p_adr.Pos("="));
			 }

		   if (CheckAuth(ROLE_ADMIN, ARequestInfo, ms))
			 AddLocationID(p_ind, p_adr, ms);

		   ms->Position = 0;
		   AResponseInfo->ContentText = ms->ReadString(ms->Size);
		 }
	  __finally {delete ms;}
	}

  AResponseInfo->ContentText = ParseString(AResponseInfo->ContentText,
										   "$ServerName",
										   ServerName);

  AResponseInfo->ContentText = ParseString(AResponseInfo->ContentText,
										   "$ServerVersion",
										   ServerVersion);
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
		   StatConnection->Params->Add("User_Name=sysdba");
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

			GenerateResultPage(RT_HIST, tmp_query, ms);
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

			GenerateResultPage(RT_HIST, tmp_query, ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestAllChanges(): " + e.ToString());
			GenerateErrorPage("Помилка запиту змін", ms);
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

			GenerateResultPage(RT_ITEM, tmp_query, ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestAllItems(): " + e.ToString());
			GenerateErrorPage("Помилка запиту переліку Присторїв", ms);
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

			GenerateResultPage(RT_USER, tmp_query, ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestUsers(): " + e.ToString());
			GenerateErrorPage("Помилка запиту переліку користувачів", ms);
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TTechService::RequestSessions(TStringStream *ms)
{
  String sqltext = "SELECT * FROM SESSIONS";
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

			GenerateResultPage(RT_SESS, tmp_query, ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestSessions(): " + e.ToString());
			GenerateErrorPage("Помилка запиту переліку сесій", ms);
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
	   GenerateErrorPage("Помилка відкриття логу", ms);
	 }

  if (!FileExists(ConfigPath + "\\Logs\\" + format_date + ".log"))
	{
	  SendLogToConsole("RequestLog(): відсутній файл " +
					   ConfigPath + "\\Logs\\" +
					   format_date + ".log");
	  GenerateErrorPage("Файл логу не знайдений", ms);
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
		   GenerateErrorPage("Помилка відкриття логу", ms);
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

			GenerateResultPage(RT_LOCS, tmp_query, ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestLocations(): " + e.ToString());
			GenerateErrorPage("Помилка запиту переліку локацій", ms);
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

            GenerateResultPage(RT_ITEM, tmp_query, ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestItem(): " + e.ToString());
			GenerateErrorPage("Помилка запиту відомостей про Пристрій", ms);
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

			GenerateResultPage(RT_ITEM, tmp_query, ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestItems(): " + e.ToString());
			GenerateErrorPage("Помилка запиту переліку Пристроїв", ms);
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

			GenerateSuccessPage("Пристрій додано", ms);

			AddHistoryRecord(user_id, OT_ADD, id);
            SetChangingAgent(id, user_id);
		  }
		catch (Exception &e)
		  {
			id = -1;
			tmp_tr->Rollback();
			SendLogToConsole("AddItem(): " + e.ToString());
			GenerateErrorPage("Не вдалося створити новий Пристрій", ms);
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
	  GenerateErrorPage("Не вказано ID Пристрою!", ms);

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

			GenerateResultPage(RT_EDIT, tmp_query, ms);
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

			GenerateSuccessPage("Пристрій виведено з експлуатації", ms);
			AddHistoryRecord(user_id, OT_REMOVE, id.ToInt());
			SetChangingAgent(id.ToInt(), user_id);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RemoveItem(): " + e.ToString());
			GenerateErrorPage("Помилка виведення Пристрою з експлуатації", ms);
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

			GenerateSuccessPage("Дані змінено", ms);

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
			GenerateErrorPage("Не вдалося змінити властивості Пристрою", ms);
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

 int __fastcall TTechService::Authorisation(const String &login,
											const String &pass,
											TStringStream *ms)
{
  int user_id;
  String sqltext = "SELECT ID, PASS, NAME FROM AGENTS";

  if (login != "")
	sqltext += " WHERE LOGIN = :login";
  else
	{
	  GenerateErrorPage("Не вказано логін!", ms);

	  return 0;
	}

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			String hash_pass = CryptUserPassword(pass);

			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("login")->AsString = login;

			tmp_query->Prepare();
			tmp_query->Open();
            tmp_tr->Commit();

			if (tmp_query->RecordCount == 1)
			  {
				tmp_query->First();

				if (tmp_query->FieldByName("PASS")->AsString == hash_pass)
				  {
                    user_id = tmp_query->FieldByName("ID")->AsInteger;
					String username = tmp_query->FieldByName("NAME")->AsString;
					GenerateSuccessPage("Ви увійшли як " + username, ms);
                  }
				else
				  {
                    user_id = 0;
					GenerateErrorPage("Невірний пароль!", ms);
                  }
			  }
			else if (tmp_query->RecordCount > 1)
			  {
                user_id = 0;
				GenerateErrorPage("Дублювання облікових записів. Будь ласка, сповістіть розробника або координатора сервісу!", ms);
              }
			else
			  {
				user_id = 0;
				GenerateErrorPage("Користувач не знайдений!", ms);
			  }

			tmp_query->Close();
		  }
		catch (Exception &e)
		  {
			user_id = 0;
			tmp_tr->Rollback();
			SendLogToConsole("Authorisation(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return user_id;
}
//---------------------------------------------------------------------------

int __fastcall TTechService::Authorised(TIdHTTPRequestInfo *RequestInfo)
{
  int cookie_ind = RequestInfo->Cookies->GetCookieIndex("TISession", 0);

  if (cookie_ind > -1)
	{
	  String cookie_hash = RequestInfo->Cookies->Cookies[cookie_ind]->Value;

	  return IsValidSessionID(cookie_hash);
	}
  else
	return 0;
}
//---------------------------------------------------------------------------

int __fastcall TTechService::CheckAuthAndLoad(const String &page_file,
											  bool check_admin,
											  TIdHTTPRequestInfo *RequestInfo,
											  TStringStream *ms)
{
  int user_id;
  bool is_admin;

  try
	 {
	   ms->Clear();

	   user_id = Authorised(RequestInfo);

       if (!user_id)
		 ms->WriteString(String(login_hdr));
	   else
		 {
		   if (check_admin)
			 is_admin = IsAdmin(user_id);

		   if (check_admin && is_admin)
			 ms->LoadFromFile(page_file);
           else if (check_admin && !is_admin)
			 {
			   GenerateErrorPage("В доступі відмовлено", ms);
               user_id = 0;
			 }
           else if (!check_admin)
			 ms->LoadFromFile(page_file);
		 }
	 }
  catch (Exception &e)
	 {
	   user_id = 0;
	   SendLogToConsole("CheckAuthAndLoad(): " + e.ToString());
	 }

  return user_id;
}
//---------------------------------------------------------------------------

int __fastcall TTechService::CheckAuth(bool check_admin,
									   TIdHTTPRequestInfo *RequestInfo,
									   TStringStream *ms)
{
  int user_id;
  bool is_admin;

  try
	 {
	   ms->Clear();

	   user_id = Authorised(RequestInfo);

       if (!user_id)
		 ms->WriteString(String(login_hdr));
	   else if (check_admin && !IsAdmin(user_id))
		 {
		   user_id = 0;
		   GenerateErrorPage("В доступі відмовлено", ms);
		 }
	 }
  catch (Exception &e)
	 {
	   user_id = 0;
	   SendLogToConsole("CheckAuth(): " + e.ToString());
	 }

  return user_id;
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

			GenerateSuccessPage("Користувач створений", ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("AddUser(): " + e.ToString());
			GenerateErrorPage("Не вдалось створити користувача", ms);
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

			GenerateSuccessPage("Користувача видалено", ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RemoveUser(): " + e.ToString());
			GenerateErrorPage("Помилка видалення користувача", ms);
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

			GenerateSuccessPage("Пароль змінено", ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("SetUserPwd(): " + e.ToString());
			GenerateErrorPage("Помилка встановлення паролю", ms);
          }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

int __fastcall TTechService::IsValidSessionID(const String &cookie_hash)
{
  int user_id;
  String sqltext = "SELECT USER_ID FROM SESSIONS WHERE HASH = :hash";

  if (cookie_hash == "")
	{
	  SendLogToConsole("IsValidSessionID(): Не вказано хеш сессії, UserID :" + IntToStr(user_id));

	  return 0;
	}

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("hash")->AsString = cookie_hash;

			tmp_query->Prepare();

			tmp_query->Open();
			tmp_tr->Commit();

			if (tmp_query->RecordCount > 0)
			  user_id = tmp_query->FieldByName("USER_ID")->AsInteger;
			else
			  user_id = 0;
		  }
		catch (Exception &e)
		  {
			user_id = 0;
			tmp_tr->Rollback();
			SendLogToConsole("IsValidSessionID(): " +
							 e.ToString() +
							 " UserID :" + IntToStr(user_id));
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return user_id;
}
//---------------------------------------------------------------------------

int __fastcall TTechService::AddSessionID(const String &session_hash, int user_id)
{
  String sqltext = "INSERT INTO SESSIONS VALUES (:id, :user, :hash, :date_add)";
  int id;

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->Open("SELECT GEN_ID(GEN_SESSION_ID, 1) AS ID FROM RDB$DATABASE");
			tmp_query->First();

			id = tmp_query->FieldByName("ID")->AsInteger;

			tmp_query->Close();

			tmp_query->SQL->Clear();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("user")->AsInteger = user_id;
			tmp_query->ParamByName("hash")->AsString = session_hash;
			tmp_query->ParamByName("id")->AsInteger = id;
			tmp_query->ParamByName("date_add")->AsDate = Date().CurrentDate();

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();
		  }
		catch (Exception &e)
		  {
			id = -1;
			tmp_tr->Rollback();
			SendLogToConsole("AddSessionID(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}

  return id;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::RemoveSessionID(const String &session_hash, int user_id)
{
  String sqltext = "DELETE FROM SESSIONS WHERE USER_ID = :user AND HASH = :hash";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();

			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("user")->AsInteger = user_id;
			tmp_query->ParamByName("hash")->AsString = session_hash;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RemoveSessionID(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::RemoveSessionID(const String &session_id)
{
  String sqltext = "DELETE FROM SESSIONS WHERE ID = :id";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();

			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("id")->AsInteger = session_id.ToInt();

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RemoveSessionID(): " + e.ToString());
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

			GenerateResultPage(RT_LOC, tmp_query, ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RequestLocations(): " + e.ToString());
			GenerateErrorPage("Помилка запиту переліку локацій", ms);
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

			GenerateSuccessPage("Дані змінено", ms);
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("SetLocationID(): " + e.ToString());
			GenerateErrorPage("Не вдалося змінити властивості Локації", ms);
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

            GenerateSuccessPage("Локацію створено", ms);
		  }
		catch (Exception &e)
		  {
			id = -1;
			tmp_tr->Rollback();
			SendLogToConsole("AddLocationID(): " + e.ToString());
            GenerateErrorPage("Не вдалося створити Локацію", ms);
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

String __fastcall TTechService::GenerateSessionHash()
{
//доробити генерацію хешей або залишити створення ІД сесії по даті/часу
  String res;

  try
	 {
	   //String dt = Date().CurrentDateTime().FormatString("yyyymmddhhnnsszzz");

	   //SetCryptKeyPath(String(ConfigPath + "\\session_hash_key").c_str());
	   //res = CryptText(String(dt).c_str());
	   res = Date().CurrentDateTime().FormatString("yyyymmddhhnnsszzz");
	 }
  catch (Exception &e)
	 {
	   res = "";
	   SendLogToConsole("GenerateSessionHash(): " + e.ToString());
     }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::RemoveOldSessions()
{
  String sqltext = "DELETE FROM SESSIONS WHERE ADDED < :target_date";

  TFDTransaction *tmp_tr = CreateNewTransactionObj();
  TFDQuery *tmp_query = CreateNewQueryObj(tmp_tr);

  try
	 {
	   try
		  {
			tmp_tr->StartTransaction();
			tmp_query->SQL->Add(sqltext);

			tmp_query->ParamByName("target_date")->AsDate = Date().CurrentDate() - CookieValidDays;

			tmp_query->Prepare();
			tmp_query->Execute();
			tmp_tr->Commit();
		  }
		catch (Exception &e)
		  {
			tmp_tr->Rollback();
			SendLogToConsole("RemoveOldSessions(): " + e.ToString());
		  }
	 }
  __finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(tmp_query);}
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

	   if (ReadParameter(ConfigPath + "\\service.conf", "HttpPort", &HttpPort, TT_TO_INT) != RP_OK)
		 throw new Exception("Помилка читання параметру HttpPort");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("ReadSettings(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::StartHttpServer()
{
  try
	 {
	   HttpServer->DefaultPort = HttpPort;
	   HttpServer->Active = true;
	   SendLogToConsole("StartHttpServer(): OK");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("StartHttpServer(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::StopHttpServer()
{
  try
	 {
	   HttpServer->Active = false;
	   SendLogToConsole("StopHttpServer(): OK");
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("StopHttpServer(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TTechService::SendLogToConsole(const String &msg)
{
  if (!DirectoryExists(ConfigPath + "\\Logs"))
	CreateDir(ConfigPath + "\\Logs");

  SaveLog(ConfigPath + "\\Logs\\" + DateToStr(Date()) + ".log", msg);

  /* //відправка логу до консолей, локальної та віддаленної
  String txt = "["
			   + DateToStr(Date())
			   + " "
			   + TimeToStr(Time())
			   + "]"
			   + " : "
			   + msg;

  if (FindPIDByHandle(ConsoleHandle))
	SendMessage(ConsoleHandle, LB_ADDSTRING, 0, (LPARAM)msg.c_str());

  TStringStream *ms = new TStringStream(msg, TEncoding::UTF8, true);

  try
	 {
       ms->Position = 0;
	   RemoteLogSender->Connect();
	   RemoteLogSender->IOHandler->Write(ms, ms->Size, true);
	 }
  __finally {delete ms;} */
}
//---------------------------------------------------------------------------

void __fastcall TTechService::GenerateResultPage(ResultPageType type,
												 TFDQuery *dataset,
												 TStringStream *output)
{
  if (type == RT_ITEM)
	{
	  try
		 {
		   output->Clear();
		   output->Position = 0;
		   output->WriteString(itm_hdr);

		   dataset->First();

		   while (!dataset->Eof)
			 {
			   output->WriteString("<tr>");
			   output->WriteString("<td>" + dataset->FieldByName("INN")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("SN")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("MODEL")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("IND")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("ADDRESS")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("NAME")->AsString + "</td>");
			   output->WriteString("<td><form method=\"post\" action=\"/edit_item.html?id=");
			   output->WriteString(dataset->FieldByName("ID")->AsString);
			   output->WriteString("\">");
			   output->WriteString("<p><button style=\"width:80px;height:25px\" type=\"submit\">Редагувати</button></p>");
			   output->WriteString("</form></td>");
			   output->WriteString("<td><form method=\"post\" action=\"/remove_item.html?id=");
			   output->WriteString(dataset->FieldByName("ID")->AsString);
			   output->WriteString("\">");
			   output->WriteString("<p><button style=\"width:80px;height:25px\" type=\"submit\">Видалити</button></p>");
			   output->WriteString("</form></td>");
			   output->WriteString("</tr>\r\n");

			   dataset->Next();
			 }

		   output->WriteString("<br>\r\n</table>\r\n");
		   output->WriteString("<br>\r\n</center>\r\n");
		   output->WriteString("<br>\r\n</body>\r\n</html>");
		 }
	  catch (Exception &e)
		 {
		   GenerateErrorPage("GenerateResultPage(): RT_ITEM: " + e.ToString(), output);
		 }
	}
  else if (type == RT_HIST)
	{
	  try
		 {
		   output->Clear();
		   output->Position = 0;
		   output->WriteString(hist_hdr);

		   dataset->First();

		   while (!dataset->Eof)
			 {
			   output->WriteString("<tr>");
			   output->WriteString("<td>" + dataset->FieldByName("DATE_OP")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("INN")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("SN")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("MODEL")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("AGENT")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("OPERATION")->AsString + "</td>");
			   output->WriteString("</tr>\r\n");

			   dataset->Next();
			 }

		   output->WriteString("<br>\r\n</table>\r\n");
           output->WriteString("<br>\r\n</center>\r\n");
		   output->WriteString("<br>\r\n</body>\r\n</html>");
		 }
	  catch (Exception &e)
		 {
		   GenerateErrorPage("GenerateResultPage(): RT_HIST: " + e.ToString(), output);
		 }
	}
  else if (type == RT_EDIT)
	{
	  try
		 {
		   output->Clear();
		   output->Position = 0;
		   output->WriteString(edit_itm_hdr);

		   dataset->First();

		   while (!dataset->Eof)
			 {
			   output->WriteString("<td><input type=\"hidden\" name=\"id\" value=\"");
			   output->WriteString(dataset->FieldByName("ID")->AsString);
			   output->WriteString("\"></input></td>");

			   output->WriteString("<td><input type=\"text\" name=\"inn\" value=\"");
			   output->WriteString(dataset->FieldByName("INN")->AsString);
			   output->WriteString("\"></input></td>");

			   output->WriteString("<td><input type=\"text\" name=\"sn\" value=\"");
			   output->WriteString(dataset->FieldByName("SN")->AsString);
			   output->WriteString("\"></input></td>");

			   output->WriteString("<td><input type=\"text\" name=\"model\" value=\"");
			   output->WriteString(dataset->FieldByName("MODEL")->AsString);
			   output->WriteString("\"></input></td>");

			   output->WriteString("<td><select size=\"1\" name=\"location\">[***]</select></td>");

			   output->WriteString("</tr>\r\n");

			   dataset->Next();
			 }

           GenerateLocationList(output);

		   output->WriteString("<br>\r\n</table>\r\n");
           output->WriteString("<p><button style=\"width:150px;height:25px\" type=\"submit\">Застосувати</button></p>");
		   output->WriteString("<br>\r\n</form>\r\n");
		   output->WriteString("<br>\r\n</center>\r\n");
		   output->WriteString("<br>\r\n</body>\r\n</html>");
		 }
	  catch (Exception &e)
		 {
		   GenerateErrorPage("GenerateResultPage(): RT_EDIT: " + e.ToString(), output);
		 }
	}
  else if (type == RT_USER)
	{
	  try
		 {
		   output->Clear();
		   output->Position = 0;
		   output->WriteString(users_hdr);

		   dataset->First();

		   while (!dataset->Eof)
			 {
			   output->WriteString("<tr>");
			   output->WriteString("<td>" + dataset->FieldByName("ID")->AsString + "</td>");
               output->WriteString("<td>" + dataset->FieldByName("LOGIN")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("NAME")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("ROLE")->AsString + "</td>");
			   output->WriteString("<td><form method=\"post\" action=\"/set_pwd.html?id=");
			   output->WriteString(dataset->FieldByName("ID")->AsString);
			   output->WriteString("\">");
			   output->WriteString("<p><button style=\"width:180px;height:25px\" type=\"submit\">Встановити пароль</button></p>");
			   output->WriteString("</form></td>");
			   output->WriteString("<td><form method=\"post\" action=\"/remove_user.html?id=");
			   output->WriteString(dataset->FieldByName("ID")->AsString);
			   output->WriteString("\">");
			   output->WriteString("<p><button style=\"width:180px;height:25px\" type=\"submit\">Видалити Агента</button></p>");
			   output->WriteString("</form></td>");
			   output->WriteString("</tr>\r\n");

			   dataset->Next();
			 }

		   output->WriteString("<br>\r\n</table>\r\n");
		   output->WriteString("<br>\r\n</center>\r\n");
		   output->WriteString("<br>\r\n</body>\r\n</html>");
		 }
	  catch (Exception &e)
		 {
		   GenerateErrorPage("GenerateResultPage(): RT_USER: " + e.ToString(), output);
		 }
	}
  else if (type == RT_SESS)
	{
	  try
		 {
		   output->Clear();
		   output->Position = 0;
		   output->WriteString(sessions_hdr);

		   dataset->First();

		   while (!dataset->Eof)
			 {
			   output->WriteString("<tr>");
			   output->WriteString("<td>" + dataset->FieldByName("ID")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("USER_ID")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("HASH")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("ADDED")->AsString + "</td>");
			   output->WriteString("<td><form method=\"post\" action=\"/remove_session.html?id=");
			   output->WriteString(dataset->FieldByName("ID")->AsString);
			   output->WriteString("\">");
			   output->WriteString("<p><button style=\"width:180px;height:25px\" type=\"submit\">Видалити</button></p>");
			   output->WriteString("</form></td>");
			   output->WriteString("</tr>\r\n");

			   dataset->Next();
			 }

		   output->WriteString("<br>\r\n</table>\r\n");
		   output->WriteString("<br>\r\n</center>\r\n");
		   output->WriteString("<br>\r\n</body>\r\n</html>");
		 }
	  catch (Exception &e)
		 {
		   GenerateErrorPage("GenerateResultPage(): RT_SESS: " + e.ToString(), output);
		 }
	}
  else if (type == RT_LOCS)
	{
	  try
		 {
		   output->Clear();
		   output->Position = 0;
		   output->WriteString(locations_hdr);

		   dataset->First();

		   while (!dataset->Eof)
			 {
			   output->WriteString("<tr>");
			   output->WriteString("<td>" + dataset->FieldByName("ID")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("IND")->AsString + "</td>");
			   output->WriteString("<td>" + dataset->FieldByName("ADDRESS")->AsString + "</td>");
			   output->WriteString("<td><form method=\"post\" action=\"/remove_loc.html?id=");
			   output->WriteString(dataset->FieldByName("ID")->AsString);
			   output->WriteString("\">");
			   output->WriteString("<p><button style=\"width:180px;height:25px\" type=\"submit\">Видалити</button></p>");
			   output->WriteString("</form></td>");
			   output->WriteString("<td><form method=\"post\" action=\"/edit_loc.html?id=");
			   output->WriteString(dataset->FieldByName("ID")->AsString);
			   output->WriteString("\">");
			   output->WriteString("<p><button style=\"width:180px;height:25px\" type=\"submit\">Редагувати</button></p>");
			   output->WriteString("</form></td>");
			   output->WriteString("</tr>\r\n");

			   dataset->Next();
			 }

		   output->WriteString("<br>\r\n</table>\r\n");
		   output->WriteString("<br><br><h2>Додати нову локацію</h2>\r\n");
		   output->WriteString("<form method=\"post\" action=\"/add_loc.html\">");
		   output->WriteString("<br>\r\n<table>\r\n");
		   output->WriteString("<tr><th>Індекс</th><th>Адреса</th><th></th></tr>");
		   output->WriteString("<tr><td><input type=\"text\" name=\"index\"></input></td>");
		   output->WriteString("<td><input type=\"text\" name=\"addr\"></input></td>");
		   output->WriteString("<td><button style=\"width:200px;height:25px\" ");
		   output->WriteString("type=\"submit\">Створити</button></td></tr>");
           output->WriteString("<br>\r\n</table>\r\n");
		   output->WriteString("<br>\r\n</form>\r\n");
		   output->WriteString("<br>\r\n</center>\r\n");
		   output->WriteString("<br>\r\n</body>\r\n</html>");
		 }
	  catch (Exception &e)
		 {
		   GenerateErrorPage("GenerateResultPage(): RT_LOCS: " + e.ToString(), output);
		 }
	}
  else if (type == RT_LOC)
	{
	  try
		 {
		   output->Clear();
		   output->Position = 0;
		   output->WriteString(location_hdr);

		   dataset->First();
		   output->WriteString("<p><input type=\"hidden\" name=\"id\" value=\"");
		   output->WriteString(dataset->FieldByName("ID")->AsString);
		   output->WriteString("\"></input>");
		   output->WriteString("<input type=\"text\" name=\"index\" value=\"");
		   output->WriteString(dataset->FieldByName("IND")->AsString);
		   output->WriteString("\"></input>");
		   output->WriteString("<input type=\"text\" name=\"addr\" value=\"");
		   output->WriteString(dataset->FieldByName("ADDRESS")->AsString);
		   output->WriteString("\"></input>");
		   output->WriteString("<p><button style=\"width:200px;height:25px\" ");
		   output->WriteString("type=\"submit\">Застосувати</button></p>");
		   output->WriteString("<br>\r\n</form>\r\n");
		   output->WriteString("<br>\r\n</center>\r\n");
		   output->WriteString("<br>\r\n</body>\r\n</html>");
		 }
	  catch (Exception &e)
		 {
		   GenerateErrorPage("GenerateResultPage(): RT_LOC: " + e.ToString(), output);
		 }
	}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::GenerateErrorPage(String error,
												TStringStream *output)
{
  output->Clear();
  output->WriteString("<html>");
  output->WriteString("<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\"></head>");
  output->WriteString("<br><body>");
  output->WriteString("<br>\r\n<center>\r\n");
  output->WriteString(error);
  output->WriteString("<br><br><a href=\"/\"><b>На головну</b></a>");
  output->WriteString("<br>\r\n</center>\r\n");
  output->WriteString("<br></body></html>");
}
//---------------------------------------------------------------------------

void __fastcall TTechService::GenerateSuccessPage(String msg,
												  TStringStream *output)
{
  output->Clear();
  output->WriteString("<html>");
  output->WriteString("<head><meta http-equiv=\"Content-Type\" content=\"text/html\" charset=\"utf-8\"></head>");
  output->WriteString("<br><body>");
  output->WriteString("<br>\r\n<center>\r\n");
  output->WriteString(msg);
  output->WriteString("<br><br><a href=\"/\"><b>На головну</b></a>");
  output->WriteString("<br>\r\n</center>\r\n");
  output->WriteString("<br></body></html>");
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
				  GenerateErrorPage("Помилка читання переліку локацій", output);
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
				  GenerateErrorPage("Помилка читання переліку локацій", output);
				}
		   }
		__finally {DeleteTransactionObj(tmp_tr); DeleteQueryObj(dataset); delete ms;}
	 }
  catch (Exception &e)
	 {
	   GenerateErrorPage("Помилка читання переліку локацій", output);
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

void __fastcall TTechService::RemSessionTimerTimer(TObject *Sender)
{
  RemoveOldSessions();
}
//---------------------------------------------------------------------------

bool __fastcall TTechService::LoadCryptoDLL()
{
  bool res;

  try
     {
	   String load_path = ConfigPath + "\\AESCrypt.dll";

	   dllhandle = LoadLibraryW(load_path.c_str());

       if (dllhandle)
		 {
		   EncryptText = (ENCRYPTTEXT) GetProcAddress(dllhandle, "AESEncryptText");
		   DecryptText = (DECRYPTTEXT) GetProcAddress(dllhandle, "AESDecryptText");

		   if (!EncryptText)
			 {
			   SendLogToConsole("LoadCryptoDLL(): Помилка ініціалізації EnryptText()");
			   res = false;
			 }
		   else if (!DecryptText)
			 {
			   SendLogToConsole("LoadCryptoDLL(): Помилка ініціалізації DecryptText()");
			   res = false;
			 }
		   else
			 {
			   String ver = GetVersionInString(String(ConfigPath + "\\AESCrypt.dll").c_str());
			   SendLogToConsole("LoadCryptoDLL(): OK, версія: " + ver);
			   res = true;
			 }
		 }
	   else
		 {
		   SendLogToConsole("LoadCryptoDLL(): Помилковий дескриптор");
		   SendLogToConsole("LoadCryptoDLL(): Код помилки " + String((int)GetLastError()));
		   res = false;
		 }
	 }
  catch(Exception &e)
	 {
	   SendLogToConsole("LoadCryptoDLL(): " + e.ToString());
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::UnLoadCryptoDLL()
{
  try
	 {
	   FreeLibrary(dllhandle);
	 }
  catch(Exception &e)
	 {
	   SendLogToConsole("UnLoadCryptoDLL(): " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

String __fastcall TTechService::CryptUserPassword(const String &pass)
{
  String res;

  try
	 {
	   res = EncryptText(pass.c_str(), "U$erHa$hK3y");
	 }
  catch(Exception &e)
	 {
	   res = "";
	   SendLogToConsole("CryptUserAuthID(): " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ConnectionServerExecute(TIdContext *AContext)
{
  String msg, cfg;
  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

  AContext->Connection->IOHandler->ReadStream(ms);

  try
	 {
	   try
		  {
			ms->Position = 0;
			msg = ms->ReadString(ms->Size);
			AContext->Connection->IOHandler->Write(ms, ms->Size, true);
		  }
	   catch (Exception &e)
		  {
			SendLogToConsole("ConnectionServerExecute: " + e.ToString());
		  }
	 }
  __finally {delete ms;}
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ConnectionServerConnect(TIdContext *AContext)
{
  //клієнт під'єднався
  SendLogToConsole("Підключився клієнт: " + AContext->Connection->Socket->BoundIP);
}
//---------------------------------------------------------------------------

void __fastcall TTechService::ConnectionServerDisconnect(TIdContext *AContext)
{
  //клієнт від'єднався
  SendLogToConsole("Відключився клієнт: " + AContext->Connection->Socket->BoundIP);
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

void __fastcall TTechService::ParseXML(TXMLDocument *ixml)
{
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
		   ProcessRequest(ixml);
		 }
	   else
		 {
		   //прийшла якась фігня
		   throw new Exception("Невідомий тип XML-документу");
		 }
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("ParseXML: " + e.ToString());
	 }
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

void __fastcall TTechService::ProcessRequest(TXMLDocument *ixml)
{
  try
	 {
	   _di_IXMLNode Document = ixml->DocumentElement; //тип документу (запит/відповідь)
	   _di_IXMLNode Command; //команда (вказує для чого призначені дані)

	   _di_IXMLNode Params; //позначає секцію з даними
	   _di_IXMLNode Param;

	   Command = Document->ChildNodes->Nodes[0];
	   Params = Document->ChildNodes->Nodes[1];

	   String datatype, value;

	   for (int i = 0; i < Params->ChildNodes->Count; i++)
		  {
			for (int j = 0; j < Params->ChildNodes->Count; j++)
			   {
				 Param = Params->ChildNodes->Nodes[j];

				 datatype = Param->GetAttribute("type");
				 value = Param->NodeValue;
			   }
		  }
	 }
  catch (Exception &e)
	 {
	   SendLogToConsole("ProcessRequest: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

