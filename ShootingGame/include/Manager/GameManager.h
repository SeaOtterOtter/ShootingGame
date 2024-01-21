#pragma once
#include <stddef.h>
#include <assert.h>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Character/Enemy/Enemy.h"
#include "Utils/Delegate.h"
#include "IManager.h"

class Player;
class GameManager : public IManager
{
private:
    GameManager();
    virtual ~GameManager();
    static GameManager* m_instance;
public:

    static GameManager* GetInstance();
    void Release();

public:
    virtual void Start() override;
    void gotoxy(int x,int y);
    Player* GetPlayer();
	void IncreaseKillCount();
	int GetKillCount();
	void GameOver();

	void RegisterGameOverEvent(std::function<void(void)> listener);
	void UnRegisterGameOverEvent(std::function<void(void)> listener);

private:
    
    virtual void Update() override;
    

    void ExitProgram();
    void Init_Player();
    //
    //void GetKey();
    //void Print_all();
    //void Print_enemy();
    //void Print_player();

    bool IsKeyDown(int key);
    void KeyInput();
    void DrawUI();

    void InvokeAllManagerStart();


private:
	Player* m_player;
	int m_killCount;
	Delegate<void> m_gameOverDelegate;
	bool m_bGameOver;
public:

	
	//언오더드 맵 만들고 거기에 없으면 해당키 펑션 추가 
};
