#include "Cluster2.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;

double MIN_DISTANCE = 0.0;
void addCluster(ClusterNode *&head, ClusterNode *&tail, const std::string &name)
{
  ClusterNode *newNode = new ClusterNode;
  newNode->name = name;
  newNode->numClusters = 1; 

  if (head == NULL)
  { 
    DistanceNode *firstDistance = new DistanceNode;
    firstDistance->distance = 0.0;

    head = tail = newNode;
    head->column = head->row = firstDistance;
  }

  else
  {
    newNode->prev = tail;
    tail->next = newNode;
    tail = newNode;
    tail->next = NULL;

    DistanceNode *firstCol = new DistanceNode;
    DistanceNode *firstRow = new DistanceNode;
    firstCol->distance = 0.0;
    firstRow->distance = 0.0;

    firstCol->nextInColumn = NULL;
    firstCol->nextInRow = NULL;

    firstRow->nextInColumn = NULL;
    firstRow->nextInRow = NULL;

    tail->column = firstCol;
    tail->row = firstRow;

    DistanceNode *currCol = tail->column;
    DistanceNode *currRow = tail->row;

    DistanceNode *prevCol = tail->prev->column;
    DistanceNode *prevRow = tail->prev->row;

    prevCol->nextInRow = currCol;
    prevRow->nextInColumn = currRow;

    while (prevCol != prevRow)
    {
      DistanceNode *newCol = new DistanceNode;
      DistanceNode *newRow = new DistanceNode;
      newCol->distance = 0.0;
      newRow->distance = 0.0;

      newCol->nextInColumn = NULL;
      newCol->nextInRow = NULL;

      newRow->nextInColumn = NULL;
      newRow->nextInRow = NULL;

      currCol->nextInColumn = newCol;
      currRow->nextInRow = newRow;

      currCol = currCol->nextInColumn;
      currRow = currRow->nextInRow;

      prevCol = prevCol->nextInColumn;
      prevRow = prevRow->nextInRow;

      prevCol->nextInRow = currCol;
      prevRow->nextInColumn = currRow;
    }
    DistanceNode *edgeNode = new DistanceNode;
    edgeNode->distance = 0.0;
    currCol->nextInColumn = currRow->nextInRow = edgeNode;
  }
}

void removeCluster(ClusterNode *&head, ClusterNode *&tail, ClusterNode *toBeRemoved)
{

  if (toBeRemoved == head && toBeRemoved == tail)
  {
    ClusterNode *tempNode = head;

    tempNode->next = NULL;
    tempNode->prev = NULL;

    head = NULL;
    tail = NULL;
    delete tempNode;
    return;
  }
  if (toBeRemoved == head)
  {
    ClusterNode *tempHead = head;
    ClusterNode *tempHeadRow;
    DistanceNode *tempVerticalDistance;
    DistanceNode *tempHeadCol;
    head = head->next;
    head->prev->next = NULL;
    head->prev = NULL;

    for (tempVerticalDistance = tempHead->column; tempVerticalDistance != NULL; tempVerticalDistance = tempVerticalDistance->nextInColumn)
    {
      tempVerticalDistance->nextInRow = NULL;
    }

    tempHeadCol = head->column->nextInColumn;

    for (tempHeadRow = head; tempHeadRow != NULL; tempHeadRow = tempHeadRow->next)
    {
      tempHeadRow->column = tempHeadRow->column->nextInColumn;
      tempHeadRow->row = tempHeadCol;

      tempHeadCol = tempHeadCol->nextInColumn;
    }
    tempHead = NULL;
    return;
  }
  else if (toBeRemoved == tail)
  {
    tail = tail->prev;
    tail->next = NULL;
    DistanceNode *tempDistanceRow;
    DistanceNode *tempDistanceCol;

    for (tempDistanceRow = tail->row, tempDistanceCol = tail->column; tempDistanceRow != tempDistanceCol; tempDistanceRow = tempDistanceRow->nextInRow, tempDistanceCol = tempDistanceCol->nextInColumn)
    {
      tempDistanceCol->nextInRow = NULL;
      tempDistanceRow->nextInColumn = NULL;
    }
    tempDistanceCol->nextInColumn = tempDistanceCol->nextInRow = NULL;
  }
  else
  {
    ClusterNode *prevNode = toBeRemoved->prev;
    ClusterNode *nextNode = toBeRemoved->next;

    toBeRemoved->prev->next = toBeRemoved->next;
    toBeRemoved->next->prev = toBeRemoved->prev;

    DistanceNode *tempColPrev = prevNode->column;
    DistanceNode *tempColNext = nextNode->column;

    DistanceNode *tempRowPrev = prevNode->row;
    DistanceNode *tempRowNext = nextNode->row;

    for (; tempColPrev != NULL; tempColPrev = tempColPrev->nextInColumn, tempColNext = tempColNext->nextInColumn)
    {
      tempColPrev->nextInRow = tempColNext;
    }

    for (; tempRowPrev != NULL; tempRowPrev = tempRowPrev->nextInRow, tempRowNext = tempRowNext->nextInRow)
    {
      tempRowPrev->nextInColumn = tempRowNext;
    }
  }
}

void findMinimum(ClusterNode *head, ClusterNode *&C, ClusterNode *&D)
{
  ClusterNode *curr = NULL;
  DistanceNode *tempStart = NULL;

  ClusterNode *secondCurr = NULL;

  ClusterNode *minClusterNode = NULL;
  DistanceNode *minDistanceNode = NULL;
  double minDistance = std::numeric_limits<double>::max();

  for (curr = head; curr != NULL; curr = curr->next)
  {
    for (tempStart = curr->column; tempStart != NULL; tempStart = tempStart->nextInColumn)
    {
      if (tempStart->distance < minDistance && tempStart->distance != 0)
      {
        minDistance = tempStart->distance;
        minClusterNode = curr;
        minDistanceNode = tempStart;
      }
    }
  }
  C = minClusterNode;
  for (secondCurr = minClusterNode->next; secondCurr != NULL; secondCurr = secondCurr->next)
  {
    for (tempStart = secondCurr->column; tempStart != NULL; tempStart = tempStart->nextInColumn)
    {
      if (tempStart->distance == minDistanceNode->distance)
      {
        MIN_DISTANCE = minDistanceNode->distance;
        D = secondCurr;
        return;
      }
    }
  }
}

int findMin(std::vector<double> &distances)
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

void UPGMA(ClusterNode *&head, ClusterNode *&tail)
{
  ClusterNode *tempHead = head;

  ClusterNode *clusterOne = NULL;
  ClusterNode *clusterTwo = NULL;

  DistanceNode *distanceOne;
  DistanceNode *distanceTwo;
  std::vector<double> clusterOneDistances;
  std::vector<double> clusterTwoDistances;
  std::vector<double> resultantDistances;

  findMinimum(tempHead, clusterOne, clusterTwo);
  for (distanceOne = clusterOne->column; distanceOne != NULL; distanceOne = distanceOne->nextInColumn)
  {
    clusterOneDistances.push_back(distanceOne->distance);
  }
  for (distanceTwo = clusterTwo->column; distanceTwo != NULL; distanceTwo = distanceTwo->nextInColumn)
  {
    clusterTwoDistances.push_back(distanceTwo->distance);
  }

  resultantDistances = useFormula(clusterOne, clusterTwo, clusterOneDistances, clusterTwoDistances);
  int min = findMin(clusterOneDistances);
  combineCluster(head, tail, clusterOne, clusterTwo, resultantDistances, clusterOneDistances[min]);
}

void combineCluster(ClusterNode *&head, ClusterNode *&tail, ClusterNode *&C, ClusterNode *&D, std::vector<double> values, double val)
{
  std::string leftparen = "(";
  std::string comma = ", ";
  std::string rightparen = ")";
  std::string doubleDot = ":";
  std::vector<double> upgmaValues = values;

  std::stringstream namess;
  namess.setf(ios::fixed);
  namess.precision(3);
  double weight = val / 2;
  namess << leftparen << C->name << doubleDot << weight << comma << D->name << doubleDot << weight << rightparen;
  std::string name = namess.str();
  DistanceNode *firstDNCol;
  DistanceNode *firstDNRow;
  ClusterNode *tempAddedClusterNode = NULL;
  int i = 0; 
  removeCluster(head, tail, C);
  removeCluster(head, tail, D);

  addCluster(head, tail, name);
  tempAddedClusterNode = tail;
  tempAddedClusterNode->numClusters = C->numClusters + D->numClusters;

  for (firstDNCol = tempAddedClusterNode->column, firstDNRow = tempAddedClusterNode->row; firstDNCol != firstDNRow; firstDNCol = firstDNCol->nextInColumn, firstDNRow = firstDNRow->nextInRow)
  {

    firstDNCol->distance = upgmaValues[i];
    firstDNRow->distance = upgmaValues[i];
    i++;
  }
  firstDNCol->nextInColumn = firstDNRow->nextInRow = NULL;
  firstDNCol->nextInRow = firstDNRow->nextInColumn = NULL;
}

std::vector<double> useFormula(ClusterNode *clusterOne, ClusterNode *clusterTwo, std::vector<double> firstValues, std::vector<double> secondValues)
{
  std::vector<double> result;
  DistanceNode *tempOne;
  DistanceNode *tempTwo;
  int numClusterOne = clusterOne->numClusters;
  int numClusterTwo = clusterTwo->numClusters;
  double numerator = 0.0;
  double denominator = 0.0;

  for (tempOne = clusterOne->column, tempTwo = clusterTwo->column; tempOne != NULL; tempOne = tempOne->nextInColumn, tempTwo = tempTwo->nextInColumn)
  {
    if ((tempOne->distance != MIN_DISTANCE && tempOne->distance != 0) && (tempTwo->distance != MIN_DISTANCE && tempTwo->distance != 0))
    {
      numerator = (numClusterOne * tempOne->distance) + (numClusterTwo * tempTwo->distance);
      denominator = numClusterOne + numClusterTwo;
      result.push_back(numerator / denominator);
    }
  }

  return result;
}


