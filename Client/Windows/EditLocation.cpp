/*!
Copyright 2020-2021 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Client.h"
#include "EditLocation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TEditLocationForm *EditLocationForm;
//---------------------------------------------------------------------------
__fastcall TEditLocationForm::TEditLocationForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TEditLocationForm::FormShow(TObject *Sender)
{
  Left = ClientForm->Left + ClientForm->ClientWidth / 2 - ClientWidth / 2;
  Top = ClientForm->Top + ClientForm->ClientHeight / 2 - ClientHeight / 2;
  Index->Text = LocationIndex;
  Name->Text = LocationName;

  if (Mode)
	{
	  Caption = "��������� �������";
	  Apply->Caption = "��������";
	}
  else
	{
	  Caption = "����������� �������";
	  Apply->Caption = "�����������";
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditLocationForm::ApplyClick(TObject *Sender)
{
  if (Index->Text == "")
	MessageBox(this->Handle, L"�� ������� ������ �������", L"�������", MB_OK|MB_ICONERROR);
  else if (Name->Text == "")
	MessageBox(this->Handle, L"�� ������� ����� �������", L"�������", MB_OK|MB_ICONERROR);
  else
	{
	  if (Mode)
		{
		  if (ClientForm->AddLocation(Index->Text, Name->Text))
			{
			  MessageBox(this->Handle, L"�������� ���� �������", L"����", MB_OK|MB_ICONINFORMATION);
			  Index->Text = "";
			  Name->Text = "";
              ClientForm->AskLocationList(ClientForm->AdmLocationsResult);
			}
		  else
			MessageBox(this->Handle, L"�� ������� �������� �������", L"�������", MB_OK|MB_ICONERROR);
		}
	  else
		{
		  if (ClientForm->EditLocation(LocationID, Index->Text, Name->Text))
			{
              MessageBox(this->Handle, L"������ ��� �������", L"����", MB_OK|MB_ICONINFORMATION);
			  Close();
			  ClientForm->AskLocationList(ClientForm->AdmLocationsResult);
			}
		  else
			MessageBox(this->Handle, L"�� ������� ������ �������", L"�������", MB_OK|MB_ICONERROR);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TEditLocationForm::CancelClick(TObject *Sender)
{
  Close();
  ClientForm->AskLocationList(ClientForm->AdmLocationsResult);
}
//---------------------------------------------------------------------------

void __fastcall TEditLocationForm::IndexKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	Apply->Click();
}
//---------------------------------------------------------------------------

void __fastcall TEditLocationForm::NameKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	Apply->Click();
}
//---------------------------------------------------------------------------
