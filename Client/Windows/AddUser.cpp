/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Client.h"
#include "Registration.h"
#include "AddUser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAddUserForm *AddUserForm;
//---------------------------------------------------------------------------
__fastcall TAddUserForm::TAddUserForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TAddUserForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;

  RegistrationResult->Hide();
  LoginError->Hide();
  PasswordError->Hide();
  ConfirmPasswordError->Hide();
  EMailError->Hide();

  Login->Text = "";
  Password->Text = "";
  ConfirmPassword->Text = "";
  EMail->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TAddUserForm::CreateClick(TObject *Sender)
{
  RegistrationResult->Hide();
  LoginError->Hide();
  PasswordError->Hide();
  ConfirmPasswordError->Hide();
  EMailError->Hide();

  if (Login->Text == "")
	{
	  LoginError->Caption = "�� ������� ����";
	  LoginError->Show();
	}
  else if (Password->Text == "")
	{
	  PasswordError->Caption = "�� ������� ������";
	  PasswordError->Show();
	}
  else if (ConfirmPassword->Text == "")
	{
	  ConfirmPasswordError->Caption = "�� ������� ������������ ������";
	  ConfirmPasswordError->Show();
	}
  else if (Password->Text != ConfirmPassword->Text)
	{
	  PasswordError->Caption = "������ �� ���� ������������ �� ���������";
	  PasswordError->Show();
	}
  else if (EMail->Text == "")
	{
	  EMailError->Caption = "�� ������� ������ ��. �����";
	  EMailError->Show();
	}
  else if (!EMail->Text.Pos("@"))
	{
	  EMailError->Caption = "������� ������ ������ ��. �����";
	  EMailError->Show();
	}
  else if (!RegistrationForm->IsLoginFree(Login->Text))
	{
	  LoginError->Caption = "���� ��� ������������";
	  LoginError->Show();
	}
  else
	{
	  bool role = UserRole->ItemIndex;

	  if (RegistrationForm->Registration(Login->Text, Password->Text, EMail->Text, !role))
		Close();
	  else
		{
          RegistrationResult->Show();
		  RegistrationResult->Caption = "�� ������� ������������ �����������";
		  RegistrationResult->Font->Color = clRed;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TAddUserForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
