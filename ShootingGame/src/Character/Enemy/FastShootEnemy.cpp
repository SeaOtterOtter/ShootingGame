#include "Character/Enemy/FastShootEnemy.h"

#include "Manager/GameManager.h"
#include "Utils/Utils.h"
#include "Manager/BulletManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/PrintManager.h"

#define MOVE_DIR_RAND_MIN 0
#define MOVE_DIR_RAND_MAX 2

//대각선 이동 불가능 
FastShootEnemy::FastShootEnemy(int x, int y) :
    m_shouldShootCount(5),
    m_downMoveDelay(60),
    m_horizontalMoveDelay(5)
{
    SetGamePos(x, y);
	m_character = L"<*|*>";
    m_hp = 4;
    m_fireRate = 130;
    m_eMoveDir = eDirect::Down;
    m_moveDelay = 40;
    
    m_sizeX = 5;
    m_bulletMoveDelay = 2;

    

    m_setInDownDir_distDiff = 3;
    m_setInLeftOrRightDir_distDiff = 2;

    
    m_eFastShootEnemey_State = eFastShootEnemy_State::Move;
    m_shootCount = 0;
    m_ShootingCycleTimer.SetFixedTime(4.0f);

    m_moveDirChangeTimer.SetFixedTime(5.0f);
    m_ShootingFireRateTimer.SetFixedTime(0.15f);

    EnemyManager::GetInstance()->AddEnemy(this);
}

FastShootEnemy::~FastShootEnemy()
{
}

void FastShootEnemy::Update()
{
    if (IsActive())
    {

        

        //set the move Dir every 3.5 second
        MoveDirChangeCycleCheckAndSet();
        ShootingCycleCheckAndSet();
        //prevent monster from out the map by setting the correct Dir
        PreventIncorrectDir();

        
        switch (m_eFastShootEnemey_State)
        {
            case eFastShootEnemy_State::Move:
                Move();
                break;

            case eFastShootEnemy_State::Shoot:
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

void FastShootEnemy::Render()
{
    //GameManager::GetInstance()->gotoxy(m_absolutePos.x, m_absolutePos.y);
    //wprintf_s(L"%s", m_character);

	PrintManager::GetInstance()->Print(m_absolutePos.x, m_absolutePos.y, m_character);

}

void FastShootEnemy::Reset()
{
    m_hp = m_maxHp;
}

void FastShootEnemy::MoveDirChangeCycleCheckAndSet()
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
    else if(m_moveDirChangeTimer.IsTimeOver())
    {
        MoveDirChange();
        m_moveDirChangeTimer.StartOrRestart();
    }

   
}

void FastShootEnemy::ShootDirChangeCycleCheckAndSet()
{
    
}

void FastShootEnemy::MoveDirChange()
{
    //randomly

    //minus 4 = because NormalEnemy do not use Horizontal Move and Up Move (3)
    int randNum = 0;
    while (true)
    {
        //avoid wrong dir(out of range) setting
        randNum = Utils::GetInstance()->GetRandIntNum(MOVE_DIR_RAND_MIN,MOVE_DIR_RAND_MAX);

        //if randNum value is 2( right diagonal dir) or randNum value 3(left diagonal dir)
        // and monster at the end of map, retry get randNum

        if ((randNum == Left && GetGamePosX() <= 0) || (randNum == Right && GetRightSideGamePosX() >= MAP_WIDTH))
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

void FastShootEnemy::Shoot()
{
    if (m_shootCount < m_shouldShootCount)
    {
        

        if (m_ShootingFireRateTimer.IsTimeOver())
        {
            Bullet* tempBullet = BulletManager::GetInstance()->GetAvailableBullet();
            tempBullet->SetOwner(eBullet_Owner::Enemy);


            
            tempBullet->SetGamePos(GetGamePosX() + 2, m_absolutePos.y + 1);
            tempBullet->SetDir(m_eShootDir);
            tempBullet->SetSpeed(m_bulletMoveDelay);
            tempBullet->SetActive(true);

            m_shootCount++;

            m_ShootingFireRateTimer.StartOrRestart();
        }

       


    }
    else if(m_shootCount >= m_shouldShootCount)
    {
        m_shootCount = 0;
        m_eFastShootEnemey_State = eFastShootEnemy_State::Move;
    }
   
}

void FastShootEnemy::ShootDirChange()
{
}

void FastShootEnemy::PreventIncorrectDir()
{
    if (GetGamePosX() <= 0 && m_eMoveDir == eDirect::Left)
    {
        int randNum = Utils::GetInstance()->GetRandIntNum(0,1);

        if (randNum == 0)
        {
            m_eMoveDir = eDirect::Down;
            m_moveDelay = m_downMoveDelay;
        }
        else
        {
            m_eMoveDir = eDirect::Right;
            m_moveDelay = m_horizontalMoveDelay;
        }
        m_moveDirChangeTimer.StartOrRestart();
    }
    else if (GetRightSideGamePosX() >= 45 && m_eMoveDir == eDirect::Right)
    {
        int randNum = Utils::GetInstance()->GetRandIntNum(0, 1);

        if (randNum == 0)
        {
            m_eMoveDir = eDirect::Down;
            m_moveDelay = m_downMoveDelay;
        }
        else
        {
            m_eMoveDir = eDirect::Left;
            m_moveDelay = m_horizontalMoveDelay;
        }
        m_moveDirChangeTimer.StartOrRestart();
    }
}


void FastShootEnemy::ShootingCycleCheckAndSet()
{
    if (m_ShootingCycleTimer.IsFirstRun())
    {
        m_ShootingCycleTimer.StartOrRestart();
    }
    else if(m_ShootingCycleTimer.IsTimeOver())
    {
        m_eFastShootEnemey_State = eFastShootEnemy_State::Shoot;
        m_ShootingCycleTimer.StartOrRestart();
    }
}

void FastShootEnemy::SetCorrectMoveDelay()
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
