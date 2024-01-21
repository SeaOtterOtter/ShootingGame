#pragma once

//0~45
#define MAP_WIDTH 45
//0~25
#define MAP_HEIGHT 25
#define MAP_OFFSET_FROM_START 2


	

#include <windows.h>
#include <cassert>

#include "Game/Macro.h"



struct Position
{
    int x;
    int y;

    Position()
    {
        x = 0;
        y = 0;
    }


    bool operator==(Position& position)
    {
        return this->x == position.x && this->y == position.y;
    }
};


