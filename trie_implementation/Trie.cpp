#include "Trie.h"

void Trie::_remove_duplicate_char(string& v)
{
    std::unordered_set<char> s; // every elements in unordered_set is unique; i.e. no duplicates

    for (char c : v)
        s.insert(c);
    
    v.clear();
    for (auto i = s.begin(); i != s.end(); ++i)
        v += *i;
}

void Trie::_search(string letters, node* root, string temp, vector<string>& results)
{
    if (letters.empty())
        return;

    string letters_to_browse = letters;
    _remove_duplicate_char(letters_to_browse);

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

        string letters_copy = letters;
        letters_copy.erase(find(letters_copy.begin(), letters_copy.end(), c));

        _search(letters_copy, root->children[probe_i], temp, results);
        temp.pop_back();
    }
}

Trie::Trie(fstream& file)
{
    string line;
    while (!file.eof())
    {
        line.clear();
        getline(file, line);
        if (!line.empty() && line.find_first_not_of(' ') != string::npos)
            insert(line);
    }
    file.clear();
    file.seekg(0, fstream::beg);
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

vector<string> Trie::search(const string& letters)
{
    string temp;
    vector<string> results;
    
    _search(letters, root, temp, results);

    return results;
}
