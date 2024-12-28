#pragma once

enum class FReason
{
	COL_ON = 1,
	COL_OFF,
	COL_STAY,
};

class GameObject;

class Collider : public Object
{
public:
	enum class eKind
	{
		NONE,
		GROUND,
		WALL,
		ROCK,
		BOMB,
		PLAYER,
		PBULLET,
		ENEMY,
		EBULLET,
		DOOR,
		DOOR_EXIT,
		ITEM,
	};
public:
	struct ObbDesc
	{
		Vector2 position;
		Vector2 axis[2];
		Vector2 halfSize;
	};

public:
	Collider(GameObject* InObject, eKind kind = eKind::NONE);
	~Collider();

public:
	void  Update();
	void  Render();

public:
	void   GUIRender();

public: // Ű����� ����ϱ� ����
	static void  RenderOnOff() { bRender = !bRender; }

public:
	Vector2 GetMin(); // { return Min; };
	Vector2 GetMax(); // { return Max; };
	//

public:  // Collsion Check
	void   OnNotify(UINT message, Collider* InOther);
	bool   Collision(Collider* InOther);
	bool& Check() { return bCheck; }
	int    GetKey() { return ID; }
	eKind  GetType() { return Type; }
	void   SetType(eKind InType) { Type = InType; }
	int    PhysicsUpdate(Collider* InOther);

public:
	void   SetOther(Collider* Value) { Other = Value; }
	Collider* GetOther() { return Other; }
	Scene* GetCurrentScene() { return CurrentScene; }
	GameObject* GetOwner() { return Owner; }

public:
	bool    GetActive();
	static int GetPhysicsValue() { return physics_change; }

private:
	Vector2   HalfScale();
	bool      AABB(Collider* InOther);
	bool      OBB(Collider* InOther);  // ȸ���� �Ǿ��ִ� ��� : DX�� ����
	bool      InterSectionRegion(Collider* InOther, Vector2& overlap);
	void      Calcuate();

private:
	ObbDesc   GetObb();
	bool      IsSeperate(Vector2 sAxis, ObbDesc box1, ObbDesc box2);
	bool      IsRotated();

private:
	static int static_number;     // class���� static���� cpp���Ͽ� ������
	static int physics_change;

private:
	GameObject* Owner = nullptr;  // Collider�� ������ GameObject
	bool bCheck = false;    // �浹(T),
	int ID = 0;            // collision�� ID
	eKind Type = eKind::NONE;
	Collider* Other = nullptr;

private:
	Matrix       World = MatrixUtil::Identity();
	Scene* CurrentScene = nullptr;
	static bool bRender;

private:
	Vector2 Min = Vector2(0, 0);
	Vector2 Max = Vector2(0, 0);

private:
	class LineCollider* Line;
};