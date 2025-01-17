#include <Commands.hpp>

#include <iostream>
#include <TaskBoard.hpp>
#include <lib/file_io.hpp>
#include <lib/dir_helpers.hpp>

class CommandRemoveCategory : public Command {
public:
    std::string get_name() {
        return "remove-category";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_CATEGORY;
    }
    std::vector<std::string> get_required_parameters() {return {"category","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Work
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        
        // Attempt to remove the category by name
        try {
            const CategoryInfo& category = board->categories.get_category(parameters.get_parameter("category"));
            
            if (category.id == 0) {
            out << "ERROR: Category ID 0 cannot be removed." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        std::string category_string = category.to_string();

        board->categories.remove_category(category.id);
        
           // Output success message with category info
           out << "REMOVE CATEGORY " << category_string << std::endl;
        }
        catch (const std::invalid_argument&) {
			// If category is not found by name, attempt removal by ID
			try {
				uint32_t id = std::stoul(parameters.get_parameter("category"));
				const CategoryInfo& category = board->categories.get_category(id);

                if (category.id == 0) {
                out << "ERROR: Category ID 0 cannot be removed." << std::endl;
                return CommandManager::COMMAND_RUN_RESULT::ERROR;
            }

                std::string category_string = category.to_string();
				board->categories.remove_category(category.id);

            // Output success message with category info
            out << "REMOVE CATEGORY " << category_string << std::endl;
        } catch (const std::invalid_argument&) {
            out << "ERROR: Category " << parameters.get_parameter("category") << " not found on board." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }
    }

		// Write the updated task board
        board->categories_changed = true;
		FileIOManager::taskboard_write(*board);

		return CommandManager::COMMAND_RUN_RESULT::GOOD;
		}
};
