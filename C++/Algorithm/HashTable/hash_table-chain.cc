#include <iostream>
#include <vector>
#include <list>
#include <string>

using std::vector;
using std::list;
using std::string;
using std::cout;
using std::endl;

struct dict{                        // self-defined dictionary
    string key;                     //  key  for Name (eg:Jordan)
    string value;                   // value for Team (eg:Bulls)
    bool operator== (const dict& d) const{ return key == d.key; }
    dict():key(""),value(""){};     
    dict(string Key, string Value):key(Key),value(Value){};  
};

class HashChain_std{
private:
    int size,                // size of table
        count;               // count: number of data

    vector<list<dict> > table;            // hash table with linked list

    int PreHashing(string key_str);       // turn string_type_key to int_type_key
    int HashFunction(string key_str);     // using Division method

public:
    HashChain_std(){};                       
    HashChain_std(int m):size(m),count(0){   
        table.resize(size);               // allocate memory for each slot
    }

    void Insert(dict data);               
    void Delete(string key);              
    string Search(string key);            
    void DisplayTable();                  
};

string HashChain_std::Search(string key_str){
    // two steps: 1. get index from hash function
    //            2. traversal in linked list
    int index = HashFunction(key_str);
    for (list<dict>::iterator itr = table[index].begin(); itr != table[index].end(); itr++) {
        if ((*itr).key == key_str) {
            return (*itr).value;
        }
    }
    return "...\nno such data";
}

void HashChain_std::Delete(string key_str){
    // two steps: 1. get index from hash function
    //            2. traversal in linked list
    int index = HashFunction(key_str);
    for (list<dict>::iterator itr = table[index].begin(); itr != table[index].end(); itr++) {
        if ((*itr).key == key_str) {
            table[index].erase(itr); // the iterator will also be eliminated
            break; // so we must break here, or it may be RE
        }
    }
}

void HashChain_std::Insert(dict data){
    // two steps: 1. get index from hash function
    //            2. insert data at the front of linked list
    int index = HashFunction(data.key);
    table[index].push_front(data);  // or push_back(data);           
}

int HashChain_std::PreHashing(string key_str){
    // if   key_str = Jordan, exp = 9
    // then key_int = ASCII(J)*9^5+ASCII(o)*9^4+ASCII(r)*9^3
    //               +ASCII(d)*9^2+ASCII(a)*9^1+ASCII(n)*9^0

    int exp = 9,        // choose randomly 
        key_int = 0,
        p = 1;

    for (int i = (int)key_str.size()-1; i >= 0; i--) {
        key_int += key_str[i]*p;
        p *= exp;
    }
    return key_int;
}

int HashChain_std::HashFunction(string key_str){

    return (PreHashing(key_str) % this->size);     // Division method
}

void HashChain_std::DisplayTable(){

    for (int i = 0; i < table.size(); i++) {
        cout << "slot#" << i << ": ";
        for (list<dict>::iterator itr = table[i].begin(); itr != table[i].end(); itr++) {
            cout << "(" << (*itr).key << "," << (*itr).value << ") ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {

    HashChain_std hash(5);
    hash.Insert(dict("T-Mac","Magic"));
    hash.Insert(dict("Bryant","Lakers"));
    hash.Insert(dict("Webber","Kings"));
    hash.Insert(dict("Arenas", "Wizards"));
    hash.Insert(dict("Davis","Clippers"));
    hash.Insert(dict("Kidd","Nets"));
    hash.DisplayTable();

    cout << "T-Mac is in " << hash.Search("T-Mac") << ". " << endl;
    cout << "Arenas is in " << hash.Search("Arenas") << ". " << endl;

    hash.Delete("Kidd");
    hash.Delete("T-Mac");
    cout << "\nAfter deleing Kidd and T-Mac:\n";
    hash.DisplayTable();

    return 0;
}
