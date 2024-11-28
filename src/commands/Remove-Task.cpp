#include <Commands.hpp>
#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>

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
        // Resolve board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        // Resolve task
        uint32_t task_id = 0;
        try {
            task_id = get_task(*board,parameters.get_parameter("task")).id;
        }
        catch(const std::invalid_argument e)
        {
            out << "ERROR: Task [" << parameters.get_parameter("task") << "] does not exist." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }
        // Save this for output
        std::string task_string = board->get_task(task_id).to_string(*board);
        // Remove task
        board->remove_task(task_id);
        // Write
        FileIOManager::taskboard_write(*board);
        // Output
        out << "REMOVE TASK " << task_string << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
