#pragma once
#include <chrono>



class Timer
{
    public:
        Timer();
        virtual ~Timer();

    private:
        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_endTime;

        float m_fixedTime;
        float m_disposableTime;
        bool m_bTimeOver;
        bool m_bIsFirstRun;
        bool m_bDisposableMode;
		bool m_bStop;
        float m_standardTime;

    public:
        void SetFixedTime(float fixedTime);
        void SetDisposableTime(float disposableTime);
        float GetCurrentSettedTimer();
        float GetElapsedTime();
        
        float GetFixedTime();
        bool IsTimeOver();
        bool IsFirstRun();
        void StartOrRestart();
		void Stop();

    private:
        std::chrono::duration<double> m_differenceBetweenTime;






};
