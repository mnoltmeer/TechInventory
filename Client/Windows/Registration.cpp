/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\..\work-functions\MyFunc.h"
#include "Client.h"
#include "Login.h"
#include "Registration.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRegistrationForm *RegistrationForm;

String VerifCode;

extern String Server;
//---------------------------------------------------------------------------
__fastcall TRegistrationForm::TRegistrationForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;

  VerificationCode->Hide();
  Confirm->Hide();
  RegistrationResult->Hide();
  LoginError->Hide();
  PasswordError->Hide();
  ConfirmPasswordError->Hide();
  EMailError->Hide();

  Login->Text = "";
  Password->Text = "";
  ConfirmPassword->Text = "";
  EMail->Text = "";
  VerificationCode->Text = "";
}
//---------------------------------------------------------------------------

bool __fastcall TRegistrationForm::IsLoginFree(const String &login)
{
  bool res;

  try
	 {
	   //��� ������� �� �������, �������� ���� ������������ ����� �� ������
       std::unique_ptr<TXMLDocument> ixml;

	   if (ClientForm->SendRequest("CHECKLOGIN", login, ixml) == "FREE")
		 res = true;
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   ClientForm->AddActionLog("IsLoginFree: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TRegistrationForm::Registration(const String &login,
												const String &pass,
												const String &mail,
												bool admin)
{
  bool res;

  try
	 {
	   //��� ������� �� �������, �������� ���� ������������ ����� �� ������
	   String hash_pwd;

	   hash_pwd = MD5(pass);
       std::unique_ptr<TXMLDocument> ixml;

	   if (ClientForm->SendRequest("REGISTER", login + ";" +
											   hash_pwd + ";" +
											   mail + ";" +
											   (unsigned int)admin, ixml) == "SUCCESS")
		 {
		   res = true;
		 }
	   else
		 res = false;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   ClientForm->AddActionLog("Registration: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

bool __fastcall TRegistrationForm::SendVerificationCode(const String &mail)
{
  bool res;

  Sleep(200);

  try
	 {
       std::unique_ptr<TXMLDocument> ixml;

	   VerifCode = ClientForm->SendRequest("VERIFY", mail, ixml);

	   if (VerifCode == "ERROR")
		 res = false;
	   else
		 res = true;
	 }
  catch (Exception &e)
	 {
	   res = false;
	   ClientForm->AddActionLog("SendVerificationCode: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::SendCodeClick(TObject *Sender)
{
  VerificationCode->Hide();
  Confirm->Hide();
  RegistrationResult->Hide();
  LoginError->Hide();
  PasswordError->Hide();
  ConfirmPasswordError->Hide();
  EMailError->Hide();

  if (Login->Text == "")
	{
	  RegistrationResult->Caption = "�� ������� ����";
      RegistrationResult->Font->Color = clRed;
	  RegistrationResult->Show();
	}
  else if (Password->Text == "")
	{
	  RegistrationResult->Caption = "�� ������� ������";
	  RegistrationResult->Font->Color = clRed;
	  RegistrationResult->Show();
	}
  else if (ConfirmPassword->Text == "")
	{
	  RegistrationResult->Caption = "�� ������� ������������ ������";
	  RegistrationResult->Font->Color = clRed;
	  RegistrationResult->Show();
	}
  else if (Password->Text != ConfirmPassword->Text)
	{
	  RegistrationResult->Caption = "������ �� ���� ������������ �� ���������";
	  RegistrationResult->Show();
	}
  else if (!ClientForm->IsValidPassword(Password->Text))
	{
	  RegistrationResult->Caption = "������ �� ������� ��������.\r\n\
������� ������ �� ���� �� ����� �� 8 �������.\r\n\
������������ �������� ����� ��������� �� ��������\r\n�������, \
����� �� ������� '!', '@', '#', '$', '%', '^', '&', '*', '-', '_'";
	  RegistrationResult->Font->Color = clRed;
	  RegistrationResult->Show();
	}
  else if (EMail->Text == "")
	{
	  RegistrationResult->Caption = "�� ������� ������ ��. �����";
	  RegistrationResult->Font->Color = clRed;
	  RegistrationResult->Show();
	}
  else if (!EMail->Text.Pos("@"))
	{
	  RegistrationResult->Caption = "������� ������ ������ ��. �����";
	  RegistrationResult->Font->Color = clRed;
	  RegistrationResult->Show();
	}
  else if (!IsLoginFree(Login->Text))
	{
	  RegistrationResult->Caption = "���� ��� ������������";
	  RegistrationResult->Font->Color = clRed;
	  RegistrationResult->Show();
	}
  else if (!SendVerificationCode(EMail->Text))
	{
	  RegistrationResult->Caption = "��� ����������� �� ��������. ��������� �� ������������ �������";
	  RegistrationResult->Font->Color = clRed;
	  RegistrationResult->Show();
	}
  else
	{
	  RegistrationResult->Caption = "�� ���� ��. ����� �������� ��� �����������, ������ ���� � ��� �����";
	  RegistrationResult->Font->Color = clBlue;
	  RegistrationResult->Show();
	  VerificationCode->Show();
	  Confirm->Show();
    }
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::ExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::ConfirmClick(TObject *Sender)
{
  if (VerificationCode->Text != VerifCode)
	{
	  RegistrationResult->Caption = "�������� ��� ����������� �� � �����";
	  RegistrationResult->Font->Color = clRed;
	}
  else
	{
	  if (Registration(Login->Text, Password->Text, EMail->Text, false))
		{
		  LoginForm->UserName->Text = Login->Text;
		  LoginForm->Password->Text = Password->Text;
		  LoginForm->StartAuth->Click();
		  RegistrationResult->Caption = "������ ���������. �������� ����� ��� ������� ������";
		  RegistrationResult->Font->Color = clGreen;
          VerifCode = "";
		}
	  else
		{
		  RegistrationResult->Caption = "�� ������� ������������ �����������";
		  RegistrationResult->Font->Color = clRed;
          VerifCode = "";
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::VerificationCodeKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
    Confirm->Click();
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::LoginKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	SendCode->Click();
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::PasswordKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	SendCode->Click();
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::ConfirmPasswordKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	SendCode->Click();
}
//---------------------------------------------------------------------------

void __fastcall TRegistrationForm::EMailKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	SendCode->Click();
}
//---------------------------------------------------------------------------

