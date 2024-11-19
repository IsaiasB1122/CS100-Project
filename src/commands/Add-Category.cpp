#include <Commands.hpp>

#include <Directory.hpp>
#include <lib/file_io.hpp>

extern Directory dir;

class CommandAddCategory : public Command {
public:
    std::string get_name() {
        return "add-category";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_CATEGORY;
    }
    std::vector<std::string> get_required_parameters() { return {"name"}; }
    std::vector<std::string> get_optional_parameters() { return {}; }

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Work
        TaskCategory* category = dir.add_category(parameters.get_parameter("name"));
        // Write
        FileIOManager::directory_write_metadata(dir);
        FileIOManager::category_write(*category);
        // Output
        out << "ADD CATEGORY " << category->to_string() << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};