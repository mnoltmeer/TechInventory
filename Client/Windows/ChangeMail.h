/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#ifndef ChangeMailH
#define ChangeMailH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TChangeMailForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *Password;
	TLabel *Label3;
	TLabel *Label5;
	TEdit *EMail;
	TLabel *EMailError;
	TLabel *PasswordError;
	TButton *Apply;
	TButton *Cancel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ApplyClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TChangeMailForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChangeMailForm *ChangeMailForm;
//---------------------------------------------------------------------------
#endif
