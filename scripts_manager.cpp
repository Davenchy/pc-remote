#include "include/scripts_manager.hpp"
#include "include/directory_reader.hpp"
#include <stdexcept>
#include <sys/stat.h>

ScriptsManager::ScriptsManager(std::string scripts_path)
    : scripts_path(scripts_path){};

ScriptsManager::~ScriptsManager() {}

std::string ScriptsManager::get_scripts_path() { return scripts_path; }

bool ScriptsManager::has_script(std::string script_name) {
  return scripts.find(script_name) != scripts.end();
}

int ScriptsManager::run_script(std::string script_name) {
  auto pair = scripts.find(script_name);
  int status = 0;

  if (pair == scripts.end())
    throw std::runtime_error("Script not found: " + script_name);
  Script &script = pair->second;
  status = script.run();

  return status;
}

void ScriptsManager::load_scripts() {
  DirectoryReader dr(scripts_path);
  std::vector<std::string> files = dr.get_files();

  scripts.clear();
  for (auto file : files) {
    Script s(file, scripts_path + "/" + file);
    if (s.is_valid()) {
      scripts.insert({s.get_name(), std::move(s)});
    }
  }
}

std::unordered_map<std::string, Script>::iterator ScriptsManager::begin() {
  return scripts.begin();
}

std::unordered_map<std::string, Script>::iterator ScriptsManager::end() {
  return scripts.end();
}
