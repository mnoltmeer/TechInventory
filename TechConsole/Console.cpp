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
  try
	 {
	   if (ReadSettings())
		 {
		   ShowLog("Старт консолі, порт: " + String(ConsolePort), ConsoleWindow);
		   ShowLog("Версія служби: " + ServerVersion, ConsoleWindow);
		   ShowLog("Сервер: " + ServerName + ":" + String(ListenPort), ConsoleWindow);

		   Listener->DefaultPort = ConsolePort;
		   Listener->Active = true;
		 }
	 }
  catch (Exception &e)
	 {
	   ShowLog("FormCreate: " + e.ToString(), ConsoleWindow);
	 }
}
//---------------------------------------------------------------------------

bool __fastcall TConsoleForm::ReadSettings()
{
  bool res = true;

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
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::ExecuteCommand(const String &command)
{

}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::ListenerExecute(TIdContext *AContext)
{
  TStringStream *msg = new TStringStream("", TEncoding::UTF8, true);
  String rec = "["
				+ DateToStr(Date())
				+ " "
				+ TimeToStr(Time())
				+ "]"
				+ " : ";

  AContext->Connection->IOHandler->ReadStream(msg);

  try
	 {
	   try //читаємо дані, що надійшли
		  {
			msg->Position = 0;
			rec += msg->ReadString(msg->Size);
			SendToLog(rec + "\r\n", ConsoleWindow);
			ConsoleWindow->Perform(WM_VSCROLL, SB_BOTTOM, 0);
		  }
	   catch (Exception &e)
		  {
			rec += "ListenerExecute: " + e.ToString();
			SendToLog(rec + "\r\n", ConsoleWindow);
			ConsoleWindow->Perform(WM_VSCROLL, SB_BOTTOM, 0);
		  }
	 }
  __finally {delete msg;}
}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::TrayIconClick(TObject *Sender)
{
  Visible = !Visible;
}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::CmdSendClick(TObject *Sender)
{
  ShowLog(" >> " + CmdText->Text, ConsoleWindow);
  ExecuteCommand(CmdText->Text);
  CmdText->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::CmdTextKeyPress(TObject *Sender, System::WideChar &Key)
{
  if (Key == 13)
	CmdSend->Click();
}
//---------------------------------------------------------------------------

