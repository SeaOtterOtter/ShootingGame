#include <iostream>
#include "Manager/EffectManager.h"
#include "Manager/GameManager.h"


EffectManager* EffectManager::m_instance;


EffectManager::EffectManager()
{
    m_possesionEffectCount = 0;
    m_canUseEffectCount = 0;
    m_vecEffectIdxPos =0;
}

EffectManager::~EffectManager()
{
    //dtor
}
void EffectManager::Start()
{
}
void EffectManager::IncreaseCanUseEffectCount()
{
    m_canUseEffectCount++;
}
void EffectManager::Release()
{
    for(size_t i = 0 ; i < m_vecEffect.size(); ++i)
    {
        SAFE_DELETE(m_vecEffect[i]);
    }

    delete m_instance;
}
Effect* EffectManager::GetAvailableEffect()
{
    //searching can use bullet

    int initialIdx = m_vecEffectIdxPos;
    int i;


    //search Idx ~ m_possesionBullet
    for(i = m_vecEffectIdxPos; i <m_possesionEffectCount; ++i)
    {
        m_vecEffectIdxPos++;
        if(m_vecEffect[i]->IsCanUse())
        {
            m_canUseEffectCount--;
			m_vecEffect[i]->Reset();
            return m_vecEffect[i];

        }
    }
    m_vecEffectIdxPos = 0;
    //search 0 ~ Idx
    for(i = 0; i < initialIdx; ++i)
    {
        m_vecEffectIdxPos++;
        if(m_vecEffect[i]->IsCanUse())
        {
            m_canUseEffectCount--;
            return m_vecEffect[i];
        }
    }



    //if not have a bullet, add more
    for(int i = 0 ; i < 30; ++i)
    {
        Effect* temp = new Effect();

        CreateEffect(temp);
    }

    return GetAvailableEffect();



}

void EffectManager::CreateEffect(Effect* effect)
{
    m_vecEffect.push_back(effect);
    m_canUseEffectCount++;
    m_possesionEffectCount++;
}
EffectManager* EffectManager::GetInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new EffectManager();
    }

    return m_instance;
}
void EffectManager::Update()
{
    //GameManager::GetInstance()->gotoxy(2,10);
    //std::cout << "possesion : " << m_possesionEffectCount;
    //GameManager::GetInstance()->gotoxy(2,11);
    //std::cout << "can use: " << m_canUseEffectCount;

    for(size_t i = 0; i < m_vecEffect.size(); ++i)
    {
        if(m_vecEffect[i]->IsActive())
        {
           m_vecEffect[i]->Update();
        }
    }

}
