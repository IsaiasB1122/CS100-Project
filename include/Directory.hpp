#ifndef INCLUDE_DIRECTORY_HPP
#define INCLUDE_DIRECTORY_HPP

#include <string>
#include <vector>
#include <cstdint>

#include <CategoryList.hpp>
#include <ActionLog.hpp>
#include <TaskBoard.hpp>

class Directory {
    std::string path;
    std::string name;
    std::vector<TaskBoard*> boards;
    ActionLog action_log;

    uint32_t next_id;
public:
    CategoryList default_categories;
    static Directory load_from_path(std::string path);
    static Directory new_a_path(std::string path);
    std::string get_path();
    std::string get_name();
    TaskBoard* add_board(std::string name);
    void remove_board(TaskBoard* board);
    std::vector<TaskBoard*> get_boards();
    TaskBoard* get_board(uint32_t id);
    std::vector<TaskBoard*> filter_board_name(std::string query, DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE);
};



#endif