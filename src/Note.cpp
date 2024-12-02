
#include <Note.hpp>
#include <TaskBoard.hpp>
#include <cstring>


Note::Note(uint32_t id, std::string name, std::string text, uint32_t author_id) {
    this->id = id;
    this->name = name;
    this->text = text;
    this->author_id = author_id;
}

std::string Note::to_string_full(const TaskBoard& board) const {
    std::string out;
    out.append("- - Note #").append(std::to_string(id)).append(": ")\
    .append(name).append("\nAuthor: ");
    if (author_id == -1) {
        out.append("<None>");
    }
    else {
        try
        {
            Member m = const_cast<MemberList&>(board.members).get_member(author_id);
            out.append(m.to_string());
        }
        catch(const std::exception& e)
        {
            out.append("<DELETED>");
        }
    }
    out.append("\n\"");
    std::string s;
    int matched_index = -1;
    for (auto c : text) {
        switch (matched_index) {
            case -1:
                if (c == '<') matched_index = 0;
                else s += c;
                break;
            case 0:
                if (c == 'b') matched_index = 1;
                else {
                    s = s + '<' + c;
                    matched_index = 0;
                }
                break;
            
            case 1:
                if (c == 'r') matched_index = 2;
                else {
                    s = s + "<b" + c;
                    matched_index = -1;
                }
                break;
            
            case 2:
                if (c == '>') s += '\n';
                else s = s + "<br" + c;

                matched_index = -1;

                break;
        }
    }
    out.append(s).append("\"");
    return out;
}