#include <iostream>
#include <Commands.hpp>
#include <command_help.hpp>
#include <map>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class CommandOutputHelp : public Command {
	public:
		string get_name(){
			return "help";
		}
		string get_help(){
			return COMMAND_HELP_OUTPUT_HELP;
		}
		vector<string> get_required_parameters() {return {};};
    	vector<string> get_optional_parameters() {return {"command"};};

		CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out){
				if (parameters.positional_parameters.size() == 0) { 
					out << "Available Commands: " << endl;
					out << "---------------------" << endl; 
					for(const auto& c : CommandManager::command_map) {
						out << "<" << c.first << ">" << endl;
						out << c.second->get_help() << endl;
					}
				}
				else {
					string requestedCommand = parameters.get_parameter(0);
					if (CommandManager::command_map.count(requestedCommand)) {
						out << CommandManager::command_map[requestedCommand]->get_help() << endl;
					}
					else{
						out << "No command found for: " << requestedCommand << endl;
					}
				}			
			return CommandManager::COMMAND_RUN_RESULT::GOOD;			
        } 		
};
