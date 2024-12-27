#include "framework.h"
#include "DConstantBuffer.h"

ConstantBuffer::~ConstantBuffer()
{
	SAFE_RELEASE(Buffer);
}

void ConstantBuffer::SetVS(UINT slot)
{
	Update();
	DC->VSSetConstantBuffers(slot, 1, &Buffer);
}

void ConstantBuffer::SetPS(UINT slot)
{
	Update();
	DC->PSSetConstantBuffers(slot, 1, &Buffer);
}

void ConstantBuffer::SetCS(UINT slot)
{
}

void ConstantBuffer::SetGS(UINT slot)
{
}

void ConstantBuffer::SetHS(UINT slot)
{
}

void ConstantBuffer::SetDS(UINT slot)
{
}

void ConstantBuffer::SetData(void* InData, UINT InDataSize)
{
	Data = InData;
	DataSize = InDataSize;


	D3D11_BUFFER_DESC      desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));

	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE; // Dynamic일 경우
	desc.ByteWidth = InDataSize;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;  // 정점,인덱스,Textue,상수


	// 메모리주소하고 갯수를 Device를 Buffer를 만듬
	HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, &Buffer);
	assert(SUCCEEDED(hr));
}

void ConstantBuffer::Update()
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, Data, DataSize);

	}
	DC->Unmap(Buffer, 0);
}
