#include "framework.h"
#include "DVertexBuffer.h"

VertexBuffer::VertexBuffer(void* InData, UINT InStride, UINT InCount)
{
	Stride = InStride;

	HRESULT hr;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	//  D3D11_USAGE_DEFAULT   : 수정(0)
	//  D3D11_USAGE_IMMUTABLE : 수정(X)
	//  D3D11_USAGE_DYNAMIC   : 수정(0)
	//  D3D11_USAGE_STAGING   : 수정(X)

	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE; // Dynamic일 경우
	desc.ByteWidth = InStride * InCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  // 정점,인덱스,Textue,상수

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = InData;

	// 지역변수  -> DECVICE내에 VRM에 변환
	hr = DEVICE->CreateBuffer(&desc, &data, &Buffer); // CPU자원
	assert(SUCCEEDED(hr));
}

VertexBuffer::~VertexBuffer()
{
	SAFE_RELEASE(Buffer);
}

void VertexBuffer::Set(D3D11_PRIMITIVE_TOPOLOGY type)
{
	UINT  offset = 0;

	DC->IASetVertexBuffers(0, 1, &Buffer, &Stride, &offset);
	DC->IASetPrimitiveTopology(type);
}

void VertexBuffer::Set(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type)
{
	UINT  offset = 0;

	DC->IASetVertexBuffers(slot, 1, &Buffer, &Stride, &offset);
	DC->IASetPrimitiveTopology(type);
}

void VertexBuffer::Update(void* data, UINT count)
{
	D3D11_MAPPED_SUBRESOURCE subResource;
	DC->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{
		memcpy(subResource.pData, data, Stride * count);

	}
	DC->Unmap(Buffer, 0);

	return;

	//간단한 업데이트는 아래 방법을 사용
	DC->UpdateSubresource(Buffer, 0, nullptr, data, Stride, count);
}
