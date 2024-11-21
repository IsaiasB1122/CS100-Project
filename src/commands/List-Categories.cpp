#include <Commands.hpp>

#include <iostream>

class CommandRemoveCategory : public Command {
public:
    std::string get_name() {
        return "remove-category";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_CATEGORY;
    }
    std::vector<std::string> get_required_parameters() {return {"category","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "remove category" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
