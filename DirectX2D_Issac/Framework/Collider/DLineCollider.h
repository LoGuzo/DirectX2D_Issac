#pragma once

class LineCollider : public Object
{
public:
	LineCollider();
	~LineCollider();

public:
	void  Update();
	void  Render();

public:
	void  AddLine(float x1, float y1, float x2, float y2);
	void  ClearLine();
	void  EndLine();

public:
	static bool IntersectionLine(Vector2 AP1, Vector2 AP2, Vector2 BP1, Vector2 BP2, Vector2& result); //교차점 

private:
	static  int  IsLeft(Vector2 left, Vector2 right);
	static  bool CheckInterSectionLine(Vector2 A, Vector2 B, Vector2 C, Vector2 D);
	static 	int  CCW(Vector2 p1, Vector2 p2, Vector2 p3);
	static  Vector2 ClosesetPoint(Vector2 start, Vector2 end, Vector2 point);

public:
	int      GetCountLine() { return (int)(Lines.size() / 2); }
	Vector2  GetStartPoint(int no);
	Vector2  GetEndPoint(int no);


private:
	void  CreateVertexBuffer();

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

private:
	vector<Vector2*>    Lines;
};