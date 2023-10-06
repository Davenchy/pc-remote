#ifndef __SCRIPTS_MANAGER_HPP__
#define __SCRIPTS_MANAGER_HPP__

#include <string>
#include <unordered_map>

class Script {
  std::string name;
  std::string path;

public:
  Script() = delete;
  Script(std::string name, std::string path);
  ~Script();

  Script(const Script &);
  Script &operator=(const Script &) = delete;

  Script(Script &&);
  Script &operator=(Script &&) = delete;

  std::string get_name();
  std::string get_path();

  bool is_valid();

  int run();
};

class ScriptsManager {
  std::string scripts_path;
  std::unordered_map<std::string, Script> scripts;

public:
  ScriptsManager() = delete;
  ScriptsManager(std::string scripts_path);
  ~ScriptsManager();

  ScriptsManager(const ScriptsManager &);
  ScriptsManager &operator=(const ScriptsManager &);

  ScriptsManager(ScriptsManager &&);
  ScriptsManager &operator=(ScriptsManager &&);

  int getCount() const;

  std::string get_scripts_path();

  bool has_script(std::string script_name);

  int run_script(std::string script_name);

  void load_scripts();

  std::unordered_map<std::string, Script>::iterator begin();
  std::unordered_map<std::string, Script>::iterator end();
};

#endif // __SCRIPTS_MANAGER_HPP__
