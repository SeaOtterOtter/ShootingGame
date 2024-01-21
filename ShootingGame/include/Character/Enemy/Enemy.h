#pragma once
#include <chrono>


#include "Utils/Timer.h"
#include "Game/Flag.h"
#include "../Character.h"




class Enemy : public Character
{
    public:
        Enemy();
        virtual ~Enemy();

   

    public:
        bool IsActive();
        void SetActive(bool value);
        void SetDirect(eDirect direct);
        void Move();
    public:
        virtual void CollideWithBullet(Bullet& bullet) override;
        virtual void MoveUp() override;
        virtual void MoveDown() override;
        virtual void MoveRight() override;
        virtual void MoveLeft() override;
        virtual void MoveRightDownDiagonal() override;
        virtual void MoveLeftDownDiagonal() override;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void Reset() = 0;

    protected:

        
        void MoveToCurDirect();
        void Die();
        virtual void MoveDirChangeCycleCheckAndSet() = 0;
        virtual void ShootDirChangeCycleCheckAndSet() = 0;
        virtual void MoveDirChange() = 0;
        virtual void Shoot() = 0;
        virtual void ShootDirChange() = 0;
        virtual void PreventIncorrectDir() = 0;
        
    private:
        
        
    protected:
        int m_fireRate;
        int m_currentFireRateDelayCount;
        int m_maxHp;
       
        Timer m_moveDirChangeTimer;
        Timer m_shootDirChangeTimer;
        Timer m_firstDirChangeTimer;
        //Distance difference set in a straight Director
        int m_setInDownDir_distDiff;
        int m_setInLeftOrRightDir_distDiff;



        eDirect m_eShootDir;
        eDirect m_eMoveDir;

        bool m_bActive;

       
   
};

