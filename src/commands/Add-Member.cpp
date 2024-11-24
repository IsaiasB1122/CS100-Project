#include <Commands.hpp>

#include <Directory.hpp>
#include <lib/file_io.hpp>

class CommandAddMember : public Command {
public:
    std::string get_name() {
        return "add-member";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_MEMBER;
    }
    std::vector<std::string> get_required_parameters() {return {"name"};};
    std::vector<std::string> get_optional_parameters() {return {};};

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Work
        MemberList* member = this->parent->dir->add_member(parameters.get_parameter("name"));
        // Write
        FileIOManager::directory_write_metadata(*this->parent->dir);
        FileIOManager::member_list_write(*member);
        // Output
        out << " NEW MEMBER " << member->to_string() << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};