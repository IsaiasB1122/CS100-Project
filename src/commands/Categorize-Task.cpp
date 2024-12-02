#include <Commands.hpp>
#include <TaskBoard.hpp>
#include <lib/file_io.hpp>
#include <lib/dir_helpers.hpp>
#include <iostream>

class CommandCategorizeTask : public Command {
public:
    std::string get_name() {
        return "categorize-task";
    }
    std::string get_help() {
        return COMMAND_HELP_CATEGORIZE_TASK;
    }
    std::vector<std::string> get_required_parameters() {return {"name","category","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
    if (board == nullptr) {
        out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::ERROR; 
    }
    const Task* task = nullptr;
    
    try {
        if (parameters.has_parameter("task")) {
            uint32_t task_id = std::stoi(parameters.get_parameter("task"));
            task = &board->get_task(task_id);
        } else if (parameters.has_parameter("name")) {
            task = &board->get_task(parameters.get_parameter("name"));
        } else {
            throw std::invalid_argument("Task name or ID is required.");
        }
    } catch (const std::invalid_argument&) {
        out << "ERROR: Task \"" << parameters.get_parameter("name") << "\" not found on board." << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::ERROR;
    }

    // Get the category
    CategoryInfo* category = nullptr;
    const std::vector<CategoryInfo*> categories = board->get_categories();
    for (auto& cat : categories) {
        if (cat->name == parameters.get_parameter("category") || 
            std::to_string(cat->id) == parameters.get_parameter("category")) {
            category = cat;
            break;
        }
    }

    if (category == nullptr) {
        out << "ERROR: Category \"" << parameters.get_parameter("category") 
            << "\" does not match any Category name or ID of board [" 
            << board->get_categories().size() << "\t" << parameters.get_parameter("board") << "]." << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::ERROR;
    }
    
    std::string old_category_name = board->categories.get_category(task->category_id).name;

    // Update the task's category
    uint32_t old_category_id = task->category_id;
    board->move_task(task->id, category->id);

    // Generate output
    out << "CATEGORIZE TASK" << task->to_string(*board) << " " << old_category_name << "-->" << category->name << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
