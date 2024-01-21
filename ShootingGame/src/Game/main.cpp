#include <iostream>


#include "Manager/GameManager.h"
#include "Manager/EnemyManager.h"
#include "Manager/BulletManager.h"
#include "Manager/EffectManager.h"
#include "Manager/ObjManager.h"


#include <windows.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>



/*
    before start the game, please change the console size to (46,26)
*/
using namespace std;


//bool CtrlHandler(DWORD ctrlType)
//{
//    switch (ctrlType)
//    {
//       
//        case CTRL_CLOSE_EVENT: 
//        case CTRL_BREAK_EVENT:
//            return true;
//
//            break;
//    }
//
//    return true;
//}


int main()
{
    //SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, TRUE);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(796);

    GameManager::GetInstance()->Start();

   


    return 0;
}
