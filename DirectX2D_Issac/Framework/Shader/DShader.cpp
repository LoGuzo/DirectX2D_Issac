#include "framework.h"
#include "DShader.h"

// HLSL�� ���̳ʸ� �������� ������ ���°��� ǥ��
void Shader::OutMessage(wstring InFileName, ID3DBlob* OutError)
{
    string message = (char*)OutError->GetBufferPointer();
    MessageBoxA(NULL, message.c_str(), "HLSL ����", MB_OK);
}