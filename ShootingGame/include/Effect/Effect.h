#pragma once

#include "Utils/Timer.h"
#include "Game/Game.h"
#include "Game/Flag.h"

class Effect
{
    friend class EffectManager;
    public:
        Effect();
        virtual ~Effect();

        bool IsActive() const;
        bool IsCanUse() const;

        void SetPos(int x , int y);
        void SetActive(bool value);
        void SetEffectType(eEffect_Type effectType);
        void SetDurationTime(float time);
        void SetEffectCycleTime(float time);

    protected:
        virtual void Update();
        virtual void PrintEffect() const;
        void Reset();
        
        
        void SetEffectActiveFalse();

    private:
        
    

    protected:
        Timer m_durationTimer;
        Timer m_effectCycleTimer;
        wchar_t* m_effectCharacter;
        bool m_bIsActive;
        bool m_bShouldStartEffect;

        Position m_pos;
    private:
        const float m_durationDefaultTime = 0.2f;
        const float m_cycleDefaultTime = 0.05f;




};

