
#include <iostream>


#include "Character/Character.h"
#include "Manager/GameManager.h"

Character::Character():
    m_hp(0),
    m_character(L"NoneCharacter"),
    m_sizeX(0),
    m_currentMoveDelayCount(0),
    m_moveDelay(0),
    m_bulletMoveDelay(0)

{
    //ctor
}

Character::~Character()
{
    //dtor
}

int Character::GetHp() const
{

    return m_hp;
}



int Character::GetCurrentMoveDelayCount() const
{
    return m_currentMoveDelayCount;
}

Position Character::GetAbsolutePos() const
{

    return m_absolutePos;
}
int Character::GetAbsolutePosX() const
{
    return m_absolutePos.x;
}

int Character::GetAbsolutePosY() const
{
    return m_absolutePos.y;
}

int Character::GetGameMiddlePosX() const
{
    return m_gamePos.x + m_sizeX / 2;
}
int Character::GetGamePosX() const
{
    //Since it is different from absolute coordinates, add 2 to it.
    return m_gamePos.x;
}
int Character::GetRightSideGamePosX() const
{
    return m_gamePos.x + m_sizeX - 1;
}
int Character::GetGamePosY() const
{

    return m_gamePos.y;
}

Position Character::GetGamePos() const
{
    return m_gamePos;
}


void Character::SetHp(int hp)
{

    m_hp = hp;
}



void Character::SetGamePosX(int x)
{
    m_gamePos.x = x;
    RefreshAbsolutePos();
}
void Character::SetGamePosY(int y)
{

    m_gamePos.y = y;
    RefreshAbsolutePos();
}
void Character::SetGamePos(int x, int y)
{

    m_gamePos.x = x;
    m_gamePos.y = y;
    RefreshAbsolutePos();
}


void Character::MoveDown()
{
    if(m_currentMoveDelayCount <= 0)
    {
         m_gamePos.y++;
         RefreshAbsolutePos();
         m_currentMoveDelayCount = m_moveDelay;
    }


}
void Character::MoveUp()
{
    if(m_currentMoveDelayCount <= 0)
    {
        m_gamePos.y--;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay;
    }
}

void Character::MoveLeft()
{
    if(m_currentMoveDelayCount <= 0)
    {
       
        m_gamePos.x--;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay;
    }
}

void Character::MoveRight()
{
    if(m_currentMoveDelayCount <= 0)
    {
        
        m_gamePos.x++;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay;
    }
}

void Character::MoveRightDownDiagonal()
{
    if(m_currentMoveDelayCount <= 0)
    {
       

        m_gamePos.x++;
        m_gamePos.y++;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay * 2;
    }

}
void Character::MoveLeftDownDiagonal()
{
    if(m_currentMoveDelayCount <= 0)
    {
     

        m_gamePos.x--;
        m_gamePos.y++;
        RefreshAbsolutePos();
        m_currentMoveDelayCount = m_moveDelay * 2;
    }

}


wchar_t* Character::GetCharacter() const
{
    return m_character;
}


int Character::GetSizeX() const
{
    return m_sizeX;
}

void Character::Update()
{

}

void Character::EraseAfterImage()
{
    for (int i = 0; i < m_sizeX; ++i)
    {
        GameManager::GetInstance()->gotoxy(GetAbsolutePosX() + i, GetAbsolutePosY());
        std::cout << " ";
    }
}

void Character::RefreshAbsolutePos()
{
    m_absolutePos.x = m_gamePos.x + 2;
    m_absolutePos.y = m_gamePos.y;
}

