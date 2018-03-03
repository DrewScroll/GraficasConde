#ifndef IDV_PRIMITIVEBASE_H
#define IDV_PRIMITIVEBASE_H


#include <IDVScene/IDVSceneProp.h>
#include <IDVVideo/IDVBaseDriver.h>

#include <vector>

#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#endif

class PrimitiveBase {
public:
	PrimitiveBase() : pScProp(0) , gSig(0) {
	
	}
	virtual ~PrimitiveBase(){}
	virtual void Create() = 0;
	virtual void Create(char *) = 0;
	virtual void Transform(float *t) = 0;
	virtual void Draw(float *t,float *vp) = 0;
	virtual void Destroy() = 0;

	void SetGlobalSignature(unsigned int f){ gSig = f; }


	void SetSceneProps(SceneProps *p) { pScProp = p; }
	SceneProps				*pScProp;
	unsigned int gSig;
};


#endif
