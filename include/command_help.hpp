#ifndef COMMAND_HELP_HPP
#define COMMAND_HELP_HPP

#define COMMAND_HELP_EXIT \
"Exits program."

#define COMMAND_HELP_ADD_BOARD \
"Creates a new board with a given name"

#define COMMAND_HELP_REMOVE_BOARD \
"Deletes a board with a given name"

#define COMMAND_HELP_OUTPUT_HELP \
"Prints all commands available to user if command is not given.\n\
Otherwise, prints help message of the given command."

#define COMMAND_HELP_ADD_BOARD_NOTE \
"Creates a new board note with the given name"

#define COMMAND_HELP_ADD_CATEGORY \
"Adds a category with the given name to the given board"

#define COMMAND_HELP_ADD_MEMBER \
"Adds member to a board"

#define COMMAND_HELP_ADD_TASK \
"Adds task to a board. Category is optional."

#define COMMAND_HELP_ASSIGN_MEMBER \
"Assigns a task to a member of a board."

#define COMMAND_HELP_CATEGORIZE_TASK \
"Sets task's category to new category."

#define COMMAND_HELP_LIST_BOARD_NOTES \
"Returns list of boards, filtered by [filter]."

#define COMMAND_HELP_LIST_BOARDS  \
"Lists all boards that have been created."

#define COMMAND_HELP_LIST_CATEGORIES \
"Lists categories in a given board\n" \
"Listed in the order they are shown on the summary left->right"

#define COMMAND_HELP_LIST_MEMBERS \
"List the members of a board. Filter is optional."

#define COMMAND_HELP_LIST_TASKS \
"Lists tasks in the board. The filter will filter by task name.\n"\
"Category filters by category\n" \
"Sort accepts options ID, RECENT, OLD. Defaults to ID\n"\
"Recent = Most recently modified. Old = Least recently modified"

#define COMMAND_HELP_MOVE_CATEGORY \
"Moves the category to the given position (starting from 1)"

#define COMMAND_HELP_REMOVE_BOARD_NOTE \
"Removes a given note from a board."

#define COMMAND_HELP_REMOVE_CATEGORY \
"Removes the category with given id from the given board."

#define COMMAND_HELP_REMOVE_MEMBER \
"Removes a member of a given board."

#define COMMAND_HELP_REMOVE_TASK \
"Removes a task of a given board."

#define COMMAND_HELP_SET \
"Sets the given parameter name's saved value to be the value\n" \
"Until unset is run with that same name,\n" \
"all parameters with that name will get that value"

#define COMMAND_HELP_SHOW_BOARD_NOTE \
"Shows the note of a given board."

#define COMMAND_HELP_SHOW_TASK \
"Shows the task of a given board"

#define COMMAND_HELP_SUMMARY \
"Prints a pretty kanban-style summary"\

#define COMMAND_HELP_UNSET \
"Unsets the given parameter"

#endif