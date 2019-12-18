#include "IOHelper.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <unordered_set>

using namespace std;

#define IS_LINEBREAK(ch) (ch == '\n' || ch == '\r')
#define OPTIMIZE_IO               \
	ios_base::sync_with_stdio(0); \
	cin.tie(0);

void fill_sequences_buff(vector<seq> &seqs, const string &filename)
{
	OPTIMIZE_IO

	ifstream file;
	file.open(filename);

	if (!file.is_open())
	{
		cout << filename << " file cannot be opened...\n";
		exit(1);
	}

	unordered_set<string> set;
	string line;

	while (getline(file, line))
	{
		if (!line.empty())
		{
			string title = line;
			getline(file, line);
			string seq_str = line;
			if (set.find(title) == set.end() && set.find(seq_str) == set.end())
			{
				seq s;
				s.title = title;
				s.seq = seq_str;
				seqs.push_back(s);
				set.insert(title);
				set.insert(seq_str);
			} 
		}
	}

	file.close();
}

void write_tree(const string &tree, const string &output_file)
{
	OPTIMIZE_IO

	ofstream out;
	out.open(output_file);
	if (!out.is_open())
	{
		cout << output_file << " file cannot be opened...\n";
		exit(1);
	}
	cout << "writing tree to => " << output_file << "\n";
	out << tree;

	out.close();
}
