#include <cstdlib>
#include <ctime>
#include "radix.h"
#include <iostream>
#include <vector>

int main()
{
    int len = 5;
    std::srand(std::time(0));
    std::vector<float> array = std::vector<float>();
    for (int i = 0; i < len; i++)
    {
        int v = rand() % 2 == 0 ? 1.f : -1.f;
        v *= (float)rand() / 1000.f;
        array.push_back(v);
    }
    
    for (int i = 0; i < len; i++)
    {
        std::cout << i << ": " << array[i] << std::endl;
    }
    
    radix::RadixSort(array);

    for (int i = 0; i < len; i++)
    {
        std::cout << i << ": " << array[i] << std::endl;
    }

    return 0;
}