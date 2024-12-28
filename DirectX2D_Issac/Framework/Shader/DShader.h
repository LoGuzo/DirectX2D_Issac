#pragma once
class Shader
{
private:
    friend class ShaderManager;
public:
    virtual void Set() = 0;
    void OutMessage(wstring InFileName, ID3DBlob* OutError);
};