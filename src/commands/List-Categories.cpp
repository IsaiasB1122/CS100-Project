#include <Commands.hpp>
#include <TaskBoard.hpp>
#include <lib/file_io.hpp>
#include <lib/dir_helpers.hpp>
#include <iostream>

class CommandListCategories : public Command {
public:
    std::string get_name() {
        return "list-categories";
    }
    std::string get_help() {
        return COMMAND_HELP_LIST_CATEGORIES;
    }
    std::vector<std::string> get_required_parameters() {return {"board"};};
    std::vector<std::string> get_optional_parameters() {return {"filter"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Work
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }
        const std::vector<CategoryInfo*> categories = board->get_categories();
    
        for (const auto& category : categories) {
            out << "[" << category->id << "\t" << category->name << "]" << std::endl;
        }        
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }

};
