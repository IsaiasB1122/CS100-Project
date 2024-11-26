#ifndef INCLUDE_TASK_BOARD_HPP
#define INCLUDE_TASK_BOARD_HPP


#include <Task.hpp>
#include <CategoryList.hpp>
#include <NoteList.hpp>
#include <ActionLog.hpp>
#include <MemberList.hpp>



class Directory;

class TaskBoard : public DataEntry {
    Directory* parent;
    std::vector<Task*> tasks;

    uint32_t next_task_id;

public:
    bool tasks_changed;
    bool members_changed;
    bool notes_changed;
    bool categories_changed;

    TaskBoard(Directory*);
    ~TaskBoard();
    MemberList members;
    NoteList notes;
    CategoryList categories;

    const std::vector<Task*> get_tasks();
    const Task& add_task(std::string name, uint32_t category = 0);
    void remove_task(uint32_t id);
    void move_task(uint32_t id, uint32_t category_id);
    const std::vector<CategoryInfo*> get_categories();
    const CategoryInfo& add_category(std::string name);
    void remove_category(uint32_t id);

    std::vector<Task*> filter_task_name(std::string query, DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE);

    friend class FileIOManager;
};


#endif
