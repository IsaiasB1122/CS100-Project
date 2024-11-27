
#include <TaskBoard.hpp>
#include <stdexcept>

TaskBoard::TaskBoard(Directory* _parent) {
    this->parent = _parent;
    this->tasks_changed = true;
    this->members_changed = true;
    this->notes_changed = true;
    this->categories_changed = true;
    this->next_task_id = 0;
}

TaskBoard::~TaskBoard() {
    for (auto task : tasks) {
        delete task;
    }
}

const Task& TaskBoard::add_task(std::string name, uint32_t category) {
    Task* new_task = new Task;
    
    new_task->id = this->next_task_id;

    new_task->name = name;
    new_task->category_id = category;
    new_task->changed = true;
    std::time(&new_task->creation_time);
    std::time(&new_task->modified_time);

    this->tasks.push_back(new_task);
    this->tasks_changed = true;

    this->next_task_id += 1;

    return *new_task;
}


void TaskBoard::remove_task(uint32_t id) {
    for (auto it = tasks.begin(); it < tasks.end(); it += 1) {
        if ((*it)->id == id)
        {
            Task* tp = *it;
            tasks.erase(it);
            delete tp;
            return;
        }
    }
    throw std::logic_error("Bad call to remove_task on missing id");
}

const std::vector<Task*> TaskBoard::get_tasks() {
    return tasks;
}

const Task& TaskBoard::get_task(uint32_t id) {
    for (auto it = tasks.begin(); it < tasks.end(); it += 1) {
        if ((*it)->id == id)
        {
            return **it;
        }
    }
    throw std::invalid_argument("");
}

const Task& TaskBoard::get_task(std::string name) {
    for (auto it = tasks.begin(); it < tasks.end(); it += 1) {
        if ((*it)->name == name)
        {
            return **it;
        }
    }
    throw std::invalid_argument("");
}

const CategoryInfo& TaskBoard::add_category(std::string name) {
    CategoryInfo new_category;
    new_category.name = name;
    const CategoryInfo& added_category = categories.add_category(new_category);

    categories_changed = true; // Mark as modified
    return added_category;
}

void TaskBoard::remove_category(uint32_t id) {
    categories.remove_category(id);

    categories_changed = true; // Mark as modified
}