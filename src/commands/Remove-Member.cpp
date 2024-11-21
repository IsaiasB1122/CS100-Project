#include <Commands.hpp>

#include <iostream>

class CommandRemoveMember : public Command {
public:
    std::string get_name() {
        return "remove-member";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_MEMBER;
    }
    std::vector<std::string> get_required_parameters() {return {"member","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "remove member" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
