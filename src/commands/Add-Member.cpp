#include <Commands.hpp>

#include <iostream>

class CommandAddMember : public Command {
public:
    std::string get_name() {
        return "add-member";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_MEMBER;
    }
    std::vector<std::string> get_required_parameters() {return {"name","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "add member" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};