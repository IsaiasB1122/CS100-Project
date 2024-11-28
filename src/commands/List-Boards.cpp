#include <iostream>
#include <string>
#include <vector>
#include <Commands.hpp>
#include <command_help.hpp>
#include <Directory.hpp>
#include <TaskBoard.hpp>
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

        CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, ostream& out) {		
            string filter = parameters.get_parameter("filter");
        }
};
