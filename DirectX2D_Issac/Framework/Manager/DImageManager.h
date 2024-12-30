#pragma once
#define  IMAGEMGR DImageManager::GetInstance()

class DImageManager : public SingleTon<DImageManager>
{
public:
    ~DImageManager();

public:
    ID3D11ShaderResourceView* AddSprite(wstring InFileName);
    ID3D11ShaderResourceView* AddSprite(wstring InFileName, ID3D11ShaderResourceView* rtv);
    ID3D11ShaderResourceView* GetSprite(wstring InFileName);
    Vector2  GetSpriteSize(wstring InFileName);

private:
    struct SpriteResource
    {
        ID3D11ShaderResourceView* SRV;
        Vector2 size = Vector2(0, 0);
    };
    map<wstring, SpriteResource*>  Images;
};