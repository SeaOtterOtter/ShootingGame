
#include <stdlib.h>
#include <chrono>
#include <random>

#include "Utils/Utils.h"


Utils* Utils::m_instance;

Utils* Utils::GetInstance()
{
    if(m_instance == NULL)
        m_instance = new Utils();

    return m_instance;
}

Utils::Utils()
{

}

Utils::~Utils()
{

}


int Utils::GetRandIntNum(int min, int max)
{
    auto cur_time = std::chrono::system_clock::now();

    auto duration = cur_time.time_since_epoch();

    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    mt_rand.seed(millis);


    std::uniform_int_distribution<int> dis(min, max);
    int num = dis(mt_rand);
    return num;
}

float Utils::GetRandFloatNum(float min, float max)
{
     auto cur_time = std::chrono::system_clock::now();

    auto duration = cur_time.time_since_epoch();

    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    mt_rand.seed(millis);


    std::uniform_real_distribution<float> dis(min, max);
    float num = dis(mt_rand);
    return num;
}

void Utils::Release()
{
    delete m_instance;
}
