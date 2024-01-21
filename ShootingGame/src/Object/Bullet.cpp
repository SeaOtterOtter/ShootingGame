
#include <iostream>

#include "Object/Bullet.h"

#include "Manager/GameManager.h"

#include "Manager/BulletManager.h"

#include "Manager/EnemyManager.h"

#include "Character/Character.h"

#include "Character/Player/Player.h"
#include <Manager/PrintManager.h>




Bullet::Bullet()
:m_damage(0) ,
 m_bUsing(false)
{
    wchar_t* a = L".";
    m_character = a;
    SetActive(false);
    m_eBulletOwner = eBullet_Owner::None;



    //ctor
}

Bullet::~Bullet()
{
    //dtor
}

void Bullet::CheckCollisionWithPlayer()
{
    Player* tempPlayer = GameManager::GetInstance()->GetPlayer();
    if(tempPlayer->GetGamePosX() <= GetGamePosX() && tempPlayer->GetGamePosX() + tempPlayer->GetSizeX() -1 >= GetGamePosX() &&
        tempPlayer->GetGamePosY() == GetGamePosY())
       {
            //플레이어 정상적인 상태일 때 충돌
            tempPlayer->CollideWithBullet(*this);
            SetBulletActiveFalse();
       }

}
void Bullet::CheckCollisionWithEnemy()
{
    std::vector<Enemy*> tempVecEnemy = EnemyManager::GetInstance()->GetVecEnemy();

    for(size_t i = 0 ; i < tempVecEnemy.size(); ++i)
    {
        if(tempVecEnemy[i]->GetGamePosX()<= GetGamePosX() && tempVecEnemy[i]->GetGamePosX() + tempVecEnemy[i]->GetSizeX() -1 >= GetGamePosX() &&
           tempVecEnemy[i]->GetGamePosY() == GetGamePosY() )
        {
            if (tempVecEnemy[i]->IsActive())
            {
                tempVecEnemy[i]->CollideWithBullet(*this);
                SetBulletActiveFalse();
            }
            
            break;
        }
    }
}
int Bullet::GetDamage() const
{
    return m_damage;
}

eDirect Bullet::GetDir() const
{

    return m_eDir;
}

bool Bullet::IsCanUse() const
{

    return !m_bActive;
}
void Bullet::SetBulletActiveFalse()
{
    SetActive(false);
    BulletManager::GetInstance()->IncreaseCanUseBulletCount();

}
void Bullet::SetOwner(eBullet_Owner owner)
{
    m_eBulletOwner = owner;

    if (m_eBulletOwner == eBullet_Owner::Enemy)
    {
        m_eColor = ePrint_Color::Dark_Yellow;
    }
    else
    {
        m_eColor = ePrint_Color::Red;
    }
}
void Bullet::SetDamage(int damage)
{
    m_damage = damage;
}

void Bullet::SetDir(eDirect direct)
{
    m_eDir = direct;
}

void Bullet::Update()
{


    if(m_currentMoveDelayCount > 0)
    {
        m_currentMoveDelayCount -= 1;
    }
    //if not have a MoveDelayCount, move
    else
    {
        m_currentMoveDelayCount = m_moveDealyCount;
        //first, erase own Image
        DeleteAfterImage();
        //and Move to direct
        MoveToCurDirect();

        //if out of the range, change active to false
        if(GetGamePosX() < 0 || GetGamePosX() > MAP_WIDTH || GetGamePosY() < 0 || GetGamePosY() >MAP_HEIGHT)
        {
           SetBulletActiveFalse();
        }

        if(m_bActive)
        {
            Render();
            //check
            if(m_eBulletOwner == eBullet_Owner::Enemy)
            {
                CheckCollisionWithPlayer();

            }
            else if(m_eBulletOwner == eBullet_Owner::Player)
            {
                CheckCollisionWithEnemy();
            }
        }
    }


}

void Bullet::Render()
{
    
    
    PrintManager::GetInstance()->Print(m_absolutePos.x , m_absolutePos.y , m_character, ePrint_Color::Yellow);

}




