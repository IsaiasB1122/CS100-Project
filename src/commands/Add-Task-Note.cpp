#include <Commands.hpp>
#include <lib/dir_helpers.hpp>
#include <lib/file_io.hpp>
#include <TaskBoard.hpp>
#include <iostream>

class CommandAddTaskNote : public Command {
public:
std::string get_name() {
        return "add-task-note";
    }
    std::string get_help() {
        return COMMAND_HELP_ADD_TASK_NOTE;
    }
    std::vector<std::string> get_required_parameters() {return {"title","text","board", "task"};};
    std::vector<std::string> get_optional_parameters() {return {"author"};};
    CommandManager::COMMAND_RUN_RESULT run(CommandParametersData parameters, std::ostream& out) {
        //first, get the board
        TaskBoard* board = get_board(*this->parent->dir, parameters.get_parameter("board"));
        if (board == nullptr) {
            out << "ERROR: Board [" << parameters.get_parameter("board") << "] is not found." << std::endl;
            return CommandManager::COMMAND_RUN_RESULT::ERROR; 
        }
        uint32_t author_id = -1; // -1 will just be largest u32.
        if (parameters.has_parameter("author")) {
            try {
                author_id = get_member(*board,parameters.get_parameter("author")).id;
            }
            catch(const std::invalid_argument e)
            {
                out << "ERROR: Member [" << parameters.get_parameter("author") << "] does not exist." << std::endl;
                return CommandManager::COMMAND_RUN_RESULT::ERROR;
            }
        }
        //assign a note to a task.
        //first, get the task
        const Task& getTask = get_task(*board, parameters.get_parameter("task"));
        //initialize another object so the "changed" memeber can be modified
        Task task = getTask;
        
        //get the notes
        NoteList& notes = task.notes;   
        const Note& n = notes.add_note(parameters.get_parameter("title"), parameters.get_parameter("text"), author_id);
    
        task.changed = true;
        FileIOManager::taskboard_write(*board);
        
        out << "ADD TASK NOTE " << n.to_string() << std::endl;
        return CommandManager::COMMAND_RUN_RESULT::GOOD;

        //task object has a notelist member
        //everything would be under notelist task
    }
};