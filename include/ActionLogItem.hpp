#ifndef INCLUDE_ACTION_LOG_ITEM_HPP
#define INCLUDE_ACTION_LOG_ITEM_HPP

#include <cstdint>
#include <ctime>
#include <string>
#include <vector>




class ActionLogItem {
public:
    uint32_t id;
    std::string action;
    std::time_t timestamp;
    std::string user;
};


#endif
