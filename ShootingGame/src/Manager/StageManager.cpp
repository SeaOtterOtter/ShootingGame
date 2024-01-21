
#include "Manager\StageManager.h"
#include "Manager/EnemyManager.h"
#include "Character/Enemy/NormalEnemy.h"
#include "Character/Enemy/DoubleShootEnemy.h"
#include "Character/Enemy/FastShootEnemy.h"
#include "Character/Enemy/LaserEnemy.h"
#include "Manager/PrintManager.h"
#include "Utils/Utils.h"
#include <Manager/GameManager.h>

StageManager* StageManager::m_instance;

StageManager* StageManager::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new StageManager();
    }
    return m_instance;
}

void StageManager::Start()
{
    m_stageTimer.SetFixedTime(5000);
    m_stageTimer.StartOrRestart();

    m_normalEnemyRespawnTimer.SetFixedTime(5);
    m_fastShootEnemyRespawnTimer.SetFixedTime(8);
    m_doubleShootEnemyRespawnTimer.SetFixedTime(10);
    m_laserEnemyRespawnTimer.SetFixedTime(10);


	GameManager::GetInstance()->RegisterGameOverEvent(std::bind(&StageManager::StopRespawn, StageManager::GetInstance()));
	GameManager::GetInstance()->RegisterGameOverEvent(std::bind(&StageManager::StopStageTimer, StageManager::GetInstance()));
}

void StageManager::Update()
{
    SetBitFlag();
    RespawnEnemy();

    //PrintManager::GetInstance()->Print(2, 8, m_stageTimer.GetElapsedTime());

}

float StageManager::GetStageElapsedTime()
{
	return m_stageTimer.GetElapsedTime();
}

void StageManager::StopRespawn()
{
	m_bShouldRespawn = false;
}

void StageManager::StopStageTimer()
{
	m_stageTimer.Stop();
}

StageManager::StageManager():
    m_normalEnemy_EmergenceTime(2),
    m_fastShootEnemy_EmergenceTime(8),
    m_doubleShootEnemy_EmergenceTime(10),
    m_laserEnemy_EmergenceTime(12),
    m_normalEnemyFlag(0x1),
    m_fastShootEnemyFlag(0x2),
    m_doubleShootEnemyFlag(0x4),
    m_laserEnemyFlag(0x8),
    m_respawnObjectFlags(0),
	m_bShouldRespawn(true)
{

}

StageManager::~StageManager()
{
}

void StageManager::SetBitFlag()
{

	float elapsedTime = m_stageTimer.GetElapsedTime();
    if (elapsedTime > m_normalEnemy_EmergenceTime)
    {
        m_respawnObjectFlags |= m_normalEnemyFlag;
    }
    if (elapsedTime > m_fastShootEnemy_EmergenceTime)
    {
        m_respawnObjectFlags |= m_fastShootEnemyFlag;
    }
    if (elapsedTime > m_doubleShootEnemy_EmergenceTime)
    {
        m_respawnObjectFlags |= m_doubleShootEnemyFlag;
    }
    if (elapsedTime > m_laserEnemy_EmergenceTime)
    {
        m_respawnObjectFlags |= m_laserEnemyFlag;
    }
}

void StageManager::RespawnEnemy()
{
	if (!m_bShouldRespawn)
	{
		return;
	}


    if (m_respawnObjectFlags & m_normalEnemyFlag)
    {
        if (m_normalEnemyRespawnTimer.IsTimeOver())
        {
            int ranNumX = Utils::GetInstance()->GetRandIntNum(0, 40);
            int ranNumY = Utils::GetInstance()->GetRandIntNum(0, 2);
            Enemy* enemy = EnemyManager::GetInstance()->GetAvailableEnemy(eEnemy_Type::Normal);
            enemy->SetGamePos(ranNumX, ranNumY);
            enemy->SetActive(true);

            m_normalEnemyRespawnTimer.StartOrRestart();
        }
    }
    if (m_respawnObjectFlags & m_fastShootEnemyFlag)
    {
        if (m_fastShootEnemyRespawnTimer.IsTimeOver())
        {
            int ranNumX = Utils::GetInstance()->GetRandIntNum(0, 40);
            int ranNumY = Utils::GetInstance()->GetRandIntNum(0, 2);
            FastShootEnemy* enemy = new FastShootEnemy(ranNumX, ranNumY);

            m_fastShootEnemyRespawnTimer.StartOrRestart();
        }
    }
    if (m_respawnObjectFlags & m_doubleShootEnemyFlag)
    {
        if (m_doubleShootEnemyRespawnTimer.IsTimeOver())
        {
            int ranNumX = Utils::GetInstance()->GetRandIntNum(0, 40);
            int ranNumY = Utils::GetInstance()->GetRandIntNum(0, 2);
            DoubleShootEnemy* enemy = new DoubleShootEnemy(ranNumX, ranNumY);

            m_doubleShootEnemyRespawnTimer.StartOrRestart();
        }
    }
    if (m_respawnObjectFlags & m_laserEnemyFlag)
    {
        if (m_laserEnemyRespawnTimer.IsTimeOver())
        {
            int ranNumX = Utils::GetInstance()->GetRandIntNum(0, 40);
            int ranNumY = Utils::GetInstance()->GetRandIntNum(0, 2);
            LaserEnemy* enemy = new LaserEnemy(ranNumX, ranNumY);

            m_laserEnemyRespawnTimer.StartOrRestart();
        }
    }
}
