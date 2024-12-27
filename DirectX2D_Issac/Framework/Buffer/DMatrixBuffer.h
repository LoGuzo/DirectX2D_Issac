#pragma once
class MatrixBuffer : public ConstantBuffer
{
public:
	MatrixBuffer(int InSlot);

public:
	void  Set(Matrix InValue);
	void  Show(Matrix InMatrix);
public:
	void  MakeProjection();
	void  MakeOrthoGraphic();
	void  MakeView();

private:
	struct FData
	{
		Matrix matrix;
	};
private:
	FData Data;
	int   Slot = 0;
};

