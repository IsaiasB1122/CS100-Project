
#include <CategoryList.hpp>

CategoryList::CategoryList() {
    next_category_id = 0;
}

CategoryList::~CategoryList() {
    for (auto c : categories) {
        delete c;
    }
}