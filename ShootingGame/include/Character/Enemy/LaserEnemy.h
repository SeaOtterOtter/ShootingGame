#pragma once
#include "Enemy.h"


class Laser;

class LaserEnemy : public Enemy
{
public:
	LaserEnemy() = delete;
    LaserEnemy(int x, int y);
	virtual ~LaserEnemy();
    virtual void Update() override;
    virtual void Render() override;
    virtual void Reset() override;
protected:

    virtual void CollideWithBullet(Bullet& bullet) override;
    virtual void MoveDirChangeCycleCheckAndSet() override;
    virtual void ShootDirChangeCycleCheckAndSet() override;
    virtual void MoveDirChange() override;
    virtual void Shoot() override;
    virtual void ShootDirChange() override;
    virtual void PreventIncorrectDir() override;
private:
    void LasingCycleCheckAndSet();
    void MoveBeforeLase();
    void Lase();
    void MoveAndLase();
    void SetCorrectMoveDelay();
    void RevertToMoveState();
private:
    const int m_downMoveDelay;
    const int m_horizontalMoveDelay;
    const int m_beforeLaseMoveDelay;
    //레이저를 쏠때 멈추는 지점을 탐색해야 하는지 아닌지
    bool m_bShouldSetStopPos;
    bool m_bShouldLasingDurationTimerStart;
    eLaserEnemy_State m_eLaserEnemy_State;
    eLaserAttack_State m_eLaserAttack_State;
    
    Timer m_LasingCycleTimer;
    Timer m_LasingDurationTimer;
    Position stopPointPos;

    Laser* m_leftLaser;
    Laser* m_rightLaser;

    enum MovableDir
    {
        Down, Left, Right
    };
};

