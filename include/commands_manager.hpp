#ifndef __COMMANDS_MANAGER_HPP__
#define __COMMANDS_MANAGER_HPP__

#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>

typedef std::function<void(std::ostringstream &)> CommandAction;

class Command {
  std::string name;
  std::string hint;
  CommandAction action;

public:
  Command(std::string name, std::string hint, CommandAction action);
  ~Command() = default;

  Command(const Command &command);

  const std::string getName() const;
  const std::string getHint() const;
  void exec(std::ostringstream &output) const;
};

class CommandsManager {
  std::unordered_map<std::string, Command> commands;

public:
  CommandsManager() = default;
  ~CommandsManager() = default;

  void defineCommand(const Command &command);
  void defineCommand(const std::string &name, const std::string &hint,
                     CommandAction action);

  std::ostringstream exec(std::string command);
  bool hasCommand(const std::string &name);

  std::unordered_map<std::string, Command>::iterator begin();
  std::unordered_map<std::string, Command>::iterator end();
};

#endif // __COMMANDS_MANAGER_HPP__
