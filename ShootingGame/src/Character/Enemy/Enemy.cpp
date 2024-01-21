#include <iostream>

#include "Character/Enemy/Enemy.h"
#include "Manager/GameManager.h"
#include "Manager/EffectManager.h"
#include "Object/Bullet.h"
#include "Manager/PrintManager.h"




Enemy::Enemy() :
    m_fireRate(0),
    m_currentFireRateDelayCount(0),
    m_eShootDir(eDirect::Down),
    m_eMoveDir(eDirect::Down),
    m_bActive(true),
    m_setInDownDir_distDiff(0),
    m_setInLeftOrRightDir_distDiff(0)
   
{
    //ctor
}

Enemy::~Enemy()
{
    //dtor
}

void Enemy::Shoot()
{

}

void Enemy::Die()
{
    EraseAfterImage();

    Effect* dieEffect[5];
       
    for (int i = 0; i < 5; ++i)
    {
       dieEffect[i] = EffectManager::GetInstance()->GetAvailableEffect();
       dieEffect[i]->SetDurationTime(0.2f);
       dieEffect[i]->SetEffectCycleTime(0.05f);
       dieEffect[i]->SetActive(true);
    }

    dieEffect[0]->SetPos(GetGamePosX(), GetGamePosY());
    dieEffect[1]->SetPos(GetGameMiddlePosX(), GetGamePosY());
    dieEffect[2]->SetPos(GetGameMiddlePosX(), GetGamePosY() - 1);
    dieEffect[3]->SetPos(GetGamePosX(), GetGamePosY() + 1);
    dieEffect[4]->SetPos(GetRightSideGamePosX(), GetGamePosY());

    
    SetActive(false);

	GameManager::GetInstance()->IncreaseKillCount();
    
}

void Enemy::CollideWithBullet(Bullet& bullet)
{
    m_hp--;
    if (m_hp <= 0)
    {
        Die();
      
    }
    else
    {
        Effect* tempEffect = EffectManager::GetInstance()->GetAvailableEffect();
        tempEffect->SetEffectType(eEffect_Type::Hit);
        tempEffect->SetPos(bullet.GetGamePosX(), bullet.GetGamePosY());
        tempEffect->SetActive(true);
    }
  

    
}
void Enemy::SetDirect(eDirect direct)
{
    m_eMoveDir = direct;
}
void Enemy::MoveDown()
{
    if(m_currentMoveDelayCount <= 0)
    {
         m_gamePos.y++;
         RefreshAbsolutePos();
         m_currentMoveDelayCount = m_moveDelay;
    }

    
}
void Enemy::MoveUp()
{
    if(m_currentMoveDelayCount <= 0)
    {
        m_gamePos.y--;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay;
    }
}

void Enemy::MoveLeft()
{
    if(m_currentMoveDelayCount <= 0)
    {
        m_gamePos.x--;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay;
    }
}

void Enemy::MoveRight()
{
    if(m_currentMoveDelayCount <= 0)
    {
        m_gamePos.x++;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay;
    }
}

void Enemy::MoveRightDownDiagonal()
{
    if(m_currentMoveDelayCount <= 0)
    {
        m_gamePos.x++;
        m_gamePos.y++;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay * 2;
    }

}
void Enemy::MoveLeftDownDiagonal()
{
    if(m_currentMoveDelayCount <= 0)
    {
        m_gamePos.x--;
        m_gamePos.y++;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay * 2;
    }

}

void Enemy::Move()
{
    if(m_currentMoveDelayCount > 0)
    {
        m_currentMoveDelayCount -= 1;
    }

    else
    {


        EraseAfterImage();
        MoveToCurDirect();


        //if out of range, make Active false and Erase Image
        if(GetGamePosX() < 0 || GetRightSideGamePosX() > MAP_WIDTH - MAP_OFFSET_FROM_START ||
           GetGamePosY() < 0 || GetGamePosY() > MAP_HEIGHT)
        {
            SetActive(false);
			EraseAfterImage();

        }




    }
}

void Enemy::MoveToCurDirect()
{
    switch(m_eMoveDir)
    {
    case eDirect::Up:
        MoveUp();
        break;
    case eDirect::Down:
        MoveDown();
        break;
    case eDirect::Left:
        MoveLeft();
        break;
    case eDirect::Right:
        MoveRight();
        break;
    case eDirect::Left_Down_Diagonal:
        MoveLeftDownDiagonal();
        break;
    case eDirect::Right_Down_Diagonal:
        MoveRightDownDiagonal();
        break;
    
    case eDirect::None:
        break;
	default:
		break;
    }
}

void Enemy::Update()
{

}

bool Enemy::IsActive()
{
    return m_bActive;
}

void Enemy::SetActive(bool value)
{
    m_bActive = value;

 
    
}
