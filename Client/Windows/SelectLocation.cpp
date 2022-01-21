/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\..\work-functions\MyFunc.h"
#include "Client.h"
#include "SelectLocation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSelectLocationForm *SelectLocationForm;

extern int CurrentRowInd, CurrentColInd; //індекси поточних рядка поля у таблиці відображення

extern String Server;
extern TLabel *Location;
//---------------------------------------------------------------------------
__fastcall TSelectLocationForm::TSelectLocationForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TSelectLocationForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;

  CurrentRowInd = 0;
  CurrentColInd = 0;

  ClientForm->AskLocationList(LocationGrid);
  ClientForm->CopyRecords(LocationGrid, FilteredGrid);
  Filter->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TSelectLocationForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TSelectLocationForm::SelectClick(TObject *Sender)
{
  if (CurrentRowInd > 0)
	{
	  Location->Tag = FilteredGrid->Cells[0][CurrentRowInd].ToInt();
	  Location->Caption = FilteredGrid->Cells[1][CurrentRowInd];
	  Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSelectLocationForm::FilteredGridMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
  FilteredGrid->MouseToCell(X, Y, CurrentColInd, CurrentRowInd);

  if (CurrentColInd >= 0)
	LbFilterField->Caption = LocationGrid->Cells[CurrentColInd][0];

  Filter->Left = LbFilterField->Left + LbFilterField->ClientWidth + 10;
}
//---------------------------------------------------------------------------

void __fastcall TSelectLocationForm::FilteredGridDblClick(TObject *Sender)
{
  Select->Click();
}
//---------------------------------------------------------------------------

void __fastcall TSelectLocationForm::FilterChange(TObject *Sender)
{
  if (Filter->Text == "")
	ClientForm->CopyRecords(LocationGrid, FilteredGrid);
  else
	ClientForm->FilterTable(LocationGrid, FilteredGrid, CurrentColInd, Filter->Text);
}
//---------------------------------------------------------------------------

