#pragma once
#include <string>

#include "Game/Game.h"
#include "Game/Flag.h"

class Obj
{
    public:
        Obj();
        virtual ~Obj();

    protected:
        int m_moveDealyCount;
        int m_currentMoveDelayCount;
        Position m_absolutePos;
        Position m_gamePos;
        wchar_t* m_character;
        int m_sizeX;
        eDirect m_eDir;
        bool m_bActive;
        std::string m_tag;
        std::string m_name;

    private:

    public:
        int GetSpeed() const;
        int GetGamePosX() const;
        int GetGamePosY() const;
        Position GetGamePos() const;
        int GetAbsolutePosX() const;
        int GetAbsolutePosY() const;
        Position GetAbsolutePos() const;
        int GetSizeX() const;
        int GetRightSideGamePosX() const;
        std::string GetTag() const;
        int GetCurrentMoveDelayCount() const;
    public:
        bool IsActive() const;
        wchar_t* GetCharacter() const;

    public:
        void SetSpeed(int speed);
        void SetGamePosX(int x);
        void SetGamePosY(int y);
        void SetGamePos(int x, int y);
        void SetTag(std::string tag);
        void SetActive(bool value);
    public:
        void MoveUp();
        void MoveDown();
        void MoveRight();
        void MoveLeft();
        void MoveLeftDownDiagonal();
        void MoveRightDownDiagonal();
        void MoveLeftUpDiagonal();
        void MoveRightUpDiagonal();
        void DeleteAfterImage();
        void MoveToCurDirect();
    public:
        virtual void Update();
        virtual void Render();
    protected:
        void RenewalAbsolutePos();
        //virtual void DecreaseDelay();
};

