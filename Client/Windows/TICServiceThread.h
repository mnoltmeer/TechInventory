//---------------------------------------------------------------------------

#ifndef TICServiceThreadH
#define TICServiceThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class TICServiceThread : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall TICServiceThread(bool CreateSuspended);

    virtual int __fastcall Work() = 0;
};
//---------------------------------------------------------------------------
#endif
