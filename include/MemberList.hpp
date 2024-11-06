#ifndef INCLUDE_MEMBER_LIST_HPP
#define INCLUDE_MEMBER_LIST_HPP

#include <cstdint>
#include <vector>

#include <Member.hpp>


class MemberList {
    std::vector<Member*> members;
    uint32_t next_members_id;
public:
    const std::vector<Member*> get_members();
    const Member& get_member(uint32_t id);
    const Member& get_member(std::string name);
    const Member& add_member(Member category);
    void remove_member(uint32_t id);
    void rename_member(uint32_t id, std::string name);

    std::vector<unsigned char> serialize();
    static MemberList deserialize(std::vector<unsigned char> data);

    std::vector<MemberList*> filter_member_name(std::string query, DataEntry::SORT_TYPE sort = DataEntry::SORT_TYPE::NONE);
};


#endif
