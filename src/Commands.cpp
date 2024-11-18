#include <Commands.hpp>

#include <stdexcept>
#include <iostream>
#include <iomanip>

std::string CommandParametersData::get_parameter(std::string name) {
    return this->named_parameters[name];
}
bool CommandParametersData::has_parameter(std::string name) {
    return this->named_parameters.count(name);
}

void CommandManager::set_parameter(std::string name, std::string value) {
    CommandManager::set_parameters[name] = value;
}
void CommandManager::unset_parameter(std::string name) {
    CommandManager::set_parameters.erase(name);
}

CommandManager::COMMAND_PARSE_RESULT CommandManager::parse_command(std::istream& in, std::ostream& out) {
    // Very unoptimized
    std::stringstream ss;
    std::string s;
    // Get line from input
    std::getline(in, s);
    ss << s;
    std::vector<std::string> args;
    s = "";
    // Extract words
    while (ss >> std::quoted(s,'"','\\'))
    {
        args.push_back(s);
    }
    // Invalid if empty
    if (args.size() < 1) return CommandManager::BAD_COMMAND;
    std::string command_name = args[0];
    // Treat command name arg as lowercase
    std::string ns;
    for (auto c : command_name) ns.push_back(std::tolower(c));
    command_name = ns;
    // Check if command is indexed
    if (!command_map.count(command_name)) return CommandManager::BAD_COMMAND;
    Command& command = *command_map[command_name];
    // Create named parameters map
    
    std::map<std::string,std::string> named_parameters;
    std::vector<std::string> positional_parameters;
    auto arg = args.begin()+1; // +1 to skip command name
    while (arg < args.end()) {
        // Check if is a name
        if ((*arg).size() > 3 and (*arg)[0] == '-' and (*arg)[1] == '-') {
            std::string n = (*arg).substr(2);
            // Put parametr name to lowercase
            std::string n_lower;
            for (auto c : n) n_lower.push_back(std::tolower(c));
            n = n_lower;
            // Now read next
            arg += 1;
            // If name is last parameter that is invalid
            if (arg >= args.end()) return CommandManager::BAD_PARAMETERS;
            // Use next as value
            named_parameters[n] = *arg;
        }
        // Else add to pos. arg list
        else {
            positional_parameters.push_back(*arg);
        }
        arg += 1;
    }

    // Now go through required and optional command parameters positionally
    std::vector<std::string> required_parameters = command.get_required_parameters();
    std::vector<std::string> optional_parameters = command.get_optional_parameters();
    size_t i = 0;
    for (auto arg = required_parameters.begin(); arg < required_parameters.end() and i < positional_parameters.size(); arg += 1, i += 1) {
        // Maybe check here and throw error if named paramter was already defined?
        named_parameters[*arg] = positional_parameters[i];
    }
    for (auto arg = optional_parameters.begin(); arg < optional_parameters.end() and i < positional_parameters.size(); arg += 1, i += 1) {
        named_parameters[*arg] = positional_parameters[i];
    }
    // Now check that all required exist and throw error if not
    for (auto arg : required_parameters) if (!named_parameters.count(arg)) return CommandManager::BAD_PARAMETERS;

    CommandParametersData paramdata;
    paramdata.named_parameters = named_parameters;
    paramdata.positional_parameters = positional_parameters;

    exit = false;
    COMMAND_RUN_RESULT r = command.run(paramdata, out);

    if (exit) {
        if (r == COMMAND_RUN_RESULT::GOOD){
            return OK_EXIT_AFTER;
        } 
        else return BAD_EXIT_AFTER;
    }  

    return COMMAND_PARSE_RESULT::OK;

}

void CommandManager::init() {
    _index_commands();
}