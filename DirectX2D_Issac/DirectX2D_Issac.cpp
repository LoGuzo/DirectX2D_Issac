// DirectX2D_Issac.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DirectX2D_Issac.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    MAIN->CreateGameWindow(hInstance, 1490, 950);
    SCENEMGR->InitScene();
    DIRECT;
    // IMGUI Setting
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        ImGui_ImplWin32_Init(MAIN->GetHandle());
        ImGui_ImplDX11_Init(DEVICE, DC);
        //    LoadFont();
        ImGui::StyleColorsDark();
    }

    //TIMER->SetLock(true, 60);
    MSG msg;
    // GetMessage  :  Idle후 Messgge를 가져 오는 방식
    // PeekMessage :  즉시 가져오는 방식
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        TIMER->Update();
        MAIN->Update();
        MAIN->Render();
    }
    // IMGUI Delete
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
    return (int)msg.wParam;
}
