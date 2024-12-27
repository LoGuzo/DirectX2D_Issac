#pragma once

class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT InCount);
	~IndexBuffer();

public:
	void Set();

private:
	ID3D11Buffer* Buffer = nullptr;
};