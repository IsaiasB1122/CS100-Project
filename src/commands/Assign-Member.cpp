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
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }


        std::string task_name = parameters.get_parameter("task");
        Task task = get_task(*board, task_name);
        std::string member_name = parameters.get_parameter("member");
        Member member_to_assign = get_member(*board, member_name);
        uint32_t id = member_to_assign.id;
        task.assigned_members.push_back(id);
        out << "ASSIGN " << member_to_assign.to_string() << " to " << task.to_string(*board) << std::endl;

        
        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};
