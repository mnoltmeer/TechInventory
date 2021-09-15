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

extern int CurrentRowInd, CurrentColInd; //������� �������� ����� ���� � ������� �����������

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
	  Location->Tag = LocationGrid->Cells[0][CurrentRowInd].ToInt();
	  Location->Caption = LocationGrid->Cells[1][CurrentRowInd] + " " +
						  LocationGrid->Cells[2][CurrentRowInd];
	  Close();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSelectLocationForm::LocationGridMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
  LocationGrid->MouseToCell(X, Y, CurrentColInd, CurrentRowInd);
}
//---------------------------------------------------------------------------

void __fastcall TSelectLocationForm::LocationGridDblClick(TObject *Sender)
{
  Select->Click();
}
//---------------------------------------------------------------------------

