#pragma once

#define OBJECTMGR DObjectManager::GetInstance();

class DObjectManager : public SingleTon<DObjectManager>
{
public:
    ~DObjectManager();

public:
    void Update(string name);
    void Render(string name);
    void UpdateAll();
    void RenderAll();
public:
    void ClearStrings() { GameObjectStrings.clear(); }
    void AddString(string name) { GameObjectStrings.push_back(name); }
    void AddPlayer(string name) { Player = name; }
    void AddOther(string name) { Other = name; }
public:
    void AddObject(string name, GameObject* InObject);
    GameObject* FindObject(string name);

private:
    map<string, GameObject*> GameObjects;
    vector<string>            GameObjectStrings;
    string      Player;
    string      Other;
};

// 생성자 패턴
namespace Factory
{
    template<typename T>
    T* CrateGameObject(string name)
    {
        T* object = dynamic_cast<T*>(DObjectManager::GetInstance()->FindObject(name));
        if (object != NULL)
            return object;

        object = new T;
        DObjectManager::GetInstance()->AddObject(name, object);
        DObjectManager::GetInstance()->AddString(name);
        return object;
    }
    template<typename T>
    T* GetGameObject(string name)
    {
        T* object = dynamic_cast<T*>(DObjectManager::GetInstance()->FindObject(name));
        if (object != NULL)
            return object;
        return NULL;
    }
}
