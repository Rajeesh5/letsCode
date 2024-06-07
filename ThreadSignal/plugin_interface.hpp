#ifndef COM_BOSCH_COMMON_ITRAMS_PLUGIN_H_
#define COM_BOSCH_COMMON_ITRAMS_PLUGIN_H_

#include <string>

namespace com::bosch::itrams_gen2e {
namespace common {

#define ITRAMS_GEN2E_PLUGIN(T)                           \
  extern "C" common::PluginInterface* Create() {         \
    return static_cast<common::PluginInterface*>(new T); \
  }

#define DISALLOW_COPY_AND_ASSIGN_PLUGIN(ClassName) \
  ClassName(const ClassName&) = delete;            \
  ClassName& operator=(const ClassName&) = delete;

#define DISALLOW_MOVE_AND_ASSIGN_PLUGIN(ClassName) \
  ClassName(const ClassName&&) = delete;           \
  ClassName& operator=(const ClassName&&) = delete;

class PluginInterface {
 public:
  /**
   * @note About CreateFn
   *
   * Function with no parameters returning a pointer to PluginInterface.
   * CreateFn type alias which is used in App-Manager as a factoty
   * method for every plugin.
   */

  using CreateFn = PluginInterface*();

  /**
   * @brief Entry point of plugin
   *
   *  Once Plugin get created properly, App-Manager will trigger
   *  activate API of releted plugin.
   */
  virtual void Activate() {
    // Provided default Implementation blank.
    // Plugin can override based on requirement.
  }

  /**
   * @brief Initialize the plugin
   *
   * The return value is checked by the AppManager
   * to verify that the plugin has been correctly created.
   */
  virtual bool Init() = 0;

  /**
   * @brief Distruct the plugin
   *
   *  Write a logic to distruct the plugins.
   */
  virtual void Deinit() = 0;

  virtual ~PluginInterface() = default;

  /**
   * @brief Return the version of the plugin interface used
   */
  std::string GetVersion() const { return "1.0"; }
};

}  // namespace common
}  // namespace com::bosch::itrams_gen2e
#endif  // COM_BOSCH_COMMON_ITRAMS_PLUGIN_H_
