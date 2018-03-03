#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct MeshVertex {
	MeshVertex() : w(1.0f), nw(1.0f)
	{}
	float x, y, z, w;
	float nx, ny, nz, nw;
	float s, t;

};

struct Material {
	unsigned int IB;
	unsigned int diffuse_textID;
	string diffusepath;
	vector <unsigned short> indices;
	int ind;
};

struct ContMesh
{
	MeshVertex *vertices;
	unsigned short	*indices;
	int vert, ind, totalmaterial;
	vector <Material*> materials;
};

class Parser
{
public:
	Parser();
	~Parser();

	string LineaActual;
	char character;
	int iNumVertex;
	float x, y, z;
	char separator;
	int totMat;

	ContMesh *XMesh;
	Material *XMaterial;
	vector <ContMesh*> Meshes;

	void Lectura(const char* NombreArchivo);
};

