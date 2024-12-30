#include "framework.h"
#include "DQuad.h"

DQuad::DQuad()
{
	CreateBuffer();
	WorldBuffer = new MatrixBuffer(0);
	cSpriteCutBuffer = new SpriteCutBuffer(10);
	cColorBuffer = new ColorBuffer(11);
}

DQuad::~DQuad()
{
	SAFE_DELETE(WorldBuffer);
	SAFE_DELETE(cSpriteCutBuffer);
	SAFE_DELETE(cColorBuffer);
}

void DQuad::SetShader(wstring shader)
{
	cVertexShader = SHADER->AddVS(shader);
	cPixelShader = SHADER->AddPS(shader);
}

void DQuad::SetImageFile(wstring imageFile)
{
	SRV[0] = IMAGEMGR->GetSprite(imageFile);
}

void DQuad::SetSecondImageFile(wstring imageFile)
{
	SRV[1] = IMAGEMGR->GetSprite(imageFile);
}

void DQuad::Render()
{
	WorldBuffer->SetVS(0);
	cVertexBuffer[(UINT)Aligement]->Set();

	cVertexShader->Set();
	cPixelShader->Set();
	cColorBuffer->Set();
	cSpriteCutBuffer->Set();

	DC->PSSetShaderResources(0, 1, &SRV[0]);
	DC->DrawIndexed(6, 0, 0);
}

void DQuad::InstanceRender()
{
	WorldBuffer->SetVS(0);
	cVertexBuffer[(UINT)Aligement]->Set();
}

void DQuad::CreateBuffer()
{
	UINT indices[] = { 0,1,3, 3,1,2 };
	cIndexBuffer = new IndexBuffer(indices, 6);
	cIndexBuffer->Set();

	// 정점을 만들고 VertexBuffer를 생성하기
	Vertex vertices[4];

	// 1. Center
	{
		vertices[0].position = Float3(-0.5f, -0.5f, 0.0f);      // 0
		vertices[1].position = Float3(-0.5f, +0.5f, 0.0f);      // 1
		vertices[2].position = Float3(+0.5f, +0.5f, 0.0f);      // 2
		vertices[3].position = Float3(+0.5f, -0.5f, 0.0f);      // 3

		vertices[0].uv = Float2(0, 1);
		vertices[1].uv = Float2(0, 0);
		vertices[2].uv = Float2(1, 0);
		vertices[3].uv = Float2(1, 1);
		cVertexBuffer[0] = new VertexBuffer(vertices, sizeof(Vertex), 4);
	}


	// 2. Left Center
	{
		vertices[0].position = Float3(0.0f, -0.5f, 0.0f);      // 0
		vertices[1].position = Float3(0.0f, +0.5f, 0.0f);      // 1
		vertices[2].position = Float3(1.0f, +0.5f, 0.0f);      // 2
		vertices[3].position = Float3(1.0f, -0.5f, 0.0f);      // 3
		cVertexBuffer[1] = new VertexBuffer(vertices, sizeof(Vertex), 4);
	}

	// 3. Right Center
	{
		vertices[0].position = Float3(-1.0f, -0.5f, 0.0f);      // 0
		vertices[1].position = Float3(-1.0f, +0.5f, 0.0f);      // 1
		vertices[2].position = Float3(0.0f, +0.5f, 0.0f);      // 2
		vertices[3].position = Float3(0.0f, -0.5f, 0.0f);      // 3
		cVertexBuffer[2] = new VertexBuffer(vertices, sizeof(Vertex), 4);
	}


	// 3. Top Center
	{
		vertices[0].position = Float3(-0.5f, -1.0f, 0.0f);      // 0
		vertices[1].position = Float3(-0.5f, +0.0f, 0.0f);      // 1
		vertices[2].position = Float3(+0.5f, +0.0f, 0.0f);      // 2
		vertices[3].position = Float3(+0.5f, -1.0f, 0.0f);      // 3
		cVertexBuffer[3] = new VertexBuffer(vertices, sizeof(Vertex), 4);
	}


	// 4. Bottom Center
	{
		vertices[0].position = Float3(-0.5f, 0.0f, 0.0f);      // 0
		vertices[1].position = Float3(-0.5f, 1.0f, 0.0f);      // 1
		vertices[2].position = Float3(+0.5f, 1.0f, 0.0f);      // 2
		vertices[3].position = Float3(+0.5f, 0.0f, 0.0f);      // 3
		cVertexBuffer[4] = new VertexBuffer(vertices, sizeof(Vertex), 4);
	}
}
