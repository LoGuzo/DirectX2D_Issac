#pragma once
class VertexBuffer
{
public:
	VertexBuffer(void* data, UINT InStride, UINT InCount);
	~VertexBuffer();
public:
	void Set(D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void Set(UINT slot, D3D11_PRIMITIVE_TOPOLOGY type = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
public:
	void Update(void* data, UINT count);

private:
	ID3D11Buffer* Buffer = nullptr;
	UINT  Stride = 0;
};

