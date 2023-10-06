#include "include/built_in_commands.hpp"
#include "include/commands_manager.hpp"
#include "include/network.hpp"
#include "include/scripts_manager.hpp"
#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <linux/limits.h>
#include <sstream>

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

std::string getScriptsPath(const char *defaultScriptsPath) {
  char *path = nullptr, fullpath[PATH_MAX];

  path = std::getenv("PC_REMOTE_SCRIPTS_PATH");
  if (path != nullptr)
    return std::string(path);

  path = std::getenv("XDG_CONFIG_HOME");
  if (path != nullptr)
    goto find_realpath;
  path = std::getenv("HOME");
  if (path != nullptr)
    goto find_realpath;

  throw std::runtime_error("Please set PC_REMOTE_SCRIPTS_PATH or "
                           "XDG_CONFIG_HOME or HOME");

find_realpath:
  realpath(path, fullpath);
  std::string ret(fullpath);
  return ret + "/remote_scripts/";
}

int main() {
  Server server(getPort(5050));
  ScriptsManager sm(getScriptsPath("~/.config/remote_scripts"));
  CommandsManager cm;

  std::cout << "loading scripts: " << sm.get_scripts_path() << std::endl;
  sm.load_scripts();

  cm.defineCommand("ls", "list all loaded scripts",
                   [&sm](std::ostringstream &output) {
                     BuiltInCommands::ls_command_action(output, sm);
                   });

  cm.defineCommand("reload", "reload all scripts",
                   [&sm](std::ostringstream &output) {
                     BuiltInCommands::reload_command_action(output, sm);
                   });

  cm.defineCommand("help", "list all commands",
                   [&cm](std::ostringstream &output) {
                     BuiltInCommands::help_command_action(output, cm);
                   });

  std::cout << "server running on port: " << server.getPort() << std::endl;

  int client_fd = server.accept();
  Client &client = server.getClient(client_fd);

  while (true) {
    client.send("> ");
    std::string script_name = client.recv();
    trim(script_name);

    if (script_name == "")
      continue;
    if (script_name == "q")
      break;

    if (cm.hasCommand(script_name)) {
      std::ostringstream stream = cm.exec(script_name);
      client.send(stream.str());
      continue;
    }

    if (sm.has_script(script_name)) {
      std::cout << "!> script: " << script_name << std::endl;
      client.send("!> Executing script: " + script_name + '\n');
      sm.run_script(script_name);
      continue;
    }

    std::cout << "!> script not found: " << script_name << std::endl;
    client.send("!> Script not found: " + script_name + '\n');
  }

  server.shutdown();

  return 0;
}
