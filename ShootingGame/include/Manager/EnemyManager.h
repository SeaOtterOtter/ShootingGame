#pragma once
#include <vector>

#include "Character/Enemy/Enemy.h"
#include "IManager.h"

class EnemyManager : public IManager
{
    private:
        EnemyManager();
        virtual ~EnemyManager();
        static EnemyManager* m_instance;

    public:
        static EnemyManager* GetInstance();
        static void ReleaseInstance();
        virtual void Start() override;
        virtual void Update() override;
        void AddEnemy(Enemy* enemy);
        void CreateEnemy(Enemy* enemey);
        void Release();
        std::vector<Enemy*> GetVecEnemy();
        Enemy* GetAvailableEnemy(eEnemy_Type enemy_Type);
		void DeleteAllEnemy();
    protected:

    private:
        std::vector<Enemy*> m_vecEnemy;

        std::vector<Enemy*> m_vecNormalEnemy;
        std::vector<Enemy*> m_vecFastShootEnemy;
        std::vector<Enemy*> m_vecDoubleShootEnemey;
        std::vector<Enemy*> m_vecLaserEnemy;
};


