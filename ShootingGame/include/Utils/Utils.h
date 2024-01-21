#pragma once
#include <random>

class Utils
{

public:
    static Utils* GetInstance();


private:
        Utils();
        virtual ~Utils();
        static Utils* m_instance;

private:
        std::mt19937 mt_rand;
public:

    int GetRandIntNum(int min, int max);
    float GetRandFloatNum(float min, float max);
    void Release();
    protected:

    private:
};
