//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Client.h"
#include "ChangeMail.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChangeMailForm *ChangeMailForm;

extern int UserID;
//---------------------------------------------------------------------------
__fastcall TChangeMailForm::TChangeMailForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TChangeMailForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;

  PasswordError->Hide();
  EMailError->Hide();

  Password->Text = "";
  EMail->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TChangeMailForm::ApplyClick(TObject *Sender)
{
  if (EMail->Text == "")
	{
	  EMailError->Caption = "Не вказано адресу ел. пошти";
	  EMailError->Show();
	}
  else if (!EMail->Text.Pos("@"))
	{
	  EMailError->Caption = "Невірний формат адреси ел. пошти";
	  EMailError->Show();
	}
  else if (Password->Text == "")
	{
	  PasswordError->Caption = "Не вказано пароль";
	  PasswordError->Show();
	}
  else if (!ClientForm->ValidUserPassword(UserID, Password->Text))
    {
	  PasswordError->Caption = "Невірний пароль";
	  PasswordError->Show();
	}
  else
	{
	  if (ClientForm->SetUserMail(UserID, EMail->Text))
		{
		  ClientForm->CurrentMail->Caption = EMail->Text;
		  MessageBox(this->Handle, L"Адресу ел. пошти успішно змінено", L"Успіх", MB_OK|MB_ICONINFORMATION);
		}
	  else
		MessageBox(this->Handle, L"Не вдалося змінити адресу ел. пошти", L"Помилка", MB_OK|MB_ICONERROR);

      Close();
    }
}
//---------------------------------------------------------------------------

void __fastcall TChangeMailForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
