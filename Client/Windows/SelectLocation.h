/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
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
	TPanel *Panel2;
	TLabel *Label1;
	TLabel *LbFilterField;
	TEdit *Filter;
	TStringGrid *FilteredGrid;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall SelectClick(TObject *Sender);
	void __fastcall FilteredGridMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall FilteredGridDblClick(TObject *Sender);
	void __fastcall FilterChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TSelectLocationForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSelectLocationForm *SelectLocationForm;
//---------------------------------------------------------------------------
#endif
