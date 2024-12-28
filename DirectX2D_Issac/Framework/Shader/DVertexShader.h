#pragma once
class VertexShader : public Shader
{
private:
    friend class ShaderManager;       // factory pattern
    VertexShader(wstring file);
    ~VertexShader();

public:
    void Set() override;

private:
    void CreateInputLayout();

private:
    ID3D11VertexShader* mShader = nullptr;
    ID3D11InputLayout* InputLayout = nullptr;

private:
    ID3D11ShaderReflection* Reflection = nullptr;
    ID3DBlob* Blob;
};