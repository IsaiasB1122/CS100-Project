#include <stdexcept>
#include <NoteList.hpp>

const std::vector<Note*> NoteList::get_notes() {
    return notes;
}
const Note& NoteList::get_note(uint32_t id) {
    for (auto it = notes.begin(); it < notes.end(); it += 1) {
        if ((*it)->id == id)
        {
            return **it;
        }
    }
    throw std::invalid_argument("");
}
const Note& NoteList::add_note(std::string title, std::string text, uint32_t author_id = -1) {
    Note* n = new Note(next_note_id,title, text, author_id);
    notes.push_back(n);

    std::time(&n->creation_time);
    std::time(&n->modified_time);

    next_note_id += 1;

    return *n;
}


void NoteList::remove_note(uint32_t id){
    for (auto it = notes.begin(); it < notes.end(); it += 1) {
        if ((*it)->id == id)
        {
            Note* tp = *it;
            notes.erase(it);
            delete tp;
            return;
        }
    }
    throw std::logic_error("Bad call to remove_note on missing id");
}

std::vector<Note*> NoteList::filter_note_name(std::string query, DataEntry::SORT_TYPE sort) {
    std::vector<DataEntry*> filtered;
    std::vector<Note*> out;
    for (auto t : notes) filtered.push_back(t);
    filtered = DataEntry::filter_data(filtered, query, sort);
    for (auto t : filtered) out.push_back( reinterpret_cast<Note*>(t) );

    return out;
}