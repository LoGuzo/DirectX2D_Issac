#pragma once

#define  OBSERVER DObserverCollision::GetInstance()

class DObserverCollision : public SingleTon<DObserverCollision>
{
private:  // 생성자를 private로
    DObserverCollision();
    friend SingleTon;
public:
    ~DObserverCollision();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
    void Update();  // 콜리젼 Check후 Event발생
    void InitCheckItems();
    void KnockBack(Collider::eKind InAttack, Collider::eKind InDefense);
public:
    void Attach(Collider* observer);
    void Detach(Collider* observer);
    void DetachAll() { Observers.clear(); };
private:
    void CheckItem(Collider::eKind InAttack, Collider::eKind InDefense);
    void DeleteObservers();
private:
    void Check();
    void DoCheckTrue(Collider* A, Collider* B);
    void DoCheckFalse(Collider* A, Collider* B);
    UINT64 CollisonID(Collider* A, Collider* B);
private:
    struct FCheckItem
    {
        Collider::eKind Attack;
        Collider::eKind Defense;
    };
private:  // Collider저장용
    map<int, Collider*> Observers;
private:
    vector<FCheckItem>   CheckItems; // 없다면 Player->Player총알
private:
    vector<Collider*>   Attacks;
    vector<Collider*>   Defenses;
    unordered_map<UINT64, bool> PrevCollisions;	// 충돌체들의 이전 충돌 정보
private:
    vector<int>  ReservedDeletes;

private:
    struct FPrevCollision
    {
        UINT64 ID;
        int    KeyA;
        int    KeyB;
    };
    vector<FPrevCollision*>   FindData;
};