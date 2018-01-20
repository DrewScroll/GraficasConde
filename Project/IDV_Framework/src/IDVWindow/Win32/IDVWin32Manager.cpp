#include <IDVWindow/IDVWin32Manager.h>

void IDVWin32Manager::InitGlobalVars() {

}

void IDVWin32Manager::OnCreateApplication() {

}

void IDVWin32Manager::OnDestroyApplication() {

}

void IDVWin32Manager::UpdateApplication() {
	while (m_bAlive) {
		ProcessInput();
		m_pApplication->OnUpdate();
	}
}

void IDVWin32Manager::ProcessInput() {

}