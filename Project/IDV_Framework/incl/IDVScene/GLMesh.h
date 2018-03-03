#ifndef IDV_MESH_GL_H
#define IDV_MESH_GL_H

#include "GL\glew.h"
#include <IDV_Maths.h>
#include <IDVVideo\IDVBaseDriver.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "IDVScene\IDVPrimitive.h"
#include "IDVUtils\IDVUtils.h"
#include "IDV_Parser.h"

using namespace std;

class GLMesh : public PrimitiveBase {
public:
	float FTM[16];
	
	char separator;
	GLMesh() {}
	void Create() {};
	void Create(char * t);
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	int contDiffuse = 0;
	int totMat = -1;

	unsigned int SigBase;

	Parser ParserMesh;
	//vector <Material*> materials;

	/*vector <MeshVertex> vertices;
	vector <unsigned short>	indices;*/
	GLuint			VB;
	GLuint			IB;

	XMATRIX44	transform;
};


#endif