#pragma once
// Shader�� �̸��� ���� ���� 1���� ����
class PixelShader : public Shader
{
private:
    friend class ShaderManager;       // factory pattern
    PixelShader(wstring file);
    ~PixelShader();

public:
    void Set() override;

private:
    ID3D11PixelShader* mShader = NULL;   // HLSL�� PS
};