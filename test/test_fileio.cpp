#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <lib/file_io.hpp>


bool compare_board(TaskBoard& board1, TaskBoard& board2) {
    if (board1.id != board2.id) return false;
    if (board1.name != board2.name) return false;
    //if (board1.get_tasks().size() != board2.get_tasks().size()) return false;
    // TODO: Compare tasks
    
    // TODO: Compare NotesList
    // TODO: Compare MemberList
    // TODO: Compare CategoryList
    return true;
}

bool compare_dir(Directory& dir1, Directory& dir2) {
    if (dir1.get_name() != dir2.get_name()) return false;
    
    if (dir1.get_boards().size() != dir2.get_boards().size()) return false;
    for (size_t i = 0; i < dir1.get_boards().size(); i += 1) {
        if (!compare_board(*dir1.get_boards()[i], *dir2.get_boards()[i])) return false;
    }
    // TODO: Compare ActionLog

    return true;
}

class FileIOTest : public testing::Test {
    protected:
    FileIOTest() {
        std::filesystem::create_directory("_test");
    }
    ~FileIOTest() {
        std::filesystem::remove_all("_test");
    }
};


// Tests whether or not the directory write/read functions can be ran, creating the expected folder and not throwing any errors
// Does not test correctness of the procedure
TEST_F(FileIOTest, DirectoryWriteReadOkay) {
    // Setup
    const std::string path ="_test/DirectoryWriteReadOkay";
    Directory dir;
    
    EXPECT_NO_THROW({
        FileIOManager::directory_new_at_path(dir,path,"test");
        FileIOManager::directory_load_from_path(dir,path);
    });
    bool exists = std::filesystem::exists(path);
    
    ASSERT_TRUE(exists);
    
};

// Tests whether a fresh directory written and read will still be equivalent
TEST_F(FileIOTest, EmptyDirectoryReadWriteMatch) {
    // setup 
    const std::string path ="_test/EmptyDirectoryReadWriteMatch";
    Directory dir;
    Directory dir2;

    EXPECT_NO_THROW({
        FileIOManager::directory_new_at_path(dir,path,"test");
        FileIOManager::directory_load_from_path(dir2,path);
    });

    EXPECT_TRUE(compare_dir(dir,dir2));
};

// Tests whether a directory will be the same after being written and read
TEST_F(FileIOTest, DirectoryReadWriteMatchAddBoards) {
    // setup 
    const std::string path ="_test/DirectoryReadWriteMatchAddBoards";
    Directory dir;
    Directory dir2;

    dir.add_board("board1");
    dir.add_board("board2");
    dir.add_board("board3");
    dir.add_board("board4");

    EXPECT_NO_THROW({
        FileIOManager::directory_new_at_path(dir,path,"test");
        FileIOManager::directory_load_from_path(dir2,path);
    });

    EXPECT_TRUE(compare_dir(dir,dir2));
};

TEST_F(FileIOTest, DirectoryReadWriteMatchAddRemoveBoards) {
    // setup 
    const std::string path ="_test/DirectoryReadWriteMatchAddRemoveBoards";
    Directory dir;
    Directory dir2;

    dir.add_board("board1");
    dir.add_board("board2");
    dir.add_board("board3");
    dir.add_board("board4");

    EXPECT_NO_THROW({
        FileIOManager::directory_new_at_path(dir,path,"test");
        FileIOManager::directory_load_from_path(dir2,path);
    });

    ASSERT_TRUE(compare_dir(dir,dir2));

    dir2.remove_board(dir2.get_board(0));
    FileIOManager::taskboard_delete(dir2,0);
    dir2.remove_board(dir2.get_board(2));
    FileIOManager::taskboard_delete(dir2,2);

    Directory dir3;
    EXPECT_NO_THROW({
        FileIOManager::directory_write_metadata(dir2);
        FileIOManager::directory_load_from_path(dir3,path);
    });

    EXPECT_TRUE(compare_dir(dir,dir3));

};