#include "framework.h"
#include "DIndexBuffer.h"

IndexBuffer::IndexBuffer(void* InData, UINT InCount)
{
	HRESULT hr;

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * InCount;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER; // ����,�ε���,���


	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = InData;

	// ��������  -> DECVICE���� VRM�� ��ȯ
	hr = DEVICE->CreateBuffer(&desc, &data, &Buffer); // CPU�ڿ�
	assert(SUCCEEDED(hr));
}

IndexBuffer::~IndexBuffer()
{
	SAFE_RELEASE(Buffer);
}

void IndexBuffer::Set()
{
	DC->IASetIndexBuffer(Buffer, DXGI_FORMAT_R32_UINT, 0);
}
