#pragma once
#include "IManager.h"
#include "Utils/Timer.h"

class StageManager :
    public IManager
{
public:
    static StageManager* GetInstance();
    virtual void Start() override;

    virtual void Update() override;


	float GetStageElapsedTime();
	void StopRespawn();
	void StopStageTimer();

private:
    StageManager();
    ~StageManager();

    void SetBitFlag();
    void RespawnEnemy();

    static StageManager* m_instance;
    
    Timer m_stageTimer;
    Timer m_normalEnemyRespawnTimer;
    Timer m_fastShootEnemyRespawnTimer;
    Timer m_doubleShootEnemyRespawnTimer;
    Timer m_laserEnemyRespawnTimer;


    const int m_normalEnemy_EmergenceTime;
    const int m_fastShootEnemy_EmergenceTime;
    const int m_doubleShootEnemy_EmergenceTime;
    const int m_laserEnemy_EmergenceTime;

    const unsigned char m_normalEnemyFlag;
    const unsigned char m_fastShootEnemyFlag;
    const unsigned char m_doubleShootEnemyFlag;
    const unsigned char m_laserEnemyFlag;

    unsigned char m_respawnObjectFlags;

	bool m_bShouldRespawn;


};

