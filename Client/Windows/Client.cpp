/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
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
#include "SetPassword.h"
#include "ChangeMail.h"
#include "EditItem.h"
#include "SelectLocation.h"
#include "EditLocation.h"
#include "AddUser.h"
#include "Client.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClientForm *ClientForm;

String Server, User; //поточний сервер та логін користувача
int UserID; //ID поточного користувача
int ItemID; //ID поточного Пристрою
bool IsAdmin; //флаг, що визначає, чи є поточний юзер адміном
bool IsLocked; //флаг, що визначає, чи є обліковий запис користувача активним
String AppPath;
String LogPath;
const char *DataCryptKey = "D@t@Ha$hK3y";
int MainFormWidth, MainFormHeight;
bool MainFormFullScreen;
int AnimFrameInd;    //індекс поточного кадру анімації завантаження
TPanel *ActivePanel; //поточна активна панель
int CurrentRowInd, CurrentColInd; //індекси поточних рядка поля у таблиці відображення
TLabel *Location; //лейбл для відображення обраної локації
TBitBtn *RefreshButton; //активна кнопка для оновлення даних
TBitBtn *EditButton;  //редагування пристрою
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

TXMLDocument *__fastcall TClientForm::CreateXMLStream(TStringStream *ms)
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
  CheckItemScannedCode->Text = "";
  CheckItemInn->Text = "";
  CheckItemSn->Text = "";
  CheckItemModel->Text = "";
  CheckItemCurrentLocation->Caption = "";
  CheckItemLastAgent->Caption = "";
  RefreshButton = CheckItemRefresh;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnCheckItemsClick(TObject *Sender)
{
  HideAllPanels();
  PnCheckItems->Show();
  ActivePanel = PnCheckItems;
  CheckItemsCurrentLocation->Caption = "";
  RefreshButton = nullptr;
  EditButton = CheckItemsEdit;
  ClearResultSet(CheckItemsResult);
  PrepareCheckTable();
  CheckError->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAddItemClick(TObject *Sender)
{
  HideAllPanels();
  PnAddItem->Show();
  ActivePanel = PnAddItem;
  AddItemCurrentLocation->Caption = "";
  IDError->Hide();
  InnError->Hide();
  ModelError->Hide();
  AddItemNewID->Text = "";
  AddItemNewInn->Text = "";
  AddItemNewSn->Text = "";
  AddItemNewModel->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnShowItemsClick(TObject *Sender)
{
  HideAllPanels();
  PnShowItems->Show();
  ActivePanel = PnShowItems;
  ShowItemsCurrentLocation->Caption = "";
  ClearResultSet(ShowItemsResult);
  RefreshButton = ShowItemsRefresh;
  EditButton = ShowItemsEdit;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnShowEventsClick(TObject *Sender)
{
  HideAllPanels();
  PnShowEvents->Show();
  ActivePanel = PnShowEvents;
  ShowEventsDateFrom->Date = Date().CurrentDate();
  ShowEventsDateTo->Date = Date().CurrentDate();
  ShowEventsDateFrom->Enabled = false;
  ShowEventsDateTo->Enabled = false;
  ShowEventsInn->Text = "";
  ShowEventsSearchType->ItemIndex = 0;
  ClearResultSet(ShowEventsResult);
  ShowEventsApply->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmUsersClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmUsers->Show();
  ActivePanel = PnAdmUsers;
  AskUserList();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmLocationsClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmLocations->Show();
  ActivePanel = PnAdmLocations;
  AskLocationList(AdmLocationsResult);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmLogsClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmLogs->Show();
  ActivePanel = PnAdmLogs;
  AdmLogsDate->Date = Date().CurrentDate();
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

	   CheckItemShowHistory->Glyph = PanelImages->GetBitmap(14, 18, 18);
	   CheckItemShowHistory->Glyph->Transparent = true;
	   CheckItemShowHistory->Glyph->TransparentColor = clBlack;

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

	   PPCheckSetUnknown->Bitmap = PanelImages->GetBitmap(15, 16, 16);
	   PPCheckSetUnknown->Bitmap->Transparent = true;

	   PPCheckDelFromTable->Bitmap = PanelImages->GetBitmap(10, 16, 16);
	   PPCheckDelFromTable->Bitmap->Transparent = true;

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

	   CheckItemsSendToUnknown->Glyph = PanelImages->GetBitmap(15, 18, 18);
	   CheckItemsSendToUnknown->Glyph->Transparent = true;

	   CheckItemsDelete->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   CheckItemsDelete->Glyph->Transparent = true;

	   AdmLocationsAdd->Glyph = PanelImages->GetBitmap(14, 18, 18);
	   AdmLocationsAdd->Glyph->Transparent = true;

	   AdmLocationsEdit->Glyph = PanelImages->GetBitmap(11, 18, 18);
	   AdmLocationsEdit->Glyph->Transparent = true;
	   AdmLocationsEdit->Glyph->TransparentColor = clBlack;

	   AdmLocationsRemove->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   AdmLocationsRemove->Glyph->Transparent = true;

	   AdmLocationsRefresh->Glyph = PanelImages->GetBitmap(13, 18, 18);
	   AdmLocationsRefresh->Glyph->Transparent = true;
	   AdmLocationsRefresh->Glyph->TransparentColor = clBlack;

	   PPAddLocation->Bitmap = PanelImages->GetBitmap(14, 16, 16);
	   PPAddLocation->Bitmap->Transparent = true;

	   PPEditLocation->Bitmap = PanelImages->GetBitmap(11, 16, 16);
	   PPEditLocation->Bitmap->Transparent = true;
	   PPEditLocation->Bitmap->TransparentColor = clBlack;

	   PPRemoveLocation->Bitmap = PanelImages->GetBitmap(10, 16, 16);
	   PPRemoveLocation->Bitmap->Transparent = true;

	   PPLocationsRefresh->Bitmap = PanelImages->GetBitmap(13, 18, 18);
	   PPLocationsRefresh->Bitmap->Transparent = true;
	   PPLocationsRefresh->Bitmap->TransparentColor = clBlack;

	   AdmUsersAdd->Glyph = PanelImages->GetBitmap(17, 18, 18);
	   AdmUsersAdd->Glyph->Transparent = true;

	   AdmUsersSetPwd->Glyph = PanelImages->GetBitmap(16, 18, 18);
	   AdmUsersSetPwd->Glyph->Transparent = true;

	   AdmUsersLock->Glyph = PanelImages->GetBitmap(15, 18, 18);
	   AdmUsersLock->Glyph->Transparent = true;

	   AdmUsersUnlock->Glyph = PanelImages->GetBitmap(18, 18, 18);
	   AdmUsersUnlock->Glyph->Transparent = true;

	   AdmUsersRefresh->Glyph = PanelImages->GetBitmap(13, 18, 18);
	   AdmUsersRefresh->Glyph->Transparent = true;
	   AdmUsersRefresh->Glyph->TransparentColor = clBlack;

	   PPSetPwd->Bitmap = PanelImages->GetBitmap(16, 16, 16);
	   PPSetPwd->Bitmap->Transparent = true;

	   PPLockUser->Bitmap = PanelImages->GetBitmap(15, 16, 16);
	   PPLockUser->Bitmap->Transparent = true;

	   PPUnlockUser->Bitmap = PanelImages->GetBitmap(18, 16, 16);
	   PPUnlockUser->Bitmap->Transparent = true;

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

	   CheckItemRemove->Enabled = false;
	   ShowItemsRemove->Enabled = false;
       PPRemove->Enabled = false;
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
		   PPRemove->Enabled = true;
		   CheckItemRemove->Enabled = true;
		   ShowItemsRemove->Enabled = true;
		 }

       MnHome->Click();
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка розблокування UI");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::UnlockUILimited()
{
  try
	 {
	   ClientVersion->Show();
	   ServerInfo->Show();
	   UserInfo->Show();

	   MnHome->Visible = true;
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
	   std::unique_ptr<TXMLDocument> ixml;

	   ServerInfo->Caption = "Сервер: " +
						Server +
						", версія: " +
						SendRequest("GETVERSION", "", ixml);
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка отримання версії серверу");
	 }
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::SetUserPassword(int user_id, const String &new_password)
{
  bool res;

  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("SETPWD", IntToStr(user_id) + ";" + MD5(new_password), ixml) == "SUCCESS")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка встановленя паролю");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::ValidUserPassword(int user_id, const String &password)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("CHECKPWD", IntToStr(user_id) + ";" + MD5(password), ixml) == "VALID")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка перевірки паролю");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::SetUserMail(int user_id, const String &new_mail)
{
  bool res;

  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("SETPWD", IntToStr(user_id) + ";" + MD5(new_mail), ixml) == "SUCCESS")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка встановленя адреси ел. пошти");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

String __fastcall TClientForm::AskItemInfo(const String &item_id)
{
  String res;

  try
	 {
	   std::unique_ptr<TStringStream> data(CreateRequest("GETITEM", item_id));

	   if (AskToServer(Server, data.get()))
		 {
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(CreateXMLStream(data.get()));

		   _di_IXMLNode Document = ixml->DocumentElement;
		   _di_IXMLNode Command = Document->ChildNodes->Nodes[0];

		   if (Command->NodeValue == "SUCCESS")
			 {
			   _di_IXMLNode Data = Document->ChildNodes->Nodes[2];
			   _di_IXMLNode Row = Data->ChildNodes->Nodes[0];
			   String inn, sn, model, location_id, location, agent;

			   inn = Row->ChildNodes->Nodes[0]->NodeValue;
			   sn = Row->ChildNodes->Nodes[1]->NodeValue;
			   model = Row->ChildNodes->Nodes[2]->NodeValue;
			   agent = Row->ChildNodes->Nodes[3]->NodeValue;
			   location_id = Row->ChildNodes->Nodes[4]->NodeValue;
			   location = Row->ChildNodes->Nodes[5]->NodeValue;

			   res = inn + ";" +
					 sn + ";" +
					 model + ";" +
					 location_id + ";" +
					 location + ";" +
					 agent;
             }
		   else
             res = "";
		 }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка запиту даних про Пристрій");
	   res = "";
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::SetItem(int item_id, const String &inn, const String &sn,
									 const String &model, int location_id, int agent_id)
{
  bool res;

  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("SETITEM",
					   IntToStr(item_id) + ";" +
					   inn + ";" +
					   sn + ";" +
					   model + ";" +
					   IntToStr(location_id) + ";" +
					   IntToStr(agent_id),
					   ixml) == "SUCCESS")
		 {
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка зміни даних Пристрою");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::RemoveItem(const String &item_id)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("REMOVEITEM", item_id, ixml) == "SUCCESS")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка видалення Пристрою");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AddEvent(int event_id, int item_id, int agent_id)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("ADDEVENT",
					   IntToStr(event_id) + ";" +
					   IntToStr(item_id) + ";" +
					   IntToStr(agent_id),
					   ixml) == "SUCCESS")
		 {
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка додання Події");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AskEventList(int search_type,
										  const String &item,
										  const String &date_from,
										  const String &date_to)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("GETEVENTS",
					   IntToStr(search_type) + ";" +
					   item + ";" +
					   date_from + ";" +
					   date_to,
					   ixml) == "SUCCESS")
		 {
		   ProcessAnswer(ixml.get(), ShowEventsResult);
		   CurrentRowInd = 1;
		   res = true;
		 }
	   else
		 {
		   ClearResultSet(ShowEventsResult);
		   res = false;
		 }
	 }
  catch (Exception &e)
	 {
	   ClientForm->AddActionLog("Помилка отримання переліку Подій");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AskItemList(int loc_id)
{
  bool res;

  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("GETITEMS", IntToStr(loc_id), ixml) == "SUCCESS")
		 {
		   ProcessAnswer(ixml.get(), ShowItemsResult);
		   CurrentRowInd = 1;
		   res = true;
		 }
	   else
		 {
		   ClearResultSet(ShowItemsResult);
		   res = false;
		 }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка отримання переліку Пристроїв");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::IsInnFree(const String &inn)
{
  bool res;

  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("CHECKINN", inn, ixml) == "FREE")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   ClientForm->AddActionLog("IsInnFree: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::CheckItemID(const String &id)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("CHECKID", id, ixml) == "FREE")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   ClientForm->AddActionLog("CheckItemID: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AddItem(int item_id, const String &inn, const String &sn,
									 const String &model, int location_id, int agent_id)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("ADDITEM",
					   IntToStr(item_id) + ";" +
					   inn + ";" +
					   sn + ";" +
					   model + ";" +
					   IntToStr(location_id) + ";" +
					   IntToStr(agent_id),
					   ixml) == "SUCCESS")
		 {
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка зміни даних Пристрою");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemInLocation(const String &item_id, int loc_id,
												 TStringGrid *grid)
{
  try
	 {
	   std::unique_ptr<TStringList> lst(new TStringList());
	   String item_data = AskItemInfo(item_id);

	   if (item_data == "")
		 {
           if (MessageBox(this->Handle,
						  L"Пристрій відсутній у БД. Бажаєте додати його?",
						  L"Запит",
						  MB_YESNO|MB_ICONINFORMATION) == mrYes)
			{
			  MnAddItem->Click();
			  AddItemNewID->Text = item_id;
			}

		   throw Exception("Невідомий Пристрій");
		 }

	   StrToList(lst.get(), item_data, ";");

       try
		  {
			grid->RowCount++;

			if (lst->Strings[3] == "???")
			  grid->Cells[0][grid->RowCount - 1] = "?";
			else if (lst->Strings[3].ToInt() == 0)
			  grid->Cells[0][grid->RowCount - 1] = "*";
			else if (lst->Strings[3].ToInt() == -1)
			  grid->Cells[0][grid->RowCount - 1] = "*";
			else if (lst->Strings[3].ToInt() == -2)
			  grid->Cells[0][grid->RowCount - 1] = "?";
			else if (lst->Strings[3].ToInt() == loc_id)
			  grid->Cells[0][grid->RowCount - 1] = "+";
			else if (lst->Strings[3].ToInt() != loc_id)
			  grid->Cells[0][grid->RowCount - 1] = "-";

			grid->Cells[1][grid->RowCount - 1] = item_id;
			grid->Cells[2][grid->RowCount - 1] = lst->Strings[0];
			grid->Cells[3][grid->RowCount - 1] = lst->Strings[1];
			grid->Cells[4][grid->RowCount - 1] = lst->Strings[2];
		  }
	   catch (Exception &e)
		  {
			e.Message = "Помилка виводу даних у таблицю: " + e.Message;
			throw e;
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка звірки даних Пристрою: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AskUserList()
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("GETUSERLIST", "", ixml) == "SUCCESS")
		 {
		   ProcessAnswer(ixml.get(), AdmUsersResult);
		   CurrentRowInd = 1;
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка отримання переліку користувачів");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::ControlUser(int user_id, int lock)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("CTRLUSER", IntToStr(user_id) + ";" + IntToStr(lock), ixml) == "SUCCESS")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка зміни статусу користувача");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AskLocationList(TStringGrid *grid)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("GETLOCATIONS", "", ixml) == "SUCCESS")
		 {
		   ProcessAnswer(ixml.get(), grid);
		   CurrentRowInd = 1;
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   ClientForm->AddActionLog("Помилка отримання переліку локацій");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::RemoveLocation(int location_id)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("REMOVELOCATION", IntToStr(location_id), ixml) == "SUCCESS")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка видалення Локації");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AddLocation(const String &index, const String &name)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("ADDLOCATION", index + ";" + name, ixml) == "SUCCESS")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка видалення Локації");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::EditLocation(int location_id, const String &index, const String &name)
{
  bool res;

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("EDITLOCATION",
					   IntToStr(location_id) + ";" + index + ";" + name,
					   ixml) == "SUCCESS")
		 {
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка видалення Локації");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::AskServerLog(const String &date)
{
  bool res;

  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("GETLOG", date, ixml) == "SUCCESS")
		 {
		   ProcessAnswer(ixml.get(), AdmLogsResult);
		   CurrentRowInd = 1;
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка отримання логу сервера");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::SendQuery(const String &query)
{
  bool res;

  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("EXECQUERY", query, ixml) == "SUCCESS")
		 {
		   ProcessAnswer(ixml.get(), AdmRequestResult);
		   CurrentRowInd = 1;
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка надсилання SQL-запиту");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::RestorePassword(const String &login, const String &mail)
{
  bool res;

  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   if (SendRequest("CHECKMAIL", mail, ixml) == "SUCCESS")
		 {
		   if (SendRequest("RESTOREPWD", login + ";" + mail, ixml) == "SUCCESS")
			 res = true;
		   else
			 res = false;
         }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Помилка надсилання SQL-запиту");
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

       ms = nullptr;
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

       ms = nullptr;
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

void __fastcall TClientForm::ProcessAnswer(TXMLDocument *ixml, TStringGrid *grid)
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

       try
		  {
			Command = Document->ChildNodes->Nodes[0];
			Titles = Document->ChildNodes->Nodes[1];
			Data = Document->ChildNodes->Nodes[2];
		  }
	   catch (Exception &e)
		  {
			e.Message = "Помилка отримання даних з XML" + e.Message;
			throw e;
		  }

	   String value;
	   int colsize;

	   if (!grid)
		 throw Exception("Не визначено таблицю відображеня даних");

	   try
		  {
			ClearResultSet(grid);

			grid->ColCount = Titles->ChildNodes->Count;
			grid->RowCount = Data->ChildNodes->Count + 1;
			grid->FixedRows = 1;

			for (int i = 0; i < Titles->ChildNodes->Count; i++)
			   {
				 Title = Titles->ChildNodes->Nodes[i];
				 colsize = StrToInt(Title->GetAttribute("size"));
				 value = Title->NodeValue;

				 grid->ColWidths[i] = colsize; //встановлюємо розмір полів
				 grid->Cells[i][0] = value; //заповнюємо перший рядок таблиці назвами полів
			   }
		  }
	   catch (Exception &e)
		  {
			e.Message = "Помилка форматування таблиці відображення даних" + e.Message;
			throw e;
		  }

       try
		  {
			grid->RowCount = Data->ChildNodes->Count + 1;
		  }
	   catch (Exception &e)
		  {
			e.Message = "Помилка встановлення рядків таблиці: " + e.Message;
			throw e;
		  }

	   try
		  {
			grid->RowCount = Data->ChildNodes->Count + 1;

			for (int i = 0; i < Data->ChildNodes->Count; i++)
			   {
				 Row = Data->ChildNodes->Nodes[i];

				 for (int j = 0; j < Row->ChildNodes->Count; j++)
					{
					  Field = Row->ChildNodes->Nodes[j];

					  value = Field->NodeValue;
                      //заповнюємо таблицю, починаючи з 1-го рядка, 0-й це заголовки
					  grid->Cells[j][i + 1] = value;
					}
			   }
		  }
	   catch (Exception &e)
		  {
			e.Message = "Помилка виводу даних у таблицю: " + e.Message;
			throw e;
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("ProcessAnswer: " + e.ToString());
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

       try
		  {
			Command = Document->ChildNodes->Nodes[0];
			Titles = Document->ChildNodes->Nodes[1];
			Data = Document->ChildNodes->Nodes[2];
		  }
	   catch (Exception &e)
		  {
			e.Message = "Помилка отримання даних з XML" + e.Message;
			throw e;
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

String __fastcall TClientForm::SendRequest(const String &command,
										   const String &params,
										   std::unique_ptr<TXMLDocument> &ixml)
{
  String res;

  try
	 {
	   std::unique_ptr<TStringStream> data;

	   if (params != "")
		 data.reset(CreateRequest(command, params));
	   else
		 data.reset(CreateRequest(command));

	   if (AskToServer(Server, data.get()))
		 {
		   data->Position = 0;
		   ixml.reset(CreateXMLStream(data.get()));

		   _di_IXMLNode Document = ixml->DocumentElement;
		   _di_IXMLNode Command = Document->ChildNodes->Nodes[0];

		   res = Command->NodeValue;
		 }
	 }
  catch (Exception &e)
	 {
	   res = "";
	   AddActionLog("SendRequest: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ClearResultSet(TStringGrid *result_set)
{
  try
	 {
	   for (int i = 0; i < result_set->RowCount - 1; i++)
		  result_set->Rows[i]->Clear();

	   result_set->ColCount = 0;
	   result_set->RowCount = 0;
	   result_set->FixedRows = 0;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("ClearResultSet: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::IsItemExistInCheckTable(const String &id)
{
  bool res;

  try
	 {
	   res = false;

	   for (int i = 1; i < CheckItemsResult->RowCount; i++)
		  {
			if (CheckItemsResult->Cells[1][i] == id)
			  {
				res = true;
				break;
			  }
		  }
	 }
  catch (Exception &e)
	 {
	   res = true;
	   AddActionLog("IsItemExistInCheckTable: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PrepareCheckTable()
{
  try
	 {
	   CheckItemsResult->ColCount = 5;
	   CheckItemsResult->ColWidths[0] = 0;
	   CheckItemsResult->ColWidths[1] = 50;
	   CheckItemsResult->ColWidths[2] = 150;
	   CheckItemsResult->ColWidths[3] = 150;
	   CheckItemsResult->ColWidths[4] = 300;
	   CheckItemsResult->Cells[0][0] = "";
	   CheckItemsResult->Cells[1][0] = "ID";
	   CheckItemsResult->Cells[2][0] = "Інвентарний номер";
	   CheckItemsResult->Cells[3][0] = "Серійний номер";
	   CheckItemsResult->Cells[4][0] = "Модель";
	 }
  catch (Exception &e)
	 {
	   AddActionLog("PrepareCheckTable: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

bool __fastcall TClientForm::IsValidPassword(const String &password)
{
  bool res;

  try
	 {
	   if (password.Length() < 8)
		 throw Exception("Довжина паролю є замалою");

	   for (int i = 1; i <= password.Length(); i++)
		  {
			res = false;

			for (int j = 0; j < cb_sz; j++)
			   {
				 if (password[i] == pwd_char_base[j])
				   {
					 res = true;
					 break;
				   }
			   }

			if (!res)
			  throw Exception("Використано недопустимий символ");
          }
	 }
  catch (Exception &e)
	 {
	   res = false;
	   AddActionLog("IsValidPassword: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ListenerExecute(TIdContext *AContext)
{
  std::unique_ptr<TStringStream> ms(new TStringStream("", TEncoding::UTF8, true));
  std::unique_ptr<TXMLDocument> ixml(nullptr);

  AContext->Connection->IOHandler->ReadStream(ms.get());

  try
	 {
	   ms->LoadFromStream(TSAESCypher::Encrypt(ms.get(), DataCryptKey));
	   ms->Position = 0;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Listener: Розшифровка пакету: " + e.ToString());

	   return;
	 }

  try
	 {
	   ixml.reset(CreateXMLStream(ms.get()));

	   ParseXML(ixml.get());
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Listener: Парсинг: " + e.ToString());

	   return;
	 }
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

void __fastcall TClientForm::CheckItemResultMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
  TStringGrid *grid = dynamic_cast<TStringGrid*>(Sender);

  if (grid)
	grid->MouseToCell(X, Y, CurrentColInd, CurrentRowInd);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemEditClick(TObject *Sender)
{
  EditItemForm->Show();

  EditItemForm->Inn->Text = CheckItemInn->Text;
  EditItemForm->Sn->Text = CheckItemSn->Text;
  EditItemForm->Model->Text = CheckItemModel->Text;
  EditItemForm->CurrentLocation->Caption = CheckItemCurrentLocation->Caption;
  EditItemForm->CurrentLocation->Tag = CheckItemCurrentLocation->Tag;

  EditItemForm->Inn->Hint = EditItemForm->Inn->Text;
  EditItemForm->Sn->Hint = EditItemForm->Sn->Text;
  EditItemForm->Model->Hint = EditItemForm->Model->Text;
  EditItemForm->CurrentLocation->Hint = IntToStr(EditItemForm->CurrentLocation->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemRemoveClick(TObject *Sender)
{
//видалення Пристрою з БД
  if (CheckItemScannedCode->Text != "")
	{
	  if (MessageBox(this->Handle,
					 L"Ви впевнені, що хочете видалити Пристрій?",
					 L"Підтвердження",
					 MB_YESNO|MB_ICONINFORMATION) == mrYes)
		{
		  RemoveItem(CheckItemScannedCode->Text);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemRefreshClick(TObject *Sender)
{
//повторний запит до БД
  CheckItemInn->Text = "";
  CheckItemSn->Text = "";
  CheckItemModel->Text = "";
  CheckItemCurrentLocation->Caption = "";
  CheckItemLastAgent->Caption = "";

  if (CheckItemScannedCode->Text != "")
	{
	  String item_data = AskItemInfo(CheckItemScannedCode->Text);

      ItemID = CheckItemScannedCode->Text.ToInt();

	  if (item_data != "")
		{
		  std::unique_ptr<TStringList> lst(new TStringList());

		  try
			 {
			   StrToList(lst.get(), item_data, ";");

			   CheckItemInn->Text = lst->Strings[0];
			   CheckItemSn->Text = lst->Strings[1];
			   CheckItemModel->Text = lst->Strings[2];
               CheckItemCurrentLocation->Tag = lst->Strings[3].ToInt();
			   CheckItemCurrentLocation->Caption = lst->Strings[4];
			   CheckItemLastAgent->Caption = lst->Strings[5];
			 }
          catch (Exception &e)
			 {
			   AddActionLog("Запит даних про Пристрій: " + e.ToString());
			 }
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemScannedCodeKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	CheckItemRefresh->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemShowHistoryClick(TObject *Sender)
{
  MnShowEvents->Click();
  ShowEventsInn->Text = IntToStr(ItemID);
  ShowEventsSearchType->ItemIndex = 0;
  ShowEventsApply->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AddItemCreateClick(TObject *Sender)
{
  //створюємо запит на додання Пристрою в БД
  //перед створенням треба перевіряти інв. № чи існує такий в БД
  IDError->Hide();
  InnError->Hide();
  ModelError->Hide();

  if (AddItemNewID->Text == "")
	{
	  IDError->Caption = "Не вказано ID Пристрою";
	  IDError->Show();
	}
  else if (AddItemNewInn->Text == "")
	{
	  InnError->Caption = "Не вказано нівентарний номер";
	  InnError->Show();
	}
  else if (AddItemNewModel->Text == "")
	{
	  ModelError->Caption = "Не вказано модель";
	  ModelError->Show();
	}
  else if (!CheckItemID(AddItemNewID->Text))
	{
	  IDError->Caption = "Пристрій з даним ID вже існує";
	  IDError->Show();
	}
  else if (!IsInnFree(AddItemNewInn->Text))
    {
	  InnError->Caption = "Даний інвентарний номер вже існує";
	  InnError->Show();
	}
  else
	{
	  int item_id = -1, location_id = 0;

	  try
		 {
		   item_id = AddItemNewID->Text.ToInt();
		 }
	  catch (Exception &e)
		 {
		   IDError->Caption = "Невірний ID Пристрою";
		   IDError->Show();
		 }

	  if (AddItemCurrentLocation->Caption != "")
		location_id = AddItemCurrentLocation->Tag;

	  if (AddItem(item_id, AddItemNewInn->Text, AddItemNewSn->Text,
				  AddItemNewModel->Text, location_id, UserID))
		{
		  AddActionLog("Пристрій успішно додано");
		  AddEvent(OP_CREATE_ITM, item_id, UserID);

		  if (location_id > 0)
			AddEvent(OP_ADD_ITM, item_id, UserID);
		}
	  else
		{
		  AddActionLog("Не вдалося додати Пристрій");
		}
    }
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
  Location = AddItemCurrentLocation;
  SelectLocationForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPSetPwdClick(TObject *Sender)
{
  AdmUsersSetPwd->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPLockUserClick(TObject *Sender)
{
  AdmUsersLock->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPUnlockUserClick(TObject *Sender)
{
  AdmUsersUnlock->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmUsersAddClick(TObject *Sender)
{
  AddUserForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmUsersSetPwdClick(TObject *Sender)
{
  int id = 0;

  if (CurrentRowInd > 0)
	id = AdmUsersResult->Cells[0][CurrentRowInd].ToInt();

  if (id)
	{
      SetPasswordForm->UserID = id;
	  SetPasswordForm->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmUsersLockClick(TObject *Sender)
{
  String id;

  if (CurrentRowInd > 0)
	id = AdmUsersResult->Cells[0][CurrentRowInd];

  if (id != "")
	{
	  if (MessageBox(this->Handle,
					 L"Заблокувати користувача?",
					 L"Підтвердження",
					 MB_YESNO|MB_ICONINFORMATION) == mrYes)
		{
		  ControlUser(id.ToInt(), true);
		  AskUserList();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmUsersUnlockClick(TObject *Sender)
{
  String id;

  if (CurrentRowInd > 0)
	id = AdmUsersResult->Cells[0][CurrentRowInd];

  if (id != "")
	{
	  if (MessageBox(this->Handle,
					 L"Разблокувати користувача?",
					 L"Підтвердження",
					 MB_YESNO|MB_ICONINFORMATION) == mrYes)
		{
		  ControlUser(id.ToInt(), false);
		  AskUserList();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmUsersRefreshClick(TObject *Sender)
{
  AskUserList();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLocationsAddClick(TObject *Sender)
{
  EditLocationForm->Mode = true;
  EditLocationForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLocationsEditClick(TObject *Sender)
{
  if (CurrentRowInd > 0)
	{
	  EditLocationForm->Mode = false;
	  EditLocationForm->LocationID = AdmLocationsResult->Cells[0][CurrentRowInd].ToInt();
	  EditLocationForm->LocationIndex = AdmLocationsResult->Cells[1][CurrentRowInd];
	  EditLocationForm->LocationName = AdmLocationsResult->Cells[2][CurrentRowInd];
	  EditLocationForm->Show();
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLocationsRemoveClick(TObject *Sender)
{
  String id;

  if (CurrentRowInd > 0)
	id = AdmLocationsResult->Cells[0][CurrentRowInd];

  if (id != "")
	{
	  if (MessageBox(this->Handle,
					 L"Видалити Локацію?",
					 L"Підтвердження",
					 MB_YESNO|MB_ICONINFORMATION) == mrYes)
		{
		  RemoveLocation(id.ToInt());
		  AskLocationList(AdmLocationsResult);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPRefreshClick(TObject *Sender)
{
  RefreshButton->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPEditClick(TObject *Sender)
{
  EditButton->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPRemoveClick(TObject *Sender)
{
  ShowItemsRemove->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPLocationsRefreshClick(TObject *Sender)
{
  RefreshButton->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPAddLocationClick(TObject *Sender)
{
  AdmLocationsAdd->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPEditLocationClick(TObject *Sender)
{
  AdmLocationsEdit->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPRemoveLocationClick(TObject *Sender)
{
  AdmLocationsRemove->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPCheckSetUnknownClick(TObject *Sender)
{
  CheckItemsSendToUnknown->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::PPCheckDelFromTableClick(TObject *Sender)
{
  CheckItemsDelete->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLogsShowClick(TObject *Sender)
{
  AskServerLog(DateToStr(AdmLogsDate->Date));
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ChangeMailClick(TObject *Sender)
{
  ChangeMailForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ChangePasswordClick(TObject *Sender)
{
  ChangePasswordForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowEventsDateFilterClick(TObject *Sender)
{
  if (ShowEventsDateFilter->Checked)
	{
	  ShowEventsDateFrom->Enabled = true;
	  ShowEventsDateTo->Enabled = true;
	}
  else
	{
	  ShowEventsDateFrom->Enabled = false;
	  ShowEventsDateTo->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowEventsApplyClick(TObject *Sender)
{
  //надсилання запиту до серверу

  if (ShowEventsDateFilter->Checked)
	{
	  AskEventList(ShowEventsSearchType->ItemIndex,
				   ShowEventsInn->Text,
				   DateToStr(ShowEventsDateFrom->Date),
				   DateToStr(ShowEventsDateTo->Date));
	}
  else
	AskEventList(ShowEventsSearchType->ItemIndex, ShowEventsInn->Text, "-", "-");
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowEventsInnKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
    ShowEventsApply->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowEventsInnChange(TObject *Sender)
{
  if (ShowEventsInn->Text != "")
	ShowEventsApply->Enabled = true;
  else
	ShowEventsApply->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowItemsSelectLocationClick(TObject *Sender)
{
  Location = ShowItemsCurrentLocation;
  SelectLocationForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowItemsEditClick(TObject *Sender)
{
  if (CurrentRowInd > 0)
	{
	  EditItemForm->Show();

	  ItemID = ShowItemsResult->Cells[0][CurrentRowInd].ToInt();

	  EditItemForm->Inn->Text = ShowItemsResult->Cells[1][CurrentRowInd];
	  EditItemForm->Sn->Text = ShowItemsResult->Cells[2][CurrentRowInd];
	  EditItemForm->Model->Text = ShowItemsResult->Cells[3][CurrentRowInd];
	  EditItemForm->CurrentLocation->Caption = ShowItemsCurrentLocation->Caption;
	  EditItemForm->CurrentLocation->Tag = ShowItemsCurrentLocation->Tag;

	  EditItemForm->Inn->Hint = EditItemForm->Inn->Text;
	  EditItemForm->Sn->Hint = EditItemForm->Sn->Text;
	  EditItemForm->Model->Hint = EditItemForm->Model->Text;
	  EditItemForm->CurrentLocation->Hint = IntToStr(EditItemForm->CurrentLocation->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowItemsRefreshClick(TObject *Sender)
{
  //запит переліку Пристроїв в локації

  if (ShowItemsCurrentLocation->Caption != "")
    AskItemList(ShowItemsCurrentLocation->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowItemsRequestClick(TObject *Sender)
{
  ShowItemsRefresh->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowItemsRemoveClick(TObject *Sender)
{
  //запит на видалення Пристрою
  String id;

  if (CurrentRowInd > 0)
	id = ShowItemsResult->Cells[0][CurrentRowInd];

  if (id != "")
	{
	  if (MessageBox(this->Handle,
					 L"Ви впевнені, що хочете видалити Пристрій?",
					 L"Підтвердження",
					 MB_YESNO|MB_ICONINFORMATION) == mrYes)
		{
		  RemoveItem(id);
          ShowItemsRefresh->Click();
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsSelectLocationClick(TObject *Sender)
{
  Location = CheckItemsCurrentLocation;
  SelectLocationForm->Show();
  ClearResultSet(CheckItemsResult);
  PrepareCheckTable();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsEditClick(TObject *Sender)
{
  if (CurrentRowInd > 0)
	{
	  EditItemForm->Show();

	  ItemID = CheckItemsResult->Cells[1][CurrentRowInd].ToInt();

	  EditItemForm->Inn->Text = CheckItemsResult->Cells[2][CurrentRowInd];
	  EditItemForm->Sn->Text = CheckItemsResult->Cells[3][CurrentRowInd];
	  EditItemForm->Model->Text = CheckItemsResult->Cells[4][CurrentRowInd];
	  EditItemForm->CurrentLocation->Caption = CheckItemsCurrentLocation->Caption;
	  EditItemForm->CurrentLocation->Tag = CheckItemsCurrentLocation->Tag;

	  EditItemForm->Inn->Hint = EditItemForm->Inn->Text;
	  EditItemForm->Sn->Hint = EditItemForm->Sn->Text;
	  EditItemForm->Model->Hint = EditItemForm->Model->Text;
	  EditItemForm->CurrentLocation->Hint = IntToStr(EditItemForm->CurrentLocation->Tag);
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsSendToUnknownClick(TObject *Sender)
{
  //запит на перенесення пристрою до нез'ясованих (ід локації = -1)
  if (CurrentRowInd > 0)
	{
	  if (MessageBox(this->Handle,
					 L"Перенести Пристрій до нез'ясованих?",
					 L"Підтвердження",
					 MB_YESNO|MB_ICONINFORMATION) == mrYes)
		{
		  try
			 {
			   String inn = CheckItemsResult->Cells[2][CurrentRowInd],
					  sn = CheckItemsResult->Cells[3][CurrentRowInd],
					  model = CheckItemsResult->Cells[4][CurrentRowInd];
			   int id = CheckItemsResult->Cells[1][CurrentRowInd].ToInt();

			   if (SetItem(id, inn, sn, model, -1, UserID))
				 {
				   AddEvent(OP_SEND_UNK, id, UserID);
				   CheckItemsDelete->Click();
				 }
			 }
		  catch (Exception &e)
			 {
			   AddActionLog("Не вдалося перенести Пристрій до нез'ясованих");
			 }
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsScannedCodeKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	CheckItemsAddToList->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsAddToListClick(TObject *Sender)
{
  //додавання пристрою до відомості
  CheckError->Hide();

  if (CheckItemsCurrentLocation->Caption == "")
	{
	  CheckError->Caption = "Не вказано Локацію";
	  CheckError->Show();
	}
  else if (CheckItemsScannedCode->Text == "")
	{
	  CheckError->Caption = "Не вказано ID Пристрою";
	  CheckError->Show();
	}
  else if (IsItemExistInCheckTable(CheckItemsScannedCode->Text))
	{
	  CheckError->Caption = "Вказаний ID вже присутній у відомості";
	  CheckError->Show();
	}
  else
	{
	  CheckItemInLocation(CheckItemsScannedCode->Text,
						  CheckItemsCurrentLocation->Tag,
						  CheckItemsResult);

      CheckItemsScannedCode->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsDeleteClick(TObject *Sender)
{
  //видалити пристрій з відомості
  if (CurrentRowInd > 0)
	{
	  for (int i = CurrentRowInd; i <= CheckItemsResult->RowCount - 2; i++)
		 CheckItemsResult->Rows[i]->Assign(CheckItemsResult->Rows[i + 1]);

      CheckItemsResult->RowCount = CheckItemsResult->RowCount - 1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsResultDrawCell(TObject *Sender, int ACol, int ARow,
													  TRect &Rect, TGridDrawState State)
{
  String cell_text = CheckItemsResult->Cells[ACol][ARow];

  Rect.SetLocation(Rect.Location.X - 3, Rect.Location.Y);
  Rect.SetWidth(Rect.Size.Width + 6);

  if (CheckItemsResult->Cells[0][ARow] == "+")
	CheckItemsResult->Canvas->Brush->Color = clGreen;
  else if (CheckItemsResult->Cells[0][ARow] == "-")
	CheckItemsResult->Canvas->Brush->Color = clRed;
  else if (CheckItemsResult->Cells[0][ARow] == "?")
	CheckItemsResult->Canvas->Brush->Color = clYellow;
  else if (CheckItemsResult->Cells[0][ARow] == "*")
	CheckItemsResult->Canvas->Brush->Color = clGray;
  else
    CheckItemsResult->Canvas->Brush->Color = clWindow;

  CheckItemsResult->Canvas->FillRect(Rect);
  CheckItemsResult->Canvas->Font->Color = clBlack;
  CheckItemsResult->Canvas->TextOut(Rect.Left + 2,
									Rect.Top + 2,
									CheckItemsResult->Cells[ACol][ARow]);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLocationsRefreshClick(TObject *Sender)
{
  AskLocationList(AdmLocationsResult);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ExecuteClick(TObject *Sender)
{
  if (QueryText->Text != "")
	SendQuery(QueryText->Text);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::QueryTextKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
  if (Key == 120)
    Execute->Click();
}
//---------------------------------------------------------------------------

