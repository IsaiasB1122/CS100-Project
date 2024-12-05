
#include <Task.hpp>
#include <TaskBoard.hpp>
#include <stdexcept>

Task::Task() {
    this->id = 0;
    this->category_id = 0;
    this->changed = false;
}

std::string Task::to_string(TaskBoard& board) const {
    std::string category_name;
    try  {
        category_name = board.categories.get_category(this->category_id).name;
    }
    catch(const std::invalid_argument){
        category_name = "<DELETED>";
    }
    return "[ " + std::to_string(this->id) + ' ' + category_name +  ' ' + this->name + " ]";
}

std::string Task::to_string_full(TaskBoard& board) const {
    std::string out;
    std::string category_string;
    try  {
        category_string = board.categories.get_category(this->category_id).to_string();
    }
    catch(const std::invalid_argument){
        category_string = "[ " + std::to_string(this->category_id) + " <DELETED> ]";
    }

    out.append("Task #").append(std::to_string(this->id)).append(": ").append(this->name).append("\n");
    out.append("Category: ").append(category_string).append("\n");
    out.append("Assigned Members: ");
    if (this->assigned_members.size() > 0) {
        for (auto id : this->assigned_members) {
            std::string member_string;
            try  {
                member_string = board.members.get_member(id).to_string();
            }
            catch(const std::invalid_argument){
                member_string = "[ " + std::to_string(id) + " <DELETED> ]";
            }
            out.append(member_string + "  ");
        }
        out.append("\n");
    }
    else out.append("- none -").append("\n");
    out.append("Notes:\n");
    NoteList& notes = const_cast<NoteList&>(this->notes);
    if (notes.get_notes().size() > 0) {
        for (auto note : notes.get_notes()) {
            out.append(note->to_string() + "  ");
        }
    } else out.append("- none -");

    return out;
}