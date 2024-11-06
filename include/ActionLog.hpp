#ifndef INCLUDE_ACTION_LOG_HPP
#define INCLUDE_ACTION_LOG_HPP

#include <cstdint>
#include <vector>
#include <ActionLogItem.hpp>



class ActionLog {
    std::vector<ActionLogItem> items;
public:
    void add_action(std::string action, std::string user);
    const std::vector<ActionLogItem*> get_actions();
};


#endif
