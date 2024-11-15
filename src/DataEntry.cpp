
#include <DataEntry.hpp>

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