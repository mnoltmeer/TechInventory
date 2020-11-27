/*!
Copyright 2020 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#ifndef LoginH
#define LoginH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
enum AuthResult {AuthOK = 0,
				 InvalidAcc = -1,
				 ConnectErr = -2,
				 UnknownErr = -3};

class TLoginForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *UserName;
	TEdit *Password;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *RegNewUser;
	TButton *StartAuth;
	TLabel *ForgotPassword;
	TLabel *AuthError;
	TLabel *Label3;
	TEdit *ServerName;
	void __fastcall StartAuthClick(TObject *Sender);
	void __fastcall RegNewUserClick(TObject *Sender);
	void __fastcall ForgotPasswordClick(TObject *Sender);
	void __fastcall UserNameKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall PasswordKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	AuthResult __fastcall Authorisation(const String &server,
										const String &user,
										const String &password);

public:		// User declarations
	__fastcall TLoginForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TLoginForm *LoginForm;
//---------------------------------------------------------------------------
#endif
