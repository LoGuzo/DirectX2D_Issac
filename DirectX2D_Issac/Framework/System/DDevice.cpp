#include "framework.h"
#include "DDevice.h"

DDevice::DDevice()
{
	InitDevice();
}

DDevice::~DDevice()
{
	SAFE_DELETE(Device);
	SAFE_DELETE(DeviceContext);
	SAFE_DELETE(SwapChain);
	SAFE_DELETE(RenderTargetView);
	SAFE_DELETE(DepthStencilView);
	SAFE_DELETE(DepthStencilBuffer);
	SAFE_DELETE(DepthStencilState);
}

void DDevice::InitDevice()
{
	UINT width = MAIN->GetWidth();
	UINT height = MAIN->GetHeight();

	// 1. D3D11CreateDeviceAndSwapChain()
	//    Device,DeviceContext,Swap 생성
	// 2. RenderTargert View를 Setting
	//    BackBuffer를 생성

	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = MAIN->GetHandle();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = true;

	vector<D3D_FEATURE_LEVEL> feature_level =
	{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,  // 11.0
			D3D_FEATURE_LEVEL_10_1,  // ps4_0,vs_4  GTX750
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3
	};

	D3D_FEATURE_LEVEL  seleted_feature_level;


	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		//		D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT, // 3D+2D(글자)
		D3D11_CREATE_DEVICE_BGRA_SUPPORT, // 3D+2D(글자)
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&SwapChain,
		&Device,
		&seleted_feature_level,   // 지원가능한 우선순위에서 선택된 feature
		&DeviceContext
	);

	assert(SUCCEEDED(hr));
	CreateBackBuffer(width, height);
}

void DDevice::Clear(float r, float g, float b, float alpha)
{
	float clearColor[4] = { r,g,b,alpha };
	SetRenderTarget();

	DeviceContext->ClearRenderTargetView(RenderTargetView, clearColor);
}

void DDevice::Present()
{
	SwapChain->Present(0, 0);
}

void DDevice::ResizeBuffer()
{
	int width = MAIN->GetWidth();
	int height = MAIN->GetHeight();

	if (width < 1 || height < 1)
		return;
	DeleteBuffer();
	//DIRECT->DeleteBackBuffer();
	{
		HRESULT hr = SwapChain->ResizeBuffers(0, (UINT)width, (UINT)height, DXGI_FORMAT_UNKNOWN, 0);
		assert(SUCCEEDED(hr));
	}
	//DIRECT->CreateBackBuffer();
	CreateBackBuffer(width, height);
	SetViewPort();
}

void DDevice::SetOutManager()
{
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	viewport.Width = (float)MAIN->GetWidth();
	viewport.Height = (float)MAIN->GetHeight();
	DeviceContext->RSSetViewports(1, &viewport);
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, DepthStencilView);
}

void DDevice::SetViewPort()
{
	D3D11_VIEWPORT viewport;
	viewport.Width = (float)MAIN->GetWidth();
	viewport.Height = (float)MAIN->GetHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	DC->RSSetViewports(1, &viewport);
}

void DDevice::CreateBackBuffer(int width, int height)
{
	HRESULT hr;

	// 2D : GetBackBuffer And Create RTV
	{
		ID3D11Texture2D* backbufferPointer;
		hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backbufferPointer);
		assert(SUCCEEDED(hr));

		hr = GetDevice()->CreateRenderTargetView(backbufferPointer, NULL, &RenderTargetView);
		assert(SUCCEEDED(hr));
		SAFE_RELEASE(backbufferPointer);
	}

	//Create DSV
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipSlice = 0;

		hr = GetDevice()->CreateDepthStencilView(DepthStencilBuffer, &desc, &DepthStencilView);
		assert(SUCCEEDED(hr));
	}
}

void DDevice::SetRenderTarget()
{
	DC->OMSetRenderTargets(1, &RenderTargetView, NULL);
}

void DDevice::DeleteBuffer()
{
	DC->OMSetRenderTargets(0, 0, 0);

	SAFE_RELEASE(RenderTargetView);
	SAFE_RELEASE(DepthStencilView);
	SAFE_RELEASE(DepthStencilBuffer);
	SAFE_RELEASE(DepthStencilState);
}
