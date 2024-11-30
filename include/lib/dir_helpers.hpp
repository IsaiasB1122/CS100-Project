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

const Member& get_member(TaskBoard& board, std::string member) {
    // First try name
    auto members = board.members.get_members();
    for (auto c : members) {
        if (c->name == member) return *c;
    }
    // Now try as ID
    uint32_t id;
    try {
        id = std::stoul(member);
        return board.members.get_member(id);
    }
    catch (std::invalid_argument) {
        throw std::invalid_argument("");
    }
}

const Note& get_board_note(TaskBoard& board, std::string note) {
    // First try name
    auto notes = board.notes.get_notes();
    for (auto c : notes) {
        if (c->name == note) return *c;
    }
    // Now try as ID
    uint32_t id;
    try {
        id = std::stoul(note);
        return board.notes.get_note(id);
    }
    catch (std::invalid_argument) {
        throw std::invalid_argument("");
    }
}

#endif