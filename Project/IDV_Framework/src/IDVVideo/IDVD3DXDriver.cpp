
#include <IDVVideo/IDVD3DXDriver.h>
#include <IDVVideo/IDVD3DXShader.h>

#include <iostream>
#include <string>

#pragma comment(lib,"D3D11.lib")
#pragma comment(lib,"D3DCompiler.lib")

// D3D11 Main Objects
ComPtr<IDXGISwapChain>			DXGISwapchain;	// Responsible of the swap buffers
ComPtr<ID3D11Device>            D3D11Device;	// Device for create resources
ComPtr<ID3D11DeviceContext>     D3D11DeviceContext; // Context to set and manipulate the resources
ComPtr<ID3D11RenderTargetView>  D3D11RenderTargetView;  // View into the back buffer
ComPtr<ID3D11DepthStencilView>  D3D11DepthStencilTargetView; // View into the depth buffer
ComPtr<ID3D11Texture2D>			D3D11DepthTex;	// Actual depth buffer texture
ComPtr<ID3D11RasterizerState>   D3D11RasterizerState;

void IDVD3DXDriver::InitDriver(){
	//	Descriptor of the Back Buffer
	DXGI_MODE_DESC BackBufferDesc;
	ZeroMemory(&BackBufferDesc, sizeof(DXGI_MODE_DESC));
	BackBufferDesc.Width = Width;
	BackBufferDesc.Height = Height;
	BackBufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // RGBA 32 bit buffer
	BackBufferDesc.RefreshRate.Numerator = 0;
	BackBufferDesc.RefreshRate.Denominator = 1;
	BackBufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	BackBufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//	Descriptor of the Swap Chain
	DXGI_SWAP_CHAIN_DESC SwapChainDesc;
	ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	SwapChainDesc.BufferDesc = BackBufferDesc;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.OutputWindow = hwnd;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//	Function to create three objects:
	//	Device
	//	Device Context
	//	Swap Chain
#define DEBUG_DRIVER 1
	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
#if DEBUG_DRIVER
		D3D11_CREATE_DEVICE_DEBUG,	// Debug errors
#else
		0,
#endif
		NULL, NULL, D3D11_SDK_VERSION, &SwapChainDesc, &DXGISwapchain, &D3D11Device, NULL, &D3D11DeviceContext);

	// Get the back buffer
	ComPtr<ID3D11Texture2D> BackBuffer;
	hr = DXGISwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), &BackBuffer);

	// Descriptor to create the Depth Buffer
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = Width;
	descDepth.Height = Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;	// 24 bits for depth 8 bits for stencil
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL; // -- > Use it as depth stencil
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	hr = D3D11Device->CreateTexture2D(&descDepth, NULL, &D3D11DepthTex);	// Output to the depth texture

	// Descriptor to create the Depth View
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));

	dsvd.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	// Using the View we can operate with the depth buffer, note this view is created from the depth texture
	hr = D3D11Device->CreateDepthStencilView(D3D11DepthTex.Get(), &dsvd, &D3D11DepthStencilTargetView);


	//	Now we create the main render target view from the back buffer texture
	hr = D3D11Device->CreateRenderTargetView(BackBuffer.Get(), NULL, &D3D11RenderTargetView);

	// Using the Context now we set the render targets, that would be the Main Render Target View (Back Buffer)
	// and the Depth Buffer View (Depth)
	D3D11DeviceContext->OMSetRenderTargets(1, D3D11RenderTargetView.GetAddressOf(), D3D11DepthStencilTargetView.Get());


	// Set the Viewport of the size of the screen
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(Width);
	viewport.Height = static_cast<float>(Height);
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	D3D11DeviceContext->RSSetViewports(1, &viewport);

	
	D3D11_RASTERIZER_DESC rasterizerState;
	rasterizerState.FillMode = D3D11_FILL_SOLID;
	rasterizerState.CullMode = D3D11_CULL_FRONT;
	rasterizerState.FrontCounterClockwise = true;
	rasterizerState.DepthBias = false;
	rasterizerState.DepthBiasClamp = 0;
	rasterizerState.SlopeScaledDepthBias = 0;
	rasterizerState.DepthClipEnable = true;
	rasterizerState.ScissorEnable = false;
	rasterizerState.MultisampleEnable = false;
	rasterizerState.AntialiasedLineEnable = false;

	D3D11Device->CreateRasterizerState(&rasterizerState,&D3D11RasterizerState);

	D3D11DeviceContext->RSSetState(D3D11RasterizerState.Get());
}

void IDVD3DXDriver::CreateSurfaces(){

}

void IDVD3DXDriver::DestroySurfaces(){

}

void IDVD3DXDriver::Update(){

}

void IDVD3DXDriver::DestroyDriver(){

}

void IDVD3DXDriver::SetWindow(void *window){
	hwnd = GetActiveWindow(); // Get the HWND of the window
}

void IDVD3DXDriver::SetDimensions(int w, int h){
	Width=w;
	Height=h;
}

void IDVD3DXDriver::Clear(){
	float rgba[4];
	rgba[0] = 0.5f;
	rgba[1] = 0.5f;
	rgba[2] = 0.5f;
	rgba[3] = 1.0f;

	// Clearing the Main Render Target View
	D3D11DeviceContext->ClearRenderTargetView(D3D11RenderTargetView.Get(), rgba);
	// Clearing the Depth Buffer
	D3D11DeviceContext->ClearDepthStencilView(D3D11DepthStencilTargetView.Get(), D3D11_CLEAR_DEPTH , 1.0f, 0);
}

void IDVD3DXDriver::SwapBuffers(){
	// Swap between back and front buffer
	DXGISwapchain->Present(0, 0);
}

int	IDVD3DXDriver::CreateShader(std::string src_vs, std::string src_fs, unsigned int sig) {
	for (unsigned int i = 0; i < Shaders.size(); i++) {
		if (Shaders[i]->Sig == sig) {
			return i;
		}
	}

	IDVD3DXShader* shader = new IDVD3DXShader();
	if (shader->CreateShader(src_vs, src_fs, sig)) {
		Shaders.push_back(shader);
		return (Shaders.size() - 1);
	}
	else {
		delete shader;
	}
	return -1;

}

IDVShaderBase*	IDVD3DXDriver::GetShaderSig(unsigned int sig) {
	for (unsigned int i = 0; i < Shaders.size(); i++) {
		if (Shaders[i]->Sig == sig) {
			return Shaders[i];
		}
	}
	printf("Warning null ptr ShaderBase Sig\n");
	return 0;
}

IDVShaderBase*	IDVD3DXDriver::GetShaderIdx(int id) {
	if (id < 0 || id >= (int)Shaders.size()) {
		printf("Warning null ptr ShaderBase Idx\n");
		return 0;
	}

	return Shaders[id];
}

void IDVD3DXDriver::DestroyShaders() {
	for (unsigned int i = 0; i < Shaders.size(); i++) {
		IDVD3DXShader *pShader = dynamic_cast<IDVD3DXShader*>(Shaders[i]);
		delete pShader;
	}
}
