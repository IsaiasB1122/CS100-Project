#include <Commands.hpp>
#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>
#include <iomanip>

#include <iostream>

class CommandListBoardNotes : public Command {
public:
    std::string get_name() {
        return "list-board-notes";
    }
    std::string get_help() {
        return COMMAND_HELP_LIST_BOARD_NOTES;
    }
    std::vector<std::string> get_required_parameters() {return {"board",};};
    std::vector<std::string> get_optional_parameters() {return {"filter","author","sort","full"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Resolve board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE;
        // Resolve sort
        if (parameters.has_parameter("sort")) {
            std::string in_sort = "";
            for (auto c : parameters.get_parameter("sort")) in_sort.push_back(std::tolower(c));

            if (in_sort == "id") sort = DataEntry::SORT_TYPE::ID;
            else if (in_sort == "recent") sort = DataEntry::SORT_TYPE::MODIFIED;
        }
        // Filter
        std::vector<Note*> notes;
        std::vector<Note*>& final_notes = notes;
        std::string filter = "";
        if (parameters.has_parameter("filter") or sort != DataEntry::SORT_TYPE::NONE) {
            filter = parameters.get_parameter("filter");
            notes = board->notes.filter_note_name(filter, sort);
        }
        else notes = board->notes.get_notes();

        // Filter via author
        std::vector<Note*> author_filter_notes;
        if (parameters.has_parameter("author")) {
            // Resolve author id
            uint32_t author_id = -1; // -1 will just be largest u32.
            if (parameters.has_parameter("author")) {
                try {
                    author_id = get_member(*board,parameters.get_parameter("author")).id;
                }
                catch(const std::invalid_argument e)
                {
                    out << "ERROR: Member [" << parameters.get_parameter("author") << "] does not exist." << std::endl;
                    return CommandManager::COMMAND_RUN_RESULT::ERROR;
                }
            }
            for (auto n : final_notes) {
                if (n->author_id == author_id) author_filter_notes.push_back(n);
            }
            final_notes = author_filter_notes;
        }

        for (auto n : final_notes){
            if (parameters.has_parameter("full")) out << n->to_string_full(*board) << std::endl;
            else out << n->to_string() << std::endl;
        }
    
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
