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
    double* array = new double[len];
    for (int i = 0; i < len; i++)
    {
        double v = rand() % 2 == 0 ? 1.f : -1.f;
        v *= (double)rand() / 1000.f;
        array[i] = v;
    }

    time_t t = algorithmTesting::TimeFunction([&array, len](){radix::RadixSort<double>(array, len);}, count);

    std::cout << "Testing took " << t << " clicks" << " (" << (float)t / CLOCKS_PER_SEC << " seconds).\n";
    std::cout << "That's " << (float)t / (CLOCKS_PER_SEC) /
        (float)count << " seconds per run at " << std::setprecision(3) << (float)(len * count) /
        ((float)t / CLOCKS_PER_SEC) << " iterations per second." << std::endl;


    for (int i = 0; i < len; i++)
    {
        std::cout << array[i] << std::endl;
    }
    

    return 0;
}