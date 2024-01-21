#pragma once
#include <unordered_map>
#include <vector>

#include "IManager.h"
#include "Utils/Delegate.h"
class InputManager : public IManager
{
private:
	InputManager();
	virtual ~InputManager();
	static InputManager* m_instance;
public:

	static InputManager* GetInstance();
	void Release();

	virtual void Start() override;
	virtual void Update() override;

	void RegisterKeyEvent(const unsigned int key, std::function<void(void)> listener);
	void UnRegisterKeyEvent(const unsigned int key, std::function<void(void)> listener);

private:
	bool IsKeyDown(int key);
	void Input();
	bool IsMoveKey(int key);
	void ProcessMoveInput();

private:
	//이동키는 제외
	std::unordered_map<unsigned int, Delegate<void> > m_keyEventHandlersMap;
};