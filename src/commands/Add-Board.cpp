#include <Commands.hpp>

#include <Directory.hpp>
#include <lib/file_io.hpp>

class CommandAddBoard : public Command {
public:
    std::string get_name() {
        return "add-board";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_BOARD;
    }
    std::vector<std::string> get_required_parameters() {return {"name"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Work
        TaskBoard* board = this->parent->dir->add_board(parameters.get_parameter("name"));
        // Write
        FileIOManager::directory_write_metadata(*this->parent->dir);
        FileIOManager::taskboard_write(*board);
        // Output
        out << "ADD BOARD " << board->to_string() << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};