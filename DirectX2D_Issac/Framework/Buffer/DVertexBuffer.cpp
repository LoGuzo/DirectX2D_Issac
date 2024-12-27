#include "framework.h"
#include "DVertexBuffer.h"

VertexBuffer::VertexBuffer(void* InData, UINT InStride, UINT InCount)
{
	Stride = InStride;

	HRESULT hr;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	//  D3D11_USAGE_DEFAULT   : ����(0)
	//  D3D11_USAGE_IMMUTABLE : ����(X)
	//  D3D11_USAGE_DYNAMIC   : ����(0)
	//  D3D11_USAGE_STAGING   : ����(X)

	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE; // Dynamic�� ���
	desc.ByteWidth = InStride * InCount;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  // ����,�ε���,Textue,���

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = InData;

	// ��������  -> DECVICE���� VRM�� ��ȯ
	hr = DEVICE->CreateBuffer(&desc, &data, &Buffer); // CPU�ڿ�
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

	//������ ������Ʈ�� �Ʒ� ����� ���
	DC->UpdateSubresource(Buffer, 0, nullptr, data, Stride, count);
}
