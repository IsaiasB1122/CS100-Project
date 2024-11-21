#include <Commands.hpp>

#include <iostream>

class CommandCategorizeTask : public Command {
public:
    std::string get_name() {
        return "categorize-task";
    }
    std::string get_help() {
        return COMMAND_HELP_CATEGORIZE_TASK;
    }
    std::vector<std::string> get_required_parameters() {return {"name","category","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "categorize task" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
