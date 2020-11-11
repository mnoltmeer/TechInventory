#include <System.SysUtils.hpp>
#include <Vcl.SvcMgr.hpp>
#pragma hdrstop
#include <tchar.h>
USEFORM("serv.cpp", TechService); /* TService: File Type */
//---------------------------------------------------------------------------
#define Application Svcmgr::Application
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		if ((!Application->DelayInitialize) || (Application->Installing()))
		{
			Application->Initialize();
		}
		Application->CreateForm(__classid(TTechService), &TechService);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Sysutils::ShowException(&exception, System::ExceptAddr());
	}
	catch(...)
	{
		try
		{
			throw Exception("");
		}
		catch(Exception &exception)
		{
			Sysutils::ShowException(&exception, System::ExceptAddr());
		}
        }
	return 0;
}
