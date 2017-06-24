#include <iostream>
#include <vector>
#include <algorithm>
#include "set.h"

void print(set<int> const& a) {
    for (set<int>::iterator it = a.begin(); it != a.end(); it++) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;
}

void T1() {
    set<int> a;
    for (int i = 0; i < 100; i++) {
        a.insert(i);
    }
    while (!a.empty()) {
        std::cout << *a.begin() << ' ';
        a.erase(a.begin());
    }
    std::cout << std::endl;

}

void T2() {
    set<int> a;

    a.insert(42);
    a.insert(1);
    a.insert(2);
    a.insert(100500);

    print(a);
}

void T3() {
    std::vector<int> v;
    for (int i = 0; i < 100; i++) {
        v.push_back(i);
    }
    std::random_shuffle(v.begin(), v.end());
    for (int i = 0; i < (int)v.size(); i++) {
        std::cout << v[i] << ' ';
    }
    std::cout << std::endl;
    set<int> a;
    for (int i = 0; i < (int)v.size(); i++) {
        a.insert(v[i]);
    }
    print(a);
    std::random_shuffle(v.begin(), v.end());
    for (int i = 0; i < (int)v.size(); i++) {
        std::cout << *a.lower_bound(v[i]) << ' ';
    }
    std::cout << std::endl;
}

int main() {
    T1();
    T2();
    T3();
    return 0;
}