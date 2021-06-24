//---------------------------------------------------------------------------

#ifndef ConsoleH
#define ConsoleH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdTCPServer.hpp>
#include <IdContext.hpp>
//---------------------------------------------------------------------------
class TConsoleForm : public TForm
{
__published:	// IDE-managed Components
	TPanel *SendCmdPanel;
	TEdit *CmdText;
	TButton *CmdSend;
	TIdTCPServer *Listener;
	TTrayIcon *TrayIcon;
	TMemo *ConsoleWindow;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ListenerExecute(TIdContext *AContext);
	void __fastcall TrayIconClick(TObject *Sender);
	void __fastcall CmdSendClick(TObject *Sender);
	void __fastcall CmdTextKeyPress(TObject *Sender, System::WideChar &Key);

private:	// User declarations
	bool __fastcall ReadSettings();
	void __fastcall ExecuteCommand(const String &command);

public:		// User declarations
	__fastcall TConsoleForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConsoleForm *ConsoleForm;
//---------------------------------------------------------------------------
#endif
