#ifndef INCLUDE_TASK_HPP
#define INCLUDE_TASK_HPP

#include <DataEntry.hpp>
#include <NoteList.hpp>

class TaskBoard;

class Task : public DataEntry {
public:
    uint32_t category_id;
    std::vector<uint32_t> assigned_members;
    NoteList notes;
    bool changed;

    std::string to_string(TaskBoard& board) const;
    std::string to_string_full(TaskBoard& board) const;


    friend class FileIOManager;
};


#endif
