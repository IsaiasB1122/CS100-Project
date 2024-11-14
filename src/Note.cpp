
#include <Note.hpp>

Note::Note(uint32_t id, std::string name, std::string text, uint32_t author_id) {
    this->id = id;
    this->name = name;
    this->text = text;
    this->author_id = author_id;
}