#include "Framework.h"
#include "DShaderManager.h"

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
    for (pair<wstring, Shader*> shader : Shaders)
        delete shader.second;  // Shader
    Shaders.clear();
}

VertexShader* ShaderManager::AddVS(wstring file)
{
    wstring key = file + L"VS";
    if (Shaders.count(key) > 0)
        return (VertexShader*)Shaders[key];
    wstring path = L"Shaders/" + file;

    //Shaders.insert(make_pair(key, new CVertexShader(path)));

    Shaders[key] = new VertexShader(path);

    return (VertexShader*)Shaders[key];
}
// Pixel/Vertex 동일파일
PixelShader* ShaderManager::AddPS(wstring file)
{
    wstring key = file + L"PS";
    if (Shaders.count(key) > 0)
        return (PixelShader*)Shaders[key];
    wstring path = L"Shaders/" + file;
    Shaders[key] = new PixelShader(path);

    return (PixelShader*)Shaders[key];
}
