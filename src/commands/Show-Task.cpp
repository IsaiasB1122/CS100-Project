#include <Commands.hpp>

#include <iostream>

class CommandShowTask : public Command {
public:
    std::string get_name() {
        return "show-task";
    }
    std::string get_help() {
        return COMMAND_HELP_SHOW_TASK;
    }
    std::vector<std::string> get_required_parameters() {return {"task","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "show task" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
