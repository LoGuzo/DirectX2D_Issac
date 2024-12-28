#pragma once

#define  QUADCOLLIDER QuadCollider::GetInstance()

class QuadCollider : public SingleTon<QuadCollider>
{
private:
	QuadCollider();
	friend SingleTon;
public:
	~QuadCollider();
public:
	void Render();
public:
	void SetMatrix(Matrix world);
	void SetColor(float r, float g, float b);

private:
	struct Vertex // 정점, 2Dor3D내에서의 한점
	{
		XMFLOAT3 position;  // x,y,z(x)
	};
private:
	VertexBuffer* cVertexBuffer = nullptr;
	VertexShader* cVertexShader = nullptr;
	PixelShader* cPixelShader = nullptr;
	MatrixBuffer* WorldBuffer = nullptr;
	ColorBuffer* cColorBuffer = nullptr;
};