/**
 *  @author Berat Postalcioglu
 **/

#include "Bloomfilter.h"

#define REP(i, a, b) for (u64 i = a; i < b; i++)

using namespace std;

void bloomfilter::_alloc_bitvector()
{
    _bitvector.reserve(_bloomsize);

    // init bitvector
    REP(i, 0, _bloomsize)
    {
        _bitvector.push_back(false);
    }
}

bloomfilter::bloomfilter(u32 kmer_len, u64 bloomsize) : _kmer_len(kmer_len), _bloomsize(bloomsize), _indexed_kmers(0), _scanned_kmers(0)
{
    _alloc_bitvector();
}

void bloomfilter::generate(vector<string> seqs)
{
    u32 seqs_len = seqs.size();

    REP(i, 0, seqs_len)
    {
        string seq = seqs[i];
        u32 seq_len = seq.size();
        u32 limit = seq_len - _kmer_len + 1;

        // iterate through kmers
        REP(j, 0, limit)
        {
            string kmer = seq.substr(j, _kmer_len);
            ++_indexed_kmers;
            // populate bitvector
            for (const function<HASH_FUNC_SIGN>& func : _hash_funcs)
            {
                u64 index = func(kmer.c_str(), kmer.size()) % _bloomsize;
                _bitvector[index] = true;
            }
        }
    }
}

u32 bloomfilter::query(vector<string> query_seqs)
{
    u32 cnt = 0;
    u32 seqs_len = query_seqs.size();

    REP(i, 0, seqs_len)
    {
        string seq = query_seqs[i];
        u32 seq_len = seq.size();
        u32 limit = seq_len - _kmer_len + 1;

        // iterate through kmers
        REP(j, 0, limit)
        {
            bool exists = true;
            string kmer = seq.substr(j, _kmer_len);
            ++_scanned_kmers;

            // test if kmer exists in bloomfilter
            for (const function<HASH_FUNC_SIGN>& func : _hash_funcs)
            {
                u32 index = func(kmer.c_str(), kmer.size()) % _bloomsize;
                
                if (_bitvector[index] == false)
                {
                    exists = false;
                    break;
                }
            }

            if (exists)
            {
                ++cnt;
            }
        }
    }

    return cnt;
}