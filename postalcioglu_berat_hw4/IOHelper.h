/**
 * @description   I/O Helper
 * @author        Berat Postalcioglu - 21401769 
 **/

#pragma once

#include <string>
#include <vector>

using namespace std;

void fill_sequence_buff(string &seq, string &title, const string &filename);
void fill_profile_buff(vector<string> &seqs, const string &filename);