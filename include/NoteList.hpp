#ifndef INCLUDE_NOTE_LIST_HPP
#define INCLUDE_NOTE_LIST_HPP

#include <Note.hpp>
#include <Member.hpp>


class NoteList {
    std::vector<Note*> notes;
    uint32_t next_note_id;
public:
    const std::vector<Note*> get_notes();
    const Note& get_note(uint32_t id);
    const Note& add_note(std::string title, std::string text, const Member& author);
    const Note& edit_note(std::string title, std::string text, const Member& author);
    void remove_note(uint32_t id);

    std::vector<unsigned char> serialize();
    static NoteList deserialize(std::vector<unsigned char> data);

    std::vector<Note*> filter_note_name(std::string query, DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE);

};


#endif
