
#include <ActionLog.hpp>
#include <ActionLogItem.hpp>
#include <CategoryInfo.hpp>
#include <CategoryList.hpp>
#include <DataEntry.hpp>
#include <Directory.hpp>
#include <Member.hpp>
#include <MemberList.hpp>
#include <Note.hpp>
#include <NoteList.hpp>
#include <Task.hpp>
#include <TaskBoard.hpp>

#include <Commands.hpp>

#include <lib/file_io.hpp>

#include <iostream>
#include <cctype>

Directory dir;

void handle_usage() {
    std::cout << "Usage: cataboard <path to directory>" << std::endl;
}

int main(int argc, char** argv) {


    if (argc < 2) {
        handle_usage();
        return 1;
    }
    // Use first argument as path
    std::string path;
    std::string buffer;
    path.assign(argv[1]);
    // First check if exists at path
    if (FileIOManager::directory_exists_at_path(path)) {
        // Load
            try {
                //dir = Directory::load_from_path(path);
                FileIOManager::directory_load_from_path(dir, path);
            }
            catch(std::runtime_error& e) {
                std::cout << "ERROR: " << e.what() << '\n';
            }
    } else {
        // Create new
        std::cout << "No CaTaBoard directory path given. Create new? (y/n): ";
        std::getline(std::cin, buffer);
        
        if (buffer.size() > 0 and std::tolower(buffer[0]) == 'y') {
            std::cout << "New Directory name: ";
            std::getline(std::cin, buffer);
            try {
                //dir = Directory::new_at_path(path, buffer);
                FileIOManager::directory_new_at_path(dir, path, buffer);
            }
            catch(std::runtime_error& e) {
                std::cout << "ERROR: " << e.what() << '\n';
            }
            
        } else return 0;
    }

    // Initialize command sys
    CommandManager::init();

    std::cout << "CaTaBoard Version " << current_version << " - Built " << __DATE__ << std::endl;
    std::cout << "Loaded Directory {" << dir.get_name() << "} at [" << std::filesystem::absolute(path).string() << "]" << std::endl;

    // Read command until exit
    while (true) {
        std::cout << "> ";
        CommandManager::COMMAND_PARSE_RESULT r = CommandManager::parse_command(std::cin,std::cout);

        switch (r) {
        case CommandManager::COMMAND_PARSE_RESULT::BAD_COMMAND:
            std::cout << "ERROR: Command not found. (run help for list)" << std::endl;
            break;
        case CommandManager::COMMAND_PARSE_RESULT::BAD_PARAMETERS:
            std::cout << "ERROR: Command parameters invalid." << std::endl;
            break;
        case CommandManager::COMMAND_PARSE_RESULT::OK:
            break;
        case CommandManager::COMMAND_PARSE_RESULT::OK_EXIT_AFTER:
            goto exit;
            break;
        case CommandManager::COMMAND_PARSE_RESULT::BAD_EXIT_AFTER:
            goto exit;
            break;
        default:
            break;
        }
    }
    exit:

    

    return 0;
}