#include <iostream>

#include "Effect/Effect.h"

#include "Manager/GameManager.h"
#include "Manager/EffectManager.h"
#include <Manager/PrintManager.h>

Effect::Effect()
{
    
    SetEffectType(eEffect_Type::Hit);
    m_bShouldStartEffect = true;
    m_bIsActive = false;
    
    //for effect do not always show , m_effectCycleTimer set lower value than m_durationTimer
    m_durationTimer.SetFixedTime(0.15f);
    m_effectCycleTimer.SetFixedTime(0.3f);
}

Effect::~Effect()
{
    //dtor
}

void Effect::Reset()
{
    m_bShouldStartEffect = true;
    m_bIsActive = false;

    m_durationTimer.SetFixedTime(m_durationDefaultTime);
    m_effectCycleTimer.SetFixedTime(m_cycleDefaultTime);

}
void Effect::SetEffectType(eEffect_Type effectType)
{
    switch (effectType)
    {
    case eEffect_Type::Hit:
        m_effectCharacter = L"o";
        break;
    case eEffect_Type::Die:
        m_effectCharacter = L"¡ß";
        break;

    default:
        break;
    }
}
void Effect::SetEffectActiveFalse()
{
  

	PrintManager::GetInstance()->PrintSpace(m_pos.x, m_pos.y);
    SetActive(false);
    EffectManager::GetInstance()->IncreaseCanUseEffectCount();

}
void Effect::SetDurationTime(float time)
{
    m_durationTimer.SetFixedTime(time);
}
void Effect::SetEffectCycleTime(float time)
{
    m_effectCycleTimer.SetFixedTime(time);
}
void Effect::SetActive(bool value)
{
    m_bIsActive = value;
}
void Effect::SetPos(int x, int y)
{
    m_pos.x = x + 2;
    m_pos.y = y;
}

bool Effect::IsCanUse() const
{
    return !m_bIsActive;
}
bool Effect::IsActive() const
{
    return m_bIsActive;
}
void Effect::PrintEffect() const
{
	PrintManager::GetInstance()->Print(m_pos.x, m_pos.y, m_effectCharacter, ePrint_Color::Yellow);

    //GameManager::GetInstance()->gotoxy(m_pos.x, m_pos.y);

    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    //wprintf_s(L"%s" , m_effectCharacter);
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
void Effect::Update()
{
    if (m_durationTimer.IsFirstRun())
    {
        m_durationTimer.StartOrRestart();
    }


    if(m_effectCycleTimer.IsTimeOver())
    {
        PrintEffect();
        m_effectCycleTimer.StartOrRestart();
    }
    //Unless it's time to show the effect, delete effect Character
    else
    {
		//PrintManager::GetInstance()->PrintSpace(m_pos.x, m_pos.y);
        
    }

    if(m_durationTimer.IsTimeOver())
    {
        SetEffectActiveFalse();
    }




}


