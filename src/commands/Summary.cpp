#include <Commands.hpp>

#include <lib/dir_helpers.hpp>
#include <lib/summary.hpp>
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
    std::vector<std::string> get_optional_parameters() {return {"start","end","limit"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Resolve board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        unsigned int start = 0;
        unsigned int end = -1;
        unsigned int limit = -1;

        if (parameters.has_parameter("start")) start = std::stoi(parameters.get_parameter("start")) - 1;
        if (parameters.has_parameter("end")) end = std::stoi(parameters.get_parameter("end"));
        if (parameters.has_parameter("limit")) limit = std::stoi(parameters.get_parameter("limit"));

        print_summary(out,*board,start,end,limit);

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
