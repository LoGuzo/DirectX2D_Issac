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
    bool  Press(int key);     // ��������� �������� ����
    bool  Toggle(int key);

private: // ture/false���� �����Ҽ� �ִ� STL
    bitset<KEYMAX> up;       // Key�� �������� up[key] = true
    bitset<KEYMAX> down;     // Key�� �������� up[key] = false
};

