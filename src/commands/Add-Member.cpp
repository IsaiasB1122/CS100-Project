#include <Commands.hpp>
#include <Directory.hpp>
#include <lib/file_io.hpp>
#include <TaskBoard.hpp>
#include <lib/dir_helpers.hpp>
#include <iostream>

class CommandAddMember : public Command {
public:
    std::string get_name() {
        return "add-member";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_MEMBER;
    }
    std::vector<std::string> get_required_parameters() { return {"name", "board"}; }
    std::vector<std::string> get_optional_parameters() { return {}; }

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {

        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }

        Member new_member;
        new_member.name = parameters.get_parameter("name");
        Member added_member = board->members.add_member(new_member);
        board->members_changed = true;
        FileIOManager::taskboard_write(*board);

        out << "ADD MEMBER " << added_member.to_string() << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;

    }
};
