#include <Commands.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <command_help.hpp>
#include <Directory.hpp>
#include <TaskBoard.hpp>
#include <MemberList.hpp>
#include <lib/dir_helpers.hpp>

class CommandListMembers : public Command {
    public:
        std::string get_name() {
            return "list-members";
        }
        std::string get_help() {
            return COMMAND_HELP_LIST_MEMBERS;
        }
        std::vector<std::string> get_required_parameters() {return {"board"};};
        std::vector<std::string> get_optional_parameters() {return {"filter"};};

        CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {

        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }


            string filter = parameters.get_parameter("filter");
            vector <Member*> members = board->members.get_members();
            vector <DataEntry*> memberlist_as_entry_data;

            for (auto member : members) {
                memberlist_as_entry_data.push_back(static_cast<DataEntry*>(member));
            }
            vector<DataEntry*> filteredMemberList = DataEntry::filter_data(memberlist_as_entry_data, filter, DataEntry::SORT_TYPE::NONE);
            if (memberlist_as_entry_data.empty()) {
                out << "No members found." << std::endl;
                return CommandManager::COMMAND_RUN_RESULT::ERROR;
            }
            else {
                for (auto member : filteredMemberList) {
                    if(member != nullptr) {
                        out << member->to_string() << endl;
                    }
                    else {
                        out << "Failed to get members" << endl;
                        return CommandManager::COMMAND_RUN_RESULT::ERROR;
                    }
                }
            }
            return CommandManager::COMMAND_RUN_RESULT::GOOD;

        }
};
