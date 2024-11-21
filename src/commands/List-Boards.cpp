#include <iostream>
#include <string>
#include <Commands.hpp>
#include <command_help.hpp>
#include <Directory.hpp>
#include <lib/dir_helpers.hpp>
using namespace std;

class CommandListBoards : public Command {
	public:
		string get_name(){
			return "list-boards";
		}
		string get_help(){
			return COMMAND_HELP_LIST_BOARDS;
		}
        vector<string> get_required_parameters() {return {};};
    	vector<string> get_optional_parameters() {return {"filter"};};

        CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out){		
            vector<TaskBoard*>  boards = this->parent->dir->get_boards();
            string filter;
            if (parameters.has_parameter("filter")) {
                filter = parameters.get_parameter("filter");
            }
            for (TaskBoard* board : boards){
                if (board != nullptr && (filter.empty() || board->to_string().find(filter) != string::npos)) {
                    out << board->to_string() << endl;
                }
            }
            
            return CommandManager::COMMAND_RUN_RESULT::GOOD;	    		
        } 
};