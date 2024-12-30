#pragma once

#define  OBSERVER DObserverCollision::GetInstance()

class DObserverCollision : public SingleTon<DObserverCollision>
{
private:  // �����ڸ� private��
    DObserverCollision();
    friend SingleTon;
public:
    ~DObserverCollision();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
    void Update();  // �ݸ��� Check�� Event�߻�
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
private:  // Collider�����
    map<int, Collider*> Observers;
private:
    vector<FCheckItem>   CheckItems; // ���ٸ� Player->Player�Ѿ�
private:
    vector<Collider*>   Attacks;
    vector<Collider*>   Defenses;
    unordered_map<UINT64, bool> PrevCollisions;	// �浹ü���� ���� �浹 ����
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