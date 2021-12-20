//---------------------------------------------------------------------------

#ifndef ImportLocationPreviewH
#define ImportLocationPreviewH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TImportLocationPreviewForm : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *LocationGrid;
	TPanel *Panel1;
	TButton *Import;
	TButton *Cancel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CancelClick(TObject *Sender);
	void __fastcall ImportClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TImportLocationPreviewForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TImportLocationPreviewForm *ImportLocationPreviewForm;
//---------------------------------------------------------------------------
#endif
