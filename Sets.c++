/* Unit-III Sets: Sets, Multisets, Maps, Hash Tables, Dictionaries. */

#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

/////////////////////////////
// SET (unique sorted elements)
/////////////////////////////
void demo_set() {
    set<int> s;
    s.insert(10);
    s.insert(5);
    s.insert(10); // Duplicate
    cout << "Set contents: ";
    for (int x : s)
        cout << x << " ";
    cout << endl;
}

/////////////////////////////
// MULTISET (allows duplicates)
/////////////////////////////
void demo_multiset() {
    multiset<int> ms;
    ms.insert(10);
    ms.insert(5);
    ms.insert(10); // Allowed
    cout << "Multiset contents: ";
    for (int x : ms)
        cout << x << " ";
    cout << endl;
}

/////////////////////////////
// MAP (unique key, sorted)
/////////////////////////////
void demo_map() {
    map<string, int> m;
    m["apple"] = 2;
    m["banana"] = 3;
    m["apple"] = 4; // Overwrites

    cout << "Map contents:\n";
    for (auto& p : m)
        cout << p.first << ": " << p.second << endl;
}

/////////////////////////////
// MULTIMAP (allows duplicate keys)
/////////////////////////////
void demo_multimap() {
    multimap<string, int> mm;
    mm.insert({"apple", 2});
    mm.insert({"banana", 3});
    mm.insert({"apple", 5});

    cout << "Multimap contents:\n";
    for (auto& p : mm)
        cout << p.first << ": " << p.second << endl;
}

/////////////////////////////
// UNORDERED MAP (Hash Table)
/////////////////////////////
void demo_unordered_map() {
    unordered_map<string, int> um;
    um["red"] = 1;
    um["green"] = 2;
    um["blue"] = 3;

    cout << "Unordered Map contents:\n";
    for (auto& p : um)
        cout << p.first << ": " << p.second << endl;
}

/////////////////////////////
// Custom Hash Table (Basic)
/////////////////////////////
class HashTable {
    static const int SIZE = 10;
    vector<pair<string, int>> table[SIZE];

    int hash(string key) {
        int h = 0;
        for (char c : key)
            h = (h * 31 + c) % SIZE;
        return h;
    }

public:
    void insert(string key, int value) {
        int i = hash(key);
        for (auto& pair : table[i]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }
        table[i].push_back({key, value});
    }

    int search(string key) {
        int i = hash(key);
        for (auto& pair : table[i]) {
            if (pair.first == key)
                return pair.second;
        }
        return -1; // Not found
    }

    void display() {
        cout << "Custom Hash Table:\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << ": ";
            for (auto& pair : table[i])
                cout << "(" << pair.first << ", " << pair.second << ") ";
            cout << endl;
        }
    }
};

/////////////////////////////
// Dictionary (Map example)
/////////////////////////////
void demo_dictionary() {
    map<string, string> dict;
    dict["dog"] = "a domesticated animal";
    dict["apple"] = "a fruit";

    cout << "Dictionary lookup:\n";
    for (auto& word : dict)
        cout << word.first << ": " << word.second << endl;
}

/////////////////////////////
// MAIN FUNCTION
/////////////////////////////
int main() {
    demo_set();
    demo_multiset();
    demo_map();
    demo_multimap();
    demo_unordered_map();

    HashTable ht;
    ht.insert("cat", 1);
    ht.insert("dog", 2);
    ht.insert("bird", 3);
    ht.display();
    cout << "Search 'dog' => " << ht.search("dog") << endl;

    demo_dictionary();

    return 0;
}
