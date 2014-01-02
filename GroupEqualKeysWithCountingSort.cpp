// Given an array of objects with a key field re-arrange the objects
// so that objects with the same key value appear together.  Order
// does not matter.
//
// O(n) time and O(k) additional space
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

struct Foo {
  int key;
  string name;

  bool operator < (const Foo & that) const { return key < that.key; }
  bool operator > (const Foo & that) const { return key > that.key; }
  bool operator == (const Foo & that) const { return key == that.key; }
  bool operator != (const Foo & that) const { return key != that.key; }
};

// Hash function for Foo
struct HashFoo {
  size_t operator()(const Foo &f) const {
    return hash<int>()(f.key) ^ hash<string>()(f.name);
  }
};

void display(const vector<Foo> &foos) {
  for (const auto &f : foos)
    cout << f.key << "|" << f.name << ", ";
  cout << endl << endl;
}

void counting_sort(vector<Foo>* foos) {

  // Count the number of occurrences of each key
  unordered_map<int, int> key_to_count; // Hash table of key -> # occurrences 
  for (const auto &f : *foos)
    ++key_to_count[f.key];

  // Display key to count
  cout << endl << "key_to_count:" << endl;
  for (const auto &k : key_to_count) {
    cout << "key: " << k.first << " count: " << k.second << endl;
  }

  // Iterate over each key and keep a cumulative count of the starting offset in the
  // array where elements with the key are placed
  unordered_map<int, int> key_to_offset; // Hash table of key -> array offset
  int offset = 0;
  for (const auto &k : key_to_count) {
    key_to_offset[k.first] = offset;
    offset += k.second;
  }

  // Display key to offset
  cout << endl << "key_to_offset:" << endl;
  for (const auto &k : key_to_offset)
    cout << "key: " << k.first << " offset: " << k.second << endl;
  cout << endl;

  // For each key swap the element at the beginning of the offset map
  // with the element at the key's final location.
  while (!key_to_offset.empty()) { // use .empty() O(1) instead of .size() ~O(n)
    auto from = key_to_offset.begin();
    auto element_at_from_offset = &(*foos)[from->second];

    auto to = key_to_offset.find((*element_at_from_offset).key);
    auto element_at_to_offset = &(*foos)[to->second];

    cout << "Swapping Refs: (" << (*element_at_from_offset).key << "|" << (*element_at_from_offset).name << ")"
      << " To: (" << (*element_at_to_offset).key << "|" << (*element_at_to_offset).name << ")" << endl;

    swap(*element_at_from_offset, *element_at_to_offset);

    display(*foos);

    // the "to" element is now sorted so decrement its 
    // count by one and move its offset forward one position.
    auto to_count = --key_to_count[to->first];

    // If key's count is zero we are finished with the key.
    if (to_count) {
      ++to->second;
    }
    else {
      cout << "Finished sorting key: " << to->first << endl << endl;
      key_to_offset.erase(to);
    }
  }
}

int main()
{
  auto foos = new vector<Foo> { 
    Foo { 2, "A" }, Foo { 1, "B" },
    Foo { 3, "C" }, Foo { 3, "D" },
    Foo { 2, "E" }, Foo { 1, "F" },
    Foo { 5, "G" }, Foo { 4, "H" },
    Foo { 1, "I" }, Foo { 1, "J" },
    Foo { 4, "K" }, Foo { 3, "L" },
    Foo { 2, "M" }, Foo { 2, "N" },
  };

  cout << endl << "Unsorted: " << endl;
  display(*foos);

  counting_sort(foos);

  cout << endl <<  "Sorted: " << endl;
  display(*foos);

  cout << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}