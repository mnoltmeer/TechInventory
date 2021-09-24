//---------------------------------------------------------------------------

#ifndef RestorePasswordH
#define RestorePasswordH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TRestorePasswordForm : public TForm
{
__published:	// IDE-managed Components
	TEdit *EMail;
	TLabel *EMailError;
	TLabel *Label5;
	TEdit *Login;
	TLabel *LoginError;
	TLabel *Label2;
	TButton *Apply;
	TButton *Cancel;
	void __fastcall ApplyClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall LoginKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall EMailKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
public:		// User declarations
	__fastcall TRestorePasswordForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRestorePasswordForm *RestorePasswordForm;
//---------------------------------------------------------------------------
#endif
