#include <Windows.h>
#include <iostream>
#include <string>
#include "Manager\PrintManager.h"
#include <Game/Game.h>
#include <Manager/GameManager.h>
#include "Character/Player/Player.h"
#include <Manager/StageManager.h>

PrintManager* PrintManager::m_instance;

PrintManager* PrintManager::GetInstance()
{
	{
		if(m_instance == nullptr)
		{
			m_instance = new PrintManager();
		}

		return m_instance;
	}
}

void PrintManager::Print(int x, int y, const char* txt, ePrint_Color print_Color)
{
	
	DWORD dw;
	COORD CursorPosition = { x, y };

	SetConsoleTextAttribute(h_screen[m_screenIndex], static_cast<int>(print_Color));

	SetConsoleCursorPosition(h_screen[m_screenIndex], CursorPosition);
	WriteFile(h_screen[m_screenIndex], txt, strlen(txt), &dw, NULL);

	SetConsoleTextAttribute(h_screen[m_screenIndex], static_cast<int>(ePrint_Color::White));


}

void PrintManager::Print(int x, int y, wchar_t* txt, ePrint_Color print_Color)
{
	
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleTextAttribute(h_screen[m_screenIndex], static_cast<int>(print_Color));

	SetConsoleCursorPosition(h_screen[m_screenIndex], CursorPosition);
	WriteFile(h_screen[m_screenIndex], txt, wcslen(txt) * sizeof(wchar_t), &dw, NULL);

	SetConsoleTextAttribute(h_screen[m_screenIndex], static_cast<int>(ePrint_Color::White));

}

void PrintManager::Print(int x, int y, int txt, ePrint_Color print_Color)
{
	Print(x, y, std::to_string(txt).c_str());
}

void PrintManager::Print(int x, int y, float txt, ePrint_Color print_Color)
{
	Print(x, y, std::to_string(txt).c_str());

}

void PrintManager::PrintSpace(int x, int y)
{
	Print(x, y, " ");

}

PrintManager::PrintManager()
{
}

PrintManager::~PrintManager()
{
}

void PrintManager::gotoxy(int x, int y)
{
    
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

void PrintManager::Start()
{
	CONSOLE_CURSOR_INFO cci;

	// 화면 버퍼 2개를 만든다.
	h_screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	h_screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);


	m_screenIndex = 0;
	// 커서를 숨긴다.
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(h_screen[0], &cci);
	SetConsoleCursorInfo(h_screen[1], &cci);



	


}

void PrintManager::Update()
{
}

void PrintManager::FlipScreen()
{
	SetConsoleActiveScreenBuffer(h_screen[m_screenIndex]);
	m_screenIndex = !m_screenIndex;
}

void PrintManager::ClearScreen()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(h_screen[m_screenIndex], ' ', 800 * 25, Coor, &dw);
}

void PrintManager::DrawUIBox(int xMin, int yMin, int xMax, int yMax , ePrint_Color print_Color)
{

	DWORD dw;
	COORD CursorPosition = { 0,0 };
	SetConsoleTextAttribute(h_screen[m_screenIndex], static_cast<int>(print_Color));

	
	char* verticalLineCharacter = "|";
	char* plusCharacter = "+";
	char* minusCharacter = "-";

	for (int i = yMin; i < yMax; ++i)
	{
		//gotoxy(1, i);
		//std::cout << "|";
		//gotoxy(yMax, i);
		//std::cout << "|";

		CursorPosition.X = xMin;
		CursorPosition.Y = i;
		SetConsoleCursorPosition(h_screen[m_screenIndex], CursorPosition);
		WriteFile(h_screen[m_screenIndex], verticalLineCharacter, strlen(verticalLineCharacter), &dw, NULL);
		
		CursorPosition.X = xMax;
		CursorPosition.Y = i;
		SetConsoleCursorPosition(h_screen[m_screenIndex], CursorPosition);
		WriteFile(h_screen[m_screenIndex], verticalLineCharacter, strlen(verticalLineCharacter), &dw, NULL);



	}

	//gotoxy(1, xMax);
	//std::cout << "+";
	//gotoxy(yMax, xMax);
	//std::cout << "+";

	CursorPosition.X = xMin;
	CursorPosition.Y = yMax;
	SetConsoleCursorPosition(h_screen[m_screenIndex], CursorPosition);
	WriteFile(h_screen[m_screenIndex], plusCharacter, strlen(plusCharacter), &dw, NULL);
	
	CursorPosition.X = xMax;
	CursorPosition.Y = yMax;
	SetConsoleCursorPosition(h_screen[m_screenIndex], CursorPosition);
	WriteFile(h_screen[m_screenIndex], plusCharacter, strlen(plusCharacter), &dw, NULL);


	for (int i = xMin + 1; i < xMax; ++i)
	{
		//gotoxy(i, xMax);
		//std::cout << "-";

		CursorPosition.X = i;
		CursorPosition.Y = yMax;
		SetConsoleCursorPosition(h_screen[m_screenIndex], CursorPosition);
		WriteFile(h_screen[m_screenIndex], minusCharacter, strlen(minusCharacter), &dw, NULL);

	}

	SetConsoleTextAttribute(h_screen[m_screenIndex], static_cast<int>(ePrint_Color::White));

}

void PrintManager::DrawDebugUI(int xMin, int yMin, int xMax, int yMax, ePrint_Color print_Color)
{
	DrawUIBox(xMin, yMin, xMax, yMax, print_Color);

	Position cursor;
	cursor.x = xMin + 2;
	cursor.y = yMin + 1;

	std::string printStr = "TIME : " + std::to_string(StageManager::GetInstance()->GetStageElapsedTime());

	PrintManager::GetInstance()->Print(cursor.x, cursor.y, printStr.c_str());

	cursor.y++;

	printStr = "Player HP : " + std::to_string(GameManager::GetInstance()->GetPlayer()->GetHp());

	PrintManager::GetInstance()->Print(cursor.x, cursor.y, printStr.c_str());


	cursor.y++;
	//cursor.y = yMin + 2;
	printStr = "Kill : " + std::to_string(GameManager::GetInstance()->GetKillCount());

	PrintManager::GetInstance()->Print(cursor.x, cursor.y, printStr.c_str());

}



void PrintManager::ReleaseScreen()
{
}
