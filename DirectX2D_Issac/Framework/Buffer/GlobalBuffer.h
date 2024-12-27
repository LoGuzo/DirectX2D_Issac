#pragma once
class DSpriteCutBuffer : public ConstantBuffer
{
public:
	DSpriteCutBuffer(int InSlot = 10)
	{
		// 상수버퍼 생성
		this->SetData(&Data, sizeof(FData));
		Slot = InSlot;

	};
public:
	void Set(Vector2 offset, Vector2 offsetSize, Vector2 imageSize)
	{
		Data.Offset.x = offset.x / imageSize.x;
		Data.Offset.y = offset.y / imageSize.y;

		Data.OffsetSize.x = offsetSize.x / imageSize.x;
		Data.OffsetSize.y = offsetSize.y / imageSize.y;

		SetVS(Slot);
		SetPS(Slot);
	}
	void Set()
	{
		SetVS(Slot);
		SetPS(Slot);
	}

private:
	struct FData
	{
		Vector2 Offset = Vector2(0, 0);
		Vector2 OffsetSize = Vector2(0, 0);
	};
private:
	FData Data;
	int   Slot = 10;
};

class CColorBuffer : public ConstantBuffer
{
public:
	CColorBuffer(int InSlot = 11)
	{
		// 상수버퍼 생성
		this->SetData(&Data, sizeof(FData));
		Slot = InSlot;

	};
public:
	void  SetColor(float r, float g, float b, float alpha)
	{
		Data.color = Float4(r, g, b, alpha);
		Set();
	}
	void Set()
	{
		SetVS(Slot);
		SetPS(Slot);
	}
	void Set(int Pass)
	{
		Data.Pass = Pass;
		Set();
	}
	void Set(int Pass, Float4 color)
	{
		Data.Pass = Pass;
		Data.color = color;
		Set();
	}
	void Set(int Pass, Float4 color, float Time)
	{
		Data.Pass = Pass;
		Data.color = color;
		Data.Time = Time;
		Set();
	}
	void Set(int Pass, Float4 color, float Time, float Time2)
	{
		Data.Pass = Pass;
		Data.color = color;
		Data.Time = Time;
		Data.Time2 = Time2;
		Set();
	}
	void Set(int Pass, Float4 color, float Time, float Time2, float Time3)
	{
		Data.Pass = Pass;
		Data.color = color;
		Data.Time = Time;
		Data.Time2 = Time2;
		Data.Time3 = Time3;
		Set();
	}
private:
	struct FData
	{
		Float4 color = Float4(0.0f, 0.0f, 0.0f, 0.5f);
		int    Pass = 0;
		float  Time = 0.0f;
		float  Time2 = 0.0f;
		float  Time3 = 0.0f;
	};
private:
	FData Data;
	int   Slot = 11;
};