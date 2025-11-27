// TODO: Imply interfaces declared in the Recorder.hpp.
void Recorder::add(int line, Statement* stmt) {
    lines_[line] = stmt;
}
void Recorder::remove(int line) {
    lines_.erase(line);
}
const Statement* Recorder::get(int line) const noexcept {
    return lines_[line];
}
bool Recorder::hasLine(int line) const noexcept {
    if (lines_.find(line) == lines_.end()) {
        return false;
    }
    else return true;
}
void Recorder::clear() noexcept {
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
