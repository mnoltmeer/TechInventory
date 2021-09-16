/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\..\work-functions\MyFunc.h"
#include "Client.h"
#include "Registration.h"
#include "Login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoginForm *LoginForm;

extern String LogPath;
extern const char *AccCryptKey;
extern const char *DataCryptKey;
extern String AppPath;
extern int UserID;
extern bool IsAdmin;
extern bool IsLocked;
extern int MainFormWidth, MainFormHeight;
extern bool MainFormFullScreen;
extern String Server, User; //поточний сервер та логін користувача
extern String AppPath;
//---------------------------------------------------------------------------
__fastcall TLoginForm::TLoginForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;
  ClientForm->LockUI();
  ServerName->Text = Server;
  UserName->Text = User;
  Password->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::StartAuthClick(TObject *Sender)
{
  AuthError->Hide();

  //спроба входу
  AuthResult res = Authorisation(ServerName->Text, UserName->Text, Password->Text);

  switch (res)
	{
	  case AuthOK:
		{
		  Server = ServerName->Text;
		  User = UserName->Text;
		  ClientForm->UserInfo->Caption = "Користувач: " + User;

		  if (IsLocked)
			ClientForm->UnlockUILimited();
		  else
			ClientForm->UnlockUI();

		  ClientForm->GetServerVersion();
		  Close();
		  break;
		}
	  case InvalidAcc:
		{
		  ClientForm->LockUI();
		  ShowAuthError("Вказані невірні облікові дані");
		  break;
		}
	  case ConnectErr:
		{
		  ClientForm->LockUI();
		  ShowAuthError("Помилка з'єднання");
		  break;
		}
	  case UnknownErr:
		{
		  ClientForm->LockUI();
		  ShowAuthError("Невідома помилка. Дивись лог");
		  break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::RegNewUserClick(TObject *Sender)
{
  //відкриття форми реєстрації
  if (ServerName->Text == "")
	ShowAuthError("Вказані невірні облікові дані");
  else
	{
      Server = ServerName->Text;
	  RegistrationForm->Show();
  	  Hide();
	}
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::ForgotPasswordClick(TObject *Sender)
{
  //відкриття форми відновлення паролю
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::UserNameKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	StartAuth->Click();
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::PasswordKeyPress(TObject *Sender, System::WideChar &Key)

{
  if (Key == 13)
	StartAuth->Click();
}
//---------------------------------------------------------------------------

AuthResult __fastcall TLoginForm::Authorisation(const String &server,
												const String &user,
												const String &password)
{
  AuthResult res;

  try
	 {
	   //тут коннект до серверу, передача йому зашифрованих логіну та паролю
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("AUTH", user + ";" + MD5(password)));

	   if (!ClientForm->AskToServer(server, data.get()))
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
				Command = Document->ChildNodes->Nodes[0];

				if (Command->NodeValue == "GRANTED")
				  {
					_di_IXMLNode Data;
					_di_IXMLNode Row;
					_di_IXMLNode ID, Role, Mail, Locked;

					Data = Document->ChildNodes->Nodes[2];
					Row = Data->ChildNodes->Nodes[0];
					ID = Row->ChildNodes->Nodes[0];
					Role = Row->ChildNodes->Nodes[1];
					Mail = Row->ChildNodes->Nodes[2];
					Locked = Row->ChildNodes->Nodes[3];

					UserID = ID->NodeValue.AsType(3);
					IsLocked = StrToBool(Locked->NodeValue);

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

void __fastcall TLoginForm::ShowAuthError(const String &error)
{
  AuthError->Show();
  AuthError->Caption = error;
  AuthError->Left = ClientWidth / 2 - AuthError->Width / 2;
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::CancelClick(TObject *Sender)
{
  ClientForm->Close();
}
//---------------------------------------------------------------------------

