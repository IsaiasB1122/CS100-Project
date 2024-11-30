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
    std::vector<std::string> get_optional_parameters() {return {"filter","sort","full"};};

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
        std::string filter = "";
        if (parameters.has_parameter("filter") or sort != DataEntry::SORT_TYPE::NONE) {
            filter = parameters.get_parameter("filter");
            notes = board->notes.filter_note_name(filter, sort);
        }
        else notes = board->notes.get_notes();

        for (auto n : notes){
            if (parameters.has_parameter("full")) out << n->to_string_full(*board) << std::endl;
            else out << n->to_string() << std::endl;
        }
    
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
