#include <Commands.hpp>

#include <iostream>

class CommandAddTask : public Command {
public:
    std::string get_name() {
        return "add-task";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_TASK;
    }
    std::vector<std::string> get_required_parameters() {return {"name","board"};};
    std::vector<std::string> get_optional_parameters() {return {"category"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "add task" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
