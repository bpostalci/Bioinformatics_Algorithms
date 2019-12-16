#pragma once
#include <string>
#include <vector>

struct DistanceNode {
  double distance;
  DistanceNode* nextInColumn;
  DistanceNode* nextInRow;
};

struct ClusterNode {
  std::string name;
  int numClusters;
  ClusterNode* prev;
  ClusterNode* next;
  DistanceNode* row;
  DistanceNode* column;
};

void addCluster(ClusterNode *&head,ClusterNode *&tail,const std::string& name);

void removeCluster(ClusterNode *&head,ClusterNode *&tail,ClusterNode *toBeRemoved);

void findMinimum(ClusterNode *head,ClusterNode *&C,ClusterNode *&D);

void UPGMA(ClusterNode *&head, ClusterNode *&tail);

void combineCluster(ClusterNode *&head, ClusterNode *&tail, ClusterNode *&C, ClusterNode *&D, std::vector<double> values, double val);

std::vector<double> useFormula(ClusterNode *clusterOne, ClusterNode *clusterTwo, std::vector<double> firstValues, std::vector<double> secondValues);


