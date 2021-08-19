//---------------------------------------------------------------------------

#ifndef SelectLocationH
#define SelectLocationH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSelectLocationForm : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *LocationGrid;
	TPanel *Panel1;
	TButton *Select;
	TButton *Cancel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall SelectClick(TObject *Sender);
	void __fastcall LocationGridMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall LocationGridDblClick(TObject *Sender);
private:	// User declarations
	bool __fastcall AskLocationList();

public:		// User declarations
	__fastcall TSelectLocationForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectLocationForm *SelectLocationForm;
//---------------------------------------------------------------------------
#endif