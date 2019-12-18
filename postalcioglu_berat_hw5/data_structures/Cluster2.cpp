#include "Cluster2.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;


int find_min_distance_val(vector<double> &distances)
{
  int min = 0;
  while (distances[min] == 0)
  {
    min++;
  }
  for (unsigned int i = 0; i < distances.size(); i++)
  {
    if (distances[i] != 0)
    {
      if (distances[min] > distances[i])
      {
        min = i;
      }
    }
  }
  return min;
}

static double GLOBAL_MIN_DISTANCE = 0.0;
void find_min_distance(cluster *fc, cluster *&c1, cluster *&c2)
{
  double min_distance = numeric_limits<double>::max();

  node_branch *tmp_branch = NULL;
  cluster *min_cluster = NULL;
  node_branch *min_branch = NULL;
  cluster *other_cluster = NULL;

  cluster *current_cluster = fc;
  while (current_cluster != NULL)
  {
    tmp_branch = current_cluster->column;
    while (tmp_branch != NULL)
    {
      if (tmp_branch->distance < min_distance && tmp_branch->distance != 0)
      {
        min_distance = tmp_branch->distance;
        min_cluster = current_cluster;
        min_branch = tmp_branch;
      }
      tmp_branch = tmp_branch->next_col;
    }

    current_cluster = current_cluster->next;
  }
  c1 = min_cluster;

  other_cluster = min_cluster->next;
  while (other_cluster != NULL)
  {
    tmp_branch = other_cluster->column;
    while (tmp_branch != NULL)
    {
      if (tmp_branch->distance == min_branch->distance)
      {
        GLOBAL_MIN_DISTANCE = min_branch->distance;
        c2 = other_cluster;
        return;
      }
      tmp_branch = tmp_branch->next_col;
    }

    other_cluster = other_cluster->next;
  }
}

void run_upgma(cluster *&fc, cluster *&lc)
{
  vector<double> c1_dists;
  vector<double> c2_dists;

  cluster *c1 = NULL;
  cluster *c2 = NULL;
  find_min_distance(fc, c1, c2);

  node_branch *first_branch = c1->column;
  while (first_branch != NULL)
  {
    c1_dists.push_back(first_branch->distance);
    first_branch = first_branch->next_col;
  }

  node_branch *second_branch = c2->column;
  while (second_branch != NULL)
  {
    c2_dists.push_back(second_branch->distance);
    second_branch = second_branch->next_col;
  }
  vector<double> res_dists = run_formula(c1, c2, c1_dists, c2_dists);
  int min = find_min_distance_val(c1_dists);
  merge_clusters(fc, lc, c1, c2, res_dists, c1_dists[min]);
}

void merge_clusters(cluster *&fc, cluster *&lc, cluster *&c1, cluster *&c2, vector<double> vals, double val)
{
  stringstream namess;
  namess.setf(ios::fixed);
  namess.precision(3);
  double weight = val / 2;
  namess << "(" << c1->name << ":" << weight << ", " << c2->name << ":" << weight << ")";
  string name = namess.str();
  node_branch *first_branch_col;
  node_branch *first_branch_row;
  remove(fc, lc, c1);
  remove(fc, lc, c2);
  insert(fc, lc, name);
  cluster *new_cluster = lc;
  new_cluster->num_of_nodes = c1->num_of_nodes + c2->num_of_nodes;

  first_branch_col = new_cluster->column;
  first_branch_row = new_cluster->row;

  for (u32 i = 0; (first_branch_col != first_branch_row); i++)
  {
    if (i < vals.size())
    {
      first_branch_col->distance = vals[i];
      first_branch_row->distance = vals[i];
    }
    else
    {
      const double tmp_val = 1.0;
      first_branch_col->distance = tmp_val;
      first_branch_row->distance = tmp_val;
    }

    first_branch_col = first_branch_col->next_col;
    first_branch_row = first_branch_row->next_row;
  }

  first_branch_col->next_col = NULL;
  first_branch_row->next_row = NULL;
  first_branch_col->next_row = NULL;
  first_branch_row->next_col = NULL;
}

void insert(cluster *&fc, cluster *&lc, const string &name)
{
  cluster *cluster_to_insert = new cluster;
  cluster_to_insert->num_of_nodes = 1;
  cluster_to_insert->name = name;

  if (fc != NULL)
  {
    cluster_to_insert->prev = lc;
    lc->next = cluster_to_insert;
    lc = cluster_to_insert;
    lc->next = NULL;

    node_branch *branch_col = new node_branch;
    node_branch *branch_row = new node_branch;

    lc->column = branch_col;
    lc->row = branch_row;

    node_branch *prev_branch_col = lc->prev->column;
    node_branch *prev_branch_row = lc->prev->row;
    node_branch *cur_branch_col = lc->column;
    node_branch *cur_branch_row = lc->row;

    prev_branch_col->next_row = cur_branch_col;
    prev_branch_row->next_col = cur_branch_row;

    while (prev_branch_col != prev_branch_row)
    {
      node_branch *new_branch_col = new node_branch;
      node_branch *new_branch_row = new node_branch;

      cur_branch_col->next_col = new_branch_col;
      cur_branch_row->next_row = new_branch_row;
      cur_branch_col = cur_branch_col->next_col;
      cur_branch_row = cur_branch_row->next_row;

      prev_branch_col = prev_branch_col->next_col;
      prev_branch_row = prev_branch_row->next_row;
      prev_branch_col->next_row = cur_branch_col;
      prev_branch_row->next_col = cur_branch_row;
    }
    cur_branch_row->next_row = cur_branch_col->next_col = new node_branch;
  }
  else
  {
    fc = cluster_to_insert;
    lc = cluster_to_insert;
    fc->column = fc->row = new node_branch;
  }
}

void remove(cluster *&fc, cluster *&lc, cluster *c_to_remove)
{
  if (c_to_remove == fc && c_to_remove == lc)
  {
    cluster *tmp_node = fc;

    tmp_node->next = NULL;
    tmp_node->prev = NULL;

    fc = NULL;
    lc = NULL;
    // delete tmp_node;
    return;
  }
  if (c_to_remove == lc)
  {
    lc = lc->prev;
    lc->next = NULL;
    node_branch *tmp_row_branch;
    node_branch *tmp_col_branch;

    tmp_row_branch = lc->row;
    tmp_col_branch = lc->column;
    while (tmp_row_branch != tmp_col_branch)
    {
      tmp_row_branch = tmp_row_branch->next_row;
      tmp_col_branch = tmp_col_branch->next_col;
    }
    tmp_col_branch->next_col = NULL;
    tmp_col_branch->next_row = NULL;
  }
  else if (c_to_remove == fc)
  {
    cluster *tmp_first = fc;
    cluster *tmp_first_row;
    node_branch *tmp_vert_branch;
    node_branch *tmp_first_col;
    fc = fc->next;
    fc->prev->next = NULL;
    fc->prev = NULL;

    tmp_vert_branch = tmp_first->column;
    while (tmp_vert_branch != NULL)
    {
      tmp_vert_branch->next_row = NULL;
      tmp_vert_branch = tmp_vert_branch->next_col;
    }
    tmp_first_col = fc->column->next_col;

    tmp_first_row = fc;
    while (tmp_first_row != NULL)
    {
      tmp_first_row->column = tmp_first_row->column->next_col;
      tmp_first_row->row = tmp_first_col;

      tmp_first_col = tmp_first_col->next_col;
      tmp_first_row = tmp_first_row->next;
    }
    tmp_first = NULL;
    return;
  }
  else
  {
    cluster *prev_node = c_to_remove->prev;
    cluster *next_node = c_to_remove->next;
    c_to_remove->prev->next = c_to_remove->next;
    c_to_remove->next->prev = c_to_remove->prev;
    node_branch *tmp_col_prev = prev_node->column;
    node_branch *tmp_col_next = next_node->column;

    node_branch *tmp_row_prev = prev_node->row;
    node_branch *tmp_row_next = next_node->row;

    while (tmp_col_prev != NULL)
    {
      tmp_col_prev->next_row = tmp_col_next;
      tmp_col_prev = tmp_col_prev->next_col;
      tmp_col_next = tmp_col_next->next_col;
    }

    while (tmp_row_prev != NULL)
    {
      tmp_row_prev->next_col = tmp_row_next;
      tmp_row_prev = tmp_row_prev->next_row;
      tmp_row_next = tmp_row_next->next_row;
    }
  }
}



vector<double> run_formula(cluster *c1, cluster *c2, vector<double> c1_vals, vector<double> v2_vals)
{
  vector<double> res_vec;
  double num = 0.0;
  long double denom = 0.0;

  node_branch *first_branch = c1->column;
  node_branch *second_branch = c2->column;
  while (first_branch != NULL)
  {
    if ((first_branch->distance != GLOBAL_MIN_DISTANCE && first_branch->distance != 0) && (second_branch->distance != GLOBAL_MIN_DISTANCE && second_branch->distance != 0))
    {
      num = (c1->num_of_nodes * first_branch->distance) + (c2->num_of_nodes * second_branch->distance);
      denom = (c1->num_of_nodes + c2->num_of_nodes);
      res_vec.push_back(num / denom);
    }
    first_branch = first_branch->next_col;
    second_branch = second_branch->next_col;
  }

  return res_vec;
}