
#include <Directory.hpp>

#include <cstring>
#include <cstdio>

Directory::Directory() {
    next_id = 0;
    default_categories.add_category({CategoryInfo(0,"TODO")});
}

Directory::~Directory() {
    for (auto board : boards) {
        delete board;
    }
}

TaskBoard* Directory::add_board(std::string name) {
    TaskBoard* board = new TaskBoard(this);

    board->name = name;
    board->id = this->next_id;
    for (auto category : this->default_categories.get_categories()) {
        board->categories.add_category(CategoryInfo(category->id,category->name));
    }
    std::time(&board->creation_time);
    std::time(&board->modified_time);

    this->boards.push_back(board);

    this->next_id += 1;

    return board;
}

std::string Directory::get_name() {
    return this->name;
}

std::vector<TaskBoard*> Directory::get_boards() {
    std::vector<TaskBoard*> boards;
    for (auto b : this->boards) boards.push_back(b);
    return boards;
}

TaskBoard* Directory::get_board(uint32_t id) {
    // If needed could use a binary search here for performance as the vector is sorted by ID
    for (auto b = this->boards.begin(); b < this->boards.end(); b += 1) {
        if ((*b)->id == id) return *b;
    }

    return nullptr;
}

void Directory::remove_board(TaskBoard* board) {
    for (auto b = this->boards.begin(); b < this->boards.end(); b += 1) {
        if (*b == board) {
            this->boards.erase(b);
            delete board;
        }
    }
}