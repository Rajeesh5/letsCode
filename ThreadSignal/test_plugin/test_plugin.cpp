#include "test_plugin.hpp"

#include <iostream>

namespace com::bosch::itrams_gen2e {
namespace test_plugins {

ITRAMS_GEN2E_PLUGIN(TestPlugin);

bool TestPlugin::Init() {
  wasInitCalled_ = true;
  return wasInitCalled_;
}
void TestPlugin::Deinit() { wasDeinitCalled_ = true; }

bool TestPlugin::WasInitCalled() const { return wasInitCalled_; };
bool TestPlugin::WasDeinitCalled() const { return wasDeinitCalled_; }

}  // namespace test_plugins
}  // namespace com::bosch::itrams_gen2e