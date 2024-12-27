#include "framework.h"
#include "GameTime.h"

GameTime::GameTime()
{
	old = std::chrono::system_clock::now(); // 현재시간
}

GameTime::~GameTime()
{
}

void GameTime::Update()
{
	if (this->m_bLock)
		return Update(this->m_LockFPS);


	// 1. duration
	duration<double> sec;
	sec = system_clock::now() - old;

	m_TimeDuration = (float)sec.count();  // 0.003sec
	old = system_clock::now();

	m_FrameCount++;
	m_RunningTime = m_RunningTime + m_TimeDuration;
	m_FPStimeDuration = m_FPStimeDuration + m_TimeDuration;

	if (m_FPStimeDuration >= 1.0f)
	{
		m_FramePerSecond = m_FPStimeDuration / m_FrameCount;
		m_FrameCountPerSecond = m_FrameCount;
		m_FrameCount = 0;
		m_FPStimeDuration = 0.0f;
	}
}

void GameTime::Update(float lockFPS)
{
	// 1. duration
	duration<double> sec;
	sec = system_clock::now() - old;

	m_TimeDuration = (float)sec.count();  // 0.003sec

	while (m_TimeDuration < 1.0f / lockFPS)
	{
		sec = system_clock::now() - old;
		m_TimeDuration = (float)sec.count();
	}

	old = system_clock::now();

	m_FrameCount++;
	m_RunningTime = m_RunningTime + m_TimeDuration;
	m_FPStimeDuration = m_FPStimeDuration + m_TimeDuration;

	if (m_FPStimeDuration >= 1.0f)
	{
		m_FramePerSecond = m_FPStimeDuration / m_FrameCount;
		m_FrameCountPerSecond = m_FrameCount;
		m_FrameCount = 0;
		m_FPStimeDuration = 0.0f;
	}
}