#include "IDVScene/D3DXMesh.h"
#include <IDVVideo/IDVD3DXShader.h>
#include <IDVUtils/IDVUtils.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

extern ComPtr<ID3D11Device>            D3D11Device;
extern ComPtr<ID3D11DeviceContext>     D3D11DeviceContext;

void D3DXMesh::Create(char* t) {
	SigBase = IDVSig::HAS_TEXCOORDS0;

	char *vsSourceP = file2string("VS_Mesh.glsl");
	char *fsSourceP = file2string("FS_Mesh.glsl");

	std::string vstr = std::string(vsSourceP);
	std::string fstr = std::string(fsSourceP);

	free(vsSourceP);
	free(fsSourceP);

	int shaderID = g_pBaseDriver->CreateShader(vstr, fstr, SigBase);

	ParserMesh.Lectura(t);

	IDVD3DXShader* s = dynamic_cast<IDVD3DXShader*>(g_pBaseDriver->GetShaderIdx(shaderID));

	D3D11_BUFFER_DESC bdesc = { 0 };
	bdesc.Usage = D3D11_USAGE_DEFAULT;
	bdesc.ByteWidth = sizeof(CBuffer);
	bdesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	HRESULT hr = D3D11Device->CreateBuffer(&bdesc, 0, pd3dConstantBuffer.GetAddressOf());
	if (hr != S_OK) {
		printf("Error Creating Constant Buffer\n");
		return;
	}

	bdesc = { 0 };
	bdesc.ByteWidth = sizeof(MeshVertex) * 4;
	bdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	for (int i = 0; i < ParserMesh.Meshes.size(); i++)
	{

		D3D11_SUBRESOURCE_DATA subData = { ParserMesh.Meshes[i]->vertices, 0, 0 };

		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &VB);
		if (hr != S_OK) {
			printf("Error Creating Vertex Buffer\n");
			return;
		}

		bdesc = { 0 };
		bdesc.ByteWidth = 6 * sizeof(USHORT);
		bdesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		subData = { ParserMesh.Meshes[i]->indices, 0, 0 };

		hr = D3D11Device->CreateBuffer(&bdesc, &subData, &IB);
		if (hr != S_OK) {
			printf("Error Creating Index Buffer\n");
			return;
		}
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
	for (int i = 0; i < 16; i++)
	{
		VP.mat[i] = vp[i];
	}
	XMATRIX44 WVP = transform * VP;

	CnstBuffer.WVP = transform;
	CnstBuffer.World = transform;
	CnstBuffer.WorldView = transform;

	D3D11DeviceContext->VSSetShader(s->pVS.Get(), 0, 0);
	D3D11DeviceContext->PSSetShader(s->pFS.Get(), 0, 0);
	D3D11DeviceContext->IASetInputLayout(s->Layout.Get());

	D3D11DeviceContext->UpdateSubresource(pd3dConstantBuffer.Get(), 0, 0, &CnstBuffer, 0, 0);
	D3D11DeviceContext->VSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());
	D3D11DeviceContext->PSSetConstantBuffers(0, 1, pd3dConstantBuffer.GetAddressOf());

	D3D11DeviceContext->IASetIndexBuffer(IB.Get(), DXGI_FORMAT_R16_UINT, 0);
	D3D11DeviceContext->IASetVertexBuffers(0, 1, VB.GetAddressOf(), &stride, &offset);

	D3D11DeviceContext->PSSetSamplers(0, 1, pSampler.GetAddressOf());
	D3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D11DeviceContext->DrawIndexed(6, 0, 0);

}

void D3DXMesh::Destroy() {
}