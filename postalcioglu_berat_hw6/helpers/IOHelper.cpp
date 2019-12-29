#include "IOHelper.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <iterator>
#include <unordered_set>

using namespace std;

#define IS_LINEBREAK(ch) (ch == '\n' || ch == '\r')
#define OPTIMIZE_IO               \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);

// if a seq's length is less than kmer_length than not add it to vector
void fill_sequences_buff(vector<string> &seqs, const string &filename, u32 kmer_length)
{
    OPTIMIZE_IO

    ifstream file;
    file.open(filename);

    if (!file.is_open())
    {
        cout << filename << " file cannot be opened...\n";
        exit(1);
    }

    string line;

    while (getline(file, line))
    {
        if (!line.empty())
        {
            getline(file, line);
            if (line.size() >= kmer_length)
            {
                seqs.push_back(line);
            }
        }
    }

    file.close();
}
