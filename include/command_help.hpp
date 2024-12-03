#ifndef COMMAND_HELP_HPP
#define COMMAND_HELP_HPP

#define COMMAND_HELP_EXIT \
"Exits program." \

#define COMMAND_HELP_ADD_BOARD \
"add-board <name>\n" \
"Creates a new board with a given name"

#define COMMAND_HELP_REMOVE_BOARD \
"remove-board <board>\n"\
"Deletes a board with a given name"

#define COMMAND_HELP_OUTPUT_HELP \
"Prints all commands available to user if command is not given.\n\
Otherwise, prints help message of the given command."

#define COMMAND_HELP_ADD_BOARD_NOTE \
"add-board-note <title> <text> <author> <board>\n"\
"Creates a new board note with the given name"

#define COMMAND_HELP_ADD_CATEGORY \
"add-category <name> <board>\n"\
"Adds a category with the given name to the given board"

#define COMMAND_HELP_ADD_MEMBER \
"add-member <name> <board>\n"\
"Adds member to a board"

#define COMMAND_HELP_ADD_TASK \
"add-task <name> <board> [category]\n"\
"Adds task to a board. Category is optional."

#define COMMAND_HELP_ASSIGN_MEMBER \
"assign-member <task> <member> <board>\n"\
"Assigns a task to a member of a board."

#define COMMAND_HELP_CATEGORIZE_TASK \
"categorize-task <task> <category> <board>\n"\
"Sets task's category to new category."

#define COMMAND_HELP_LIST_BOARD_NOTES \
"list-board-notes <board> [filter] [sort] [full]\n"\
"Returns list of boards."

#define COMMAND_HELP_LIST_BOARDS  \
"list-boards [filter]\n"\
"Lists all boards that have been created."

#define COMMAND_HELP_LIST_CATEGORIES \
"list-categories <board>\n"\
"Lists categories in a given board\n" \
"Listed in the order they are shown on the summary left->right"

#define COMMAND_HELP_LIST_MEMBERS \
"list-members <board> [filter]\n"\
"List the members of a board. Filter is optional."

#define COMMAND_HELP_LIST_TASKS \
"list-tasks <board> [filter] [category] [sort]\n"\
"Lists tasks in the board. The filter will filter by task name.\n"\
"Category filters by category\n" \
"Sort accepts options ID, RECENT, OLD. Defaults to ID\n"\
"Recent = Most recently modified. Old = Least recently modified"

#define COMMAND_HELP_MOVE_CATEGORY \
"move-category <category> <position> <board>\n"\
"Moves the category to the given position (starting from 1)"

#define COMMAND_HELP_REMOVE_BOARD_NOTE \
"remove-board-note <note> <board>\n"\
"Removes a given note from a board."

#define COMMAND_HELP_REMOVE_CATEGORY \
"remove-category <category> <board>\n"\
"Removes the category with given id from the given board."

#define COMMAND_HELP_REMOVE_MEMBER \
"remove-member <member> <board>\n"\
"Removes a member of a given board."

#define COMMAND_HELP_REMOVE_TASK \
"remove-task <task> <board>\n"\
"Removes a task of a given board."

#define COMMAND_HELP_SET \
"set [...]\n"\
"Sets the given parameter name's saved value to be the value\n" \
"Until unset is run with that same name,\n" \
"all parameters with that name will get that value"

#define COMMAND_HELP_SHOW_BOARD_NOTE \
"show-board-note <note> <board>\n"\
"Shows the note of a given board."

#define COMMAND_HELP_SHOW_TASK \
"show-task <task> <board>\n"\
"Shows the task of a given board"

#define COMMAND_HELP_SUMMARY \
"summary <board> [start] [end]\n"\
"Prints a pretty kanban-style summary"\

#define COMMAND_HELP_UNSET \
"unset <name>\n"\
"Unsets the given parameter"

#endif