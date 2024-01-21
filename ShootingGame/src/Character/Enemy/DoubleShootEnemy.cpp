#include "Character\Enemy\DoubleShootEnemy.h"
#include "Manager/GameManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/PrintManager.h"
#include "Utils/Utils.h"
#include "Manager/BulletManager.h"
#include "Character/Player/Player.h"
#include <iostream>

#define MOVE_DIR_RAND_MIN 0
#define MOVE_DIR_RAND_MAX 5

DoubleShootEnemy::DoubleShootEnemy(int x, int y) :
	m_shouldShootCount(3)
{
	SetGamePos(x, y);
	m_character = L"<(:)>";
	m_hp = 4;
	m_fireRate = 130;
	m_eMoveDir = eDirect::Down;
	m_moveDelay = 5;
	
	m_sizeX = 5;
	m_bulletMoveDelay = 3;


	m_eDoubleShootEnemey_State = eDoubleShootEnemey_State::Move;
	m_shootCount = 0;
	m_setInDownDir_distDiff = 3;
	m_setInLeftOrRightDir_distDiff = 2;

	m_ShootingCycleTimer.SetFixedTime(4.0f);

	m_moveDirChangeTimer.SetFixedTime(3.5f);
	m_ShootingFireRateTimer.SetFixedTime(0.15f);

	EnemyManager::GetInstance()->AddEnemy(this);

}

DoubleShootEnemy::~DoubleShootEnemy()
{
}

void DoubleShootEnemy::Update()
{
	if (IsActive())
	{



		//정해진 시간마다 MoveDir를 바꿈 (4초)
		MoveDirChangeCycleCheckAndSet();
		//4초마다 Shoot상태로 전환
		ShootingCycleCheckAndSet();
		//맵밖으로 못나가게 막음
		PreventIncorrectDir();


		//위에서 정한 스테이트에 따라 Move또는 Shoot
		switch(m_eDoubleShootEnemey_State)
		{
			case eDoubleShootEnemey_State::Move:
				Move();
				break;

			case eDoubleShootEnemey_State::Shoot:
				Shoot();
				break;
			default:
				break;
		}

		if (IsActive())
		{
			//if Enemy is out of range, Move() is has already set Active to false
			Render();
			
		}

		



	}
}

void DoubleShootEnemy::Render()
{
	//GameManager::GetInstance()->gotoxy(m_absolutePos.x, m_absolutePos.y);
	//wprintf_s(L"%s", m_character);

	PrintManager::GetInstance()->Print(m_absolutePos.x, m_absolutePos.y , m_character);
}

void DoubleShootEnemy::Reset()
{
	m_hp = m_maxHp;
}

void DoubleShootEnemy::MoveDirChangeCycleCheckAndSet()
{
	//처음에 바로 Dir을 변경하는것이 아닌 약간 텀을 주고 변경하기 위해 0.3~1.0 초 가 지나면 방향이 변경된다
	//이 코드는 한 번만 실행 됨
	if (m_firstDirChangeTimer.IsFirstRun())
	{
		float randNumf = Utils::GetInstance()->GetRandFloatNum(0.3f, 1.0f);

		m_firstDirChangeTimer.SetFixedTime(randNumf);

		m_firstDirChangeTimer.StartOrRestart();

	}

	if (m_moveDirChangeTimer.IsFirstRun() && m_firstDirChangeTimer.IsTimeOver())
	{
		m_moveDirChangeTimer.StartOrRestart();
	}
	else if (m_moveDirChangeTimer.IsTimeOver())
	{
		MoveDirChange();
		m_moveDirChangeTimer.StartOrRestart();
	}

}

void DoubleShootEnemy::ShootDirChangeCycleCheckAndSet()
{
}

void DoubleShootEnemy::MoveDirChange()
{
	
	int randNum = 0;
	while (true)
	{
		//위,아래,좌,우,대각(좌), 대각(우)
		randNum = Utils::GetInstance()->GetRandIntNum(MOVE_DIR_RAND_MIN, MOVE_DIR_RAND_MAX);

		

		//벽 끝에 있으면 안 나가도록 방향 재설정
		if (((randNum == Left || randNum == Left_down_diagonal) && GetGamePosX() <= 0) ||
			((randNum == Right || randNum == Right_down_diagonal) && GetRightSideGamePosX() >= MAP_WIDTH) ||
			(randNum == Up && GetGamePosY() <= 0)||
			(randNum == Down && GetGamePosY() >= MAP_HEIGHT))
		{
			continue;
		}
		else
		{
			break;
		}



	}



	switch (randNum)
	{

		case MovableDir::Up:
			m_eMoveDir = eDirect::Up;
			break;
		case MovableDir::Down:
			m_eMoveDir = eDirect::Down;
			break;
		case MovableDir::Right:
			m_eMoveDir = eDirect::Right;
			break;
		case MovableDir::Left:
			m_eMoveDir = eDirect::Left;
			break;
		case MovableDir::Right_down_diagonal:
			m_eMoveDir = eDirect::Right_Down_Diagonal;
			break;
		case MovableDir::Left_down_diagonal:
			m_eMoveDir = eDirect::Left_Down_Diagonal;
			break;
		default:
			assert(false);
			break;


	}
}

void DoubleShootEnemy::Shoot()
{
	if(m_shootCount < m_shouldShootCount)
	{

		if(m_ShootingFireRateTimer.IsTimeOver())
		{

			Bullet* leftBullet = BulletManager::GetInstance()->GetAvailableBullet();
			leftBullet->SetOwner(eBullet_Owner::Enemy);
			leftBullet->SetSpeed(m_bulletMoveDelay);
			leftBullet->SetActive(true);

			Bullet* rightBullet = BulletManager::GetInstance()->GetAvailableBullet();
			rightBullet->SetOwner(eBullet_Owner::Enemy);			
			rightBullet->SetSpeed(m_bulletMoveDelay);
			rightBullet->SetActive(true);

			if(GetGamePosY() > GameManager::GetInstance()->GetPlayer()->GetGamePosY())
			{
				leftBullet->SetGamePos(GetGamePosX() + 2, m_absolutePos.y - 1);
				leftBullet->SetDir(eDirect::Left_Up_Diagonal);
				rightBullet->SetGamePos(GetRightSideGamePosX() - 1, m_absolutePos.y - 1);
				rightBullet->SetDir(eDirect::Right_Up_Diagonal);
			}
			else
			{
				leftBullet->SetGamePos(GetGamePosX() + 2, m_absolutePos.y + 1);
				leftBullet->SetDir(eDirect::Left_Down_Diagonal);
				rightBullet->SetGamePos(GetRightSideGamePosX() - 1, m_absolutePos.y + 1);
				rightBullet->SetDir(eDirect::Right_Down_Diagonal);
			}

			
			m_shootCount++;

			m_ShootingFireRateTimer.StartOrRestart();
		}




	}
	else if(m_shootCount >= m_shouldShootCount)
	{
		m_shootCount = 0;
		m_eDoubleShootEnemey_State = eDoubleShootEnemey_State::Move;
	}
}

void DoubleShootEnemy::ShootDirChange()
{
}

void DoubleShootEnemy::PreventIncorrectDir()
{
	bool isMoveDirChange = false;

	if(GetGamePosX() <= 0)
	{
		while((m_eMoveDir == eDirect::Left || m_eMoveDir == eDirect::Left_Down_Diagonal))
		{
			MoveDirChange();
		}

		isMoveDirChange = true;
	}
	if(GetRightSideGamePosX() >= MAP_WIDTH)
	{
		while((m_eMoveDir == eDirect::Right || m_eMoveDir == eDirect::Right_Down_Diagonal))
		{
			MoveDirChange();
		}

		isMoveDirChange = true;
	}
	if(GetGamePosY() >= MAP_HEIGHT)
	{
		while((m_eMoveDir == eDirect::Down || m_eMoveDir == eDirect::Left_Down_Diagonal ||
			m_eMoveDir == eDirect::Right_Down_Diagonal))
		{
			MoveDirChange();
		}
		isMoveDirChange = true;
	}
	if(GetGamePosY() <= 0)
	{
		while(m_eMoveDir == eDirect::Up)
		{
			MoveDirChange();
		}

		isMoveDirChange = true;
	}

	if(isMoveDirChange)
	{
		m_moveDirChangeTimer.SetDisposableTime(2.0f);
	}
	
	
}

void DoubleShootEnemy::ShootingCycleCheckAndSet()
{
	if(m_ShootingCycleTimer.IsFirstRun())
	{
		m_ShootingCycleTimer.StartOrRestart();
	}
	else if(m_ShootingCycleTimer.IsTimeOver())
	{
		m_eDoubleShootEnemey_State = eDoubleShootEnemey_State::Shoot;
		m_ShootingCycleTimer.StartOrRestart();
	}
}
