#ifndef IDV_QUAD_GL_H
#define IDV_QUAD_GL_H

#include <IDV_Maths.h>

#include <GL/glew.h>

#include <IDVVideo\IDVBaseDriver.h>
#include <IDVScene\IDVPrimitive.h>

class GLQuad : public PrimitiveBase{
public:
	struct Vert {
		float x,y,z,w;
		float u,v;
	};

	GLQuad(){}
	void Create();
	void Create(char *){}
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	unsigned int	SigBase;

	Vert			vertices[4];
	unsigned short	indices[6];
	unsigned int	VB;
	unsigned int	IB;
	XMATRIX44		transform;
};

#endif
