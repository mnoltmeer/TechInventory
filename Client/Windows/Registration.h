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
	TEdit *Edit2;
	TEdit *EMail;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *VerificationCode;
	TLabel *Label6;
	TButton *SendCode;
	TButton *Confirm;
	TButton *Exit;
	TLabel *RegistrationResult;
private:	// User declarations
public:		// User declarations
	__fastcall TRegistrationForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRegistrationForm *RegistrationForm;
//---------------------------------------------------------------------------
#endif
