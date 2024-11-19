#include <Commands.hpp>

#include <Directory.hpp>
#include <lib/file_io.hpp>
#include <lib/dir_helpers.hpp>

extern Directory dir;

class CommandRemoveCategory : public Command {
public:
    std::string get_name() {
        return "remove-category";
    }
    std::string get_help() {
        return COMMAND_HELP_REMOVE_CATEGORY;
    }
    std::vector<std::string> get_required_parameters() { return {"category"}; }
    std::vector<std::string> get_optional_parameters() { return {}; }

    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        // Work
        TaskCategory* category = get_category(dir, parameters.get_parameter("category"));
        if (category == nullptr) {
            out << "ERROR: Category [" << parameters.get_parameter("category") << "] not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR;
        }

        // Save these before erasure
        std::string category_string = category->to_string();
        uint32_t id = category->id;

        dir.remove_category(category);
        // Write
        FileIOManager::directory_write_metadata(dir);
        FileIOManager::category_delete(dir, id);
        // Output
        out << "REMOVE CATEGORY " << category_string << std::endl;

        return CommandManager::COMMAND_RUN_RESULT::GOOD;
    }
};