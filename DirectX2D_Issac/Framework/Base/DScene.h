#pragma once

class GameObject;
class Sprite;
class Collider;
class LineCollider;
class Vector2;

class Scene
{
public:
	virtual void Update() = 0;  // ���������Լ�
	virtual void Render() = 0;  // ���������Լ�
public:
	void    UpdateAll();
	void    RenderAll();

public:
	virtual void GUIRender() {};
	virtual void PostRender() {}; // Font�� ������
	virtual void Enter() {};    //  Scene1 --> Scene2
	virtual void Exit() {};    //  Scene1 --> Scene2

public:
	virtual void EntranceEvent(string direction) {};
	virtual void DoorCheckEvent(string enemy) {};
	virtual void Debug();
public:
	vector<GameObject*>& GetEffector() { return Effects; }
	vector<GameObject*>& GetItems() { return Items; }
	vector<LineCollider*>& GetLines() { return Lines; }

public:
	bool    IsActive() { return bActive; }
	void    SetActive(bool InValue) { bActive = InValue; }
	void    SetName(string InValue) { Name = InValue; }
	string  GetName() { return Name; }

protected:
	bool    bActive = false; // T(Scene U/R), F(X) 
	string  Name;           // ���� ��Ī

protected:
	vector<GameObject*> Obstacles;
	vector<GameObject*> Effects;
	vector<GameObject*> Monsters;
	vector<GameObject*> Items;
	vector<Collider*>   Walls;
	vector<LineCollider*> Lines;
	Sprite* Background = nullptr;
};

