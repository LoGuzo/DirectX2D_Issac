#pragma once

#define SCENEMGR   SceneManager::GetInstance()

class SceneManager : public SingleTon<SceneManager>
{
private:
    SceneManager();
    friend SingleTon;

public:
    ~SceneManager();

public:
    void InitScene();
public:
    void  Update();
    void  Render();
    void  GUIRender();
    void  PostRender();
public:
    Scene* GetCurrentScene() { return CurrentScene; }
    Scene* GetUIScene() { return UIScene; }
    void  ChangeScene(string InName);
    void  SetPrevScene(string InName) { PrevScene = InName; }


public:   // Door & Enemy Check¿ë
    void EntranceEvent(string direction)
    {
        CurrentScene->EntranceEvent(direction);
    };
    void DoorCheckEvent(string enemy)
    {
        CurrentScene->DoorCheckEvent(enemy);
    }

private:
    void  ThreadStart();
    void  ThreadSound();

private:
    void  CreateSamplerState();
    void  CreateBlendState();
    void  CreateRasterState();

private:
    vector<class Scene*>  Scenes;
    string   PrevScene;
    Scene* CurrentScene = nullptr;
    Scene* UIScene = nullptr;
    bool bThreadEnd = false;

private:
    ID3D11SamplerState* SamplerState = nullptr;
    ID3D11BlendState* BlendState = nullptr;
    ID3D11RasterizerState* RasterState = nullptr;
};

