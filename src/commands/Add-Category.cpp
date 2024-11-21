#include <Commands.hpp>

#include <iostream>

class CommandAddCategory : public Command {
public:
    std::string get_name() {
        return "add-category";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_CATEGORY;
    }
    std::vector<std::string> get_required_parameters() {return {"name","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "add category" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
