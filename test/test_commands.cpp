#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <Directory.hpp>
#include <Commands.hpp>
#include <lib/file_io.hpp>
#include <filesystem>
#include <string>



class CommandsTest : public testing::Test {
    protected:
    CommandManager manager;
    CommandsTest() {
        manager.init();
        manager.dir = new Directory;
        std::filesystem::create_directory("_test");
        FileIOManager::directory_new_at_path(*manager.dir,"_test/_testdir","testdir");
    }
    ~CommandsTest() {
        std::filesystem::remove_all("_test");
        delete manager.dir;
    }
};


TEST_F(CommandsTest, testEmptyLine) {
    std::stringstream in;
    std::stringstream out;

    in << "" << std::endl;

    auto result = manager.parse_command(in, out);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::BAD_COMMAND);
};

TEST_F(CommandsTest, testBadcommand) {
    std::stringstream in;
    std::stringstream out;

    in << "asdffdafsdfaf" << std::endl;

    auto result = manager.parse_command(in, out);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::BAD_COMMAND);
};

TEST_F(CommandsTest, testAddBoard1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    in << "add-board board" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "ADD BOARD [ 0 board ]");
    EXPECT_EQ(manager.dir->get_board(0)->name,"board");
}

TEST_F(CommandsTest, testAddBoard2) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    in << "add-board --name board" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "ADD BOARD [ 0 board ]");
    EXPECT_EQ(manager.dir->get_board(0)->name,"board");

    in << "add-board board2" << std::endl;

    result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "ADD BOARD [ 1 board2 ]");
    EXPECT_EQ(manager.dir->get_board(1)->name,"board2");
}

TEST_F(CommandsTest, testRemoveBoardError1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    in << "remove-board board" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_THAT(output, testing::HasSubstr("ERROR"));
}

TEST_F(CommandsTest, testRemoveBoardError2) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    in << "remove-board --board 0" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_THAT(output, testing::HasSubstr("ERROR"));
}

TEST_F(CommandsTest, testAddRemoveBoard1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    in << "add-board board" << std::endl;
    in << "remove-board board" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "ADD BOARD [ 0 board ]");
    EXPECT_EQ(manager.dir->get_board(0)->name,"board");

    result = manager.parse_command(in, out);
    std::getline(out, output);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "REMOVE BOARD [ 0 board ]");
    EXPECT_EQ(manager.dir->get_boards().size(),0);
}

TEST_F(CommandsTest, testSet1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    in << "set --board 0" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "board = 0");
    ASSERT_TRUE(manager.set_parameters.count("board") == 1);
    EXPECT_EQ(manager.set_parameters["board"], "0");
}

TEST_F(CommandsTest, testSet2) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    in << "set --board 1 --author Bob" << std::endl;

    auto result = manager.parse_command(in, out);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    std::getline(out, output);
    EXPECT_EQ(output, "board = 1");
    std::getline(out, output);
    EXPECT_EQ(output, "author = Bob");
    ASSERT_TRUE(manager.set_parameters.count("board") == 1);
    ASSERT_TRUE(manager.set_parameters.count("author") == 1);
    EXPECT_EQ(manager.set_parameters["board"], "1");
    EXPECT_EQ(manager.set_parameters["author"], "Bob");
}

TEST_F(CommandsTest, testUnset1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    manager.set_parameters["board"] = "b";

    in << "unset board" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "board unset");
    ASSERT_TRUE(manager.set_parameters.count("board") == 0);
}

TEST_F(CommandsTest, testUnset2) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    manager.set_parameters["author"] = "xb";

    in << "unset author" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "author unset");
    ASSERT_TRUE(manager.set_parameters.count("author") == 0);
}

TEST_F(CommandsTest, testListBoards1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    manager.dir->add_board("Board1");
    manager.dir->add_board("Task Board Group 1");
    manager.dir->add_board("Group 2");

    in << "list-boards" << std::endl;

    auto result = manager.parse_command(in, out);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    
    std::getline(out, output);
    EXPECT_EQ(output, "[ 0 Board1 ]");
    std::getline(out, output);
    EXPECT_EQ(output, "[ 1 Task Board Group 1 ]");
    std::getline(out, output);
    EXPECT_EQ(output, "[ 2 Group 2 ]");
}

TEST_F(CommandsTest, testListBoards2) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    manager.dir->add_board("Board1");
    manager.dir->add_board("Task Board Group 1");
    manager.dir->add_board("Group 2");

    in << "list-boards board" << std::endl;

    auto result = manager.parse_command(in, out);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    
    std::getline(out, output);
    EXPECT_EQ(output, "[ 0 Board1 ]");
    std::getline(out, output);
    EXPECT_EQ(output, "[ 1 Task Board Group 1 ]");
}

TEST_F(CommandsTest, testAddBoardNote1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    TaskBoard* board = manager.dir->add_board("Board2");
    board->members.add_member(Member(3,"Siddharth"));

    in << "add-board-note \"TODO: Finish task categories\" \"We need to add more task categories.\nI hope we can meet sometime!\" --author Siddharth --board Board2" << std::endl;

    auto result = manager.parse_command(in, out);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    
    std::getline(out, output);
    EXPECT_EQ(output, "ADD NOTE [ 0 TODO: Finish task categories ]");
    
    ASSERT_EQ(board->notes.get_notes().size(),1);
    EXPECT_EQ(board->notes.get_note(0).name,"TODO: Finish task categories");
    EXPECT_EQ(board->notes.get_note(0).text,"We need to add more task categories.\nI hope we can meet sometime!");
    EXPECT_EQ(board->notes.get_note(0).author_id, 3);


}

TEST_F(CommandsTest, testRemoveBoardNote1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    Member dummy(0,"dummy");
    TaskBoard* board = manager.dir->add_board("Board2");
    board->notes.add_note("TODO: Finish task categories","",dummy);

    in << "remove-board-note 0 Board2" << std::endl;

    auto result = manager.parse_command(in, out);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    
    std::getline(out, output);
    EXPECT_EQ(output, "REMOVE NOTE [ 0 TODO: Finish task categories ]");

    // Test side effects
    ASSERT_EQ(board->notes.get_notes().size(),0);
}



TEST_F(CommandsTest, testListBoardNotes1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    TaskBoard* board = manager.dir->add_board("Board2");
    Member m0 = board->members.add_member(Member(0,"Amanda"));
    Member m1 = board->members.add_member(Member(1,"Siddharth"));
    board->notes.add_note("TODO: Finish task categories",
    "We need more task categories.\nI hope we can meet sometime!",m0);
    board->notes.add_note("RE: TODO: Finish task categories",
    "But I thought we already made all of them? :p",m1);
    

    in << "list-board-notes Board2" << std::endl;

    auto result = manager.parse_command(in, out);
    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    
    std::getline(out, output);
    EXPECT_EQ(output, "[ 0 TODO: Finish task categories ]");
    std::getline(out, output);
    EXPECT_EQ(output, "[ 1 RE: TODO: Finish task categories ]");
}

TEST_F(CommandsTest, testAddCategory1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    TaskBoard* board = manager.dir->add_board("Board1");

    in << "add-category Finished Board1" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "ADD CATEGORY [ 1 Finished ]");
    ASSERT_EQ(board->categories.get_categories().size(),2);
    EXPECT_EQ(board->categories.get_category(0).name,"Finished");
}
TEST_F(CommandsTest, testAddCategory2) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    TaskBoard* board = manager.dir->add_board("Board1");

    in << "add-category \"In Testing\" --board Board1" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(result, CommandManager::COMMAND_PARSE_RESULT::OK);
    EXPECT_EQ(output, "ADD CATEGORY [ 1 In Testing ]");
    ASSERT_EQ(board->categories.get_categories().size(),2);
    EXPECT_EQ(board->categories.get_category(0).name,"Finished");
}
TEST_F(CommandsTest, testRemoveCategory1) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    TaskBoard* board = manager.dir->add_board("Board1");
    board->categories.add_category(CategoryInfo(1,"Finished"));
    board->categories.add_category(CategoryInfo(2,"In Testing"));

    in << "remove-category \"In Testing\" --board Board1" << std::endl;

  

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(output, "REMOVE CATEGORY [ 2 In Testing ]");

    ASSERT_EQ(board->categories.get_categories().size(), 2);
}
TEST_F(CommandsTest, testRemoveCategory2) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    TaskBoard* board = manager.dir->add_board("Board1");
    board->categories.add_category(CategoryInfo(1,"Finished"));
    board->categories.add_category(CategoryInfo(2,"In Testing"));

    in << "remove-category 1 --board Board1" << std::endl;

  

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_EQ(output, "REMOVE CATEGORY [ 1 Finished ]");

    ASSERT_EQ(board->categories.get_categories().size(), 2);
}

TEST_F(CommandsTest, testRemoveCategory3) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    TaskBoard* board = manager.dir->add_board("Board1");
    board->categories.add_category(CategoryInfo(1,"Finished"));
    board->categories.add_category(CategoryInfo(2,"In Testing"));

    in << "remove-category 0 --board Board1" << std::endl;

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

    EXPECT_THAT(output, testing::HasSubstr("ERROR"));

    ASSERT_EQ(board->categories.get_categories().size(), 3);
}






TEST_F(CommandsTest, testRemoveCategoryx) {
    std::stringstream in;
    std::stringstream out;
    std::string output;

    // pre
    TaskBoard* board = manager.dir->add_board("Board1");

  

    auto result = manager.parse_command(in, out);
    std::getline(out, output);

}