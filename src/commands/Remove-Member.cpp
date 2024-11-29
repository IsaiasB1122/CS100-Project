#include <Commands.hpp>

#include <iostream>

class CommandRemoveMember : public Command {
public:
    std::string get_name() {
        return "remove-member";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_MEMBER;
    }
    std::vector<std::string> get_required_parameters() {return {"member","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        std::string member_name = parameters.get_parameter("member");
        Member member_to_remove = board->members.get_member(member_name);
        uint32_t id = member_to_remove.id;
        board->members.remove_member(id);
        board->members_changed = true;
        FileIOManager::taskboard_write(*board);

        out << "REMOVE MEMBER " << member_to_remove.to_string() << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
