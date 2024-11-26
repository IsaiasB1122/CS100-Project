
#include <NoteList.hpp>

// TEMPORAY FOR STUBS, REMOVE WHEN ACTUALLY IMPLEMENTING!
const Note dummy(0,"dummy");

const std::vector<Note*> NoteList::get_notes() {
    return std::vector<Note*>{};
}
const Note& NoteList::get_note(uint32_t id) {
    return dummy;
}
const Note& NoteList::add_note(std::string title, std::string text, const Member& author) {
    return dummy;
}
const Note& NoteList::edit_note(std::string title, std::string text, const Member& author) {
    return dummy;
}
void NoteList::remove_note(uint32_t id){

}