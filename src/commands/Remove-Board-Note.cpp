#include <Commands.hpp>

#include <iostream>

class CommandRemoveBoardNote : public Command {
public:
    std::string get_name() {
        return "remove-board-note";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_BOARD_NOTE;
    }
    std::vector<std::string> get_required_parameters() {return {"note","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "remove board note" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
