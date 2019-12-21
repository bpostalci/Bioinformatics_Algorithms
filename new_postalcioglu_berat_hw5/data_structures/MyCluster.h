#pragma once

#include <vector>
#include <string>
#include "Typedefs.h"

struct cluster
{
public:
	std::string name;
	u32 num_of_nodes;
	cluster() : num_of_nodes(0) {}
	cluster(std::string _name, u32 _num_of_nodes) : name(_name), num_of_nodes(_num_of_nodes) {}
};

struct neighbor
{
public:
	std::string name;
	double distance;
	neighbor() : distance(0.0) {}
	neighbor(std::string _name, double _distance) : name(_name), distance(_distance) {}
};

struct cluster_compare
{
	bool operator() (const cluster& lhs, const cluster& rhs) const
	{
		return lhs.name < rhs.name;
	}
};