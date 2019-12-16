#include "Cluster.h"
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

double MIN_DISTANCE = 0.0;

void clusters::insert(const std::string &label)
{
    // Initialize ClusterNode with name and the number of clusters inside
    cluster *node_to_insert = new cluster;
    node_to_insert->label = label;
    node_to_insert->noc = 1; // Used to keep track of how many clusters have been combined into one ClusterNode
        
    if (this->f != NULL)
    {
        // Reattach pointers of the added ClusterNode and set tail to newly created ClusterNode
        node_to_insert->p = this->l;
        this->l->n = node_to_insert;
        this->l = node_to_insert;
        // Ensure tail->next is set to NULL
        this->l->n = NULL;

        // Initialize first DistanceNodes
        cluster_distance *f_col = new cluster_distance;
        cluster_distance *f_row = new cluster_distance;
        f_row->dist = f_col->dist = 0.0;

        // Ensure pointers are set to NULL to prevent pointing to wrong locations
        f_row->nc = f_col->nc = NULL;
        f_row->nr = f_col->nr = NULL;

        this->l->col = f_col;
        this->l->row = f_row;

        // Attach first DistanceNodes to first column and row of newly added ClusterNode
        cluster_distance *cur_col = f_col;
        cluster_distance *cur_row = f_row;

        cluster_distance *prev_col = this->l->p->col;
        cluster_distance *prev_row = this->l->p->row;

        prev_col->nr = cur_col;
        prev_row->nc = cur_row;

        // Go through each DistanceNode and attach pointers like a singly-linked list
        while (prev_col != prev_row)
        {
            // Initialize DistanceNodes for use
            cluster_distance *new_col = new cluster_distance;
            cluster_distance *new_row = new cluster_distance;
            new_col->dist = new_row->dist = 0.0;

            // Ensure pointers are set to NULL to prevent pointing to wrong locations
            new_row->nc = new_col->nc = NULL;
            new_row->nr = new_col->nr = NULL;
            cur_col = cur_col->nc = new_col;
            cur_row = cur_row->nr = new_row;

            prev_col = prev_col->nc;
            prev_row = prev_row->nr;

            prev_col->nr = cur_col;
            prev_row->nc = cur_row;
        }
        // Initialize and attach the last DistanceNode in newly added ClusterNode
        cluster_distance *last_node = new cluster_distance;
        last_node->dist = 0.0;
        cur_col->nc = cur_row->nr = last_node;
    }
    else
    {
        cluster_distance *f_distance = new cluster_distance;
        f_distance->dist = 0.0;
        node_to_insert->col = node_to_insert->row = f_distance;
        this->f = this->l = node_to_insert;
    }
}
void clusters::remove(cluster *node_to_remove)
{
    // If there is only one ClusterNode left in the list, delete the only node and set pointers to NULL for addCluster to function correctly
    if (node_to_remove == this->f && node_to_remove == this->l)
    {
        cluster *tempNode = this->f;

        tempNode->n = NULL;
        tempNode->p = NULL;

        this->f = NULL;
        this->l = NULL;
        delete tempNode;
        return;
    }
    if (node_to_remove == this->f)
    {
        // Steps:
        // reassign head to head->next
        // go down ->nextInColumn until NULL, then go down ->nextInRow until NULL and remove pointers

        cluster *tempHead = this->f;
        cluster *tempHeadRow;
        cluster_distance *tempVerticalDistance;
        cluster_distance *tempHeadCol;
        this->f = this->f->n;
        this->f->p->n = NULL;
        this->f->p = NULL;

        for (tempVerticalDistance = tempHead->col; tempVerticalDistance != NULL; tempVerticalDistance = tempVerticalDistance->nc)
        {
            tempVerticalDistance->nr = NULL;
        }

        tempHeadCol = this->f->col->nc;

        for (tempHeadRow = this->f; tempHeadRow != NULL; tempHeadRow = tempHeadRow->n)
        {
            tempHeadRow->col = tempHeadRow->col->nc;
            tempHeadRow->row = tempHeadCol;

            tempHeadCol = tempHeadCol->nc;
        }
        tempHead = NULL;
        return;
    }
    else if (node_to_remove == this->l)
    {
        // Steps:
        // go down ->column->nextInColumn until NULL and remove pointers; also set pointers pointing to tail list to NULL
        // go down ->row->nextInRow until NULL and remove pointers; also set pointers pointing to tail list NULL;

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
    }
    else
    {
        // Steps:
        // reattach pointers to cluster node
        // Go down nextInRow and nextInColumn until pointers are equal and remove + reattach pointers
        // go to ->prev and ->next cluster node and traverse down list
        cluster *prevNode = node_to_remove->p;
        cluster *nextNode = node_to_remove->n;

        node_to_remove->p->n = node_to_remove->n;
        node_to_remove->n->p = node_to_remove->p;

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
    }
}

void clusters::find_min_distance(cluster *&n1, cluster *&n2)
{
    // Create temporary Cluster and Distance Nodes
    cluster *curr = NULL;
    cluster_distance *tempStart = NULL;

    cluster *secondCurr = NULL;

    cluster *minClusterNode = NULL;
    cluster_distance *minDistanceNode = NULL;
    // Set minDistance to max Double value
    double minDistance = std::numeric_limits<double>::max();

    // Go through each DistanceNode and check for minimum value
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
    // set corresponding ClusterNode of minimum DistanceNode to given ClusterNode C
    n1 = minClusterNode;
    // Go through each DistanceNode and find matching minimum value
    for (secondCurr = minClusterNode->n; secondCurr != NULL; secondCurr = secondCurr->n)
    {
        for (tempStart = secondCurr->col; tempStart != NULL; tempStart = tempStart->nc)
        {
            if (tempStart->dist == minDistanceNode->dist)
            {
                // Set minimum distance value to global variable
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
    for (unsigned int i = 1; i < distances.size(); i++)
    {
        if (distances[min] > distances[i])
        {
            min = i;
        }
    }
    return min;
}

std::vector<double> run_formula(cluster *n1, cluster *n2, vector<double> first_vals, vector<double> second_vals)
// Uses given formula to calculate values to be put into each DistanceNode of added ClusterNode
{
    // Initialize and set variables
    vector<double> result;
    cluster_distance *tempOne;
    cluster_distance *tempTwo;
    int numClusterOne = n1->noc;
    int numClusterTwo = n2->noc;
    double numerator = 0.0;
    double denominator = 0.0;

    // Loop through each DistanceNode
    for (tempOne = n1->col, tempTwo = n2->col; tempOne != NULL; tempOne = tempOne->nc, tempTwo = tempTwo->nc)
    {
        // Only compute values that are not the minimum distance or zero
        if ((tempOne->dist != MIN_DISTANCE && tempOne->dist != 0) && (tempTwo->dist != MIN_DISTANCE && tempTwo->dist != 0))
        {
            // Compute numerator and denominator of formula
            numerator = (numClusterOne * tempOne->dist) + (numClusterTwo * tempTwo->dist);
            denominator = numClusterOne + numClusterTwo;
            // Push computed value into vector to be returned
            result.push_back(numerator / denominator);
        }
    }

    return result;
}

void clusters::run_upgma()
{
    // Create temporary Cluster and Distance Nodes
    // node *tempHead = this->f;

    cluster *clusterOne = NULL;
    cluster *clusterTwo = NULL;

    cluster_distance *distanceOne;
    cluster_distance *distanceTwo;
    // Create vectors to hold distances of DistanceNodes
    std::vector<double> clusterOneDistances;
    std::vector<double> clusterTwoDistances;
    std::vector<double> resultantDistances;

    // Call findMinimum function to locate two ClusterNodes containing the minimum distance in DynMatrix
    // clusterOne and clusterTwo are the ClusterNodes containing the minimum distance
    find_min_distance(clusterOne, clusterTwo);

    // Store the distances in the two ClusterNodes' clusterOne and clusterTwo in vectors
    for (distanceOne = clusterOne->col; distanceOne != NULL; distanceOne = distanceOne->nc)
    {
        clusterOneDistances.push_back(distanceOne->dist);
    }
    for (distanceTwo = clusterTwo->col; distanceTwo != NULL; distanceTwo = distanceTwo->nc)
    {
        clusterTwoDistances.push_back(distanceTwo->dist);
    }

    // Use useFormula function to compute average distances and store inside resultant vector
    resultantDistances = run_formula(clusterOne, clusterTwo, clusterOneDistances, clusterTwoDistances);
    // cout << "clusterOneDistances\n";
    // for (auto it : clusterOneDistances)
    // {
    //   cout << it << " ";
    // }
    // cout << "\n";
    // cout << "clusterTwoDistances\n";
    // for (auto it : clusterTwoDistances)
    // {
    //   cout << it << " ";
    // }
    // cout << "\n";
    int min = find_min_ele(clusterOneDistances);
    // Call combineCluster function to remove the two ClusterNodes and add the new ClusterNode into the DynMatrix
    merge(clusterOne, clusterTwo, resultantDistances, clusterOneDistances[min]);
}

void clusters::merge(cluster *&n1, cluster *&n2, std::vector<double> values, double val)
{

    // Set variables to make new ClusterNode name
    string leftparen = "(";
    string comma = ", ";
    string rightparen = ")";
    string doubleDot = ":";
    // Assign values of vector parameter to new vector
    vector<double> upgmaValues = values;

    stringstream namess;
    namess << leftparen << n1->label << doubleDot << val / 2 << comma << n2->label << doubleDot << val / 2 << rightparen;
    // Construct new ClusterNode name
    string name = namess.str();
    cluster_distance *firstDNCol;
    cluster_distance *firstDNRow;
    cluster *tempAddedClusterNode = NULL;
    int i = 0; // initialize vector index
    // Remove the two ClusterNodes containing the minimum distance
    remove(n1);
    remove(n2);

    // Add a new cluster to the matrix, with 0.0 distance values for rows and columns.
    insert(name);
    // Update numClusters of newly added ClusterNode to keep track of how many ClusterNodes are in the newly added one
    tempAddedClusterNode = this->l;
    this->cnt = n1->noc + n2->noc;

    // Fill distance values of DistanceNodes in newly added ClusterNode with values from given vector
    for (firstDNCol = tempAddedClusterNode->col, firstDNRow = tempAddedClusterNode->row; firstDNCol != firstDNRow; firstDNCol = firstDNCol->nc, firstDNRow = firstDNRow->nr)
    {
        firstDNCol->dist = upgmaValues[i];
        firstDNRow->dist = upgmaValues[i];
        i++;
    }
    // Ensure pointers are NULL to prevent accessing wrongly linked locations
    firstDNCol->nc = firstDNRow->nr = NULL;
    firstDNCol->nr = firstDNRow->nc = NULL;
}
