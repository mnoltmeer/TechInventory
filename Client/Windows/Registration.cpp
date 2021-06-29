//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

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

bool __fastcall TLoginForm::IsLoginFree(const String &login)
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
				Data = Document->ChildNodes->Nodes[2];

				if (Command->NodeValue == "FREE")
				  res = true;
				else
				  res = false;
			  }
		   catch (Exception &e)
			  {
				res = ConnectErr;
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

bool __fastcall TLoginForm::Registration(const String &login,
										 const String &pass,
										 const String &mail)
{
  bool res;

  try
	 {
	   //тут коннект до серверу, передача йому зашифрованих логіну та паролю
	   String hash_pwd;
	   Server = ServerName->Text;
	   User = UserName->Text;

	   hash_pwd = MD5(Password->Text);
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("AUTH", User + ";" + hash_pwd));

	   if (!ClientForm->AskToServer(Server, data.get()))
		 res = ConnectErr;
	   else
		 {
		   data->Position = 0;
		   ClientForm->AddActionLog(data->ReadString(data->Size));
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   try
			  {
				_di_IXMLNode Document = ixml->DocumentElement;
				_di_IXMLNode Command;
				_di_IXMLNode Data;
				_di_IXMLNode Row1, Row2, Row3;
				_di_IXMLNode ID, Role, Mail;

				Command = Document->ChildNodes->Nodes[0];
				Data = Document->ChildNodes->Nodes[2];

				if (Command->NodeValue == "GRANTED")
				  {
					Row1 = Data->ChildNodes->Nodes[0];
					Row2 = Data->ChildNodes->Nodes[1];
                    Row3 = Data->ChildNodes->Nodes[2];
					ID = Row1->ChildNodes->Nodes[0];
					Role = Row2->ChildNodes->Nodes[0];
					Mail = Row3->ChildNodes->Nodes[0];

					UserID = ID->NodeValue.AsType(3);

					if (UpperCase(Role->NodeValue) == "ADMIN")
					  IsAdmin = true;
					else
					  IsAdmin = false;

					ClientForm->CurrentMail->Caption = Mail->NodeValue;

					res = AuthOK;
				  }
				else
				  {
					res = InvalidAcc;
				  }
			  }
		   catch (Exception &e)
			  {
				res = ConnectErr;
				ClientForm->AddActionLog("Authorisation: Парсинг: " + e.ToString());
			  }
		 }
	 }
  catch (Exception &e)
	 {
	   res = UnknownErr;
	   ClientForm->AddActionLog("Authorisation: " + e.ToString());
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
	  EMailError->Caption = "Не вірний формат адреси ел. пошти";
	  EMailError->Show();
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

