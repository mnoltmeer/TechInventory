/*!
Copyright 2020 Maxim Noltmeer (m.noltmeer@gmail.com)
*/
//---------------------------------------------------------------------------
/*!
Тут описано об'єкт потоку, в якому будуть виконуватись операції обміну даними
між клієнтом і сервером. У об'єкта є віртуальний метод int __fastcall Work()
який перевизначається при створені об'єкта. У цьому методі будуть виконуватись
різні операції обміну даними.
Метод повертає 0 у разі успіху, або значення <0 у разі помилки.
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

__fastcall TICServiceThread::TICServiceThread(TStringGrid *source, TStringGrid *target)
	: TThread(true)
{
  FreeOnTerminate = true;
  FSource = source;
  FTarget = target;
}
//---------------------------------------------------------------------------
void __fastcall TICServiceThread::Execute()
{
  Synchronize(&InsertIntoResultSet);
}
//---------------------------------------------------------------------------

void __fastcall TICServiceThread::InsertIntoResultSet()
{
  try
	 {
	   ClearResultSet();

	   FTarget->FixedCols = FSource->FixedCols;
	   FTarget->FixedRows = FSource->FixedRows;

	   FTarget->ColCount = FSource->ColCount;
	   FTarget->RowCount = FSource->RowCount;

	   for (int col = 0; FSource->ColCount - 1; col++)
		  {
			for (int row = 0; FSource->RowCount - 1; row++)
			   FTarget->Cells[col][row] = FSource->Cells[col][row];
		  }
	 }
  catch (Exception &e)
	 {
	   return;
	 }
}
//---------------------------------------------------------------------------

void __fastcall TICServiceThread::ClearResultSet()
{
  try
	 {
	   for (int i = 0; i < FTarget->RowCount - 1; i++)
		  FTarget->Rows[i]->Clear();

	   FTarget->ColCount = 0;
	   FTarget->RowCount = 0;
	   FTarget->FixedRows = 1;
	 }
  catch (Exception &e)
	 {
	   return;
	 }
}
//---------------------------------------------------------------------------
