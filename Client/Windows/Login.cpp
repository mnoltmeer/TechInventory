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

extern String LogPath;
extern const char *AccCryptKey;
extern const char *DataCryptKey;
extern String AppPath;
extern String Server, User;
extern int UserID;
extern bool IsAdmin;
extern int MainFormWidth, MainFormHeight;
extern bool MainFormFullScreen;
extern String Server, User; //�������� ������ �� ���� �����������
extern String AppPath;
extern TClientForm *ClientForm;
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
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::StartAuthClick(TObject *Sender)
{
  AuthError->Hide();

  //������ �����
  AuthResult res = Authorisation(ServerName->Text, UserName->Text, Password->Text);

  switch (res)
	{
	  case AuthOK:
		{
		  ClientForm->UnlockUI();
		  Close();
		  break;
		}
	  case InvalidAcc:
		{
		  ClientForm->LockUI();
		  ShowAuthError("������� ������ ������ ����");
		  break;
		}
	  case ConnectErr:
		{
		  ClientForm->LockUI();
		  ShowAuthError("������� �'�������");
		  break;
		}
	  case UnknownErr:
		{
		  ClientForm->LockUI();
		  ShowAuthError("������� �������. ������ ���");
		  break;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::RegNewUserClick(TObject *Sender)
{
  //�������� ����� ���������
}
//---------------------------------------------------------------------------

void __fastcall TLoginForm::ForgotPasswordClick(TObject *Sender)
{
  //�������� ����� ���������� ������
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
	   //��� ������� �� �������, �������� ���� ������������ ����� �� ������
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
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   try
			  {
				_di_IXMLNode Document = ixml->DocumentElement;
				_di_IXMLNode Command;
				_di_IXMLNode Data;
				_di_IXMLNode Row1, Row2;
				_di_IXMLNode ID, Role;

				Command = Document->ChildNodes->Nodes[0];
				Data = Document->ChildNodes->Nodes[2];

				if (Command->NodeValue == "GRANTED")
				  {
					Row1 = Data->ChildNodes->Nodes[0];
					Row2 = Data->ChildNodes->Nodes[1];
					ID = Row1->ChildNodes->Nodes[0];
					Role = Row2->ChildNodes->Nodes[0];

					UserID = ID->NodeValue.AsType(3);

					if (UpperCase(Role->NodeValue) == "ADMIN")
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
						"Authorisation: �������: " + e.ToString());
			  }
		 }
	 }
  catch (Exception &e)
	 {
	   res = UnknownErr;
	   SaveLog(LogPath + "\\TIClient_exceptions.log", "Authorisation: " + e.ToString());
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


