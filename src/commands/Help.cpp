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
    	vector<string> get_optional_parameters() {return {"command"};}; //let program know this command require an optional parameter

		CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out){
				//if there is a paramter print all commands
				out << parameters.get_parameter("command") << endl;
				if (parameters.has_parameter("command"))  { 
					string requestedCommand = parameters.get_parameter(0);
					//print given command with description
					if (CommandManager::command_map.count(requestedCommand)) {
						out << CommandManager::command_map[requestedCommand]->get_help() << endl;
					}
					//if the user inputed an invalid parameter, let the user know.
					else{
						out << "No command found for: " << requestedCommand << endl;
					}	
				}
				else { //when there is no parameter after "help"
					out << "Available Commands: " << endl;
					out << "-------------------" << endl; 
					for(const auto& c : CommandManager::command_map) {
						out << "<" << c.first << ">" << endl;
						out << c.second->get_help() << endl;
					}
				}			
			return CommandManager::COMMAND_RUN_RESULT::GOOD;			
        } 		
};
