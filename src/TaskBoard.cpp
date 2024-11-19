
#include <TaskBoard.hpp>

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

void TaskBoard::add_category(std::string category_name) {
    CategoryInfo new_category;
    new_category.name = category_name;
    this->categories.add_category(new_category);
    this->categories_changed = true;
}

void TaskBoard::remove_category(uint32_t category_id) {
    this->categories.remove_category(category_id);
    this->categories_changed = true;
}