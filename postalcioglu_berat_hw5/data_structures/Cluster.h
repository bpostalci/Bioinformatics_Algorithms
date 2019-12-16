#pragma once

#include "Typedefs.h"
#include <string>
#include <vector>

struct cluster_distance
{
    cluster_distance *nr; // next row
    cluster_distance *nc; // next column
    double dist;       // distance
};

struct cluster
{
    cluster *p; // previous node
    cluster *n; // next node
    std::string label;
    cluster_distance *row;
    cluster_distance *col;
    u32 cnt = 0;
};

struct clusters
{
private:
    cluster *f = NULL; // first cluster
    cluster *l = NULL; // last cluster
    u32 cnt = 0;       // number of clusters
public:
    u32 total() {return cnt;}
    cluster *&first() { return f; }
    cluster *&last() { return l; }
    void insert(const std::string &label);
    bool remove(cluster *node);
    void find_min_distance(cluster *&n1, cluster *&n2);
    void run_upgma();
    void merge(cluster *&n1, cluster *&n2, std::vector<double> values, double val);
};
std::vector<double> run_formula(cluster *n1, cluster *n2, std::vector<double> first_vals, std::vector<double> second_vals);
