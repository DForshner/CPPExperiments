// Write a function that returns the size of the rectangular intersection of two 
// xy-aligned rectangles intersect.
//
// Complier: Visual Studio 2013 (v120)

#include <iostream>
using namespace std;

struct Rectangle {
  int x, y, width, height;
};

// Use library 
inline int min(const int& a, const int& b) { return (a < b) ? a : b; }
inline int max(const int& a, const int& b) { return (a > b) ? a : b; }

bool intersect(const Rectangle& a, const Rectangle& b) {
  return
    // Sliding a leftwards over b (right) they begin to intersect when (a.x + a.w) > b.x
    // and stop overlapping when a.x > (b.x + b.y)
    ((a.x + a.width) >= b.x) && (a.x <= (b.x + b.width)) &&
    // Sliding a (top) downwards over b (bottom) they being to intersect when (a.y) < (b.y + b.h)
    // and stop overlapping when (a.y + a.h) < b.y
    (a.y <= (b.y + b.height)) && ((a.y + a.height) >= b.y);
}

Rectangle find_intersection(const Rectangle& a, const Rectangle& b) {
  // If they do not intersect return an rectangle of size zero.
  if (!intersect(a, b))
    return Rectangle() = { 0, 0, 0, 0 };

  auto x = max(a.x, b.x);
  auto w = min((a.x + a.width), (b.x + b.width)) - x;
  auto y = max(a.y, b.y);
  auto h = min((a.y + a.height), (b.y + b.height)) - y;
  return Rectangle() = { x, y, w, h };
}

void display(const Rectangle &show) {
  cout << endl << "x: " << show.x << " y: " << show.y <<
    " width: " << show.width << " height: " << show.height;
}

int main()
{
  auto a = Rectangle() = { 0, 0, 4, 4 };
  auto b = Rectangle() = { 3, 3, 4, 4 };
  cout << endl << "Intersection of a & b";
  display(find_intersection(a , b));

  auto c = Rectangle() = { 10, 10, 10, 10 };
  auto d = Rectangle() = { 0, 0, 11, 11 };
  cout << endl << "Intersection of c & d";
  display(find_intersection(c, d));

  cout << endl << "[Press enter to exit]" << endl;
  cin.ignore();
  return 0;
}