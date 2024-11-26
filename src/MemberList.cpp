
#include <MemberList.hpp>

// TEMPORAY FOR STUBS, REMOVE WHEN ACTUALLY IMPLEMENTING!
const Member dummy(0,"dummy");

MemberList::MemberList() {
    next_members_id = 0;
}

MemberList::~MemberList() {
    for (auto c : members) {
        delete c;
    }
}

const std::vector<Member*> MemberList::get_members() {
    return std::vector<Member*>{};
}
const Member& MemberList::get_member(uint32_t id) {
    return dummy;
}
const Member& MemberList::get_member(std::string name) {
    return dummy;
}
const Member& MemberList::add_member(Member category) {
    return dummy;
}
void MemberList::remove_member(uint32_t id) {

}
void MemberList::rename_member(uint32_t id, std::string name) { 

}
std::vector<MemberList*> MemberList::filter_member_name(std::string query, DataEntry::SORT_TYPE sort) {
    return std::vector<MemberList*>{};
}