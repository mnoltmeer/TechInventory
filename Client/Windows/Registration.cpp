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
	   //тут коннект до серверу, передача йому зашифрованих логіну та паролю
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
				ClientForm->AddActionLog("IsLoginFree: Парсинг: " + e.ToString());
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
												const String &mail,
												bool admin)
{
  bool res;

  try
	 {
	   //тут коннект до серверу, передача йому зашифрованих логіну та паролю
	   String hash_pwd;

	   hash_pwd = MD5(pass);
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("REGISTER",
																	 login + ";" +
																	 hash_pwd + ";" +
																	 mail + ";" +
																	 (unsigned int)admin));

	   if (!ClientForm->AskToServer(Server, data.get()))
		 res = false;
	   else
		 {
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   try
			  {
				_di_IXMLNode Document = ixml->DocumentElement;
				_di_IXMLNode Command = Document->ChildNodes->Nodes[0];

				if (Command->NodeValue == "SUCCESS")
				  res = true;
				else
				  res = false;
			  }
		   catch (Exception &e)
			  {
				res = false;
				ClientForm->AddActionLog("Registration: Парсинг: " + e.ToString());
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

bool __fastcall TRegistrationForm::SendVerificationCode(const String &mail)
{
  bool res;

  Sleep(200);

  try
	 {
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("VERIFY", mail));

	   if (!ClientForm->AskToServer(Server, data.get()))
		 res = false;
	   else
		 {
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   try
			  {
				_di_IXMLNode Document = ixml->DocumentElement;
				_di_IXMLNode Command = Document->ChildNodes->Nodes[0];

				if (Command->NodeValue == "ERROR")
				  res = false;
				else
				  VerifCode = Command->NodeValue;
			  }
		   catch (Exception &e)
			  {
				res = false;
				ClientForm->AddActionLog("SendVerificationCode: Парсинг: " + e.ToString());
			  }
		 }
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
	  LoginError->Caption = "Не вказано логін";
	  LoginError->Show();
	}
  else if (Password->Text == "")
	{
	  PasswordError->Caption = "Не вказано пароль";
	  PasswordError->Show();
	}
  else if (ConfirmPassword->Text == "")
	{
	  ConfirmPasswordError->Caption = "Не вказане підтвердження паролю";
	  ConfirmPasswordError->Show();
	}
  else if (Password->Text != ConfirmPassword->Text)
	{
	  PasswordError->Caption = "Пароль та його підтвердження не збігаються";
	  PasswordError->Show();
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
  else if (!IsLoginFree(Login->Text))
	{
	  LoginError->Caption = "Логін вже зареєстровано";
	  LoginError->Show();
	}
  else if (!SendVerificationCode(EMail->Text))
	{
	  RegistrationResult->Caption = "Код верифікації не надіслано. Зверніться до адміністратора серверу";
	  RegistrationResult->Font->Color = clRed;
      RegistrationResult->Show();
	}
  else
	{
	  RegistrationResult->Caption = "На вашу ел. пошту надіслано код верифікації, введіть його у полі нижче";
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
	  RegistrationResult->Caption = "Введений код верифікації не є вірним";
	  RegistrationResult->Font->Color = clRed;
	}
  else
	{
	  if (Registration(Login->Text, Password->Text, EMail->Text, false))
		{
		  LoginForm->UserName->Text = Login->Text;
		  LoginForm->Password->Text = Password->Text;
		  LoginForm->StartAuth->Click();
		  RegistrationResult->Caption = "Успішна реєстрація. Натисніть Вихід для початку роботи";
		  RegistrationResult->Font->Color = clGreen;
          VerifCode = "";
		}
	  else
		{
		  RegistrationResult->Caption = "Не вдалось зареєструвати користувача";
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

