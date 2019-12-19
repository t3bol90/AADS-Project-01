//
// Created by t3bol90 on 19/12/2019.
//

#ifndef PROJECT01_HASHTABLE_V1_UNITY_H
#define PROJECT01_HASHTABLE_V1_UNITY_H

#include "LookupTable.h"

class Unity {
public:
    void load_dict(LookupTable &lk, string path);
};

void Unity::load_dict(LookupTable &lk, string path) {
    fstream fin(path.c_str(),ios_base::in);
    if (!fin.is_open())
        abort();
    while (!fin.eof())
    {
        string tmp;
        fin >> tmp;
        lk.insert(tmp);
    }
    fin.close();
}


#endif //PROJECT01_HASHTABLE_V1_UNITY_H
