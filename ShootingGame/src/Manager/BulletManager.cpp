
#include <stdlib.h>
#include <iostream>
#include "Manager/BulletManager.h"
#include "Manager/ObjManager.h"
#include "Manager/GameManager.h"

#include "Game/Macro.h"


BulletManager* BulletManager::m_instance;

BulletManager::BulletManager():
    m_possesionBulletCount(0),
    m_vecBulletIdxPos(0),
    m_canUseBulletCount(0)
{
//    Bullet* bullet = new Bullet();
//    bullet->SetPos(10,10);
//    bullet->SetDir(eDirect::D_DOWN);
//    bullet->SetSpeed(3);
//    m_vecBullet.push_back(bullet);

    m_vecBullet.reserve(200);




    //ctor
}

BulletManager::~BulletManager()
{
    
}

BulletManager* BulletManager::GetInstance()
{
    if(m_instance == NULL)
        m_instance = new BulletManager();

    return m_instance;
}


void BulletManager::Start()
{
    //Initalize
    for(int i = 0 ; i<3; ++i)
    {
        Bullet* temp = new Bullet();
        temp->SetDir(eDirect::Up);
        temp->SetSpeed(3);

        CreateBullet(temp);
    }

}

void BulletManager::Update()
{
    

}
void BulletManager::CreateBullet(Bullet* bullet)
{
    m_vecBullet.push_back(bullet);
    m_possesionBulletCount++;
    m_canUseBulletCount++;

    ObjManager::GetInstance()->AddObj(bullet);

}

void BulletManager::Release()
{
    delete m_instance;
}



//object pooling
Bullet* BulletManager::GetAvailableBullet()
{
    //searching can use bullet

    int initialIdx = m_vecBulletIdxPos;
    int i;

    //search Idx ~ m_possesionBullet
    for(i = m_vecBulletIdxPos; i <m_possesionBulletCount; ++i)
    {
        m_vecBulletIdxPos++;
        if(m_vecBullet[i]->IsCanUse())
        {
            m_canUseBulletCount--;
            return m_vecBullet[i];
        }
    }
    m_vecBulletIdxPos = 0;
    //search 0 ~ Idx
    for(i = 0; i < initialIdx; ++i)
    {
        m_vecBulletIdxPos++;
        if(m_vecBullet[i]->IsCanUse())
        {
            m_canUseBulletCount--;
            return m_vecBullet[i];
        }
    }



    //if not have a bullet, add more
    for(int i = 0 ; i < 100; ++i)
    {
        Bullet* temp = new Bullet();
        //temp->SetDir(eDirect::D_UP);
        //temp->SetSpeed(3);

        CreateBullet(temp);
    }

    return GetAvailableBullet();





}

void BulletManager::IncreaseCanUseBulletCount()
{
    m_canUseBulletCount++;
}
