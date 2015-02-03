#include <vector>
#include "XORHash.h"

using namespace std;

template <class T>
unsigned XORHash<T>::Hash(const T& key, std::size_t len)
{
  unsigned int hash = 0;
  unsigned i;

  for ( i = 0; i < len; i++ )
    hash ^= (unsigned char) key[i];

  return hash;
}