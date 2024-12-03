// TODO: Move exceptions to here and make a better variety
//  - And following add exceptions to all file-opening statements
// # 427, 457: Read and write tasks
#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <Directory.hpp>
#include <TaskBoard.hpp>

#include <cstring>

#include <filesystem>

typedef std::filesystem::path fspath;

const char directory_magic[6] = "CTBDN";
const char taskboard_magic[6] = "CTBBN";
const char categorylist_magic[5] = "CTCL";
const char memberlist_magic[5] = "CTML";
const char notelist_magic[5] = "CTNL";
const char task_magic[4] = "CTT";

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

        for (uint32_t i = 0; i < board_num; i += 1) {
            // Read ID
            uint32_t id;
            std::fread(&id,4,1,metadata);
            // Read board
            TaskBoard* board = new TaskBoard(&dir);
            taskboard_load(*board,id);

            dir.boards.push_back(board);
        }
        std::fclose(metadata);
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

    // Writes categoryinfo to given file
    static void category_info_write(const CategoryInfo& category, FILE* f) {
        // Write id
        std::fwrite(&category.id,4,1,f);
        // Write name
        write_string(f,category.name);
    }
    static void category_info_read(CategoryInfo& category, FILE* f) {
        std::fread(&category.id,4,1,f);
        category.name = read_string(f);
    }
    // Writes category list to given file
    static void category_list_write(const CategoryList& cl, FILE* f) {
        // Write magic
        std::fwrite(categorylist_magic,1,4,f);
        // Write next id
        std::fwrite(&cl.next_category_id,4,1,f);
        // Write category num
        uint32_t category_num = cl.categories.size();
        std::fwrite(&category_num,4,1,f);
        // Write categories
        for (uint32_t i = 0; i < category_num; i += 1) {
            category_info_write(*cl.categories[i],f);
        }
    }
    // Reads category list from given file
    static void category_list_read(CategoryList& cl, FILE* f) {
        // Check magic
        char buffer[4];
        std::fread(buffer,1,4,f);
        if (strncmp(buffer,categorylist_magic, 4)) throw Directory::invalid_path("CategoryList invalid/corrupted"); 
        // Read next id
        std::fread(&cl.next_category_id, 4, 1, f);
        // Read category num
        uint32_t category_num;
        std::fread(&category_num, 4, 1, f);
        for (uint32_t i = 0; i < category_num; i += 1) {
            CategoryInfo* category = new CategoryInfo;
            category_info_read(*category, f);
            cl.categories.push_back(category);
        }
    }

    // Writes member to given file
    static void member_write(const Member& member, FILE* f) {
        // Write id
        std::fwrite(&member.id, 4, 1, f);
        // Write name
        write_string(f, member.name);
    }
    // Reads member from file
    static void member_read(Member& member, FILE* f) {
        std::fread(&member.id,4,1,f);
        member.name = read_string(f);
    }
    // Writes member list to given file
    static void member_list_write(const MemberList& ml, FILE* f) {
        // Write magic
        std::fwrite(memberlist_magic,1,4,f);
        // Write next id
        std::fwrite(&ml.next_members_id,4,1,f);
        // Write member num
        uint32_t member_num = ml.members.size();
        std::fwrite(&member_num,4,1,f);
        // Write members
        for (uint32_t i = 0; i < member_num; i += 1) {
            member_write(*ml.members[i],f);
        }
    }
    // Reads member list from file
    static void member_list_read(MemberList& ml, FILE* f) {
        // Check magic
        char buffer[4];
        std::fread(buffer,1,4,f);
        if (strncmp(buffer,memberlist_magic, 4)) throw Directory::invalid_path("CategoryList invalid/corrupted"); 
        // Read next id
        std::fread(&ml.next_members_id, 4, 1, f);
        // Read member num
        uint32_t member_num;
        std::fread(&member_num, 4, 1, f);
        for (uint32_t i = 0; i < member_num; i += 1) {
            Member* member = new Member;
            member_read(*member, f);
            ml.members.push_back(member);
        }
    }

    // Writes note to file
    static void note_write(const Note& note, FILE* f) {
        // Write id
        std::fwrite(&note.id, 4, 1, f);
        // Write name
        write_string(f, note.name);
        // Write text
        write_string(f, note.text);
        // Write author id
        std::fwrite(&note.author_id, 4, 1, f);
        // Write time created
        uint64_t time_created = (uint64_t) note.creation_time;
        std::fwrite(&time_created,8,1,f);
        // Write time modified
        uint64_t time_modified = (uint64_t) note.modified_time;
        std::fwrite(&time_modified,8,1,f);
    }
    // Reads note from file
    static void note_read(Note& note, FILE* f) {
        std::fread(&note.id, 4, 1, f);
        note.name = read_string(f);
        note.text = read_string(f);
        std::fread(&note.author_id, 4, 1, f);
        uint64_t time_created;
        std::fread(&time_created,8,1,f);
        uint64_t time_modified;
        std::fread(&time_modified,8,1,f);
        note.creation_time = time_created;
        note.modified_time = time_modified;
    }

    static void note_list_write(const NoteList& nl, FILE* f) {
        // Write magic
        std::fwrite(notelist_magic,1,4,f);
        // Write next member id
        std::fwrite(&nl.next_note_id,4,1,f);
        // Write note num
        uint32_t note_num = nl.notes.size();
        std::fwrite(&note_num,4,1,f);
        // Write notes
        for (uint32_t i = 0; i < note_num; i += 1) {
            note_write(*nl.notes[i],f);
        }

    }
    static void note_list_read(NoteList& nl, FILE* f) {
        // check magic
        char buffer[4];
        std::fread(buffer,1,4,f);
        if (strncmp(buffer,notelist_magic, 4)) throw Directory::invalid_path("NoteList invalid/corrupted"); 
        // Read next id
        std::fread(&nl.next_note_id, 4, 1, f);
        // Write note num
        uint32_t note_num;
        std::fread(&note_num,4,1,f);
        // Read notes
        for (uint32_t i = 0; i < note_num; i += 1) {
            Note* note = new Note;
            note_read(*note, f);
            nl.notes.push_back(note);
        }
    }

    static fspath task_get_path(const Task& task, const TaskBoard& board) {
        return taskboard_get_tasks_path(board) / std::to_string(task.id);
    }
    static void task_write(const Task& task, const TaskBoard& board) {
        // Open file
        FILE* f = std::fopen(task_get_path(task, board).string().c_str(),"wb");
        // Write magic
        std::fwrite(task_magic,1,3,f);
        // Write id
        std::fwrite(&task.id,4,1,f);
        // Write name
        write_string(f, task.name);
        // Write category id
        std::fwrite(&task.category_id,4,1,f);
        // Write time created/modified
        uint64_t time_created = task.creation_time;
        std::fwrite(&time_created,8,1,f);
        uint64_t time_modified = task.modified_time;
        std::fwrite(&time_modified,8,1,f);
        // Write assigned member num
        uint32_t assigned_member_num = task.assigned_members.size();
        std::fwrite(&assigned_member_num,4,1,f);
        // Write assigned members
        for (uint32_t i = 0; i < assigned_member_num; i += 1) std::fwrite(&task.assigned_members[i],4,1,f);
        // Write notelist
        note_list_write(task.notes,f);

        std::fclose(f);
    }
    static void task_read(Task& task, const TaskBoard& board) {
        // Open file
        FILE* f = std::fopen(task_get_path(task, board).string().c_str(),"rb");
        // Check magic
        char buffer[3];
        std::fread(buffer,1,3,f);
        if (strncmp(buffer,task_magic,3)) throw Directory::invalid_path("Task invalid/corrupted");
        // Read id
        std::fread(&task.id,4,1,f);
        // Read name
        task.name =  read_string(f);
        // Read category id
        std::fread(&task.category_id, 4, 1, f);
        // Rdad time created/modified
        uint64_t time_created;
        std::fread(&time_created,8,1,f);
        uint64_t time_modified;
        std::fread(&time_modified,8,1,f);
        task.creation_time = time_created;
        task.modified_time = time_modified;
        // Read assigned member num
        uint32_t assigned_member_num;
        std::fread(&assigned_member_num,4,1,f);
        // read assigned members
        task.assigned_members.resize(assigned_member_num);
        for (uint32_t i = 0; i < assigned_member_num; i += 1) std::fread(&task.assigned_members[i],4,1,f);
        // Read notelist
        note_list_read(task.notes, f);

        std::fclose(f);
    }

    static bool taskboard_path_exists(const TaskBoard& board) {
        fspath p = taskboard_get_path(board);
        // Check root dir
        if (!std::filesystem::exists(p)) return false;
        return true;
    }
    static bool taskboard_tasks_path_exists(const TaskBoard& board) {
        fspath p = taskboard_get_tasks_path(board);
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

        // Read time created/modified
        uint64_t time_created;
        std::fread(&time_created,8,1,metadata);
        uint64_t time_modified;
        std::fread(&time_modified,8,1,metadata);
        board.creation_time = time_created;
        board.modified_time = time_modified;

        // Read board name
        board.name = read_string(metadata);
        // Read next task id
        std::fread(&board.next_task_id,4,1,metadata);
        // Read task num
        uint32_t task_num;
        std::fread(&task_num,4,1,metadata);
        // Read tasks
        for (uint32_t i = 0; i < task_num; i += 1) {
            Task* task = new Task;
            // Read task ID
            std::fread(&(task->id),4,1,metadata);

            task_read(*task, board);

            board.tasks.push_back(task);
        }

        // Read categorylist
        FILE* categorylist = std::fopen(taskboard_get_categories_path(board).string().c_str(),"rb");
        category_list_read(board.categories, categorylist);
        std::fclose(categorylist);
        // Read memberlist
        FILE* memberlist = std::fopen(taskboard_get_members_path(board).string().c_str(),"rb");
        member_list_read(board.members, memberlist);
        std::fclose(memberlist);
        // Read notes
        FILE* noteslist = std::fopen(taskboard_get_notes_path(board).string().c_str(),"rb");
        note_list_read(board.notes,noteslist);
        std::fclose(noteslist);

        std::fclose(metadata);
    }
    static void taskboard_write_metadata(const TaskBoard& board) {
        FILE* metadata = std::fopen(taskboard_get_metadata_path(board).string().c_str(),"wb");
        if (!metadata) throw Directory::invalid_path("Path invalid.");
        // Write magic
        std::fwrite(taskboard_magic,1,5,metadata);
        // Write task board ID
        std::fwrite(&(board.id),4,1,metadata);
        // Write time created/modified
        uint64_t time_created = board.creation_time;
        std::fwrite(&time_created,8,1,metadata);
        uint64_t time_modified = board.modified_time;
        std::fwrite(&time_modified,8,1,metadata);
        // Write task board name
        write_string(metadata, board.name);
        // Write next task id
        std::fwrite(&board.next_task_id,4,1,metadata);
        // Write task #
        uint32_t task_num = board.tasks.size();
        std::fwrite(&task_num,4,1,metadata);
        // Write tasks IDs
        for (uint32_t i = 0; i < task_num; i += 1) {
            std::fwrite(&(board.tasks[i]->id),4,1,metadata);
        }

        std::fclose(metadata);
    }
    static void taskboard_write(TaskBoard& board) {
        // Create root directory if needed
        if (!taskboard_path_exists(board)) {
            std::filesystem::create_directory(taskboard_get_path(board));
        }
        // Create tasks directory if needed
        if (!taskboard_tasks_path_exists(board)) {
            std::filesystem::create_directory(taskboard_get_tasks_path(board));
        }
        // write metadata
        taskboard_write_metadata(board);
        // Write any takss that have been changed
        for (auto task : board.tasks) {
            if (task->changed) {
                task->changed = false;
                task_write(*task, board);
            }
        }
        if (board.categories_changed) {
            FILE* categorylist = std::fopen(taskboard_get_categories_path(board).string().c_str(),"wb");
            category_list_write(board.categories, categorylist);
            std::fclose(categorylist);
            board.categories_changed = false;
        }
        if (board.members_changed) {
            FILE* memberlist = std::fopen(taskboard_get_members_path(board).string().c_str(),"wb");
            member_list_write(board.members, memberlist);
            std::fclose(memberlist);
            board.members_changed = false;
        }
        if (board.notes_changed) {
            FILE* notelist = std::fopen(taskboard_get_notes_path(board).string().c_str(),"wb");
            note_list_write(board.notes, notelist);
            std::fclose(notelist);
            board.notes_changed = false;
        }
    }
    static void taskboard_delete(Directory& dir, uint32_t id) {
        // Dummy just to get path
        TaskBoard board(&dir);
        board.id = id;
        fspath p = taskboard_get_path(board);

        std::filesystem::remove_all(p);
    }

};

#endif