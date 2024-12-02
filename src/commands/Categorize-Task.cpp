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
    std::vector<std::string> get_required_parameters() {return {"task","category","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
    if (board == nullptr) {
        out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::ERROR; 
    }
    const Task* task = nullptr;
    
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
    task = &board->get_task(task_id);

    // Get the category
    const CategoryInfo* category = nullptr;
    const std::vector<CategoryInfo*> categories = board->get_categories();
    for (auto& cat : categories) {
        if (cat->name == parameters.get_parameter("category") || 
            std::to_string(cat->id) == parameters.get_parameter("category")) {
            category = cat;
            break;
        }
    }
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
    category = &board->categories.get_category(category_id);
    
    std::string old_category_name = board->categories.get_category(task->category_id).name;

    // Update the task's category
    uint32_t old_category_id = task->category_id;
    board->move_task(task->id, category->id);

    // Write
    FileIOManager::taskboard_write(*board);

    // Generate output
    out << "CATEGORIZE TASK " << task->to_string(*board) << " " << old_category_name << "-->" << category->name << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
