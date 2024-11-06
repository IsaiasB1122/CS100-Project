#ifndef INCLUDE_NOTE_HPP
#define INCLUDE_NOTE_HPP

#include <DataEntry.hpp>


class Note : public DataEntry {
public:
    std::string text;
    uint32_t author_id;
};


#endif
