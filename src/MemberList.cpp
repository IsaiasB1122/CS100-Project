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
    for (auto it = members.begin(); it != members.end(); ++it) {
        if ((*it)->id == id) return **it; 
    }
    throw std::runtime_error("Member not found");
}

const Member& MemberList::get_member(std::string name) {
    for (auto it = members.begin(); it != members.end(); ++it) {
        if ((*it)->name == name) return **it; 
    }
    throw std::runtime_error("Member not found");
}

const Member& MemberList::add_member(Member member) {
    Member* new_member = new Member();
    new_member->name = member.name;
    new_member->id = next_members_id;
    this->next_members_id += 1;

    this->members.push_back(new_member);

    return *new_member;

}

void MemberList::remove_member(uint32_t id) {
    for (auto m = this->members.begin(); m != this->members.end(); ) {
        if ((*m)->id == id) {
            delete *m;
            m = this->members.erase(m); 
        } else {
            ++m; 
        }
    }
}