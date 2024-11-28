#ifndef DIR_HELPERS_HPP
#define DIR_HELPERS_HPP


#include <Directory.hpp>
#include <stdexcept>

TaskBoard* get_board(Directory& dir, std::string board) {
    // First try board as string name
    auto boards = dir.get_boards();
    for (auto b : boards) {
        if (b->name == board) return b;
    }
    // Now try as ID
    uint32_t id;
    try {
        id = std::stoul(board);
        return dir.get_board(id);
    }
    catch (std::invalid_argument) {
        return nullptr;
    }
}

const Task& get_task(TaskBoard& board, std::string task) {
    // First try name
    auto tasks = board.get_tasks();
    for (auto t : tasks) {
        if (t->name == task) return *t;
    }
    // Now try as ID
    uint32_t id;
    try {
        id = std::stoul(task);
        return board.get_task(id);
    }
    catch (std::invalid_argument) {
        throw std::invalid_argument("");
    }
}

const CategoryInfo& get_category(TaskBoard& board, std::string category) {
    // First try name
    auto categories = board.categories.get_categories();
    for (auto c : categories) {
        if (c->name == category) return *c;
    }
    // Now try as ID
    uint32_t id;
    try {
        id = std::stoul(category);
        return board.categories.get_category(id);
    }
    catch (std::invalid_argument) {
        throw std::invalid_argument("");
    }
}



#endif