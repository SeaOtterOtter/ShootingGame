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

	//���߿� delete �ؾߵ�
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

		//MoveBeforeLase��尡 �ƴ� ���� ���� 

		//������ �ð����� MoveDir�� �ٲ� (4��)
		MoveDirChangeCycleCheckAndSet();
		//4�ʸ��� Shoot���·� ��ȯ
		LasingCycleCheckAndSet();
		//�ʹ����� �������� ����
		PreventIncorrectDir();


		//������ ���� ������Ʈ�� ���� Move�Ǵ� Shoot
		switch(m_eLaserEnemy_State)
		{
			case eLaserEnemy_State::Move:
				Move();
				break;

			//Lase���°� �Ǹ� ���۽����� �̵� 
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
	//�ױ����� �θ� �ִ� �⺻ �Լ� ����
	Enemy::CollideWithBullet(bullet);
	//������ ���ֱ�
	m_leftLaser->HideLaser();
	m_rightLaser->HideLaser();
}

void LaserEnemy::MoveDirChangeCycleCheckAndSet()
{//ó���� �ٷ� Dir�� �����ϴ°��� �ƴ� �ణ ���� �ְ� �����ϱ� ���� 0.3~1.0 �� �� ������ ������ ����ȴ�
	//�� �ڵ�� �� ���� ���� ��
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
		//��,��,�Ʒ�
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
	//���� Move������ ���� LasingCycleTimer �ʱ�ȭ 
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

			//������ ���� �ٲ� ��, �̵� �ؾߵǴϱ� ������ ī��Ʈ 0����
			m_currentMoveDelayCount = 0;
			
		}
	}
}

void LaserEnemy::MoveBeforeLase()
{
	
	

	//����� �� ���� �� ���� Ž���Ͽ� ����
	if(m_bShouldSetStopPos)
	{
		stopPointPos.x = GameManager::GetInstance()->GetPlayer()->GetGameMiddlePosX();
		m_bShouldSetStopPos = false;
	}
	
	


	//�̵��ӵ� ����
	m_moveDelay = m_beforeLaseMoveDelay;
	
	//�� middlePos�� stopPoint�� �� ������ ��� �̵� , �� �̵� ������ Lase���� �ٲٱ�
	if(GetGameMiddlePosX() == stopPointPos.x)
	{
		m_eLaserAttack_State = eLaserAttack_State::Lase;
	}
	else
	{
		//���� ������ �� ������ �ٴµ� ���߿� ����
		if(GetGameMiddlePosX() < stopPointPos.x)
		{
			
			m_eMoveDir = eDirect::Right;
			
		}
		else
		{
			m_eMoveDir = eDirect::Left;
			
		}

		//�߰��� ������ �� ������ ��������� Lase���� ��ȯ
		if((m_eMoveDir == eDirect::Right && GetRightSideGamePosX() < MAP_WIDTH) ||
			(m_eMoveDir == eDirect::Left && GetGamePosX() > 0))
		{
			//stopPointPos�� ��ġ �� �������� �̵�
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
		//���� LasingDurationTimer�� ���� �ȳ����� �������� ��� ������
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

//Move���� �ǵ����� ��, ������ �ùٸ��� �ʱ�ȭ
void LaserEnemy::RevertToMoveState()
{
	
	
	//Move�� ������ ��, ���� �̵� ���⿡ �´� Delay ����
	SetCorrectMoveDelay();
	m_bShouldSetStopPos = true;
	//Lase()���� Ÿ�̸Ӱ� ����ǰ� �ϱ� ���� true�� �ٲٱ�
	m_bShouldLasingDurationTimerStart = true;
	m_LasingCycleTimer.StartOrRestart();

	m_eLaserAttack_State = eLaserAttack_State::MoveBeforeLase;
	m_eLaserEnemy_State = eLaserEnemy_State::Move;
}
