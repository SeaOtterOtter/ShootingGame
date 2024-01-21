#include "Manager/InputManager.h"
#include <Windows.h>
#include <Manager/GameManager.h>

#include "Character/Player/Player.h"


InputManager* InputManager::m_instance;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager* InputManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new InputManager();

	return m_instance;
}

void InputManager::Release()
{
	delete m_instance;
	m_instance = nullptr;
}

void InputManager::Start()
{
}

void InputManager::Update()
{
	Input();
}

bool InputManager::IsKeyDown(int key)
{

	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

void InputManager::Input()
{
	//부드러운 이동을 위해 이동키들은 따로 처리해준다 
	ProcessMoveInput();

	for (auto iter = m_keyEventHandlersMap.begin(); iter != m_keyEventHandlersMap.end(); iter++)
	{
		
		if (IsKeyDown(iter->first))
		{
			//delegate 호출
			iter->second();
		}
	}
}

bool InputManager::IsMoveKey(int key)
{
	return (key == VK_LEFT || key == VK_RIGHT || key == VK_UP || key == VK_DOWN);
}

void InputManager::ProcessMoveInput()
{
	Player* player = GameManager::GetInstance()->GetPlayer();
	if (player->GetCurrentMoveDelayCount() <= 0)
	{
		if (IsKeyDown(VK_LEFT))
		{
			player->KeyDownCheck(VK_LEFT);
			
		}

		if (IsKeyDown(VK_RIGHT))
		{
			player->KeyDownCheck(VK_RIGHT);

		}
		if (IsKeyDown(VK_DOWN))
		{
			player->KeyDownCheck(VK_DOWN);

		}
		if (IsKeyDown(VK_UP))
		{
			player->KeyDownCheck(VK_UP);

		}
	}
}

void InputManager::RegisterKeyEvent(const unsigned int key, std::function<void(void)> listener)
{
	auto findIter = m_keyEventHandlersMap.find(key);
	
	if (findIter == m_keyEventHandlersMap.end())
	{
		Delegate<void> delegate;
		delegate += listener;
	
		
		m_keyEventHandlersMap[key] = delegate;
	}
	else
	{
		findIter->second += listener;
	}
	

}

//void InputManager::UnRegisterKeyEvent(const unsigned int key, std::function<void(void)>& listener)
//{
//}
