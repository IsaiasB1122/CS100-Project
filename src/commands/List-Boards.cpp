#include <Commands.hpp>

#include <iostream>

class CommandListBoards : public Command {
public:
    std::string get_name() {
        return "list-boards";
    }
    std::string get_help() {
        return COMMAND_HELP_LIST_BOARDS;
    }
    std::vector<std::string> get_required_parameters() {return {};};
    std::vector<std::string> get_optional_parameters() {return {"filter"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "list boards" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
