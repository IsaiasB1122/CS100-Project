#include <Commands.hpp>
#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>

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
        // Resolve board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        // Resolve category
        uint32_t category_id = 0;
        if (parameters.has_parameter("category")) {
            try {
                category_id = get_category(*board,parameters.get_parameter("category")).id;
            }
            catch(const std::invalid_argument e)
            {
                out << "ERROR: Category [" << parameters.get_parameter("category") << "] does not exist." << std::endl;
                return CommandManager::COMMAND_RUN_RESULT::ERROR;
            }
        }
        // Add task
        Task task = board->add_task(parameters.get_parameter("name"),category_id);
        // Write
        FileIOManager::taskboard_write(*board);
        // Output
        out << "ADD TASK " << task.to_string(*board) << std::endl; 
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
