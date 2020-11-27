/*!
Copyright 2020 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------
/*!
��� ������� ��'��� ������, � ����� ������ ������������ �������� ����� ������
�� �볺���� � ��������. � ��'���� � ���������� ����� int __fastcall Work()
���� ��������������� ��� ������� ��'����. � ����� ����� ������ ������������
��� �������� ����� ������.
����� ������� 0 � ��� �����, ��� �������� <0 � ��� �������.
*/
//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "TICServiceThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TICServiceThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TICServiceThread::TICServiceThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TICServiceThread::Execute()
{
	//---- Place thread code here ----
}
//---------------------------------------------------------------------------
