#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

class Person {
 public:
  // Constructor
  Person(const std::string& name, int age) : name(name), age(age) {}

  // Getter methods
  std::string getName() const { return name; }

  int getAge() const { return age; }

  // Setter methods
  void setName(const std::string& newName) { name = newName; }

  void setAge(int newAge) { age = newAge; }

  struct CompareById {
    bool operator()(const Person& p1, const Person& p2) const {
      return p1.getName() < p2.getName();
    }
  };

 private:
  std::string name;
  int age;
};

std::vector<Person> CreatePersons() {
  std::vector<Person> persons;

  // Create and add persons to the vector
  persons.emplace_back("Alice", 25);
  persons.emplace_back("Bob", 30);
  persons.emplace_back("Charlie", 35);

  return persons;
}

// Create a vector of persons
const std::vector<Person> persons = CreatePersons();

class PersonNotFound : public std::exception {
 public:
  const char* what() const noexcept override { return "Person not found"; }
};

std::unique_ptr<Person> fetchPerson(const std::string& nm) {
  std::unique_ptr<Person> person;
  for (const auto& p : persons) {
    if (p.getName() == nm) {
      person = std::make_unique<Person>(p);
      break;
    }
  }
  if (!person) {
    throw PersonNotFound();
  }

  return person;
}

using OptionalPesron = std::optional<Person>;

OptionalPesron fetchPersonOptional(const std::string& nm) {
  for (const auto& p : persons) {
    if (p.getName() == nm) {
      return p;
    }
  }
  return {};
}

int main() {
  std::string nameToFetch = "Alice1";
  try {
    std::unique_ptr<Person> fetchedPerson = fetchPerson(nameToFetch);
    std::cout << "Person found: " << fetchedPerson->getName() << std::endl;
  } catch (const PersonNotFound& e) {
    // Handle the exception
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  auto fetchedPerson = fetchPersonOptional(nameToFetch);

  try {
    Person p = fetchedPerson.value();
    std::cout << "Person found: " << p.getName() << std::endl;
  } catch (const std::bad_optional_access& e) {
    // Handle the exception
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
