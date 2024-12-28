#include "framework.h"
#include "DShader.h"

// HLSL에 바이너리 컴파일중 에러가 나온곳을 표시
void Shader::OutMessage(wstring InFileName, ID3DBlob* OutError)
{
    string message = (char*)OutError->GetBufferPointer();
    MessageBoxA(NULL, message.c_str(), "HLSL 에러", MB_OK);
}