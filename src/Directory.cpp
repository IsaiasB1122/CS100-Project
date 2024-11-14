
#include <Directory.hpp>

#include <cstring>
#include <cstdio>


TaskBoard* Directory::add_board(std::string name) {
    TaskBoard* board = new TaskBoard(this);

    board->name = name;
    board->id = this->next_id;
    board->categories = this->default_categories;

    this->boards.push_back(board);

    this->next_id += 1;

    return board;
}