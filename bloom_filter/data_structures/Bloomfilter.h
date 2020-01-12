/**
 *  @author Berat Postalcioglu
 **/

#pragma once

#include "Typedefs.h"
#include <vector>
#include <functional>
#include <string>

class bloomfilter
{
private:
    /**
        std::vector<bool> is a possibly space-efficient specialization of std::vector for the type bool.
        The manner in which std::vector<bool> is made space efficient (as well as whether it is optimized at all) is implementation defined. 
        One potential optimization involves coalescing vector elements such that each element occupies a single bit instead of sizeof(bool) bytes.
        For more information: https://en.cppreference.com/w/cpp/container/vector_bool
    **/
    std::vector<bool> _bitvector;
    u32 _kmer_len;
    u64 _bloomsize;
    std::vector<std::function<HASH_FUNC_SIGN>> _hash_funcs; // hash functions container, all of them must have same signature
    u64 _indexed_kmers;
    u64 _scanned_kmers;
    void _alloc_bitvector();

public:
    bloomfilter(u32 kmer_len, u64 bloomsize);
    inline const std::vector<bool> &bitvector() { return _bitvector; }
    inline void add_hash_func(std::function<HASH_FUNC_SIGN> f) { _hash_funcs.push_back(f); }
    inline u64 indexed_kmers() { return _indexed_kmers; }
    inline u64 scanned_kmers() { return _scanned_kmers; }
    /**
     *   populates bitvector by a string vector seqs
     **/
    void generate(std::vector<std::string> seqs);
    /**
     *   performs membership test for a string vector query_seqs and returns number of occurences by using bitvector
     **/
    u32 query(std::vector<std::string> query_seqs);
};