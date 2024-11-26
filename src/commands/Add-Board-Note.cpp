#include <Commands.hpp>

#include <iostream>

class CommandAddBoardNote : public Command {
public:
    std::string get_name() {
        return "add-board-note";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_BOARD_NOTE;
    }
    std::vector<std::string> get_required_parameters() {return {"title","text","author","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "add board note" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
