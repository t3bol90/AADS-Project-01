//
// Created by t3bol90 on 19/12/2019.
//

#ifndef PROJECT01_HASHTABLE_V1_LOOKUPTABLE_H
#define PROJECT01_HASHTABLE_V1_LOOKUPTABLE_H

#include <bits/stdc++.h>
using namespace std;

class LookupTable {
public:
    static unordered_map<char,int> char_table;
    unordered_map<unsigned long long,vector<string>> dict;
    void insert(string word);
    unsigned long long gethash(string word);
    set<string> lookup(string word);
};


#endif //PROJECT01_HASHTABLE_V1_LOOKUPTABLE_H
