// TODO: Move exceptions to here and make a better variety
// TODO: Move notes/... etc list serialization/deserialization here
#include <Directory.hpp>
#include <TaskBoard.hpp>

#include <cstring>

#include <filesystem>

typedef std::filesystem::path fspath;

// This is only a class to use friendship for convenience
class FileIOManager {
public:

    // Writes a size+length strength into the given file
    static void write_string(FILE* f, std::string s) {
        uint32_t s_len = s.size() + 1; // +1 for nullterm
        // Write length
        std::fwrite(&s_len,4,1,f);
        // Write string
        std::fwrite(s.c_str(),1,s_len,f);
    }
    // Reads a size+length string from file into std::string
    static std::string read_string(FILE* f) {
        std::string s;
        uint32_t len;
        char* buffer;
        // Read length
        std::fread(&len,4,1,f);
        // Allocate buffer
        buffer = new char[len];
        // Read string to buffer
        std::fread(buffer,1,len,f);
        // Assign buffer to stdstring
        s.assign(buffer);
        // Exterminate buffer
        delete[] buffer;

        return s;
    }

    static fspath directory_get_metadata_path(const Directory& dir) {
        fspath p = dir.path;
        return p / "_directory.cdm";
    }
    static fspath directory_get_boards_path(const Directory& dir) {
        fspath p = fspath(dir.path);
        return p / "boards"; 
    }
    static fspath directory_get_board_path(const Directory& dir, TaskBoard* board) {
        return directory_get_boards_path(dir) / board->name;
    }
    static void directory_write_metadata(const Directory& dir) {
        FILE* metadata;
        // First try to open the would-be metadata file
        metadata = std::fopen(directory_get_metadata_path(dir).string().c_str(), "wb");
        if (!metadata) throw Directory::invalid_path("Path invalid.");
        
        // Now write to file
        // Write magic
        std::fwrite(directory_magic,1,5,metadata);
        // Write version
        std::fwrite(&current_version,4,1,metadata);
        // Write name
        write_string(metadata,dir.name);

        // Write next board id
        std::fwrite(&(dir.next_id),4,1,metadata);
        // Write board num 
        uint32_t board_num = dir.boards.size();
        std::fwrite(&(board_num),4,1,metadata);

        // Write board IDs
        for (uint32_t i = 0; i < board_num; i += 1) {
            std::fwrite(&(dir.boards[i]->id),4,1,metadata);
        }

        std::fclose(metadata);
    }
    static bool directory_exists_at_path(std::string path) {
        fspath p = fspath(path);

        // Check root dir
        if (!std::filesystem::exists(p)) return false;
        // Now check metadata dir
        if (!std::filesystem::exists(p / "_directory.cdm")) return false;

        return true;
    }
    // Pass uninitialized Directory ref as dir
    static void directory_load_from_path(Directory& dir, std::string path) {
        FILE* metadata;
        char* buffer = nullptr;
        //FILE* action_log;
        dir.path = path;
        // Try to open file
        metadata = std::fopen(directory_get_metadata_path(dir).string().c_str(), "r+b");
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

    }
    // Pass uninitialized Directory ref as dir
    static void directory_new_at_path(Directory& dir, std::string path, std::string name) {
        dir.path = path;
        // Try to make root path
        if (!std::filesystem::create_directory(fspath(dir.path))) throw Directory::invalid_path("Path invalid.");

        // With file verified, now initialize directory
        dir.name = name;
        dir.boards = std::vector<TaskBoard*>{};
        dir.action_log = ActionLog();
        dir.next_id = 0;

        directory_write_metadata(dir);

        // Create boards directory
        std::filesystem::create_directory(directory_get_boards_path(dir));

    }

    static bool taskboard_path_exists(const TaskBoard& board) {
        fspath p = taskboard_get_path(board);
        // Check root dir
        if (!std::filesystem::exists(p)) return false;
        return true;
    }
    static fspath taskboard_get_path(const TaskBoard& board) {
        fspath p = directory_get_boards_path(*board.parent);
        return p / std::to_string(board.id);
    }
    static fspath taskboard_get_metadata_path(const TaskBoard& board) {
        return taskboard_get_path(board) / "_board.cbm";
    }
    static fspath taskboard_get_tasks_path(const TaskBoard& board) {
        return taskboard_get_path(board) / "tasks";
    }
    static fspath taskboard_get_members_path(const TaskBoard& board) {
        return taskboard_get_path(board) / "member_list.cml";
    }
    static fspath taskboard_get_notes_path(const TaskBoard& board) {
        return taskboard_get_path(board) / "note_list.cnl";
    }
    static fspath taskboard_get_categories_path(const TaskBoard& board) {
        return taskboard_get_path(board) / "category_list.ccl";
    }
    // Pass default-constructed TaskBoard ref
    static void taskboard_load(TaskBoard& board, uint32_t id) {
        FILE* metadata;
        char* buffer;
        board.id = id;
        metadata = std::fopen(taskboard_get_metadata_path(board).string().c_str(),"rb");
        if (!metadata) throw Directory::invalid_path("Error loading taskboard from path");
        // check magic
        buffer = new char[6];
        std::fread(buffer,1,5,metadata);
        if (strncmp(buffer,taskboard_magic,5)) throw Directory::invalid_path("Taskboard metadata invalid/corrupted");
        delete[] buffer;

        // Read id
        uint32_t read_id;
        std::fread(&read_id,4,1,metadata);
        if (read_id != board.id) throw Directory::invalid_path("Taskboard metadata invalid/corrupted");

        // Read board name
        board.name = read_string(metadata);
        // Read task num
        uint32_t task_num;
        std::fread(&task_num,4,1,metadata);
        // Read tasks
        // ...
    }
    static void taskboard_write_metadata(const TaskBoard& board) {
        FILE* metadata = std::fopen(taskboard_get_metadata_path(board).string().c_str(),"wb");
        if (!metadata) throw Directory::invalid_path("Path invalid.");
        // Write magic
        std::fwrite(taskboard_magic,1,5,metadata);
        // Write task board ID
        std::fwrite(&(board.id),4,1,metadata);
        // Write task board name
        write_string(metadata, board.name);
        // Write task #
        uint32_t task_num = board.tasks.size();
        std::fwrite(&task_num,4,1,metadata);
        // Write tasks paths
        // ...
    }
    static void taskboard_write(TaskBoard& board) {
        // Create root directory if needed
        if (!taskboard_path_exists(board)) {
            std::filesystem::create_directory(taskboard_get_path(board));
        }
        // write metadata
        taskboard_write_metadata(board);
        if (board.tasks_changed) {
            board.tasks_changed = false;
        }
        if (board.categories_changed) {
            board.categories_changed = false;
        }
        if (board.members_changed) {
            board.members_changed = false;
        }
        if (board.notes_changed) {
            board.notes_changed = false;
        }
    }

};

