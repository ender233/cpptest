//
// Created by ender on 2/25/18.
//

#include <iostream>
#include "fridge.hpp"
#include <memory>

struct Fridge::FridgeImpl
{
public:
    void coolDown() {
        std::cout<<"cool Down func"<<std::endl;
    }
};

Fridge::Fridge():impl_(std::make_unique<FridgeImpl>()) {}
Fridge::~Fridge() = default;

void Fridge::coolDown() {
    impl_->coolDown();
}

