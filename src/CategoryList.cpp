
#include <CategoryList.hpp>

CategoryList::CategoryList() {
    next_category_id = 0;
}

CategoryList::~CategoryList() {
    for (auto c : categories) {
        delete c;
    }
}

CategoryInfo* CategoryList::add_category(CategoryInfo category) {
    category.id = this->next_category_id++;
    categories.push_back(new CategoryInfo(category));
    return categories.back();
}

void CategoryList::remove_category(uint32_t id) {
    auto it = std::find_if(categories.begin(), categories.end(), [id](CategoryInfo* category) {
        return category->id == id;
    });

    if (it != categories.end()) {
        delete *it;
        categories.erase(it);
    }
}