#include <vector>
#include "FNVHash.h"

using namespace std;

template <class T>
unsigned FNVHash<T>::Hash(const T& key, std::size_t len)
{
  unsigned hash = 2166136261;
  unsigned i;

  for ( i = 0; i < len; i++ )
    hash = ( hash * 16777619 ) ^ (unsigned char) key[i];

  return hash;
}