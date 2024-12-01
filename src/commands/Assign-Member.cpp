#include <Commands.hpp>

#include <iostream>

class CommandAssignMember : public Command {
public:
    std::string get_name() {
        return "assign-member";
    }
    std::string get_help() {
        return COMMAND_HELP_ASSIGN_MEMBER;
    }
    std::vector<std::string> get_required_parameters() {return {"task","member","board"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            throw std::runtime_error("Board [" + parameters.get_parameter("board") + "] not found.");
        }

        std::string task_name = parameters.get_parameter("task");
        Task task;
        try {
            task = get_task(*board, task_name); 
        } catch (const std::exception& e) {
            out << "Error: Task [" << task_name << "] not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        std::string member_name = parameters.get_parameter("member");
        Member member_to_assign;

        try {
            member_to_assign = get_member(*board, member_name);
        } catch (const std::exception& e) {
            out << "Error: Member [" << member_name << "] not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }
        uint32_t task_id = task.id;
        uint32_t member_id = member_to_assign.id;
        board->assign_member(task_id, member_id);
        task.changed = true;

        FileIOManager::taskboard_write(*board);
        out << "ASSIGN " << member_to_assign.to_string() << " to " << task.to_string(*board) << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
