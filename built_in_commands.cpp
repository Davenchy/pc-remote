#include "include/built_in_commands.hpp"

void BuiltInCommands::ls_command_action(std::ostringstream &output,
                                        ScriptsManager &sm) {
  for (auto it : sm)
    output << it.first << std::endl;
}

void BuiltInCommands::reload_command_action(std::ostringstream &output,
                                            ScriptsManager &sm) {
  sm.load_scripts();
}

void BuiltInCommands::help_command_action(std::ostringstream &output,
                                          CommandsManager &cm) {
  for (auto it : cm)
    output << it.first << " - " << it.second.getHint() << std::endl;
}
