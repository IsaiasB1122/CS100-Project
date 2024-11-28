#include <Commands.hpp>
#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>

#include <iostream>

class CommandListTasks : public Command {
public:
    std::string get_name() {
        return "list-tasks";
    }
    std::string get_help() {
        return COMMAND_HELP_LIST_TASKS;
    }
    std::vector<std::string> get_required_parameters() {return {"board"};};
    std::vector<std::string> get_optional_parameters() {return {"filter","category","sort"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Resolve board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }

        std::vector<Task*> tasks;
        DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE;
        // Resolve sort
        if (parameters.has_parameter("sort")) {
            std::string in_sort = "";
            for (auto c : parameters.get_parameter("sort")) in_sort.push_back(std::tolower(c));

            if (in_sort == "id") sort = DataEntry::SORT_TYPE::ID;
            else if (in_sort == "recent") sort = DataEntry::SORT_TYPE::MODIFIED;
        }
        // Filter
        std::string filter = "";
        if (parameters.has_parameter("filter") or sort != DataEntry::SORT_TYPE::NONE) {
            filter = parameters.get_parameter("filter");
            tasks = board->filter_task_name(filter, sort);
        }
        else tasks = board->get_tasks();
        // Filter category
        if (parameters.has_parameter("category")) {
            const std::string categoryParameter = parameters.get_parameter("category"); 
            try {
                const CategoryInfo& category = get_category(*board, categoryParameter);
                std::vector<Task*> tasks_category_filtered;

                for (auto task : tasks) {
                    if (task->category_id == category.id) {
                        tasks_category_filtered.push_back(task);
                    }
                }
                tasks = tasks_category_filtered;
            } catch(const std::exception& e) {
                out << "No tasks in board that have category: " << categoryParameter <<  std::endl;
                return CommandManager::COMMAND_RUN_RESULT::ERROR;
            }
        }
        // Out
        for (auto t : tasks) {
            out << t->to_string(*board) << std::endl;
        }

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
