/*!
Copyright 2020 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\..\work-functions\MyFunc.h"
#include "..\..\..\work-functions\Cypher.h"
#include "..\..\..\work-functions\TCPRequester.h"
#include "TICServiceThread.h"
#include "Login.h"
#include "ChangePassword.h"
#include "Client.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClientForm *ClientForm;

String Server, User; //поточний сервер та логін користувача
int UserID; //ID поточного користувача
bool IsAdmin; //флаг, що визначає, чи є поточний юзер адміном
String AppPath;
String LogPath;
const char *DataCryptKey = "D@t@Ha$hK3y";
int MainFormWidth, MainFormHeight;
bool MainFormFullScreen;
int AnimFrameInd;    //індекс поточного кадру анімації завантаження
TPanel *ActivePanel; //поточна активна панель
int CurrentRowInd, CurrentColInd; //індекси поточних рядка поля у таблиці відображення
int SelectedLocation; //ід обраної локації для Пристрою
TStringGrid *CurrentResultSet; //поточна активна таблиця для відображення результату
//---------------------------------------------------------------------------
__fastcall TClientForm::TClientForm(TComponent* Owner)
	: TForm(Owner)
{
  AppPath = Application->ExeName;
  int pos = AppPath.LastDelimiter("\\");
  AppPath.Delete(pos, AppPath.Length() - (pos - 1));

  LogPath = GetEnvironmentVariable("USERPROFILE") + "\\Documents";

  ReadSettings();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::FormShow(TObject *Sender)
{
  ClientHeight = MainFormHeight;
  ClientWidth = MainFormWidth;

  if (MainFormFullScreen)
    WindowState = wsMaximized;

  ClientVersion->Caption = "Версія клієнта: " +
  						   GetVersionInString(Application->ExeName.c_str());

  ServerInfo->Caption = "Сервер: " +
						Server +
						", версія: "; //потрібно отримати версію сервера

  UserInfo->Caption = "Користувач: " + User;

  SetUIImages();

  LoginForm->Show();
  LoginForm->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  WriteSettings();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AddActionLog(String status)
{
  ShowLog(status, ActionLog);
  SendMessage(ActionLog->Handle, WM_VSCROLL, SB_BOTTOM, 0);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ReadSettings()
{
  try
	 {
	   std::unique_ptr<TRegistry> reg(new TRegistry());

	   reg->RootKey = HKEY_CURRENT_USER;

	   if (reg->OpenKey("Software\\TIClient\\Form", false))
		 {
		   if (reg->ValueExists("FullScreen"))
			 MainFormFullScreen = reg->ReadBool("FullScreen");

			 if (reg->ValueExists("Height"))
			   MainFormHeight = reg->ReadInteger("Height");
			 else
			   {
				 MainFormHeight = 600;
				 reg->WriteInteger("Height", 600);
			   }

			 if (reg->ValueExists("Width"))
			   MainFormWidth = reg->ReadInteger("Width");
			 else
			   {
				 MainFormWidth = 800;
				 reg->WriteInteger("Width", 800);
			   }

			 reg->CloseKey();
		 }

	   if (reg->OpenKey("Software\\TIClient\\Params", false))
		 {
		   if (reg->ValueExists("Server"))
			 Server = reg->ReadString("Server");

		   if (reg->ValueExists("LastUser"))
			 User = reg->ReadString("LastUser");

			 reg->CloseKey();
		 }
	 }
  catch (Exception &e)
	 {
	   SaveLog(LogPath + "\\TIClient_exceptions.log", "ReadSettings: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::WriteSettings()
{
  try
	 {
	   std::unique_ptr<TRegistry> reg(new TRegistry());

	   reg->RootKey = HKEY_CURRENT_USER;

	   if (!reg->KeyExists("Software\\TIClient\\Form"))
		 reg->CreateKey("Software\\TIClient\\Form");

	   if (!reg->KeyExists("Software\\TIClient\\Params"))
		 reg->CreateKey("Software\\TIClient\\Params");

	   if (reg->OpenKey("Software\\TIClient\\Form", false))
		 {
		   reg->WriteInteger("Height", ClientHeight);
		   reg->WriteInteger("Width", ClientWidth);

		   if (ClientForm->WindowState == wsMaximized)
			 reg->WriteBool("FullScreen", true);
		   else
			 reg->WriteBool("FullScreen", false);

		   reg->CloseKey();
		 }

	   if (reg->OpenKey("Software\\TIClient\\Params", false))
		 {
		   reg->WriteString("Server", Server);
		   reg->WriteString("LastUser", User);

		   reg->CloseKey();
		 }
	 }
  catch (Exception &e)
	 {
	   SaveLog(LogPath + "\\TIClient_exceptions.log", "WriteSettings: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::SendToServer(const String &host, TStringStream *buffer)
{
  std::unique_ptr<TTCPRequester> sender(new TTCPRequester(host, DEFAULT_SERVER_PORT));
  bool res = true;

  try
	 {
	   try
		  {
			AddActionLog("Шифрування буферу даних");
			buffer->LoadFromStream(TSAESCypher::Crypt(buffer, DataCryptKey));
		  }
	   catch (Exception &e)
		  {
			throw Exception("Помилка шифрування: " + e.ToString());
		  }

	   AddActionLog("Відправка даних на сервер");

	   if (!sender->SendData(buffer))
		 throw Exception("Помилка відправки даних");

	   buffer->Clear();
	 }
  catch (Exception &e)
	 {
	   AddActionLog(String(host) + ": " + e.ToString());
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AskToServer(const String &host, TStringStream *buffer)
{
  std::unique_ptr<TTCPRequester> sender(new TTCPRequester(host, DEFAULT_SERVER_PORT));
  bool res = true;

  try
	 {
	   try
		  {
			AddActionLog("Шифрування буферу даних");
			buffer->LoadFromStream(TSAESCypher::Crypt(buffer, DataCryptKey));
		  }
	   catch (Exception &e)
		  {
			throw Exception("Помилка шифрування: " + e.ToString());
		  }

	   AddActionLog("Обмін даними з сервером");

	   if (!sender->AskData(buffer))
		  throw Exception("Помилка обміну даними");

	   try
		  {
			AddActionLog("Розшифрування буферу даних");
			buffer->Position = 0;
			buffer->LoadFromStream(TSAESCypher::Encrypt(buffer, DataCryptKey));
		  }
	   catch (Exception &e)
		 {
		   throw Exception("Помилка шифрування: " + e.ToString());
		 }
	 }
  catch (Exception &e)
	 {
	   AddActionLog(String(host) + ": " + e.ToString());
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

TXMLDocument *__fastcall TClientForm::CreatXMLStream(TStringStream *ms)
{
  TXMLDocument *ixml;

  try
	 {
	   ixml = new TXMLDocument(this);

	   ixml->DOMVendor = GetDOMVendor(sOmniXmlVendor);
	   ixml->Active = true;
	   ixml->Encoding = "UTF-8";
	   ixml->Options = ixml->Options << doNodeAutoIndent;
	   ixml->LoadFromStream(ms, xetUTF_8);
	 }
  catch (Exception &e)
	 {
	   AddActionLog("CreatXMLStream(): " + e.ToString());
	   ixml = NULL;
	 }

  return ixml;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowLoadingImage()
{
  AnimFrameInd = 0;
  PnLoading->Show();
  PnLoading->BringToFront();
  ActivePanel->Hide();
  LoadAnimTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::HideLoadingImage()
{
  PnLoading->Hide();
  LoadAnimTimer->Enabled = false;
  ActivePanel->Show();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::LoadAnimTimerTimer(TObject *Sender)
{
  if (AnimFrameInd >= LoadingAnimImageList->Count)
	AnimFrameInd = 0;

  PnLoading->Picture->Bitmap = LoadingAnimImageList->GetBitmap(AnimFrameInd, 64, 64);

  AnimFrameInd++;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::HideAllPanels()
{
  PnHome->Hide();
  PnCheckItem->Hide();
  PnCheckItems->Hide();
  PnAddItem->Hide();
  PnShowItems->Hide();
  PnShowEvents->Hide();
  PnAdmUsers->Hide();
  PnAdmLocations->Hide();
  PnAdmLogs->Hide();
  PnAdmManage->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnHomeClick(TObject *Sender)
{
  HideAllPanels();
  PnHome->Show();
  ActivePanel = PnHome;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnCheckItemClick(TObject *Sender)
{
  HideAllPanels();
  PnCheckItem->Show();
  ActivePanel = PnCheckItem;
  CheckItemScannedCode->SetFocus();
  CurrentResultSet = CheckItemResult;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnCheckItemsClick(TObject *Sender)
{
  HideAllPanels();
  PnCheckItems->Show();
  ActivePanel = PnCheckItems;
  CurrentResultSet = CheckItemsResult;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAddItemClick(TObject *Sender)
{
  HideAllPanels();
  PnAddItem->Show();
  ActivePanel = PnAddItem;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnShowItemsClick(TObject *Sender)
{
  HideAllPanels();
  PnShowItems->Show();
  ActivePanel = PnShowItems;
  CurrentResultSet = ShowItemsResult;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnShowEventsClick(TObject *Sender)
{
  HideAllPanels();
  PnShowEvents->Show();
  ActivePanel = PnShowEvents;
  CurrentResultSet = ShowEventsResult;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmUsersClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmUsers->Show();
  ActivePanel = PnAdmUsers;
  CurrentResultSet = AdmUsersResult;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmLocationsClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmLocations->Show();
  ActivePanel = PnAdmLocations;
  CurrentResultSet = AdmLocationsResult;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmLogsClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmLogs->Show();
  ActivePanel = PnAdmLogs;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmManageClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmManage->Show();
  ActivePanel = PnAdmManage;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ReconnectClick(TObject *Sender)
{
  LoginForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::SetUIImages()
{
  try
	 {
	   MnHome->Glyph = PanelImages->GetBitmap(5, 30, 30);
	   MnHome->Glyph->Transparent = true;

	   MnCheckItem->Glyph = PanelImages->GetBitmap(3, 30, 30);
	   MnCheckItem->Glyph->Transparent = true;

	   MnCheckItems->Glyph = PanelImages->GetBitmap(2, 30, 30);
	   MnCheckItems->Glyph->Transparent = true;

	   MnAddItem->Glyph = PanelImages->GetBitmap(0, 30, 30);
	   MnAddItem->Glyph->Transparent = true;

	   MnShowItems->Glyph = PanelImages->GetBitmap(6, 30, 30);
	   MnShowItems->Glyph->Transparent = true;

	   MnShowEvents->Glyph = PanelImages->GetBitmap(8, 30, 30);
	   MnShowEvents->Glyph->Transparent = true;

	   MnAdmUsers->Glyph = PanelImages->GetBitmap(1, 30, 30);
	   MnAdmUsers->Glyph->Transparent = true;

	   MnAdmLocations->Glyph = PanelImages->GetBitmap(9, 30, 30);
	   MnAdmLocations->Glyph->Transparent = true;

	   MnAdmLogs->Glyph = PanelImages->GetBitmap(7, 30, 30);
	   MnAdmLogs->Glyph->Transparent = true;

	   MnAdmManage->Glyph = PanelImages->GetBitmap(4, 30, 30);
	   MnAdmManage->Glyph->Transparent = true;

	   CheckItemEdit->Glyph = PanelImages->GetBitmap(11, 18, 18);
	   CheckItemEdit->Glyph->Transparent = true;
	   CheckItemEdit->Glyph->TransparentColor = clBlack;

	   CheckItemRemove->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   CheckItemRemove->Glyph->Transparent = true;

	   CheckItemRefresh->Glyph = PanelImages->GetBitmap(13, 18, 18);
	   CheckItemRefresh->Glyph->Transparent = true;
	   CheckItemRefresh->Glyph->TransparentColor = clBlack;

	   PPEdit->Bitmap = PanelImages->GetBitmap(11, 16, 16);
	   PPEdit->Bitmap->Transparent = true;
	   PPEdit->Bitmap->TransparentColor = clBlack;

	   PPRemove->Bitmap = PanelImages->GetBitmap(10, 16, 16);
	   PPRemove->Bitmap->Transparent = true;

	   PPRefresh->Bitmap = PanelImages->GetBitmap(13, 18, 18);
	   PPRefresh->Bitmap->Transparent = true;
	   PPRefresh->Bitmap->TransparentColor = clBlack;

	   Reconnect->Glyph = PanelImages->GetBitmap(12, 16, 16);
	   Reconnect->Glyph->Transparent = true;

	   PPCheckEdit->Bitmap = PanelImages->GetBitmap(11, 16, 16);
	   PPCheckEdit->Bitmap->Transparent = true;
	   PPCheckEdit->Bitmap->TransparentColor = clBlack;

	   PPCheckSetUnknown->Bitmap = PanelImages->GetBitmap(10, 16, 16);
	   PPCheckSetUnknown->Bitmap->Transparent = true;

	   PPCheckRefresh->Bitmap = PanelImages->GetBitmap(13, 18, 18);
	   PPCheckRefresh->Bitmap->Transparent = true;
	   PPCheckRefresh->Bitmap->TransparentColor = clBlack;

	   ShowItemsEdit->Glyph = PanelImages->GetBitmap(11, 18, 18);
	   ShowItemsEdit->Glyph->Transparent = true;
	   ShowItemsEdit->Glyph->TransparentColor = clBlack;

	   ShowItemsRemove->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   ShowItemsRemove->Glyph->Transparent = true;

	   ShowItemsRefresh->Glyph = PanelImages->GetBitmap(13, 18, 18);
	   ShowItemsRefresh->Glyph->Transparent = true;
	   ShowItemsRefresh->Glyph->TransparentColor = clBlack;

	   CheckItemsEdit->Glyph = PanelImages->GetBitmap(11, 18, 18);
	   CheckItemsEdit->Glyph->Transparent = true;
	   CheckItemsEdit->Glyph->TransparentColor = clBlack;

	   CheckItemsSendToUnknown->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   CheckItemsSendToUnknown->Glyph->Transparent = true;

	   CheckItemsRefresh->Glyph = PanelImages->GetBitmap(13, 18, 18);
	   CheckItemsRefresh->Glyph->Transparent = true;
	   CheckItemsRefresh->Glyph->TransparentColor = clBlack;

	   AdmLocationsAdd->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   AdmLocationsAdd->Glyph->Transparent = true;

	   AdmLocationsEdit->Glyph = PanelImages->GetBitmap(11, 18, 18);
	   AdmLocationsEdit->Glyph->Transparent = true;
	   AdmLocationsEdit->Glyph->TransparentColor = clBlack;

	   AdmLocationsRemove->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   AdmLocationsRemove->Glyph->Transparent = true;

	   AdmLocationsRefresh->Glyph = PanelImages->GetBitmap(13, 18, 18);
	   AdmLocationsRefresh->Glyph->Transparent = true;
	   AdmLocationsRefresh->Glyph->TransparentColor = clBlack;

	   PPAddLocation->Bitmap = PanelImages->GetBitmap(10, 16, 16);
	   PPAddLocation->Bitmap->Transparent = true;

	   PPEditLocation->Bitmap = PanelImages->GetBitmap(11, 16, 16);
	   PPEditLocation->Bitmap->Transparent = true;
	   PPEditLocation->Bitmap->TransparentColor = clBlack;

	   PPRemoveLocation->Bitmap = PanelImages->GetBitmap(10, 16, 16);
	   PPRemoveLocation->Bitmap->Transparent = true;

	   PPLocationsRefresh->Bitmap = PanelImages->GetBitmap(13, 18, 18);
	   PPLocationsRefresh->Bitmap->Transparent = true;
	   PPLocationsRefresh->Bitmap->TransparentColor = clBlack;

	   AdmUsersAdd->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   AdmUsersAdd->Glyph->Transparent = true;

	   AdmUsersSetPwd->Glyph = PanelImages->GetBitmap(11, 18, 18);
	   AdmUsersSetPwd->Glyph->Transparent = true;
	   AdmUsersSetPwd->Glyph->TransparentColor = clBlack;

	   AdmUsersRemove->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   AdmUsersRemove->Glyph->Transparent = true;

	   AdmUsersRefresh->Glyph = PanelImages->GetBitmap(13, 18, 18);
	   AdmUsersRefresh->Glyph->Transparent = true;
	   AdmUsersRefresh->Glyph->TransparentColor = clBlack;

	   PPSetPwd->Bitmap = PanelImages->GetBitmap(11, 16, 16);
	   PPSetPwd->Bitmap->Transparent = true;
	   PPSetPwd->Bitmap->TransparentColor = clBlack;

	   PPRemoveUser->Bitmap = PanelImages->GetBitmap(10, 16, 16);
	   PPRemoveUser->Bitmap->Transparent = true;

	   PPUsersRefresh->Bitmap = PanelImages->GetBitmap(13, 18, 18);
	   PPUsersRefresh->Bitmap->Transparent = true;
	   PPUsersRefresh->Bitmap->TransparentColor = clBlack;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка налаштування UI");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::LockUI()
{
  try
	 {
	   HideAllPanels();

	   ClientVersion->Hide();
	   ServerInfo->Hide();
	   UserInfo->Hide();

	   MnHome->Visible = false;
	   MnCheckItem->Visible = false;
	   MnCheckItems->Visible = false;
	   MnAddItem->Visible = false;
	   MnShowItems->Visible = false;
	   MnShowEvents->Visible = false;
	   MnAdmUsers->Visible = false;
	   MnAdmLocations->Visible = false;
	   MnAdmLogs->Visible = false;
	   MnAdmManage->Visible = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка блокування UI");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::UnlockUI()
{
  try
	 {
	   ClientVersion->Show();
	   ServerInfo->Show();
	   UserInfo->Show();

	   MnHome->Visible = true;
	   MnCheckItem->Visible = true;
	   MnCheckItems->Visible = true;
	   MnAddItem->Visible = true;
	   MnShowItems->Visible = true;
	   MnShowEvents->Visible = true;

	   if (IsAdmin)
		 {
		   MnAdmUsers->Visible = true;
		   MnAdmLocations->Visible = true;
		   MnAdmLogs->Visible = true;
		   MnAdmManage->Visible = true;
		 }

       MnHome->Click();
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка розблокування UI");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::GetServerVersion()
{
  try
	 {
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("GETVERSION"));

	   if (AskToServer(Server, data.get()))
		 {
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   _di_IXMLNode Document = ixml->DocumentElement;
		   _di_IXMLNode Command = Document->ChildNodes->Nodes[0];

		   ServerInfo->Caption += Command->NodeValue;
         }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка отримання версії серверу");
	 }
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::SetUserPassword(const String &login, const String &new_password)
{
  bool res;

  try
	 {
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("SETPWD",
	   																 login + ";" + MD5(new_password)));

	   if (AskToServer(Server, data.get()))
		 {
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   _di_IXMLNode Document = ixml->DocumentElement;
		   _di_IXMLNode Command = Document->ChildNodes->Nodes[0];

		   if (Command->NodeValue == "SUCCESS")
			 res = true;
		   else
			 res = false;
         }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка отримання версії серверу");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

TMemoryStream* __fastcall TClientForm::CryptData(String data, const char *pass)
{
  TMemoryStream *res = new TMemoryStream();

  TAESCypher *cypher = new TAESCypher(data, pass);

  try
	 {
	   res->LoadFromStream(cypher->Data);

	   if (cypher->LastError != "")
		 AddActionLog("CryptData(): " + cypher->LastError);
	 }
  __finally{delete cypher;}

  return res;
}
//---------------------------------------------------------------------------

String __fastcall TClientForm::EncryptData(TMemoryStream *crypted_data, const char *pass)
{
  String res;

  TAESCypher *cypher = new TAESCypher(crypted_data, pass, coEncrypt);

  try
	 {
	   res = cypher->DataToString();

	   if (cypher->LastError != "")
		 AddActionLog("EncryptData(): " + cypher->LastError);
	 }
  __finally{delete cypher;}

  return res;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TClientForm::CreateRequest(const String &command,
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
	   AddActionLog("CreateRequest(" + command + "): " + e.ToString());

	   if (ms) {delete ms;}

       ms = NULL;
	 }

  return ms;
}
//---------------------------------------------------------------------------

TStringStream* __fastcall TClientForm::CreateRequest(const String &command)
{
  TStringStream *ms;

  try
	 {
	   ms = new TStringStream("", TEncoding::UTF8, true);

	   ms->WriteString("<Request>");
	   ms->WriteString("<Command>" + command + "</Command>");
	   ms->WriteString("<Params>");
	   ms->WriteString("</Params>");
       ms->WriteString("</Request>");
	 }
  catch (Exception &e)
	 {
	   AddActionLog("CreateRequest(" + command + "): " + e.ToString());

	   if (ms) {delete ms;}

       ms = NULL;
	 }

  return ms;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ParseXML(TXMLDocument *ixml)
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
		   throw Exception("Невідомий тип XML-документу");
		 }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("ParseXML: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ProcessAnswer(TXMLDocument *ixml)
{
  try
	 {
	   _di_IXMLNode Document = ixml->DocumentElement; //тип документу (запит/відповідь)
	   _di_IXMLNode Command; //команда (вказує для чого призначені дані)

	   _di_IXMLNode Titles; //перелік заголовків для полей таблиці результату
	   _di_IXMLNode Title;

	   _di_IXMLNode Data; //позначає секцію з даними
	   _di_IXMLNode Row;
	   _di_IXMLNode Field;

	   Command = Document->ChildNodes->Nodes[0];
	   Titles = Document->ChildNodes->Nodes[1];
	   Data = Document->ChildNodes->Nodes[2];

	   String datatype, value;
	   int colsize;

	   //за текстом команди визначаємо панель та таблицю у яку будемо зберігати дані
	   TStringGrid *res;

	   try
		  {
			res->ColCount = Titles->ChildNodes->Count;
			res->RowCount = Data->ChildNodes->Count + 1;
			res->FixedRows = 1;

			for (int i = 0; i < Titles->ChildNodes->Count; i++)
			   {
				 Title = Titles->ChildNodes->Nodes[i];
				 colsize = StrToInt(Title->GetAttribute("size"));
				 value = Title->NodeValue;

				 res->ColWidths[i] = colsize; //встановлюємо розмір полів
				 res->Cells[i][0] = value; //заповнюємо перший рядок таблиці назвами полів
			   }
		  }
	   catch (Exception &e)
		  {
            throw Exception("Помилка форматування таблиці відображення даних");
		  }

	   try
		  {
			for (int i = 0; i < Data->ChildNodes->Count; i++)
			   {
				 Row = Data->ChildNodes->Nodes[i];

				 for (int j = 0; j < Row->ChildNodes->Count; j++)
					{
					  Field = Row->ChildNodes->Nodes[j];

					  datatype = Field->GetAttribute("type");
					  value = Field->NodeValue;
                      //заповнюємо таблицю, починаючи з 1-го рядка, 0-й це заголовки
					  res->Cells[j][i + 1] = value;
					}
			   }
		  }
	   catch (Exception &e)
		  {
            throw Exception("Помилка виводу даних у таблицю");
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("ProcessAnswer: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ProcessRequest(TXMLDocument *ixml)
{
  try
	 {
	   _di_IXMLNode Document = ixml->DocumentElement; //тип документу (запит/відповідь)
	   _di_IXMLNode Command; //команда (вказує для чого призначені дані)

	   _di_IXMLNode Params; //позначає секцію з переліком параметрів
	   _di_IXMLNode Param;

	   Command = Document->ChildNodes->Nodes[0];
	   Params = Document->ChildNodes->Nodes[1];

	   String command, params;

	   command = Command->NodeValue;

	   for (int i = 0; i < Params->ChildNodes->Count; i++)
		  {
			Param = Params->ChildNodes->Nodes[i];
			params = params + Param->NodeValue + ";";
		  }

	   params.Delete(params.Length() - 1, 1);
	 }
  catch (Exception &e)
	 {
	   AddActionLog("ProcessRequest: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ListenerExecute(TIdContext *AContext)
{
  TXMLDocument *ixml;
  TStringStream *ms = new TStringStream("", TEncoding::UTF8, true);

  AContext->Connection->IOHandler->ReadStream(ms);

  try
	 {
	   try
		  {
			ms->LoadFromStream(TSAESCypher::Encrypt(ms, DataCryptKey));
			ms->Position = 0;
		  }
	   catch (Exception &e)
		  {
			AddActionLog("Listener: Розшифровка пакету: " + e.ToString());
		  }

	   try
		  {
			ixml = CreatXMLStream(ms);

            try
			   {
				 ParseXML(ixml);
			   }
			catch (Exception &e)
			   {
				 AddActionLog("Listener: Парсинг: " + e.ToString());
			   }
		  }
	   __finally {delete ixml;}
	 }
  __finally {delete ms;}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ListenerConnect(TIdContext *AContext)
{
  //клієнт під'єднався
  AddActionLog("Надійшли дані з серверу");
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ListenerDisconnect(TIdContext *AContext)
{
  //клієнт від'єднався
  AddActionLog("Передачу даних з серверу завершено");
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemScannedCodeKeyPress(TObject *Sender, System::WideChar &Key)
{
  try
		  {
			CheckItemResult->ColCount = 5;
			CheckItemResult->RowCount = 10 + 1;
			CheckItemResult->FixedRows = 1;

			for (int i = 0; i < 5; i++)
			   {
				 CheckItemResult->ColWidths[i] = 50;
				 CheckItemResult->Cells[i][0] = IntToStr(i);
			   }
		  }
	   catch (Exception &e)
		  {
            throw Exception("Помилка форматування таблиці відображення даних");
		  }

       try
		  {
			for (int i = 1; i < 11; i++)
			   {
				 for (int j = 0; j < 5; j++)
					{
					  CheckItemResult->Cells[j][i] = IntToStr(i);
					}
			   }
		  }
	   catch (Exception &e)
		  {
            throw Exception("Помилка виводу даних у таблицю");
		  }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPEditClick(TObject *Sender)
{
  CheckItemEdit->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPRemoveClick(TObject *Sender)
{
  CheckItemRemove->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemResultMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
  CurrentResultSet->MouseToCell(X, Y, CurrentColInd, CurrentRowInd);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemEditClick(TObject *Sender)
{
  if (CurrentRowInd > 0) //якщо поточний рядок не заголовки
	{
	  //відкриття форми редагування Пристрою
	}

  CurrentRowInd = 0;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemRemoveClick(TObject *Sender)
{
  if (CurrentRowInd > 0) //якщо поточний рядок не заголовки
	{
	  //видалення Пристрою з БД
	}

  CurrentRowInd = 0;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemRefreshClick(TObject *Sender)
{
  //повторний запит до БД
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AddItemCreateClick(TObject *Sender)
{
  //створюємо запит на додання Пристрою в БД
  //перед створенням треба перевіряти інв. № чи існує такий в БД
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AddItemClearFieldsClick(TObject *Sender)
{
  AddItemNewInn->Clear();
  AddItemNewSn->Clear();
  AddItemNewModel->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AddItemSelectLocationClick(TObject *Sender)
{
  //вивід форми вибору локації
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPSetPwdClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPRemoveUserClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmUsersAddClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmUsersSetPwdClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmUsersRemoveClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLocationsAddClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLocationsEditClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLocationsRemoveClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPLocationsRefreshClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPAddLocationClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPEditLocationClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPRemoveLocationClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLogsShowClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPCheckSetUnknownClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPRefreshClick(TObject *Sender)
{
  //
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ChangeMailClick(TObject *Sender)
{
  String NewMail = InputBox("Зміна адреси ел. пошти", "Нова адреса:", "");
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ChangePasswordClick(TObject *Sender)
{
  PasswordChangeForm->Show();
}
//---------------------------------------------------------------------------

