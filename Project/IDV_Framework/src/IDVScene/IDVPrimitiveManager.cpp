#include <IDVScene/IDVPrimitiveManager.h>
#include <IDVScene/IDVGLQuad.h>
#include <IDVScene/IDVD3DQuad.h>

PrimitiveBase*	PrimitiveManager::GetPrimitive(unsigned int index) {
	if (index >= primitives.size())
		return 0;

	return primitives[index];
}

int PrimitiveManager::CreateQuad() {
	PrimitiveBase *primitive = 0;

	if(this->SelectedApi==IDVAPI::OPENGL)
		primitive = new GLQuad();
	else
		primitive = new D3DXQuad();

	primitive->Create();
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}

int PrimitiveManager::CreateMesh(char * t)
{
	PrimitiveBase *primitive = 0;
	if (this->SelectedApi == IDVAPI::OPENGL)
		primitive = new GLMesh();
	else
		primitive = new D3DXMesh();
	primitive->Create(t);
	primitives.push_back(primitive);
	return (int)(primitives.size() - 1);
}

void PrimitiveManager::SetSceneProps(SceneProps *p) {
	for (unsigned int i = 0; i < primitives.size(); i++) {
		primitives[i]->SetSceneProps(p);
	}
}

void PrimitiveManager::DrawPrimitives() {
	for(unsigned int i=0;i<primitives.size();i++){
		primitives[i]->Draw(0,&(*pVP).m[0][0]);
	}
}

void PrimitiveManager::DestroyPrimitives() {
	for (unsigned int i = 0; i < primitives.size(); i++) {
		primitives[i]->Destroy();
		delete primitives[i];
	}
	primitives.clear();
}
