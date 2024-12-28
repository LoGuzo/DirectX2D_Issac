#pragma once

class Collider;

class GameObject : public Object
{
public:
    virtual void Update() = 0;
    virtual void Render() = 0;

public:
    virtual void GUIRender() {};
    virtual void PostRender() {};

public:
    virtual void OnNotify(UINT msg, Collider* Other) {};

public:
    virtual void Enter() {};

public:  // setter
    void SetActive(bool value) { bActive = value; }
    void SetBlockHit(bool value) { bBlock = value; }
    void SetName(string name) { Name = name; }
    string GetName() { return Name; }
    UINT GetOrder() { return DisplayOrder; }
    void SetOrder(UINT value) { DisplayOrder = value; }

public:
    bool IsPhysicsChange(Collider* other);

public:
    bool& IsGround() { return bGround; }
    bool  IsActive() { return bActive; }

public:  // getter
    bool GetActive() { return bActive; }
    Collider* GetCollider();
    //CAnimation* GetAnimation();
    //CAnimation* Animation = nullptr;  // Animation객체
    Collider* cCollider = nullptr;  // 충돌 Check용 객체
    bool bActive = true;     // false : render(x),updata(x)
    bool bBlock = true;     // 콜리젼 ON시 물리 반응
    bool bGround = false;
    string Name;

protected:
    UINT DisplayOrder = 0;
};