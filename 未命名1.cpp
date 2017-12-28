#include <iostream>
using namespace std;

class A {
  static int a;
};



class B : public A {
  virtual void test();
};

int *c;

void B::test() {

}

int main() {
  A a;
  B b;
  printf("%ld\n", sizeof(a));
}
