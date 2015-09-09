// A type map that allows mapping of type K to a values of type V.
//
// Compiled using Visual Studio 2015

#include <iostream>
#include <atomic>
#include <unordered_map>
#include <string>
#include <memory>
#include <cassert>

namespace TypeMap {

  template<class V>
  class TypeMap {
  public:
    // These type definitions are necessary to be compliant with the STL because it uses iterator traits.
    // See the Nested container section of: http://www.cs.northwestern.edu/~riesbeck/programming/c++/stl-iterator-define.html
    typedef std::unordered_map<int, V> Map;
    typedef typename Map::iterator iterator;
    typedef typename Map::const_iterator const_iterator;
    typedef typename Map::value_type value_type;

    const_iterator cbegin() const { return _map.cbegin(); }

    const_iterator cend() const { return _map.cend(); }

    iterator begin() { return _map.begin(); }

    iterator end() { return _map.end(); }

    // Find value associated with type K
    template<class K>
    iterator find() { return _map.find(getTypeId<K>()); }

    // Find value associated with type K
    template<class K>
    const_iterator find() const { return _map.find(getTypeId<K>()); }

    // Associate value with type
    template<class K>
    void put(V &&val) {
      _map[getTypeId<K>()] = std::forward<V>(val);
    }

  private:

    static std::atomic_int _idCounter;
    Map _map;

    // Returns a unique integer per type V
    template <typename V>
    int getTypeId() {
      static int id = ++_idCounter;
      return id;
    }
  };
    
  // Stores an single instantiation of a derived class against its Type.
  template<typename BaseType>
  class DerivedTypeMap {
  public:

    template<typename DerivedType>
    DerivedType* get() {
      auto it = _map.find<DerivedType>();
      assert(it != _map.end());
      return static_cast<DerivedType*>(it->second.get());
    }

    template<typename DerivedType>
    void put(std::unique_ptr<DerivedType> &&val) {
      _map.put<DerivedType>(std::forward<std::unique_ptr<DerivedType>>(val));
    }

  private:
    TypeMap<std::unique_ptr<BaseType>> _map;
  };

  template<class V>
  std::atomic_int TypeMap<V>::_idCounter(0);
}

class A { virtual void display() = 0; };
class B : public A { public: void display() override { std::cout << "B" << std::endl; } };
class C : public A { public: void display() override { std::cout << "C" << std::endl; } };
class D : public A { public: void display() override { std::cout << "D" << std::endl; } };

int main() {

  TypeMap::TypeMap<std::string> map;
  map.put<int>("Integers");
  map.put<double>("Doubles");
  std::cout << map.find<int>()->second << std::endl;
  std::cout << map.find<double>()->second << std::endl;

  TypeMap::DerivedTypeMap<A> derivedMap;
  derivedMap.put<B>(std::make_unique<B>());
  derivedMap.put<C>(std::make_unique<C>());
  derivedMap.put<D>(std::make_unique<D>());

  derivedMap.get<D>()->display();
  derivedMap.get<C>()->display();
  derivedMap.get<B>()->display();

  return 0;
}
