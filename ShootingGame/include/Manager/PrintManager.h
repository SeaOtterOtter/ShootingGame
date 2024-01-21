#pragma once
#include "IManager.h"
#include "Game/Flag.h"

class PrintManager : public IManager
{
public:
	static PrintManager* GetInstance();

	// IManager을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Update() override;

	void Print(int x, int y, const char* txt, ePrint_Color print_Color = ePrint_Color::White);
	void Print(int x, int y, wchar_t* txt, ePrint_Color print_Color = ePrint_Color::White);
	void Print(int x, int y, int txt, ePrint_Color print_Color = ePrint_Color::White);
	void Print(int x, int y, float txt, ePrint_Color print_Color = ePrint_Color::White);
	void PrintSpace(int x, int y);
	void gotoxy(int x, int y);

	void FlipScreen();
	void ClearScreen();

	void DrawUIBox(int xMin, int yMin ,int xMax, int yMax , ePrint_Color print_Color);
	void DrawDebugUI(int xMin, int yMin, int xMax, int yMax, ePrint_Color print_Color);


private:
	PrintManager();
	~PrintManager();
	
	
private:
	static PrintManager* m_instance;
	
	

	
	void ReleaseScreen();

private:
	int m_screenIndex;
	HANDLE h_screen[2];

};

