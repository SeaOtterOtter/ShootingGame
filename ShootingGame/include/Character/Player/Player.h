#pragma once
#include "Character/Character.h"
#include "Utils/Timer.h"


class Player : public Character
{
	friend class GameManager;
public:
    Player();
    virtual ~Player();
public:
    virtual void CollideWithBullet(class Bullet& bullet) override;
    void CollideWithLaser(class Laser& laser);
    virtual void MoveUp() override;
    virtual void MoveDown()  override;
    virtual void MoveRight() override;
    virtual void MoveLeft() override;
    virtual void Update() override;
    virtual void Render() override;

	void Shoot();
		

    void KeyDownCheck(int key);
private:
	void Die();

private:
	std::vector<int> m_vecShootPos;
	int m_fireRate;
	int m_currentFireRateDelayCount;
	int m_life;
	Timer m_laserHitDelayTimer;
	const float m_laserHitDelay;
		
};

