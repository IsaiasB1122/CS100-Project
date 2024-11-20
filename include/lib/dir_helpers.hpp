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

#endif