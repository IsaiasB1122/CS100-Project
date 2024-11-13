
#include <TaskBoard.hpp>

TaskBoard::TaskBoard(Directory* _parent) {
    this->parent = _parent;
    this->tasks_changed = true;
    this->members_changed = true;
    this->notes_changed = true;
    this->categories_changed = true;
}

TaskBoard::~TaskBoard() {
    for (auto task : tasks) {
        delete task;
    }
}

// fspath TaskBoard::get_members_path() {
//     return this->parent_path / this->name / "member_list.cml";
// }

// fspath TaskBoard::get_notes_path() {
//     return this->parent_path / this->name / "note_list.cnl";
// }

// fspath TaskBoard::get_categories_path() {
//     return this->parent_path / this->name / "note_list.ccl";
// }

// int TaskBoard::write() {
//     // write metadata
//     FILE* metadata = std::fopen(this->get_metadata_path().string().c_str(),"wb");
//     //if (!metadata) throw Directory::invalid_path("Path invalid.");

//     // TODO: make schema for this file
// }