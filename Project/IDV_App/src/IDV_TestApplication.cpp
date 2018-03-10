#include <IDV_TestApplication.h>

#include <stdio.h>

void IDVTestApplication::InitVars() {

}

void IDVTestApplication::CreateAssets() 
{
	PrimitiveMgr = new PrimitiveManager(m_pWindow->m_pVideoDriver->SelectedApi);

	PrimitiveMgr->SetVP(&VP);

	//int index = PrimitiveMgr->CreateQuad();
	int indexMesh = PrimitiveMgr->CreateMesh("NuBatman.X");

	//QuadInst.CreateInstance(PrimitiveMgr->GetPrimitive(index), &VP);
	Mesh[0].CreateInstance(PrimitiveMgr->GetPrimitive(indexMesh), &VP);
}

void IDVTestApplication::DestroyAssets() {
	delete PrimitiveMgr;
}

void IDVTestApplication::OnUpdate() {

	OnDraw();
}

void IDVTestApplication::OnDraw(){
	m_pWindow->m_pVideoDriver->Clear();

	//QuadInst.Draw();
	Mesh->Draw();

	m_pWindow->m_pVideoDriver->SwapBuffers();
}

void IDVTestApplication::OnInput() {

}