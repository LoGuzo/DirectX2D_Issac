#pragma once
#include <bitset>
#define KEYBOARD Keyboard::GetInstance()

#define  KEYMAX  255

class Keyboard : public SingleTon<Keyboard>
{
private:
    Keyboard();
    ~Keyboard();
    friend SingleTon;

public:
    bool  Down(int key);
    bool  Up(int key);
    bool  Press(int key);     // 계속적으로 눌려지는 상태
    bool  Toggle(int key);

private: // ture/false값을 저장할수 있는 STL
    bitset<KEYMAX> up;       // Key가 눌려지면 up[key] = true
    bitset<KEYMAX> down;     // Key가 떨어지면 up[key] = false
};

