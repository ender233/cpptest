#include <iostream>
#include <vector>

// static binding
/*
class Cat
{
public:
    static void say_hello() {
        std::cout<<"miao miao miao!"<<std::endl;
    }
};
class Dog
{
public:
    static void say_hello() {
        std::cout<<"wang wang wang!"<<std::endl;
    }
};
template<typename T>
class Pet
{
public:
   void say_hello() {
       T::say_hello();
   }
};
 */

// dynamic binding
class Pet1
{
public:
    virtual void say_hello() = 0;
};
class Cat1 : public Pet1
{
public:
    void say_hello(){
        std::cout<<"1 miao miao miao!"<<std::endl;
    }
};
class Dog1 : public Pet1
{
public:
    void say_hello(){
        std::cout<<"2 wang wang wang!"<<std::endl;
    }
};

class NumberType
{
public:
    virtual ~NumberType() {
    }
};
class IntType : public NumberType
{
public:
    virtual ~IntType() {
    }
private:
    int x;
};
class FloatType: public NumberType
{
public:
    virtual ~FloatType() {
    }
private:
    float x;
};

int main() {
    /*
    Pet<Cat> cat;
    Pet<Dog> dog;
    cat.say_hello();
    dog.say_hello();
     */

    std::vector<Pet1 *> pets;
    pets.push_back(new Cat1);
    pets.push_back(new Dog1);
    for(auto p : pets) {
       p->say_hello();
    }

    return 0;
}