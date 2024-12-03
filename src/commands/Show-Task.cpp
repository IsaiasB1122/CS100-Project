#include <Commands.hpp>
#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>

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
        // Resolve board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        // Resolve task
        Task task;
        try {
            task = get_task(*board,parameters.get_parameter("task"));
        }
        catch(const std::invalid_argument e)
        {
            out << "ERROR: Task [" << parameters.get_parameter("task") << "] does not exist." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        // Output
        out << task.to_string_full(*board) << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
