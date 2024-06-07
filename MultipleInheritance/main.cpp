
#include "superhuman.hpp"

// DummyPlugin ->  SuperHuman
// PluginInterface -> IAnimal
// EventHandler -> IPerson
// EventAdmin -> Loin

void foo(SuperHuman h) { h.Runner(); }

int main() {
  // SuperHuman *rajeev = new  SuperHuman();
  // std::shared_ptr<SuperHuman> plugin(rajeev);
  // plugin->Runner();
  // plugin->QuickThinker();

  SuperHuman h1;
  foo(std::move(h1));
  return 0;
}
