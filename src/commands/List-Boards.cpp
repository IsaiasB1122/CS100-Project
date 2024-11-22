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

        CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, ostream& out){		
            string filter = parameters.get_parameter("filter");
            vector <TaskBoard*> boards = this->parent->dir->get_boards();
            vector<DataEntry*> boards_as_data_entry;

            for (auto board : boards) {
                boards_as_data_entry.push_back(static_cast<DataEntry*>(board));
            }
             
            vector<DataEntry*> filteredBoards = DataEntry::filter_data(boards_as_data_entry, filter, DataEntry::SORT_TYPE::NONE);
            if (filteredBoards.empty()) {
                out << "No boards match the filter provided." << endl;
            }
            else {
                for (auto board : filteredBoards) {
                    //TaskBoard* itr = dynamic_cast<TaskBoard*>(board);
                    if(board) {
                        out << board->to_string() << endl;
                    }
                    else {
                        out << "Failed to cast DataEntry to TaskBoard" << endl;
                    }
                }
            }
            return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
    
};