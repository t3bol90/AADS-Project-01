//
// Created by t3bol90 on 19/12/2019.
//

#include "LookupTable.h"

unordered_map<char, int> LookupTable::char_table = {{'a', 2},
                                                    {'b', 3},
                                                    {'c', 5},
                                                    {'d', 7},
                                                    {'e', 11},
                                                    {'f', 13},
                                                    {'g', 17},
                                                    {'h', 19},
                                                    {'i', 23},
                                                    {'j', 29},
                                                    {'k', 31},
                                                    {'l', 37},
                                                    {'m', 41},
                                                    {'n', 43},
                                                    {'o', 47},
                                                    {'p', 53},
                                                    {'q', 59},
                                                    {'r', 61},
                                                    {'s', 67},
                                                    {'t', 71},
                                                    {'u', 73},
                                                    {'v', 79},
                                                    {'w', 83},
                                                    {'x', 89},
                                                    {'y', 97},
                                                    {'z', 101}};

unsigned long long LookupTable::gethash(string &word) {
    int n = word.size();
    unsigned long long h = 1;
    for (int i = 0;i < n;i++)
    {
        h *= LookupTable::char_table[word[i]];
    }
    return h;
}

void LookupTable::insert(string &word)
{

        unsigned long long h = gethash(word);
        if (dict.find(h) == dict.end()) {
            dict[h] = vector<string>();
            dict[h].push_back(word);
        } else {
            dict[h].push_back(word);
        }
}
typedef unsigned long long ll;
set<string> LookupTable::lookup(string &word)
{
    set<string> ans;
    unordered_set<unsigned long long> preset;
    int n = word.size();
    ll maxsize = 1;
    for (int i = 1;i <= n;i++)
    {
        maxsize = maxsize*2;
    }
    for (ll i = 1;i <= maxsize;i++) {
        string query = "";
        int j = 0;
        ll tmp = i;
        while (tmp > 0)
        {
            if (tmp%2 == 1)
                query+=word[j];
            tmp = tmp/2;
            j++;
        }
        ll h = gethash(query);
        if (preset.count(h) || query.size() < 3)
            continue;
        preset.insert(h);
        if (dict.count(h)) {
            for (const auto& str: dict[h]) {
                ans.insert(str);
            }
        }
    }
    return ans;
}


