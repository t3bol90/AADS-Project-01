#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Trie
{
    private:
        struct node
        {
            char key = 0;
            bool isWord = false;
            vector<node*> children;
        };
        node* root = new node;
        void _search(vector<char> letters, node* root, string temp, vector<string>& results);

    public:
        Trie(string filepath);      // build from dict file
        void insert(string word);
        vector<string> search(const vector<char>& letters);
};
