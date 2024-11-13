#ifndef INCLUDE_DIRECTORY_HPP
#define INCLUDE_DIRECTORY_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <stdexcept>


#include <CategoryList.hpp>
#include <ActionLog.hpp>
#include <TaskBoard.hpp>



const uint32_t current_version = 1;
const uint32_t minimum_supported_version = 1;




class Directory {
    // Path to the root directory of the Directory
    std::string path;
    std::string name;
    std::vector<TaskBoard*> boards;
    ActionLog action_log;

    uint32_t next_id;

    void write_metadata();

public:
    class invalid_path : std::runtime_error {using std::runtime_error::runtime_error;};
    class unsupported_version : std::runtime_error {using std::runtime_error::runtime_error;};
    CategoryList default_categories;
    // fspath get_metadata_path();
    // fspath get_boards_path();
    // fspath get_board_path(TaskBoard* board);
    static bool exists_at_path(std::string path);
    static Directory load_from_path(std::string path);
    static Directory new_at_path(std::string path, std::string name);
    std::string get_path();
    std::string get_name();
    TaskBoard* add_board(std::string name);
    void remove_board(TaskBoard* board);
    std::vector<TaskBoard*> get_boards();
    TaskBoard* get_board(uint32_t id);
    std::vector<TaskBoard*> filter_board_name(std::string query, DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE);

    friend class FileIOManager;
};


#endif