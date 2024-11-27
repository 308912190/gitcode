#include <iostream>
#include <vector>
#include <algorithm>  
using namespace std;

void printvector(vector<int>& v) {
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}

void test01() {
    vector<int> v1;
    for (int i = 0; i < 10; i++) {
        v1.push_back(i);
    }
    printvector(v1);  // print all numbers from 0 to 9
}

int main() {
    test01();
    return 0;
}
