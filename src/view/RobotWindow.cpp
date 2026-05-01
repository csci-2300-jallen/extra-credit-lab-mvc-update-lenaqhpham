#include "view/RobotWindow.h"

#include "controller/RobotController.h"
#include "view/RobotGridWidget.h"

#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

RobotWindow::RobotWindow() {
    setWindowTitle("Robot History Serialization");

    // This lets the window receive keyboard input.
    setFocusPolicy(Qt::StrongFocus);
    resize(360, 430);

    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    grid = new RobotGridWidget(this);
    QLabel* hint = new QLabel("Use WASD keys to move the robot", this);
    hint->setAlignment(Qt::AlignCenter);

    QHBoxLayout* historyLayout = new QHBoxLayout();
    undoButton = new QPushButton("UNDO", this);
    redoButton = new QPushButton("REDO", this);
    undoButton->setFocusPolicy(Qt::NoFocus);
    redoButton->setFocusPolicy(Qt::NoFocus);
    historyLayout->addWidget(undoButton);
    historyLayout->addWidget(redoButton);

    QHBoxLayout* fileLayout = new QHBoxLayout();
    saveButton = new QPushButton("Save History", this);
    loadButton = new QPushButton("Load History", this);
    saveButton->setFocusPolicy(Qt::NoFocus);
    loadButton->setFocusPolicy(Qt::NoFocus);
    fileLayout->addWidget(saveButton);
    fileLayout->addWidget(loadButton);

    statusLabel = new QLabel("", this);
    statusLabel->setAlignment(Qt::AlignCenter);

    mainLayout->addWidget(hint);
    mainLayout->addWidget(grid, 0, Qt::AlignCenter);
    mainLayout->addLayout(historyLayout);
    mainLayout->addLayout(fileLayout);
    mainLayout->addWidget(statusLabel);

    setCentralWidget(central);
}

void RobotWindow::setRobotPosition(int x, int y) {
    grid->setRobotPosition(x, y);
}

void RobotWindow::setController(RobotController* newController) {
    controller = newController;
}

void RobotWindow::setUndoEnabled(bool enabled) {
    undoButton->setEnabled(enabled);
}

void RobotWindow::setRedoEnabled(bool enabled) {
    redoButton->setEnabled(enabled);
}

void RobotWindow::setStatusText(const QString& text) {
    statusLabel->setText(text);
}

QPushButton* RobotWindow::getUndoButton() const {
    return undoButton;
}

QPushButton* RobotWindow::getRedoButton() const {
    return redoButton;
}

QPushButton* RobotWindow::getSaveButton() const {
    return saveButton;
}

QPushButton* RobotWindow::getLoadButton() const {
    return loadButton;
}

void RobotWindow::keyPressEvent(QKeyEvent* event) {
    if (controller != nullptr && controller->handleKeyPress(event)) {
        return;
    }

    QMainWindow::keyPressEvent(event);
}
