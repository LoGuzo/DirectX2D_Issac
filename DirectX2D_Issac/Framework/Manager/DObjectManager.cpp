#include "framework.h"
#include "DObjectManager.h"

DObjectManager::~DObjectManager()
{
}

void DObjectManager::Update(string name)
{
	GameObject* value = FindObject(name);
	if (value)
		value->Update();
}

void DObjectManager::Render(string name)
{
	GameObject* value = FindObject(name);
	if (value)
	{
		if (value->IsActive())
			value->Render();
	}
}

void DObjectManager::UpdateAll()
{
	for (auto a : GameObjects)
	{
		if (!a.second->GetActive())
			continue;
		if (!CAMERA->ContainFrustum(a.second->Pos()))
			continue;
		a.second->Update();
	}
}

void DObjectManager::RenderAll()
{
	for (auto a : GameObjects)
	{
		if (!a.second->GetActive())
			continue;
		if (!CAMERA->ContainFrustum(a.second->Pos()))
			continue;
		if (a.first != "Player")
			a.second->Render();
	}
}

void DObjectManager::AddObject(string name, GameObject* InObject)
{
	InObject->SetName(name);
	GameObjects.insert(make_pair(name, InObject));
}

GameObject* DObjectManager::FindObject(string name)
{
	GameObject* value = nullptr;
	if (GameObjects.count(name))
		value = GameObjects[name];
	return value;
}
