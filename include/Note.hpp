#ifndef INCLUDE_NOTE_HPP
#define INCLUDE_NOTE_HPP

#include <DataEntry.hpp>


class Note : public DataEntry {
public:
    using DataEntry::DataEntry;
    Note(uint32_t id, std::string name, std::string text, uint32_t author_id);
    std::string text;
    uint32_t author_id;
};


#endif
