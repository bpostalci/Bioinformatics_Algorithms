#include "IOHelper.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>

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

	string line;
	while (getline(file, line))
	{
		if (!line.empty())
		{
			seq s;
			s.title = line;
			getline(file, line);
			s.seq = line;
			seqs.push_back(s);
		}
	}

	file.close();
}

void fill_sequence_buff(string &seq, string &title, const string &filename)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ifstream file;
	file.open(filename);

	if (!file.is_open())
	{
		cout << filename << " file cannot be opened...\n";
		exit(1);
	}

	getline(file, title);

	stringstream ss;
	while (getline(file, seq))
	{
		ss << seq;
	}

	seq = string(ss.str());

	file.close();
}

void fill_profile_buff(vector<string> &seqs, vector<string> &seqs_titles, const string &filename)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ifstream file;
	file.open(filename);

	if (!file.is_open())
	{
		cout << filename << " file cannot be opened...\n";
		exit(1);
	}

	string line;
	while (getline(file, line))
	{
		istringstream iss(line);
		vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
		seqs_titles.push_back(tokens[0]);
		seqs.push_back(tokens[1]);
	}

	file.close();
}

void write_alignment(const string &aln, const string &output_file)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	ofstream out;
	out.open(output_file);
	if (!out.is_open())
	{
		cout << output_file << " file cannot be opened...\n";
		exit(1);
	}

	out << aln;

	out.close();
}