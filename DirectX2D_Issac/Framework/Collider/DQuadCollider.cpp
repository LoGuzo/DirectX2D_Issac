#include "framework.h"
#include "DQuadCollider.h"

QuadCollider::QuadCollider()
{
	WorldBuffer = new MatrixBuffer(0);
	Vertex vertices[5];
	vertices[0].position = Float3(-0.5f, -0.5f, 0.0f);
	vertices[1].position = Float3(-0.5f, +0.5f, 0.0f);
	vertices[2].position = Float3(+0.5f, +0.5f, 0.0f);
	vertices[3].position = Float3(+0.5f, -0.5f, 0.0f);
	vertices[4].position = Float3(-0.5f, -0.5f, 0.0f);
	cVertexBuffer = new VertexBuffer(vertices, sizeof(Vertex), 5);

	//cVertexShader = SHADER->AddVS(L"Color.hlsl");   // 번지
	//cPixelShader = SHADER->AddPS(L"Color.hlsl");   // 번지

	cColorBuffer = new ColorBuffer(11);
}

QuadCollider::~QuadCollider()
{
	SAFE_DELETE(WorldBuffer);
	SAFE_DELETE(cVertexBuffer);
	SAFE_DELETE(cColorBuffer);
}

void QuadCollider::Render()
{
	cVertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	//cVertexShader->Set();                   // VS
	WorldBuffer->SetVS(0);                 // VS
	WorldBuffer->SetPS(0);
	//cPixelShader->Set();                    // PS
	cColorBuffer->SetPS(11);

	DC->Draw(5, 0);
}

void QuadCollider::SetMatrix(Matrix world)
{
	WorldBuffer->Set(world);
}

void QuadCollider::SetColor(float r, float g, float b)
{
	cColorBuffer->SetColor(r, g, b, 1.0f);
}
