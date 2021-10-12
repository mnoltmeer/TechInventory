//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Main.cpp", ServerForm);
USEFORM("Settings.cpp", SettingsForm);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		//�������� �� ��������� ��������� ��������
		if (FindWindowW(NULL, L"������ �� ���������"))
		  Application->Terminate();

		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Sapphire Kamri");
		Application->CreateForm(__classid(TServerForm), &ServerForm);
		Application->CreateForm(__classid(TSettingsForm), &SettingsForm);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
