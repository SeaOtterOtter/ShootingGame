#pragma once

#include "Obj.h"
#include "Game/Flag.h"


class LaserEnemy;

class Laser : public Obj
{
public:
	Laser(LaserEnemy* owner , eLaserShootPosition laserShootPosition);
	virtual ~Laser();

public:
	virtual void Update() override; 
	virtual void Render() override;
	void ShowLaser();
	void HideLaser();
private:
	void CheckCollisionWithPlayer();
	void SetPositionFromLaserEnemy();
private:
	wchar_t* m_laserSideEffect;
	LaserEnemy* m_owner;
	eLaserShootPosition m_eLaserShootPosition;
	//가장 최근에 레이져가 쏴진 좌표들 (지울때 사용)
	int occurredLaserPosX;
	int occurredLaserPosY;
	
};

