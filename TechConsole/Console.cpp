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
           ShowLog("����� ������", ConsoleWindow);
		   ShowLog("������: " + ServerName + ":" + String(ListenPort), ConsoleWindow);
		   ShowLog("����� �������: " + ServerVersion, ConsoleWindow);
		   ShowLog("������ ������: " + ConfigPath, ConsoleWindow);

		   Listener->DefaultPort = ListenPort;
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
				  throw new Exception("³������ �������� ConfigPath");

				reg->CloseKey();
			  }
		  }
	   __finally {delete reg;}

       if (ReadParameter(ConfigPath + "\\service.conf", "ServerName", &ServerName, TT_TO_STR) != RP_OK)
		 throw new Exception("������� ������� ��������� ServerName");

	   ServerVersion = GetVersionInString(String(ConfigPath + "\\TIService.exe").c_str());

       if (ReadParameter(ConfigPath + "\\service.conf", "ListenPort", &ListenPort, TT_TO_INT) != RP_OK)
		 throw new Exception("������� ������� ��������� ListenPort");

	   if (ReadParameter(ConfigPath + "\\service.conf", "ConsolePort", &ConsolePort, TT_TO_INT) != RP_OK)
		 throw new Exception("������� ������� ��������� ConsolePort");
	 }
  catch (Exception &e)
	 {
	   ShowLog("������� ������� ������: " + e.ToString(), ConsoleWindow);
	   res = false;
	 }

  return res;
}
//---------------------------------------------------------------------------

void __fastcall TConsoleForm::ListenerExecute(TIdContext *AContext)
{
  TStringStream *msg = new TStringStream("", TEncoding::UTF8, true);
  String rec;

  try
	 {
	   try //������ ���, �� �������
		  {
			AContext->Connection->IOHandler->ReadStream(msg);
			msg->Position = 0;
			rec = msg->ReadString(msg->Size);
			ConsoleWindow->Perform(LB_ADDSTRING, 0, (LPARAM)rec.c_str());
		  }
	   catch (Exception &e)
		  {
			rec = "ListenerExecute: " + e.ToString();
			ConsoleWindow->Perform(LB_ADDSTRING, 0, (LPARAM)rec.c_str());
		  }
	 }
  __finally {delete msg;}
}
//---------------------------------------------------------------------------
