#include "Trie.h"

#include <chrono>
#include <locale>
using namespace std::chrono;

// STOLEN - REIMPLEMENTAION REQUIRED
struct my_numpunct : numpunct<char> {
    string do_grouping() const { return "\03"; }
};

vector<char> tovectorchar(string x)
{
    vector<char> v;
    for (char c : x) v.push_back(c);
    return v;
}


int main()
{
    time_point<high_resolution_clock> start, end;

    // STOLEN - REIMPLEMENTAION REQUIRED
    locale loc(std::cout.getloc(), new my_numpunct);
    cout.imbue(loc);

    cout << "Building dictionary..." << endl;
    start = high_resolution_clock::now();
    Trie x("C:\\Users\\Administrator\\Desktop\\Dic.txt");
    end = high_resolution_clock::now();
    cout << "Dictionary built in " << (end - start).count() << " ns." << endl;

    /*vector<char> query = {'a', 'l', 'g', 'o', 'r', 'i', 's', 'm' };*/
    vector<char> query = tovectorchar("aaaabbbccccddddeeeeffffgggghhhhiiiijjkkkkllllmmmmnnnnooooopppqqrrrrsssssttttuuuuvvvwwwwxxxyyyzzzz");
    // for (char i = 'a'; i <= 'z'; i++) query.push_back(i);
    // for (char i = 1; i <= 11; i++) query.push_back('a');
    cout << "Query has " << query.size() << " letters." << endl;

    cout << "Searching dictionary..." << endl;
    start = high_resolution_clock::now();
    vector<string> results = x.search(query);
    end = high_resolution_clock::now();
    cout << "Found " << results.size() << " result(s) in " << (end - start).count() << " ns." << endl;

    fstream output("C:\\Users\\Administrator\\Desktop\\output.txt", fstream::out | fstream::trunc);
    for (auto i : results)
        output << i << endl;

    return 0;
}

//#include <iostream>
//#include <fstream>
//#include <string>
//using namespace std;
//
//int main()
//{
//    fstream file("C:\\Users\\Administrator\\Desktop\\Dic.txt", fstream::in);
//
//    if (!file.is_open()) exit(-1);
//
//    int sticky_sieve[26]  = {0};
//
//    while (!file.eof())
//    {
//        string line;
//        getline(file, line);
//        int sieve[26] = {0};
//        if (!line.empty() && line.find_first_not_of(' ') != string::npos)
//        {
//            for (char c : line)
//                sieve[c - 'a']++;
//            for (int i = 0; i < 26; i++)
//            {
//                if (sieve[i] > sticky_sieve[i]) sticky_sieve[i] = sieve[i];
//            }
//        }
//    }
//    for (int i = 0; i < 26; i++)
//    {
//        for (int j = 0; j < sticky_sieve[i]; j++)
//        {
//            cout << (char)(i + 'a');
//        }
//    }
//    cout << endl;
//
//    return 0;
//}