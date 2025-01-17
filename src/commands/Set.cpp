#include <Commands.hpp>

#include <iostream>

class CommandSet : public Command {
public:
    std::string get_name() {
        return "set";
    }
    std::string get_help() {
        return COMMAND_HELP_SET;
    }
    std::vector<std::string> get_required_parameters() {return {};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        auto pairs = parameters.get_named_parameter_pairs();
        for (auto p : pairs) {
            this->parent->set_parameter(p.first, p.second);
            out << p.first << " = " << p.second << std::endl;
        }
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
