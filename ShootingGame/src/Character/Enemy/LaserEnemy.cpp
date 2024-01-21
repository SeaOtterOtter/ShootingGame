#include <iostream>
#include "Character/Enemy/LaserEnemy.h"
#include "Utils/Utils.h"
#include "Manager/GameManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/PrintManager.h"
#include "Character/Player/Player.h"
#include "Game/Game.h"
#include "Object/Laser.h"
#include "Effect/Effect.h"


#define MOVE_DIR_RAND_MIN 0
#define MOVE_DIR_RAND_MAX 2

LaserEnemy::LaserEnemy(int x, int y):
	m_downMoveDelay(60),
	m_horizontalMoveDelay(40),
	m_beforeLaseMoveDelay(1)
{
	SetGamePos(x, y);
	m_character = L"|_|::|_|";
	m_hp = 4;
	m_fireRate = 130;
	m_eMoveDir = eDirect::Down;
	m_moveDelay = 5;
	
	m_sizeX = 8;
	m_bulletMoveDelay = 3;


	
	m_eLaserEnemy_State = eLaserEnemy_State::Move;
	m_eLaserAttack_State = eLaserAttack_State::MoveBeforeLase;
	
	
	m_bShouldSetStopPos = true;
	m_bShouldLasingDurationTimerStart = true;
	m_setInDownDir_distDiff = 3;
	m_setInLeftOrRightDir_distDiff = 2;

	

	m_moveDirChangeTimer.SetFixedTime(4.0f);

	m_LasingCycleTimer.SetFixedTime(5.0f);
	m_LasingDurationTimer.SetFixedTime(2.0f);

	//나중에 delete 해야됨
	m_leftLaser = new Laser(this, eLaserShootPosition::Left);
	m_rightLaser = new Laser(this , eLaserShootPosition::Right);

	
	
	EnemyManager::GetInstance()->AddEnemy(this);
	
}

LaserEnemy::~LaserEnemy()
{

}

void LaserEnemy::Update()
{
	if(IsActive())
	{

		//MoveBeforeLase모드가 아닐 때만 실행 

		//정해진 시간마다 MoveDir를 바꿈 (4초)
		MoveDirChangeCycleCheckAndSet();
		//4초마다 Shoot상태로 전환
		LasingCycleCheckAndSet();
		//맵밖으로 못나가게 막음
		PreventIncorrectDir();


		//위에서 정한 스테이트에 따라 Move또는 Shoot
		switch(m_eLaserEnemy_State)
		{
			case eLaserEnemy_State::Move:
				Move();
				break;

			//Lase상태가 되면 갑작스럽게 이동 
			case eLaserEnemy_State::Lase:
				MoveAndLase();
				
				break;
			default:
				assert(false);
				break;
		}

		if(IsActive())
		{
			//if Enemy is out of range, Move() is has already set Active to false
			Render();
			
		}


		


	}
}

void LaserEnemy::Render()
{
	//GameManager::GetInstance()->gotoxy(m_absolutePos.x, m_absolutePos.y);
	//wprintf_s(L"%s", m_character);

	PrintManager::GetInstance()->Print(m_absolutePos.x, m_absolutePos.y, m_character);


	/*GameManager::GetInstance()->gotoxy(3, 14);
	if(m_eLaserEnemy_State == eLaserEnemy_State::Move)
	{
		std::cout << "Move";
	}
	else
	{
		std::cout << "Lase";
	}
	GameManager::GetInstance()->gotoxy(3, 15);
	std::cout << "Cycle : " << m_LasingCycleTimer.GetElapsedTime();
	GameManager::GetInstance()->gotoxy(3, 16);
	std::cout << "Duration : " << m_LasingDurationTimer.GetElapsedTime();
	GameManager::GetInstance()->gotoxy(3, 17);
	if(m_eLaserAttack_State == eLaserAttack_State::Lase)
	{
		std::cout << "State :: Lase";
	}
	else
	{
		std::cout << "State :: MBFL";
	}*/

}

void LaserEnemy::Reset()
{
	m_hp = m_maxHp;
}

void LaserEnemy::CollideWithBullet(Bullet& bullet)
{
	//죽기전에 부모에 있는 기본 함수 실행
	Enemy::CollideWithBullet(bullet);
	//레이져 없애기
	m_leftLaser->HideLaser();
	m_rightLaser->HideLaser();
}

void LaserEnemy::MoveDirChangeCycleCheckAndSet()
{//처음에 바로 Dir을 변경하는것이 아닌 약간 텀을 주고 변경하기 위해 0.3~1.0 초 가 지나면 방향이 변경된다
	//이 코드는 한 번만 실행 됨
	if(m_eLaserEnemy_State == eLaserEnemy_State::Move)
	{
		if(m_firstDirChangeTimer.IsFirstRun())
		{
			float randNumf = Utils::GetInstance()->GetRandFloatNum(0.3f, 1.0f);

			m_firstDirChangeTimer.SetFixedTime(randNumf);

			m_firstDirChangeTimer.StartOrRestart();

		}

		if(m_moveDirChangeTimer.IsFirstRun() && m_firstDirChangeTimer.IsTimeOver())
		{
			m_moveDirChangeTimer.StartOrRestart();
		}
		else if(m_moveDirChangeTimer.IsTimeOver())
		{
			MoveDirChange();
			m_moveDirChangeTimer.StartOrRestart();
		}
	}
	
}

void LaserEnemy::ShootDirChangeCycleCheckAndSet()
{
}

void LaserEnemy::MoveDirChange()
{
	int randNum = 0;
	while(true)
	{
		//좌,우,아래
		randNum = Utils::GetInstance()->GetRandIntNum(MOVE_DIR_RAND_MIN, MOVE_DIR_RAND_MAX);


		if((randNum == Left && GetGamePosX() <= 0) || (randNum == Right && GetRightSideGamePosX() >= MAP_WIDTH))
		{
			continue;
		}
		else
		{
			break;
		}



	}



	switch(randNum)
	{

		case MovableDir::Down:
			m_eMoveDir = eDirect::Down;
			
			break;
		case MovableDir::Left:
			m_eMoveDir = eDirect::Left;
			
			break;
		case MovableDir::Right:
			m_eMoveDir = eDirect::Right;
			
			break;
		default:
			assert(false);
			break;


	}

	SetCorrectMoveDelay();
}

void LaserEnemy::Shoot()
{
	//Change State to BeforeLaseMove
	MoveBeforeLase();

}

void LaserEnemy::ShootDirChange()
{
	
}

void LaserEnemy::PreventIncorrectDir()
{
	
	if(GetGamePosX() <= 0)
	{
		while(m_eMoveDir == eDirect::Left)
		{
			MoveDirChange();
		}

		m_moveDirChangeTimer.StartOrRestart();
	}
	if(GetRightSideGamePosX() >= 45)
	{
		while(m_eMoveDir == eDirect::Right)
		{
			MoveDirChange();
		}

		m_moveDirChangeTimer.StartOrRestart();
	}
	if(GetGamePosY() <= 0)
	{
		while(m_eMoveDir == eDirect::Up)
		{
			MoveDirChange();
		}

		m_moveDirChangeTimer.StartOrRestart();
	}
}

void LaserEnemy::LasingCycleCheckAndSet()
{
	//현재 Move상태일 때만 LasingCycleTimer 초기화 
	if(m_eLaserEnemy_State == eLaserEnemy_State::Move)
	{
		if(m_LasingCycleTimer.IsFirstRun())
		{
			m_LasingCycleTimer.StartOrRestart();
		}
		else if(m_LasingCycleTimer.IsTimeOver())
		{
			m_eLaserEnemy_State = eLaserEnemy_State::Lase;
			m_eLaserAttack_State = eLaserAttack_State::MoveBeforeLase;

			//레이저 모드로 바뀐 뒤, 이동 해야되니까 딜레이 카운트 0으로
			m_currentMoveDelayCount = 0;
			
		}
	}
}

void LaserEnemy::MoveBeforeLase()
{
	
	

	//멈춰야 될 지점 한 번만 탐색하여 설정
	if(m_bShouldSetStopPos)
	{
		stopPointPos.x = GameManager::GetInstance()->GetPlayer()->GetGameMiddlePosX();
		m_bShouldSetStopPos = false;
	}
	
	


	//이동속도 변경
	m_moveDelay = m_beforeLaseMoveDelay;
	
	//내 middlePos가 stopPoint가 될 떄까지 계쏙 이동 , 다 이동 됐으면 Lase모드로 바꾸기
	if(GetGameMiddlePosX() == stopPointPos.x)
	{
		m_eLaserAttack_State = eLaserAttack_State::Lase;
	}
	else
	{
		//지금 무조건 벽 끝까지 붙는데 나중에 수정
		if(GetGameMiddlePosX() < stopPointPos.x)
		{
			
			m_eMoveDir = eDirect::Right;
			
		}
		else
		{
			m_eMoveDir = eDirect::Left;
			
		}

		//중간에 벽뚫할 것 같으면 멈춰버리고 Lase모드로 전환
		if((m_eMoveDir == eDirect::Right && GetRightSideGamePosX() < MAP_WIDTH) ||
			(m_eMoveDir == eDirect::Left && GetGamePosX() > 0))
		{
			//stopPointPos에 위치 안 했을때만 이동
			if(GetGameMiddlePosX() != stopPointPos.x)
				Move();
			
			
		}
		else
		{
			m_eLaserAttack_State = eLaserAttack_State::Lase;
		}
		
	}

	
	
}

void LaserEnemy::Lase()
{

	if(m_bShouldLasingDurationTimerStart)
	{
		m_LasingDurationTimer.StartOrRestart();
		m_bShouldLasingDurationTimerStart = false;

	}


	
	if(!m_LasingDurationTimer.IsTimeOver())
	{
		//현재 LasingDurationTimer가 끝이 안났으면 레이져를 계속 보여줌
		m_leftLaser->ShowLaser();
		m_rightLaser->ShowLaser();

	}
	else
	{
		
		m_leftLaser->HideLaser();
		m_rightLaser->HideLaser();
		RevertToMoveState();
		
	}


	


	
	
}

void LaserEnemy::MoveAndLase()
{

	switch(m_eLaserAttack_State)
	{
		case eLaserAttack_State::MoveBeforeLase:
			MoveBeforeLase();
			break;
		case eLaserAttack_State::Lase:
			Lase();
			break;
		default:
			assert(false);
	}
	
}

void LaserEnemy::SetCorrectMoveDelay()
{
	switch(m_eMoveDir)
	{
		case eDirect::Left:
			[[fallthrough]];
		case eDirect::Right:
			m_moveDelay = m_horizontalMoveDelay;
			break;

		case eDirect::Down:
			m_moveDelay = m_downMoveDelay;
			break;

		default:
			assert(false);
			break;
	}
}

//Move모드로 되돌리기 전, 설정들 올바르게 초기화
void LaserEnemy::RevertToMoveState()
{
	
	
	//Move로 변경한 뒤, 현재 이동 방향에 맞는 Delay 설정
	SetCorrectMoveDelay();
	m_bShouldSetStopPos = true;
	//Lase()에서 타이머가 실행되게 하기 위해 true로 바꾸기
	m_bShouldLasingDurationTimerStart = true;
	m_LasingCycleTimer.StartOrRestart();

	m_eLaserAttack_State = eLaserAttack_State::MoveBeforeLase;
	m_eLaserEnemy_State = eLaserEnemy_State::Move;
}
