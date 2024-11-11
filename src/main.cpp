
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

#include <iostream>
#include <cctype>

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
    Directory dir;
    path.assign(argv[1]);
    // First check if exists at path
    if (Directory::exists_at_path(path)) {
        // Load
            try {
                dir = Directory::load_from_path(path);
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
                dir = Directory::new_at_path(path, buffer);
            }
            catch(std::runtime_error& e) {
                std::cout << "ERROR: " << e.what() << '\n';
            }
            
        } else return 0;

       
    }

    return 0;
}