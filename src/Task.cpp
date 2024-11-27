
#include <Task.hpp>
#include <TaskBoard.hpp>
#include <stdexcept>

std::string Task::to_string(TaskBoard& board) const {
    std::string category_name;
    try  {
        category_name = board.categories.get_category(this->category_id).name;
    }
    catch(const std::invalid_argument){
        category_name = "<DELETED>";
    }
    return "[ " + std::to_string(this->id) + ' ' + category_name +  ' ' + this->name + " ]";
}