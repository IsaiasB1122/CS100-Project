#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <Directory.hpp>
#include <Commands.hpp>
#include <lib/file_io.hpp>
#include <filesystem>



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