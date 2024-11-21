#include <Commands.hpp>

#include <iostream>

class CommandShowBoardNote : public Command {
public:
    std::string get_name() {
        return "show-board-note";
    }
    std::string get_help() {
        return COMMAND_HELP_SHOW_BOARD_NOTE;
    }
    std::vector<std::string> get_required_parameters() {return {"note","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "show board note" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
