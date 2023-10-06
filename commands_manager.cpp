#include "include/commands_manager.hpp"

// Command //
Command::Command(std::string name, std::string hint, CommandAction action)
    : name(name), hint(hint), action(action) {}
Command::Command(const Command &command) {
  name = command.name;
  hint = command.hint;
  action = command.action;
}

const std::string Command::getName() const { return name; }
const std::string Command::getHint() const { return hint; }
void Command::exec(std::ostringstream &output) const { action(output); }

// Commands Manager //
void CommandsManager::defineCommand(const Command &command) {
  commands.insert({command.getName(), command});
}

void CommandsManager::defineCommand(const std::string &name,
                                    const std::string &hint,
                                    CommandAction action) {
  Command command(name, hint, action);
  defineCommand(command);
}

bool CommandsManager::hasCommand(const std::string &name) {
  return commands.find(name) != commands.end();
}

std::ostringstream CommandsManager::exec(std::string command) {
  std::ostringstream output;
  auto it = commands.find(command);

  if (it != commands.end())
    it->second.exec(output);

  return output;
}

std::unordered_map<std::string, Command>::iterator CommandsManager::begin() {
  return commands.begin();
}

std::unordered_map<std::string, Command>::iterator CommandsManager::end() {
  return commands.end();
}
