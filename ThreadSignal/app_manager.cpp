#include "app_manager.hpp"

namespace com::bosch::itrams_gen2e {
namespace appmgr {

std::unique_ptr<AppManager> AppManager::instance_;
void AppManager::Start() {
  try {
    auto someip = RegisterPlugin(
        "/home/crr4kor/code/gen2e/application_app_fix/build/lib/"
        "libtest_plugin.so");

    std::cout << "Application stated.." << std::endl;

  } catch (const std::exception& e) {
    // Handle the exception & terminate the
    // program.
    std::cout << e.what();
  }
}

/**
 * @brief It will Load the Plugin and call Init() API
 *        of plugin. Loaded Plugin must be initialize in order to work
 *        properly.
 */
std::shared_ptr<common::PluginInterface> AppManager::RegisterPlugin(
    const std::string& plugin_path) {
  std::string msg;
  common::PluginInterface* plugin = nullptr;
  plugin = LoadPlugin(plugin_path);

  if (plugin != nullptr) {
    if (!plugin->Init()) {
      // TODO :: Check the throw Exceptions, and msg log
      msg = "Failed to initialize the \'" + plugin_path + "\' plugin \n";
      std::cout << msg;
      throw std::runtime_error(msg);
    }
    msg = "Shared library " + plugin_path + " loaded\n";
    std::cout << msg;
  } else {
    msg = "The shared library \'" + plugin_path + "\' could not be loaded\n";
    std::cout << msg;
    throw std::runtime_error(msg);
  }
  // Wrap raw pointer with shared_ptr.
  std::shared_ptr<common::PluginInterface> shared_plugin;

  if (plugin != nullptr) {
    shared_plugin = std::shared_ptr<common::PluginInterface>(plugin);
    loaded_plugins_.push_back(shared_plugin);
  }
  return shared_plugin;
}

/**
 * @brief LoadPlugin will load the .so file and create the
 *        Object of loaded plugin. Plugin must has the 'Create'
 *        macro in order to create an Object.
 */
common::PluginInterface* AppManager::LoadPlugin(const std::string& so_path) {
  common::PluginInterface* loaded_plugin = nullptr;
  void* plugin = ::dlopen(so_path.c_str(), RTLD_LAZY);
  if (plugin) {
    void* fn = ::dlsym(plugin, "Create");
    if (fn) {
      auto plugin_factory =
          reinterpret_cast<common::PluginInterface::CreateFn*>(fn);
      loaded_plugin = plugin_factory();

      handles_[so_path] = plugin;
    } else {
      std::cerr << "Unable to get Plugin CreateFn : " << ::dlerror()
                << std::endl;
      ::dlclose(plugin);  // Close the opened library
      plugin = nullptr;   // Reset the plugin handle
    }
  } else {
    std::cerr << "Error opening shared library: " << ::dlerror() << std::endl;
  }
  return loaded_plugin;
}

/**
 * @brief App-Manager call the Deinit() of every plugin before terminating
 *        the application. It should be resposibility of Plugin developer
 *        to write clean-up code in Deinit and leave distructor as default.
 *        Also clear all the plugins hold by Component.
 */
void AppManager::RemoveAllPlugins() {
  // Un-intialize all the plugins, which is in reverse order of its creation.

  for (auto it = loaded_plugins_.rbegin(); it != loaded_plugins_.rend(); ++it) {
    (*it)->Deinit();
  }
  loaded_plugins_.clear();

  // Check for any working Handlers that exist.
  /*
    auto admin = common::EventAdmin::GetInstance();
    if (admin->HasActiveHandler()) {
      std::cout << "Still has active handler \n Application may not \
      terminate successfully "
                << std::endl;
    }

    // Clear the plugin refrence hold by Component, if any.
    common::Component::GetInstance()->UnregisterAllPlugins();
  */
  // Finally Unload the shared lib.
  for (const auto& plugin : handles_) {
    void* handle = plugin.second;

    // Unload the plugin using dlclose
    if (handle) {
      if (::dlclose(handle) != 0) {
        // TODO :: Need to route error msg
        std::cerr << "Error unloading shared library: " << ::dlerror()
                  << std::endl;
      } else {
        std::cout << "Library unloded :" << plugin.first << std::endl;
        // handle = nullptr;
      }
    }
  }
  // Clear the plugins map
  handles_.clear();
  std::cout << "END of RemoveAllPlugins." << std::endl;
}

}  // namespace appmgr
}  // namespace com::bosch::itrams_gen2e
