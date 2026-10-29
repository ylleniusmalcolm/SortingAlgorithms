#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>
#include <iostream>

namespace radix
{
    const int bucketSize = 8;
    const int bucketCount = 1 << bucketSize;
    const int iterations = 32 / bucketSize;
    const uint32_t filter = bucketCount - 1;
    const uint32_t sign = 0x80000000U;

    void RadixSort(float *first, int length);
    void RadixSort(std::vector<float> &first);
}