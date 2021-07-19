//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Client.h"
#include "SelectLocation.h"
#include "EditItem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
extern int UserID; //ID ��������� �����������
extern int ItemID; //ID ��������� ��������
extern int LocationID; //�� ������ ������� ��� ��������

TLabel *Location;
TEditItemForm *EditItemForm;
//---------------------------------------------------------------------------
__fastcall TEditItemForm::TEditItemForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TEditItemForm::CancelClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------

void __fastcall TEditItemForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;
  Location = CurrentLocation;
}
//---------------------------------------------------------------------------

void __fastcall TEditItemForm::ApplyClick(TObject *Sender)
{
  if (!ClientForm->SetItem(ItemID, Inn->Text, Sn->Text, Model->Text, Location->Tag, UserID))
	ClientForm->AddActionLog("�� ������� ������ ��� ��������");
  else
	{
	  Close();
      ClientForm->CheckItemRefresh->Click();
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditItemForm::SelectLocationClick(TObject *Sender)
{
  SelectLocationForm->Show();
}
//---------------------------------------------------------------------------

