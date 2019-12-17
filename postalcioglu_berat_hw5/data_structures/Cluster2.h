#pragma once

#include <string>
#include <vector>
#include "Typedefs.h"

namespace upgma
{
struct node_branch
{
  double distance;
  node_branch *next_col;
  node_branch *next_row;
};

struct cluster
{
  cluster *prev;
  cluster *next;
  node_branch *row;
  node_branch *column;
  std::string name;
  int num_of_nodes;
};

void run_upgma(cluster *&fc, cluster *&lc);

std::vector<double> run_formula(cluster *c1, cluster *c2, std::vector<double> c1_vals, std::vector<double> v2_vals);

void insert(cluster *&fc, cluster *&lc, const std::string &name);

void remove(cluster *&fc, cluster *&lc, cluster *c_no_remove);

void find_min_distance(cluster *fc, cluster *&c1, cluster *&c2);

void merge_clusters(cluster *&fc, cluster *&lc, cluster *&c1, cluster *&c2, std::vector<double> vals, double val);

}; // namespace upgma
