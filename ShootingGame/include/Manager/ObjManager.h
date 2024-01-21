#pragma once

#include "Object/Obj.h"
#include "IManager.h"
#include <vector>

class ObjManager : public IManager
{
    private:
        ObjManager();
        virtual ~ObjManager();
        static ObjManager* m_instance;
       

    private:
        std::vector<Obj*> m_vecObj;

    public:
        static ObjManager* GetInstance();
      
        void AddObj(Obj* obj);
        void Release();
    public:
        virtual void Start() override;
        virtual void Update() override;

};
