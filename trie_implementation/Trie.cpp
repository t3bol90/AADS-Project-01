#include "Trie.h"

// STOLEN - REIMPLEMENTATION REQUIRED
template <class T> void remove_duplicates(vector<T>& v)
{
    auto itr = v.begin();
    std::unordered_set<T> s;
    for (auto curr = v.begin(); curr != v.end(); ++curr) {
        if (s.insert(*curr).second)
            *itr++ = *curr;
    }
    v.erase(itr, v.end());
}

void Trie::_search(vector<char> letters, node* root, string temp, vector<string>& results)
{
    if (letters.empty())
        return;

    vector<char> letters_to_browse = letters;
    remove_duplicates(letters_to_browse);

    for (char c : letters_to_browse)
    {
        size_t probe_i = -1;
        for (size_t i = 0; i < root->children.size(); ++i)
        {
            if (root->children[i]->key == c)
                probe_i = i;
        }

        // not found
        if (probe_i == -1)
            continue;

        temp += root->children[probe_i]->key;
        if (root->children[probe_i]->isWord) results.push_back(temp);

        vector<char> letters_copy = letters;
        letters_copy.erase(find(letters_copy.begin(), letters_copy.end(), c));

        _search(letters_copy, root->children[probe_i], temp, results);
        temp.pop_back();
    }
}

Trie::Trie(string filepath)
{
    fstream dictfile(filepath, fstream::in);
    if (!dictfile.is_open())
        exit(-1);

    string line;
    while (!dictfile.eof())
    {
        line.clear();
        getline(dictfile, line);
        if (!line.empty() && line.find_first_not_of(' ') != string::npos)
            insert(line);
    }

    dictfile.close();
}

void Trie::insert(string word)
{
    node* traverse = root;
    for (size_t wi = 0; wi < word.size(); ++wi)
    {
        bool c_isEndofWord = (wi == word.size() - 1);
        
        bool node_exists = false;
        
        for (size_t i = 0; i < traverse->children.size(); ++i)
        {
            if (traverse->children[i]->key == word[wi])
            {
                traverse->children[i]->isWord |= c_isEndofWord;
                traverse = traverse->children[i];
                node_exists = true;
                break;
            }
        }

        if (!node_exists)
        {
            traverse->children.push_back(new node {word[wi], c_isEndofWord});
            traverse = traverse->children[traverse->children.size() - 1];
        }
    }
}

vector<string> Trie::search(const vector<char>& letters)
{
    string temp;
    vector<string> results;
    
    _search(letters, root, temp, results);

    return results;
}
