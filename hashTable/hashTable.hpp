//
// Created by ender on 3/26/18.
//
#ifndef HASHTABLE_HASHTABLE_HPP
#define HASHTABLE_HASHTABLE_HPP

#include <list>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
typedef std::vector<std::list<int>> NodeType;

class  HashTable {
public:
    HashTable(int prime_, int size_) :
            prime_(prime_),
            size_(size_)
    {
        node_.resize(size_);
    }
    ~HashTable() {}

    void insert(int x) {
        if(isValueExited(x)) return;

        int key = Hash(x);
        node_[key].push_back(x);
    }

    void remove(int x) {
        if(!isValueExited(x)) return;

        int key = Hash(x);
        node_[key].remove(x);
    }

    void display() {
        for(auto &p : node_) {
            for(auto &v : p) {
                std::cout << v << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    bool isValueExited(int x) {
        int key = Hash(x);
        const std::list<int> list = node_[key];

        if(!list.empty() &&
                std::find(list.begin(), list.end(), x)!=list.end()) {
            return true;
        }

        return false;
    }

    int Hash(int x) {
        return x % prime_;
    }


private:
    int         prime_;
    int         size_;
    NodeType    node_;
};
#endif //HASHTABLE_HASHTABLE_HPP
