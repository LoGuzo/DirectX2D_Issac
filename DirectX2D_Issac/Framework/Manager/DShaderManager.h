#pragma once
#define  SHADER ShaderManager::GetInstance()
class ShaderManager : public SingleTon<ShaderManager>
{
private:
    ShaderManager();
    friend SingleTon;

public:
    ~ShaderManager();

public:
    class VertexShader* AddVS(wstring file);
    class PixelShader* AddPS(wstring file);

private:
    unordered_map<wstring, class Shader*> Shaders;
};
