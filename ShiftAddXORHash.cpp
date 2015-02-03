#include <vector>
#include "ShiftAddXORHash.h"

using namespace std;

template <class T>
unsigned ShiftAddXORHash<T>::Hash(const T& key, std::size_t len)
{
  unsigned int hash = 0;
  unsigned i;

  for ( i = 0; i < len; i++ )
    hash ^= ( hash << 5 ) + ( hash >> 2 ) + (unsigned char) key[i];

  return hash;
}