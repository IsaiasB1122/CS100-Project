#include <Commands.hpp>

#define register_command(n) CommandManager::command_map[#n] = new Command_##n;

// Include command headers here
#include <Exit.cpp>

void CommandManager::_index_commands() {
    // Include command registering here
    register_command(exit);
}