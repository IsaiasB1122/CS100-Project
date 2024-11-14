
#include <MemberList.hpp>

MemberList::MemberList() {
    next_members_id = 0;
}

MemberList::~MemberList() {
    for (auto c : members) {
        delete c;
    }
}