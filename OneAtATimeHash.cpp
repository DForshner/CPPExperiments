#include <vector>
#include "OneAtATimeHash.h"

using namespace std;

template <class T>
unsigned OneAtATimeHash<T>::Hash(const T& key, std::size_t len)
{
  unsigned int hash = 0;
  unsigned i;

  for ( i = 0; i < len; i++ )
  {
    hash += (unsigned char) key[i]; // Add the current hash to the new input
    hash += ( hash << 10 ); // Add the hash to itself shifted left by ten
    hash ^= ( hash >> 6 ); // XOR the hash to itself shifted right by 6
  }

  // Perform final mixing
  hash += ( hash << 3 );
  hash ^= ( hash >> 11 ); // XOR the hash to itself shifted right by 11
  hash += ( hash << 15 );

  return hash;
}