#pragma once
#include <vector>
#include <cstdint>
#include <algorithm>
#include <type_traits>
#include <functional>

namespace radix32
{
    const int bucketSize = 8;
    const int bucketCount = 1 << bucketSize;
    const int iterations = 32 / bucketSize;
    const uint32_t filter = bucketCount - 1;
    const uint32_t sign = 0x80000000U;

    void RadixSort(float *first, int length);
    void RadixSort(std::vector<float> &first);

    void RadixSort(int32_t *first, int length);
    void RadixSort(std::vector<int32_t> &first);
    
    void RadixSort(uint32_t *first, int length);
    void RadixSort(std::vector<uint32_t> &first);
}

namespace radix64
{
    const int bucketSize = 8;
    const int bucketCount = 1 << bucketSize;
    const int iterations = 64 / bucketSize;
    const uint64_t filter = bucketCount - 1;
    const uint64_t sign = 0x8000000000000000ULL;

    void RadixSort(double *first, int length);
    void RadixSort(std::vector<double> &first);

    void RadixSort(int64_t *first, int length);
    void RadixSort(std::vector<int64_t> &first);
    
    void RadixSort(uint64_t *first, int length);
    void RadixSort(std::vector<uint64_t> &first);
}

namespace radix
{
    template<typename T>
    using rType = std::conditional_t<
        sizeof(T) == 1,
        uint8_t,
        std::conditional_t<
            sizeof(T) == 2,
            uint16_t,
            std::conditional_t<
                sizeof(T) == 4,
                uint32_t,
                std::conditional_t<
                    sizeof(T) == 8,
                    uint64_t,
                    void
                >
            >
        >
    >;
    
    const int bucketSize = 8;
    const int bucketCount = 1 << bucketSize;

    template<typename T>
    const int iterations = (sizeof(T) * 8) / bucketSize;
    template<typename T>
    const rType<T> signFlag = (rType<T>)1 << ((sizeof(T) * 8) - 1);    
    template<typename T>
    const rType<T> filter = bucketCount - 1;
    template<typename T>
    const rType<T> rTypeMax = ((rType<T>)0) - 1;

    template<typename T>
    inline rType<T> BitTransform(rType<T> v)
    {
        if constexpr(std::is_floating_point<T>::value)
            return (v & signFlag<T>) == 0 ? v ^ signFlag<T> : v ^ rTypeMax<T>;
        else if constexpr(std::is_integral<T>::value && std::is_signed<T>::value)
            return v ^ signFlag<T>;
        else
            return v;
    }

    template<typename T>
    void RadixSort(T* first, size_t length)
    {
        static_assert(std::is_arithmetic_v<T>, "Can only be used on arithmetic types.");

        //Needs a second buffer.
        T *second = new T[length];

        //Precalculating how many items will be in each bucket for each iteration.
        int *indices = new int[bucketCount * iterations<T>];
        for (int i = 0; i < bucketCount * iterations<T>; i++)
            indices[i] = 0;
        for (size_t i = 0; i < length; i++)
        {
            rType<T> v;
            if constexpr(std::is_floating_point<T>::value)
            {
                //Undefined behavior to the resuce! Taking the bit representation of the float and putting it in a uint so we can do bitwise logic.
                v = *reinterpret_cast<rType<T>*>(&(first[i]));
            }
            else
                v = first[i];
            v = BitTransform<T>(v);
            for (size_t j = 0; j < iterations<T>; j++)
                indices[((v >> (j * bucketSize)) & filter<T>) + j * bucketCount]++;
        }
        

        //Adding previous counts to each bucket to get a starting index.
        for (int i = 0; i < iterations<T>; i++)
        {
            int total = 0;
            for (int j = 0; j < bucketCount; j++)
            {
                indices[i * bucketCount + j] += total;
                total = indices[i * bucketCount + j];
            }
        }

        //Shifting all indices down one index to start at 0.
        for (int i = 0; i < iterations<T>; i++)
        {
            for (int j = bucketCount - 1; j > 0; j--)    
                indices[i * bucketCount + j] = indices[i * bucketCount + j - 1];
            indices[i * bucketCount] = 0;
        }        

        //Sorting with buckets!!
        for (int i = 0; i < iterations<T>; i++)
        {
            for (size_t j = 0; j < length; j++)
            {
                rType<T> v;
                if constexpr(std::is_floating_point<T>::value)
                    v = *reinterpret_cast<rType<T>*>(&(first[j]));
                else
                    v = first[j];
                v = BitTransform<T>(v);
                v = (v >> (i * bucketSize)) & filter<T>;
                second[indices[v + i * bucketCount]] = first[j];
                indices[v + i * bucketCount]++;
            }
            std::swap(first, second);
        }    

        delete second;
        delete indices;
    }

    template<typename T>
    void RadixSort(std::vector<T> &first)
    {
        static_assert(std::is_arithmetic_v<T>, "Can only be used on arithmetic types.");

        //Needs a second buffer.
        std::vector<T> second = std::vector<T>();
        second.resize(first.size());

        //Precalculating how many items will be in each bucket for each iteration.
        int *indices = new int[bucketCount * iterations<T>];
        for (int i = 0; i < bucketCount * iterations<T>; i++)
            indices[i] = 0;
        for (size_t i = 0; i < first.size(); i++)
        {
            rType<T> v;
            if constexpr(std::is_floating_point<T>::value)
            {
                //Undefined behavior to the resuce! Taking the bit representation of the float and putting it in a uint so we can do bitwise logic.
                v = *reinterpret_cast<rType<T>*>(&(first[i]));
            }
            else
                v = first[i];
            v = BitTransform<T>(v);
            for (size_t j = 0; j < iterations<T>; j++)
                indices[((v >> (j * bucketSize)) & filter<T>) + j * bucketCount]++;
        }
        

        //Adding previous counts to each bucket to get a starting index.
        for (int i = 0; i < iterations<T>; i++)
        {
            int total = 0;
            for (int j = 0; j < bucketCount; j++)
            {
                indices[i * bucketCount + j] += total;
                total = indices[i * bucketCount + j];
            }
        }

        //Shifting all indices down one index to start at 0.
        for (int i = 0; i < iterations<T>; i++)
        {
            for (int j = bucketCount - 1; j > 0; j--)    
                indices[i * bucketCount + j] = indices[i * bucketCount + j - 1];
            indices[i * bucketCount] = 0;
        }        

        //Sorting with buckets!!
        for (int i = 0; i < iterations<T>; i++)
        {
            for (size_t j = 0; j < first.size(); j++)
            {
                rType<T> v;
                if constexpr(std::is_floating_point<T>::value)
                    v = *reinterpret_cast<rType<T>*>(&(first[j]));
                else
                    v = first[j];
                v = BitTransform<T>(v);
                v = (v >> (i * bucketSize)) & filter<T>;
                second[indices[v + i * bucketCount]] = first[j];
                indices[v + i * bucketCount]++;
            }
            std::swap(first, second);
        }    

        delete indices;
    }
}