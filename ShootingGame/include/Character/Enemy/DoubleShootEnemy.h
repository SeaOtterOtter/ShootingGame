#pragma once
#include "Enemy.h"

class Timer;


class DoubleShootEnemy : public Enemy
{
public:
	DoubleShootEnemy() = delete;
    DoubleShootEnemy(int x, int y);
	virtual ~DoubleShootEnemy();
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

private:

    eDoubleShootEnemey_State m_eDoubleShootEnemey_State;
    int m_shootCount;
    const int m_shouldShootCount;
    Timer m_ShootingCycleTimer;
    Timer m_ShootingFireRateTimer;
    enum MovableDir
    {
        Up, Down, Right, Left, Right_down_diagonal, Left_down_diagonal
    };
};

