//---------------------------------------------------------------------------

#ifndef TICServiceThreadH
#define TICServiceThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------
class TICServiceThread : public TThread
{
private:
	TStringGrid *FSource;
	TStringGrid *FTarget;
protected:
	void __fastcall Execute();
public:
	__fastcall TICServiceThread(TStringGrid *source, TStringGrid *target);

//вставляє дані з тимчасової таблиці в таблицю для відображення
//виконується через Synchronize()
	void __fastcall InsertIntoResultSet();
	void __fastcall ClearResultSet();
};
//---------------------------------------------------------------------------
#endif
