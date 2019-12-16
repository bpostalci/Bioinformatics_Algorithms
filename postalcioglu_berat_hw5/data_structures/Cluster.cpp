#include "Cluster.h"
#include <sstream>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

static double GLOBAL_MIN_DIST = 0.0;

void clusters::find_min_distance(cluster *&c1, cluster *&c2)
{
    double max_dist = numeric_limits<double>::max();

    cluster *cur = NULL;
    cluster *other = NULL;
    cluster *min_cluster = NULL;

    cluster_distance *first_dist = NULL;
    cluster_distance *min_distance = NULL;

    cur = this->f;
    while (cur != NULL)
    {
        first_dist = cur->col;
        while (first_dist != NULL)
        {
            if (first_dist->dist < max_dist && first_dist->dist != 0)
            {
                max_dist = first_dist->dist;
                min_cluster = cur;
                min_distance = first_dist;
            }
            first_dist = first_dist->nc;
        }
        cur = cur->n;
    }

    c1 = min_cluster;
    other = min_cluster->n;
    while (other != NULL)
    {
        first_dist = other->col;
        while (first_dist != NULL)
        {
            if (first_dist->dist == min_distance->dist)
            {
                GLOBAL_MIN_DIST = min_distance->dist;
                c2 = other;
                return;
            }
            first_dist = first_dist->nc;
        }
        other = other->n;
    }
}

bool clusters::remove(cluster *cluster_to_remove)
{
    if (cluster_to_remove == this->f && cluster_to_remove == this->l)
    {
        cluster *tmp_cluster = this->f;
        tmp_cluster->p = tmp_cluster->n = NULL;
        this->f = this->l = NULL;
        delete tmp_cluster;

        return true;
    }
    if (cluster_to_remove == this->f)
    {
        cluster_distance *first_col;
        cluster_distance *first_col_dist;
        cluster *tmp_first = this->f;
        cluster *first_neighbors;

        this->f = this->f->n;
        this->f->p = this->f->p->n = NULL;

        first_col_dist = tmp_first->col;
        while (first_col_dist != NULL)
        {
            first_col_dist->nr = NULL;
            first_col_dist = first_col_dist->nc;
        }
        first_col = this->f->col->nc;

        first_neighbors = this->f;
        while (first_neighbors != NULL)
        {
            first_neighbors->col = first_neighbors->col->nc;
            first_neighbors->row = first_col;
            first_col = first_col->nc;
            first_neighbors = first_neighbors->n;
        }
        tmp_first = NULL;

        return true;
    }
    else if (cluster_to_remove == this->l)
    {
        this->l = this->l->p;
        this->l->n = NULL;
        cluster_distance *row_dist;
        cluster_distance *col_dist;

        row_dist = this->l->row;
        col_dist = this->l->col;
        while (row_dist != col_dist)
        {
            row_dist->nc = col_dist->nr = NULL;
            row_dist = row_dist->nr;
            col_dist = col_dist->nc;
        }
        col_dist->nc = col_dist->nr = NULL;

        return true;
    }
    else
    {
        cluster *prev_cluster = cluster_to_remove->p;
        cluster *next_cluster = cluster_to_remove->n;

        cluster_to_remove->p->n = cluster_to_remove->n;
        cluster_to_remove->n->p = cluster_to_remove->p;

        cluster_distance *row_prev = prev_cluster->row;
        cluster_distance *row_next = next_cluster->row;
        cluster_distance *col_prev = prev_cluster->col;
        cluster_distance *col_next = next_cluster->col;

        while (col_prev != NULL)
        {
            col_prev->nr = col_next;
            col_prev = col_prev->nc;
            col_next = col_next->nc;
        }

        while(row_prev != NULL)
        {
            row_next->nc = row_next;
            row_prev = row_next->nr;
            row_next = row_next->nr;
        }

        return true;
    }

    return false;
}

void clusters::insert(const std::string &label)
{
    cluster *cluster_to_insert = new cluster;
    ++cluster_to_insert->cnt;
    cluster_to_insert->label = label;

    if (this->f != NULL)
    {
        cluster_to_insert->p = this->l;
        this->l->n = cluster_to_insert;
        this->l = cluster_to_insert;
        this->l->n = NULL;

        cluster_distance *f_col = new cluster_distance;
        cluster_distance *f_row = new cluster_distance;
        f_row->dist = f_col->dist = 0.0;

        f_row->nc = f_col->nc = NULL;
        f_row->nr = f_col->nr = NULL;

        this->l->col = f_col;
        this->l->row = f_row;

        cluster_distance *cur_col = f_col;
        cluster_distance *cur_row = f_row;

        cluster_distance *prev_col = this->l->p->col;
        cluster_distance *prev_row = this->l->p->row;

        prev_col->nr = cur_col;
        prev_row->nc = cur_row;

        while (prev_col != prev_row)
        {
            cluster_distance *new_col = new cluster_distance;
            cluster_distance *new_row = new cluster_distance;
            new_col->dist = new_row->dist = 0.0;

            new_row->nc = new_col->nc = NULL;
            new_row->nr = new_col->nr = NULL;
            cur_col = cur_col->nc = new_col;
            cur_row = cur_row->nr = new_row;

            prev_col = prev_col->nc;
            prev_row = prev_row->nr;

            prev_col->nr = cur_col;
            prev_row->nc = cur_row;
        }
        cluster_distance *last_node = new cluster_distance;
        last_node->dist = 0.0;
        cur_col->nc = cur_row->nr = last_node;
    }
    else
    {
        cluster_distance *f_distance = new cluster_distance;
        f_distance->dist = 0.0;
        cluster_to_insert->col = cluster_to_insert->row = f_distance;
        this->f = this->l = cluster_to_insert;
    }
}

int find_min_ele(std::vector<double> &distances)
{
    // first remove zeroes
    for (auto it = distances.begin(); it != distances.end(); ++it)
    {
        if (*it == 0)
        {
            distances.erase(it);
        }
    }

    int min = 0;
    for (u32 i = 1; i < distances.size(); i++)
    {
        if (distances[min] > distances[i])
        {
            min = i;
        }
    }
    return min;
}

std::vector<double> run_formula(cluster *n1, cluster *n2, vector<double> first_vals, vector<double> second_vals)
{
    vector<double> result;
    cluster_distance *tempOne;
    cluster_distance *tempTwo;
    int numClusterOne = n1->cnt;
    int numClusterTwo = n2->cnt;
    double numerator = 0.0;
    double denominator = 0.0;

    for (tempOne = n1->col, tempTwo = n2->col; tempOne != NULL; tempOne = tempOne->nc, tempTwo = tempTwo->nc)
    {
        if ((tempOne->dist != GLOBAL_MIN_DIST && tempOne->dist != 0) && (tempTwo->dist != GLOBAL_MIN_DIST && tempTwo->dist != 0))
        {
            numerator = (numClusterOne * tempOne->dist) + (numClusterTwo * tempTwo->dist);
            denominator = numClusterOne + numClusterTwo;
            result.push_back(numerator / denominator);
        }
    }

    return result;
}

void clusters::run_upgma()
{
    cluster *clusterOne = NULL;
    cluster *clusterTwo = NULL;

    cluster_distance *distanceOne;
    cluster_distance *distanceTwo;
    std::vector<double> clusterOneDistances;
    std::vector<double> clusterTwoDistances;
    std::vector<double> resultantDistances;

    find_min_distance(clusterOne, clusterTwo);

    for (distanceOne = clusterOne->col; distanceOne != NULL; distanceOne = distanceOne->nc)
    {
        clusterOneDistances.push_back(distanceOne->dist);
    }
    for (distanceTwo = clusterTwo->col; distanceTwo != NULL; distanceTwo = distanceTwo->nc)
    {
        clusterTwoDistances.push_back(distanceTwo->dist);
    }

    resultantDistances = run_formula(clusterOne, clusterTwo, clusterOneDistances, clusterTwoDistances);
    int min = find_min_ele(clusterOneDistances);
    merge(clusterOne, clusterTwo, resultantDistances, clusterOneDistances[min]);
}

void clusters::merge(cluster *&n1, cluster *&n2, std::vector<double> values, double val)
{
    string leftparen = "(";
    string comma = ", ";
    string rightparen = ")";
    string doubleDot = ":";
    vector<double> upgmaValues = values;

    stringstream namess;
    namess << leftparen << n1->label << doubleDot << val / 2 << comma << n2->label << doubleDot << val / 2 << rightparen;
    string name = namess.str();
    cluster_distance *firstDNCol;
    cluster_distance *firstDNRow;
    cluster *tempAddedClusterNode = NULL;
    int i = 0;
    remove(n1);
    remove(n2);

    insert(name);
    tempAddedClusterNode = this->l;
    this->cnt = n1->cnt + n2->cnt;

    for (firstDNCol = tempAddedClusterNode->col, firstDNRow = tempAddedClusterNode->row; firstDNCol != firstDNRow; firstDNCol = firstDNCol->nc, firstDNRow = firstDNRow->nr)
    {
        firstDNCol->dist = upgmaValues[i];
        firstDNRow->dist = upgmaValues[i];
        i++;
    }
    firstDNCol->nc = firstDNRow->nr = NULL;
    firstDNCol->nr = firstDNRow->nc = NULL;
}
