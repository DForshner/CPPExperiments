
#include <iostream>

//
// Complier: Visual Studio 2013 (v120)
// Use /d1reportAllClassLayout or /d1reportSingleClassLayoutXXX compiler option to see object layout in memory.

using namespace std;

struct A {
  char a; // 1 byte
  char b; // 1 byte
  char c; // 1 byte
  char d; // 1 byte
  char e; // 1 byte
}; // 5 bytes + 0 byte padding = 5 bytes

//1>  class A	size(5) :
//1>  	+-- -
//1>   0 | a
//1>   1 | b
//1>   2 | c
//1>   3 | d
//1>   4 | e
//1>  	+-- -

struct B {
  char a; // 1 byte + 3 byte padding
  char* b; // 4 bytes
}; // 5 bytes + 3 bytes padding = 8 bytes

//1>  class B	size(8) :
//1>  	+-- -
//1>   0 | a
//1> | <alignment member> (size = 3)
//1>   4 | b
//1>  	+-- -

struct C {
  char a; // 1 byte
  char b; // 1 byte
  char c; // 1 byte + 1 byte padding 
  char* d; // 4 bytes
}; // 7 bytes + 1 byte padding = 8 bytes

//1>  class C	size(8) :
//1>  	+-- -
//1>   0 | a
//1>   1 | b
//1>   2 | c
//1> | <alignment member> (size = 1)
//1>   4 | d
//1>  	+-- -

struct D {
  char* a; // 4 byte
  char* b; // 4 bytes
  char c; // 1 byte + 3 bytes padding
}; // 9 bytes + 3 bytes padding = 12 bytes

//1>  class D	size(12) :
//1>  	+-- -
//1>   0 | a
//1>   4 | b
//1>   8 | c
//1> | <alignment member> (size = 3)
//1>  	+-- -

struct E {
  char a; // 1 byte + 3 bytes padding
  char* b; // 4 byte
  char c; // 1 byte + 3 bytes padding
  char* d; // 4 bytes
  char e; // 1 byte + 3 bytes padding
  char* f; // 4 bytes
}; // 15 bytes + 9 bytes padding = 24 bytes

//1>  class E	size(24) :
//1>  	+-- -
//1>   0 | a
//1> | <alignment member> (size = 3)
//1>   4 | b
//1>   8 | c
//1> | <alignment member> (size = 3)
//1>  12 | d
//1>  16 | e
//1> | <alignment member> (size = 3)
//1>  20 | f
//1>  	+-- -

struct F {
  int a; // 4 byte
  int* b; // 4 byte
}; // 8 bytes + 0 bytes padding = 8 bytes

struct G {
  bool a; // 1 byte
  bool b; // 1 byte + 2 byte padding
  int* c; // 4 byte
}; // 6 bytes + 2 bytes padding = 8 bytes

int main() {
  cout << " sizeof(bool) " << sizeof(bool) << endl;
  cout << " sizeof(char) " << sizeof(char) << endl;
  cout << " sizeof(char*) " << sizeof(char*) << endl;
  cout << " sizeof(int) " << sizeof(int) << endl;
  cout << " sizeof(int*) " << sizeof(int*) << endl << endl;

  cout << " sizeof(A) " << sizeof(A) << endl;
  cout << " sizeof(B) " << sizeof(B) << endl;
  cout << " sizeof(C) " << sizeof(C) << endl;
  cout << " sizeof(D) " << sizeof(D) << endl;
  cout << " sizeof(E) " << sizeof(E) << endl;
  cout << " sizeof(F) " << sizeof(F) << endl;
  cout << " sizeof(G) " << sizeof(G) << endl;

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}