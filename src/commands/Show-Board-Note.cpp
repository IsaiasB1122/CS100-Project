#include <Commands.hpp>

#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>
#include <iostream>

class CommandShowBoardNote : public Command {
public:
    std::string get_name() {
        return "show-board-note";
    }
    std::string get_help() {
        return COMMAND_HELP_SHOW_BOARD_NOTE;
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
        const Note* note = 0;
        try {
            note = &get_board_note(*board,parameters.get_parameter("note"));
        }
        catch(const std::invalid_argument e)
        {
            out << "ERROR: Note [" << parameters.get_parameter("note") << "] does not exist." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        std::cout << note->to_string_full(*board) << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
