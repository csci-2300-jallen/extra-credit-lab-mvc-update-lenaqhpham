#include "model/Robot.h"

#include <fstream>

Robot::Robot(const std::string& name)
    : name_(name) {}

std::string Robot::getName() const {
    return name_;
}

int Robot::getX() const {
    return x;
}

int Robot::getY() const {
    return y;
}

int Robot::getCurrentHistoryIndex() const {
    return currentHistoryIndex;
}

const std::vector<Point2D>& Robot::getHistory() const {
    return history;
}

int Robot::getTotalDistanceMoved() const {
    return totalDistanceMoved;
}

bool Robot::isUpgraded() const {
    return totalDistanceMoved >= 10;
}

void Robot::moveUp() {
    int distance = isUpgraded() ? 2 : 1;
    moveTo(x, y - distance);
}

void Robot::moveDown() {
    int distance = isUpgraded() ? 2 : 1;
    moveTo(x, y + distance);
}

void Robot::moveLeft() {
    int distance = isUpgraded() ? 2 : 1;
    moveTo(x - distance, y);
}

void Robot::moveRight() {
    int distance = isUpgraded() ? 2 : 1;
    moveTo(x + distance, y);
}

void Robot::undo() {
    if (!canUndo()) {
        return;
    }

    currentHistoryIndex--;
    x = history[currentHistoryIndex].x;
    y = history[currentHistoryIndex].y;
}

void Robot::redo() {
    if (!canRedo()) {
        return;
    }

    currentHistoryIndex++;
    x = history[currentHistoryIndex].x;
    y = history[currentHistoryIndex].y;
}

bool Robot::canUndo() const {
    return currentHistoryIndex > 0;
}

bool Robot::canRedo() const {
    return currentHistoryIndex < static_cast<int>(history.size()) - 1;
}

void Robot::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath);

    file << name_ << '\n';
    file << currentHistoryIndex << '\n';
    file << totalDistanceMoved << '\n';

    for (const Point2D& point : history) {
        file << point.x << ' ' << point.y << '\n';
    }
}

void Robot::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);

    std::string loadedName;
    int loadedIndex = 0;
    int loadedDistance = 0;
    std::getline(file, loadedName);
    file >> loadedIndex;
    file >> loadedDistance;

    int pointX = 0;
    int pointY = 0;
    std::vector<Point2D> loadedHistory;
    for (int index = 0; index <= loadedIndex; index++) {
        file >> pointX >> pointY;
        loadedHistory.push_back({pointX, pointY});
        x = pointX;
        y = pointY;
    }

    name_ = loadedName;
    history = loadedHistory;
    currentHistoryIndex = loadedIndex;
    totalDistanceMoved = loadedDistance;
}

void Robot::moveTo(int newX, int newY) {
    if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) {
        return;
    }

    if (newX == x && newY == y) {
        return;
    }

    // Calculate distance moved (Manhattan distance)
    int dx = (newX > x) ? (newX - x) : (x - newX);
    int dy = (newY > y) ? (newY - y) : (y - newY);
    totalDistanceMoved += (dx + dy);

    x = newX;
    y = newY;
    recordPosition();
}

void Robot::recordPosition() {
    if (canRedo()) {
        history.erase(history.begin() + currentHistoryIndex + 1, history.end());
    }

    history.push_back({x, y});
    currentHistoryIndex = static_cast<int>(history.size()) - 1;
}
