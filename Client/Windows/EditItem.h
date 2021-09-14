/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#ifndef EditItemH
#define EditItemH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TEditItemForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label7;
	TEdit *Inn;
	TEdit *Sn;
	TLabel *Label8;
	TLabel *Label9;
	TEdit *Model;
	TButton *SelectLocation;
	TLabel *CurrentLocation;
	TLabel *Label11;
	TButton *Apply;
	TButton *Cancel;
	TLabel *Label1;
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ApplyClick(TObject *Sender);
	void __fastcall SelectLocationClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TEditItemForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditItemForm *EditItemForm;
//---------------------------------------------------------------------------
#endif
