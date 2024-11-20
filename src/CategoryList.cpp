
#include <CategoryList.hpp>
#include <stdexcept> 

CategoryList::CategoryList() {
    next_category_id = 0;
}

CategoryList::~CategoryList() {
    for (auto c : categories) {
        delete c;
    }
}

const std::vector<CategoryInfo*> CategoryList::get_categories() {
    return categories;
}

const CategoryInfo& CategoryList::get_category(uint32_t id) {
    for (CategoryInfo* category : categories) {
        if (category->id == id) {
            return *category;
        }
    }
    throw std::invalid_argument("Category with the given ID does not exist.");
}

const CategoryInfo& CategoryList::get_category(std::string name) {
    for (CategoryInfo* category : categories) {
        if (category->name == name) {
            return *category;
        }
    }
    throw std::invalid_argument("Category with the given name does not exist.");
}

const CategoryInfo& CategoryList::add_category(CategoryInfo category) {
    category.id = next_category_id++; // Assign a unique ID to the category
    CategoryInfo* new_category = new CategoryInfo(category);
    categories.push_back(new_category);
    return *new_category;
}

void CategoryList::remove_category(uint32_t id) {
    for (auto it = categories.begin(); it != categories.end(); ++it) {
        if ((*it)->id == id) {
            delete *it; // Free memory
            categories.erase(it); // Remove from the list
            return;
        }
    }
    throw std::invalid_argument("Category with the given ID does not exist.");
}