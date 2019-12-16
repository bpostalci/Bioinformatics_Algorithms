// #include "UPGMA.h"
// #include "../data_structures/Cluster.h"
// #include <iostream>
// #include <utility>
// #include <memory>

// #define REP(i, a, b) for (u32 i = a; i < b; i++)

// void buildUPGMA(double **dm, u32 size, const vector<seq> &seqs, stringstream &result)
// {
//     cout << "loop";

//     unique_ptr<clusters> c(new clusters);
//     for (auto it : seqs)
//     {
//         string label(it.title);
//         label.replace(0, 1, "");
//         c->insert(label);
//     }
//     cluster *new_cluster = c->first();
//     REP(i, 0, size)
//     {
//         cluster_distance *new_dist = new_cluster->row;
//         REP(j, 0, size)
//         {
//             new_dist->dist = dm[i][j];
//             new_dist = new_dist->nr;
//         }
//         new_cluster = new_cluster->n;
//     }

//     u32 j = 1;
//     while (c->first()->n)
//     {
//         c->run_upgma();
//         ++j;
//     }

//     result << c->first()->label;
// }

// #include "UPGMA.h"
// #include "../data_structures/Cluster3.h"
// #include <iostream>
// #include <utility>
// #include <memory>

// #define REP(i, a, b) for (u32 i = a; i < b; i++)

// void buildUPGMA(double **dm, u32 size, const vector<seq> &seqs, stringstream &result)
// {
//     cluster *head = NULL;
//     cluster *tail = NULL;
//     for (auto it : seqs)
//     {
//         string label(it.title);
//         label.replace(0, 1, "");
//         addCluster(head, tail, label);
//     }

//     cluster *node = head;
//     REP(i, 0, size)
//     {
//         cluster_distance *newDistance = node->row;
//         REP(j, 0, size)
//         {
//             newDistance->distance = dm[i][j];
//             newDistance = newDistance->nr;
//         }
//         node = node->next;
//     }
//     int j = 1;
//     while (head->next)
//     {
//         // cout << "---------------Printing UPGMA Round " << j << " (by rows)---------------" << endl;
//         // printRowByRow(head);
//         // cout << "--------------------------------------------------------------" << endl;

//         // cout << "---------------Printing UPGMA Round " << j << " (by columns)------------" << endl;
//         // printColumnByColumn(head);
//         // cout << "--------------------------------------------------------------" << endl;

//         UPGMA(head, tail);

//         j++;
//     }

//     result << head->name;
// }

#include "UPGMA.h"
#include "../data_structures/Cluster2.h"
#include <iostream>
#include <utility>
#include <memory>

#define REP(i, a, b) for (u32 i = a; i < b; i++)

void buildUPGMA(double **dm, u32 size, const vector<seq> &seqs, stringstream &result)
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

    result << head->name;
}
