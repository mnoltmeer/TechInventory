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
	TLabel *Label10;
	TButton *SelectLocation;
	TLabel *CurrentLocation;
	TLabel *Label11;
	TButton *Apply;
	TButton *ClearFields;
	TLabel *Label1;
private:	// User declarations
public:		// User declarations
	__fastcall TEditItemForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TEditItemForm *EditItemForm;
//---------------------------------------------------------------------------
#endif
