#pragma once

#include "Typedefs.h"
#include <string>
#include <vector>

struct node_distance
{
    node_distance *nr; // next row
    node_distance *nc; // next column
    double dist;       // distance
};

struct node
{
    node *p; // previous node
    node *n; // next node
    std::string label;
    node_distance *row;
    node_distance *col;
    u32 noc = 0;
};

struct clusters
{
private:
    node *f = NULL; // first node of the cluster
    node *l = NULL; // last node of the cluster
    u32 cnt;      // number of clusters
public:
    u32 total() {return cnt;}
    node *&first() { return f; }
    node *&last() { return l; }
    void insert(const std::string &label);
    void remove(node *node);
    void find_min_distance(node *&n1, node *&n2);
    void run_upgma();
    void merge(node *&n1, node *&n2, std::vector<double> values, double val);
};
std::vector<double> run_formula(node *n1, node *n2, std::vector<double> first_vals, std::vector<double> second_vals);
