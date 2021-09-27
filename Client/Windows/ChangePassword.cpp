/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Client.h"
#include "ChangePassword.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChangePasswordForm *ChangePasswordForm;

extern int UserID;
//---------------------------------------------------------------------------
__fastcall TChangePasswordForm::TChangePasswordForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TChangePasswordForm::ApplyClick(TObject *Sender)
{
  if (OldPassword->Text == "")
	MessageBox(this->Handle, L"Не вказано старий пароль", L"Помилка", MB_OK|MB_ICONERROR);
  else if (Password->Text == "")
	MessageBox(this->Handle, L"Не вказано пароль", L"Помилка", MB_OK|MB_ICONERROR);
  else if (ConfirmPassword->Text == "")
	MessageBox(this->Handle, L"Не вказане підтвердження паролю", L"Помилка", MB_OK|MB_ICONERROR);
  else if (Password->Text != ConfirmPassword->Text)
	MessageBox(this->Handle, L"Пароль та його підтвердження не збігаються", L"Помилка", MB_OK|MB_ICONERROR);
  else if (!ClientForm->ValidUserPassword(UserID, OldPassword->Text))
    MessageBox(this->Handle, L"Невірно вказано старий пароль", L"Помилка", MB_OK|MB_ICONERROR);
  else if (!ClientForm->IsValidPassword(Password->Text))
	MessageBox(this->Handle, L"Пароль не відповідає правилам. Довжина паролю має бути не менше ніж 8 символів. Допускаються латинські літери верхнього та нижнього регістру, цифри та символи '!', '@', '#', '$', '%', '^', '&', '*', '-', '_'", L"Помилка", MB_OK|MB_ICONERROR);
  else
	{
	  if (ClientForm->SetUserPassword(UserID, Password->Text))
		{
		  MessageBox(this->Handle, L"Пароль успішно змінено", L"Успіх", MB_OK|MB_ICONINFORMATION);
          Close();
		}
	  else
		MessageBox(this->Handle, L"Не вдалось змінити пароль", L"Помилка", MB_OK|MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;
  OldPassword->Text = "";
  Password->Text = "";
  ConfirmPassword->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordForm::OldPasswordKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	Apply->Click();
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordForm::PasswordKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	Apply->Click();
}
//---------------------------------------------------------------------------

void __fastcall TChangePasswordForm::ConfirmPasswordKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	Apply->Click();
}
//---------------------------------------------------------------------------

