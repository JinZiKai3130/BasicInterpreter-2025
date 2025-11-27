// TODO: Imply interfaces declared in the Recorder.hpp.
#include "Recorder.hpp"
#include <iostream>


Recorder::~Recorder() {
    this->clear();
}

void Recorder::add(int line, Statement* stmt) {
    auto it = lines_.find(line);
    if (it != lines_.end()) {
        delete it->second;
    }
    lines_[line] = stmt;
}
void Recorder::remove(int line) {
    auto it = lines_.find(line);
    if (it != lines_.end()) {
        delete it->second;
        lines_.erase(it);
    }
}
const Statement* Recorder::get(int line) const noexcept {
    auto it = lines_.find(line);
    if (it != lines_.end()) {
        return it->second;
    }
    return nullptr;
}
bool Recorder::hasLine(int line) const noexcept {
    if (lines_.find(line) == lines_.end()) {
        return false;
    }
    else return true;
}
void Recorder::clear() noexcept {
    for (auto it = lines_.begin(); it != lines_.end(); ++it) {
        delete it->second;
    }
    lines_.clear();
}
void Recorder::printLines() const {
    for (auto it = lines_.begin(); it != lines_.end(); ++it) {
        std::cout << it->second->text() << std::endl;
    }
}
int Recorder::nextLine(int line) const noexcept {
    auto it = lines_.find(line);
    ++it;
    if (it == lines_.end()) return -1;
    else return it->first;
}

int Recorder::getMinLine() const noexcept {
    if (lines_.empty()) {
        return -1; // 配合Program中的size()检查，实际不会走到这里
    }
    return lines_.begin()->first; // lines_为std::map，按行号升序排列
}