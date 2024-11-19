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

TaskCategory* get_category(Directory& dir, std::string category) {
    // First try category as string name
    auto categories = dir.get_categories();
    for (auto c : categories) {
        if (c->name == category) return c;
    }
    // Now try as ID
    uint32_t id;
    try {
        id = std::stoul(category);
        return dir.get_category(id);
    } 
    catch (std::invalid_argument&) {
        return nullptr;
    }
}

#endif