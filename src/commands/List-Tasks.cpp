#include <Commands.hpp>

#include <iostream>

class CommandListTasks : public Command {
public:
    std::string get_name() {
        return "list-tasks";
    }
    std::string get_help() {
        return COMMAND_HELP_LIST_TASKS;
    }
    std::vector<std::string> get_required_parameters() {return {"board"};};
    std::vector<std::string> get_optional_parameters() {return {"filter","category","sort"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "list tasks" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
