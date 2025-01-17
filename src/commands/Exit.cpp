#include <Commands.hpp>

class CommandExit : public Command {
public:
    std::string get_name() {
        return "exit";
    }
    std::string get_help() {
        return COMMAND_HELP_EXIT;
    }
    std::vector<std::string> get_required_parameters() {return {};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
       this->parent->exit = true;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
