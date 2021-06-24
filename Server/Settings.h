//---------------------------------------------------------------------------

#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TSettingsForm : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *ServicePort;
	TCheckBox *StartMinimised;
	TBitBtn *Apply;
	TBitBtn *Cancel;
	TCheckBox *EnableAutoStart;
	TLabeledEdit *Server;
	TLabeledEdit *Host;
	TLabeledEdit *Database;
	TLabeledEdit *Port;
	TLabel *Label1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall ApplyClick(TObject *Sender);
private:	// User declarations
	void __fastcall ReadSettings();
    void __fastcall WriteSettings();

public:		// User declarations
	__fastcall TSettingsForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSettingsForm *SettingsForm;
//---------------------------------------------------------------------------
#endif
