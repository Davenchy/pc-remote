#ifndef __BUILT_IN_COMMANDS_HPP__
#define __BUILT_IN_COMMANDS_HPP__

#include "commands_manager.hpp"
#include "scripts_manager.hpp"
#include <sstream>

namespace BuiltInCommands {
void ls_command_action(std::ostringstream &output, ScriptsManager &sm);
void reload_command_action(std::ostringstream &output, ScriptsManager &sm);
void help_command_action(std::ostringstream &output, CommandsManager &cm);
} // namespace BuiltInCommands

#endif // __BUILT_IN_COMMANDS_HPP__
