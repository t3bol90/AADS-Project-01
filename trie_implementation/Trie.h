#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm> // find()
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

        void _remove_duplicate_char(string& v);
        void _search(string letters, node* root, string temp, vector<string>& results);

    public:
        Trie(fstream& file);
        void insert(string word);
        vector<string> search(const string& letters);
};
