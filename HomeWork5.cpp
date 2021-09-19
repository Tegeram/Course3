#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <sstream>
#include <boost/algorithm/string.hpp>



using namespace std;

//=====Task 1==========================================================================================================

template <typename T>
void UniqueWord(T from, T to) {
    auto new_last = from;
    for (auto it{ from }; it != to; ++it) {
        if (find(from, new_last, *it) == new_last)
        {
            if (new_last != it) *new_last = *it;
            ++new_last;
            cout << *it << '\n';
        }
    }
}

//=====Task 2==========================================================================================================

void PhraseSort(string str) {
    multimap<int,string> myMap;
    istringstream iss(str);
    string input;
    while (iss) {
        getline(iss, input, '.');
        boost::algorithm::trim(input);        
        myMap.insert(make_pair(input.length(),input));
    }

    for (auto a : myMap) {
        cout << a.second << '\n';
    }
}

//=====================================================================================================================

int main()
{
    cout << "Task 1" << endl;
    list<string> line;
    line.push_back("No");
    line.push_back("will");
    line.push_back("No");
    line.push_back("I");
    line.push_back("will");
    line.push_back("forget");
    line.push_back("never");
    line.push_back("forget");
    UniqueWord(line.begin(), line.end());

    cout << '\n';
    vector<string> tokens{ "duplicates","to","string","remove", "to", "remove", "string","duplicates", "in"};
    UniqueWord(tokens.begin(),tokens.end());

    //=================================================================================================================

    cout << endl << "Task 2" << endl << "Enter text through '.':" << endl;
    string str;
    getline(cin, str);
    PhraseSort(str);
}
