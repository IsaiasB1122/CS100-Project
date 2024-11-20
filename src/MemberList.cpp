
#include <MemberList.hpp>

MemberList::MemberList() {
    next_members_id = 0;
}

MemberList::~MemberList() {
    for (auto c : members) {
        delete c;
    }
}

const std::vector<Member*> MemberList::get_members() {
    std::vector<Member*> members;
    for (auto m : this->members) members.push_back(m);
    return members;
}

const Member& MemberList::get_member(uint32_t id) {
    for (auto m = this->members.begin(); m < members.end(); m += 1) { 
        if ((m*)->id == id) return *m;
    }
    return nullptr;
}

const Member& MemberList::get_member(std::string name) {
    for (auto m = this->members.begin(); m < members.end(); m += 1) { 
        if ((m*)->name == name) return *m;
    }
    return nullptr;
}

const Member& MembersList::add_member(Member category) {
    Members* member = new Member(this);
    member->name = name;
    member->id = next_members_id;
    this->next_members_id += 1;

    return member;
}

void remove_member(uint32_t id) {
    for (auto m = this->members.begin(); m < this->members.end(); m += 1) {
        if (m*->id == id) {
            this->members.erase(m);
            delete member;
        }
    }
}