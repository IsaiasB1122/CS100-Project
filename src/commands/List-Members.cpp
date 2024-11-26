#include <Commands.hpp>

#include <iostream>

class CommandListMembers : public Command {
public:
    std::string get_name() {
        return "list-members";
    }
    std::string get_help() {
        return COMMAND_HELP_LIST_MEMBERS;
    }
    std::vector<std::string> get_required_parameters() {return {"board"};};
    std::vector<std::string> get_optional_parameters() {return {"filter"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "list members" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
