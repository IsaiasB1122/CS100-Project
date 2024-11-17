#include <Commands.hpp>

#define register_command(n, c) CommandManager::command_map[n] = new c;

// Include command headers here
#include <Exit.cpp>
#include <Add-Board.cpp>
#include <Remove-Board.cpp>
#include <Help.cpp>

void CommandManager::_index_commands() {
    // Include command registering here
    register_command("exit", CommandExit);
    register_command("add-board",CommandAddBoard);
    register_command("remove-board",CommandRemoveBoard);
    register_command("help", CommandOutputHelp);
}