#pragma once
#include<vector>

#include "Object/Bullet.h"
#include "IManager.h"

class BulletManager : public IManager
{
    private:
        BulletManager();
        virtual ~BulletManager();
        static BulletManager* m_instance;
        
        int m_possesionBulletCount;
        int m_vecBulletIdxPos;
        int m_canUseBulletCount;
    private:
        std::vector<Bullet*> m_vecBullet;
    public:
        static BulletManager* GetInstance();
        virtual void Start() override;
        virtual void Update() override;
        Bullet* GetAvailableBullet();
        void CreateBullet(Bullet* bullet);
        void Release();

        void IncreaseCanUseBulletCount();

};

