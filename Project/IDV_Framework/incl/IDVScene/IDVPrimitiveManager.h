#ifndef IDV_PRIMITIVEMANAGER_H
#define IDV_PRIMITIVEMANAGER_H

#include <IDV_Maths.h>

#include <vector>

#include <IDVVideo/IDVBaseDriver.h>
#include <IDVScene/IDVPrimitive.h>
#include <IDVScene/IDVSceneProp.h>
#include <IDVScene/GLMesh.h>
#include <IDVScene/D3DXMesh.h>

class PrimitiveManager {
public:
	PrimitiveManager(IDVAPI Selected) { SelectedApi = Selected;  }
	void SetVP(XMATRIX44 *vp) {
		pVP = vp;
	}
	int  CreateQuad();
	int CreateMesh(char* t);

	void SetSceneProps(SceneProps *p);

	void DrawPrimitives();
	void DestroyPrimitives();
	PrimitiveBase*	GetPrimitive(unsigned int);

	std::vector<PrimitiveBase*> primitives;

	IDVAPI		SelectedApi;
	XMATRIX44 *pVP;
};

#endif
