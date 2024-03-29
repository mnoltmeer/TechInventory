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
#include "ImportLocationPreview.h"
#include "Client.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TClientForm *ClientForm;

String Server, User; //�������� ������ �� ���� �����������
int UserID; //ID ��������� �����������
int ItemID; //ID ��������� ��������
bool IsAdmin; //����, �� �������, �� � �������� ���� ������
bool IsLocked; //����, �� �������, �� � �������� ����� ����������� ��������
String AppPath;
String LogPath;
int MainFormWidth, MainFormHeight;
bool MainFormFullScreen;
TPanel *ActivePanel; //������� ������� ������
int CurrentRowInd, CurrentColInd; //������� �������� ����� ���� � ������� �����������
TLabel *Location; //����� ��� ����������� ������ �������
TBitBtn *RefreshButton; //������� ������ ��� ��������� �����
TBitBtn *EditButton;  //����������� ��������
bool NeedUpdate; //���� �� ������� ������������ ��������� ���� �������� ��������
TStringGrid *ResultGrid, *FilteredGrid;
TEdit *CurrentFilter;
TLabel *CurrentFilterLabel;
//---------------------------------------------------------------------------

__fastcall TClientForm::TClientForm(TComponent* Owner)
	: TForm(Owner)
{
  NeedUpdate = false;
  AppPath = GetDirPathFromFilePath(Application->ExeName);
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

  Listener->DefaultPort = DEFAULT_CLIENT_PORT;
  Listener->Active = true;

  ClientVersion->Caption = "����� �볺���: " +
						   GetVersionInString(Application->ExeName.c_str());

  ServerInfo->Caption = "������: " +
						Server +
						", �����: "; //������� �������� ����� �������

  UserInfo->Caption = "����������: " + User;

  SetUIImages();

  LoginForm->Show();
  LoginForm->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::FormClose(TObject *Sender, TCloseAction &Action)
{
  Listener->Active = false;
  WriteSettings();

  if (NeedUpdate)
    StartProcessByExeName(AppPath + "\\DownloadedClient.exe");
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

	   if (reg->OpenKey("Software\\TIClient\\Form", true))
		 {
		   if (reg->ValueExists("FullScreen"))
			 MainFormFullScreen = reg->ReadBool("FullScreen");
		   else
			 MainFormFullScreen = false;

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

	   if (reg->OpenKey("Software\\TIClient\\Params", true))
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
  bool res = true;

  try
	 {
       String server = host;
	   int port = DEFAULT_SERVER_PORT;

	   try
		  {
			int pos = host.LastDelimiter(":");

			if (pos)
			  {
				port = server.SubString(pos + 1, server.Length() - pos).ToInt();
				server = server.Delete(pos, server.Length() - pos);
			  }
		  }
	   catch (Exception &e)
		  {
			throw Exception("������� ���������� ��������� ����������: " + e.ToString());
		  }

	   std::unique_ptr<TTCPRequester> sender(new TTCPRequester(server, port));

	   try
		  {
			AddActionLog("���������� ������ �����");
			buffer->LoadFromStream(TSAESCypher::Crypt(buffer, GenHashKey()));
		  }
	   catch (Exception &e)
		  {
			throw Exception("������� ����������: " + e.ToString());
		  }

	   AddActionLog("³������� ����� �� ������");

	   if (!sender->SendData(buffer))
		 throw Exception("������� �������� �����");

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
  bool res = true;

  try
	 {
	   String server = host;
	   int port = DEFAULT_SERVER_PORT;

	   try
		  {
			int pos = host.LastDelimiter(":");

			if (pos)
			  {
				port = server.SubString(pos + 1, server.Length() - pos).ToInt();
				server = server.Delete(pos, server.Length() - pos);
			  }
		  }
	   catch (Exception &e)
		  {
			throw Exception("������� ���������� ��������� ����������: " + e.ToString());
		  }

       std::unique_ptr<TTCPRequester> sender(new TTCPRequester(server, port));

	   try
		  {
			AddActionLog("���������� ������ �����");
			buffer->LoadFromStream(TSAESCypher::Crypt(buffer, GenHashKey()));
		  }
	   catch (Exception &e)
		  {
			throw Exception("������� ����������: " + e.ToString());
		  }

	   AddActionLog("���� ������ � ��������");

	   if (!sender->AskData(buffer))
		  throw Exception("������� ����� ������");

	   try
		  {
			AddActionLog("������������� ������ �����");
			buffer->Position = 0;
			buffer->LoadFromStream(TSAESCypher::Encrypt(buffer, GenHashKey()));
		  }
	   catch (Exception &e)
		 {
		   throw Exception("������� ����������: " + e.ToString());
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
  PrepareCheckTable();
  CheckError->Hide();

  ResultGrid = CheckItemsResult;
  FilteredGrid = CheckItemsFiltered;
  CurrentFilter = Edit4;
  CurrentFilterLabel = Label33;
  CurrentFilter->Text = "";
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
  RefreshButton = ShowItemsRefresh;
  EditButton = ShowItemsEdit;

  ResultGrid = ShowItemsResult;
  FilteredGrid = ShowItemsFiltered;
  CurrentFilter = Edit5;
  CurrentFilterLabel = Label35;
  CurrentFilter->Text = "";
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
  ShowEventsApply->Enabled = false;

  ResultGrid = ShowEventsResult;
  FilteredGrid = ShowEventsFiltered;
  CurrentFilter = Edit6;
  CurrentFilterLabel = Label37;
  CurrentFilter->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmUsersClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmUsers->Show();
  ActivePanel = PnAdmUsers;
  AskUserList();

  ResultGrid = AdmUsersResult;
  FilteredGrid = AdmUsersFiltered;
  CurrentFilter = Edit3;
  CurrentFilterLabel = Label25;
  CopyRecords(ResultGrid, FilteredGrid);
  CurrentFilter->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmLocationsClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmLocations->Show();
  ActivePanel = PnAdmLocations;
  AskLocationList(AdmLocationsResult);

  ResultGrid = AdmLocationsResult;
  FilteredGrid = AdmLocationsFiltered;
  CurrentFilter = Filter;
  CurrentFilterLabel = LbFilterField;
  CopyRecords(ResultGrid, FilteredGrid);
  CurrentFilter->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmLogsClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmLogs->Show();
  ActivePanel = PnAdmLogs;
  AdmLogsDate->Date = Date().CurrentDate();

  ResultGrid = AdmLogsResult;
  FilteredGrid = AdmLogsFiltered;
  CurrentFilter = Edit1;
  CurrentFilterLabel = Label12;
  CurrentFilter->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::MnAdmManageClick(TObject *Sender)
{
  HideAllPanels();
  PnAdmManage->Show();
  ActivePanel = PnAdmManage;

  ResultGrid = AdmRequestResult;
  FilteredGrid = AdmRequestFiltered;
  CurrentFilter = Edit2;
  CurrentFilterLabel = Label22;
  CurrentFilter->Text = "";
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

	   AdmLocationsAdd->Glyph = PanelImages->GetBitmap(21, 18, 18);
	   AdmLocationsAdd->Glyph->Transparent = true;

	   AdmLocationsEdit->Glyph = PanelImages->GetBitmap(11, 18, 18);
	   AdmLocationsEdit->Glyph->Transparent = true;
	   AdmLocationsEdit->Glyph->TransparentColor = clBlack;

	   AdmLocationsRemove->Glyph = PanelImages->GetBitmap(10, 18, 18);
	   AdmLocationsRemove->Glyph->Transparent = true;

	   AdmLocationsRefresh->Glyph = PanelImages->GetBitmap(13, 18, 18);
	   AdmLocationsRefresh->Glyph->Transparent = true;
	   AdmLocationsRefresh->Glyph->TransparentColor = clBlack;

	   PPAddLocation->Bitmap = PanelImages->GetBitmap(21, 16, 16);
	   PPAddLocation->Bitmap->Transparent = true;

	   AdmLocationsImportCSV->Glyph = PanelImages->GetBitmap(19, 18, 18);
	   AdmLocationsImportCSV->Glyph->Transparent = true;

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

	   AdmManageExportCSV->Glyph = PanelImages->GetBitmap(22, 18, 18);
	   AdmManageExportCSV->Glyph->Transparent = true;

	   AdmManageExportExcel->Glyph = PanelImages->GetBitmap(20, 18, 18);
	   AdmManageExportExcel->Glyph->Transparent = true;

	   AdmUsersExportCSV->Glyph = PanelImages->GetBitmap(22, 18, 18);
	   AdmUsersExportCSV->Glyph->Transparent = true;

	   AdmUsersExportExcel->Glyph = PanelImages->GetBitmap(20, 18, 18);
	   AdmUsersExportExcel->Glyph->Transparent = true;

	   AdmLogsExportCSV->Glyph = PanelImages->GetBitmap(22, 18, 18);
	   AdmLogsExportCSV->Glyph->Transparent = true;

	   AdmLogsExportExcel->Glyph = PanelImages->GetBitmap(20, 18, 18);
	   AdmLogsExportExcel->Glyph->Transparent = true;

	   AdmLocationsExportCSV->Glyph = PanelImages->GetBitmap(22, 18, 18);
	   AdmLocationsExportCSV->Glyph->Transparent = true;

	   AdmLocationsExportExcel->Glyph = PanelImages->GetBitmap(20, 18, 18);
	   AdmLocationsExportExcel->Glyph->Transparent = true;

	   CheckItemsExportCSV->Glyph = PanelImages->GetBitmap(22, 18, 18);
	   CheckItemsExportCSV->Glyph->Transparent = true;

	   CheckItemsExportExcel->Glyph = PanelImages->GetBitmap(20, 18, 18);
	   CheckItemsExportExcel->Glyph->Transparent = true;

	   ShowItemsExportCSV->Glyph = PanelImages->GetBitmap(22, 18, 18);
	   ShowItemsExportCSV->Glyph->Transparent = true;

	   ShowItemsExportExcel->Glyph = PanelImages->GetBitmap(20, 18, 18);
	   ShowItemsExportExcel->Glyph->Transparent = true;

	   ShowEventsExportCSV->Glyph = PanelImages->GetBitmap(22, 18, 18);
	   ShowEventsExportCSV->Glyph->Transparent = true;

	   ShowEventsExportExcel->Glyph = PanelImages->GetBitmap(20, 18, 18);
	   ShowEventsExportExcel->Glyph->Transparent = true;

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
	   AddActionLog("������� ������������ UI");
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
	   AddActionLog("������� ���������� UI");
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
	   AddActionLog("������� ������������� UI");
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
	   AddActionLog("������� ������������� UI");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AskServerVersion()
{
  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   ServerInfo->Caption = "������: " +
						Server +
						", �����: " +
						SendRequest("GETVERSION", "", ixml);
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� ��������� ���� �������");
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
	   AddActionLog("������� ����������� ������");
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
	   AddActionLog("������� �������� ������");
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
	   AddActionLog("������� ����������� ������ ��. �����");
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
	   AddActionLog("������� ������ ����� ��� �������");
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
	   AddActionLog("������� ���� ����� ��������");
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
		 {
		   AddEvent(OP_REMOVE_ITM, ItemID, UserID);
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� ��������� ��������");
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
	   AddActionLog("������� ������� ��䳿");
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
	   ClientForm->AddActionLog("������� ��������� ������� ����");
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
	   AddActionLog("������� ��������� ������� ��������");
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
		   AddEvent(OP_CREATE_ITM, ItemID, UserID);
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� ���� ����� ��������");
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
						  L"������� �������� � ��. ������ ������ ����?",
						  L"�����",
						  MB_YESNO|MB_ICONINFORMATION) == mrYes)
			{
			  MnAddItem->Click();
			  AddItemNewID->Text = item_id;
			}

		   throw Exception("�������� �������");
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
			e.Message = "������� ������ ����� � �������: " + e.Message;
			throw e;
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� ����� ����� ��������: " + e.ToString());
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
	   AddActionLog("������� ��������� ������� ������������");
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
	   AddActionLog("������� ���� ������� �����������");
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
	   ClientForm->AddActionLog("������� ��������� ������� �������");
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
	   AddActionLog("������� ��������� �������");
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
	   AddActionLog("������� ��������� �������");
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
	   AddActionLog("������� ����������� �������");
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
	   AddActionLog("������� ��������� ���� �������");
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
	   AddActionLog("������� ���������� SQL-������");
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
	   AddActionLog("������� �������� ������");
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AskActualClientVersion()
{
  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;
	   String ver = GetVersionInString(Application->ExeName.c_str()),
			  actver = SendRequest("GETCLIENTVERSION", "", ixml);

       ActualClientVersion->Caption = actver;

	   if ((ver != actver) && (actver != "no_data"))
		 UpdateClient->Enabled = true;
	   else
		 UpdateClient->Enabled = false;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� ��������� ��������� ���� �볺���");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::DownloadClient()
{
  try
	 {
	   std::unique_ptr<TXMLDocument> ixml;

	   ActualClientVersion->Caption = SendRequest("DOWNLOADMODULE", "", ixml);
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� ������������ �볺�������� ������");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CopyTitles(TStringGrid *from, TStringGrid *to)
{
  try
	 {
	   to->ColCount = from->ColCount;
	   to->RowCount = 1;

	   for (int i = 0; i < from->ColCount; i++)
		  {
			to->ColWidths[i] = from->ColWidths[i];
			to->Cells[i][0] = from->Cells[i][0];
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� �������� ��������� �� ���������");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CopyRecords(TStringGrid *from, TStringGrid *to)
{
  try
	 {
	   ClearResultSet(to);
	   CopyTitles(from, to);

	   to->RowCount = from->RowCount;

	   for (int i = 1; i < from->RowCount; i++)
		  {
			for (int j = 0; j < from->ColCount; j++)
			   to->Cells[j][i] = from->Cells[j][i];
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� �������� ����� �� ���������");
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::FilterTable(TStringGrid *from, TStringGrid *to,
										 int col, const String &text)
{
  try
	 {
	   ClearResultSet(to);
	   CopyTitles(from, to);

	   for (int i = 1; i < from->RowCount; i++)
		  {
			if (from->Cells[col][i].UpperCase().Pos(text.UpperCase()))
			  {
				to->RowCount++;

				for (int j = 0; j < from->ColCount; j++)
				   to->Cells[j][to->RowCount - 1] = from->Cells[j][i];
			  }
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� ���������� �������");
	 }
}
//---------------------------------------------------------------------------

const char* __fastcall TClientForm::GenHashKey()
{
  AnsiString res;

  try
	 {
	   res = IntToStr(static_cast<int>(Date()) << 3);
	 }
  catch (Exception &e)
	 {
	   res = "";
	   AddActionLog("������� ��������� ���-�����");
	 }

  return res.c_str();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ImportLocations(const String &file, TStringGrid *grid)
{
  try
	 {
	   std::unique_ptr<TDataHolder> csv(new TDataHolder());

	   try
		  {
            csv->ImportCSV(file, ",");
		  }
	   catch (Exception &e)
		  {
			e.Message = "������� ������� �����: " + e.Message;
			throw e;
		  }

	   try
		  {
			ClearResultSet(grid);

			grid->ColCount = 2;
			grid->RowCount = csv->RecordCount + 1;
			grid->FixedRows = 1;

			grid->ColWidths[0] = 300;
			grid->Cells[0][0] = "�������";
			grid->ColWidths[1] = 200;
			grid->Cells[1][0] = "������";
		  }
	   catch (Exception &e)
		  {
			e.Message = "������� ������������ ������� ����������� �����: " + e.Message;
			throw e;
		  }

	   try
		  {
			for (int i = 0; i < csv->RecordCount; i++)
			   {
				 grid->Cells[0][i + 1] = csv->Cells[0][i];
				 grid->Cells[1][i + 1] = csv->Cells[7][i] + ", " + csv->Cells[6][i];
			   }
		  }
	   catch (Exception &e)
		  {
			e.Message = "������� ������ ����� � �������: " + e.Message;
			throw e;
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� ������� ������� ������� � �����: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

TDataHolder* __fastcall TClientForm::ImportDataToHolder(TStringGrid *grid)
{
  TDataHolder *res;

  try
	 {
	   res = new TDataHolder();

	   for (int i = 0; i < grid->RowCount; i++)
		  {
			TStructuredData *row = res->Add();

			for (int j = 0; j < grid->ColCount; j++)
			   row->Add(grid->Cells[j][i]);
		  }
	 }
  catch (Exception &e)
	 {
       res = nullptr;
	   AddActionLog("������� ���������� ����� � TDataHolder: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ExportDataExcel(const String &file, TStringGrid *grid)
{
  try
	 {
	   std::unique_ptr<TDataHolder> holder(ImportDataToHolder(grid));

	   try
		  {
			holder->ExportXLS(file);
		  }
	   catch (Exception &e)
		  {
			e.Message = "������� ������ � ����: " + e.Message;
			throw e;
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� �������� �����: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ExportDataCSV(const String &file, TStringGrid *grid)
{
  try
	 {
	   std::unique_ptr<TDataHolder> holder(ImportDataToHolder(grid));

	   try
		  {
			holder->ExportCSV(file, ";");
		  }
	   catch (Exception &e)
		  {
			e.Message = "������� ������ � ����: " + e.Message;
			throw e;
		  }
	 }
  catch (Exception &e)
	 {
	   AddActionLog("������� �������� �����: " + e.ToString());
	 }
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
	   _di_IXMLNode Document = ixml->DocumentElement; //��� ��������� (�����/�������)

	   if (Document->GetNodeName() == "Answer")
		 {
		   //���������� �������
		   ProcessAnswer(ixml);
		 }
	   else if (Document->GetNodeName() == "Request")
		 {
		   //���������� �����
		   ProcessRequest(ixml);
		 }
	   else
		 {
		   //������� ����� �����
		   throw Exception("�������� ��� XML-���������");
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
	   _di_IXMLNode Document = ixml->DocumentElement; //��� ��������� (�����/�������)
	   _di_IXMLNode Command; //������� (����� ��� ���� ���������� ����)

	   _di_IXMLNode Titles; //������ ��������� ��� ����� ������� ����������
	   _di_IXMLNode Title;

	   _di_IXMLNode Data; //������� ������ � ������
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
			e.Message = "������� ��������� ����� � XML" + e.Message;
			throw e;
		  }

	   String value;
	   int colsize;

	   if (!grid)
		 throw Exception("�� ��������� ������� ���������� �����");

	   try
		  {
			ClearResultSet(grid);
			grid->RowCount = 2;
			grid->ColCount = Titles->ChildNodes->Count;
			grid->FixedRows = 1;

			for (int i = 0; i < Titles->ChildNodes->Count; i++)
			   {
				 Title = Titles->ChildNodes->Nodes[i];
				 colsize = StrToInt(Title->GetAttribute("size"));
				 value = Title->NodeValue;

				 grid->ColWidths[i] = colsize; //������������ ����� ����
				 grid->Cells[i][0] = value; //���������� ������ ����� ������� ������� ����
			   }
		  }
	   catch (Exception &e)
		  {
			e.Message = "������� ������������ ������� ����������� �����" + e.Message;
			throw e;
		  }

	   try
		  {
			grid->RowCount = Data->ChildNodes->Count + 1;
		  }
	   catch (Exception &e)
		  {
			e.Message = "������� ������������ ����� �������: " + e.Message;
			throw e;
		  }

	   try
		  {
			for (int i = 0; i < Data->ChildNodes->Count; i++)
			   {
				 Row = Data->ChildNodes->Nodes[i];

				 for (int j = 0; j < Row->ChildNodes->Count; j++)
					{
					  Field = Row->ChildNodes->Nodes[j];

					  value = Field->NodeValue;
					  //���������� �������, ��������� � 1-�� �����, 0-� �� ���������
					  grid->Cells[j][i + 1] = value;
					}
			   }
		  }
	   catch (Exception &e)
		  {
			e.Message = "������� ������ ����� � �������: " + e.Message;
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
	   _di_IXMLNode Document = ixml->DocumentElement; //��� ��������� (�����/�������)
	   _di_IXMLNode Command; //������� (����� ��� ���� ���������� ����)

	   _di_IXMLNode Titles; //������ ��������� ��� ����� ������� ����������
	   _di_IXMLNode Title;

	   _di_IXMLNode Data; //������� ������ � ������
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
			e.Message = "������� ��������� ����� � XML" + e.Message;
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
	   _di_IXMLNode Document = ixml->DocumentElement; //��� ��������� (�����/�������)
	   _di_IXMLNode Command; //������� (����� ��� ���� ���������� ����)

	   _di_IXMLNode Params; //������� ������ � �������� ���������
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
	   CheckItemsResult->ColWidths[2] = 250;
	   CheckItemsResult->ColWidths[3] = 250;
	   CheckItemsResult->ColWidths[4] = 300;
	   CheckItemsResult->Cells[0][0] = "";
	   CheckItemsResult->Cells[1][0] = "ID";
	   CheckItemsResult->Cells[2][0] = "����������� �����";
	   CheckItemsResult->Cells[3][0] = "������� �����";
	   CheckItemsResult->Cells[4][0] = "������";
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
		 throw Exception("������� ������ � �������");

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
			  throw Exception("����������� ������������ ������");
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
  std::unique_ptr<TFileStream> fs(new TFileStream(AppPath + "\\DownloadedClient.exe",
													   fmOpenWrite|fmCreate|fmShareDenyWrite));

  AContext->Connection->IOHandler->ReadStream(ms.get());

  try
	 {
	   ms->Position = 0;
	   ms->SaveToStream(fs.get());

	   MessageBox(this->Handle,
				  L"����������� ��������� �볺�������� ������. ������������ �������� ��� ���������� ���������",
				  L"����������",
				  MB_OK|MB_ICONINFORMATION);

       NeedUpdate = true;
	 }
  catch (Exception &e)
	 {
	   AddActionLog("Listener: ������� �����: " + e.ToString());
	   NeedUpdate = false;

	   return;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ListenerConnect(TIdContext *AContext)
{
  //�볺�� ��'�������
  AddActionLog("������� ���� � �������");
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ListenerDisconnect(TIdContext *AContext)
{
  //�볺�� ��'�������
  AddActionLog("�������� ����� � ������� ���������");
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
  if (CheckItemScannedCode->Text != "")
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
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemRemoveClick(TObject *Sender)
{
//��������� �������� � ��
  if (CheckItemScannedCode->Text != "")
	{
	  if (MessageBox(this->Handle,
					 L"�� ��������, �� ������ �������� �������?",
					 L"ϳ�����������",
					 MB_YESNO|MB_ICONINFORMATION) == mrYes)
		{
		  RemoveItem(CheckItemScannedCode->Text);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemRefreshClick(TObject *Sender)
{
//��������� ����� �� ��
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
			   AddActionLog("����� ����� ��� �������: " + e.ToString());
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
  if (CheckItemScannedCode->Text != "")
	{
	  MnShowEvents->Click();
	  ShowEventsInn->Text = IntToStr(ItemID);
	  ShowEventsSearchType->ItemIndex = 0;
	  ShowEventsApply->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AddItemCreateClick(TObject *Sender)
{
  //��������� ����� �� ������� �������� � ��
  //����� ���������� ����� ��������� ���. � �� ���� ����� � ��
  IDError->Hide();
  InnError->Hide();
  ModelError->Hide();

  if (AddItemNewID->Text == "")
	{
	  IDError->Caption = "�� ������� ID ��������";
	  IDError->Show();
	}
  else if (AddItemNewInn->Text == "")
	{
	  InnError->Caption = "�� ������� ����������� �����";
	  InnError->Show();
	}
  else if (AddItemNewModel->Text == "")
	{
	  ModelError->Caption = "�� ������� ������";
	  ModelError->Show();
	}
  else if (!CheckItemID(AddItemNewID->Text))
	{
	  IDError->Caption = "������� � ����� ID ��� ����";
	  IDError->Show();
	}
  else if (!IsInnFree(AddItemNewInn->Text))
    {
	  InnError->Caption = "����� ����������� ����� ��� ����";
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
		   IDError->Caption = "������� ID ��������";
		   IDError->Show();
		 }

	  if (AddItemCurrentLocation->Caption != "")
		location_id = AddItemCurrentLocation->Tag;

	  if (AddItem(item_id, AddItemNewInn->Text, AddItemNewSn->Text,
				  AddItemNewModel->Text, location_id, UserID))
		{
		  AddActionLog("������� ������ ������");
		  AddEvent(OP_CREATE_ITM, item_id, UserID);

		  if (location_id > 0)
			AddEvent(OP_ADD_ITM, item_id, UserID);
		}
	  else
		{
		  AddActionLog("�� ������� ������ �������");
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
					 L"����������� �����������?",
					 L"ϳ�����������",
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
					 L"������������ �����������?",
					 L"ϳ�����������",
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
					 L"�������� �������?",
					 L"ϳ�����������",
					 MB_YESNO|MB_ICONINFORMATION) == mrYes)
		{
		  RemoveLocation(id.ToInt());
		  AskLocationList(AdmLocationsResult);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmLocationsImportCSVClick(TObject *Sender)
{
  if (OpenCSVDialog->Execute())
	{
	  ImportLocations(OpenCSVDialog->FileName, ImportLocationPreviewForm->LocationGrid);
      ImportLocationPreviewForm->Show();
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
  CopyRecords(ResultGrid, FilteredGrid);
  CurrentFilter->Text = "";
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
  //���������� ������ �� �������

  if (ShowEventsDateFilter->Checked)
	{
	  AskEventList(ShowEventsSearchType->ItemIndex,
				   ShowEventsInn->Text,
				   DateToStr(ShowEventsDateFrom->Date),
				   DateToStr(ShowEventsDateTo->Date));
	}
  else
	AskEventList(ShowEventsSearchType->ItemIndex, ShowEventsInn->Text, "-", "-");

  CopyRecords(ResultGrid, FilteredGrid);
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
  //����� ������� �������� � �������

  if (ShowItemsCurrentLocation->Caption != "")
	{
	  AskItemList(ShowItemsCurrentLocation->Tag);
      CopyRecords(ResultGrid, FilteredGrid);
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowItemsRequestClick(TObject *Sender)
{
  ShowItemsRefresh->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::ShowItemsRemoveClick(TObject *Sender)
{
  //����� �� ��������� ��������
  String id;

  if (CurrentRowInd > 0)
	id = ShowItemsResult->Cells[0][CurrentRowInd];

  if (id != "")
	{
	  if (MessageBox(this->Handle,
					 L"�� ��������, �� ������ �������� �������?",
					 L"ϳ�����������",
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
  ClearResultSet(ResultGrid);
  CopyRecords(ResultGrid, FilteredGrid);
  PrepareCheckTable();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsEditClick(TObject *Sender)
{
  if (CurrentRowInd > 0)
	{
	  EditItemForm->Show();

	  ItemID = FilteredGrid->Cells[1][CurrentRowInd].ToInt();

	  EditItemForm->Inn->Text = FilteredGrid->Cells[2][CurrentRowInd];
	  EditItemForm->Sn->Text = FilteredGrid->Cells[3][CurrentRowInd];
	  EditItemForm->Model->Text = FilteredGrid->Cells[4][CurrentRowInd];
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
  //����� �� ����������� �������� �� ���'�������� (�� ������� = -1)
  if (CurrentRowInd > 0)
	{
	  if (MessageBox(this->Handle,
					 L"��������� ������� �� ���'��������?",
					 L"ϳ�����������",
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
			   AddActionLog("�� ������� ��������� ������� �� ���'��������");
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
  //��������� �������� �� �������
  CheckError->Hide();

  if (CheckItemsCurrentLocation->Caption == "")
	{
	  CheckError->Caption = "�� ������� �������";
	  CheckError->Show();
	}
  else if (CheckItemsScannedCode->Text == "")
	{
	  CheckError->Caption = "�� ������� ID ��������";
	  CheckError->Show();
	}
  else if (IsItemExistInCheckTable(CheckItemsScannedCode->Text))
	{
	  CheckError->Caption = "�������� ID ��� ��������� � �������";
	  CheckError->Show();
	}
  else
	{
	  CheckItemInLocation(CheckItemsScannedCode->Text,
						  CheckItemsCurrentLocation->Tag,
						  ResultGrid);
	  CopyRecords(ResultGrid, FilteredGrid);

      CheckItemsScannedCode->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsDeleteClick(TObject *Sender)
{
  //�������� ������� � �������
  if (CurrentRowInd > 0)
	{
	  for (int i = CurrentRowInd; i <= FilteredGrid->RowCount - 2; i++)
		 {
		   FilteredGrid->Rows[i]->Assign(FilteredGrid->Rows[i + 1]);
		   ResultGrid->Rows[i]->Assign(ResultGrid->Rows[i + 1]);
		 }

	  ResultGrid->RowCount = ResultGrid->RowCount - 1;
	  FilteredGrid->RowCount = FilteredGrid->RowCount - 1;
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::CheckItemsResultDrawCell(TObject *Sender, int ACol, int ARow,
													  TRect &Rect, TGridDrawState State)
{
  TStringGrid *grid = dynamic_cast<TStringGrid*>(Sender);

  String cell_text = grid->Cells[ACol][ARow];

  Rect.SetLocation(Rect.Location.X - 3, Rect.Location.Y);
  Rect.SetWidth(Rect.Size.Width + 6);

  if (grid->Cells[0][ARow] == "+")
	grid->Canvas->Brush->Color = clGreen;
  else if (grid->Cells[0][ARow] == "-")
	grid->Canvas->Brush->Color = clRed;
  else if (grid->Cells[0][ARow] == "?")
	grid->Canvas->Brush->Color = clYellow;
  else if (grid->Cells[0][ARow] == "*")
	grid->Canvas->Brush->Color = clGray;
  else
	grid->Canvas->Brush->Color = clWindow;

  grid->Canvas->FillRect(Rect);
  grid->Canvas->Font->Color = clBlack;
  grid->Canvas->TextOut(Rect.Left + 2,
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
	{
	  SendQuery(QueryText->Text);
      CopyRecords(ResultGrid, FilteredGrid);
	  CurrentFilter->Text = "";
	}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::QueryTextKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
{
  if (Key == 120)
    Execute->Click();
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmManageExportExcelClick(TObject *Sender)
{
  String old_fltr = SaveCfgDialog->Filter;

  try
	 {
	   SaveCfgDialog->Filter = "����� Excel|*.xlsx";

	   if (SaveCfgDialog->Execute())
		 ExportDataExcel(SaveCfgDialog->FileName, FilteredGrid);
	 }
  __finally {SaveCfgDialog->Filter = old_fltr; SaveCfgDialog->FileName = "";}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::AdmManageExportCSVClick(TObject *Sender)
{
  String old_fltr = SaveCfgDialog->Filter;

  try
	 {
	   SaveCfgDialog->Filter = "����� CSV|*.csv";

	   if (SaveCfgDialog->Execute())
		 ExportDataCSV(SaveCfgDialog->FileName, FilteredGrid);
	 }
  __finally {SaveCfgDialog->Filter = old_fltr; SaveCfgDialog->FileName = "";}
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::SaveSessionLogClick(TObject *Sender)
{
  SaveCfgDialog->InitialDir = AppPath;

  if (SaveCfgDialog->Execute())
	ActionLog->Lines->SaveToFile(SaveCfgDialog->FileName);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::UpdateClientClick(TObject *Sender)
{
  SendToServer(Server, CreateRequest("DOWNLOADMODULE"));
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::FilterChange(TObject *Sender)
{
  if (CurrentFilter->Text == "")
	CopyRecords(ResultGrid, FilteredGrid);
  else
	FilterTable(ResultGrid, FilteredGrid, CurrentColInd, CurrentFilter->Text);
}
//---------------------------------------------------------------------------

void __fastcall TClientForm::FilteredGridMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
  FilteredGrid->MouseToCell(X, Y, CurrentColInd, CurrentRowInd);

  if (CurrentColInd >= 0)
	CurrentFilterLabel->Caption = FilteredGrid->Cells[CurrentColInd][0];
}
//---------------------------------------------------------------------------
