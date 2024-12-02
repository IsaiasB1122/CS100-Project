#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <vector>
#include <string>
#include <map>

#include "Directory.hpp"

#include <command_help.hpp>

class Command;

class CommandManager {
public:
    enum COMMAND_PARSE_RESULT {BAD_COMMAND, BAD_PARAMETERS, OK, OK_EXIT_AFTER, BAD_EXIT_AFTER};
    enum COMMAND_RUN_RESULT {ERROR, GOOD};

    std::map<std::string,std::string> set_parameters;
    std::map<std::string, Command*> command_map;

    bool exit;

    void set_parameter(std::string name, std::string value);
    void unset_parameter(std::string name);

    COMMAND_PARSE_RESULT parse_command(std::istream& in, std::ostream& out);

    void _index_commands();
    // * This should be done in a class inheriting from CommandManager ideally but trying to keep project simpler
    Directory* dir;

    void init();
};

class CommandParametersData {
    std::vector<std::string> positional_parameters;
    std::map<std::string, std::string> named_parameters;
    CommandManager* parent;
public:
    std::string get_parameter(std::string name);
    bool has_parameter(std::string name);
    const std::map<std::string, std::string>& get_named_parameter_pairs();

    friend class CommandManager;
};

class Command {
public:
    CommandManager* parent;
    virtual std::string get_name() = 0;
    virtual std::string get_help() = 0;
    virtual std::vector<std::string> get_required_parameters() = 0;
    virtual std::vector<std::string> get_optional_parameters() = 0;

    virtual CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) = 0;
};

#endif