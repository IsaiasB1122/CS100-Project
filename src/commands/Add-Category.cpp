#include <Commands.hpp>

#include <iostream>
#include <TaskBoard.hpp>
#include <lib/file_io.hpp>
#include <lib/dir_helpers.hpp>

class CommandAddCategory : public Command {
public:
    std::string get_name() {
        return "add-category";
    }

    std::string get_help() {
        return COMMAND_HELP_ADD_CATEGORY;
    }
  
    std::vector<std::string> get_required_parameters() {return {"name","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Work
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        // Add the category to the board
        const CategoryInfo& category = board->add_category(parameters.get_parameter("name"));

        // Write the updated task board
        FileIOManager::taskboard_write(*board);

        // Output with corrected format
        out << "NEW CATEGORY " << category.id << " " << category.name << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};