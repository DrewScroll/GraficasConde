#ifndef IDV_WIN32_MANAGER
#define IDV_WIN32_MANAGER

#include <IDVDefs.h>
#include <IDVBase/IDVCoreBase.h>

class IDVWin32Manager : public IDVBaseWindow {
public:
	IDVWin32Manager(IDVBaseApplication *pBaseApp) : IDVBaseWindow(pBaseApp) {
		m_pApplication->SetWindow(this);
		m_bAlive = true;
	}

	void InitGlobalVars();
	void OnCreateApplication();
	void OnDestroyApplication();
	void UpdateApplication();
	void ProcessInput();
};


#endif