#include <string>
#include <cassert>
#include <typeinfo>
#include "Serial.h"
#define SAME(X, Y) {assert(typeid(X) == typeid(Y)); assert(X == Y);}

using namespace std;

int main() {
  Serial s;
  s.put(9832759025L);
  SAME(s.str(), "\x6c\x42\x4a\x13\xfe\xf1"s)
  return 0;
}
