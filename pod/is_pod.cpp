#include <iostream>
#include <type_traits>
#include <vector>
// adapter from https://stackoverflow.com/questions/4178175/what-are-aggregates-and-pods-and-how-why-are-they-special/7189821#

template <typename T>
void ispod() {
  std::cout << std::boolalpha;
  std::cout << std::is_pod<T>::value << '\n';
}

/*****************/
template <typename T>
struct Type {
  T value;
};

struct POD {
  int x;
  char y;
  void f() {} // no harm if there's a function
  static std::vector<char > v;
};


/*****************/
struct NotPOD1 {
  ~NotPOD1() {} // user-define destructor
};
struct NotPOD2 {
  NotPOD1 arr[3]; // array of non-POD struct
};

int main()
{
  ispod<POD>();
  ispod<Type<int>>();
  ispod<NotPOD1>();
  ispod<NotPOD2>();
  return 1;
}
