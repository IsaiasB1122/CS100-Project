
#include <DataEntry.hpp>

#include <algorithm>

DataEntry::DataEntry() {
    this->id = 0;
    this->name = "";
}

DataEntry::DataEntry(uint32_t id, std::string name) {
    this->id = id;
    this->name = name;
}

std::string DataEntry::to_string() {
    return "[ " + std::to_string(this->id) + " " + this->name + " ]";
}

std::vector<DataEntry*> DataEntry::filter_data(std::vector<DataEntry*> data, std::string filter, DataEntry::SORT_TYPE sort) {
    std::vector<DataEntry*> filtered_data;

    // If filter 
    if (filter.size() > 1) {
        for (auto d : data) {
            if (filter.size() > d->name.size()) continue;
            bool pass = false;
            for (auto data_name_i = 0; data_name_i < d->name.size(); data_name_i += 1) {
                for (auto query_name_i = 0; query_name_i < filter.size(); query_name_i += 1) {
                    if (data_name_i + query_name_i > d->name.size()) break;
                    if (filter[query_name_i] != d->name[data_name_i + query_name_i]) break;
                    if (query_name_i == filter.size()-1) {
                        pass = true;
                        goto end_check;
                    }
                }
            }
            end_check:
            if (pass) filtered_data.push_back(d);
        }
    }
    // Else just copy data
    else {
        for (auto d : data) filtered_data.push_back(d);
    }
    // Apply sort
    switch (sort) {
        case DataEntry::SORT_TYPE::NONE:
            break;
        case DataEntry::SORT_TYPE::ID:
        {
            struct {bool operator()(DataEntry* l, DataEntry* r) const { return l->id < r->id; }} compare;
            std::sort(filtered_data.begin(), filtered_data.end(), compare);
            break;
        }
        case DataEntry::SORT_TYPE::MODIFIED:
        {
            struct {bool operator()(DataEntry* l, DataEntry* r) const { return l->modified_time < r->modified_time; }} compare;
            std::sort(filtered_data.begin(), filtered_data.end(), compare);
            break;
        }
    }

    return filtered_data;
}