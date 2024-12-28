#include "framework.h"
#include "DPixelShader.h"

PixelShader::PixelShader(wstring file)
{
    HRESULT hr;

    ID3DBlob* blob = nullptr;
    ID3DBlob* outerror = nullptr;
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    hr = D3DCompileFromFile(file.c_str(), nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS",
        "ps_5_0", flags, 0, &blob, &outerror);


    assert(SUCCEEDED(hr));

    DEVICE->CreatePixelShader(blob->GetBufferPointer(),
        blob->GetBufferSize(), nullptr, &mShader);
    assert(SUCCEEDED(hr));

    SAFE_RELEASE(blob);
    SAFE_RELEASE(outerror);

}
PixelShader::~PixelShader()
{
    SAFE_RELEASE(mShader);
}

void PixelShader::Set()
{
    DC->PSSetShader(mShader, nullptr, 0);
}
