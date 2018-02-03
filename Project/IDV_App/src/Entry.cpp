#include <IDVDefs.h>

#include <IDVWindow/IDVWin32Manager.h>
#include <IDV_TestApplication.h>

#include <IDVParser.h>
#include <IDV_Maths.h>

IDVBaseApplication *g_pApplication = 0;
IDVBaseWindow	   *g_pWindow = 0;

int main(int arg, char ** args) {

	PrintFromLibrary();

	g_pApplication = new IDVTestApplication();
	g_pWindow = new IDVWin32Manager((IDVBaseApplication*)g_pApplication);
	g_pWindow->InitGlobalVars();
	g_pWindow->OnCreateApplication();

	//g_pWindow->UpdateApplication();
	
	XMATRIX44 Position, RotationX, RotationY, RotationZ, Scale, Projection;
	XMatTranslation(Position, 15.0f, -5.0f, 0.0f);
	XMatRotationXLH(RotationX, Deg2Rad(90.0f));
	XMatRotationYLH(RotationY, Deg2Rad(15.0f));
	XMatRotationZLH(RotationZ, Deg2Rad(120.0f));
	XMatScaling(Scale, 1.1f, 1.1f, 1.1f);
	XMatPerspectiveLH(Projection, Deg2Rad(60.0f), 1280.0f / 720.0f, 1.0f, 1000.0f);
	XMATRIX44 Final = Projection * Scale * RotationX * RotationY * RotationZ * Position;
	XMATRIX44 test = Projection * Position;


	PrintMatrix(Final);

	g_pWindow->OnDestroyApplication();

	delete g_pWindow;
	delete g_pApplication;

	return 0;
}