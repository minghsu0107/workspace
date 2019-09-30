#include <bits/stdc++.h>
using namespace std;
struct cmp {
    bool operator() (int a, int b) {
        return a < b;
    }
};

int main() {
    int arr[] = {1, 5, 3, 7, 4, 2, 6, 0, 9, 8};
    int arr2[] = {11, 15, 13, 17, 14, 12, 16, 10, 19, 18};
    vector<int> vec(arr, arr + 10);
    vector<int> vec2(arr2, arr2 + 10);
    vector<int>::iterator it = vec.begin();
    vector<int>::iterator it2 = vec2.begin();
    
    swap(vec[9], vec2[9]);
    iter_swap(it + 2, it2 + 2);
    cout << "vec: " << endl;
    for (auto x: vec) cout << x << " ";
    cout << endl; 
    cout << "vec2: " << endl;
    for (auto x: vec2) cout << x << " ";
    cout << endl;
    
    reverse(arr, arr + 10);
    reverse(vec2.begin(), vec2.end());
    cout << "arr: " << endl;
    for (auto x: arr) cout << x << " ";
    cout << endl;
    cout << "vec2: " << endl;
    for (auto x: vec2) cout << x << " ";
    cout << endl;

    sort(arr, arr + 10, cmp()); 
    cout << "arr: " << endl;
    for (auto x: arr) cout << x << " ";
    cout << endl;
    
    stable_sort(vec2.begin(), vec2.end(), cmp());
    cout << "vec2: " << endl;
    for (auto x: vec2) cout << x << " ";
    cout << endl;
}