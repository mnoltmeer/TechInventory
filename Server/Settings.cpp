/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\work-functions\MyFunc.h"
#include "Main.h"
#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSettingsForm *SettingsForm;

extern int ListenPort, MailPort;
extern String DBHost, DBPath, DBPort, ServerName, MailServer, SenderName;
//---------------------------------------------------------------------------
__fastcall TSettingsForm::TSettingsForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::FormShow(TObject *Sender)
{
  Left = ServerForm->Left + ServerForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ServerForm->Top + ServerForm->ClientHeight / 2 - ClientHeight / 2;

  ServicePort->SetFocus();

  ReadSettings();
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::ReadSettings()
{
  try
	 {
	   std::unique_ptr<TRegistry> reg(new TRegistry(KEY_READ));

	   reg->RootKey = HKEY_CURRENT_USER;

	   if (reg->OpenKey("Software\\TechInventServer\\Form", false))
		 {
		   if (reg->ValueExists("HideWindow"))
			 StartMinimised->Checked = reg->ReadBool("HideWindow");

		   reg->CloseKey();
		 }

	   ServicePort->Text = IntToStr(ListenPort);
	   Server->Text = ServerName;
	   Host->Text = DBHost;
	   Port->Text = DBPort;
	   Database->Text = DBPath;
       SMTPServer->Text = MailServer;
	   SMTPPort->Text = IntToStr(MailPort);
	   SenderLabel->Text = SenderName;

	   EnableAutoStart->Checked = CheckAppAutoStart("TechInventServer", FOR_CURRENT_USER);
	 }
  catch (Exception &e)
	 {
	   ServerForm->WriteLog("SettingsForm::ReadSettings: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::WriteSettings()
{
  try
	 {
	   std::unique_ptr<TRegistry> reg(new TRegistry(KEY_WRITE));

	   reg->RootKey = HKEY_CURRENT_USER;

	   if (!reg->KeyExists("Software\\TIServer\\Form"))
		 reg->CreateKey("Software\\TIServer\\Form");

	   if (reg->OpenKey("Software\\TIServer\\Form", false))
		 {
		   reg->WriteBool("HideWindow", StartMinimised->Checked);
		   reg->CloseKey();
		 }

	   ListenPort = ServicePort->Text.ToInt();
	   ServerName = Server->Text;
	   DBHost = Host->Text;
	   DBPort = Port->Text;
	   DBPath = Database->Text;
	   MailServer = SMTPServer->Text;
	   MailPort = SMTPPort->Text.ToInt();
	   SenderName = SenderLabel->Text;

	   if (EnableAutoStart->Checked)
		 AddAppAutoStart("TIServer", Application->ExeName, FOR_CURRENT_USER);
	   else
		 RemoveAppAutoStart("TIServer", FOR_CURRENT_USER);
	 }
  catch (Exception &e)
	 {
	   ServerForm->WriteLog("SettingsForm::WriteSettings: " + e.ToString());
	 }
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TSettingsForm::ApplyClick(TObject *Sender)
{
  WriteSettings();
  ServerForm->WriteSettings();
  Close();
}
//---------------------------------------------------------------------------

