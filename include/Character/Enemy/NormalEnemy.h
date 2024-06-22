#pragma once
#include "Character/Enemy/Enemy.h"

class NormalEnemy : public Enemy
{
    public:
        NormalEnemy() = delete;
        NormalEnemy(int x, int y);
        virtual ~NormalEnemy();
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
        
       //�̵� ������ �κ��� �迭�� �ֱ� 

    private:
        enum MovableDir
        {
            None, Down, Right_down_diagonal, Left_down_diagonal
        };
   
        

};

