#include <Commands.hpp>
#include <TaskBoard.hpp>
#include <lib/file_io.hpp>
#include <lib/dir_helpers.hpp>
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
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        uint32_t new_position = std::stoul(parameters.get_parameter("position")) - 1; // Convert to 0-based index

        try {
            // Resolve category
            uint32_t category_id = 0;
            try {
                category_id = get_category(*board,parameters.get_parameter("category")).id;
            }
            catch(const std::invalid_argument e)
            {
                out << "ERROR: Category [" << parameters.get_parameter("category") << "] does not exist." << std::endl;
                return CommandManager::COMMAND_RUN_RESULT::ERROR;
            }
            const CategoryInfo& category = board->categories.get_category(category_id);
            uint32_t old_position = board->categories.move_category(category_id, new_position) + 1;

            out << "MOVE CATEGORY " << category.to_string() << " #" << old_position << " --> #" << new_position + 1 << std::endl;

            board->categories_changed = true;
            FileIOManager::taskboard_write(*board);  // Save changes
        } 
        catch (const std::out_of_range&) {
            out << "ERROR: Category #" << new_position + 1 << " out of range. (board " << board->to_string() 
            << " only has " << board->categories.get_categories().size() << " categories)" << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        } 
        catch (const std::exception& e) {
            out << "ERROR: " << e.what() << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};