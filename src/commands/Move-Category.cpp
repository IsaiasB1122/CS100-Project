#include <Commands.hpp>

#include <iostream>

class CommandMoveCategory : public Command {
public:
    std::string get_name() {
        return "move-category";
    }
    std::string get_help() {
        return COMMAND_HELP_MOVE_CATEGORY;
    }
    std::vector<std::string> get_required_parameters() {return {"category","position","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "move category" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
