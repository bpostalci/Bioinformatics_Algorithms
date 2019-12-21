#include "UPGMA.h"
#include "../data_structures/Cluster2.h"
#include "../helpers/IOHelper.h"
#include <iostream>
#include <utility>
#include <memory>

#define REP(i, a, b) for (u32 i = a; i < b; i++)

void buildUPGMA(double **dm, u32 size, const vector<seq> &seqs, const string &outfile)
{
    cluster *fc = NULL;
    cluster *lc = NULL;
    for (auto it : seqs)
    {
        string label(it.title);
        label.replace(0, 1, "");
        insert(fc, lc, label);
    }

    cluster *curc = fc;
    REP(i, 0, size)
    {
        node_branch *branch = curc->row;
        REP(j, 0, size)
        {
            branch->distance = dm[i][j];
            branch = branch->next_row;
        }
        curc = curc->next;
    }
    int j = 1;
    while (fc->next)
    {
        run_upgma(fc, lc);
        j++;
    }
    // cout << fc->name << "\n";
    fc->name += ";";
    write_tree(fc->name, outfile);
}
