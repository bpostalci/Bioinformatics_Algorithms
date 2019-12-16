#include "UPGMA.h"
#include "../data_structures/Cluster.h"
#include <iostream>
#include <utility>
#include <memory>

#define REP(i, a, b) for (u32 i = a; i < b; i++)

void buildUPGMA(double **dm, u32 size, const vector<seq> &seqs, stringstream &result)
{
    unique_ptr<clusters> c(new clusters);
    for (auto it : seqs)
    {
        string label(it.title);
        label.replace(0, 1, "");
        c->insert(label);
    }
    node *new_node = c->first();
    REP(i, 0, size)
    {
        node_distance *new_dist = new_node->row;
        REP(j, 0, size)
        {
            new_dist->dist = dm[i][j];
            new_dist = new_dist->nr;
        }
        new_node = new_node->n;
    }

    u32 j = 1;
    while (c->first()->n)
    {
        c->run_upgma();
        ++j;
    }

    result << c->first()->label;
}
