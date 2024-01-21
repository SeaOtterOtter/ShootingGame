#include <stdlib.h>
#include <typeinfo>
//

#include "Manager/EnemyManager.h"
#include "Character/Enemy/NormalEnemy.h"
#include "Character/Enemy/FastShootEnemy.h"
#include "Character/Enemy/DoubleShootEnemy.h"
#include "Character/Enemy/LaserEnemy.h"
#include "Game/Macro.h"
#include <Manager/GameManager.h>


EnemyManager* EnemyManager::m_instance;


EnemyManager* EnemyManager::GetInstance()
{
    if(m_instance == nullptr)
        m_instance = new EnemyManager();

    return m_instance;
}

void EnemyManager::ReleaseInstance()
{
    delete m_instance;
    m_instance = nullptr;


}

std::vector<Enemy*> EnemyManager::GetVecEnemy()
{
    return m_vecEnemy;
}
Enemy* EnemyManager::GetAvailableEnemy(eEnemy_Type enemy_Type)
{
    switch (enemy_Type)
    {
    case eEnemy_Type::Normal:

        //있으면 찾아서 리턴
        for (size_t i = 0; i < m_vecNormalEnemy.size(); ++i)
        {
            if (m_vecNormalEnemy[i]->IsActive() == false)
            {
                //초기화 시키기
                m_vecNormalEnemy[i]->Reset();
                return m_vecNormalEnemy[i];
            }
        }
        //없으면 새로 생성
        
        for (int i = 0; i < 30; ++i)
        {
            NormalEnemy* enemy = new NormalEnemy(1,1);
            enemy->SetActive(false);

            //마지막 반복문이면 enemy 리턴 시켜주기
            if (i == 29)
            {
                return enemy;
            }
        }


        break;

    case eEnemy_Type::FastShoot:
        //있으면 찾아서 리턴
        for (size_t i = 0; i < m_vecFastShootEnemy.size(); ++i)
        {
            if (m_vecFastShootEnemy[i]->IsActive() == false)
            {
                //초기화 시키기
                m_vecFastShootEnemy[i]->Reset();
                return m_vecFastShootEnemy[i];
            }
        }
        //없으면 새로 생성

        for (int i = 0; i < 30; ++i)
        {
            FastShootEnemy* enemy = new FastShootEnemy(1, 1);
            enemy->SetActive(false);

            //마지막 반복문이면 enemy 리턴 시켜주기
            if (i == 29)
            {
                return enemy;
            }
        }
        break;

    case eEnemy_Type::DoubleShoot:
        break;
    case eEnemy_Type::Laser:
        break;
    default:
        assert(false);
    }
}

void EnemyManager::DeleteAllEnemy()
{
	m_vecNormalEnemy.clear();
	m_vecNormalEnemy.clear();
	m_vecNormalEnemy.clear();
	m_vecNormalEnemy.clear();

	size_t size = m_vecEnemy.size();
	for (int i = 0; i < size; i++)
	{
		SAFE_DELETE(m_vecEnemy[i]);;
	}

	m_vecEnemy.clear();
	
	
	m_vecNormalEnemy.clear();
	
	
	m_vecFastShootEnemy.clear();


	m_vecDoubleShootEnemey.clear();


	m_vecLaserEnemy.clear();




}
EnemyManager::EnemyManager()
{
    m_vecEnemy.reserve(200);
    m_vecNormalEnemy.reserve(50);
    m_vecFastShootEnemy.reserve(50);
    m_vecDoubleShootEnemey.reserve(50);
    m_vecLaserEnemy.reserve(50);

   

}

EnemyManager::~EnemyManager()
{
    

}

void EnemyManager::Start()
{
    for (int i = 0; i < 10; ++i)
    {
        //error is here!
        NormalEnemy* normalEnemey = new NormalEnemy(0, 0);
        normalEnemey->SetActive(false);

        FastShootEnemy* fastShootEnemey = new FastShootEnemy(0, 0);
        fastShootEnemey->SetActive(false);
    }

	
	GameManager::GetInstance()->RegisterGameOverEvent(std::bind(&EnemyManager::DeleteAllEnemy, EnemyManager::GetInstance()));
}

void EnemyManager::Update()
{
    for(size_t i = 0 ; i <m_vecNormalEnemy.size(); ++i)
    {
        m_vecNormalEnemy[i]->Update();
    }
    for (size_t i = 0; i < m_vecFastShootEnemy.size(); ++i)
    {
        m_vecFastShootEnemy[i]->Update();
    }
    for (size_t i = 0; i < m_vecDoubleShootEnemey.size(); ++i)
    {
        m_vecDoubleShootEnemey[i]->Update();
    }
    for (size_t i = 0; i < m_vecLaserEnemy.size(); ++i)
    {
        m_vecLaserEnemy[i]->Update();
    }
}

void EnemyManager::AddEnemy(Enemy* enemy)
{
    if (typeid(*enemy).name() == typeid(NormalEnemy).name())
    {
        m_vecNormalEnemy.push_back(enemy);
    }
    else if (typeid(*enemy).name() == typeid(FastShootEnemy).name())
    {
        m_vecFastShootEnemy.push_back(enemy);
    }
    else if (typeid(*enemy).name() == typeid(DoubleShootEnemy).name())
    {
        m_vecDoubleShootEnemey.push_back(enemy);
    }
    else if (typeid(*enemy).name() == typeid(LaserEnemy).name())
    {
        m_vecLaserEnemy.push_back(enemy);
    }

    m_vecEnemy.push_back(enemy);
    
}

void EnemyManager::CreateEnemy(Enemy* enemey)
{

}

void EnemyManager::Release()
{
    for (size_t i = 0; i < m_vecEnemy.size(); ++i)
    {
        //SAFE_DELETE(m_vecEnemy[i]);
    }

    delete m_instance;
}
