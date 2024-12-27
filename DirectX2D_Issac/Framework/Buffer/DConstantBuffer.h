#pragma once
class ConstantBuffer
{
public:
	ConstantBuffer() = default;
	~ConstantBuffer();

public: // VS,PS,
	void  SetVS(UINT slot);  // VertexShader
	void  SetPS(UINT slot);  // PixelShader
	void  SetCS(UINT slot);  // Computing Shader
	void  SetGS(UINT slot);  // Geometry Shader
	void  SetHS(UINT slot);  // Hull Shader
	void  SetDS(UINT slot);  // Domain Shader

protected:
	void  SetData(void* InData, UINT InDataSize);
private:
	void  Update();
private:
	ID3D11Buffer* Buffer = nullptr;
	void* Data = nullptr;
	UINT          DataSize = 0;

};

