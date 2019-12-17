#include "UPGMA.h"
#include "../data_structures/Cluster2.h"
#include "../helpers/IOHelper.h"
#include <iostream>
#include <utility>
#include <memory>

#define REP(i, a, b) for (u32 i = a; i < b; i++)

void buildUPGMA(double **dm, u32 size, const vector<seq> &seqs, const string &outfile)
{
    ClusterNode *head = NULL;
    ClusterNode *tail = NULL;
    for (auto it : seqs)
    {
        string label(it.title);
        label.replace(0, 1, "");
        addCluster(head, tail, label);
    }

    ClusterNode *node = head;
    REP(i, 0, size)
    {
        DistanceNode *newDistance = node->row;
        REP(j, 0, size)
        {
            newDistance->distance = dm[i][j];
            newDistance = newDistance->nextInRow;
        }
        node = node->next;
    }
    int j = 1;
    while (head->next)
    {
        UPGMA(head, tail);
        j++;
    }
    head->name += ";";
    write_tree(head->name, outfile);
}
