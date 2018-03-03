#include <IDVDefs.h>

#include <IDVWindow/IDVWin32Manager.h>
#include <IDV_TestApplication.h>

#include <IDV_Parser.h>
#include <IDV_Maths.h>

IDVBaseApplication *g_pApplication = 0;
IDVBaseWindow	   *g_pWindow = 0;

int main(int arg, char ** args) {

	g_pApplication = new IDVTestApplication();
	g_pWindow = new IDVWin32Manager((IDVBaseApplication*)g_pApplication);
	g_pWindow->InitGlobalVars();
	g_pWindow->OnCreateApplication();

	g_pWindow->UpdateApplication();

	g_pWindow->OnDestroyApplication();

	delete g_pWindow;
	delete g_pApplication;

	return 0;
}