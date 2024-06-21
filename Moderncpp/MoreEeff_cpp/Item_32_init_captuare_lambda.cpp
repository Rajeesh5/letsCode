#include <iostream>
#include <memory>

class Widget {
 public:
  bool isValidated() const;
  bool isProcessed() const;
  bool isArchived() const;
};

int main() {
  auto pw = std::make_unique<Widget>();  // Create a Widget
  // ... configure *pw ...

  auto func = [pwc = std::move(pw)]  // init capture
  { return pwc->isValidated() && pwc->isArchived(); };

  auto func = [pw = std::make_unique<Widget>()]  // init capture
  { return pw->isValidated() && pw->isArchived(); };
}