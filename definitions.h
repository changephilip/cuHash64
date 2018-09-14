/**
 *   \file definitions.h
 *   \brief Stores configuration flags and definitions for hard-coded values in
 * hash table implementations.
 *
 *  Detailed description
 *
 */

#ifndef CUDAHT__CUCKOO__SRC__LIBRARY__DEFINITIONS__H
#define CUDAHT__CUCKOO__SRC__LIBRARY__DEFINITIONS__H

#include <cstdio>
#include <limits>
inline void PrintMessage(const char *message, const bool error = false)
{
        if (error) {
                printf("!!! %s\n", message);
        } else {
                printf("%s\n", message);
        }
}
/**
 *  Hash table constants and definitions
 */
namespace CudaHT
{
        namespace CuckooHashing{
// A key and its value are stored in a 96-bit struct.
typedef struct {
        unsigned long long key;
        unsigned value;
}Entry;

// Number of build attempts
const unsigned kMaxRestartAttempts = 10;
// Signifies empty slots in the table.
const unsigned long long kKeyEmpty = 0xFFFFFFFFFFFFFFFFu;
// Signifies that a query key was not found.
const unsigned kNotFound =
    0xFFFFFFFFu;  // Signifies that a query key was not found.
const unsigned kMaxHashFunctions =
    5;  // Maximum number of hash functions allowed.
const unsigned kStashSize = 101;

const Entry kEntryEmpty = (Entry){kKeyEmpty, 0u};
const Entry kEntryNotFound = (Entry){kKeyEmpty, kNotFound};
const unsigned kBlockSize = 64;
const unsigned kGridSize = 16384;
const float kMinimumSpaceUsages[] = {std::numeric_limits<float>::max(),
                                     std::numeric_limits<float>::max(),
                                     2.01f,
                                     1.1f,
                                     1.03f,
                                     1.02f};

};  // namespace CuckooHashing
};  // namespace CudaHT
#endif
