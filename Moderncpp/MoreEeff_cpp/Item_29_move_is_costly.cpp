#include <iostream>
#include <vector>

class NoMove {
 public:
  NoMove(int data) : data(new int(data)) {}
  NoMove(const NoMove& other) : data(new int(*other.data)) {
    std::cout << "Copy constructor" << std::endl;
  }  // Copy constructor
  NoMove& operator=(const NoMove& other) {
    if (this != &other) {
      delete data;
      data = new int(*other.data);
    }
    return *this;
  }  // Copy assignment operator
  ~NoMove() { delete data; }

 private:
  int* data;
};

class MoveNotFaster {
 public:
  MoveNotFaster(int data) : data(new int(data)) {}
  MoveNotFaster(const MoveNotFaster& other)
      : data(new int(*other.data)) {}  // Copy constructor

  MoveNotFaster& operator=(const MoveNotFaster& other) {
    if (this != &other) {
      delete data;
      data = new int(*other.data);
    }
    return *this;
  }  // Copy assignment operator

  // Move constructor
  MoveNotFaster(MoveNotFaster&& other) noexcept : data(other.data) {
    other.data = nullptr;
  }

  // Move assignment operator
  MoveNotFaster& operator=(MoveNotFaster&& other) noexcept {
    if (this != &other) {
      delete data;
      data = other.data;
      other.data = nullptr;
    }
    return *this;
  }

  ~MoveNotFaster() { delete data; }

 private:
  int* data;
};

class MoveNotNoexcept {
 public:
  MoveNotNoexcept(int data) : data(new int(data)) {}
  MoveNotNoexcept(const MoveNotNoexcept& other) : data(new int(*other.data)) {
    std::cout << "Copy constructor" << std::endl;
  }  // Copy constructor

  // Move constructor not marked noexcept
  MoveNotNoexcept(MoveNotNoexcept&& other) : data(other.data) {
    other.data = nullptr;
    std::cout << "Move constructor" << std::endl;
  }

  MoveNotNoexcept& operator=(const MoveNotNoexcept& other) {
    if (this != &other) {
      delete data;
      data = new int(*other.data);
    }
    return *this;
  }  // Copy assignment operator

  // Move assignment operator not marked noexcept
  MoveNotNoexcept& operator=(MoveNotNoexcept&& other) {
    if (this != &other) {
      delete data;
      data = other.data;
      other.data = nullptr;
    }
    return *this;
  }

  ~MoveNotNoexcept() { delete data; }

 private:
  int* data;
};

class SomeClass {
 public:
  SomeClass(int data) : data(new int(data)) {}
  SomeClass(const SomeClass& other) : data(new int(*other.data)) {
    std::cout << "Copy constructor" << std::endl;
  }  // Copy constructor

  SomeClass(SomeClass&& other) noexcept : data(other.data) {
    other.data = nullptr;
  }  // Move constructor

  SomeClass& operator=(const SomeClass& other) {
    if (this != &other) {
      delete data;
      data = new int(*other.data);
    }
    return *this;
  }  // Copy assignment operator

  SomeClass& operator=(SomeClass&& other) noexcept {
    if (this != &other) {
      delete data;
      data = other.data;
      other.data = nullptr;
    }
    return *this;
  }  // Move assignment operator

  ~SomeClass() { delete data; }

 private:
  int* data;
};

void example_lval() {
  SomeClass a(10);
  SomeClass b(a);  // Copy constructor used
  b = a;           // Copy assignment used
}

void example_noexpect() {
  std::vector<MoveNotNoexcept> vec;
  MoveNotNoexcept obj(10);
  vec.push_back(
      std::move(obj));  // Falls back to copy because move is not noexcept
}

void example_non_fast() {
  MoveNotFaster a(10);
  MoveNotFaster b(std::move(a));  // Move is no faster than copy
}

void example_no_move() {
  NoMove a(10);
  NoMove b(std::move(a));  // Falls back to copy constructor
}

int main() {
  // example_no_move();
  // example_noexpect();
  example_lval();
  return 0;
}