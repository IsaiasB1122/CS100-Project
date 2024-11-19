#include <Commands.hpp>
#include <TaskBoard.hpp>

class CommandAddCategory : public Command {
public:
    CommandAddCategory(TaskBoard* board) : board(board) {}

    void execute(std::vector<std::string>& args) override {
        if (args.size() < 2) {
            std::cout << "Error: Please provide a category name." << std::endl;
            return;
        }

        std::string category_name = args[1];
        board->add_category(category_name);
        std::cout << "Category '" << category_name << "' added successfully." << std::endl;
    }

private:
    TaskBoard* board;
};