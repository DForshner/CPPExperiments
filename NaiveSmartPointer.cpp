// Implement a smart pointer class that simulates a pointer while providing 
// automatic garbage collection when the number of references reaches zero.
//
// Complier: Visual Studio 2013 (v120)

#include <assert.h>
#include <iostream>
#include <string>

namespace smart_pointer {

  template <class T>
  class SmartPointer {

  public:
    // Constructor for new object
    SmartPointer(T* object) {
      assert(object != nullptr);
      obj = object;
      ref_count = new unsigned(1);
    }

    // Constructor for existing object
    SmartPointer(SmartPointer<T>& ptr) {
      assert(&ptr != nullptr);
      obj = ptr.obj;
      ref_count = ptr.ref_count;
      ++(*ref_count);
    }

    // Setting one equal to another
    SmartPointer<T> & operator= (SmartPointer<T>& ptr) {
      assert(&ptr != nullptr);

      // Check if we are assigning this objec to itself.
      if (this == &ptr)
        return *this;

      // If this pointer was already assigned to another object decrease ref count.
      if (ref_count > 0) {
        --(*ref_count);
        // Remove object if we just removed the final ref to this object.
        if (*ref_count == 0) {
          remove();
        }
      }

      // Assign this pointer to the new object. 
      obj = ptr.obj;
      ref_count = ptr.ref_count;
      ++(*ref_count);
      return *this;
    }

    // Destructor
    ~SmartPointer() {
      --(*ref_count);

      // If there are no more references to object than free memory.
      if (*ref_count == 0)
        remove();
    }

    unsigned get_reference_count() const {
      return *ref_count;
    }

  private:
    void remove()
    {
      assert(*ref_count == 0);
      delete obj;
      obj = nullptr;
      delete ref_count;
      ref_count = nullptr;
    }

    T * obj;
    unsigned int * ref_count;
  };

}

class Foo {
  std::string id;

public:
  Foo(std::string name) {
    id = name;
    std::cout << "Foo - " << id << " constructor called" << std::endl;
  }

  ~Foo() {
    std::cout << "Foo - " << id << " destructor called" << std::endl;
  }
};

using namespace smart_pointer;

// Test depleting the number of references to zero.
void reference_test() {
  auto a = new SmartPointer<Foo>(new Foo("Reference test A"));
  std::cout << "Test - ref count after construct a: " << a->get_reference_count() << std::endl;
  auto b = new SmartPointer<Foo>(*a);
  std::cout << "Test - ref count after construct b: " << a->get_reference_count() << std::endl;
  auto c = new SmartPointer<Foo>(*b);
  std::cout << "Test - ref count after construct c: " << a->get_reference_count() << std::endl;

  delete c;
  std::cout << "Test - ref count after delete c: " << a->get_reference_count() << std::endl;
  delete b;
  std::cout << "Test - ref count after delete b: " << a->get_reference_count() << std::endl;
  delete a;
}

// Test pointer being created and then going out of method scope.
void scope_test() {
  auto a = SmartPointer<Foo>(new Foo("Scope test B"));
  auto b = SmartPointer<Foo>(a);
  std::cout << "Test - ref count after construct b: " << a.get_reference_count() << std::endl;
  auto c = SmartPointer<Foo>(new Foo("Scope test C"));
  std::cout << "Test - ref count after construct c: " << a.get_reference_count() << std::endl;
}

void main() {

  std::cout << std::endl << "Reference Test - Start" << std::endl;
  reference_test();
  std::cout << "Reference Test - End" << std::endl;

  std::cout << std::endl << "Scope Test - Start" << std::endl;
  scope_test();
  std::cout << "Scope Test - End" << std::endl;

  std::cout << std::endl << "[Press enter to exit]" << std::endl;
  std::cin.ignore();
}