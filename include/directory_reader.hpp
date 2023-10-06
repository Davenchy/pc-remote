#ifndef __DIRECTORY_READER_HPP__
#define __DIRECTORY_READER_HPP__

#include <dirent.h>
#include <string>
#include <vector>

class DirectoryReader {
  std::string path;
  DIR *dir = nullptr;

public:
  DirectoryReader() = delete;
  DirectoryReader(std::string path);
  ~DirectoryReader();

  DirectoryReader(const DirectoryReader &) = delete;
  DirectoryReader &operator=(const DirectoryReader &) = delete;

  DirectoryReader(DirectoryReader &&) = delete;
  DirectoryReader &operator=(DirectoryReader &&) = delete;

  std::string get_path();
  std::vector<std::string> get_files();
};

#endif // __DIRECTORY_READER_HPP__
