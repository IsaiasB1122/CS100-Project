#ifndef INCLUDE_DATA_ENTRY_HPP
#define INCLUDE_DATA_ENTRY_HPP

#include <cstdint>
#include <string>
#include <vector>
#include <ctime>

class DataEntry {
public:
    enum SORT_TYPE {NONE, ID, MODIFIED};
    uint32_t id;
    std::string name;
    std::time_t creation_time;
    std::time_t modified_time;

    DataEntry();
    DataEntry(uint32_t id, std::string name);

    static std::vector<DataEntry*> filter_data(std::vector<DataEntry*> data, std::string filter = "", SORT_TYPE sort = SORT_TYPE::NONE);
    std::string to_string() const;
};


#endif
