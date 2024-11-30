#include <Commands.hpp>
#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>

#include <iostream>

class CommandRemoveBoardNote : public Command {
public:
    std::string get_name() {
        return "remove-board-note";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_BOARD_NOTE;
    }
    std::vector<std::string> get_required_parameters() {return {"note","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Resolve board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        // Resolve note
        uint32_t note_id = 0;
        try {
            note_id = get_board_note(*board,parameters.get_parameter("note")).id;
        }
        catch(const std::invalid_argument e)
        {
            out << "ERROR: Note [" << parameters.get_parameter("note") << "] does not exist." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }
        // Save this for output
        std::string note_string = board->notes.get_note(note_id).to_string();
        // Remove task
        board->notes_changed = true;
        board->notes.remove_note(note_id);
        // Write
        FileIOManager::taskboard_write(*board);
        // Output
        out << "REMOVE NOTE " << note_string << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
