#include <Commands.hpp>
#include <TaskBoard.hpp>

class CommandRemoveCategory : public Command {
public:
    CommandRemoveCategory(TaskBoard* board) : board(board) {}

    void execute(std::vector<std::string>& args) override {
        if (args.size() < 2) {
            std::cout << "Error: Please provide a category ID." << std::endl;
            return;
        }

        uint32_t category_id = std::stoi(args[1]);
        board->remove_category(category_id);
        std::cout << "Category with ID " << category_id << " Removed successfully." << std::endl;
    }

private:
    TaskBoard* board;
};