#include <Commands.hpp>

#include <iostream>

class CommandSummary : public Command {
public:
    std::string get_name() {
        return "summary";
    }
    std::string get_help() {
        return COMMAND_HELP_SUMMARY;
    }
    std::vector<std::string> get_required_parameters() {return {"board"};};
    std::vector<std::string> get_optional_parameters() {return {"start","end"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        out << "summary" << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
