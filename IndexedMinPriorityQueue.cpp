//// The indexed priority queue supports the usual insert and delete-min operations of a priority queue
//// But also lets the client refer to keys on the priority queue using an index that is associated with 
//// each key—the client uses this integer to specify which key to delete or change.
////
//// Based on the by the IndexMinPQ by Robert Sedgewick and Kevin Wayne. 
//// 
//// Complier: Visual Studio 2013 (v120)
//
//#include <iostream>
//#include <memory>
//
//using namespace std;
//
//template <typename T>
//class IndexedMinPriorityQueue {
//public:
//  // Constructor
//  IndexedMinPriorityQueue(unsigned max_capacity)
//    : _nodes(new Node[max_capacity + 1]),
//
//    _index(new unsigned[max_capacity + 1]),
//    _capacity(max_capacity),
//    _size(0) {
//
//    // Zero array
//    std::fill_n(_index.get(), _capacity + 1, 0); 
//  }
//
//  // O(log(n))
//  void add(unsigned index, T key) {
//    if ((_size + 1) > _capacity)
//      throw std::exception("Unable to add");
//
//    Node &n = _nodes[++_size];
//    n.key = key;
//    n.index = index;
//
//    // Store the node's location in the index
//    _index[index] = _size;
//
//    reheapify_up(_size);
//  }
//
//  // O(1)
//  unsigned get_min_key() {
//    return _nodes[1].key;
//  }
//
//  // O(1)
//  void del_min_key() {
//    if (_size == 0)
//      throw std::exception("Unable to delete min.");
//
//    swap_node(1, _size--);
//    reheapify_down(1);
//  }
//
//  // Change the key at a given index. O(log(n))
//  void change_key(unsigned index, T key) {
//    index = _index[index];
//    Node &n = _nodes[index];
//    T tmp_key = n.key;
//    n.key = key;
//
//    if (key > tmp_key)
//      reheapify_down(index);
//    else
//      reheapify_up(index);
//  }
//
//  const T &get_key(unsigned index) {
//    return _nodes[_index[index]].key;
//  }
//
//  bool empty()  { return (_size == 0); }
//
//  size_t size()  { return _size; }
//
//  bool contains(unsigned index) { return !!_index[index]; }
//
//  void display() {
//      cout << endl << "Current Queue Contents" << endl << "i \t Nodes \t Key \t Index" << endl;
//      for (unsigned i = 1; i <= _size; ++i) {
//        cout << i << "\t" << _nodes[i].key << "\t" << _nodes[_index[i]].key << "\t" << _nodes[_index[i]].index << endl;
//      }
//  }
//
//private:
//  struct Node {
//    Node() : key(0), index(0) {}
//
//    // Copy constructor
//    Node(const Node &other)
//     : key(other.key), index(other.index) {}
//
//    T key;
//    unsigned index;
//  };
//
//  void reheapify_up(unsigned child_index) {
//    while (child_index > 1) {
//      unsigned parent_index = child_index >> 1;
//
//      // If index being examined is less than parent bubble up.
//      if (_nodes[child_index].key < _nodes[parent_index].key) {
//        swap_node(child_index, parent_index);
//        child_index = parent_index;
//      } else {
//        break;
//      }
//    }
//  }
//
//  void reheapify_down(unsigned parent_index) {
//    unsigned child_index = parent_index << 1;
//
//    // While the child index is inside bounds
//    while (child_index <= _size) {
//      // If not the final node choose the smallest of the child nodes.
//      if (child_index != _size && (_nodes[child_index].key > _nodes[child_index + 1].key))
//        child_index++;
//
//      // If the parent is less than the child do nothing.
//      if (_nodes[parent_index].key <= _nodes[child_index].key)
//        break;
//
//      // percolate down.
//      swap_node(parent_index, child_index);
//      parent_index = child_index;
//      child_index = parent_index << 1;
//    }
//  }
//
//  void swap_node(unsigned index_a, unsigned index_b) {
//    std::swap(_nodes[index_a], _nodes[index_b]);
//    std::swap(_index[_nodes[index_a].index], _index[_nodes[index_b].index]);
//  }
//
//  std::unique_ptr<Node[]> _nodes;
//  std::unique_ptr<unsigned[]> _index;
//
//  unsigned _capacity;
//  unsigned _size;
//};
//
//int main()
//{
//  IndexedMinPriorityQueue<unsigned> pq(10);
//  pq.add(1, 20);
//  pq.add(2, 90);
//  pq.add(3, 40);
//  pq.add(4, 80);
//  pq.del_min_key();
//  pq.add(10, 21);
//  pq.add(5, 60);
//  pq.add(6, 10);
//  pq.add(7, 30);
//  pq.add(4, 50);
//  pq.add(8, 100);
//  pq.display();
//
//  if (pq.contains(1))
//    cout << endl << "Queue still contains value of index 1." << endl;
//
//  if (!pq.contains(8))
//    cout << endl << "Queue did not contain value of index 8." << endl;
//
//  pq.change_key(2, 88);
//  pq.change_key(3, 15);
//
//  cout << endl << "start->";
//  while (pq.size() > 0) {
//    cout << pq.get_min_key() << "->";
//    pq.del_min_key();
//  }
//  cout << "end" << endl;
//
//  cout << "[Press enter to exit]" << endl;
//  cin.ignore();
//  return 0;
//}