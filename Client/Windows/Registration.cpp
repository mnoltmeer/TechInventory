//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\..\work-functions\MyFunc.h"
#include "Client.h"
#include "Registration.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRegistrationForm *RegistrationForm;

extern String Server;
extern TClientForm *ClientForm;
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
}
//---------------------------------------------------------------------------

bool __fastcall TRegistrationForm::IsLoginFree(const String &login)
{
  bool res;

  try
	 {
	   //��� ������� �� �������, �������� ���� ������������ ����� �� ������
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("CHECKLOGIN", login));

	   if (!ClientForm->AskToServer(Server, data.get()))
		 res = false;
	   else
		 {
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   try
			  {
				_di_IXMLNode Document = ixml->DocumentElement;
				_di_IXMLNode Command;

				Command = Document->ChildNodes->Nodes[0];

				if (Command->NodeValue == "FREE")
				  res = true;
				else
				  res = false;
			  }
		   catch (Exception &e)
			  {
				res = false;
				ClientForm->AddActionLog("IsLoginFree: �������: " + e.ToString());
			  }
		 }
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
										 		const String &mail)
{
  bool res;

  try
	 {
	   //��� ������� �� �������, �������� ���� ������������ ����� �� ������
	   String hash_pwd;

	   hash_pwd = MD5(pass);
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("REGISTER",
																	 login + ";" +
																	 hash_pwd + ";" +
																	 mail));

	   if (!ClientForm->AskToServer(Server, data.get()))
		 res = false;
	   else
		 {
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   try
			  {
				_di_IXMLNode Document = ixml->DocumentElement;
				_di_IXMLNode Command;

				Command = Document->ChildNodes->Nodes[0];

				if (Command->NodeValue == "SUCCSESS")
				  res = true;
				else
				  res = false;
			  }
		   catch (Exception &e)
			  {
				res = false;
				ClientForm->AddActionLog("Registration: �������: " + e.ToString());
			  }
		 }
	 }
  catch (Exception &e)
	 {
	   res = false;
	   ClientForm->AddActionLog("Registration: " + e.ToString());
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
	  EMailError->Caption = "�� ����� ������ ������ ��. �����";
	  EMailError->Show();
	}
  else if (!IsLoginFree(Login->Text))
	{
	  LoginError->Caption = "���� ��� ������������";
	  LoginError->Show();
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

