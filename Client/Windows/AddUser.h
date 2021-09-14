/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#ifndef AddUserH
#define AddUserH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TAddUserForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *LoginError;
	TLabel *PasswordError;
	TLabel *EMailError;
	TLabel *ConfirmPasswordError;
	TEdit *Login;
	TEdit *Password;
	TEdit *ConfirmPassword;
	TEdit *EMail;
	TComboBox *UserRole;
	TLabel *Label1;
	TButton *Create;
	TButton *Cancel;
	TLabel *RegistrationResult;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CreateClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TAddUserForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAddUserForm *AddUserForm;
//---------------------------------------------------------------------------
#endif
