#include <Commands.hpp>

#include <iostream>

class CommandListBoardNotes : public Command {
public:
    std::string get_name() {
        return "list-board-notes";
    }
    std::string get_help() {
        return COMMAND_HELP_LIST_BOARD_NOTES;
    }
    std::vector<std::string> get_required_parameters() {return {"board",};};
    std::vector<std::string> get_optional_parameters() {return {"filter","sort","full"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "list board notes" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
