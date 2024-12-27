#include "framework.h"
#include "DKeyboard.h"

Keyboard::Keyboard()
{
	for (UINT i = 0; i < KEYMAX; i++)
	{
		up.set(i, false);
		down.set(i, false);
	}
}

Keyboard::~Keyboard()
{
}

bool Keyboard::Down(int key)
{
    // 0x8000 : ������ �������� ���� ȣ������� ���� ����
    if (GetAsyncKeyState(key) & 0x8000)
    {
        if (down[key] == false) // 1st �ԷµȻ���
        {
            down.set(key, true);
            return true;
        }
    }
    else
        down.set(key, false);

    return false;  // 1st�� check�� ���Ĵ�
}

bool Keyboard::Up(int key)
{
    // 0x8000 : ������ �������� ���� ȣ������� ���� ����
    if (GetAsyncKeyState(key) & 0x8000)
        up.set(key, true);
    else
    {
        if (up[key]) // 1st �ԷµȻ���
        {
            up.set(key, false);
            return true;
        }
    }
    return false;
}

bool Keyboard::Press(int key)
{
    // 0x8000 : ������ �������� ���� ȣ������� ���� ����
    if (GetAsyncKeyState(key) & 0x8000)
        return true;
    return false;
}

bool Keyboard::Toggle(int key)
{
    // 0x0001 : ������ �������� �ְ� ȣ������� �� ���� ����
    if (GetAsyncKeyState(key) & 0x0001)
        return true;
    return false;
}
