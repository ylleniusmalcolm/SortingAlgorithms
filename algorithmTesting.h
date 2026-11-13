#pragma once
#include <time.h>

namespace algorithmTesting{
    template<typename T>
    time_t TimeFunction(T&& func, int count = 1)
    {
        time_t t = clock();
        for (int i = 0; i < count; i++)
        {
            func();
        }       

        return clock() - t;
    }
}