#include "framework.h"
#include "DObserverCollision.h"

DObserverCollision::DObserverCollision()
{
	InitCheckItems();
}

DObserverCollision::~DObserverCollision()
{
}

void DObserverCollision::Update()
{
    Scene* cScene = SCENEMGR->GetCurrentScene();

    if (CAMERA->IsMoveCamera())
        return;

    DeleteObservers();

    for (FCheckItem& item : CheckItems)
    {
        Attacks.clear();  // 동적할당이 아닌경우
        Defenses.clear(); // 동적할당이 아닌경우
        for (auto collider : Observers)
        {
            if (!collider.second->GetActive())
                continue;
            if (!CAMERA->ContainFrustum(collider.second->Pos()))
                continue;

            //Vector2 size = collider.second->Scale();
            //Vector2 pos = collider.second->Pos();
            //if (!CAMERA->ContainFrustum(pos, size))
            //    continue;


            if (item.Attack == collider.second->GetType())
                Attacks.push_back(collider.second);

            if (item.Defense == collider.second->GetType())
                Defenses.push_back(collider.second);
        }
        Check();
    }

    KnockBack(Collider::eKind::PLAYER, Collider::eKind::WALL);
    KnockBack(Collider::eKind::PLAYER, Collider::eKind::ROCK);

    KnockBack(Collider::eKind::ENEMY, Collider::eKind::WALL);
    KnockBack(Collider::eKind::ENEMY, Collider::eKind::ROCK);
}

// 없다면 Player->Player총알
// Check할 아이템을 하나씩 등록
void DObserverCollision::InitCheckItems()
{
    FCheckItem item;

    // Player & Ground
    {
        CheckItem(Collider::eKind::PLAYER, Collider::eKind::DOOR);
        CheckItem(Collider::eKind::PLAYER, Collider::eKind::DOOR_EXIT);
        CheckItem(Collider::eKind::PLAYER, Collider::eKind::WALL);
        CheckItem(Collider::eKind::PLAYER, Collider::eKind::ROCK);
        CheckItem(Collider::eKind::PLAYER, Collider::eKind::ENEMY);
        CheckItem(Collider::eKind::PLAYER, Collider::eKind::ITEM);

        CheckItem(Collider::eKind::ENEMY, Collider::eKind::WALL);
        CheckItem(Collider::eKind::ENEMY, Collider::eKind::ROCK);
        CheckItem(Collider::eKind::ENEMY, Collider::eKind::BOMB);

        CheckItem(Collider::eKind::EBULLET, Collider::eKind::PLAYER);
        CheckItem(Collider::eKind::EBULLET, Collider::eKind::WALL);
        CheckItem(Collider::eKind::EBULLET, Collider::eKind::ROCK);

        CheckItem(Collider::eKind::PBULLET, Collider::eKind::ENEMY);
        CheckItem(Collider::eKind::PBULLET, Collider::eKind::WALL);
        CheckItem(Collider::eKind::PBULLET, Collider::eKind::ROCK);

        CheckItem(Collider::eKind::BOMB, Collider::eKind::ENEMY);
        CheckItem(Collider::eKind::BOMB, Collider::eKind::PLAYER);
        CheckItem(Collider::eKind::BOMB, Collider::eKind::ROCK);


        CheckItem(Collider::eKind::ENEMY, Collider::eKind::ENEMY);
    }
}

void DObserverCollision::KnockBack(Collider::eKind InAttack, Collider::eKind InDefense)
{
    FCheckItem item2;
    // Player & Wall
    {
        item2.Attack = InAttack;
        item2.Defense = InDefense;
    }
    Attacks.clear();  // 동적할당이 아닌경우
    Defenses.clear(); // 동적할당이 아닌경우
    for (auto collider : Observers)
    {
        if (!collider.second->GetActive())
            continue;

        if (!CAMERA->ContainFrustum(collider.second->Pos()))
            continue;

        if (item2.Attack == collider.second->GetType())
            Attacks.push_back(collider.second);

        if (item2.Defense == collider.second->GetType())
            Defenses.push_back(collider.second);
    }
    Check();
}

void DObserverCollision::Attach(Collider* observer)
{
    Observers.insert(make_pair(observer->GetKey(), observer));
}

void DObserverCollision::Detach(Collider* observer)
{
    ReservedDeletes.push_back(observer->GetKey());
    return;
}

void DObserverCollision::CheckItem(Collider::eKind InAttack, Collider::eKind InDefense)
{
}

void DObserverCollision::DeleteObservers()
{
    map<int, Collider*>::iterator it; // 반복자
    // Delete
    for (auto a : ReservedDeletes)
    {
        it = Observers.find(a);
        if (it == Observers.end())  // 없는경우
            continue;
        Observers.erase(it);
    }
    ReservedDeletes.clear();
}

void DObserverCollision::Check()
{
    for (UINT i = 0; i < (UINT)Attacks.size(); i++)
    {
        for (UINT j = 0; j < (UINT)Defenses.size(); j++)
        {
            if (Attacks[i] == Defenses[j]) continue;

            // 충돌 정보가 없었던 경우, 충돌하지 않은 상태로 보관
            UINT64 id = CollisonID(Attacks[i], Defenses[j]);
            if (PrevCollisions.find(id) == PrevCollisions.end())
                PrevCollisions.insert(make_pair(id, false));
            if (Attacks[i]->GetActive() == false || Defenses[j]->GetActive() == false)
            {
                PrevCollisions[id] = false;
                //               continue;
            }


            bool hit = Attacks[i]->Collision(Defenses[j]);
            if (hit)
                DoCheckTrue(Attacks[i], Defenses[j]);
            else
                DoCheckFalse(Attacks[i], Defenses[j]);

        }
    }
}

void DObserverCollision::DoCheckTrue(Collider* A, Collider* B)
{
    UINT64 id = CollisonID(A, B);
    A->Check() = true;
    B->Check() = true;

    if (PrevCollisions[id])  // 이전 : 충돌 , 현재 충돌 
    {
        A->OnNotify(2, B);
        B->OnNotify(2, A);
        return;
    }
    else    // 이전 : 충돌X , 현재 충돌O 
    {
        A->OnNotify(1, B);
        B->OnNotify(1, A);
        PrevCollisions[id] = true;
    }
}

void DObserverCollision::DoCheckFalse(Collider* A, Collider* B)
{
    UINT64 id = CollisonID(A, B);

    A->Check() = false;
    B->Check() = false;

    if (PrevCollisions[id])  // 이전 : 충돌(0) , 현재 충돌(x) 
    {
        A->OnNotify(0, B);
        B->OnNotify(0, A);
    }
    PrevCollisions[id] = false;
}

UINT64 DObserverCollision::CollisonID(Collider* A, Collider* B)
{
    UINT64 result = 0;
    UINT leftID = A->GetKey();
    UINT rightID = B->GetKey();

    if (leftID < rightID)
    {
        result |= (UINT64)leftID << 32;
        result |= rightID;
        return result;
    }
    else
    {
        result |= (UINT64)rightID << 32;
        result |= leftID;
        return result;
    }
}
