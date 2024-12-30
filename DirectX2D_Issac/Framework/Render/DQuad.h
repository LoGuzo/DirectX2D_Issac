#pragma once

class CVertexBuffer;
class CIndexBuffer;
class CVertexShader;
class CPixelShader;

#define  QUAD DQuad::GetInstance()

class DQuad : public SingleTon<DQuad>
{
private:
	DQuad();
	friend SingleTon;
public:
	~DQuad();
public:
	enum class eAlignment
	{
		CENTER,
		LEFT,
		RIGHT,
		TOP,
		BOT,
		MAX
	};
private:
	struct Vertex // 정점, 2Dor3D내에서의 한점
	{
		XMFLOAT3 position;  // x,y,z(x)
		XMFLOAT2 uv;
	};

public:
	void SetShader(wstring shader);
	void SetAlignement(UINT type)
	{
		Aligement = (eAlignment)type;
	}
	MatrixBuffer* GetMatritxBuffer() { return WorldBuffer; }
	SpriteCutBuffer* GetSpriteCutBuffer() { return cSpriteCutBuffer; }
	ColorBuffer* GetColorBuffer() { return cColorBuffer; }

	void SetImageFile(wstring imageFile);
	void SetSecondImageFile(wstring imageFile);
public:
	void Render();
	void InstanceRender();
private:
	void CreateBuffer();

private:
	eAlignment  Aligement = eAlignment::CENTER;
	ID3D11ShaderResourceView* SRV[5];
	VertexBuffer* cVertexBuffer[5];
	IndexBuffer* cIndexBuffer = nullptr;
	VertexShader* cVertexShader = nullptr;
	PixelShader* cPixelShader = nullptr;
	MatrixBuffer* WorldBuffer = nullptr;
	SpriteCutBuffer* cSpriteCutBuffer = nullptr;
	ColorBuffer* cColorBuffer = nullptr;
};