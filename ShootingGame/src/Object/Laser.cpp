
#include "Object\Laser.h"
#include "Manager/GameManager.h"
#include "Manager/PrintManager.h"
#include "Character/Enemy/LaserEnemy.h"
#include "Manager/ObjManager.h"
#include "Character/Player/Player.h"



Laser::Laser(LaserEnemy* owner, eLaserShootPosition laserShootPosition)
{
	m_eLaserShootPosition = laserShootPosition;
	m_owner = owner;
	m_laserSideEffect = L":";
	m_character = L"|";

	//나중에 LaserEnemey에서 호출할 때 나타나도록 일단 false
	SetActive(false);

	ObjManager::GetInstance()->AddObj(this);
}

Laser::~Laser()
{
}

void Laser::Update()
{
	if(m_bActive)
	{
		SetPositionFromLaserEnemy();
		CheckCollisionWithPlayer();
		Render();

	}
}

void Laser::Render()
{
	//LaserEnemey의 포지션에 맞춰 적절하게 Laser포지션 설정
	
	for(int i = 0; i < MAP_HEIGHT - m_gamePos.y + 1; ++i)
	{


		PrintManager::GetInstance()->Print(m_absolutePos.x - 1, m_absolutePos.y + i , m_laserSideEffect , ePrint_Color::Dark_Yellow);
		PrintManager::GetInstance()->Print(m_absolutePos.x, m_absolutePos.y + i, m_character, ePrint_Color::Red);
		PrintManager::GetInstance()->Print(m_absolutePos.x + 1, m_absolutePos.y + i, m_laserSideEffect, ePrint_Color::Dark_Yellow);
		
	}

	occurredLaserPosX = m_absolutePos.x;
	occurredLaserPosY = m_absolutePos.y;
}

void Laser::ShowLaser()
{
	SetActive(true);
}

void Laser::HideLaser()
{
	for(int i = 0; i < MAP_HEIGHT - m_gamePos.y + 1; ++i)
	{


		PrintManager::GetInstance()->PrintSpace(occurredLaserPosX - 1, occurredLaserPosY + i);
		PrintManager::GetInstance()->PrintSpace(occurredLaserPosX, occurredLaserPosY + i);
		PrintManager::GetInstance()->PrintSpace(occurredLaserPosX + 1, occurredLaserPosY + i);
		
	}

	SetActive(false);
}

void Laser::CheckCollisionWithPlayer()
{
	Player* tempPlayer = GameManager::GetInstance()->GetPlayer();

	bool isCollision = false;
	if(tempPlayer->GetGamePosX() <= GetGamePosX() -1 && tempPlayer->GetRightSideGamePosX() >= GetGamePosX() -1)
	{
		isCollision = true;
	}
	if (tempPlayer->GetGamePosX() <= GetGamePosX() - 1 && tempPlayer->GetRightSideGamePosX() >= GetGamePosX() + 1)
	{
		isCollision = true;
	}
	if (tempPlayer->GetGamePosX() >= GetGamePosX() - 1 && tempPlayer->GetGamePosX() <= GetGamePosX() + 1)
	{
		isCollision = true;
	}


	//플레이어 정상적인 상태일 때 충돌
	if (isCollision)
	{
		tempPlayer->CollideWithLaser(*this);
		
	}
	
}

void Laser::SetPositionFromLaserEnemy()
{
	switch (m_eLaserShootPosition)
	{
	case eLaserShootPosition::Left:
		SetGamePos(m_owner->GetGamePosX() + 1, m_owner->GetGamePosY() + 1);
		break;
	case eLaserShootPosition::Right:
		SetGamePos(m_owner->GetGamePosX() + 6, m_owner->GetGamePosY() + 1);
		break;
	default:
		assert(false);
		break;
	}
}
