#ifndef COM_BOSCH_COMMON_ITRAMS_APP_MANAGER_H_
#define COM_BOSCH_COMMON_ITRAMS_APP_MANAGER_H_

#include <dlfcn.h>

#include <condition_variable>
#include <csignal>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include <utility>
#include <vector>

#include "plugin_interface.hpp"

namespace com::bosch::itrams_gen2e {
namespace appmgr {

#define DISALLOW_COPY_AND_ASSIGN_APP_MGR(ClassName) \
  ClassName(const ClassName&) = delete;             \
  ClassName& operator=(const ClassName&) = delete;

#define DISALLOW_MOVE_AND_ASSIGN_APP_MGR(ClassName) \
  ClassName(const ClassName&&) = delete;            \
  ClassName& operator=(const ClassName&&) = delete;

class AppManager final {
 public:
  /**
   * @brief Singleton class
   * @return Instance of AppManeger
   */
  static AppManager& GetInstance() {
    if (instance_ == nullptr) {
      instance_.reset(new AppManager());
    }
    return *instance_;
  }

  /**
   * @brief main will only call start call.
   *        All Plugins should be intialize here.
   * @return void
   */
  void Start();

  /**
   * @brief It will not only register the pugins, but will load the
   *        plugin so and call the factory method 'Create' to construct
   *        the object.
   * @return Return the shared pointer of base abstract class of loaded
   *        plugin.
   */
  std::shared_ptr<common::PluginInterface> RegisterPlugin(
      const std::string& plugin_path);

  DISALLOW_COPY_AND_ASSIGN_APP_MGR(AppManager);
  DISALLOW_MOVE_AND_ASSIGN_APP_MGR(AppManager);

  ~AppManager() = default;
  void RemoveAllPlugins();

 private:
  AppManager() = default;

  static std::unique_ptr<AppManager> instance_;
  std::map<const std::string, void*, std::less<>> handles_;
  std::vector<std::shared_ptr<common::PluginInterface>> loaded_plugins_;

  common::PluginInterface* LoadPlugin(const std::string& so_path);
};
}  // namespace appmgr
}  // namespace com::bosch::itrams_gen2e
#endif  // COM_BOSCH_COMMON_ITRAMS_APP_MANAGER_H_
