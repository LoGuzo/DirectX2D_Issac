#include "framework.h"
#include "DGameObject.h"

bool GameObject::IsPhysicsChange(Collider* other)
{
	return false;
}

Collider* GameObject::GetCollider()
{
	return cCollider;
}
