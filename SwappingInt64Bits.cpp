// Implement code that takes as input a 64-bit integer and swaps
// bits at selected indices.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <bitset>
#include "stdafx.h"


unsigned __int64 swap(unsigned __int64 x, int indice1, int indice2) {
  auto bitIndice1 = (x >> indice1) & 1;
  auto bitIndice2 = (x >> indice2) & 1;

  // If the bits are the same there is nothing to do.
  if (bitIndice1 == bitIndice2) {
    std::cout << "Bits at indices match" << std::endl;
    return x;
  }

  auto mask = (1ul << indice1) | (1ul << indice2);
  std::cout << "Mask:   " << std::bitset<64>(mask) << std::endl;

  // Bitwise XOR (exclusive or) with the mask.
  return x ^= mask;
}

int _tmain(int argc, _TCHAR* argv[])
{
  unsigned __int64 x = 0xFFFF00000000FFFF;
  std::cout << "Before: " << std::bitset<64>(x) << std::endl;
  auto swappedx = swap(x, 20, 5);
  std::cout << "After:  " << std::bitset<64>(swappedx) << std::endl << std::endl;

  unsigned __int64 y = 0xFFFFFFFFFFFFFFFF;
  std::cout << "Before: " << std::bitset<64>(y) << std::endl;
  auto swappedy = swap(y, 20, 5);
  std::cout << "After:  " << std::bitset<64>(swappedy) << std::endl;

  return 0;
}