
#include <iostream>

#include "Character/Enemy/NormalEnemy.h"
#include "Manager/GameManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/PrintManager.h"
#include "Character/Player/Player.h"
#include "Utils/Utils.h"
#include "Object/Bullet.h"
#include "Manager/BulletManager.h"


#define MOVE_DIR_RAND_MIN 0
#define MOVE_DIR_RAND_MAX 3

NormalEnemy::NormalEnemy(int x, int y)
{
    
    SetGamePos(x, y);

    m_hp = 3;    
    m_maxHp = 3;

    m_character =L"[||]";
    m_sizeX = 4;
    m_moveDelay = 20;
    m_fireRate = 130;
    m_setInDownDir_distDiff = 3;
    m_setInLeftOrRightDir_distDiff = 2;
    m_eMoveDir = eDirect::Down;

    
    
    
    
   
    

    m_moveDirChangeTimer.SetFixedTime(2.0f);
    m_shootDirChangeTimer.SetFixedTime(2.5f);

    EnemyManager::GetInstance()->AddEnemy(this);

}

NormalEnemy::~NormalEnemy()
{

}

void NormalEnemy::ShootDirChange()
{
    int playerMiddlePosX = GameManager::GetInstance()->GetPlayer()->GetGameMiddlePosX();
    int playerPosY = GameManager::GetInstance()->GetPlayer()->GetGamePosY();


    int enemyMiddlePosX = m_absolutePos.x + m_sizeX / 2;

    //default setting to Down;
    m_eShootDir = eDirect::Down;

    //When the player is further to the right
    if(playerPosY >= m_absolutePos.y - m_setInLeftOrRightDir_distDiff &&
       playerPosY <= m_absolutePos.y + m_setInLeftOrRightDir_distDiff )
    {
        if(enemyMiddlePosX <= playerMiddlePosX)
        {
//            GameManager::GetInstance()->gotoxy(1,6);
//            std::cout << "right";
            m_eShootDir = eDirect::Right;
        }
        else
        {
//            GameManager::GetInstance()->gotoxy(1,6);
//            std::cout << "left";
            m_eShootDir = eDirect::Left;
        }
    }
    else if(playerMiddlePosX > enemyMiddlePosX - m_setInDownDir_distDiff &&
       playerMiddlePosX < enemyMiddlePosX + m_setInDownDir_distDiff )
    {
//        GameManager::GetInstance()->gotoxy(1,6);
//            std::cout << "down";
        m_eShootDir = eDirect::Down;
    }
    else
    {
       if(playerMiddlePosX > enemyMiddlePosX)
       {
//           GameManager::GetInstance()->gotoxy(1,6);
//            std::cout << "right_down_diagonal";
           m_eShootDir = eDirect::Right_Down_Diagonal;
       }
       else if(playerMiddlePosX < enemyMiddlePosX)
       {
//           GameManager::GetInstance()->gotoxy(1,6);
//            std::cout << "left_down_diagonal";
           m_eShootDir = eDirect::Left_Down_Diagonal;
       }

    }

}
void NormalEnemy::ShootDirChangeCycleCheckAndSet()
{
    if (m_shootDirChangeTimer.IsFirstRun())
    {
        m_shootDirChangeTimer.StartOrRestart();
    }
    else if (m_shootDirChangeTimer.IsTimeOver())
    {
        ShootDirChange();
        m_shootDirChangeTimer.StartOrRestart();
    }

   
}
void NormalEnemy::Shoot()
{
   if(m_currentFireRateDelayCount <= 0)
    {
        m_currentFireRateDelayCount = m_fireRate;

        Bullet* tempBullet = BulletManager::GetInstance()->GetAvailableBullet();
        tempBullet->SetOwner(eBullet_Owner::Enemy);
        GameManager::GetInstance()->gotoxy(2,7);

        tempBullet->SetGamePos(GetGamePosX() + 1, m_absolutePos.y + 1 );
        tempBullet->SetDir(m_eShootDir);
        tempBullet->SetSpeed(4);
        tempBullet->SetActive(true);


    }
    else
    {
        m_currentFireRateDelayCount--;
    }


}

void NormalEnemy::MoveDirChange()
{
    //randomly

    //minus 4 = because NormalEnemy do not use Horizontal Move and Up Move (3)
    int randNum = 0;
    while(true)
    {
        //avoid wrong dir(out of range) setting
        randNum = Utils::GetInstance()->GetRandIntNum(MOVE_DIR_RAND_MIN, MOVE_DIR_RAND_MAX);

        //if randNum value is 2( right diagonal dir) or randNum value 3(left diagonal dir)
        // and monster at the end of map, retry get randNum

        if((randNum == Left_down_diagonal && GetGamePosX() <= 0) || 
            (randNum == Right_down_diagonal && GetRightSideGamePosX() >= MAP_WIDTH))
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
        case MovableDir::None:
            m_eMoveDir = eDirect::None;
            break;
        case MovableDir::Down:
            m_eMoveDir = eDirect::Down;
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
void NormalEnemy::MoveDirChangeCycleCheckAndSet()
{
    //If it is run for the first time, Wait until m_firstDirChangeTimer is TimeOvered
    if(m_firstDirChangeTimer.IsFirstRun())
    {
         float randNumf = Utils::GetInstance()->GetRandFloatNum(0.3f , 1.0f);

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

void NormalEnemy::PreventIncorrectDir()
{
   


    if(GetGamePosX() <= 0 && m_eMoveDir == eDirect::Left_Down_Diagonal)
    {
        while(m_eMoveDir == eDirect::Left_Down_Diagonal)
        {
            MoveDirChange();
        }

        m_moveDirChangeTimer.StartOrRestart();
    }
    else if(GetRightSideGamePosX() >= MAP_WIDTH && m_eMoveDir == eDirect::Right_Down_Diagonal)
    {
        while(m_eMoveDir == eDirect::Right_Down_Diagonal)
        {
            MoveDirChange();
        }

        m_moveDirChangeTimer.StartOrRestart();
    }
}

void NormalEnemy::Render()
{
    PrintManager::GetInstance()->Print(m_absolutePos.x, m_absolutePos.y, GetCharacter());
   
}

void NormalEnemy::Reset()
{
    m_hp = m_maxHp;
}



void NormalEnemy::Update()
{

    if(IsActive())
    {

        //shoot
        //처음 생성 됐을 때 랜덤타임으로 방향 설정하는거 만들기

        //set the move Dir every 3.5 second
        MoveDirChangeCycleCheckAndSet();
        //set the shoot Dir every 2.5 second
        ShootDirChangeCycleCheckAndSet();
        //prevent monster from out the map by setting the correct Dir
        PreventIncorrectDir();


        
        Move();
        Shoot();

        if(IsActive())
        {
            //if Enemy is out of range, Move() is has already set Active to false
            Render();
           
        }




    }

}
