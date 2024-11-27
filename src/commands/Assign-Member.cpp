#include <Commands.hpp>

#include <iostream>

class CommandAssignMember : public Command {
public:
    std::string get_name() {
        return "assign-member";
    }
    std::string get_help() {
        return COMMAND_HELP_ASSIGN_MEMBER;
    }
    std::vector<std::string> get_required_parameters() {return {"task","member","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "assign member" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};