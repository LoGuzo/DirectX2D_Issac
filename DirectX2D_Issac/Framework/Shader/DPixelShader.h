#pragma once
// Shader는 이름이 같은 경우는 1개만 생성
class PixelShader : public Shader
{
private:
    friend class ShaderManager;       // factory pattern
    PixelShader(wstring file);
    ~PixelShader();

public:
    void Set() override;

private:
    ID3D11PixelShader* mShader = NULL;   // HLSL을 PS
};