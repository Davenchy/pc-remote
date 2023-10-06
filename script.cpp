#include "include/scripts_manager.hpp"
#include <sys/stat.h>

Script::Script(std::string name, std::string path) : name(name), path(path) {}
Script::~Script() {}

Script::Script(const Script &other) {
  name = other.name;
  path = other.path;
}

Script::Script(Script &&other) {
  name = other.name;
  path = other.path;

  other.name.clear();
  other.path.clear();
}

bool Script::is_valid() {
  struct stat st {};

  if (!::stat(path.c_str(), &st) && S_ISREG(st.st_mode) &&
      (st.st_mode & S_IXUSR))
    return true;
  return false;
}

std::string Script::get_name() { return name; }
std::string Script::get_path() { return path; }

int Script::run() { return system(path.c_str()); }
