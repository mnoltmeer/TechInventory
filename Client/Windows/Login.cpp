/*!
Copyright 2020 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\..\work-functions\MyFunc.h"
#include "Client.h"
#include "Login.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TLoginForm *LoginForm;

extern ENCRYPTTEXT EncryptText;
extern DECRYPTTEXT DecryptText;

extern String LogPath;
extern const char *AccCryptKey;
extern const char *DataCryptKey;
extern String AppPath;
extern String Server, User;
extern int UserID;
extern bool IsAdmin;
extern int MainFormWidth, MainFormHeight;
extern bool MainFormFullScreen;
extern String Server, User; //поточний сервер та логін користувача
extern String AppPath;
extern TClientForm *ClientForm;
//---------------------------------------------------------------------------
__fastcall TLoginForm::TLoginForm(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::StartAuthClick(TObject *Sender)
{
  //спроба входу
  AuthResult res = Authorisation(ServerName->Text, UserName->Text, Password->Text);

  switch (res)
	{
	  case AuthOK:
		{
		  ClientForm->UnlockUI();
		  Close();
		  break;
        }
	  case InvalidAcc: AuthError->Caption = "Вказані невірні облікові дані"; break;
	  case ConnectErr: AuthError->Caption = "Помилка з'єднання"; break;
      case UnknownErr: AuthError->Caption = "Невідома помилка. Дивись лог"; break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::RegNewUserClick(TObject *Sender)
{
  //відкриття форми реєстрації
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
	   String crypt_login, crypt_pwd;
	   Server = ServerName->Text;
	   User = UserName->Text;

	   crypt_pwd = EncryptText(Password->Text.c_str(), AccCryptKey);

	   TStringStream *data = ClientForm->CreateRequest("AUTH", User + ";" + crypt_pwd);

	   try
		  {
			if (ClientForm->AskToServer(Server.c_str(), data) < 0)
			  res = ConnectErr;
			else
			  {
				TXMLDocument *ixml = ClientForm->CreatXMLStream(data);

				try
				   {
					 try
						{
						  _di_IXMLNode Document = ixml->DocumentElement;
						  _di_IXMLNode Command;
						  _di_IXMLNode Data;
						  _di_IXMLNode Row;
						  _di_IXMLNode Field_1, Field_2;

						  Command = Document->ChildNodes->Nodes[0];
						  Data = Document->ChildNodes->Nodes[2];
						  Row = Data->ChildNodes->Nodes[0];
						  Field_1 = Row->ChildNodes->Nodes[0];
						  Field_2 = Row->ChildNodes->Nodes[1];

						  if (Command->NodeValue == "GRANTED")
							{
							  UserID = StrToInt(Field_1->NodeValue);

							  if (Field_1->NodeValue == "admin")
								IsAdmin = true;
							  else
								IsAdmin = false;

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
						  SaveLog(LogPath + "\\TIClient_exceptions.log",
						  		  "Authorisation: Парсинг: " + e.ToString());
						}
				   }
				__finally {delete ixml;}
			  }
		  }
	   __finally {delete data;}
	 }
  catch (Exception &e)
	 {
	   res = UnknownErr;
	   SaveLog(LogPath + "\\TIClient_exceptions.log", "Authorisation: " + e.ToString());
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::FormShow(TObject *Sender)
{
  Left = ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->ClientHeight / 2 - ClientHeight / 2;
  ClientForm->LockUI();
  ServerName->Text = Server;
  UserName->Text = User;
}
//---------------------------------------------------------------------------

