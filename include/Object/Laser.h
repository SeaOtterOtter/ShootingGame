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
	//���� �ֱٿ� �������� ���� ��ǥ�� (���ﶧ ���)
	int occurredLaserPosX;
	int occurredLaserPosY;
	
};

