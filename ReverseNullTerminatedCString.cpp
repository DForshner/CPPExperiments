// Reverse a null terminated (C) string.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>

using namespace std;

void reverse(char* str) {
  // Find the end
  auto end = str;
  while (*end!= '\n') {
    end++;
  }
  end--; // Was pointing at string's null terminator.

  // Swap characters from the ends moving inwards to the middle.
  while (str < end) {
    auto tmp = *end;
    *end-- = *str;
    *str++ = tmp;
  }
}

int main()
{
  char str[] = { "This is a string that needs reversing.\n" };
  cout << endl << "Before: " << str;
  reverse(str);
  cout << endl << "After: " << str;

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}