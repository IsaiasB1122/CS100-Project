#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include <map>

#include <command_help.hpp>

class Command;

class CommandManager {
public:
    enum COMMAND_PARSE_RESULT {BAD_COMMAND, BAD_PARAMETERS, OK, OK_EXIT_AFTER, BAD_EXIT_AFTER};
    enum COMMAND_RUN_RESULT {ERROR, GOOD};

    static inline std::map<std::string,std::string> set_parameters;
    static inline std::map<std::string, Command*> command_map;

    static inline bool exit;

    static void set_parameter(std::string name, std::string value);
    static void unset_parameter(std::string name);

    static COMMAND_PARSE_RESULT parse_command(std::istream& in, std::ostream& out);

    static void _index_commands();

    static void init();
};

class CommandParametersData {
    
    std::map<std::string, std::string> named_parameters;
public:
    std::vector<std::string> positional_parameters; //changing this vector to be public
    std::string get_parameter(unsigned int index);
    std::string get_parameter(std::string name);
    bool has_parameter(std::string name);

    friend class CommandManager;
};

class Command {
public:
    virtual std::string get_name() = 0;
    virtual std::string get_help() = 0;
    virtual std::vector<std::string> get_required_parameters() = 0;
    virtual std::vector<std::string> get_optional_parameters() = 0;

    virtual CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) = 0;
};

#endif