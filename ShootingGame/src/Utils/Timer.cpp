#include "Utils/Timer.h"

Timer::Timer():
    m_fixedTime(0),
    m_standardTime(0)
{
    //When constructed, m_bTimeOver is set to true as an initial value.
    m_bTimeOver = true;
    m_bIsFirstRun = true;
    m_bDisposableMode = false;
	m_bStop = false;
    
    
}

Timer::~Timer()
{
    //dtor
}

float Timer::GetFixedTime()
{
    return m_fixedTime;
}
void Timer::SetFixedTime(float fixedTime)
{
    m_fixedTime = fixedTime;
}

void Timer::SetDisposableTime(float disposableTime)
{
    m_disposableTime = disposableTime;
    m_bDisposableMode = true;
}

float Timer::GetCurrentSettedTimer()
{
    return m_standardTime;
}

float Timer::GetElapsedTime()
{
	if (!m_bStop)
	{
		m_endTime = std::chrono::steady_clock::now();
		m_differenceBetweenTime = m_endTime - m_startTime;
	}

    
    return m_differenceBetweenTime.count();
}


bool Timer::IsFirstRun()
{
    return m_bIsFirstRun;
}
void Timer::StartOrRestart()
{
    if(m_bIsFirstRun)
    {
        m_bIsFirstRun = false;
    }
    m_startTime = std::chrono::steady_clock::now();
}

void Timer::Stop()
{
	m_bStop = true;

}

bool Timer::IsTimeOver()
{
	std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

	std::chrono::duration<double> differenceBetweenTime = endTime - m_startTime;
    
   
    //만약 일회용 모드이면 일회용 시간 적용
    if(m_bDisposableMode)
    {
        m_standardTime = m_disposableTime;
    }
    else
    {
        m_standardTime = m_fixedTime;
    }

    if(differenceBetweenTime.count() >= m_standardTime)
    {
        m_bTimeOver = true;
        m_bDisposableMode = false;
    }
    else
    {
        m_bTimeOver = false;
    }

    return m_bTimeOver;
}
