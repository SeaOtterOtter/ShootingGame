#pragma once
#include "Game/Game.h"
#include <vector>

class Bullet;

class Character
{
    public:
        Character();
        virtual ~Character();

    protected:
        int m_hp;
        Position m_absolutePos;
        Position m_gamePos;

        wchar_t* m_character;
        int m_sizeX;
        int m_currentMoveDelayCount;
        int m_moveDelay;
        int m_bulletMoveDelay;




    private:

    public:
        int GetHp() const;        
        int GetGamePosX() const;
        int GetGamePosY() const;
        Position GetGamePos() const;
        int GetAbsolutePosX() const;
        int GetAbsolutePosY() const;
        int GetRightSideGamePosX() const;
        Position GetAbsolutePos() const;
        int GetSizeX() const;
        int GetGameMiddlePosX() const;
        int GetCurrentMoveDelayCount() const;
        wchar_t* GetCharacter() const;

    public:
        void SetHp(int hp);      
        void SetGamePosX(int x);
        void SetGamePosY(int y);
        void SetGamePos(int x, int y);

        virtual void CollideWithBullet(class Bullet& bullet) = 0;
        virtual void MoveUp();
        virtual void MoveDown();
        virtual void MoveRight();
        virtual void MoveLeft();
        virtual void MoveRightDownDiagonal();
        virtual void MoveLeftDownDiagonal();


    public:
        virtual void Update() = 0;
        virtual void Render() = 0;

    protected:
        void EraseAfterImage();
        void RefreshAbsolutePos();
    private:
        



};

