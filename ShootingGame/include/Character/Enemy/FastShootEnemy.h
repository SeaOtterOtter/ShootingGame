#pragma once

#include "Enemy.h"
class Timer;

class FastShootEnemy : public Enemy
{
	public:
		FastShootEnemy() = delete;
        FastShootEnemy(int x, int y);
		virtual ~FastShootEnemy();
        virtual void Update() override;
        virtual void Render() override;
        virtual void Reset() override;
    protected:

        virtual void MoveDirChangeCycleCheckAndSet() override;
        virtual void ShootDirChangeCycleCheckAndSet() override;
        virtual void MoveDirChange() override;
        virtual void Shoot() override;
        virtual void ShootDirChange() override;
        virtual void PreventIncorrectDir() override;
        

    private:

        void ShootingCycleCheckAndSet();
        void SetCorrectMoveDelay();
    private:
        
        eFastShootEnemy_State m_eFastShootEnemey_State;
        int m_shootCount;
        const int m_shouldShootCount;
        const int m_downMoveDelay;
        const int m_horizontalMoveDelay;
        Timer m_ShootingCycleTimer;
        Timer m_ShootingFireRateTimer;
        enum MovableDir
        {
            Down, Right, Left
        };
};

