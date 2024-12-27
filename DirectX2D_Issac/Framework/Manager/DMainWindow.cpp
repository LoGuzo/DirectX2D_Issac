#include "framework.h"
#include "DMainWindow.h"
#include "Resource.h"

#define  OFFSETX  -1000
#define  OFFSETY  10

// IMGI
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

MainWindow::MainWindow()
{
}

MainWindow::~MainWindow()
{
}

void MainWindow::CreateGameWindow(HINSTANCE InInstance, int InWidth, int InHeight)
{
    //1.윈도우 클래스를 등록 : Callback함수
    WNDCLASSEXW wcex;
    {
        wcex.lpszClassName = L"D3D";
        wcex.cbSize = sizeof(WNDCLASSEXW);    //3.x,4.0~
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;          // callback
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = InInstance;
        wcex.hIcon = LoadIcon(InInstance, MAKEINTRESOURCE(IDI_DIRECTX2DISSAC));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCE(IDI_DIRECTX2DISSAC);
        wcex.lpszMenuName = L"";
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
        RegisterClassExW(&wcex);
    }

    // 2. 윈도우를 생성
    if (0)
    {
        RECT adjustRect = { 0,0,InWidth,InHeight };
        // overlap window사 포함된 size계산
        AdjustWindowRect(&adjustRect, WS_OVERLAPPEDWINDOW, false);
        int w = adjustRect.right - adjustRect.left;
        int h = adjustRect.bottom - adjustRect.top;

        WinHandle = CreateWindow(L"D3D", L"2D 프로그램",
            WS_OVERLAPPEDWINDOW,  // Window Style
            OFFSETX, OFFSETY, w, h, nullptr, nullptr,
            InInstance, nullptr);
    }
    if (1)
    {

        WinHandle = CreateWindow(L"D3D", L"2D 프로그램",
            WS_OVERLAPPEDWINDOW,  // Window Style
            OFFSETX, OFFSETY, InWidth, InHeight, nullptr, nullptr,
            InInstance, nullptr);
    }

    RECT rect;
    GetClientRect(WinHandle, &rect);
    Width = rect.right - rect.left;
    Height = rect.bottom - rect.top;

    int check = MessageBox(NULL, L"윈도우가 표시되지 않으면 OFFSET_X를 조정하세요!!", L"Warning", MB_YESNO);

    if (check == 7)
    {
        MoveWindow(WinHandle, -1000, 0, Width, Height, true);
    }

    DDevice::GetInstance(); // DX초기화

    //    ShowWindow(WinHandle, SW_SHOWDEFAULT);
    ShowWindow(WinHandle, SW_SHOWMAXIMIZED);
    UpdateWindow(WinHandle);
}

void MainWindow::Update()
{
}

void MainWindow::Render()
{
    DDevice::GetInstance()->Clear(0.0f, 0.0f, 0.0f, 1.0f);
    {
    }

    // IMGUI
    {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
    }

    {
        static bool bActive = true;
        if (ImGui::Begin("Inspector"), &bActive)
        {
        }
        ImGui::End();
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    DDevice::GetInstance()->Present();
}

void MainWindow::OnSize()
{
    RECT rect;
    GetClientRect(MAIN->GetHandle(), &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    if (width < 1 || height < 1)
        return;

    Width = width;
    Height = height;
    DDevice::GetInstance()->ResizeBuffer();
}

void MainWindow::OnMouseMove(LPARAM lParam)
{

}

LRESULT MainWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
        case VK_TAB:
            break;
        }
    }
    break;
    case WM_SIZE:
        MAIN->OnSize();
        break;
    case WM_MOUSEMOVE:
        MAIN->OnMouseMove(lParam);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
