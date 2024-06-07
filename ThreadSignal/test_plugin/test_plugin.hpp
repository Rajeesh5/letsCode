
#ifndef TEST1_PLUGIN_HPP
#define TEST1_PLUGIN_HPP

#include "plugin_interface.hpp"

namespace com::bosch::itrams_gen2e {
namespace test_plugins {

class TestPlugin : public common::PluginInterface {
 public:
  TestPlugin() = default;
  ~TestPlugin() override = default;

  bool Init() override;
  void Deinit() override;
  bool WasInitCalled() const;
  bool WasDeinitCalled() const;

 private:
  bool wasInitCalled_ = false;
  bool wasDeinitCalled_ = false;
};
}  // namespace test_plugins
}  // namespace com::bosch::itrams_gen2e
#endif  // TEST_PLUGIN_HPP