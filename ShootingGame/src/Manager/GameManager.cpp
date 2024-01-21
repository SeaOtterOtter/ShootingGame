#include <iostream>

#include <stdlib.h>
#include <locale>
#include <conio.h>

#include "Manager/GameManager.h"
#include "Manager/BulletManager.h"
#include "Manager/ObjManager.h"
#include "Manager/PrintManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/EffectManager.h"
#include "Manager/StageManager.h"
#include "Manager/InputManager.h"

#include "Character/Player/Player.h"

#include "Game/Game.h"

#include "Utils/Utils.h"
#include "Utils/Delegate.h"

#include "Character/Enemy/NormalEnemy.h"
#include "Character/Enemy/FastShootEnemy.h"
#include "Character/Enemy/DoubleShootEnemy.h"
#include "Character/Enemy/LaserEnemy.h"








GameManager* GameManager::m_instance;


GameManager::GameManager()
	: m_killCount(0)
	, m_bGameOver(false)
{
    //ctor
}

GameManager::~GameManager()
{
   
}

GameManager* GameManager::GetInstance()
{
    if(m_instance == NULL)
        m_instance = new GameManager();

    return m_instance;

}

void GameManager::Release()
{
    delete m_player;
    delete m_instance;
    
}

void GameManager::gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);

}

bool GameManager::IsKeyDown(int key)
{
	
    return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

//void GameManager::Print_all()
//{
//
//
//    Print_player();
//}


//void GameManager::Print_player()
//{
//    gotoxy(m_player->GetAbsolutePosX(), m_player->GetAbsolutePosY());
//    wprintf_s(L"%s" ,m_player->GetCharacter());
//
//}

void GameManager::ExitProgram()
{
    GameManager::GetInstance()->Release();
    //Bullet은 ObjManager에서 다 지우기 때문에 자기 인스턴스만 지움
    BulletManager::GetInstance()->Release();
    EffectManager::GetInstance()->Release();
    EnemyManager::GetInstance()->Release();
    ObjManager::GetInstance()->Release();

    Utils::GetInstance()->Release();
}

void GameManager::Init_Player()
{
    m_player = new Player();
    m_player->SetGamePos(6,6);

}
Player* GameManager::GetPlayer()
{

    return m_player;
}

void GameManager::IncreaseKillCount()
{
	m_killCount++;
}

int GameManager::GetKillCount()
{
	return m_killCount;
}

void GameManager::GameOver()
{
	//call
	m_gameOverDelegate();

	//
	m_bGameOver = true;

}

void GameManager::RegisterGameOverEvent(std::function<void(void)> listener)
{
	m_gameOverDelegate += listener;
}

void GameManager::UnRegisterGameOverEvent(std::function<void(void)> listener)
{
	m_gameOverDelegate -= listener;

}

//void GameManager::BindKeyEvent(const int key, const std::function<void(int)>& listener)
//{
//	if (m_keyEventHandlersMap.find(key) != m_keyEventHandlersMap.end())
//	{
//		delegate 
//		m_keyEventHandlersMap[key] += ;
//	}
//}

void GameManager::DrawUI()
{
    
}

void GameManager::InvokeAllManagerStart()
{
    ObjManager::GetInstance()->Start();
    BulletManager::GetInstance()->Start();
    EnemyManager::GetInstance()->Start();
    EffectManager::GetInstance()->Start();
    StageManager::GetInstance()->Start();
	PrintManager::GetInstance()->Start();
	InputManager::GetInstance()->Start();
}


void GameManager::Start()
{
	
	//default settings
    setlocale(LC_ALL, "");
    //HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_CURSOR_INFO consoleCursur;
    //consoleCursur.bVisible = 0;
    //consoleCursur.dwSize = 1;
    //SetConsoleCursorInfo(consoleHandle, &consoleCursur);



    //Initialize Player
    Init_Player();


	


    /*NormalEnemy* normal1 = new NormalEnemy(1,5);
   

    NormalEnemy* normal2 = new NormalEnemy(3,7);
    

    FastShootEnemy* fastEnemy1 = new FastShootEnemy(10,0);
    
    

    DoubleShootEnemy* db1 = new DoubleShootEnemy(15,15);
    
    

    LaserEnemy* le1 = new LaserEnemy(16,3);*/
    
  
    

	

    //Print_all();

    InvokeAllManagerStart();


    Update();
}



void GameManager::Update()
{
    
    while(true)
    {
        //Print_all();

		

		PrintManager::GetInstance()->ClearScreen();

        
        

        //Input();
		InputManager::GetInstance()->Update();

        m_player->Update();

        
        ObjManager::GetInstance()->Update();
        BulletManager::GetInstance()->Update();
        EnemyManager::GetInstance()->Update();
        EffectManager::GetInstance()->Update();
        StageManager::GetInstance()->Update();

		PrintManager::GetInstance()->DrawUIBox(1, 0,MAP_WIDTH + 1 , MAP_HEIGHT + 1,ePrint_Color::Gray);
		PrintManager::GetInstance()->DrawDebugUI(MAP_WIDTH + 3, 0,MAP_WIDTH + 30 , MAP_HEIGHT  - 5,ePrint_Color::Gray);

		if (m_bGameOver)
		{
			PrintManager::GetInstance()->Print(2, 2, "GAME OVER!!");

			PrintManager::GetInstance()->Print(MAP_WIDTH / 2 - 10, 10, "GAME OVER!!");

			PrintManager::GetInstance()->Print(17, 17, "GAME OVER!!");
			PrintManager::GetInstance()->Print(5, 20, "GAME OVER!!");

		}


		PrintManager::GetInstance()->FlipScreen();

        Sleep(10);


    }

}

//void GameManager::Input()
//{
//    if(m_player->GetCurrentMoveDelayCount() <= 0)
//    {
//        MoveInput();
//    }
//
//    KeyInput();
//
//}

//void GameManager::MoveInput()
//{
//    //moveInput
//   
//    //if(IsKeyDown(VK_LEFT))
//    //{
//    //    m_player->KeyDownCheck(VK_LEFT);
//    //}
//	//
//    //if(IsKeyDown(VK_RIGHT))
//    //{
//    //    m_player->KeyDownCheck(VK_RIGHT);
//    //}
//    //if(IsKeyDown(VK_UP))
//    //{
//    //    m_player->KeyDownCheck(VK_UP);
//    //}
//	//
//    //if(IsKeyDown(VK_DOWN))
//    //{
//    //    m_player->KeyDownCheck(VK_DOWN);
//    //}
//}

//void GameManager::KeyInput()
//{
//    //X
//    if(IsKeyDown(0x58))
//    {
//        //gotoxy(g_player->GetX(), g_player->GetY());
//
//        m_player->Shoot();
//    }
//    if (IsKeyDown(VK_ESCAPE))
//    {
//        
//        ExitProgram();
//        exit(0);
//    }
//
//}




