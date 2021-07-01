//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Client.h"
#include "ChangePassword.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPasswordChangeForm *PasswordChangeForm;

extern String User;
//---------------------------------------------------------------------------
__fastcall TPasswordChangeForm::TPasswordChangeForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPasswordChangeForm::ApplyClick(TObject *Sender)
{
  if (OldPassword->Text == "")
	MessageBox(this->Handle, L"Не вказано старий пароль", L"Помилка", MB_OK|MB_ICONERROR);
  else if (Password->Text == "")
	MessageBox(this->Handle, L"Не вказано пароль", L"Помилка", MB_OK|MB_ICONERROR);
  else if (ConfirmPassword->Text == "")
	MessageBox(this->Handle, L"Не вказане підтвердження паролю", L"Помилка", MB_OK|MB_ICONERROR);
  else if (Password->Text != ConfirmPassword->Text)
	MessageBox(this->Handle, L"Пароль та його підтвердження не збігаються", L"Помилка", MB_OK|MB_ICONERROR);
  else
	{
	  if (ClientForm->SetUserPassword(User, Password->Text))
		{
		  MessageBox(this->Handle, L"Пароль успішно змінено", L"Успіх", MB_OK|MB_ICONINFORMATION);
          Close();
		}
	  else
		MessageBox(this->Handle, L"Не вдалось змінити пароль", L"Помилка", MB_OK|MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------

void __fastcall TPasswordChangeForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TPasswordChangeForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;
}
//---------------------------------------------------------------------------

