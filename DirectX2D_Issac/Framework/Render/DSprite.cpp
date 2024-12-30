#include "framework.h"
#include "DSprite.h"
#include  <io.h>

Vector2 GlobalScale = Vector2(1.8f, 1.8f);

DSprite::DSprite(wstring InFile)
{
	CreateBuffer(InFile, 0, 0, 0, 0);
	QUAD;
	QUAD->SetShader(L"Texture.hlsl");
}

DSprite::DSprite(wstring InFile, int sx, int sy, int ex, int ey)
{
	CreateBuffer(InFile, sx, sy, ex, ey);
	QUAD;
	QUAD->SetShader(L"Texture.hlsl");
}

DSprite::~DSprite()
{
}

void DSprite::Update()
{
	Matrix S, T, R, P, IP;

	S = MatrixUtil::Scaling(mScale.x * mOffsetSize.x * GlobalScale.x * mDefaultScale.x,
		mScale.y * mOffsetSize.y * GlobalScale.y * mDefaultScale.y, 0.0f);

	T = MatrixUtil::Translation(mPosition.x + mDefaultPos.x, mPosition.y + mDefaultPos.y, 0.0f);
	R = MatrixUtil::RotationRollPitchYaw(mRotation.y, mRotation.x, mRotation.z);
	P = MatrixUtil::Translation(mPivot.x, mPivot.y, 0.0f);
	IP = MatrixUtil::Inverse(P);

	World = S * IP * R * T * P;
}

void DSprite::Render()
{
	QUAD->SetAlignement((UINT)Alignment);
	QUAD->GetMatritxBuffer()->Set(World);
	QUAD->GetSpriteCutBuffer()->Set(mOffset, mOffsetSize, mTextureSize);
	QUAD->SetImageFile(mImageFile);
	QUAD->Render();
}

void DSprite::GUIRender()
{
	string Name = "Sprite";

	// Tree를 하나 생성하고 그 및에 속성이 나타나도록
	if (ImGui::TreeNode((Name + "_Transform").c_str()))
	{
		ImGui::Text(Name.c_str());
		string temp = Name + "_Pos";
		ImGui::DragFloat2(temp.c_str(), (float*)&mPosition, 1.0f);


		temp = Name + "_Scale";
		ImGui::DragFloat2(temp.c_str(), (float*)&mScale, 0.1f);
		ImGui::TreePop();
	}
}

Vector2 DSprite::ScaledTextureSize()
{
	Vector2 size;
	size.x = mTextureSize.x * GlobalScale.x * mScale.x;
	size.y = mTextureSize.y * GlobalScale.y * mScale.y;
	return size;
}

Vector2 DSprite::ScaledOffsetSize()
{
	Vector2 size;
	size.x = mOffsetSize.x * GlobalScale.x * mScale.x * mDefaultScale.x;
	size.y = mOffsetSize.y * GlobalScale.y * mScale.y * mDefaultScale.y;
	return size;
}

void DSprite::SetShader(wstring InFile)
{
	QUAD->SetShader(InFile);
}

void DSprite::SetImageFile(wstring InFile)
{
	mImageFile = InFile;
	mTextureSize = IMAGEMGR->GetSpriteSize(mImageFile);
}

void DSprite::CreateBuffer(wstring InFile, int sx, int sy, int ex, int ey)
{
	IsExistFile(InFile);
	mImageFile = InFile;                 // Image파일명 저장
	IMAGEMGR->AddSprite(InFile);         // SRV의 주소저장

	mOffset = Vector2(sx, sy);          // Image의 시작위치
	Vector2 size = IMAGEMGR->GetSpriteSize(InFile);  // Image의 전체 크기
	mTextureSize = size;
	if (sx == ex && sy == ey)
		mOffsetSize = size;
	else
		mOffsetSize = Vector2(ex - sx, ey - sy);
}

bool DSprite::IsExistFile(wstring file)
{
	string str;
	str.assign(file.begin(), file.end());
	if (_access(str.c_str(), 00) != 0)
	{
		MessageBoxA(NULL, str.c_str(), "File Error", MB_OK);

		assert(SUCCEEDED(false));
		return false;
	}
	return true;
}
