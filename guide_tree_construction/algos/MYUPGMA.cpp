#include "MYUPGMA.h"
#include "../data_structures/MyCluster.h"
#include "../helpers/IOHelper.h"
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <limits>

#define REP(i, start, end) for (u32 i = start; i < end; i++)

using namespace std;

u32 calc_num_of_nodes(const string &cluster)
{
	u32 result = 1;
  u32 cluster_size = cluster.size();
  REP(i, 0, cluster_size)
	{
		if (cluster[i] == ',')
			result++;
	}
	return result;
}

void run_algorithm(unordered_map<string, vector<neighbor>> &al)
{
	// find min distance
	string min_cluster_name;
	u32 min_neighbor_index = 0;
	double min_distance = numeric_limits<double>::max();
	for (const auto &node : al)
	{
		REP(i, 0, node.second.size())
		{
			if (node.second[i].distance < min_distance)
			{
				min_distance = node.second[i].distance;
				min_cluster_name = node.first;
				min_neighbor_index = i;
			}
		}
	}

	string leftp = "(";
	string comma = ", ";
	string rightp = ")";
	string doubledot = ":";

	// calculate new name
	stringstream new_namess;
	double weight = min_distance / 2;
	string min_neighbor_name = al[min_cluster_name][min_neighbor_index].name;
	new_namess << leftp << min_cluster_name << doubledot << weight << comma << min_neighbor_name << doubledot << weight << rightp;

	// run upgma formula
	unordered_map<string, double> common_neighbor_vals;
	u32 c1_num_of_nodes = calc_num_of_nodes(min_cluster_name);
	for (const auto &neighbor : al[min_cluster_name])
	{
		if (neighbor.name != min_neighbor_name)
		{
			double val = 0.0;
			val += neighbor.distance * c1_num_of_nodes;
			common_neighbor_vals[neighbor.name] = val;
		}
	}

	u32 c2_num_of_nodes = calc_num_of_nodes(min_neighbor_name);
	for (const auto &neighbor : al[min_neighbor_name])
	{
		if (common_neighbor_vals.find(neighbor.name) != common_neighbor_vals.end())
		{
			double val = common_neighbor_vals[neighbor.name];
			val += neighbor.distance * c2_num_of_nodes;
			common_neighbor_vals[neighbor.name] = val;
		}
	}

	vector<neighbor> new_neighbors;
	for (auto &it : common_neighbor_vals)
	{
		it.second = it.second / (c1_num_of_nodes + c2_num_of_nodes);
		new_neighbors.push_back(neighbor(it.first, it.second));
	}

	string new_name = new_namess.str();
	al[new_name] = new_neighbors;

	al.erase(min_cluster_name);
	al.erase(min_neighbor_name);

	// remove erased clusters from other clusters
	for (const auto &node : al)
	{
		vector<u32> indexes_to_remove;
		vector<neighbor> neighbors = node.second;
		REP(i, 0, neighbors.size())
		{
			if (neighbors[i].name == min_cluster_name || neighbors[i].name == min_neighbor_name)
			{
				indexes_to_remove.push_back(i);
			}
		}

		while (!indexes_to_remove.empty())
		{
			u32 index = indexes_to_remove.back();
			neighbors.erase(neighbors.begin() + index);
			indexes_to_remove.pop_back();
		}
		al[node.first] = neighbors;
	}

	// add new cluster to other clusters as neighbor
	for (auto &node : al)
	{
		if (node.first != new_name)
		{
			// find distance to new cluster
			double distance = 0.0;
			for (const auto &neighbor : al[new_name])
			{
				if (neighbor.name == node.first)
				{
					distance = neighbor.distance;
				}
			}
			node.second.push_back(neighbor(new_name, distance));
		}
	}
}

void build_UPGMA(double **dm, u32 size, const vector<seq> &seqs, const string &outfile)
{
	unordered_map<string, vector<neighbor>> adjacency_list;

	// populate adjacency list
	REP(i, 0, size)
	{
		string title = seqs[i].title.substr(1, seqs[i].title.size());
		vector<neighbor> neighbors;

		REP(j, 0, size)
		{
			if (i != j)
			{
				string neighbor_title = seqs[j].title.substr(1, seqs[j].title.size());
				neighbors.push_back(neighbor(neighbor_title, dm[i][j]));
			}
		}
		adjacency_list[title] = neighbors;
	}

	/*for (auto it : adjacency_list)
	{
		cout << it.first << " => ";
		for (auto itt : it.second)
		{
			cout << itt.name << "=" << itt.distance << " ";
		}
		cout << "\n";
	}*/
	while (adjacency_list.size() > 1)
	{
		run_algorithm(adjacency_list);
	}

	for (const auto &node : adjacency_list)
	{
		write_tree(node.first + ";", outfile);
	}
}
