// This console app calculates the number of bits changed in the hash
// values of a string when a single character is changed.
//
// The avalanche effect is a desirable function in hash functions where
// when the input is changed slightly the output changes significantly.
// This is useful in hashing because it increases the random distribution 
// of hashes.
// See: http://en.wikipedia.org/wiki/Avalanche_effect

// Compiler: Microsoft Visual C++ Compiler Nov 2012 CTP (v120_CTP_Nov2012)

#include <string>
#include <iostream>
#include <bitset> // For bitset
#include <climits>  // For CHAR_BIT

using namespace std;

// Example 1
void StdHashExample(std::string& str1, std::string& str2)
{
  std::cout << std::endl << "Example 1 - %bit difference using std:hash" << std::endl;

  std::hash<std::string> hasher;
  size_t str1_hash = hasher(str1);
  std::cout << "String 1: " << str1 << " , Hash: " << str1_hash << std::endl;

  size_t str2_hash = hasher(str2);
  std::cout << "String 2: " << str2 << " , Hash: " << str2_hash << std::endl;
  
  auto difference = str1_hash ^ str2_hash; // XOR to show what has changed

  int count = 0;
  auto total_bits = sizeof(difference) * CHAR_BIT;  // Example: sizeof(3.33) * CHAR_BIT; gives the number of bits for a float

  std::cout << "Number of bits: " << total_bits << std::endl << "XOR: ";

  for (auto i = 0; i < total_bits; ++i) { 
    std::cout << (difference & 1);
    count += (difference & 1); // (difference & 1) gives bit in position 1
    difference >>= 1; // shift bits right by one
  }

  std::cout << std::endl << "Bits changed: " << count << " , % bits changed: " << (float) count / total_bits * 100 << std::endl;
};

// A questionable additive hash
unsigned AdditiveHash(std::string& key, unsigned len)
{
  unsigned int hash = 0;
  unsigned i;

  for ( i = 0; i < len; i++)
    hash += (unsigned char) key[i];

  return hash;
};

// Example 2
void AdditiveHashExample(std::string& str1, std::string& str2)
{
  std::cout << std::endl << "Example 2 - %bit difference using questionable additive hash" << std::endl;

  unsigned str1_hash = AdditiveHash(str1, 15);
  std::cout << "String 1: " << str1 << " , Hash: " << str1_hash << std::endl;
  bitset<32> hash1_bitset (str1_hash);
  
  unsigned str2_hash = AdditiveHash(str2, 15);
  std::cout << "String 2: " << str2 << " , Hash: " << str2_hash << std::endl;
  bitset<32> hash2_bitset (str2_hash);

  auto difference = hash1_bitset ^ hash2_bitset; // XOR to show what has changed

  int count = 0;
  auto total_bits = sizeof(difference) * CHAR_BIT;

  std::cout << "Number of bits: " << total_bits << std::endl << "XOR: ";

  for (auto i = 0 ; i < total_bits ; i++) {
    std::cout << difference[i];
    count += (difference[i]) ? 1 : 0;
  }

  std::cout << std::endl << "Bits changed: " << count << " , % bits changed: " << (float) count / total_bits * 100 << std::endl;
};

int main()
{
  std::string str1 = "This is a test!";
  std::string str2 = "This is a test.";
  
  StdHashExample(str1, str2);
  AdditiveHashExample(str1, str2);
}