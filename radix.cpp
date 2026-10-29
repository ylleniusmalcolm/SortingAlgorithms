#include "radix.h"

namespace radix{
    void RadixSort(float *first, int length)
    {
        //Needs a second buffer.
        float *second = new float[length];

        //Precalculating how many items will be in each bucket for each iteration.
        int *indices = new int[bucketCount * iterations];
        for (int i = 0; i < bucketCount * iterations; i++)
            indices[i] = 0;
        for (int i = 0; i < length; i++)
        {
            //Undefined behavior to the resuce! Taking the bit representation of the float and putting it in a uint so we can do bitwise logic.
            uint32_t v = *reinterpret_cast<uint32_t*>(&(first[i]));
            //Negative sign is 1, so gotta flip it. If number is negative, gotta flip the whole thing instead, otherwise we'd be sorting by magnitude.
            v = (v & sign) == 0 ? v ^ sign : v ^ UINT32_MAX;
            for (int j = 0; j < iterations; j++)
                indices[((v >> (j * bucketSize)) & filter) + j * bucketCount]++;
        }

        //Adding previous counts to each bucket to get a starting index.
        for (int i = 0; i < iterations; i++)
        {
            int total = 0;
            for (int j = 0; j < bucketCount; j++)
            {
                indices[i * bucketCount + j] += total;
                total = indices[i * bucketCount + j];
            }
        }

        //Shifting all indices down one index to start at 0.
        for (int i = 0; i < iterations; i++)
        {
            for (int j = bucketCount - 1; j > 0; j--)    
                indices[i * bucketCount + j] = indices[i * bucketCount + j - 1];
            indices[i * bucketCount] = 0;
        }    

        //Sorting with buckets!!
        for (int i = 0; i < iterations; i++)
        {
            for (int j = 0; j < length; j++)
            {
                //Same hacky solution as in precalculation with added filtering.
                uint32_t v = *reinterpret_cast<uint32_t*>(&(first[j]));
                v = (((v & sign) == 0 ? v ^ sign : v ^ UINT32_MAX) >> (i * bucketSize)) & filter;
                second[indices[v + i * bucketCount]] = first[j];
                indices[v + i * bucketCount]++;
            }
            std::swap(first, second);
        }    

        delete second;
        delete indices;
    }

    void RadixSort(std::vector<float> &first)
    {
        //Needs a second buffer.
        std::vector<float> second = std::vector<float>();
        second.resize(first.size());
        
        //Precalculating how many items will be in each bucket for each iteration.
        int *indices = new int[bucketCount * iterations];
        for (int i = 0; i < bucketCount * iterations; i++)
            indices[i] = 0;
        for (int i = 0; i < (int)first.size(); i++)
        {
            //Undefined behavior to the resuce! Taking the bit representation of the float and putting it in a uint so we can do bitwise logic.
            uint32_t v = *reinterpret_cast<uint32_t*>(&(first[i]));
            //Negative sign is 1, so gotta flip it. If number is negative, gotta flip the whole thing instead, otherwise we'd be sorting by magnitude.
            v = (v & sign) == 0 ? v ^ sign : v ^ UINT32_MAX;
            for (int j = 0; j < iterations; j++)
                indices[((v >> (j * bucketSize)) & filter) + j * bucketCount]++;
        }

        //Adding previous counts to each bucket to get a starting index.
        for (int i = 0; i < iterations; i++)
        {
            int total = 0;
            for (int j = 0; j < bucketCount; j++)
            {
                indices[i * bucketCount + j] += total;
                total = indices[i * bucketCount + j];
            }
        }

        //Shifting all indices down one index to start at 0.
        for (int i = 0; i < iterations; i++)
        {
            for (int j = bucketCount - 1; j > 0; j--)    
                indices[i * bucketCount + j] = indices[i * bucketCount + j - 1];
            indices[i * bucketCount] = 0;
        }    

        //Sorting with buckets!!
        for (int i = 0; i < iterations; i++)
        {
            for (int j = 0; j < (int)first.size(); j++)
            {
                //Same hacky solution as in precalculation with added filtering.
                uint32_t v = *reinterpret_cast<uint32_t*>(&(first[j]));
                v = (((v & sign) == 0 ? v ^ sign : v ^ UINT32_MAX) >> (i * bucketSize)) & filter;
                second[indices[v + i * bucketCount]] = first[j];
                indices[v + i * bucketCount]++;
            }
            std::swap(first, second);
        }    

        delete indices;
    }

    void RadixSort(int32_t *first, int length)
    {
        //Needs a second buffer.
        int32_t *second = new int32_t[length];

        //Precalculating how many items will be in each bucket for each iteration.
        int *indices = new int[bucketCount * iterations];
        for (int i = 0; i < bucketCount * iterations; i++)
            indices[i] = 0;
        for (int i = 0; i < length; i++)
        {
            //Negative sign is 1, so gotta flip it.
            int32_t v = first[i] ^ sign;
            for (int j = 0; j < iterations; j++)
                indices[((v >> (j * bucketSize)) & filter) + j * bucketCount]++;
        }

        //Adding previous counts to each bucket to get a starting index.
        for (int i = 0; i < iterations; i++)
        {
            int total = 0;
            for (int j = 0; j < bucketCount; j++)
            {
                indices[i * bucketCount + j] += total;
                total = indices[i * bucketCount + j];
            }
        }

        //Shifting all indices down one index to start at 0.
        for (int i = 0; i < iterations; i++)
        {
            for (int j = bucketCount - 1; j > 0; j--)    
                indices[i * bucketCount + j] = indices[i * bucketCount + j - 1];
            indices[i * bucketCount] = 0;
        }    

        //Sorting with buckets!!
        for (int i = 0; i < iterations; i++)
        {
            for (int j = 0; j < length; j++)
            {
                uint32_t v = first[j] ^ sign;
                v = (v >> (i * bucketSize)) & filter;
                second[indices[v + i * bucketCount]] = first[j];
                indices[v + i * bucketCount]++;
            }
            std::swap(first, second);
        }    

        delete second;
        delete indices;
    }

    void RadixSort(std::vector<int32_t> &first)
    {
        //Needs a second buffer.
        std::vector<int32_t> second = std::vector<int32_t>();
        second.resize(first.size());
        
        //Precalculating how many items will be in each bucket for each iteration.
        int *indices = new int[bucketCount * iterations];
        for (int i = 0; i < bucketCount * iterations; i++)
            indices[i] = 0;
        for (int i = 0; i < (int)first.size(); i++)
        {
            //Negative sign is 1, so gotta flip it.
            uint32_t v = first[i] ^ sign;
            for (int j = 0; j < iterations; j++)
                indices[((v >> (j * bucketSize)) & filter) + j * bucketCount]++;
        }

        //Adding previous counts to each bucket to get a starting index.
        for (int i = 0; i < iterations; i++)
        {
            int total = 0;
            for (int j = 0; j < bucketCount; j++)
            {
                indices[i * bucketCount + j] += total;
                total = indices[i * bucketCount + j];
            }
        }

        //Shifting all indices down one index to start at 0.
        for (int i = 0; i < iterations; i++)
        {
            for (int j = bucketCount - 1; j > 0; j--)    
                indices[i * bucketCount + j] = indices[i * bucketCount + j - 1];
            indices[i * bucketCount] = 0;
        }    

        //Sorting with buckets!!
        for (int i = 0; i < iterations; i++)
        {
            for (int j = 0; j < (int)first.size(); j++)
            {
                uint32_t v = ((first[j] ^ sign) >> (i * bucketSize)) & filter;
                second[indices[v + i * bucketCount]] = first[j];
                indices[v + i * bucketCount]++;
            }
            std::swap(first, second);
        }    

        delete indices;
    }

    void RadixSort(uint32_t *first, int length)
    {
        //Needs a second buffer.
        uint32_t *second = new uint32_t[length];

        //Precalculating how many items will be in each bucket for each iteration.
        int *indices = new int[bucketCount * iterations];
        for (int i = 0; i < bucketCount * iterations; i++)
            indices[i] = 0;
        for (int i = 0; i < length; i++)
        {
            uint32_t v = first[i];
            for (int j = 0; j < iterations; j++)
                indices[((v >> (j * bucketSize)) & filter) + j * bucketCount]++;
        }

        //Adding previous counts to each bucket to get a starting index.
        for (int i = 0; i < iterations; i++)
        {
            int total = 0;
            for (int j = 0; j < bucketCount; j++)
            {
                indices[i * bucketCount + j] += total;
                total = indices[i * bucketCount + j];
            }
        }

        //Shifting all indices down one index to start at 0.
        for (int i = 0; i < iterations; i++)
        {
            for (int j = bucketCount - 1; j > 0; j--)    
                indices[i * bucketCount + j] = indices[i * bucketCount + j - 1];
            indices[i * bucketCount] = 0;
        }    

        //Sorting with buckets!!
        for (int i = 0; i < iterations; i++)
        {
            for (int j = 0; j < length; j++)
            {
                uint32_t v = (first[i] >> (i * bucketSize)) & filter;
                second[indices[v + i * bucketCount]] = first[j];
                indices[v + i * bucketCount]++;
            }
            std::swap(first, second);
        }    

        delete second;
        delete indices;
    }

    void RadixSort(std::vector<uint32_t> &first)
    {
        //Needs a second buffer.
        std::vector<uint32_t> second = std::vector<uint32_t>();
        second.resize(first.size());
        
        //Precalculating how many items will be in each bucket for each iteration.
        int *indices = new int[bucketCount * iterations];
        for (int i = 0; i < bucketCount * iterations; i++)
            indices[i] = 0;
        for (int i = 0; i < (int)first.size(); i++)
            for (int j = 0; j < iterations; j++)
                indices[((first[i] >> (j * bucketSize)) & filter) + j * bucketCount]++;

        //Adding previous counts to each bucket to get a starting index.
        for (int i = 0; i < iterations; i++)
        {
            int total = 0;
            for (int j = 0; j < bucketCount; j++)
            {
                indices[i * bucketCount + j] += total;
                total = indices[i * bucketCount + j];
            }
        }

        //Shifting all indices down one index to start at 0.
        for (int i = 0; i < iterations; i++)
        {
            for (int j = bucketCount - 1; j > 0; j--)    
                indices[i * bucketCount + j] = indices[i * bucketCount + j - 1];
            indices[i * bucketCount] = 0;
        }    

        //Sorting with buckets!!
        for (int i = 0; i < iterations; i++)
        {
            for (int j = 0; j < (int)first.size(); j++)
            {
                uint32_t v = (first[j] >> (i * bucketSize)) & filter;
                second[indices[v + i * bucketCount]] = first[j];
                indices[v + i * bucketCount]++;
            }
            std::swap(first, second);
        }    

        delete indices;
    }
}