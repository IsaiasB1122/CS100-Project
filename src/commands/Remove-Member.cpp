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
        Member* member = nullptr;

        try {
            member = &board->members.get_member(member_name);
        } catch (const std::runtime_error& e) {
            out << "ERROR: Member [" << member_name << "] not found on board [" << parameters.get_parameter("board") << "]." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }


        uint32_t member_id = member->id;
        std::string member_string = member->to_string();


        board->members.remove_member(member_id);
        board->members_changed = true;
        FileIOManager::taskboard_write(*board);
        FileIOManager::directory_write_metadata(*this->parent->dir);


        out << "REMOVE MEMBER " << member_string << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
