#include <vector>
#include "RotatingHash.h"

using namespace std;

template <class T>
unsigned RotatingHash<T>::Hash(const T& key, std::size_t len)
{
  unsigned int hash = 0;
  unsigned i;

  // 1) The current hash shifted left 4 bits XORed with the current hash shifted right 28 bits.
  // 2) The result is XORed with the next byte.
  for ( i = 0; i < len; i++ )
    hash = ( hash << 4 ) ^ ( hash >> 28 ) ^ (unsigned char) key[i];

  return hash;
}