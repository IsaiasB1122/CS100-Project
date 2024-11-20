#include <Commands.hpp>
#include <TaskBoard.hpp>
#include <lib/file_io.hpp>
#include <lib/dir_helpers.hpp>

extern Directory dir;

class CommandRemoveCategory : public Command {
public:
    std::string get_name() {
        return "remove-category";
    }
    std::string get_help() {
        return "Removes a category from a task board.";
    }
    std::vector<std::string> get_required_parameters() { return {"category", "board"}; }
    std::vector<std::string> get_optional_parameters() { return {}; }

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Get the task board
        TaskBoard* board = get_board(dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        // Attempt to remove the category by name
        try {
            const CategoryInfo& category = board->categories.get_category(parameters.get_parameter("category"));
            board->categories.remove_category(category.id);
        } catch (const std::invalid_argument& e) {
            out << "ERROR: Category [" << parameters.get_parameter("category") << "] not found on board." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        // Write the updated task board
        FileIOManager::taskboard_write(*board);

        // Output success message
        out << "REMOVED CATEGORY " << parameters.get_parameter("category") << " from board " << board->to_string() << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};