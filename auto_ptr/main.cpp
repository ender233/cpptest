#include <iostream>
#include "my_autoPtr.hpp"

struct Base
{
   int x;
   Base(int x=0) : x(x) {}
   virtual void printX(){std::cout<<"Base Print x:"<<x<<std::endl;}
};

struct Child : public Base
{
    Child(int x) : Base(x) {}
    virtual void printX() {std::cout<<"Chind Print x:"<<x<<std::endl;}
};

int main()
{
    My_autoPtr<Child> cp(new Child(222));
    cp->printX();
    (*cp).printX();

    std::cout<<"-------"<<std::endl;
    My_autoPtr<Base> bp = cp;
    My_autoPtr<Base> bp2(new Base(333));
    bp2->printX();
    bp->printX();
}
