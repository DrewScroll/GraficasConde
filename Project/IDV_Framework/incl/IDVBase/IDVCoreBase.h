#ifndef IDV_CORE_BASE
#define IDV_CORE_BASE

#include <IDVDefs.h>

class IDVBaseWindow;

class IDVBaseApplication {
public:
	IDVBaseApplication() : m_pWindow(0) {}
	virtual void InitVars() = 0;
	virtual void CreateAssets() = 0;
	virtual void DestroyAssets() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDraw() = 0;
	virtual void OnInput() = 0;

	void		 SetWindow(IDVBaseWindow *pWindow) {
		m_pWindow = pWindow;
	}

	IDVBaseWindow	*m_pWindow;
};

class IDVBaseWindow {
public:
	IDVBaseWindow(IDVBaseApplication *pApplication) : m_pApplication(pApplication) {}

	virtual void InitGlobalVars() = 0;
	virtual void OnCreateApplication() = 0;
	virtual void OnDestroyApplication() = 0;
	virtual void UpdateApplication() = 0;
	virtual void ProcessInput() = 0;

	IDVBaseApplication	*m_pApplication;
	bool	m_bAlive;
};


#endif
