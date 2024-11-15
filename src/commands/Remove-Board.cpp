#include <Commands.hpp>

#include <Directory.hpp>
#include <lib/file_io.hpp>
#include <lib/dir_helpers.hpp>

extern Directory dir;

class CommandRemoveBoard : public Command {
public:
    std::string get_name() {
        return "remove-board";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_BOARD;
    }
    std::vector<std::string> get_required_parameters() {return {"board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Work
        TaskBoard* board = get_board(dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        // Save these needed before erasure
        std::string board_string = board->to_string();
        uint32_t id = board->id;

        dir.remove_board(board);
        // Write
        FileIOManager::directory_write_metadata(dir);
        FileIOManager::taskboard_delete(dir, id);
        // Output
        out << "REMOVE BOARD " << board_string << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
