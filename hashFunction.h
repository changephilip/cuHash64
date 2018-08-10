/**
 *   \file hashFunction.h
 *   \brief A Documented file.
 *
 *  Detailed description
 *
 */

#ifndef HASH_FUNCTIONS__H
#define HASH_FUNCTIONS__H

#include <vector_types.h>
#include "definitions.h"

namespace CUHASH_HF
{
const unsigned kPrimeDivisor = 4294967291u;

void GenerateFunctions(const unsigned N, const unsigned num_keys,
                        const unsigned long long *d_keys,
                        const unsigned table_size, uint2 *constants);
template <unsigned N>
struct Functions {
        uint2 constants[N];

        void Generate(const unsigned num_keys, const unsigned long long *d_keys,
                      const unsigned table_size)
        {
                GenerateFunctions(N, num_keys, d_keys, table_size, constants);
        }
};

inline __device__ __host__ unsigned hash_function_inner(
    const uint2 constants, const unsigned long long key)
{
        return ((constants.x ^ key) + constants.y) % kPrimeDivisor;
}

template <unsigned kNumHashFunctions>
inline __device__ __host__ unsigned hash_function(
    const Functions<kNumHashFunctions> functions, const unsigned which_function,
    const unsigned long long key)
{
        return hash_function_inner(functions.constants[which_function], key);
}

inline __device__ __host__ unsigned stash_hash_function(
    const uint2 stash_constants, const unsigned long long key)
{
        return (stash_constants.x ^ key + stash_constants.y) % CUHASH::kStashSize;
}
}  // namespace CUHASH

#endif
