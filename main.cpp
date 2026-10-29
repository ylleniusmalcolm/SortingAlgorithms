#include <cstdlib>
#include <ctime>
#include "radix.h"
#include <iostream>

int main()
{
    int len = 5;
    std::srand(std::time(0));
    float* array = new float[len];
    for (int i = 0; i < len; i++)
    {
        array[i] = rand() % 2 == 0 ? 1.f : -1.f;
        array[i] *= (float)rand() / 1000.f;
    }
    
    for (int i = 0; i < len; i++)
    {
        std::cout << i << ": " << array[i] << std::endl;
    }

    RadixSort(array, len);

    for (int i = 0; i < len; i++)
    {
        std::cout << i << ": " << array[i] << std::endl;
    }

    return 0;
}