//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "..\..\work-functions\MyFunc.h"
#include "Console.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TConsoleForm *ConsoleForm;
int ListenPort, ConsolePort;
String ServerName, ServerVersion, ConfigPath;

//---------------------------------------------------------------------------
__fastcall TConsoleForm::TConsoleForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::FormCreate(TObject *Sender)
{
  ReadSettings();

  try
	 {

     }
}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::ReadSettings()
{
  try
	 {
	   TRegistry *reg = new TRegistry();

	   try
		  {
			reg->RootKey = HKEY_LOCAL_MACHINE;

			if (reg->OpenKey("SOFTWARE\\TechInventServer", false))
			  {
				if (reg->ValueExists("ConfigPath"))
				  ConfigPath = reg->ReadString("ConfigPath");
				else
				  throw new Exception("Відсутній параметр ConfigPath");

				reg->CloseKey();
			  }
		  }
	   __finally {delete reg;}

       if (ReadParameter(ConfigPath + "\\service.conf", "ServerName", &ServerName, TT_TO_STR) != RP_OK)
		 throw new Exception("Помилка читання параметру ServerName");

	   ServerVersion = GetVersionInString(String(ConfigPath + "\\TIService.exe").c_str());

       if (ReadParameter(ConfigPath + "\\service.conf", "ListenPort", &ListenPort, TT_TO_INT) != RP_OK)
		 throw new Exception("Помилка читання параметру ListenPort");

	   if (ReadParameter(ConfigPath + "\\service.conf", "ConsolePort", &ConsolePort, TT_TO_INT) != RP_OK)
		 throw new Exception("Помилка читання параметру ConsolePort");
	 }
  catch (Exception &e)
	 {
	   ShowLog("Помилка запуску консолі: " + e.ToString(), ConsoleWindow);
	 }
}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::ListenerExecute(TIdContext *AContext)
{
  TStringStream *msg = new TStringStream("", TEncoding::UTF8, true);

  try
	 {
	   try //читаємо дані, що надійшли
		  {
			AContext->Connection->IOHandler->ReadStream(msg);
			msg->Position = 0;
            ShowLog(msg->ReadString(msg->Size), ConsoleWindow);
		  }
	   catch (Exception &e)
		  {
			ShowLog("ListenerExecute: " + e.ToString(), ConsoleWindow);
		  }
	 }
  __finally {delete msg;}
}
//---------------------------------------------------------------------------
