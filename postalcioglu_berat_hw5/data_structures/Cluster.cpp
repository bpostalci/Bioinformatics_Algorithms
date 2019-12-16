#include "Cluster.h"
#include <sstream>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

double MIN_DISTANCE = 0.0;

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

        for (first_neighbors = this->f; first_neighbors != NULL; first_neighbors = first_neighbors->n)
        {
            first_neighbors->col = first_neighbors->col->nc;
            first_neighbors->row = first_col;
            first_col = first_col->nc;
        }
        tmp_first = NULL;

        return true;
    }
    else if (cluster_to_remove == this->l)
    {
        this->l = this->l->p;
        this->l->n = NULL;
        cluster_distance *tempDistanceRow;
        cluster_distance *tempDistanceCol;

        for (tempDistanceRow = this->l->row, tempDistanceCol = this->l->col; tempDistanceRow != tempDistanceCol; tempDistanceRow = tempDistanceRow->nr, tempDistanceCol = tempDistanceCol->nc)
        {
            tempDistanceCol->nr = NULL;
            tempDistanceRow->nc = NULL;
        }
        tempDistanceCol->nc = tempDistanceCol->nr = NULL;

        return true;
    }
    else
    {
        cluster *prevNode = cluster_to_remove->p;
        cluster *nextNode = cluster_to_remove->n;

        cluster_to_remove->p->n = cluster_to_remove->n;
        cluster_to_remove->n->p = cluster_to_remove->p;

        cluster_distance *tempColPrev = prevNode->col;
        cluster_distance *tempColNext = nextNode->col;

        cluster_distance *tempRowPrev = prevNode->row;
        cluster_distance *tempRowNext = nextNode->row;

        for (; tempColPrev != NULL; tempColPrev = tempColPrev->nc, tempColNext = tempColNext->nc)
        {
            tempColPrev->nr = tempColNext;
        }

        for (; tempRowPrev != NULL; tempRowPrev = tempRowPrev->nr, tempRowNext = tempRowNext->nr)
        {
            tempRowPrev->nc = tempRowNext;
        }

        return true;
    }

    return false;
}

void clusters::find_min_distance(cluster *&n1, cluster *&n2)
{
    cluster *curr = NULL;
    cluster_distance *tempStart = NULL;

    cluster *secondCurr = NULL;

    cluster *minClusterNode = NULL;
    cluster_distance *minDistanceNode = NULL;
    double minDistance = std::numeric_limits<double>::max();

    for (curr = this->f; curr != NULL; curr = curr->n)
    {
        for (tempStart = curr->col; tempStart != NULL; tempStart = tempStart->nc)
        {
            if (tempStart->dist < minDistance && tempStart->dist != 0)
            {
                minDistance = tempStart->dist;
                minClusterNode = curr;
                minDistanceNode = tempStart;
            }
        }
    }
    n1 = minClusterNode;
    for (secondCurr = minClusterNode->n; secondCurr != NULL; secondCurr = secondCurr->n)
    {
        for (tempStart = secondCurr->col; tempStart != NULL; tempStart = tempStart->nc)
        {
            if (tempStart->dist == minDistanceNode->dist)
            {
                MIN_DISTANCE = minDistanceNode->dist;
                n2 = secondCurr;
                return;
            }
        }
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
        if ((tempOne->dist != MIN_DISTANCE && tempOne->dist != 0) && (tempTwo->dist != MIN_DISTANCE && tempTwo->dist != 0))
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
