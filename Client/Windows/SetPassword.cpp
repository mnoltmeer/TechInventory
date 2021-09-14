/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Client.h"
#include "SetPassword.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSetPasswordForm *SetPasswordForm;
//---------------------------------------------------------------------------
__fastcall TSetPasswordForm::TSetPasswordForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSetPasswordForm::ApplyClick(TObject *Sender)
{
  if (Password->Text == "")
	MessageBox(this->Handle, L"�� ������� ������", L"�������", MB_OK|MB_ICONERROR);
  else if (ConfirmPassword->Text == "")
	MessageBox(this->Handle, L"�� ������� ������������ ������", L"�������", MB_OK|MB_ICONERROR);
  else if (Password->Text != ConfirmPassword->Text)
	MessageBox(this->Handle, L"������ �� ���� ������������ �� ���������", L"�������", MB_OK|MB_ICONERROR);
  else
	{
	  if (ClientForm->SetUserPassword(UserID, Password->Text))
		{
		  MessageBox(this->Handle, L"������ ������ ������", L"����", MB_OK|MB_ICONINFORMATION);
		  Close();
		}
	  else
		MessageBox(this->Handle, L"�� ������� ������ ������", L"�������", MB_OK|MB_ICONERROR);
	}
}
//---------------------------------------------------------------------------

void __fastcall TSetPasswordForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TSetPasswordForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;
  Password->Text = "";
  ConfirmPassword->Text = "";
}
//---------------------------------------------------------------------------
