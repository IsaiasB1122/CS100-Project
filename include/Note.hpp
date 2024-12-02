#ifndef INCLUDE_NOTE_HPP
#define INCLUDE_NOTE_HPP

#include <DataEntry.hpp>

class TaskBoard;

class Note : public DataEntry {
public:
    using DataEntry::DataEntry;
    Note(uint32_t id, std::string name, std::string text, uint32_t author_id);
    std::string text;
    uint32_t author_id;

    std::string to_string_full(const TaskBoard& board) const;
};


#endif
