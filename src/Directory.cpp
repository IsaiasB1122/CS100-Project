
#include <Directory.hpp>

#include <cstring>
#include <cstdio>
#include <filesystem>

fspath Directory::get_metadata_path() {
    fspath p = fspath(this->path);
    return p / "_directory.cdm";
}

fspath Directory::get_boards_path() {
    fspath p = fspath(this->path);
    return p / "boards"; 
}

fspath Directory::get_board_path(TaskBoard* board) {
    return this->get_boards_path() / board->name;
}

bool Directory::exists_at_path(std::string path) {
    fspath p = fspath(path);

    // Check root dir
    if (!std::filesystem::exists(p)) return false;
    // Now check metadata dir
    if (!std::filesystem::exists(p / "_directory.cdm")) return false;

    return true;
}

Directory Directory::load_from_path(std::string path) {
    Directory dir;
    FILE* metadata;
    char* buffer = nullptr;
    //FILE* action_log;
    dir.path = path;
    // Try to open file
    metadata = std::fopen(dir.get_metadata_path().string().c_str(), "r+b");
    // Throw invalid path if error opening file
    if (!metadata) throw Directory::invalid_path("Path invalid or Directory cannot be opened.");
    // Verify magic
    buffer = new char[5];
    std::fread(buffer, 1, 5, metadata);
    // Throw if magic does not match
    if (std::strncmp(buffer,directory_magic,5)) throw Directory::invalid_path("Directory is invalid or corrupted.");
    delete[] buffer;
    // Read and verify version
    uint32_t version;
    std::fread(&version,4,1,metadata);
    if (version < minimum_supported_version) {
        throw Directory::unsupported_version("Directory is from an unsupported version.");
    } else if (version > current_version) {
        throw Directory::unsupported_version("Directory is from a future version.");
    } else if (version < current_version) {
        // placeholder
    }
    // Read name
    uint32_t len;
    std::fread(&len,4,1,metadata);
    buffer = new char[len];
    std::fread(buffer,1,len,metadata);
    dir.name.assign(buffer);
    delete[] buffer;
    // Load boards
    // Read next board id
    uint32_t next_board_id;
    std::fread(&next_board_id,4,1,metadata);
    
    // Read board num
    uint32_t board_num;
    std::fread(&board_num,4,1,metadata);

    dir.next_id = next_board_id;

    std::fclose(metadata);

    for (uint32_t i = 0; i < board_num; i += 1) {
        // read boards here
        // - create path to baord folder
        // - read board metadata
        // - read board list files
        // - for task in tasks...
    }
    // TODO: ActionLog

    return dir;
}

Directory Directory::new_at_path(std::string path, std::string name) {
    Directory dir;
    FILE* metadata;
    dir.path = path;
    // Try to make root path
    if (!std::filesystem::create_directory(fspath(dir.path))) throw Directory::invalid_path("Path invalid.");
    // First try to open the would-be metadata file
    metadata = std::fopen(dir.get_metadata_path().string().c_str(), "wb");
    if (!metadata) throw Directory::invalid_path("Path invalid.");

    // With file verified, now initialize directory
    dir.name = name;
    dir.boards = std::vector<TaskBoard*>{};
    dir.action_log = ActionLog();
    dir.next_id = 0;
    
    // Now write to file
    // Write magic
    std::fwrite(directory_magic,1,5,metadata);
    // Write version
    std::fwrite(&current_version,4,1,metadata);
    // Write name
    // length
    uint32_t name_len = dir.name.size()+1; // +1 for nullterm
    std::fwrite(&name_len,4,1,metadata);
    // data
    std::fwrite(dir.name.c_str(),1,name_len,metadata);

    // Write next board id (0)
    std::fwrite(&dir.next_id,4,1,metadata);
    // Write board num (also 0)
    std::fwrite(&dir.next_id,4,1,metadata);


    // Create boards directory
    std::filesystem::create_directory(dir.get_boards_path());

    std::fclose(metadata);

    return dir;
}