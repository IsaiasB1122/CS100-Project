
#include <CategoryList.hpp>

// TEMPORAY FOR STUBS, REMOVE WHEN ACTUALLY IMPLEMENTING!
const CategoryInfo dummy(0,"dummy");

CategoryList::CategoryList() {
    next_category_id = 0;
}

CategoryList::~CategoryList() {
    for (auto c : categories) {
        delete c;
    }
}
const std::vector<CategoryInfo*> CategoryList::get_categories() {
    return std::vector<CategoryInfo*>{};
}
const CategoryInfo& CategoryList::get_category(uint32_t id) {
    return dummy;
}
const CategoryInfo& CategoryList::get_category(std::string name) {
    return dummy;
}
const CategoryInfo& CategoryList::add_category(CategoryInfo category) {
    return dummy;
}
void CategoryList::remove_category(uint32_t id) {

}
void CategoryList::move_category(uint32_t id, uint32_t index) {

}
void CategoryList::rename_category(uint32_t id, std::string name) {

}