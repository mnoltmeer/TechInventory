//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Client.h"
#include "ImportLocationPreview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TImportLocationPreviewForm *ImportLocationPreviewForm;

extern int CurrentRowInd, CurrentColInd; //������� �������� ����� ���� � ������� �����������

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

  CurrentRowInd = 0;
  CurrentColInd = 0;

  ClientForm->CopyRecords(LocationGrid, FilteredGrid);
  Filter->Text = "";
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
				 L"�������� ������ ��� ������� ������� ����� ��������?",
				 L"ϳ�����������",
				 MB_YESNO|MB_ICONINFORMATION) == mrYes)
	{
	  ClientForm->SendQuery("DELETE FROM LOCATIONS WHERE ID NOT IN (-1, 0)");
	}

  for (int i = 1; i < LocationGrid->RowCount; i++)
	 ClientForm->AddLocation(LocationGrid->Cells[0][i], LocationGrid->Cells[1][i]);

  Close();
}
//---------------------------------------------------------------------------

void __fastcall TImportLocationPreviewForm::FilterChange(TObject *Sender)
{
  if (Filter->Text == "")
	ClientForm->CopyRecords(LocationGrid, FilteredGrid);
  else
	ClientForm->FilterTable(LocationGrid, FilteredGrid, CurrentColInd, Filter->Text);
}
//---------------------------------------------------------------------------

void __fastcall TImportLocationPreviewForm::FilteredGridMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
  FilteredGrid->MouseToCell(X, Y, CurrentColInd, CurrentRowInd);

  if (CurrentColInd >= 0)
	LbFilterField->Caption = LocationGrid->Cells[CurrentColInd][0];

  Filter->Left = LbFilterField->Left + LbFilterField->ClientWidth + 10;
}
//---------------------------------------------------------------------------
