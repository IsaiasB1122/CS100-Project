
#include <Directory.hpp>

#include <cstring>
#include <cstdio>


TaskBoard* Directory::add_board(std::string name) {
    TaskBoard* board = new TaskBoard(this);
    this->boards.push_back(board);

    board->name = name;
    board->id = this->next_id;
    this->next_id += 1;


    return board;
}