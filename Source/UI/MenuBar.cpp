//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/MenuBar.hpp"

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent)
{
    createFileMenu();
}

MenuBar::~MenuBar() = default;

void MenuBar::createFileMenu()
{
    QMenu* file = addMenu(tr("&File"));

    file->addAction(tr("E&xit"), this, &MenuBar::exit, QKeySequence::Quit);
}
