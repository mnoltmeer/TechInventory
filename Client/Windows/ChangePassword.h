//---------------------------------------------------------------------------

#ifndef ChangePasswordH
#define ChangePasswordH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TPasswordChangeForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *Password;
	TEdit *ConfirmPassword;
	TLabel *Label3;
	TLabel *Label4;
	TButton *Apply;
	TButton *Cancel;
	TLabel *Label1;
	TEdit *OldPassword;
	void __fastcall ApplyClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TPasswordChangeForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPasswordChangeForm *PasswordChangeForm;
//---------------------------------------------------------------------------
#endif
