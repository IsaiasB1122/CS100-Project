#ifndef INCLUDE_TASK_BOARD_HPP
#define INCLUDE_TASK_BOARD_HPP

#include <Task.hpp>
#include <CategoryList.hpp>
#include <NoteList.hpp>
#include <ActionLog.hpp>
#include <MemberList.hpp>

// declare directory
class Directory;

class TaskBoard : public DataEntry {
    Directory* parent;
    std::vector<Task*> tasks;
    bool tasks_changed;
    bool members_changed;
    bool notes_changed;
    bool categories_changed;
public:
    MemberList members;
    NoteList notes;
    CategoryList categories;

    uint32_t get_id();
    int write();
    const std::vector<Task*> get_tasks();
    const Task& add_task(std::string name, uint32_t author = 0, uint32_t category = 0);
    void remove_task(uint32_t id);
    void move_task(uint32_t id, uint32_t category_id);

    std::vector<Task*> filter_task_name(std::string query, DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE);
};


#endif
