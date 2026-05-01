#pragma once

#include "model/Point2D.h"

#include <string>
#include <vector>

class Robot {
public:
    Robot(const std::string& name);

    std::string getName() const;
    int getX() const;
    int getY() const;
    int getCurrentHistoryIndex() const;
    const std::vector<Point2D>& getHistory() const;
    int getTotalDistanceMoved() const;
    bool isUpgraded() const;

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void undo();
    void redo();

    bool canUndo() const;
    bool canRedo() const;

    void saveToFile(const std::string& filePath) const;
    void loadFromFile(const std::string& filePath);

private:
    void moveTo(int newX, int newY);
    void recordPosition();

    static const int gridSize = 5;
    std::string name_;
    int x = 2;
    int y = 2;
    int currentHistoryIndex = 0;
    int totalDistanceMoved = 0;
    std::vector<Point2D> history = {{2, 2}};
};
