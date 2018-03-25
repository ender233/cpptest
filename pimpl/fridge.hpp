//
// Created by ender on 2/25/18.
//

#ifndef PIMPL_FRIDGE_HPP
#define PIMPL_FRIDGE_HPP

#include <memory>

class Fridge
{
public:
    Fridge();
    ~Fridge();
    void coolDown();

private:
    struct FridgeImpl;
    std::unique_ptr<FridgeImpl> impl_;
};

#endif //PIMPL_FRIDGE_HPP
