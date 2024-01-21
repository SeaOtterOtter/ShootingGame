#pragma once

#include "Object/Obj.h"
#include "Game/Flag.h"



class Bullet : public Obj
{
    public:
        Bullet();
        virtual ~Bullet();

    protected:
        int m_damage;
        bool m_bUsing;


    private:
        eBullet_Owner m_eBulletOwner;
        ePrint_Color m_eColor;
    private:
        void SetBulletActiveFalse();
        void CheckCollisionWithPlayer();
        void CheckCollisionWithEnemy();

    public:
        int GetDamage() const;
        eDirect GetDir() const;
        bool IsCanUse() const;

    public:
        void SetDamage(int damage);
        void SetDir(eDirect direct);
        void SetOwner(eBullet_Owner owner);



        virtual void Update() override;
        virtual void Render() override;

};
