#include <Commands.hpp>
#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>


#include <iostream>

class CommandAddBoardNote : public Command {
public:
    std::string get_name() {
        return "add-board-note";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_BOARD_NOTE;
    }
    std::vector<std::string> get_required_parameters() {return {"title","text","board"};};
    std::vector<std::string> get_optional_parameters() {return {"author"};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Resolve board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
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
        // Add note
        Note n = board->notes.add_note(parameters.get_parameter("title"),parameters.get_parameter("text"),author_id);
        
        // Write
        board->notes_changed = true;
        FileIOManager::taskboard_write(*board);

        // Output
        out << "ADD NOTE " << n.to_string() << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
