#include <iostream>
#include "hashTable.hpp"
#include <random>

int main() {
    HashTable h(25, 25);

    std::cout << "/***********insert&display************/" << std::endl;
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 999);
    for(int i=0; i<100; ++i) {
        h.insert(dist(rd));
    }
    h.display();

    std::cout << "\n" << "/***********del&display************/" << std::endl;
    HashTable h2(25, 25);
    for(int i=0; i<30; ++i) {
        h2.insert(i) ;
    }
    h2.remove(26);
    h2.display();
}