#include "framework.h"
#include "DImageManager.h"
#include  <io.h>

DImageManager::~DImageManager()
{
	for (auto a : Images)
	{
		SAFE_RELEASE(a.second->SRV);
	}
	Images.clear();
}

ID3D11ShaderResourceView* DImageManager::AddSprite(wstring InFileName)
{
	// 데이터가 존재 하면 return
	if (Images.find(InFileName) != Images.end())
	{
		return Images[InFileName]->SRV;
	}
	SpriteResource* pSprite = new SpriteResource();

	DirectX::ScratchImage image;
	DirectX::LoadFromWICFile(InFileName.c_str(), WIC_FLAGS_IGNORE_SRGB, nullptr, image);
	HRESULT hr;
	hr = DirectX::CreateShaderResourceView(DEVICE, image.GetImages(),
		image.GetImageCount(), image.GetMetadata(), &pSprite->SRV);

	float w = (float)image.GetMetadata().width;
	float h = (float)image.GetMetadata().height;
	pSprite->size = Vector2(w, h);

	assert(SUCCEEDED(hr));

	// Map에 저장
	Images.insert(make_pair(InFileName, pSprite));
	return pSprite->SRV;
}

ID3D11ShaderResourceView* DImageManager::AddSprite(wstring InFileName, ID3D11ShaderResourceView* rtv)
{
	// 데이터가 존재 하면 return
	if (Images.find(InFileName) != Images.end())
	{
		return Images[InFileName]->SRV;
	}
	SpriteResource* pSprite = new SpriteResource();
	pSprite->SRV = rtv;
	pSprite->size = Vector2(0, 0);

	// Map에 저장
	Images.insert(make_pair(InFileName, pSprite));
	return pSprite->SRV;
}

ID3D11ShaderResourceView* DImageManager::GetSprite(wstring InFileName)
{
	ID3D11ShaderResourceView* value = nullptr;

	if (Images.find(InFileName) == Images.end())
		return value;

	value = Images[InFileName]->SRV;
	return value;
}

Vector2 DImageManager::GetSpriteSize(wstring InFileName)
{
	Vector2 value = Vector2(0, 0);
	if (Images.find(InFileName) == Images.end())
		return value;

	value = Images[InFileName]->size;
	return value;
}
