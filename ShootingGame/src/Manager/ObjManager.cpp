#include <stdlib.h>
#include <iostream>


#include "Manager/ObjManager.h"

#include "Game/Game.h"



ObjManager* ObjManager::m_instance;

ObjManager::ObjManager()
{

}

ObjManager::~ObjManager()
{
    
}

void ObjManager::Release()
{
    for (size_t i = 0; i < m_vecObj.size(); ++i)
    {
        SAFE_DELETE(m_vecObj[i]);
    }

    delete m_instance;
}

void ObjManager::Start()
{
}

void ObjManager::Update()
{
    for(size_t i = 0; i < m_vecObj.size(); ++i)
    {
        if(m_vecObj[i]->IsActive())
        {
            m_vecObj[i]->Update();
        }
    }

    //std::cout << m_vecObj.size();
}

ObjManager* ObjManager::GetInstance()
{

    if(m_instance == NULL)
    {
        m_instance = new ObjManager();
    }

    return m_instance;
}



void ObjManager::AddObj(Obj* obj)
{
    m_vecObj.push_back(obj);
}
