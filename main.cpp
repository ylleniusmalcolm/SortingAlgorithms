#include <cstdlib>
#include <time.h>
#include <functional>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include "radix.h"
#include "algorithmTesting.h"
#include "inputHandler.h"

int main()
{
    int len = InputHandler::InputT<int>("Number of iterations: ", [](int v){ return v > 0; }, "Value must be greater than 0.");
    int count = InputHandler::InputT<int>("Number of runs: ", [](int v){ return v > 0; }, "Value must be greater than 0.");
    std::srand(time(0));
    std::vector<double> array = std::vector<double>();

    for (int i = 0; i < len; i++)
    {
        array.push_back((double)(rand() * rand() % 2 == 0 ? 1 : -1) / 100.f);
    }

    int64_t t = algorithmTesting::TimeFunction([&array](){radix::RadixSort<double>(array);}, count);

    if (!algorithmTesting::VerifyArray<double>(array))
        std::cout << "Sorting failed\n";
    else
    {
        std::cout << "Testing took " << t << " clicks" << " (" << (double)t / CLOCKS_PER_SEC << " seconds).\n";
        std::cout << "That's " << (double)t / (CLOCKS_PER_SEC) /
            (double)count << " seconds per run at " << std::setprecision(3) << (double)(len * count) /
            ((double)t / CLOCKS_PER_SEC) << " iterations per second." << std::endl;    
    }    

    return 0;
}