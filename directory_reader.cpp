#include "include/directory_reader.hpp"
#include <cstring>
#include <dirent.h>
#include <stdexcept>
#include <string>
#include <sys/stat.h>

DirectoryReader::DirectoryReader(std::string path) : path(path) {
  struct stat st {};

  if (stat(path.c_str(), &st) != 0)
    if (mkdir(path.c_str(), 0776))
      throw std::runtime_error(std::string("Failed to create directory: ") +
                               std::strerror(errno));

  dir = opendir(path.c_str());
  if (dir == nullptr)
    throw std::runtime_error(std::string("Failed to open directory: ") +
                             std::strerror(errno));
}

DirectoryReader::~DirectoryReader() {
  if (dir != nullptr)
    closedir(dir);
}

std::string DirectoryReader::get_path() { return path; }

std::vector<std::string> DirectoryReader::get_files() {
  std::vector<std::string> files;
  dirent *entry = nullptr;

  for (entry = readdir(dir); entry != nullptr; entry = readdir(dir))
    files.push_back(entry->d_name);
  return files;
}
