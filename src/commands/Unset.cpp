#include <Commands.hpp>

#include <iostream>

class CommandUnset : public Command {
public:
    std::string get_name() {
        return "set";
    }
    std::string get_help() {
        return COMMAND_HELP_UNSET;
    }
    std::vector<std::string> get_required_parameters() {return {"name"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        parent->unset_parameter(parameters.get_parameter("name"));
        out << parameters.get_parameter("name") << " unset" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
