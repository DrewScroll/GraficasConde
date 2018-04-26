#include "IDVScene/D3DXMesh.h"
#include <IDVVideo/IDVD3DXShader.h>
#include <IDVUtils/IDVUtils.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;

void D3DXMesh::Create(char* t) {
	SigBase = IDVSig::HAS_TEXCOORDS0 | IDVSig::HAS_NORMALS;
	HRESULT hr;
	char *vsSourceP = file2string("Shaders/VS_Mesh.hlsl");
	char *fsSourceP = file2string("Shaders/FS_Mesh.hlsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	ParserMesh.Lectura(t);

	for (int i = 0; i < ParserMesh.Meshes.size(); i++)
	{
		int shaderID = g_pBaseDriver->CreateShader(vstr, fstr, SigBase);

		IDVD3DXShader* s = dynamic_cast<IDVD3DXShader*>(g_pBaseDriver->GetShaderIdx(shaderID));

		D3D11_BUFFER_DESC bdesc = { 0 };
		bdesc.Usage = D3D11_USAGE_DEFAULT;
		bdesc.ByteWidth = sizeof(CBuffer);
		bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		hr = D3D11Device->CreateBuffer(&bdesc, 0, pd3dConstantBuffer.GetAddressOf());
		if (hr != S_OK) {
			printf("Error Creating Constant Buffer\n");
			return;
		}

		bdesc = { 0 };
		bdesc.ByteWidth = sizeof(MeshVertex) * ParserMesh.Meshes[i]->vert;
		bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subData = { &ParserMesh.Meshes[i]->vertices[0], 0, 0 };
		mesh_info tmp;
		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &tmp.VB_ID);
		if (hr != S_OK) {
			printf("Error Creating Vertex Buffer\n");
			return;
		}

		bdesc = { 0 };

		bdesc.ByteWidth = ParserMesh.Meshes[i]->ind * sizeof(USHORT);
		bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &tmp.IB_ID);
		subData = { &ParserMesh.Meshes[i]->indices[0], 0, 0 };

		for (int j = 0; j < ParserMesh.Meshes[i]->totalmaterial; j++)
		{
			subset_info tmp_2;
			bdesc = { 0 };
			bdesc.ByteWidth = ParserMesh.Meshes[i]->materials[j]->ind * sizeof(unsigned short) * 3;
			bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			subData = { &ParserMesh.Meshes[i]->materials[j]->indices[0], 0, 0 };

			hr = D3D11Device->CreateBuffer(&bdesc, &subData, &tmp_2.IB_ID);
			if (hr != S_OK) {
				printf("Error Creating Index Buffer\n");
				return;
			}
			tmp.subInfo.push_back(tmp_2);
		}
		MeshInfo.push_back(tmp);
	}

	D3D11_SAMPLER_DESC sdesc;
	sdesc.Filter = D3D11_FILTER_ANISOTROPIC;
	sdesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	sdesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	sdesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	sdesc.MinLOD = 0;
	sdesc.MaxLOD = D3D11_FLOAT32_MAX;
	sdesc.MipLODBias = 0.0f;
	sdesc.MaxAnisotropy = 1;
	sdesc.BorderColor[0] = sdesc.BorderColor[1] = sdesc.BorderColor[2] = sdesc.BorderColor[3] = 0;
	D3D11Device->CreateSamplerState(&sdesc, pSampler.GetAddressOf());

	XMatIdentity(transform);
}

void D3DXMesh::Transform(float *t) {
	for (int i = 0; i < 16; i++)
	{
		transform.mat[i] = t[i];
	}
}

void D3DXMesh::Draw(float *t, float *vp) {

	if (t)
		for (int i = 0; i < 16; i++)
		{
			transform.mat[i] = t[i];
		}

	unsigned int sig = SigBase;
	sig |= gSig;
	IDVD3DXShader * s = dynamic_cast<IDVD3DXShader*>(g_pBaseDriver->GetShaderSig(sig));
	UINT offset = 0;
	UINT stride = sizeof(MeshVertex);

	XMATRIX44 VP;
	XMATRIX44 WV;

	for (int i = 0; i < 16; i++)
	{
		VP.mat[i] = vp[i];
		WV.mat[i] = vp[i];
	}
	//XMATRIX44 WVP = transform * VP;

	XMATRIX44 Scale;
	XMATRIX44 View;
	XMATRIX44 Projection;
	XMatViewLookAtLH(View, XVECTOR3(0.0f, 0.0f, -10.0f), XVECTOR3(0.0f, 0.0f, 1.0f), XVECTOR3(0.0f, 1.0f, 0.0f));
	XMatPerspectiveLH(Projection, Deg2Rad(60.0f), 1280.0f / 720.0f, 0.1f, 100.0f);
	XMatScaling(Scale, 0.15f, 0.15f, 0.15f);
	XMATRIX44 WVP = Scale * View*Projection;

	CnstBuffer.WVP = WVP;
	CnstBuffer.World = transform;
	CnstBuffer.WorldView = transform;

	for (int i = 0; i < ParserMesh.Meshes.size(); ++i)
	{
		D3D11DeviceContext->IASetVertexBuffers(0, 1, MeshInfo[i].VB_ID.GetAddressOf(), &stride, &offset);
		for (int j = 0; j < ParserMesh.totMat; ++j)
		{

			D3D11DeviceContext->VSSetShader(s->pVS.Get(), 0, 0);
			D3D11DeviceContext->PSSetShader(s->pFS.Get(), 0, 0);
			D3D11DeviceContext->IASetInputLayout(s->Layout.Get());

			D3D11DeviceContext->UpdateSubresource(pd3dConstantBuffer.Get(), 0, 0, &CnstBuffer, 0, 0);
			D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
			D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());

			D3D11DeviceContext->IASetIndexBuffer(MeshInfo[i].subInfo[j].IB_ID.Get(), DXGI_FORMAT_R16_UINT, 0);

			D3D11DeviceContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
			D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			D3D11DeviceContext->DrawIndexed(ParserMesh.Meshes[i]->materials[j]->ind * 3, 0, 0);
		}
	}
}

void D3DXMesh::Destroy() {
}