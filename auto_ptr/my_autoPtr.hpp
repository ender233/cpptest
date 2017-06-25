#pragma once

template< typename T>
class My_autoPtr
{
private:
    T *ptr;
    template<class> friend class My_autoPtr; // ok
    //template<class U> friend class My_autoPtr<U>; // error

public:
    explicit My_autoPtr(T *ptr=NULL) : ptr(ptr) {}
    template<typename U>
    My_autoPtr(My_autoPtr<U> &rhs) : ptr(rhs.release()) {}
    virtual ~My_autoPtr() {delete ptr;}

    My_autoPtr<T> & operator = (My_autoPtr &rhs) {
        if(this != &rhs) reset(rhs.release());
        return *this;
    }

    // operator double(){};
    template<typename U>
    explicit operator My_autoPtr<U>() {
        return My_autoPtr<U>(ptr);
    }
    
    T & operator*() const {
        return *ptr; 
    }
    T * operator->() const {
        return ptr; 
    }

    T* get() const{
        return ptr;    
    }
    T* release() {
        T *newPtr = ptr; 
        ptr = NULL;
        return newPtr;
    }
    void reset(T *p) {
        if(p != ptr) {
            delete ptr; 
            ptr = p;
        }
    }
};
