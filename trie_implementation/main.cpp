#include "Trie.h"

// Timing execution
#include <chrono>
using high_resolution_clock = chrono::high_resolution_clock;
using time_point = chrono::time_point<chrono::high_resolution_clock>;
#define ms_cast chrono::duration_cast<chrono::milliseconds>

// Cosmetics / Digits grouping
// http://www.cplusplus.com/reference/locale/numpunct/grouping/
#include <locale>
struct _3digit_grouping : numpunct<char>
{
    string do_grouping() const { return "\03"; }
};

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        cout << "Exactly 3 args required: [dictionary file] [query file] [output file]" << endl;
        return -1;
    }

    fstream file_dict(argv[1], fstream::in);
    fstream file_query(argv[2], fstream::in);
    fstream file_output(argv[3], fstream::out | fstream::trunc);
    if (!file_query.is_open() || !file_output.is_open())
    {
        cout << "Unable to open input or output file." << endl;
        return -1;
    }

    time_point start, end;

    static locale l(cout.getloc(), new _3digit_grouping);
    cout.imbue(l);

    string query;
    while (!file_query.eof())
    {
        char c = file_query.get();
        if (c >= 'a' && c <= 'z') query += c;
        else if (c >= 'A' && c <= 'Z') query += tolower(c);
    }
    cout << "Query has " << query.size() << " letters." << endl;

    cout << "Building dictionary...";

    start = high_resolution_clock::now();
    Trie x(file_dict);
    end = high_resolution_clock::now();
    cout << " Done in " << ms_cast(end - start).count() << " ms." << endl;
    

    cout << "Searching dictionary...";
    start = high_resolution_clock::now();
    vector<string> results = x.search(query);
    end = high_resolution_clock::now();
    
    cout << " Found " << results.size() << " result(s) in " << ms_cast(end - start).count() << " ms." << endl;

    for (auto i : results)
        file_output << i << endl;

    return 0;
}
