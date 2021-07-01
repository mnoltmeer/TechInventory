//---------------------------------------------------------------------------

#ifndef RegistrationH
#define RegistrationH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TRegistrationForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TEdit *Login;
	TEdit *Password;
	TEdit *ConfirmPassword;
	TEdit *EMail;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *VerificationCode;
	TButton *SendCode;
	TButton *Confirm;
	TButton *Exit;
	TLabel *RegistrationResult;
	TLabel *LoginError;
	TLabel *PasswordError;
	TLabel *EMailError;
	TLabel *ConfirmPasswordError;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall SendCodeClick(TObject *Sender);
	void __fastcall ExitClick(TObject *Sender);
	void __fastcall ConfirmClick(TObject *Sender);
	void __fastcall VerificationCodeKeyPress(TObject *Sender, System::WideChar &Key);

private:	// User declarations
	bool __fastcall IsLoginFree(const String &login);
	bool __fastcall Registration(const String &login,
								 const String &pass,
								 const String &mail);
	bool __fastcall SendVerificationCode(const String &mail);

public:		// User declarations
	__fastcall TRegistrationForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRegistrationForm *RegistrationForm;
//---------------------------------------------------------------------------
#endif
