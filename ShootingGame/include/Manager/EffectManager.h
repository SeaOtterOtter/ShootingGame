#pragma once
#include <vector>
#include "Effect/Effect.h"
#include "IManager.h"


class EffectManager : public IManager
{
    public:
        static EffectManager* GetInstance();
        void CreateEffect(Effect* effect);
        
        Effect* GetAvailableEffect();
        void IncreaseCanUseEffectCount();
        void Release();

        virtual void Start() override;
        virtual void Update() override;
    private:
        EffectManager();
        virtual ~EffectManager();

    private:
        static EffectManager* m_instance;
        std::vector<Effect*> m_vecEffect;
        int m_possesionEffectCount;
        int m_vecEffectIdxPos;
        int m_canUseEffectCount;



        // IManager을(를) 통해 상속됨
       

};


