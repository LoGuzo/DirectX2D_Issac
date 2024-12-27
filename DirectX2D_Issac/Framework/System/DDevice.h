#pragma once
class DDevice : public SingleTon<DDevice>
{
private:
	DDevice();
	friend SingleTon;

public:
	~DDevice();

public:    // DirectX
	ID3D11Device* GetDevice() { return Device; }
	ID3D11DeviceContext* GetDeviceContext() { return DeviceContext; }
	IDXGISwapChain* GetSwapChain() { return SwapChain; }

public:
	void InitDevice();
	void Clear(float r, float g, float b, float alpha);
	void Present();
	void ResizeBuffer();

private:
	void SetOutManager();
	void SetViewPort();
	void CreateBackBuffer(int width, int height);
	void SetRenderTarget();

private:
	void DeleteBuffer();

private:  // DirectX 초기화
	ID3D11Device* Device = nullptr;   // CPU의 자원
	ID3D11DeviceContext* DeviceContext = nullptr;   // GPU의 자원
	IDXGISwapChain* SwapChain = nullptr;   // Back-Front

private:  // 2D용 Buffer
	ID3D11RenderTargetView* RenderTargetView = nullptr;   // rendering target

private:  // 3D용 Depth Buffer
	ID3D11DepthStencilView* DepthStencilView = nullptr;
	ID3D11Texture2D* DepthStencilBuffer = nullptr;
	ID3D11DepthStencilState* DepthStencilState = nullptr;
};

