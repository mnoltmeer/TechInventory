//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("Client.cpp", ClientForm);
USEFORM("Login.cpp", LoginForm);
USEFORM("EditItem.cpp", EditItemForm);
USEFORM("Registration.cpp", RegistrationForm);
USEFORM("ChangePassword.cpp", Form1);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
        Application->CreateForm(__classid(TClientForm), &ClientForm);
		Application->CreateForm(__classid(TLoginForm), &LoginForm);
		Application->CreateForm(__classid(TEditItemForm), &EditItemForm);
		Application->CreateForm(__classid(TRegistrationForm), &RegistrationForm);
		Application->CreateForm(__classid(TForm1), &Form1);
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
