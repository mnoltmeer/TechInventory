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

  AskLocationList();
}
//---------------------------------------------------------------------------

bool __fastcall TSelectLocationForm::AskLocationList()
{
  bool res;

  try
	 {
	   std::unique_ptr<TStringStream> data(ClientForm->CreateRequest("GETLOCATIONS"));

	   if (ClientForm->AskToServer(Server, data.get()))
		 {
		   data->Position = 0;
		   std::unique_ptr<TXMLDocument> ixml(ClientForm->CreatXMLStream(data.get()));

		   _di_IXMLNode Document = ixml->DocumentElement;
		   _di_IXMLNode Command = Document->ChildNodes->Nodes[0];

		   if (Command->NodeValue == "SUCCESS")
			 {
			   ClientForm->ProcessAnswer(ixml.get(), LocationGrid);
               CurrentRowInd = 1;
			 }
		   else
			 res = false;
         }
	 }
  catch (Exception &e)
	 {
	   ClientForm->AddActionLog("Помилка отримання переліку локацій");
	   res = false;
	 }

  return res;
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

