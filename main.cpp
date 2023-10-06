#include "include/network.hpp"
#include "include/scripts_manager.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>

static void trim(std::string &s) {
  s.erase(s.begin(), std::find_if_not(s.begin(), s.end(),
                                      [](char c) { return std::isspace(c); }));
  s.erase(std::find_if_not(s.rbegin(), s.rend(),
                           [](char c) { return std::isspace(c); })
              .base(),
          s.end());
}

int getPort(int defaultPort) {
  char *port = std::getenv("PC_REMOTE_PORT");
  if (port)
    return std::atoi(port);
  else
    return defaultPort;
}

std::string getScriptsPath(std::string defaultScriptsPath) {
  char *path = std::getenv("PC_REMOTE_SCRIPTS_PATH");
  if (path)
    return std::string(path);
  else
    return defaultScriptsPath;
}

int main() {
  Server server(getPort(5050));
  ScriptsManager sm(getScriptsPath("remote_scripts/"));

  sm.load_scripts();

  std::cout << "server running on port: " << server.getPort() << std::endl;

  int client_fd = server.accept();
  Client &client = server.getClient(client_fd);

  while (true) {
    client.send("> ");
    std::string script_name = client.recv();
    trim(script_name);

    if (script_name == "")
      continue;
    if (script_name == "q") {
      std::cout << "!> quit" << std::endl;
      client.send("!> byebye\n");
      break;
    }

    if (script_name == "help") {
      client.send("!> help\n");
      client.send("");
    }

    if (script_name == "reload") {
    }

    if (script_name == "ls") {
      std::cout << "!> ls" << std::endl;
      client.send("!> ls\n");
      continue;
    }

    if (!sm.has_script(script_name)) {
      std::cout << "!> script not found: " << script_name << std::endl;
      client.send("!> Script not found: " + script_name + '\n');
      continue;
    }

    std::cout << "!> script: " << script_name << std::endl;
    client.send("!> Executing script: " + script_name + '\n');
    sm.run_script(script_name);
  }

  return 0;
}
