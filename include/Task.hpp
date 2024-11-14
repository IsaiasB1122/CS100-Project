#ifndef INCLUDE_TASK_HPP
#define INCLUDE_TASK_HPP

#include <DataEntry.hpp>
#include <NoteList.hpp>

class Task : public DataEntry {
public:
    uint32_t category_id;
    std::vector<uint32_t> assigned_members;
    NoteList notes;
    bool changed;


    friend class FileIOManager;
};


#endif
