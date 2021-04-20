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
	TListBox *ConsoleWindow;
	TIdTCPServer *Listener;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall ListenerExecute(TIdContext *AContext);

private:	// User declarations
	void __fastcall ReadSettings();

public:		// User declarations
	__fastcall TConsoleForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TConsoleForm *ConsoleForm;
//---------------------------------------------------------------------------
#endif
