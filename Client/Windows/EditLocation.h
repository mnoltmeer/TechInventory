/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#ifndef EditLocationH
#define EditLocationH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TEditLocationForm : public TForm
{
__published:	// IDE-managed Components
	TLabeledEdit *Index;
	TLabeledEdit *Name;
	TButton *Apply;
	TButton *Cancel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ApplyClick(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall IndexKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall NameKeyPress(TObject *Sender, System::WideChar &Key);
private:	// User declarations
	bool FMode;
	int FLocationID;
	String FLocationIndex;
	String FLocationName;

public:		// User declarations
	__fastcall TEditLocationForm(TComponent* Owner);

	__property bool Mode = {read = FMode, write = FMode};
	__property int LocationID = {read = FLocationID, write = FLocationID};
	__property String LocationIndex = {read = FLocationIndex, write = FLocationIndex};
	__property String LocationName = {read = FLocationName, write = FLocationName};
};
//---------------------------------------------------------------------------
extern PACKAGE TEditLocationForm *EditLocationForm;
//---------------------------------------------------------------------------
#endif
