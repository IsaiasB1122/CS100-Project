#include <CategoryList.hpp>
#include <stdexcept> 
#include <algorithm>

CategoryList::CategoryList() {
    next_category_id = 0;
}

CategoryList::~CategoryList() {
    for (auto c : categories) {
        delete c;
    }
}


uint32_t CategoryList::move_category(uint32_t id, uint32_t index) {
    if (index >= categories.size()) {
        throw std::out_of_range("Target index is out of range.");
    }

    auto it = std::find_if(categories.begin(), categories.end(),
    [id](const CategoryInfo* category) { return category->id == id; });

    uint32_t old_index = it - categories.begin();

    if (it == categories.end()) {
        throw std::invalid_argument("Category with the given ID does not exist.");
    }

    CategoryInfo* category = *it;
    categories.erase(it);  // Remove from the current position
    categories.insert(categories.begin() + index, category);

    return old_index;
}

void CategoryList::rename_category(uint32_t id, std::string name) {

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
    categories.push_back(new CategoryInfo(category));
    return *categories.back();
}

void CategoryList::remove_category(uint32_t id) {
    for (auto it = categories.begin(); it < categories.end(); it += 1) {
        if ((*it)->id == id)
        {
            CategoryInfo* tp = *it;
            categories.erase(it);
            delete tp;
            return;
        }
    }
    throw std::logic_error("Bad call to remove_category on missing id");
}