// Bitmasks are used to store multiple Boolean values in
// in the individual bits that makes up another basic type.
// Instead of storing 8 bool types which consume 8 x 1 byte = 8 bytes
// we can store all 8 Boolean values in a 1 char = 1 byte.

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

#include <iostream>
#include <climits>  // For CHAR_BIT

using namespace std;

int main()
{
  const char ONE = 0x01; // 00000001
  const char TWO = 0x02; // 00000010
  const char THREE = 0x04; // 00000100
  const char FOUR = 0x08; // 00001000
  const char FIVE = 0x10; // 00010000
  const char SIX = 0x20; // 00100000
  const char SEVEN = 0x40; // 01000000
  const char EIGHT = 0x80; // 10000000
  
  //
  // Example 1 - If statements require only one bit to match to be true;
  //
  std::cout << std::endl << "Example 1" << std::endl;

  char test = 0x42; // 01000010

  if (test & TWO) // And
    std::cout << "Contains a two" << std::endl;

  if (test & (TWO | THREE)) // test AND (00000011)
    std::cout << "Contains a two and/or a three" << std::endl;

  //
  // Example 2 - Switch statements require all of the bits to match to take a particular branch.
  //
  std::cout << std::endl << "Example 2" << std::endl;

  char test2 = 0xC0; // 11000001
  const char FILTER = 0xF0; // 11110000 // Use a filter to only examine a subsection of the bits.
  
  switch (test2 & FILTER)
  {
    case ONE: // 00000001
      std::cout << "Contains a one" << std::endl;
      break;
    // ..
    case SEVEN | EIGHT: // 11000000 - The OR operation combines the bitmasks together.
      std::cout << "Contains seven and eight" << std::endl;
      break;
  }

  //
  // Example 3 - The shift operator can be used to loop through a bitmask from LSB to MSB.
  //
  std::cout << std::endl << "Example 3" << std::endl;

  char test3 = 0xA6; // 10100110

  std::cout << "Value before: " << test3 << std::endl;

  // Get total number of bits
  auto number_of_bits = sizeof(test3) * CHAR_BIT;

  // Cycle through bits from LSB to MSB
  for (auto i = 0; i < number_of_bits; i++) {
    // test & (00000001) gives the first bit position
    std::cout << (test3 & 1) << " ";
    
    // Shift bits right by one.  
    // Note: this is actually altering the value of test3 and hopefully putting returning it to its original value.
    test3 >>= 1;
  }

  std::cout << std::endl << "Value after: " << test3 << std::endl;
}