#pragma once

//8°³
enum class eDirect
{
    None,
    Up,
    Down,
    Right,
    Left,
    Right_Down_Diagonal,
    Left_Down_Diagonal,
    Right_Up_Diagonal,
    Left_Up_Diagonal,
    Length

};

enum class eBullet_Owner
{
    None,
    Enemy,
    Player
};

enum class eFastShootEnemy_State
{
    Shoot,
    Move
};
enum class eDoubleShootEnemey_State
{
    Shoot,
    Move
};

enum class eLaserEnemy_State
{
    Lase,
    Move
   
};

enum class eLaserAttack_State
{
    MoveBeforeLase,
    Lase

};

enum class eLaserShootPosition
{
    Left,
    Right
};

enum class eEffect_Type
{
    Hit,
    Die
};

enum class ePrint_Color
{
    Black,
    Dark_Blue,
    Dark_Green,
    Dark_SkyBlue,
    Dark_Red,
    Dark_Violet,
    Dark_Yellow,
    Gray,
    Dark_Gray,
    Blue,
    Green,
    SkyBlue,
    Red,
    Violet,
    Yellow,
    White
};

enum class eEnemy_Type
{
    Normal,
    FastShoot,
    DoubleShoot,
    Laser
};