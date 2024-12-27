#pragma once
#include  <chrono>  // STL Time���� ���̺귯��
#define TIMER GameTime::GetInstance()

using namespace chrono;

class GameTime : public SingleTon<GameTime>
{
private:  // �����ڸ� �̱��濡���� private
	GameTime();
	friend SingleTon;

public:
	~GameTime();

public:
	void  Update();
	float Delta() { return  m_TimeDuration; }
	float GetRunning() { return  m_RunningTime; }
	float GetFPS() { return  m_FramePerSecond; }
	int   GetFrame() { return  m_FrameCountPerSecond; }
	void  SetLock(bool lock, float lockfps)
	{
		m_bLock = lock;
		m_LockFPS = lockfps;
	}
private:
	void  Update(float lockFPS);  // �����ð��� ���

private:  // ������
	float  m_TimeDuration = 0.0f;  // ������ �ð�
	float  m_FPStimeDuration = 0.0f;  // 1�ʸ� Check�ϴ� �ð�
	float  m_RunningTime = 0.0f;  // ���α׷� ���ۺ��� ��������� ����
	float  m_FramePerSecond = 0.0f;  // �ʴ� frame �ð�
	int    m_FrameCount = 0;     // Frame ����
	int    m_FrameCountPerSecond = 0; // �ʴ� Frame Count
	system_clock::time_point old;  // ������ �ð�
	float  m_LockFPS = 0.0f;
	bool   m_bLock = false;
};

