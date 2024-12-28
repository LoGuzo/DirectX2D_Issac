#include "framework.h"
#include "DLineCollider.h"

#define   dot(u,v)   ( (u).x*(v).x + (u).y*(v).y)  // AdotB   = |A*B|cos() ����
#define   cross(u,v) ( (u).x*(v).y - (u).y*(v).x)  // AcrossB = |A*B|sin() ����

LineCollider::LineCollider()
{
	WorldBuffer = new MatrixBuffer(0);
	cVertexShader = SHADER->AddVS(L"Color.hlsl");   // ����
	cPixelShader = SHADER->AddPS(L"Color.hlsl");   // ����
	cColorBuffer = new ColorBuffer(0);
}

LineCollider::~LineCollider()
{
	SAFE_DELETE(cVertexBuffer);
	SAFE_DELETE(WorldBuffer);
	SAFE_DELETE(cColorBuffer);
	ClearLine();
}

void LineCollider::Update()
{
}

void LineCollider::Render()
{
	cVertexBuffer->Set(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	cVertexShader->Set();                   // VS
	WorldBuffer->SetVS(0);                 // VS
	WorldBuffer->SetPS(0);
	cPixelShader->Set();                    // PS
	cColorBuffer->SetColor(0, 1, 0, 1);
	cColorBuffer->SetPS(11);

	DC->Draw((UINT)Lines.size(), 0);
}

void LineCollider::AddLine(float x1, float y1, float x2, float y2)
{
	Vector2* point = new Vector2(x1, y1);
	Lines.push_back(point);
	point = new Vector2(x2, y2);
	Lines.push_back(point);
}

void LineCollider::ClearLine()
{
	for (auto line : Lines)
	{
		SAFE_DELETE(line);
	}
	Lines.erase(Lines.begin(), Lines.end());
}

void LineCollider::EndLine()
{
	CreateVertexBuffer();
}

bool LineCollider::IntersectionLine(Vector2 AP1, Vector2 AP2, Vector2 BP1, Vector2 BP2, Vector2& result)
{
	double t;
	double s;
	// cross
	double under = (BP2.y - BP1.y) * (AP2.x - AP1.x) -
		(BP2.x - BP1.x) * (AP2.y - AP1.y);

	if (!CheckInterSectionLine(AP1, AP2, BP1, BP2))
		return false;

	// ������ ������ Ȯ���ϴ� Check
	if (under == 0)
	{
		// CCW�� �̿��Ͽ� Check
		float x1 = AP2.x - AP1.x;
		float y1 = AP2.y - AP1.y;

		float x2 = BP1.x - AP1.x;
		float y2 = BP1.y - AP1.y;

		Vector2 v1 = Vector2(x1, y1);
		Vector2 v2 = Vector2(x2, y2);

		float c = cross(v1, v2);

		// Intersection 2���� ����
		if (c == 0)
		{
			Vector2 A = ClosesetPoint(AP1, AP2, BP1);
			Vector2 B = ClosesetPoint(AP1, AP2, BP2);

			if (dot(v1, v2) > 0)
				result = B;
			else
				result = A;
			return true;
		}
		return false;
	}

	double _t = (double)(BP2.x - BP1.x) * (AP1.y - BP1.y) - (BP2.y - BP1.y) * (AP1.x - BP1.x);
	double _s = (double)(AP2.x - AP1.x) * (AP1.y - BP1.y) - (AP2.y - AP1.y) * (AP1.x - BP1.x);

	t = _t / under;
	s = _s / under;


	if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0)
		return false;
	if (_t == 0 && _s == 0) return false;

	result.x = (float)(AP1.x + t * (double)(AP2.x - AP1.x));
	result.y = (float)(AP1.y + t * (double)(AP2.y - AP1.y));

	return true;
}

// right�� left ���� ũ�� true�� ��ȯ�մϴ�.
int LineCollider::IsLeft(Vector2 left, Vector2 right)
{
	int ret;
	if (left.x == right.x)
	{
		ret = (left.y <= right.y);
	}
	else
	{
		ret = (left.x <= right.x);
	}
	return ret;
}

bool LineCollider::CheckInterSectionLine(Vector2 A, Vector2 B, Vector2 C, Vector2 D)
{
	int ret;
	// l1(A-B)�� �������� l2(C-D)�� �����ϴ� �� Ȯ���Ѵ�.
		int l1_l2 = CCW(A, B, C) * CCW(A, B, D);
	// l2�� �������� l1�� �����ϴ� �� Ȯ���Ѵ�.
		int l2_l1 = CCW(C, D, A) * CCW(C, D, B);

	// l1 �� l2�� ������ �� �ִ� ���
	if (l1_l2 == 0 && l2_l1 == 0)
	{
		// Line1�� ���� ũ�� ������ p1 < p2 ������ �����.
		if (IsLeft(B, A)) swap(A, B);
		// Line2�� ���� ũ�� ������ p1 < p2 ������ �����.
		if (IsLeft(D, C)) swap(C, D);

		// A -----------B
		//         C -----------D
		// �� ������ �����ϴ� �� ���캻��.
		if ((IsLeft(C, B) > 0) && (IsLeft(A, D) > 0))
			ret = 1;
		else
			ret = 0;
	}
	// l1�� l2�� ������ �� ���� �ʴ� ���
	else
	{
		ret = (l1_l2 <= 0) && (l2_l1 <= 0);
	}
	return ret;
}
/*
- input : p1 = (p1.x, p1.y), p2 = (p2.x, p2.y), p3 = (p3.x, p3.y)
- output : 1 (counter clockwise), 0 (collinear), -1 (clockwise)
�� vector v1 = (p2 - p1), vector v2 = (p3 - p1)
*/
int LineCollider::CCW(Vector2 p1, Vector2 p2, Vector2 p3)
{
	float cross_product = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);

	if (cross_product > 0)
		return 1;

	else if (cross_product < 0)
		return -1;
	else
		return 0;
}
// ������ ���п� ���� ����� �Ÿ�
Vector2 LineCollider::ClosesetPoint(Vector2 start, Vector2 end, Vector2 point)
{
	Vector2 line = end - start;
	Vector2 A = point - start;

	float x = Vector2::Dot(line, A);
	float y = Vector2::Dot(line, line);

	float t = Vector2::Clamp(0, 1, x / y);

	return start + line * t;
}

Vector2 LineCollider::GetStartPoint(int no)
{
	// 0 : start, 1: end

	Vector2 pos = Vector2(Lines[no * 2]->x, Lines[no * 2]->y);
	return pos;
}

Vector2 LineCollider::GetEndPoint(int no)
{
	Vector2 pos = Vector2(Lines[no * 2 + 1]->x, Lines[no * 2 + 1]->y);
	return pos;
}

void LineCollider::CreateVertexBuffer()
{
	if (Lines.size() == 0)
		return;
	if (cVertexBuffer)
		SAFE_DELETE(cVertexBuffer);

	vector<Vertex> vertices;

	for (UINT i = 0; i < Lines.size(); i++)
	{
		Vertex temp;
		temp.position.x = Lines[i]->x;
		temp.position.y = Lines[i]->y;
		temp.position.z = 0.0f;
		vertices.push_back(temp);
	}
	cVertexBuffer = new VertexBuffer(vertices.data(), sizeof(Vertex), (UINT)Lines.size());
	vertices.clear();
}
