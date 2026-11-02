#include <cstdlib>
#include <time.h>
#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include "string"
#include "radix.h"
#include "algorithmTesting.h"
#include "inputHandler.h"

int main()
{
    int len = InputHandler::InputInteger("Number of iterations: ", [](int v){ return v > 0; });
    int count = InputHandler::InputInteger("Number of runs: ", [](int v){ return v > 0; });
    std::srand(time(0));
    std::vector<double> array = std::vector<double>();
    for (int i = 0; i < len; i++)
    {
        double v = rand() % 2 == 0 ? 1.f : -1.f;
        v *= (double)rand() / 1000.f;
        array.push_back(v);
    }
    
    /*for (int i = 0; i < len; i++)
    {
        std::cout << i << ": " << std::setprecision(10) << array[i] << std::endl;
    }*/
    
    time_t t = algorithmTesting::TimeFunction([&array](){radix64::RadixSort(array);}, count);

    /*for (int i = 0; i < len; i++)
    {
        std::cout << i << ": " << std::setprecision(10) << array[i] << std::endl;
    }*/

    std::cout << "Testing took " << t << " clicks" << " (" << (float)t / CLOCKS_PER_SEC << " seconds).\n";

    return 0;
}