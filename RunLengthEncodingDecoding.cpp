// Implement run length encoding and decoding functions assuming string contains
// only letters and no digits.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

void push_string(vector<char>& vec, const string& str) {
  for (const char &c : str)
    vec.push_back(c);
}

string encode(const string& original) {
  vector<char> encoded;
  encoded.reserve(original.size());

  char encoding_char = NULL;
  unsigned count = 0;
  for (const char &c : original) {

    // Is this char the same as the previous one being encoded.
    if (c == encoding_char) {
      ++count;
      continue;
    }

    // Store the count for the char that was being encoded if 
    // it's not zero (first char in array) or one.
    if (count > 1) {
      auto s = std::to_string(count);
      push_string(encoded, s);
    }

    // Store the new char
    encoded.push_back(c);
    encoding_char = c;
    count = 1;
  }

  return string(encoded.cbegin(), encoded.cend());
}

string decode(const string& encoded) {
  vector<char> decoded;
  vector<char> current_number;

  for (const char& c : encoded) {

    // Check if part of number
    if (std::isdigit(c)) {
      current_number.push_back(c);
      continue;
    }

    // if previous char was part of a number then 
    // add that many instances of the last char.
    if (current_number.size() > 0) {
      auto count = std::stoi(string(current_number.cbegin(), current_number.cend()));
      auto last = decoded.back();

      // Remember that one char has already been appended.
      for (auto i = 1; i < count; ++i)
        decoded.push_back(last);

      current_number.clear(); // Reset
    }

    // current char is regular char.
    decoded.push_back(c);
  }

  return string(decoded.cbegin(), decoded.cend());
}

void main() {
  auto original = string("This iissss aaaaaaaa really SHOOORT TEST!!");
  cout << "Original string: " << original << endl;

  auto encoded = encode(original);
  cout << "Encoded string: " << encoded << endl;

  cout << "Compressed by " << ((float)encoded.length() / (float)original.length() * 100) << " percent." << endl;

  auto decoded = decode(encoded);
  cout << "Decoded string: " << decoded << endl;

  cout << endl << "[Press enter to exit]";
  cin.ignore();
}