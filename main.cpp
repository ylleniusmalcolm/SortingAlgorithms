#include "stdlib.h"
#include "radix.h"
#include <iostream>

int main()
{
    float* array = new float[1000];
    for (int i = 0; i < 1000; i++)
    {
        array[i] = (float)(i - 500) / 50.f;
        std::cout << array[i] << std::endl;
    }
    
    RadixSort(array, 1000);

    for (int i = 0; i < 1000; i++)
    {
        std::cout << array[i] << std::endl;
    }

    return 0;
}