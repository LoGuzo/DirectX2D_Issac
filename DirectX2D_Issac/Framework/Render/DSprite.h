#pragma once

class DQuad;

class DSprite
{
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
public:
	DSprite(wstring InFile);
	DSprite(wstring InFile, int sx, int sy, int ex, int ey);
	~DSprite();

public:
	void Update();
	void Render();
	void GUIRender();

public:
	Vector2& Pos() { return mPosition; }
	Vector2& Scale() { return mScale; }
	Vector3& Rotation() { return mRotation; }
	Vector2& Pivot() { return mPivot; }

public:
	Vector2& Offset() { return mOffset; }
	Vector2& OffsetSize() { return mOffsetSize; }
	Vector2& TextureSize() { return mTextureSize; }
	Vector2& DefaultPos() { return mDefaultPos; }
	Vector2& DefaultScale() { return mDefaultScale; }

	Vector2  ScaledTextureSize();
	Vector2  ScaledOffsetSize();

public:
	void     SetShader(wstring InFile);
	void     SetImageFile(wstring InFile);
	void     SetAlignment(eAlignment type) { Alignment = type; };
	Matrix& GetMatrix() { return World; }

private:
	void     CreateBuffer(wstring InFile, int sx, int sy, int ex, int ey);

private:
	bool     IsExistFile(wstring file);

private:
	Vector2  mPosition = Vector2(0, 0);      // 위치
	Vector2  mScale = Vector2(1, 1);      // 크기
	Vector3  mRotation = Vector3(0, 0, 0);
private:
	Vector2  mOffset = Vector2(0, 0);     // Image의 시작위치
	Vector2  mOffsetSize = Vector2(0, 0);     // Image의 그림그려질 크기
	Vector2  mPivot = Vector2(0, 0);     // Image의 시작위치
	Vector2  mTextureSize = Vector2(0, 0);     // Image의 크기
	wstring  mImageFile;
private:
	Vector2  mDefaultPos = Vector2(0, 0);
	Vector2  mDefaultScale = Vector2(1, 1);
private:
	Matrix  World;
	eAlignment  Alignment = eAlignment::CENTER;
};