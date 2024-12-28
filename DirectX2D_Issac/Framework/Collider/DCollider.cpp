#include "framework.h"
#include "DCollider.h"
#include "DQuadCollider.h"
#define  OFF  0
#define  ON   1
#define  STAY 2
#define  TOP     1
#define  RIGHT   2
#define  BOTTOM  3
#define  LEFT    4

bool            Collider::bRender = false;
int             Collider::static_number = 0;   // class내의 static변수
int             Collider::physics_change = 0;

Collider::Collider(GameObject* InObject, eKind kind)
{
	QuadCollider::GetInstance();

	Owner = InObject;
	Type = kind;

	ID = static_number;
	static_number++;
	//OBSERVER->Attach(this);
	Line = new LineCollider();
}

Collider::~Collider()
{
	//OBSERVER->Detach(this);
}

void Collider::Update()
{
	Matrix S, T, R;

	S = MatrixUtil::Scaling(Scale().x, Scale().y, 0.0f);
	T = MatrixUtil::Translation(Pos().x, Pos().y, 0.0f);
	R = MatrixUtil::RotationRollPitchYaw(mRotation.y, mRotation.x, mRotation.z);


	// SRT
	World = S * R * T;
	CurrentScene = SCENEMGR->GetCurrentScene();

	Min.x = Pos().x * (Scale().x * -0.5f);
	Min.y = Pos().y * (Scale().y * -0.5f);

	Max.x = Pos().x * (Scale().x * 0.5f);
	Max.y = Pos().y * (Scale().y * 0.5f);
	Calcuate();
	if (IsRotated())
		Calcuate();
}

void Collider::Render()
{
	if (bRender == false)
		return;

	if (bCheck)
		QUADCOLLIDER->SetColor(1, 0, 0);
	else
		QUADCOLLIDER->SetColor(0, 1, 0);
	QUADCOLLIDER->SetMatrix(World);
	QUADCOLLIDER->Render();

}

void Collider::GUIRender()
{
	string Name = "Collider" + to_string(ID);

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

bool Collider::Collision(Collider* InOther)
{
	if (IsRotated() || InOther->IsRotated())
		return OBB(InOther);
	return AABB(InOther);
}
void Collider::OnNotify(UINT message, Collider* InOther)
{
	InOther->SetOther(this);

	if (Owner)
	{
		if (message == 0)
		{
			if (InOther->GetType() == Collider::eKind::GROUND)
				Owner->IsGround() = false;
			Owner->OnNotify((UINT)(FReason::COL_OFF), InOther);
		}
		else
		{
			if (Owner->IsPhysicsChange(InOther))
			{
				int contact = PhysicsUpdate(InOther);
				// TOP Side
				if ((InOther->GetType() == Collider::eKind::GROUND) && contact == 1)
					Owner->IsGround() = true;
				// Bottom Side
				if ((InOther->GetType() == Collider::eKind::GROUND) && contact == 3)
					Owner->IsGround() = false;
			}
			if (message == 1)
				Owner->OnNotify((UINT)(FReason::COL_ON), InOther);
			if (message == 2)
				Owner->OnNotify((UINT)(FReason::COL_STAY), InOther);
		}
	}
}

Vector2 Collider::GetMin()
{
	return Min;
	Vector2 value;
	value.x = Pos().x - Scale().x * 0.5f;
	value.y = Pos().y - Scale().y * 0.5f;
	return value;
}
Vector2 Collider::GetMax()
{
	return Max;
	Vector2 value;
	value.x = Pos().x + Scale().x * 0.5f;
	value.y = Pos().y + Scale().y * 0.5f;
	return value;
}
Vector2 Collider::HalfScale()
{
	Vector2 value;


	value.x = abs(Max.x - Min.x) * 0.5f;
	value.y = abs(Max.y - Min.y) * 0.5f;
	return value;
}
// 
// Axis Alignment Bounding Box
bool Collider::AABB(Collider* InOther)
{
	Vector2 minA = GetMin();
	Vector2 maxA = GetMax();
	Vector2 minB = InOther->GetMin();
	Vector2 maxB = InOther->GetMax();

	if (minA.x > maxB.x) return false;
	if (minB.x > maxA.x) return false;
	if (minA.y > maxB.y) return false;
	if (minB.y > maxA.y) return false;

	return true;
}

// Ground, Wall인경우 blocking
// 위치를 재조정
int Collider::PhysicsUpdate(Collider* InOther)
{

	Vector2 overap;
	Vector2 pos = Pos();
	Vector2 size = HalfScale();
	int     Value = 0;

	InterSectionRegion(InOther, overap);
	if (abs(overap.x) > abs(overap.y)) // 상하 충돌
	{
		if (Pos().y > InOther->Pos().y) // 상
		{
			pos.y = InOther->Pos().y + InOther->HalfScale().y + size.y;
			Value = 1;
		}
		else
		{
			pos.y = InOther->Pos().y - InOther->HalfScale().y - size.y;
			Value = 3;
		}

	}
	else // 좌우충돌
	{
		if (Pos().x > InOther->Pos().x)
		{
			pos.x = InOther->Pos().x + InOther->HalfScale().x + size.x;
			Value = 2;
		}

		else
		{
			pos.x = InOther->Pos().x - InOther->HalfScale().x - size.x;
			Value = 4;

		}

	}

	Owner->Pos() = pos;
	Pos() = pos;
	physics_change = Value;
	return Value;

}

bool Collider::GetActive()
{
	if (!Owner)
		return true;
	return(Owner->IsActive());
}

bool Collider::InterSectionRegion(Collider* InOther, Vector2& overlap)
{
	float left = max(GetMin().x, InOther->GetMin().x);
	float right = min(GetMax().x, InOther->GetMax().x);
	float top = min(GetMax().y, InOther->GetMax().y);
	float bottom = max(GetMin().y, InOther->GetMin().y);


	float width = right - left;
	float height = top - bottom;
	if (width <= 0 || bottom <= 0)
		false;
	overlap.x = width;
	overlap.y = height;

	return true;
}

void Collider::Calcuate()
{
	vector<Vector2> Points;
	const float TO_RADIAN = 3.141592f / 180.0f;

	Vector2 size = Scale() * 0.5f;

	Matrix T = MatrixUtil::Translation(Pos().x, Pos().y, 0.0f);
	Matrix R = MatrixUtil::RotationRollPitchYaw(mRotation.y, mRotation.x, mRotation.z);

	Matrix W = R * T;


	Points.push_back(Vector2(-size.x, +size.y));  // LeftTop
	Points.push_back(Vector2(-size.x, -size.y));  // LeftBottom
	Points.push_back(Vector2(+size.x, +size.y));  // RightTop
	Points.push_back(Vector2(+size.x, -size.y));  // RightBottom

	float r = sqrtf(Scale().x * Scale().x + Scale().y * Scale().y);
	Vector2 min = Vector2(FLT_MAX, FLT_MAX);
	Vector2 max = Vector2(-FLT_MAX, -FLT_MAX);
	for (UINT i = 0; i < Points.size(); i++)
	{
		Points[i] = Points[i] * W;
		min.x = min(Points[i].x, min.x);
		min.y = min(Points[i].y, min.y);
		max.x = max(Points[i].x, max.x);
		max.y = max(Points[i].y, max.y);

	}
	Min = min;
	Max = max;

	//	Line->ClearLine();
	//	Line->AddLine(Min.x, Min.y, Max.x, Min.y);
	//	Line->AddLine(Max.x, Min.y, Max.x, Max.y);
	//	Line->AddLine(Max.x, Max.y, Min.x, Max.y);
	//	Line->AddLine(Min.x, Max.y, Min.x, Min.y);
	//	Line->EndLine();
	//	Line->Update();
}

Collider::ObbDesc Collider::GetObb()
{
	ObbDesc result;

	Matrix R = MatrixUtil::RotationRollPitchYaw(0.0f, 0.0f, mRotation.z);
	XMFLOAT4X4 matWorld = MatrixUtil::StoreFloat4(R);

	Vector2  Up = Vector2(matWorld._21, matWorld._22);
	Vector2 Right = Vector2(matWorld._11, matWorld._12);

	Up = Vector2::Normalize(Up);
	Right = Vector2::Normalize(Right);


	result.position = Pos();
	result.halfSize = Scale() * 0.5f;
	result.axis[0] = Right;
	result.axis[1] = Up;
	return result;
}

bool Collider::IsSeperate(Vector2 sAxis, ObbDesc box1, ObbDesc box2)
{
	// box1과 box2의 중점을 내적 --> 투영된 길이
 // 백터(방향) = A위치 - B위치
	float dist = abs(Vector2::Dot(sAxis, box1.position - box2.position));

	Vector2 right = box1.axis[0] * box1.halfSize.x;
	Vector2 up = box1.axis[1] * box1.halfSize.y;

	float a = abs(Vector2::Dot(sAxis, right)) + abs(Vector2::Dot(sAxis, up));

	right = box2.axis[0] * box2.halfSize.x;
	up = box2.axis[1] * box2.halfSize.y;

	float b = abs(Vector2::Dot(sAxis, right)) + abs(Vector2::Dot(sAxis, up));


	return (dist > (a + b));
}

bool Collider::IsRotated()
{
	if (abs(Rotation().z) >= 0.00001f)
		return true;
	return false;
}

bool Collider::OBB(Collider* InOther)
{
	ObbDesc oA = GetObb();
	ObbDesc oB = InOther->GetObb();

	if (IsSeperate(oA.axis[0], oA, oB)) return false;  // Right
	if (IsSeperate(oA.axis[1], oA, oB)) return false;  // UP
	if (IsSeperate(oB.axis[0], oA, oB)) return false;  // Right 
	if (IsSeperate(oB.axis[1], oA, oB)) return false;  // UP

	return true;
}
