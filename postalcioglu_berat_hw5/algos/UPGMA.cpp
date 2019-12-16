#include "UPGMA.h"
#include <iostream>
#include <utility>

#define REP(i, a, b) for (u32 i = a; i < b; i++)

pair<int, int> min(double **dm, u32 size)
{
    pair<int, int> res;
    int min_i = 1;
    int min_j = 0;
    REP(i, 0, size)
    {
        REP(j, 0, size)
        {
            if (i != j)
            {
                if (dm[i][j] < dm[min_i][min_j])
                {
                    min_i = i;
                    min_j = j;
                }
            }
        }
    }

    res.first = min_i;
    res.second = min_j;
    return res;
}

void buildUPGMA(double **dm, u32 size, const vector<seq> &seqs, stringstream &result)
{
   
    for(auto it : seqs) 
    {
        cout << it.title << "\n";
    }
    
}

// void buildUPGMA(double **dm, u32 size, const vector<seq> &seqs, stringstream &result)
// {
//     if (size == 1)
//     {
//         return;
//     }

//     pair<int, int> mp = min(dm, size);
//     if (mp.second > mp.first)
//     {
//         mp.first = mp.second;
//         mp.second = mp.first;
//     }

//     string title1(seqs[mp.second].title);
//     title1.replace(0, 1, "");
//     string title2(seqs[mp.first].title);
//     title2.replace(0, 1, "");

//     double val = (dm[mp.first][mp.second]) / 2;
//     result << "(" << title1 << ":" << val << ", " << title2 << ":" << val << ")";
//     cout << result.str() << "\n";

//     // calculate new matrix

// }