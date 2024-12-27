#pragma once
#include  <chrono>  // STL Time관련 라이브러리
#define TIMER GameTime::GetInstance()

using namespace chrono;

class GameTime : public SingleTon<GameTime>
{
private:  // 생성자를 싱글톤에서는 private
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
	void  Update(float lockFPS);  // 일정시간을 대기

private:  // 변수들
	float  m_TimeDuration = 0.0f;  // 현재경과 시간
	float  m_FPStimeDuration = 0.0f;  // 1초를 Check하는 시간
	float  m_RunningTime = 0.0f;  // 프로그램 시작부터 현재까지의 누적
	float  m_FramePerSecond = 0.0f;  // 초당 frame 시간
	int    m_FrameCount = 0;     // Frame 숫자
	int    m_FrameCountPerSecond = 0; // 초당 Frame Count
	system_clock::time_point old;  // 현재의 시간
	float  m_LockFPS = 0.0f;
	bool   m_bLock = false;
};

