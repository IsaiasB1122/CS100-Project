#ifndef INCLUDE_CATEGORY_LIST_HPP
#define INCLUDE_CATEGORY_LIST_HPP

#include <cstdint>
#include <vector>

#include <CategoryInfo.hpp>


class CategoryList {
    std::vector<CategoryInfo*> categories;
    uint32_t next_category_id;
public:
    const std::vector<CategoryInfo*> get_categories();
    const CategoryInfo& get_category(uint32_t id);
    const CategoryInfo& get_category(std::string name);
    const CategoryInfo& add_category(CategoryInfo category);
    void remove_category(uint32_t id);
    void move_ctagory(uint32_t id, uint32_t index);
    void rename_category(uint32_t id, std::string name);

    std::vector<unsigned char> serialize();
    static CategoryList deserialize(std::vector<unsigned char> data);

    std::vector<CategoryInfo*> filter_category_name(std::string query, DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE);
};


#endif
