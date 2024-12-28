#include "framework.h"
#include "DVertexShader.h"

VertexShader::VertexShader(wstring file)
{
    HRESULT hr;

    ID3DBlob* outerror = nullptr;
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    hr = D3DCompileFromFile(file.c_str(), nullptr,
        D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS",
        "vs_5_0", flags, 0, &Blob, &outerror);

    if (outerror)
    {
        OutMessage(file, outerror);
        assert(false);
    }

    assert(SUCCEEDED(hr));

    DEVICE->CreateVertexShader(Blob->GetBufferPointer(),
        Blob->GetBufferSize(), nullptr, &mShader);
    assert(SUCCEEDED(hr));
    SAFE_RELEASE(outerror);

    CreateInputLayout();
    SAFE_RELEASE(Blob);
    SAFE_RELEASE(Reflection);
}

VertexShader::~VertexShader()
{
    SAFE_RELEASE(mShader);
    SAFE_RELEASE(InputLayout);
}

void VertexShader::Set()
{
    DC->IASetInputLayout(InputLayout);
    DC->VSSetShader(mShader, nullptr, 0);
}
// HLSL�� �������� Blob�� relection�Ͽ� Layout���� ��Ŵ
// �ø�ƽ���� Vector3�� ���� POSITION���� �ݵ�� ����
// DrawInstanced()����  �ø�ƽ  INSTANCE����  �ݵ�� ����
void VertexShader::CreateInputLayout()
{
    HRESULT hr;

    hr = D3DReflect(Blob->GetBufferPointer(), Blob->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)&Reflection);

    assert(SUCCEEDED(hr));

    D3D11_SHADER_DESC shaderDesc;
    Reflection->GetDesc(&shaderDesc);

    vector<D3D11_INPUT_ELEMENT_DESC> inputLayouts;
    inputLayouts.reserve(shaderDesc.InputParameters);

    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        Reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask < 2)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask < 4)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask < 8)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask < 16)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        string temp = paramDesc.SemanticName;

        if (temp == "POSITION")
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        int n = temp.find_first_of('_');
        temp = temp.substr(0, n);

        if (temp == "INSTANCE")
        {
            elementDesc.InputSlot = 1;
            elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
            elementDesc.InstanceDataStepRate = 1;
        }

        inputLayouts.push_back(elementDesc);
    }

    hr = DEVICE->CreateInputLayout(inputLayouts.data(), inputLayouts.size(),
        Blob->GetBufferPointer(), Blob->GetBufferSize(),
        &InputLayout);
    assert(SUCCEEDED(hr));
}
