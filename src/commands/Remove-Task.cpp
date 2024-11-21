#include <Commands.hpp>

#include <iostream>

class CommandRemoveTask : public Command {
public:
    std::string get_name() {
        return "remove-task";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_TASK;
    }
    std::vector<std::string> get_required_parameters() {return {"task","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "remove task" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
