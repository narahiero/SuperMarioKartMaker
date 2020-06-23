//////////////////////////////////////////////////
//  Copyright (c) 2020 Nara Hiero
//
// This file is licensed under GPLv3+
// Refer to the `License.txt` file included.
//////////////////////////////////////////////////

#include "UI/MenuBar.hpp"

#include "UI/CoreCallbacks.hpp"

MenuBar::MenuBar(QWidget* parent) : QMenuBar(parent)
{
    createFileMenu();

    connectAll();
}

MenuBar::~MenuBar() = default;

void MenuBar::createFileMenu()
{
    QMenu* file = addMenu(tr("&File"));

    file->addAction(tr("&New..."), this, &MenuBar::newProject, QKeySequence::New);

    file->addSeparator();

    m_closeProject = file->addAction(tr("&Close Project"), this, &MenuBar::closeProject);
    m_closeProject->setDisabled(true);

    file->addSeparator();

    file->addAction(tr("E&xit"), this, &MenuBar::exit, QKeySequence::Quit);
}

void MenuBar::connectAll()
{
    connect(CoreCallbacks::instance(), &CoreCallbacks::activeProjectChanged,
        this, &MenuBar::activeProjectChanged);
}

void MenuBar::activeProjectChanged(const std::shared_ptr<Project>& project)
{
    m_closeProject->setEnabled(project != nullptr);
}
