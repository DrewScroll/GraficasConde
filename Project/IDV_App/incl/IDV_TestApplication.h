#ifndef IDV_TEST_APPLICATION
#define IDV_TEST_APPLICATION

#include <IDVBase/IDVCoreBase.h>

class IDVTestApplication : public IDVBaseApplication {
public:
	IDVTestApplication() : IDVBaseApplication() {}
	void InitVars();
	void CreateAssets();
	void DestroyAssets();
	void OnUpdate();
	void OnDraw();
	void OnInput();
};

#endif