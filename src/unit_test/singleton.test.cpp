#include "common/singleton.hpp"
#include <iostream>

class C {
};

int main(int argc, const char* argv[]) {
  std::cout << "Singleton unit test !!!" << std::endl;
  // utils::Singleton<C>::instance();
}
