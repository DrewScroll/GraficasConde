#ifndef IDV_MESH_D3D_H
#define IDV_MESH_D3D_H

#include <IDV_Maths.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <wrl.h>
#include <wrl/client.h>
using namespace Microsoft::WRL;

#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>

#include <IDVVideo\IDVBaseDriver.h>
#include "IDVScene\IDVPrimitive.h"
#include "IDVUtils\IDVUtils.h"
#include "IDV_Parser.h"

class D3DXMesh : public PrimitiveBase {
public:
	struct CBuffer {
		XMATRIX44 WVP;
		XMATRIX44 World;
		XMATRIX44 WorldView;
	};

	float FTM[16];

	struct subset_info {
		ComPtr<ID3D11Buffer> IB_ID;
	};

	struct mesh_info {
		ComPtr<ID3D11Buffer> VB_ID;
		ComPtr<ID3D11Buffer> IB_ID;
		std::vector<subset_info> subInfo;
	};

	std::vector<mesh_info> MeshInfo;
	char separator;
	void Create() {};
	void Create(char * t);
	void Transform(float *t);
	void Draw(float *t, float *vp);
	void Destroy();

	int contDiffuse = 0;
	int totMat = -1;

	Parser ParserMesh;
	//vector <Material*> materials;

	unsigned int SigBase;

	/*vector <MeshVertex> vertices;
	vector <unsigned short>	indices;*/
	ComPtr<ID3D11Buffer>        pd3dConstantBuffer;
	ComPtr<ID3D11SamplerState>  pSampler;

	CBuffer			CnstBuffer;

	XMATRIX44	transform;
};

#endif