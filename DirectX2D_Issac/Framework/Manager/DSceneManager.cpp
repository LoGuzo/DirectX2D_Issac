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

	wstring temp; // = L"���� Test";
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

		// 1. ����ȭ�� ��ǥ�� �Ѱ����� ��� ó���ؾ� �ϴ���?
		//  WRAP   : ���� �ȼ��� �������� ä���
		//  MIRROR : ������   �ȼ��� �������� ä���
		//  CLAMP  : �Ǹ����� �ȼ��� �������� ä���
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		// 2.  �ܰ��� ���� ���� ó��
		desc.BorderColor[0] = 1;
		desc.BorderColor[1] = 1;
		desc.BorderColor[2] = 1;
		desc.BorderColor[3] = 1;
		// 3. ����/���� �����͸� ���ϴ� Falg
		desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		// 4. ȭ�� Ȯ��/��ҽ��� Flag  : �̸� 1/4ũ��� �̹����� ����
		//    MIN : ���
		//    MAG : Ȯ��
		//    LINEAR : 2���� �ȼ��� ��հ�
		//    POINT  : 2���� �ȼ��� �ϳ��� ���

		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		desc.MaxAnisotropy = 16;
		desc.MinLOD = 0;
		desc.MaxLOD = D3D11_FLOAT32_MAX;
	}

	//LOD(Level Of Detail) : ī�޶���� �Ÿ��� ���� ����Ƽ�� �ٸ��� ǥ���ϴ� ���
	DEVICE->CreateSamplerState(&desc, &SamplerState);
	DC->PSSetSamplers(0, 1, &SamplerState);
}

void SceneManager::CreateBlendState()
{
	D3D11_BLEND_DESC desc = {};

	desc.AlphaToCoverageEnable = false;    // �ڿ� �׵θ� ����
	desc.IndependentBlendEnable = true;   // ���� ȥ��

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
		desc.FillMode = D3D11_FILL_SOLID;  // ���θ� ä��°�
		desc.CullMode = D3D11_CULL_NONE;   // ��/�� �ٲپ ���� rendering
		desc.FrontCounterClockwise = false;
	}
	HRESULT hr = DEVICE->CreateRasterizerState(&desc, &RasterState);
	assert(SUCCEEDED(hr));

	// RS�ܰ�
	DC->RSSetState(RasterState);
}