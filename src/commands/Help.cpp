#include <iostream>
#include <Commands.hpp>
#include <command_help.hpp>
#include <map>
#include <algorithm>

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
			string requestedCommand;
			
			if (parameters.has_parameter("command")){
				requestedCommand = parameters.get_parameter("command");
			}	
			if (requestedCommand.empty()) {
				out << "Available Commands: " << std::endl;
				out << "---------------------" << std::endl;
				for (const auto& cMap : CommandManager::command_map) {
					out << "<" << cMap.first << ">" << std::endl;
					out << cMap.second->get_help() << std::endl;
       			}
			}
			else {
				if (CommandManager::command_map.count(requestedCommand)) {
					out << "Help for command <" << requestedCommand << ">:" << endl;
					out << CommandManager::command_map[requestedCommand]->get_help() << endl;
				}
				else {
					out << "No command found for: " << requestedCommand << endl;
				}
			}
			return CommandManager::COMMAND_RUN_RESULT::GOOD;
        } 		
};
