#include "framework.h"
#include "DSceneManager.h"

SceneManager::SceneManager()
{
	CreateSamplerState();
	CreateBlendState();
	CreateRasterState();
}

SceneManager::~SceneManager()
{
	SAFE_RELEASE(SamplerState);
	SAFE_RELEASE(BlendState);
	SAFE_DELETE(UIScene);

	for (auto a : Scenes)
		SAFE_DELETE(a);
	Scenes.erase(Scenes.begin(), Scenes.end());
}

void SceneManager::InitScene()
{
	
}

void SceneManager::Update()
{
	for (UINT i = 0; i < Scenes.size(); i++)
	{
		if (Scenes[i]->IsActive())
		{
			CurrentScene = Scenes[i];
			Scenes[i]->Update();
		}

		if (Scenes[i]->GetName() == PrevScene)
			Scenes[i]->Update();
	}

	if (UIScene)
	{
		if (UIScene->IsActive())
			UIScene->Update();
	}
}

void SceneManager::Render()
{
	for (UINT i = 0; i < Scenes.size(); i++)
	{
		if (Scenes[i]->IsActive())
			Scenes[i]->Render();
		if (Scenes[i]->GetName() == PrevScene)
			Scenes[i]->Render();
	}
	if (UIScene)
	{
		if (UIScene->IsActive())
			UIScene->Render();
	}
}

void SceneManager::GUIRender()
{
	for (UINT i = 0; i < Scenes.size(); i++)
	{
		if (Scenes[i]->IsActive())
			Scenes[i]->GUIRender();
	}
	if (UIScene)
	{
		if (UIScene->IsActive())
			UIScene->GUIRender();
	}
}

void SceneManager::PostRender()
{
	for (UINT i = 0; i < Scenes.size(); i++)
	{
		if (Scenes[i]->IsActive())
			Scenes[i]->PostRender();
	}

	wstring temp; // = L"글자 Test";
	string  temp2 = CurrentScene->GetName();
	if (temp2.size() > 0)
		temp.assign(temp2.begin(), temp2.end());

	DIRECT->GetDC()->BeginDraw();
	{
		DIRECT->RenderText(temp, Vector2(100, 50), 255, 0, 0, 40.0f);
	}
	DIRECT->GetDC()->EndDraw();
}

void SceneManager::ChangeScene(string InName)
{
}

void SceneManager::ThreadStart()
{
}

void SceneManager::ThreadSound()
{
}

void SceneManager::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	{
		ZeroMemory(&desc, sizeof(desc));

		// 1. 정규화된 좌표를 넘겼을때 어떻게 처리해야 하는지?
		//  WRAP   : 원본 픽셀로 나머지를 채운다
		//  MIRROR : 인접한   픽셀로 나머지를 채운다
		//  CLAMP  : 맨마지막 픽셀로 나머지를 채운다
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		// 2.  외곽선 색상에 대한 처리
		desc.BorderColor[0] = 1;
		desc.BorderColor[1] = 1;
		desc.BorderColor[2] = 1;
		desc.BorderColor[3] = 1;
		// 3. 이전/현재 데이터를 비교하는 Falg
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		// 4. 화면 확대/축소시의 Flag  : 미리 1/4크기로 이미지를 구성
		//    MIN : 축소
		//    MAG : 확대
		//    LINEAR : 2개의 픽셀의 평균값
		//    POINT  : 2개의 픽셀이 하나를 폐기

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.MaxAnisotropy = 16;
		desc.MinLOD = 0;
		desc.MaxLOD = D3D11_FLOAT32_MAX;
	}

	//LOD(Level Of Detail) : 카메라와의 거리에 따라서 퀄리티를 다르게 표현하는 기술
	DEVICE->CreateSamplerState(&desc, &SamplerState);
	DC->PSSetSamplers(0, 1, &SamplerState);
}

void SceneManager::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};

	desc.AlphaToCoverageEnable = false;    // 뒤에 테두리 제거
	desc.IndependentBlendEnable = true;   // 알파 혼합

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	DEVICE->CreateBlendState(&desc, &BlendState);

	float blendFactor[4] = {};
	DC->OMSetBlendState(BlendState, blendFactor, 0xffffffff);
}

void SceneManager::CreateRasterState()
{
	D3D11_RASTERIZER_DESC desc;
	{
		ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
		desc.FillMode = D3D11_FILL_SOLID;  // 내부를 채우는것
		desc.CullMode = D3D11_CULL_NONE;   // 앞/뒤 바꾸어도 전부 rendering
		desc.FrontCounterClockwise = false;
	}
	HRESULT hr = DEVICE->CreateRasterizerState(&desc, &RasterState);
	assert(SUCCEEDED(hr));

	// RS단계
	DC->RSSetState(RasterState);
}