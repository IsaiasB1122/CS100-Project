#include <Commands.hpp>
#define register_command(n, c) CommandManager::command_map[n] = new c; CommandManager::command_map[n]->parent = this;

// Include command headers here
#include <Exit.cpp>
#include <Add-Board.cpp>
#include <Remove-Board.cpp>
#include <Add-Category.cpp>
#include <Help.cpp>
#include <Add-Board-Note.cpp>
#include <Add-Member.cpp>
#include <Add-Task.cpp>
#include <Assign-Member.cpp>
#include <Categorize-Task.cpp>
#include <List-Board-Notes.cpp>
#include <List-Boards.cpp>
#include <List-Categories.cpp>
#include <List-Members.cpp>
#include <List-Tasks.cpp>
#include <Move-Category.cpp>
#include <Remove-Board-Note.cpp>
#include <Remove-Category.cpp>
#include <Remove-Member.cpp>
#include <Remove-Task.cpp>
#include <Set.cpp>
#include <Show-Board-Note.cpp>
#include <Show-Task.cpp>
#include <Summary.cpp>
#include <Unset.cpp>

void CommandManager::_index_commands() {
    // Include command registering here
    register_command("exit", CommandExit);
    register_command("add-board",CommandAddBoard);
    register_command("remove-board",CommandRemoveBoard);
    register_command("help", CommandOutputHelp);
    register_command("add-board-note",CommandAddBoardNote);
    register_command("add-category",CommandAddCategory);
    register_command("add-member",CommandAddMember);
    register_command("add-task",CommandAddTask);
    register_command("assign-member",CommandAssignMember);
    register_command("categorize-task",CommandCategorizeTask);
    register_command("list-board-notes",CommandListBoardNotes);
    register_command("list-boards",CommandListBoards);
    register_command("list-categories",CommandListCategories);
    register_command("list-members",CommandListMembers);
    register_command("list-tasks",CommandListTasks);
    register_command("move-category",CommandMoveCategory);
    register_command("remove-board-note",CommandRemoveBoardNote);
    register_command("remove-category", CommandRemoveCategory);
    register_command("remove-member",CommandRemoveMember);
    register_command("remove-task",CommandRemoveTask);
    register_command("set",CommandSet);
    register_command("show-board-note",CommandShowBoardNote);
    register_command("show-task",CommandShowTask);
    register_command("summary",CommandSummary);
    register_command("unset",CommandUnset);
}