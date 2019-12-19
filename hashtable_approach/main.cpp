#include "Unity.h"

int main() {

    LookupTable table;
    Unity uni;
    uni.load_dict(table, "../Dic.txt");
    string input = "abcdefjhijklmnopqrstuvwxyz";
//    cout << "Input string query: ";
//    cin >> input;
    set<string> ans = table.lookup(input);
    cout << ans.size() << "\n";
    for (auto i: ans)
    {
        cout << i << "\n";
    }
    return 0;
}