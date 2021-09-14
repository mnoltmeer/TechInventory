/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#ifndef SetPasswordH
#define SetPasswordH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TSetPasswordForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label3;
	TLabel *Label4;
	TEdit *Password;
	TEdit *ConfirmPassword;
	TButton *Apply;
	TButton *Cancel;
	void __fastcall ApplyClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	int FUserID;
public:		// User declarations
	__fastcall TSetPasswordForm(TComponent* Owner);

    __property int UserID = {read = FUserID, write = FUserID};
};
//---------------------------------------------------------------------------
extern PACKAGE TSetPasswordForm *SetPasswordForm;
//---------------------------------------------------------------------------
#endif
