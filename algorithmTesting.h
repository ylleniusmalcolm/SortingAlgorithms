#pragma once
#include <chrono>
#include <cstdint>

namespace algorithmTesting{
    template<typename T>
    int64_t TimeFunction(T&& func, int count = 1)
    {
        std::chrono::_V2::system_clock::time_point t = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < count; i++)
        {
            func();
        }
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t).count();
    }

    template<typename T>
    bool VerifyArray(T* array, size_t length)
    {
        for (size_t i = 0; i < length - 1; i++)
        {
            if (!(array[i] <= array[i + 1]))
                return false;
        }
        return true;
    }

    template<typename T>
    bool VerifyArray(std::vector<T> &array)
    {
        for (size_t i = 0; i < array.size() - 1; i++)
        {
            if (!(array[i] <= array[i + 1]))
                return false;
        }
        return true;
    }
}