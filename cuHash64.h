/**
 *   \file cuHash64.h
 *   \brief Header for a basic hash table that stores one value per key.
 *
 *  Detailed description
 *
 */
#ifndef CUDAHT__CUCKOO__SRC__LIBRARY__HASH_TABLE__H
#define CUDAHT__CUCKOO__SRC__LIBRARY__HASH_TABLE__H


#include "definitions.h"
#include "hashFunction.h"


#include <cstdio>
#include <cudpp.h>

namespace CudaHT{
namespace CuckooHashing {
dim3 ComputerGridDim(unsigned threads);

unsigned ComputeMaxIterations(const unsigned num_keys,
                              const unsigned table_size,
                              const unsigned num_functions);

class HashTable
{
       public:
        HashTable();

        virtual ~HashTable(){Release();}

        virtual bool Initialize(const unsigned max_input_size,
                                const float space_usage = 1.25,
                                const unsigned num_functions = 4);

        virtual void Release();

        virtual bool Build(const unsigned input_size,
                           const unsigned long long *d_keys,
                           const unsigned *d_vals);

        virtual void Retrieve(const unsigned n_queries,
                              const unsigned long long *d_query_keys,
                              unsigned *d_query_results);
        inline unsigned get_table_size() const { return table_size_; }
        inline unsigned get_stash_count() const { return stash_count_; }
        inline uint2 get_stash_constants() const { return stash_constants_; }
        inline const Entry *get_contents() const { return d_contents_; }
        inline unsigned get_num_hash_functions() const
        {
                return num_hash_functions_;
        }

        inline Functions<2> get_constants_2() const { return constants_2_; }
        inline Functions<3> get_constants_3() const { return constants_3_; }
        inline Functions<4> get_constants_4() const { return constants_4_; }

        inline Functions<5> get_constants_5() const { return constants_5_; }

        //! Set the internal CUDPP instance
        inline void setTheCudpp(CUDPPHandle theCudpp_) { theCudpp = theCudpp_; }
       protected:
        unsigned table_size_;          //!< Size of the hash table.
        unsigned num_hash_functions_;  //!< Number of hash functions being used.
        CUHASH::Entry *d_contents_;  //!< Device memory: The hash table contents.  The
                             //!stash is stored at the end.
        unsigned stash_count_;  //!< Number of key-value pairs currently stored.
        uint2 stash_constants_;  //!< Hash function constants for the stash.

        Functions<2>
            constants_2_;  //!< Constants for a set of two hash functions.
        Functions<3>
            constants_3_;  //!< Constants for a set of three hash functions.
        Functions<4>
            constants_4_;  //!< Constants for a set of four hash functions.
        Functions<5>
            constants_5_;  //!< Constants for a set of five hash functions.

        unsigned *d_failures_;  //!< Device memory: General use error flag.

        CUDPPHandle theCudpp;  //!< CUDPP instance
};

namespace CUDAWrapper{
//! Fills a 64-bit array with a particular value.
void ClearTable(const unsigned  slots_in_table,
                const Entry     fill_value,
                Entry    *d_array);

//! Calls the Cuckoo Hash construction kernel.
void CallCuckooHash(const unsigned      n_entries,
                    const unsigned      num_hash_functions,
                    const unsigned     long long *d_keys,
                    const unsigned     *d_values,
                    const unsigned      table_size,
                    const Functions<2>  constants_2,
                    const Functions<3>  constants_3,
                    const Functions<4>  constants_4,
                    const Functions<5>  constants_5,
                    const unsigned      max_iteration_attempts,
                    Entry        *d_contents,
                          uint2         stash_constants,
                          unsigned     *d_stash_count,
                          unsigned     *d_failures,
                          unsigned     *d_iterations_taken);

//! Calls the kernel that performs retrievals.
void CallHashRetrieve(const unsigned      n_queries,
                      const unsigned      num_hash_functions,
                      const unsigned long long *keys_in,
                      const unsigned      table_size,
                      const Entry        *table,
                      const Functions<2>  constants_2,
                      const Functions<3>  constants_3,
                      const Functions<4>  constants_4,
                      const Functions<5>  constants_5,
                      const uint2         stash_constants,
                      const unsigned      stash_count,
                            unsigned     *values_out);
};

}; // namespace CuckooHashing
}; // namespace CudaHT
#endif
