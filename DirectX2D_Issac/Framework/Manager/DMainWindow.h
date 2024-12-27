#pragma once
#define   MAIN   MainWindow::GetInstance()

class MainWindow : public SingleTon<MainWindow>
{
private:
    MainWindow();
    friend SingleTon;

public:
    ~MainWindow();

public:
    void CreateGameWindow(HINSTANCE InInstance, int InWidth, int InHeight);
    void Update();
    void Render();
    void OnSize();
    void OnMouseMove(LPARAM lParam);

public:
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
    int  GetWidth() { return Width; }
    int  GetHeight() { return Height; }
    HWND GetHandle() { return WinHandle; }

private:
    HWND WinHandle = NULL;
    int  Width = 0;
    int  Height = 0;
    //Vector2 MousePos;
};

