#pragma once

#include "Typedefs.h"
#include "Seq.h"
#include <unordered_map>
#include <vector>

using namespace std;

struct adj_list
{
private:
    // sequence title to adjacent sequences
    unordered_map<string, vector<seq>> _graph;
public:
    inline unordered_map<string, vector<seq>>& graph() { return _graph; }
};

