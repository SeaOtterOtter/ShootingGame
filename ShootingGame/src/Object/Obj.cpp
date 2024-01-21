#include <iostream>


#include "Object/Obj.h"
#include "Manager/GameManager.h"
#include "Game/Game.h"





Obj::Obj():
    m_moveDealyCount(0),
    m_currentMoveDelayCount(0),
    m_character(L"OBJ"),
    m_sizeX(0),
    m_eDir(eDirect::None),
    m_bActive(true),
    m_tag("None"),
    m_name("None")

{

    //ctor
}

Obj::~Obj()
{
    //dtor
}


int Obj::GetSpeed() const
{

    return m_moveDealyCount;
}
void Obj::SetSpeed(int speed)
{

    m_moveDealyCount = speed;
}

int Obj::GetGamePosX() const
{

    return m_gamePos.x;
}
int Obj::GetGamePosY() const
{

    return m_gamePos.y;
}

Position Obj::GetGamePos() const
{
    return m_gamePos;
}

int Obj::GetAbsolutePosX() const
{
    return m_absolutePos.x;
}

int Obj::GetAbsolutePosY() const
{
    return m_absolutePos.y;
}

Position Obj::GetAbsolutePos() const
{
    return m_absolutePos;
}

int Obj::GetRightSideGamePosX() const
{
    return m_gamePos.x + m_sizeX - 1;
}

std::string Obj::GetTag() const
{
    return m_tag;
}
bool Obj::IsActive() const
{

    return m_bActive;
}
void Obj::SetGamePosX(int x)
{

    m_gamePos.x = x;
    RenewalAbsolutePos();
}
void Obj::SetGamePosY(int y)
{

    m_gamePos.y = y;
    RenewalAbsolutePos();
}
void Obj::SetGamePos(int x, int y)
{

    m_gamePos.x = x;
    m_gamePos.y = y;
    RenewalAbsolutePos();
}

void Obj::SetTag(std::string tag)
{
    m_tag = tag;
}
void Obj::SetActive(bool value)
{
    m_bActive = value;
}

void Obj::MoveDown()
{
    m_gamePos.y++;
    RenewalAbsolutePos();
}
void Obj::MoveUp()
{
   
    m_gamePos.y--;
    RenewalAbsolutePos();
}

void Obj::MoveLeft()
{
    
    m_gamePos.x--;
    RenewalAbsolutePos();
}

void Obj::MoveRight()
{
   
    m_gamePos.x++;
    RenewalAbsolutePos();
}

void Obj::MoveRightDownDiagonal()
{
    m_gamePos.x++;
    m_gamePos.y++;
    RenewalAbsolutePos();
}

void Obj::MoveLeftUpDiagonal()
{
    m_gamePos.x--;
    m_gamePos.y--;
    RenewalAbsolutePos();
}

void Obj::MoveRightUpDiagonal()
{
    m_gamePos.x++;
    m_gamePos.y--;
    RenewalAbsolutePos();
}

void Obj::MoveLeftDownDiagonal()
{
    m_gamePos.x--;
    m_gamePos.y++;
    RenewalAbsolutePos();
}
wchar_t* Obj::GetCharacter() const
{
    return m_character;
}


int Obj::GetSizeX() const
{
    return m_sizeX;
}

int Obj::GetCurrentMoveDelayCount() const
{
    return m_currentMoveDelayCount;
}
void Obj::DeleteAfterImage()
{
    GameManager::GetInstance()->gotoxy(m_absolutePos.x , m_absolutePos.y);
    std::cout << " ";
}
void Obj::MoveToCurDirect()
{

    switch(m_eDir)
    {
    case eDirect::Up:
        MoveUp();
        break;
    case eDirect::Down:
        MoveDown();
        break;
    case eDirect::Left:
        MoveLeft();
        break;
    case eDirect::Right:
        MoveRight();
        break;
    case eDirect::Left_Down_Diagonal:
        MoveLeftDownDiagonal();
        break;
    case eDirect::Right_Down_Diagonal:
        MoveRightDownDiagonal();
        break;
    case eDirect::Left_Up_Diagonal:
        MoveLeftUpDiagonal();
        break;
    case eDirect::Right_Up_Diagonal:
        MoveRightUpDiagonal();
        break;
    default:
        break;
    case eDirect::None:
        break;
    }
}

void Obj::Update()
{

}
void Obj::Render()
{

}
void Obj::RenewalAbsolutePos()
{
    m_absolutePos.x = m_gamePos.x + 2;
    m_absolutePos.y = m_gamePos.y;
}
//void Obj::DecreaseDelay()
//{
//
//}
