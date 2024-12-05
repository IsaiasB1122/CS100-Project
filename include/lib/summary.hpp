// Generating the summary well is not cross-platform due to requiring methods to get the terminal width
#ifndef SUMMARY_HPP
#define SUMMARY_HPP

#include <list>
#include <iostream>
#include <iomanip>
#include <Directory.hpp>


// macro for line
#define print_line(out, width) out << '|'; for (unsigned int i = 0; i < width-2; i += 1) out << '-'; out << '|' << std::endl;;
// macro for entry text
#define print_entry(out, width, entry) out << "| "; \
unsigned int left = (width - entry.size())/2; \
unsigned int right = width - entry.size() - left; \
for (unsigned int i = 0; i < left; i += 1) {out << ' ';} \
out << entry; \
for (unsigned int i = 0; i < right; i += 1) {out << ' ';} \
out << " |";


void print_summary(std::ostream& out, TaskBoard& board, uint32_t start_category, uint32_t end_category, uint32_t max_num) {
    // Get category list
    std::vector<CategoryInfo*> categories;
    const std::vector<CategoryInfo*> _categories = board.categories.get_categories();
    for (unsigned int i = start_category; (i < end_category) and (i < _categories.size()); i += 1 ) {
        categories.push_back(_categories[i]);
    }
    unsigned int col_num = categories.size();
    // Get tasks
    std::vector<Task*> tasks = board.get_tasks();
    
    // The longest string on any column
    unsigned int max_size = 0;
    // First set to the length of each category title
    for (auto category : categories) {
        if ((category->name.size()) > max_size) max_size = (category->name.size());
    }

    // Generate map of categories to tasks
    std::map<uint32_t, std::list<Task*>> category_tasks_map;
    for (auto task : tasks) category_tasks_map[task->category_id].push_front(task);

    // Generate table data
    std::vector<std::vector<Task*>> table;
    for (unsigned int row = 0; row < max_num; row += 1) {
        // This row
        std::vector<Task*>& this_row = table.emplace_back();
        bool real_added = false;
        for (unsigned int col = 0; col < col_num; col += 1) {
            if (category_tasks_map[categories[col]->id].empty()) this_row.push_back(nullptr);
            else {
                real_added = true;
                // Get next task in category to add
                Task*& t = category_tasks_map[categories[col]->id].back();
                // Update max size
                unsigned int size = (t->name + std::to_string(t->id)).size()+1; // Account for ID
                if (size > max_size) max_size = size;
                this_row.push_back(t);
                category_tasks_map[categories[col]->id].pop_back();
            }
        }
        // If no new entires were found for this row, end generation
        if (!real_added) {
           table.pop_back();
           goto done;
        }
    }
    done:
    // Calculate needed width
    unsigned int width = 2;
    width += (max_size + 4)*col_num;

    // Top line
    print_line(out,width);
    // Categoryies
    out << "|";
    for (auto category : categories) {
       print_entry(out,max_size,category->name);
       2;
    }
    out << "|" << std::endl;
    print_line(out,width);
    // Tasks
    for (auto row : table) {
        out << "|";
        for (auto entry : row) {
            std::string entry_text;
            if (entry == nullptr) {
                entry_text = std::string(max_size, ' ');
            }
            else
            {
                entry_text = std::to_string(entry->id) + " " + entry->name;
            }
            print_entry(out,max_size,entry_text);
        }
        out << "|" << std::endl;
    }

    
    
    print_line(out,width);
}


#endif