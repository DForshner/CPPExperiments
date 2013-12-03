// Implementation of the sieve of Eratosthenes to find primes.
//
// Uses an array of native ints to sieve primes.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <bitset>
#include <limits>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

typedef unsigned long long number;
const number max_search = 10000;

class PrimeBitArray
{
public:
  PrimeBitArray(number max_pos) {
    bitslong = CHAR_BIT * sizeof(long);
    max_slots = max_pos / bitslong;
    slots = new unsigned int[max_slots]; // Heap allocation

    // Init with zeros.
    for (int i = 0; i < max_slots; i++)
      slots[i] = 0;

    cout << "max: " << max_pos << " / " << bitslong << " = slots:" << max_slots << endl;
  }

  ~PrimeBitArray() {
    delete[] slots;
  }

  bool get(number pos) {
    auto slot = get_slot(pos);
    if (slot > max_slots)
      throw "Index is out of bounds.";

    auto index = get_slot_index(pos);
    //cout << "GET - pos:" << pos << " - slot:" << slot << ", slot index:" << index << endl;
    return (slots[slot] & (1UL << index));
  }

  void put(number pos, bool value) {
    number slot = get_slot(pos);
    //cout << "Before: " << bitset<32>(slots[slot]) << endl;

    long slot_value = slots[slot];
    unsigned int index = get_slot_index(pos);
    unsigned int mask = 1ULL << index;
    bool old_value = (slot_value & mask);

    // If value needs to be changed toggle with XOR.
    if (old_value != value)
      slots[slot] ^= mask;

    //cout << "After:  " << bitset<32>(slots[slot]) << endl;
  }

  int get_max_position() { return max_slots * bitslong; }

  // Which slot to store in.
  inline long get_slot(number pos) {
    return pos / bitslong;
  }

  // Which bit of the slot to store in.
  inline unsigned int get_slot_index(number pos) {
    return (unsigned int)(pos % bitslong);
  }

private:
  int bitslong; // How many bits long each slot is
  unsigned int* slots; // Array of slots
  int max_slots; // The maximum number of slots.
};

// Since we are storing only odd composite numbers we can
// reduce the bit array by half by removing the first
// few known primes and even numbers.
inline number map_to_array(number n) {
  // Remove 1,2,3 cases
  n -= 3;
  // Remove even numbers
  n /= 2;
  return (number)n;
}

bool isPrime(PrimeBitArray* bit_array, number n){
  // 1 is not considered prime.
  if (n == 1)
    return 0;

  // 2,3 are prime.
  if (n < 4)
    return 1;

  // Even numbers other than 2 are not prime.
  if ((n % 2) == 0){
    return 0;
  }

  auto val = bit_array->get(map_to_array(n));
  //cout << endl << "IsPrime - num: " << n << ", pos: " << pos << ", value: " << val << endl;
  return !val;
}

// start sieving at odd multiples of offset (internal position) offset with width step 
void doSieve(PrimeBitArray* bit_array, number offset, number step){
  auto current = 2 * step;
  while (current < bit_array->get_max_position() ){

    // If odd multiple set bits as composite number.
    if (current % 2 != 0)
        bit_array->put(map_to_array(current), 1);

    current += step;
  }
}

void sieve(PrimeBitArray* bit_array) {
  number spot = 1, pos = 0;

  // While every odd number up to the square root of the maximum.
  while (spot < 1 + sqrt((float)max_search)){
    spot += 2; // Start at 3

    // Check if spot has already been marked as not being prime.
    if (!isPrime(bit_array, spot)){
      pos++;
      continue;
    }

    cout << "Found seed prime: " << spot << endl;
    doSieve(bit_array, pos, spot);
    pos++;
  }
}

vector<int> get_known_primes()
{
  // From: http://primes.utm.edu/lists/small/1000.txt 
  std::string known_primes =
  "5      7     11     13     17     19     23     29 \
    4861   4871   4877   4889   4903   4909   4919   4931   4933   4937 \
                5099   5101   5107   5113   5119   5147   5153   5167   5171   5179 \
                    7841   7853   7867   7873   7877   7879   7883   7901   7907   7919";

  istringstream iss(known_primes);
  vector<int> values;
  int n;
  while (iss >> n) {
    values.push_back(n);
  }

  return values;
}

void main()
{
  cout << "Sieve of Eratosthenes" << endl;

  // The array is only storing odd composite numbers which are not 1 or 3
  auto bit_array = new PrimeBitArray((max_search - 3) / 2);
  sieve(bit_array);

  cout << endl << endl << "Print out all primes found." << endl;
  for (auto i = 1; i <= max_search; i++)
    if (isPrime(bit_array, i))
      cout << i << ", ";

  cout << endl << endl << "Check against known prime numbers." << endl;
  auto known_primes = get_known_primes();
  for_each(known_primes.begin(), known_primes.end(), [&bit_array](int x) {
    if (isPrime(bit_array, x))
        cout << "Known prime " << x << " is prime." << endl; 
    else
        cout << "Known prime " << x << " is NOT prime." << endl; 
  });

  cout << endl << endl << "Check against known none prime numbers." << endl;
  for_each(known_primes.begin(), known_primes.end(), [&bit_array](int x) {
    if (isPrime(bit_array, x - 1))
        cout << "Known non prime " << x << " is prime." << endl; 
    else
        cout << "Known non prime " << x << " is NOT prime." << endl; 
  });

  cout << endl << "[Press enter to exit]";
  cin.ignore();
}