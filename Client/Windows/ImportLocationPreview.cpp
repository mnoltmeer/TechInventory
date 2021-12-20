//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Client.h"
#include "ImportLocationPreview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TImportLocationPreviewForm *ImportLocationPreviewForm;
//---------------------------------------------------------------------------
__fastcall TImportLocationPreviewForm::TImportLocationPreviewForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TImportLocationPreviewForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;
}
//---------------------------------------------------------------------------

void __fastcall TImportLocationPreviewForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TImportLocationPreviewForm::ImportClick(TObject *Sender)
{
  if (MessageBox(ClientForm->Handle,
				 L"Видалити поточні дані таблиці Локацій перед імпортом?",
				 L"Підтвердження",
				 MB_YESNO|MB_ICONINFORMATION) == mrYes)
	{
	  ClientForm->SendQuery("DELETE FROM LOCATIONS WHERE ID NOT IN (-1, 0)");
	}

  for (int i = 1; i < LocationGrid->RowCount; i++)
	 ClientForm->AddLocation(LocationGrid->Cells[0][i], LocationGrid->Cells[1][i]);

  Close();
}
//---------------------------------------------------------------------------
