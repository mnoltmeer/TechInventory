//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Client.h"
#include "RestorePassword.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRestorePasswordForm *RestorePasswordForm;
//---------------------------------------------------------------------------
__fastcall TRestorePasswordForm::TRestorePasswordForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TRestorePasswordForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;
  Login->Text = "";
  EMail->Text = "";
  LoginError->Hide();
  EMailError->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TRestorePasswordForm::ApplyClick(TObject *Sender)
{
  LoginError->Hide();
  EMailError->Hide();
  std::unique_ptr<TXMLDocument> ixml;

  if (Login->Text == "")
	{
	  LoginError->Caption = "Не вказано логін";
	  LoginError->Show();
	}
  else if (ClientForm->SendRequest("CHECKLOGIN", Login->Text, ixml) == "FREE")
	{
	  LoginError->Caption = "Логін відсутній у системі";
	  LoginError->Show();
	}
  else if (EMail->Text == "")
	{
	  EMailError->Caption = "Не вказано адресу ел. пошти";
	  EMailError->Show();
	}
  else if (!EMail->Text.Pos("@"))
	{
	  EMailError->Caption = "Невірний формат адреси ел. пошти";
	  EMailError->Show();
	}
  else if (!ClientForm->RestorePassword(Login->Text, EMail->Text))
	MessageBox(this->Handle, L"Не вдалось скинути пароль", L"Помилка", MB_OK|MB_ICONERROR);
  else
	{
      MessageBox(this->Handle, L"Пароль успішно скинуто і відправлено на адресу ел. пошти. Перевірте поштову скриньку", L"Успіх", MB_OK|MB_ICONINFORMATION);
	  Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TRestorePasswordForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TRestorePasswordForm::LoginKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	Apply->Click();
}
//---------------------------------------------------------------------------

void __fastcall TRestorePasswordForm::EMailKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	Apply->Click();
}
//---------------------------------------------------------------------------
