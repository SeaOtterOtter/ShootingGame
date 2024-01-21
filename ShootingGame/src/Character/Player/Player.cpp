#include <iostream>


#include "Character/Player/Player.h"
#include "Object/Bullet.h"
#include "Manager/BulletManager.h"
#include "Manager/ObjManager.h"
#include "Manager/GameManager.h"
#include "Manager/EffectManager.h"
#include "Manager/PrintManager.h"
#include "Effect/Effect.h"
#include "Object/Laser.h"
#include "Utils/Timer.h"
#include <Manager/InputManager.h>




Player::Player() :
    m_laserHitDelay(1.0f)
{
    m_character = L"<-^->";
    m_sizeX = 5;
    m_vecShootPos.push_back(1);
    m_vecShootPos.push_back(3);
    m_fireRate = 8;
    m_moveDelay = 3;
    m_currentFireRateDelayCount = 0;
    m_hp = 5;
    m_bulletMoveDelay = 1;
    m_laserHitDelayTimer.SetFixedTime(m_laserHitDelay);
    //ctor

	//InputManager::GetInstance()->RegisterKeyEvent(VK_LEFT, std::bind(&Player::MoveLeft , this));
	//InputManager::GetInstance()->RegisterKeyEvent(VK_RIGHT, std::bind(&Player::MoveRight , this));
	//InputManager::GetInstance()->RegisterKeyEvent(VK_DOWN, std::bind(&Player::MoveDown , this));
	//InputManager::GetInstance()->RegisterKeyEvent(VK_UP, std::bind(&Player::MoveUp , this));



	//InputManager::GetInstance()->RegisterKeyEvent(VK_LEFT, std::bind(&Player::KeyDownCheck, this , std::placeholders::_1));
	//InputManager::GetInstance()->RegisterKeyEvent(VK_RIGHT, std::bind(&Player::KeyDownCheck, this, std::placeholders::_1));
	//InputManager::GetInstance()->RegisterKeyEvent(VK_DOWN, std::bind(&Player::KeyDownCheck, this, std::placeholders::_1));
	//InputManager::GetInstance()->RegisterKeyEvent(VK_UP, std::bind(&Player::KeyDownCheck, this, std::placeholders::_1));




	InputManager::GetInstance()->RegisterKeyEvent(0x58, std::bind(&Player::Shoot, this));
}

Player::~Player()
{
    //dtor
}

void Player::MoveDown() 
{
	
	m_gamePos.y++;
	RefreshAbsolutePos();

	m_currentMoveDelayCount = m_moveDelay;
	
}
void Player::MoveUp()
{
	//if (m_currentMoveDelayCount <= 0)
	//{
		m_gamePos.y--;
		RefreshAbsolutePos();
		m_currentMoveDelayCount = m_moveDelay;
	//}
}

void Player::MoveLeft()
{
	
		m_gamePos.x--;
		RefreshAbsolutePos();
		m_currentMoveDelayCount = m_moveDelay;
	
}

void Player::MoveRight()
{
	
		m_gamePos.x++;
		RefreshAbsolutePos();
		m_currentMoveDelayCount = m_moveDelay;
	
}
void Player::CollideWithBullet(Bullet& bullet)
{
    Effect* tempEffect = EffectManager::GetInstance()->GetAvailableEffect();
    tempEffect->SetPos(bullet.GetGamePosX(), bullet.GetGamePosY());
    tempEffect->SetActive(true);
    m_hp--;

	if (m_hp <= 0)
	{
		Die();
	}
}

//수정 필요
void Player::CollideWithLaser(Laser& laser)
{
    
    //딜레이 때만 체력깎기
    if (m_laserHitDelayTimer.IsTimeOver() || m_laserHitDelayTimer.IsFirstRun())
    {
        m_laserHitDelayTimer.StartOrRestart();
        Effect* tempEffect = EffectManager::GetInstance()->GetAvailableEffect();
        tempEffect->SetPos(laser.GetGamePosX(), laser.GetGamePosY());
        tempEffect->SetActive(true);
        m_hp--;
    }
   
}
void Player::Update()
{
	if (m_hp <= 0)
	{
		return;
	}

    if(m_currentFireRateDelayCount > 0)
    {
        m_currentFireRateDelayCount--;
    }
    if(m_currentMoveDelayCount > 0)
    {
        m_currentMoveDelayCount--;
    }

    Render();


    //laserTimer

    

}
void Player::Render()
{
   PrintManager::GetInstance()->Print(GetAbsolutePosX(), GetAbsolutePosY(), GetCharacter(), 
       ePrint_Color::Dark_SkyBlue);
	//
	//PrintManager::GetInstance()->Print(0,0, m_currentMoveDelayCount,
   //    ePrint_Color::Dark_SkyBlue);
	//
	//PrintManager::GetInstance()->Print(5,0, m_gamePos.x,
   //    ePrint_Color::Dark_SkyBlue);

    //PrintManager::GetInstance()->gotoxy(2, 3);
    //std::cout << "HP: " << m_hp;

    
    /*PrintManager::GetInstance()->gotoxy(2, 4);
    std::cout << "LaserTimer : " << m_laserHitDelayTimer.GetElapsedTime();*/
    
}

//0x58 == x키

void Player::KeyDownCheck(int key)
{

	

    if(key == VK_LEFT && GetGamePosX() > 0)
    {
        //잔상 지우기 용
        PrintManager::GetInstance()->PrintSpace(GetAbsolutePosX() + GetSizeX() - 1, GetAbsolutePosY());
        MoveLeft();
        
    }

    if(key == VK_RIGHT && GetRightSideGamePosX() < MAP_WIDTH - MAP_OFFSET_FROM_START)
    {
       
        
        PrintManager::GetInstance()->PrintSpace(GetAbsolutePosX(), GetAbsolutePosY());
        MoveRight();
       
    }
    if(key == VK_UP && GetGamePosY() > 0)
    {
        

        for(int i = 0; i < GetSizeX(); ++i)
        {
            PrintManager::GetInstance()->PrintSpace(GetAbsolutePosX() + i, GetAbsolutePosY());
        }


        MoveUp();
      
    }

    if(key == VK_DOWN && GetGamePosY() < MAP_HEIGHT)
    {
        for(int i = 0; i < GetSizeX(); ++i)
        {
            PrintManager::GetInstance()->PrintSpace(GetAbsolutePosX() + i, GetAbsolutePosY());
        }


        MoveDown();
       
    }
}

void Player::Die()
{
	GameManager::GetInstance()->GameOver();
}

void Player::Shoot()
{


    if(m_currentFireRateDelayCount <= 0)
    {
        m_currentFireRateDelayCount = m_fireRate;

        Bullet* tempBullet = BulletManager::GetInstance()->GetAvailableBullet();
        tempBullet->SetOwner(eBullet_Owner::Player);
        tempBullet->SetGamePos(GetGamePosX() + 2, GetGamePosY() -1 );
        tempBullet->SetDir(eDirect::Up);
        tempBullet->SetSpeed(m_bulletMoveDelay);
        tempBullet->SetActive(true);
    }

}
