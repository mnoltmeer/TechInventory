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
